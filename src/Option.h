#ifndef OPTION_H
#define OPTION_H

#include "ImageEditor.h"
#include <QDialog>

namespace Ui {
class Option;
}

class Option : public QDialog
{
    Q_OBJECT
    bool init;
    int UndoSizeTemp;

public:
    explicit Option(ImageEditor &ref, QWidget *parent = nullptr);
    ~Option();

private slots:
    void on_CloseBtn_clicked();
    void on_ThemeBlack_clicked();
    void on_ThemeWhie_clicked();
    void on_ThemePurple_clicked();
    void on_ColorPreviewSize_valueChanged(int arg1);
    void on_SaveAsk_stateChanged(int arg1);
    void on_ResizeRate_stateChanged(int arg1);
    void on_CUndoSize_valueChanged(int arg1);
    void on_SaveCompress_valueChanged(int arg1);

private:
    Ui::Option *ui;
    ImageEditor &mRef;
};

#endif // OPTION_H
