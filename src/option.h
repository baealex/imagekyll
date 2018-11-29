#ifndef OPTION_H
#define OPTION_H

#include "mainwindow.h"
#include <QDialog>

namespace Ui {
class Option;
}

class Option : public QDialog
{
    Q_OBJECT

public:
    explicit Option(MainWindow &ref, QWidget *parent = nullptr);
    ~Option();

private slots:
    void on_BlackTheme_clicked();
    void on_WhiteTheme_clicked();
    void on_PurpleTheme_clicked();
    void on_CloseBtn_clicked();
    void on_spinBox_valueChanged(int arg1);

private:
    Ui::Option *ui;
    MainWindow &mRef;
};

#endif // OPTION_H
