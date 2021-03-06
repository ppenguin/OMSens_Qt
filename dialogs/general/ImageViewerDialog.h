#ifndef IMAGEVIEWER_H
#define IMAGEVIEWER_H

#include <QDialog>
#include <QLabel>
#include <QScrollArea>
#include <QString>

class ImageViewerDialog : public QDialog
{
    Q_OBJECT

public:
    ImageViewerDialog(QString filePath, QWidget *parent = 0);
    static QStringList compatibleMIMETypes();

private:
    bool loadFile(const QString &);
    void setImage(const QImage &newImage);

    QImage image;
    QLabel *imageLabel;
    QScrollArea *scrollArea;

};

#endif // IMAGEVIEWER_H
