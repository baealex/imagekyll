#include "BlogRepo.h"
#include "ui_blogrepo.h"

BlogRepo::BlogRepo(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::BlogRepo)
{
    ui->setupUi(this);

    ui->appendRopoButton->setText("Append Blog Repo");
}

void BlogRepo::on_appendRopoButton_clicked()
{
    ui->appendRopoButton->setText("zzz");
}

BlogRepo::~BlogRepo()
{
    delete ui;
}
