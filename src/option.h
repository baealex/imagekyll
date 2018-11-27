#ifndef OPTION_H
#define OPTION_H

#include <QDialog>

namespace Ui {
class Option;
}

class Option : public QDialog
{
    Q_OBJECT

public:
    explicit Option(QWidget *parent = nullptr);
    ~Option();

private:
    Ui::Option *ui;
};

#endif // OPTION_H
