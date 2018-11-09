#include "rgb_changer.h"
#include "ui_rgb_changer.h"

#include <QImage>

rgb_changer::rgb_changer(MainWindow &ref, int Mode, int r, int g, int b, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::rgb_changer),
    mRef(ref),
    ModeSelect(Mode)
{
    this->setWindowFlags(this->windowFlags() & ~Qt::WindowContextHelpButtonHint);

    rColor = 0;
    gColor = 0;
    bColor = 0;
    ui->setupUi(this);

    switch (ModeSelect) {
    case 0:
        setWindowTitle("Image RGB");
        ui->redSlider->setMaximum(255);
        ui->redSlider->setMinimum(-255);
        ui->redSlider->setValue(r);
        ui->redSlider->setStyleSheet("QSlider::groove:horizontal {border: 1px solid #999999; height: 8px; background:qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(0, 0, 0, 255), stop:1 rgba(255, 0, 0, 255)); margin: 2px 0;}");
        ui->greenSlider->setMaximum(255);
        ui->greenSlider->setMinimum(-255);
        ui->greenSlider->setValue(g);
        ui->greenSlider->setStyleSheet("QSlider::groove:horizontal {border: 1px solid #999999; height: 8px; background:qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(0, 0, 0, 255), stop:1 rgba(0, 255, 0, 255)); margin: 2px 0;}");
        ui->blueSlider->setMaximum(255);
        ui->blueSlider->setMinimum(-255);
        ui->blueSlider->setValue(b);
        ui->blueSlider->setStyleSheet("QSlider::groove:horizontal {border: 1px solid #999999; height: 8px; background:qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(0, 0, 0, 255), stop:1 rgba(0, 0, 255, 255)); margin: 2px 0;}");
        break;
    case 1:
        setWindowTitle("Brush Color");
        ui->redSlider->setMaximum(255);
        ui->redSlider->setMinimum(0);
        ui->redSlider->setValue(r);
        ui->redSlider->setStyleSheet("QSlider::groove:horizontal {border: 1px solid #999999; height: 8px; background:qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(0, 0, 0, 255), stop:1 rgba(255, 0, 0, 255)); margin: 2px 0;}");
        ui->greenSlider->setMaximum(255);
        ui->greenSlider->setMinimum(0);
        ui->greenSlider->setValue(g);
        ui->greenSlider->setStyleSheet("QSlider::groove:horizontal {border: 1px solid #999999; height: 8px; background:qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(0, 0, 0, 255), stop:1 rgba(0, 255, 0, 255)); margin: 2px 0;}");
        ui->blueSlider->setMaximum(255);
        ui->blueSlider->setMinimum(0);
        ui->blueSlider->setValue(b);
        ui->blueSlider->setStyleSheet("QSlider::groove:horizontal {border: 1px solid #999999; height: 8px; background:qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(0, 0, 0, 255), stop:1 rgba(0, 0, 255, 255)); margin: 2px 0;}");
        break;
    case 2:
        // redSlider =
        // greenSlider =
        // blueSluder =
        break;
    }
}

rgb_changer::~rgb_changer()
{
    delete ui;
}

void rgb_changer::on_redSlider_valueChanged(int value)
{
    switch (ModeSelect) {
    case 0:
        mRef.Image_RGB_Preview_Change(rColor=value, gColor, bColor);
        break;
    case 1:
        mRef.setColorStyle(rColor=value, gColor, bColor);
        break;
    }
}

void rgb_changer::on_greenSlider_valueChanged(int value)
{
    switch (ModeSelect) {
        case 0:
            mRef.Image_RGB_Preview_Change(rColor, gColor=value, bColor);
            break;
        case 1:
            mRef.setColorStyle(rColor, gColor=value, bColor);
            break;
    }
}

void rgb_changer::on_blueSlider_valueChanged(int value)
{
    switch (ModeSelect) {
        case 0:
            mRef.Image_RGB_Preview_Change(rColor, gColor, bColor=value);
            break;
        case 1:
            mRef.setColorStyle(rColor, gColor, bColor=value);
            break;
    }
}

void rgb_changer::on_redSlider_sliderReleased()
{
    switch (ModeSelect) {
    case 0:
        mRef.Image_RGB_Change(rColor, gColor, bColor);
        break;
    }
}

void rgb_changer::on_greenSlider_sliderReleased()
{
    switch (ModeSelect) {
    case 0:
        mRef.Image_RGB_Change(rColor, gColor, bColor);
        break;
    }
}

void rgb_changer::on_blueSlider_sliderReleased()
{
    switch (ModeSelect) {
    case 0:
        mRef.Image_RGB_Change(rColor, gColor, bColor);
        break;
    }
}
