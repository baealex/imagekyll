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
#include <QScrollBar>
#include <QTimer>

#include "paintscene.h"

class UserConfig {
private:
    QFile *file;
public:
    // Layout infomation
    int PosX;
    int PosY;
    int Width;
    int Height;
    QString lastWorkDirectory;
    unsigned long UndoSize;

    // Setting Theme Tab infomation
    int Theme;

    // Setting Save Tab infomation
    int SaveAsk;
    int SaveCompress;

    // Setting Color Tab infomation
    int PreviewSize;

    // Setting Resize Tab infomation
    int ResizeRate;

    UserConfig(){
        file = new QFile;
        file->setFileName("UserConfig_2.conf");
        if(!file->open(QIODevice::ReadOnly | QIODevice::Text))
        {
            PosX = 100;
            PosY = 100;
            Width = 730;
            Height = 550;
            lastWorkDirectory = "";
            UndoSize = 5;
            Theme = 1;
            SaveAsk = 1;
            SaveCompress = 100;
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
        out << PosX << "\n" << PosY << "\n" << Width << "\n" << Height << "\n" << lastWorkDirectory << "\n" << UndoSize << "\n" <<
               Theme << "\n" <<
               SaveAsk << "\n" << SaveCompress << "\n" <<
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
         UndoSize = in.readLine().toLong();

         Theme = in.readLine().toInt();
         SaveAsk = in.readLine().toInt();
         SaveCompress = in.readLine().toInt();
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
    void FindPen();
    void Image_Hue_Change(int slider);
    void Image_Intensity_Change(int slider);
    void Image_Saturation_Change(int slider);
    QPixmap scanImage();
    UserConfig config;
    void ImageBackup();

private:
    Ui::MainWindow *ui;
    QPixmap pixmap;
    paintScene *scene;
    int ScrollPos[2];

    QString fileLink;
    QFile *file;

    QGraphicsPixmapItem *item;
    QPointF PreviousPos;
    QPixmap preview;
    int scaleCount = 0;

    QPixmap *ActivityPixmap;
    int ActivityCount;
    int StartPoint;
    int StopPoint;
    int nowPoint;
    bool Cycle;
    bool possibleRedo;
    bool runUndo;

    // SAVE RGB INFOMATION
    int imgRed, imgGreen, imgBlue;
    int penRed, penGreen, penBlue;

    bool Crop = false;
    bool OpenImage = false;
    QPointF previousPoint;
    QPointF lastPoint;

    QTimer *timer;

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
    void PaintWatch();
    void Undo();
    void Redo();
    void on_actionHIS_triggered();
};

#endif // MAINWINDOW_H
