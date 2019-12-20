#ifndef IMAGECOMPRESSOR_H
#define IMAGECOMPRESSOR_H

#include <QDialog>
#include <QFile>

namespace Ui {
class ImageCompressor;
}

class ImageCompressor : public QDialog
{
    Q_OBJECT

public:
    explicit ImageCompressor(QString file, QWidget *parent = nullptr);
    ~ImageCompressor();

private slots:
    void on_compSlider_valueChanged(int value);
    void on_okButton_clicked();

private:
    Ui::ImageCompressor *ui;
    QString filePath;
};

#endif // IMAGECOMPRESSOR_H
