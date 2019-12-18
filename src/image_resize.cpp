#include "ImageResize.h"
#include "ui_image_resize.h"

image_resizer::image_resizer(ImageEditor &ref, int w, int h, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::image_resizer),
    mRef(ref)
    {
    setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
    setWindowFlags(this->windowFlags() & ~Qt::WindowContextHelpButtonHint);

    ui->setupUi(this);

    setWindowTitle("Image Resize");

    ui->spinWidth->setValue(w);
    ui->spinHeight->setValue(h);

    __Width = w;
    __Height = h;

    int x = gdc(w,h);
    mWidth = w/x;
    mHeight = h/x;
    if(mRef.config.ResizeRate) {
        ui->checkBox->setChecked(true);
    }
}

int image_resizer::gdc(int a, int b)
{
    int temp = 0;

    int i, j=(a<b)?a:b;
    for(i=1; i<=j; i++) {
        if(a%i==0 && b%i==0) {
            temp=i;
        }
    }

    return temp;
}

image_resizer::~image_resizer()
{
    delete ui;
}

void image_resizer::on_spinWidth_valueChanged(int arg1)
{
    if(checkRatio && !changeValue)
    {
        changeValue = true;
        ui->spinHeight->setValue(mHeight * (int)(arg1/mWidth));
        changeValue = false;
    }
}

void image_resizer::on_spinHeight_valueChanged(int arg1)
{
    if(checkRatio && !changeValue)
    {
        changeValue = true;
        ui->spinWidth->setValue(mWidth * (int)(arg1/mHeight));
        changeValue = false;
    }
}

void image_resizer::on_checkBox_stateChanged(int arg1)
{
    Q_UNUSED(arg1);
    if(checkRatio)
    {
        checkRatio = false;
    }
    else
    {
        checkRatio = true;
    }
}

void image_resizer::on_apply_btn_clicked()
{
    mRef.Image_Size_Change(ui->spinWidth->text().toInt(),
                           ui->spinHeight->text().toInt());
}

void image_resizer::on_cancel_btn_clicked()
{
    close();
}
