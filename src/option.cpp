#include "option.h"
#include "ui_option.h"

Option::Option(MainWindow &ref, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Option),
    mRef(ref)
{
    setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
    setWindowFlags(this->windowFlags() & ~Qt::WindowContextHelpButtonHint);

    ui->setupUi(this);

    setWindowTitle("Option");
}

Option::~Option()
{
    delete ui;
}

void Option::on_BlackTheme_clicked()
{
    mRef.ThemeSelect(1);
}

void Option::on_WhiteTheme_clicked()
{
    mRef.ThemeSelect(2);
}

void Option::on_PurpleTheme_clicked()
{
    mRef.ThemeSelect(3);
}

void Option::on_spinBox_valueChanged(int arg1)
{
    mRef.SetPreviewSize(arg1);
}

void Option::on_CloseBtn_clicked()
{
    close();
}
