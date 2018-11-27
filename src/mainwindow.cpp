#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "rgb_changer.h"
#include "option.h"
#include "image_resizer.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    new QShortcut(QKeySequence(Qt::SHIFT + Qt::CTRL + Qt::Key_S), this, SLOT(on_actionSave_as_triggered()));

    scene = new paintScene(this);
    ui->graphicsView->setScene(scene);

    ui->penSize->setValue(5);
    setColorStyle(0,0,0);

    allCheckFalse();

    file = new QFile("LastWorkStation.txt");
}

MainWindow::~MainWindow()
{
    delete ui;
}

/*
 *
 * MY FUNCTION
 *
 */

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

QPixmap MainWindow::scanImage()
{
    int widthTemp, heightTemp;
    widthTemp = ui->graphicsView->geometry().width();
    heightTemp = ui->graphicsView->geometry().height();

    ui->graphicsView->setGeometry(ui->graphicsView->geometry().x(),ui->graphicsView->geometry().y(),scene->width(),scene->height());
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->resetMatrix();
    ui->graphicsView->setStyleSheet("border:0px;");
    ui->graphicsView->scroll(0,0);

    QPixmap temp = ui->graphicsView->grab();

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

    return temp;
}

/*
 *
 * MENU OPTION
 *
 */

void MainWindow::on_actionSave_as_triggered()
{
    QPixmap savePixmap = scanImage();
    savePixmap.save(QFileDialog::getSaveFileName(this,"SAVE FILE","",tr("PNG(*.png) ;; JPEG (*.jpg)")));
}

void MainWindow::on_actionOpen_triggered()
{
    if(scene->runEdit)
    {
        int Answer = QMessageBox::question(this,
                                           "Really?",
                                           "Are you sure you want to erase this image and open a new file?",
                                           QMessageBox::Yes | QMessageBox::No);
        switch (Answer) {
        case QMessageBox::Yes :
            break;
        case QMessageBox::No :
            return;
        }
    }

    if(file->open(QIODevice::ReadOnly | QIODevice::Text))
    {
        file->open(QIODevice::ReadOnly);
        QTextStream in(file);
        in.setCodec("UTF-8");
        lastWorkDirectory = in.readAll();
        file->close();
        fileLink = QFileDialog::getOpenFileName(this,"",lastWorkDirectory);
    }
    else
    {
        fileLink = QFileDialog::getOpenFileName(this);
    }

    file->open(QIODevice::WriteOnly);
    QTextStream out(file);
    out.setCodec("UTF-8");
    out << fileLink;
    file->close();

    pixmap.load(fileLink);
    if(pixmap.height() > pixmap.width()) {
        PreviewSize = pixmap.height() / 1080;
    } else { PreviewSize = pixmap.width() / 1080; }

    scene = new paintScene(this);
    ui->graphicsView->setScene(scene);

    scene->setPenSize(ui->penSize->value());
    scene->setColor(penRed, penGreen, penBlue);
    allCheckFalse();

    imgRed = 1;
    imgGreen = 1;
    imgBlue = 1;

    item = new QGraphicsPixmapItem(pixmap);
    scene->addItem(item);

    scene->runEdit = false;
}

void MainWindow::on_actionResizing_triggered()
{
    image_resizer resizer(*this, pixmap.width(), pixmap.height(), this);
    resizer.exec();
}

void MainWindow::on_actionSetting_triggered()
{
}

/*
 *
 * BUTTON
 *
 */

void MainWindow::on_zoomoutBtn_clicked(){
    ui->graphicsView->scale(0.8,0.8);
    scaleCount--;
}

void MainWindow::on_zoominBtn_clicked(){
    ui->graphicsView->scale(1.25,1.25);
    scaleCount++;
}

