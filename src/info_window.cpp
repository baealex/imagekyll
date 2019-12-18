#include "InfoWindow.h"
#include "ui_info_window.h"

Infomation::Infomation(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Infomation)
{
    setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
    setWindowFlags(this->windowFlags() & ~Qt::WindowContextHelpButtonHint);

    ui->setupUi(this);

    setWindowTitle("Infomation");
}

Infomation::~Infomation()
{
    delete ui;
}

void Infomation::on_RightBtn_clicked()
{
    close();
}
