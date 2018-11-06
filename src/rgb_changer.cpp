#include "rgb_changer.h"
#include "ui_rgb_changer.h"

#include <QImage>

rgb_changer::rgb_changer(MainWindow &ref, int Mode, int r, int g, int b, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::rgb_changer),
    mRef(ref),
    ModeSelect(Mode)
{
    rColor = 0;
    gColor = 0;
    bColor = 0;
    ui->setupUi(this);

    switch (ModeSelect) {
    case 0:
        ui->redSlider->setMaximum(255);
        ui->redSlider->setMinimum(-255);
        ui->redSlider->setValue(r);
        ui->greenSlider->setMaximum(255);
        ui->greenSlider->setMinimum(-255);
        ui->greenSlider->setValue(g);
        ui->blueSlider->setMaximum(255);
        ui->blueSlider->setMinimum(-255);
        ui->blueSlider->setValue(b);
        break;
    case 1:
        ui->redSlider->setMaximum(255);
        ui->redSlider->setMinimum(0);
        ui->redSlider->setValue(r);
        ui->greenSlider->setMaximum(255);
        ui->greenSlider->setMinimum(0);
        ui->greenSlider->setValue(g);
        ui->blueSlider->setMaximum(255);
        ui->blueSlider->setMinimum(0);
        ui->blueSlider->setValue(b);
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
