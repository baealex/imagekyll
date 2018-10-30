#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPixmap>
#include <QPainter>
#include <QFileDialog>
#include <QShortcut>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QResizeEvent>

#include "paintscene.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void allCheckFalse();
    QPixmap pixmap;
    paintScene *scene;

private:
    Ui::MainWindow *ui;
    QString fileLink;
    QGraphicsPixmapItem *item;
    QPointF PreviousPos;

protected:
    void resizeEvent(QResizeEvent *event);

private slots:
    void on_lineBtn_clicked();
    void on_squreBtn_clicked();
    void on_roundBtn_clicked();
    void on_actionSave_as_triggered();
    void on_actionOpen_triggered();
    void on_zoomoutBtn_clicked();
    void on_zoominBtn_clicked();
    void on_dotBtn_clicked();
    void on_actionRGB_triggered();
};

#endif // MAINWINDOW_H
