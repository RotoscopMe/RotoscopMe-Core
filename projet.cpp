#include "projet.h"
#include <QtDebug>
#include <QProcess>

const QSize Projet::sizeOutput = QSize(1002, 561);

Projet::Projet()
{

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

Projet* Projet::create(QString &name, QDir &workspace, QFile &video, int frequenceVideo)
{
    Projet *projet = new Projet();

    projet->_frequenceVideo = frequenceVideo;

    if(workspace.exists())
    {
        if(video.exists())
        {
            if(workspace.mkdir(name))
            {
                projet->_project = new QDir(workspace.path()+"/"+name);
                qDebug() << projet->_project->path();
                projet->_project->mkdir("input");
                projet->_input = new QDir(projet->_project->path()+"/input");
                projet->_project->mkdir("output");
                projet->_output = new QDir(projet->_project->path()+"/output");
                video.copy(projet->_project->path()+"/input/video");
                projet->_video = new QFile(projet->_project->path()+"/input/video");

                QProcess process;
                process.start("avconv -i " + projet->_project->path() +"/input/video -vsync 1 -s " + QString::number(sizeOutput.width()) + "x" + QString::number(projet->sizeOutput.height()) + " -r " +  QString::number(projet->_frequenceVideo) + " -y " + projet->_project->path() + "/input/img%d.bmp");
                process.waitForFinished(-1);

                QStringList filters;
                filters << "img*.bmp";
                projet->_nbFrameVideo = projet->_input->entryList(filters).count();
                qDebug() << "Nombre de frames : " << projet->_nbFrameVideo;

                QFile file(projet->_project->path() + "/info");
                file.open(QIODevice::WriteOnly | QIODevice::Text);
                QTextStream out(&file);

                out << QString::number(projet->_frequenceVideo) << "\n" << QString::number(projet->_nbFrameVideo);

                file.close();

                for(int i = 1; i <= projet->_nbFrameVideo; i++)
                {
                    projet->_imagesVideo.push_back(new QImage(projet->_input->path()+"/img"+QString::number(i)+".bmp"));
                    QImage *image = new QImage(projet->sizeOutput.width(),projet->sizeOutput.height(),QImage::Format_ARGB32);
                    image->fill(Qt::white);
                    image->save(projet->_output->path() + "/img" + QString::number(i) + ".bmp");
                    projet->_imagesOutput.push_back(image);
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

    return projet;
}

Projet* Projet::open(QDir &path)
{
    Projet *projet = new Projet();

    if(path.exists())
    {
        projet->_project = new QDir(path.path());
        projet->_input = new QDir(path.path() + "/input");
        projet->_output = new QDir(path.path() + "/output");

        if(projet->_input->exists())
        {
            projet->_video = new QFile(projet->_input->path() + "/video");
        }
        else
        {
            throw QString("Ce projet est mal formé");
        }
    }
    else
    {
        throw QString("Ce projet n'existe pas");
    }

    return projet;
}

void Projet::save()
{
    for(size_t i = 0; i < _imagesOutput.size(); i++)
    {
        _imagesOutput.at(i)->save(_output->path()+"/img" + QString::number(i) + ".bmp");
    }
}
