#include "ImageCompressor.h"
#include "ui_imagecompressor.h"

ImageCompressor::ImageCompressor(QString file, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ImageCompressor)
{
    setWindowFlags(this->windowFlags() & ~Qt::WindowContextHelpButtonHint);
    ui->setupUi(this);

    filePath = file;

    ui->imagePreview->setPixmap(
        QPixmap(filePath).scaled(
            ui->imagePreview->width(), ui->imagePreview->height(), Qt::KeepAspectRatio));
}

void ImageCompressor::on_compSlider_valueChanged(int value)
{
    QPixmap(filePath).save("temp.jpg", nullptr, value);
    ui->okButton->setText(QString::number((double)QFile("temp.jpg").size()/1048576, 'f', 2) + "MB");

    ui->imagePreview->setPixmap(
        QPixmap("temp.jpg").scaled(
            ui->imagePreview->width(), ui->imagePreview->height(), Qt::KeepAspectRatio));
}

void ImageCompressor::on_okButton_clicked()
{
    QFile::remove(filePath);
    QFile::copy("temp.jpg", filePath);
    close();
}

ImageCompressor::~ImageCompressor()
{
    delete ui;
}
