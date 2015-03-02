#ifndef PROJET_H
#define PROJET_H

#include <QDir>
#include <QFile>
#include <QImage>

class Projet
{
    public:

        static Projet* create(QString &name, QDir &workspace, QFile &video, int frequenceVideo);
        static Projet* open(QDir &path);
        void save();
        void saveAs(QDir &projet);
        void exportImage(QDir &dir);
        void exportVideo(QDir &dir);


        QImage* getImageVideo(int number);
        QImage* getImageOutput(int number);

        QString getName();
        QString getWorkspace();
        QString getVideo();
        int getFrequence();

        int getNbFrameVideo();

        static const QSize sizeOutput;

    private:
        Projet();

        QDir* _project;
        QDir* _input;
        QDir* _output;
        QFile* _video;
        int _frequenceVideo;
        int _nbFrameVideo;

        QString _origineVideo;

        std::vector<QImage*> _imagesVideo;
        std::vector<QImage*> _imagesOutput;
};

#endif // PROJET_H
