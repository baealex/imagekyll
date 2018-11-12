#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "rgb_changer.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    new QShortcut(QKeySequence(Qt::SHIFT + Qt::CTRL + Qt::Key_S), this, SLOT(on_actionSave_as_triggered()));
    scene = new paintScene(this);

    allCheckFalse();

    ui->penSize->setValue(5);
    setColorStyle(0,0,0);
    penRed = 0;
    penGreen = 0;
    penBlue = 0;

    imgRed = 1;
    imgGreen = 1;
    imgBlue = 1;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_dotBtn_clicked()
{
    allCheckFalse();
    ui->dotBtn->setChecked(true);
    scene->setDrawDot(true);
}

void MainWindow::on_lineBtn_clicked()
{
    allCheckFalse();
    ui->lineBtn->setChecked(true);
    scene->setDrawLine(true);
}

void MainWindow::on_squreBtn_clicked()
{
    allCheckFalse();
    ui->squreBtn->setChecked(true);
    scene->setDrawSqure(true);
}

void MainWindow::on_roundBtn_clicked()
{
    allCheckFalse();
    ui->roundBtn->setChecked(true);
    scene->setDrawRound(true);
}

void MainWindow::allCheckFalse()
{
    ui->dotBtn->setChecked(false);
    ui->lineBtn->setChecked(false);
    ui->squreBtn->setChecked(false);
    ui->roundBtn->setChecked(false);

    scene->setDrawDot(false);
    scene->setDrawLine(false);
    scene->setDrawSqure(false);
    scene->setDrawRound(false);
}

void MainWindow::on_actionSave_as_triggered()
{
    // Backup Size
    int widthTemp, heightTemp;
    widthTemp = ui->graphicsView->geometry().width();
    heightTemp = ui->graphicsView->geometry().height();

    // Initialize Size and Scale
    ui->graphicsView->setGeometry(ui->graphicsView->geometry().x(),ui->graphicsView->geometry().y(),scene->width(),scene->height());
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->resetMatrix();
    ui->graphicsView->setStyleSheet("border:0px;");
    ui->graphicsView->scroll(0,0);

    // Save Image
    QPixmap savePixmap = ui->graphicsView->grab();
    savePixmap.save(QFileDialog::getSaveFileName(this,"SAVE FILE","",tr("JPEG (*.jpg) ;; PNG(*.png)")));

    // Throwed Layout
    ui->graphicsView->setGeometry(ui->graphicsView->geometry().x(),ui->graphicsView->geometry().y(),widthTemp,heightTemp);
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    if(scaleCount > 0)
    {
        for(int i=0;i<scaleCount;i++)
            ui->graphicsView->scale(1.25,1.25);
    }
    else if(scaleCount == 0)
    {
        ui->graphicsView->resetMatrix();
    }
    else
    {
        scaleCount *= -1;
        for(int i=0;i<scaleCount;i++)
            ui->graphicsView->scale(0.8,0.8);
        scaleCount *= -1;
    }
}

void MainWindow::on_actionOpen_triggered()
{
    // 변경된 내용이 있습니다. 정말 저장하지 않으시겠습니까? 추가해야됨!!

    scene->clear();
    fileLink = QFileDialog::getOpenFileName(this);

    ui->graphicsView->setScene(scene);

    pixmap.load(fileLink);
    item = new QGraphicsPixmapItem(pixmap);
    scene->addItem(item);
}

void MainWindow::resizeEvent(QResizeEvent *event) {
    ui->graphicsView->setGeometry(ui->graphicsView->geometry().x(),ui->graphicsView->geometry().y(),this->geometry().width()-ui->graphicsView->geometry().x(),this->geometry().height()-ui->graphicsView->geometry().y()-20);

    ui->zoominBtn->setGeometry(this->geometry().width()-60,0,ui->zoominBtn->geometry().width(),ui->zoominBtn->geometry().height());
    ui->zoomoutBtn->setGeometry(this->geometry().width()-30,0,ui->zoominBtn->geometry().width(),ui->zoominBtn->geometry().height());

    ui->separator->setGeometry(0,0,this->geometry().width(),1);
}

void MainWindow::on_zoomoutBtn_clicked(){
    ui->graphicsView->scale(0.8,0.8);
    scaleCount--;
}

void MainWindow::on_zoominBtn_clicked(){
    ui->graphicsView->scale(1.25,1.25);
    scaleCount++;
}

void MainWindow::on_actionRGB_triggered()
{
    rgb_changer rgb(*this, 0, imgRed, imgGreen, imgBlue, this);
    rgb.exec();
}

void MainWindow::Image_RGB_Change(int slider_r, int slider_g, int slider_b)
{
    imgRed = slider_r; imgGreen = slider_g; imgBlue = slider_b;
    QImage image = pixmap.toImage();
    int r,g,b;
    QRgb rgb;

    for(int y = 0; y < image.height(); y++)
    {
        for(int x = 0 ; x < image.width(); x++)
        {
            rgb = image.pixel(x,y);
            r = qRed(rgb) + slider_r;
            g = qGreen(rgb) + slider_g;
            b = qBlue(rgb) + slider_b;
            if(r < 0) r = 0;
            else if(r > 255) r = 255;
            if(g < 0) g = 0;
            else if(g > 255) g = 255;
            if(b < 0) b = 0;
            else if(b > 255) b = 255;
            image.setPixel(x,y,qRgb(r,g,b));
        }
    }
    preview = QPixmap::fromImage(image);
    item->setPixmap(preview);
    scene->addItem(item);
}

void MainWindow::Image_RGB_Preview_Change(int slider_r, int slider_g, int slider_b)
{
    QPixmap pixmap2 = pixmap.scaled(pixmap.size().width()/3,pixmap.size().height()/3);
    QImage image = pixmap2.toImage();
    int r,g,b;
    QRgb rgb;
    for(int y = 0; y < image.height(); y++)
    {
        for(int x = 0 ; x < image.width(); x++)
        {
            rgb = image.pixel(x,y);
            r = qRed(rgb) + slider_r;
            g = qGreen(rgb) + slider_g;
            b = qBlue(rgb) + slider_b;
            if(r < 0) r = 0;
            else if(r > 255) r = 255;
            if(g < 0) g = 0;
            else if(g > 255) g = 255;
            if(b < 0) b = 0;
            else if(b > 255) b = 255;
            image.setPixel(x,y,qRgb(r,g,b));
        }
    }
    preview = QPixmap::fromImage(image.scaled(image.size().width()*3,image.size().height()*3));
    item->setPixmap(preview);
    scene->addItem(item);
}

void MainWindow::setColorStyle(int slider_r, int slider_g, int slider_b)
{
    penRed = slider_r; penGreen = slider_g; penBlue = slider_b;
    ui->penColor->setStyleSheet("background:rgb("+QString::number(slider_r)+","+QString::number(slider_g)+","+QString::number(slider_b)+")");
    scene->setColor(slider_r,slider_g,slider_b);
}

void MainWindow::on_penSize_valueChanged(int arg1)
{
    scene->setPenSize(arg1);
}

void MainWindow::on_penColor_clicked()
{
    rgb_changer rgb(*this, 1, penRed, penGreen, penBlue, this);
    rgb.exec();
}
