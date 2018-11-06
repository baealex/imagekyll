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
    void Image_RGB_Change(int slider_r, int slider_g, int slider_b);
    void Image_RGB_Preview_Change(int slider_r, int slider_g, int slider_b);
    void setColorStyle(int slider_r, int slider_g, int slider_b);
    QPixmap pixmap;
    paintScene *scene;

private:
    Ui::MainWindow *ui;
    QString fileLink;
    QGraphicsPixmapItem *item;
    QPointF PreviousPos;
    QPixmap preview;
    int scaleCount = 0;

    int imgRed, imgGreen, imgBlue;
    int penRed, penGreen, penBlue;

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
    void on_penColor_clicked();
    void on_penSize_valueChanged(int arg1);
};

#endif // MAINWINDOW_H
