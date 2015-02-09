#include "projet.h"
#include <QtDebug>
#include <QProcess>

Projet::Projet(QString &name, QDir &workspace, QFile &video, int frequence)
{
    if(workspace.exists() && video.exists() && workspace.mkdir(name))
    {
        _project = new QDir(workspace.path()+"/"+name);
        qDebug() << _project->path();
        _project->mkdir("input");
        video.copy(_project->path()+"/input/video");
        _video = new QFile(_project->path()+"/input/video");

        QProcess process;
        process.startDetached("avconv -i " + _project->path() +"/input/video -vsync 1 -r 8 -y " + _project->path() + "/input/img%d.jpg");
    }
}
