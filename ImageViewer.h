#ifndef IMAGEVIEWER_H
#define IMAGEVIEWER_H

#include <QDialog>
#include <QLabel>
#include <QScrollArea>
#include <QString>

class ImageViewer : public QDialog
{
    Q_OBJECT

public:
    ImageViewer(QWidget *parent = 0);

private:
    bool loadFile(const QString &);
    void setImage(const QImage &newImage);

    QImage image;
    QLabel *imageLabel;
    QScrollArea *scrollArea;

};

#endif // IMAGEVIEWER_H
