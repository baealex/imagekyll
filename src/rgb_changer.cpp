#include "rgb_changer.h"
#include "ui_rgb_changer.h"

#include <QImage>

rgb_changer::rgb_changer(MainWindow &ref, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::rgb_changer),
    imageRef(ref)
{
    rColor = 0;
    gColor = 0;
    bColor = 0;
    ui->setupUi(this);
}

rgb_changer::~rgb_changer()
{
    delete ui;
}

void rgb_changer::on_redSlider_valueChanged(int value)
{
    QImage image = imageRef.pixmap.toImage();
    QRgb rgb;
    int r,g,b;
    rColor = value;
    for(int y = 0; y < image.height(); y++)
    {
        for(int x = 0 ; x < image.width(); x++)
        {
            rgb = image.pixel(x,y);
            r = qRed(rgb) + rColor;
            g = qGreen(rgb) + gColor;
            b = qBlue(rgb) + bColor;
            if(r < 0) r = 0;
            else if(r > 255) r = 255;
            if(g < 0) g = 0;
            else if(g > 255) g = 255;
            if(b < 0) b = 0;
            else if(b > 255) b = 255;
            image.setPixel(x,y,qRgb(r,g,b));
        }
    }
    QPixmap preview = QPixmap::fromImage(image);
    QGraphicsPixmapItem *item = new QGraphicsPixmapItem(preview);
    imageRef.scene->addItem(item);
}

void rgb_changer::on_greenSlider_valueChanged(int value)
{
    QImage image = imageRef.pixmap.toImage();
    QRgb rgb;
    int r,g,b;
    gColor = value;
    for(int y = 0; y < image.height(); y++)
    {
        for(int x = 0 ; x < image.width(); x++)
        {
            rgb = image.pixel(x,y);
            r = qRed(rgb) + rColor;
            g = qGreen(rgb) + gColor;
            b = qBlue(rgb) + bColor;
            if(r < 0) r = 0;
            else if(r > 255) r = 255;
            if(g < 0) g = 0;
            else if(g > 255) g = 255;
            if(b < 0) b = 0;
            else if(b > 255) b = 255;
            image.setPixel(x,y,qRgb(r,g,b));
        }
    }
    QPixmap preview = QPixmap::fromImage(image);
    QGraphicsPixmapItem *item = new QGraphicsPixmapItem(preview);
    imageRef.scene->addItem(item);
}

void rgb_changer::on_blueSlider_valueChanged(int value)
{
    QImage image = imageRef.pixmap.toImage();
    QRgb rgb;
    int r,g,b;
    bColor = value;
    for(int y = 0; y < image.height(); y++)
    {
        for(int x = 0 ; x < image.width(); x++)
        {
            rgb = image.pixel(x,y);
            r = qRed(rgb) + rColor;
            g = qGreen(rgb) + gColor;
            b = qBlue(rgb) + bColor;
            if(r < 0) r = 0;
            else if(r > 255) r = 255;
            if(g < 0) g = 0;
            else if(g > 255) g = 255;
            if(b < 0) b = 0;
            else if(b > 255) b = 255;
            image.setPixel(x,y,qRgb(r,g,b));
        }
    }
    QPixmap preview = QPixmap::fromImage(image);
    QGraphicsPixmapItem *item = new QGraphicsPixmapItem(preview);
    imageRef.scene->addItem(item);
}
