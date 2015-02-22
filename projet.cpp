#include "projet.h"
#include <QtDebug>
#include <QProcess>

Projet::Projet(QString &name, QDir &workspace, QFile &video, int frequence)
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
                video.copy(_project->path()+"/input/video");
                _video = new QFile(_project->path()+"/input/video");

                QProcess process;
                process.startDetached("avconv -i " + _project->path() +"/input/video -vsync 1 -r " +  QString::number(frequence) + " -y " + _project->path() + "/input/img%d.jpg");
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
