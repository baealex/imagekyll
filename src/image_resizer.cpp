#include "image_resizer.h"
#include "ui_image_resizer.h"

image_resizer::image_resizer(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::image_resizer)
{
    ui->setupUi(this);
}

image_resizer::~image_resizer()
{
    delete ui;
}
