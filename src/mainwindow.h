#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#define UNDO_SIZE 10

#include <QMainWindow>
#include <QPixmap>
#include <QPainter>
#include <QFileDialog>
#include <QShortcut>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QResizeEvent>
#include <QMessageBox>

#include "paintscene.h"

class UserConfig {
private:
    QFile *file;
public:
    // Basic Config
    int PosX;
    int PosY;
    int Width;
    int Height;
    QString lastWorkDirectory;

    // Theme Tab Config
    int Theme;

    // Save Tab Config
    int SaveAsk;

    // Color Tab Config
    int PreviewSize;

    // Resize Tab Config
    int ResizeRate;

    UserConfig(){
        file = new QFile;
        file->setFileName("UserConfig.dat");
        if(!file->open(QIODevice::ReadOnly | QIODevice::Text))
        {
            PosX = 100;
            PosY = 100;
            Width = 730;
            Height = 550;
            lastWorkDirectory = "";
            Theme = 1;
            SaveAsk = 1;
            PreviewSize = 1080;
            ResizeRate = 1;
        }
        else
        {
            LOAD();
        }
    }
    void SAVE(){
        file->open(QIODevice::WriteOnly);
        QTextStream out(file);
        out << PosX << "\n" << PosY << "\n" << Width << "\n" << Height << "\n" << lastWorkDirectory << "\n" <<
               Theme << "\n" <<
               SaveAsk << "\n" <<
               PreviewSize << "\n" <<
               ResizeRate;
        file->close();
    }
    void LOAD(){
         file->open(QIODevice::ReadOnly);
         QTextStream in(file);
         PosX = in.readLine().toInt();
         PosY = in.readLine().toInt();
         Width = in.readLine().toInt();
         Height = in.readLine().toInt();
         lastWorkDirectory = in.readLine();

         Theme = in.readLine().toInt();
         SaveAsk = in.readLine().toInt();
         PreviewSize = in.readLine().toInt();
         ResizeRate = in.readLine().toInt();
         file->close();
    }
    ~UserConfig(){
        delete file;
    }
};

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
    void Image_Size_Change(int h, int w);
    void Image_RGB_Change(int slider_r, int slider_g, int slider_b);
    void Image_RGB_Preview_Change(int slider_r, int slider_g, int slider_b);
    void setColorStyle(int slider_r, int slider_g, int slider_b);
    void Image_Hue_Change();
    void ThemeSelect(int arg1);
    QPixmap scanImage();
    UserConfig config;

private:
    Ui::MainWindow *ui;
    QPixmap pixmap;
    paintScene *scene;

    QString fileLink;
    QFile *file;

    QGraphicsPixmapItem *item;
    QPointF PreviousPos;
    QPixmap preview;
    int scaleCount = 0;

    // SAVE RGB INFOMATION
    int imgRed, imgGreen, imgBlue;
    int penRed, penGreen, penBlue;

    bool Crop = false;
    bool OpenImage = false;
    QPointF previousPoint;

protected:
    void resizeEvent(QResizeEvent *event);
    void mousePressEvent(QMouseEvent * event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

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
    void on_cropBtn_clicked();
    void on_actionResizing_triggered();
    void ShowContextMenu(const QPoint& pos);
    void on_actionSave_triggered();
    void on_actionOption_triggered();
    void on_actionInfo_triggered();
};

#endif // MAINWINDOW_H
