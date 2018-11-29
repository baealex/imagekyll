#ifndef INFOMATION_H
#define INFOMATION_H

#include <QDialog>

namespace Ui {
class Infomation;
}

class Infomation : public QDialog
{
    Q_OBJECT

public:
    explicit Infomation(QWidget *parent = nullptr);
    ~Infomation();

private slots:
    void on_RightBtn_clicked();

private:
    Ui::Infomation *ui;
};

#endif // INFOMATION_H
