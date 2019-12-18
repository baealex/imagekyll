#ifndef BLOGREPO_H
#define BLOGREPO_H

#include <QMainWindow>

namespace Ui {
class BlogRepo;
}

class BlogRepo : public QMainWindow
{
    Q_OBJECT

public:
    explicit BlogRepo(QWidget *parent = nullptr);
    ~BlogRepo();

private slots:
    void on_appendRopoButton_clicked();

private:
    Ui::BlogRepo *ui;
};

#endif // BLOGREPO_H
