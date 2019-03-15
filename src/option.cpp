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

    ui->ColorPreviewSize->setValue(mRef.config.PreviewSize);
    ui->CUndoSize->setValue(mRef.config.UndoSize);
    ui->SaveCompress->setValue(mRef.config.SaveCompress);
    init = false;
    if(!mRef.config.ResizeRate) {
        ui->ResizeRate->setChecked(true);
    }
    if(!mRef.config.SaveAsk) {
        ui->SaveAsk->setChecked(true);
    }
    init = true;
}

Option::~Option()
{
    if(mRef.config.UndoSize != UndoSizeTemp) {
        mRef.config.UndoSize = UndoSizeTemp;
        mRef.config.SAVE();
        QMessageBox::warning(this, "Notify", "Number of 'undo' has been changed. Please restart the program. Otherwise an error will occur.");
    }
    delete ui;
}

void Option::on_CloseBtn_clicked()
{
    close();
}

void Option::on_ThemeBlack_clicked()
{
    mRef.ThemeSelect(1);
}

void Option::on_ThemeWhie_clicked()
{
    mRef.ThemeSelect(2);
}

void Option::on_ThemePurple_clicked()
{
    mRef.ThemeSelect(3);
}

void Option::on_ColorPreviewSize_valueChanged(int arg1)
{
    mRef.config.PreviewSize = arg1;
}

void Option::on_CUndoSize_valueChanged(int arg1)
{
    UndoSizeTemp = arg1;
}

void Option::on_SaveAsk_stateChanged(int arg1)
{
    Q_UNUSED(arg1);
    if(init) {
        if(mRef.config.SaveAsk) {
            mRef.config.SaveAsk = 0;
        }
        else {
            mRef.config.SaveAsk = 1;
        }
    }
}

void Option::on_ResizeRate_stateChanged(int arg1)
{
    Q_UNUSED(arg1);
    if(init) {
        if(mRef.config.ResizeRate) {
            mRef.config.ResizeRate = 0;
        }
        else {
            mRef.config.ResizeRate = 1;
        }
    }
}

void Option::on_SaveCompress_valueChanged(int arg1)
{
    mRef.config.SaveCompress = arg1;
}