void MainWindow::on_cropBtn_clicked()
{
    allCheckFalse();
    if(!Crop) {
        Crop = true;
        ui->maskLabel->setStyleSheet("background:rgba(255,255,255,0.5)");
        ui->maskLabel->setGeometry(ui->graphicsView->geometry().x(),ui->graphicsView->geometry().y(),this->geometry().width()-ui->graphicsView->geometry().x(),this->geometry().height()-ui->graphicsView->geometry().y()-20);
    }
    else {
        Crop = false;
        ui->maskLabel->setStyleSheet("background:rgba(255,255,255,0)");
        ui->cropLabel->setStyleSheet("border: 0px solid red;");
        ui->maskLabel->setGeometry(0,0,0,0);
        ui->cropLabel->setGeometry(0,0,0,0);
    }
    ui->cropBtn->setChecked(Crop);
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

/*
 *
 * RGB CHANGE
 *
 */

void MainWindow::on_actionRGB_triggered()
{
    rgb_changer rgb(*this, 0, imgRed, imgGreen, imgBlue, this);
    rgb.exec();
}

void MainWindow::Image_RGB_Change(int slider_r, int slider_g, int slider_b)
{
    scene->runEdit = true;
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
}

void MainWindow::Image_RGB_Preview_Change(int slider_r, int slider_g, int slider_b)
{
    QPixmap pixmap2 = pixmap.scaled(pixmap.size().width()/PreviewSize,pixmap.size().height()/PreviewSize);
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
    preview = QPixmap::fromImage(image.scaled(image.size().width()*PreviewSize,image.size().height()*PreviewSize));
    item->setPixmap(preview);
}

void MainWindow::Image_Hue_Change()
{
    QPixmap pixmap2 = pixmap.scaled(pixmap.size().width(),pixmap.size().height());
    QImage image = pixmap2.toImage();
    for(int i=0; i<image.width(); i++)
    {
        for(int j=0; j<image.height(); j++)
        {
            QColor color = image.pixelColor(i,j);

            int hue = color.hue();
            color.setHsv(hue, color.saturation(), color.value(), color.alpha());
            image.setPixelColor(i, j, color);
        }
    }
    preview = QPixmap::fromImage(image.scaled(image.size().width(),image.size().height()));
    item->setPixmap(preview);
}

/*
 *
 * PEN CUSTOM
 *
 */


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

/*
 *
 * IMAGE SIZE
 *
 */

void MainWindow::Image_Size_Change(int w, int h)
{
    pixmap = pixmap.scaled(w,h);

    scene = new paintScene(this);
    ui->graphicsView->setScene(scene);

    item = new QGraphicsPixmapItem(pixmap);
    scene->addItem(item);
}

/*
 *
 * EVENT
 *
 */

void MainWindow::mousePressEvent(QMouseEvent *event) {
    if(Crop) {
        previousPoint = event->localPos();
        ui->cropLabel->setStyleSheet("border: 3px solid red;");
    }
}

void MainWindow::mouseMoveEvent(QMouseEvent *event) {
    if(Crop) {
        ui->cropLabel->setGeometry(previousPoint.x(),previousPoint.y(),event->localPos().x()-previousPoint.x(),event->localPos().y()-previousPoint.y());
    }
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event) {
    if(Crop) {
        ui->maskLabel->setStyleSheet("background:rgba(255,255,255,0)");
        ui->cropLabel->setStyleSheet("border: 0px solid red;");
        ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

        pixmap = ui->graphicsView->grab(QRect(previousPoint.x(),previousPoint.y(),event->localPos().x()-previousPoint.x(),event->localPos().y()-previousPoint.y()));

        ui->graphicsView->resetMatrix();
        scaleCount = 0;
        ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        ui->maskLabel->setGeometry(0,0,0,0);
        ui->cropLabel->setGeometry(0,0,0,0);

        scene = new paintScene(this);
        ui->graphicsView->setScene(scene);

        item = new QGraphicsPixmapItem(pixmap);
        scene->addItem(item);

        Crop = false;
    }
}

void MainWindow::resizeEvent(QResizeEvent *event) {
    ui->graphicsView->setGeometry(ui->graphicsView->geometry().x(),ui->graphicsView->geometry().y(),this->geometry().width()-ui->graphicsView->geometry().x(),this->geometry().height()-ui->graphicsView->geometry().y()-20);

    if(Crop)
    {
        ui->maskLabel->setGeometry(ui->graphicsView->geometry().x(),ui->graphicsView->geometry().y(),this->geometry().width()-ui->graphicsView->geometry().x(),this->geometry().height()-ui->graphicsView->geometry().y()-20);
    }

    ui->zoominBtn->move(this->geometry().width()-60,0);
    ui->zoomoutBtn->move(this->geometry().width()-30,0);
    ui->cropBtn->move(0,this->geometry().height()-50);

    ui->separator->setGeometry(0,0,this->geometry().width(),1);
}
