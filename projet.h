#ifndef PROJET_H
#define PROJET_H

#include <QDir>
#include <QFile>

class Projet
{
    public:
        Projet(QString &name, QDir &workspace, QFile &video, int frequence);

    private:
        QDir* _project;
        QDir* _input;
        QFile* _video;
        int _frequenceVideo;
        int _nbFrameVideo;
};

#endif // PROJET_H
