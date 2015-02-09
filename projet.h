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
        QFile* _video;
        int _frequenceVideo;
};

#endif // PROJET_H
