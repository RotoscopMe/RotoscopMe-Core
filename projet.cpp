#include "projet.h"
#include <QtDebug>
#include <QProcess>

Projet::Projet(QString &name, QDir &workspace, QFile &video, int frequence) : _frequenceVideo(frequence)
{
    if(workspace.exists())
    {
        if(video.exists())
        {
            if(workspace.mkdir(name))
            {
                _project = new QDir(workspace.path()+"/"+name);
                qDebug() << _project->path();
                _project->mkdir("input");
                _input = new QDir(_project->path()+"/input");
                _project->mkdir("output");
                _output = new QDir(_project->path()+"/output");
                video.copy(_project->path()+"/input/video");
                _video = new QFile(_project->path()+"/input/video");

                QProcess process;
                process.start("avconv -i " + _project->path() +"/input/video -vsync 1 -r " +  QString::number(_frequenceVideo) + " -y " + _project->path() + "/input/img%d.bmp");
                process.waitForFinished(-1);

                QStringList filters;
                filters << "img*.bmp";
                _nbFrameVideo = _input->entryList(filters).count();
                qDebug() << "Nombre de frames : " << _nbFrameVideo;

                for(int i = 1; i <= _nbFrameVideo; i++)
                {
                    QImage *image = new QImage(_input->path()+"/img"+QString::number(i)+".bmp");
                    _imagesVideo.push_back(new QImage(image->scaled(1280,720)));
                    delete image;
                    _imagesOutput.push_back(new QImage(1280,720,QImage::Format_ARGB32));
                }
            }
            else
            {
                throw QString("Ce projet existe déjà");
            }
        }
        else
        {
            throw QString("La vidéo n'existe pas");
        }
    }
    else
    {
        throw QString("Le workspace n'existe pas");
    }
}

QImage* Projet::getImageVideo(int number)
{
    return _imagesVideo.at(number);
}

QImage* Projet::getImageOutput(int number)
{
    return _imagesOutput.at(number);
}

int Projet::getNbFrameVideo()
{
    return _nbFrameVideo;
}
