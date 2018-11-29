#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "rgb_changer.h"
#include "image_resizer.h"
#include "option.h"
#include "infomation.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ThemeSelect(1);

    this->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(this, SIGNAL(customContextMenuRequested(const QPoint&)),this, SLOT(ShowContextMenu(const QPoint&)));

    new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_O), this, SLOT(on_actionOpen_triggered()));
    new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_S), this, SLOT(on_actionSave_triggered()));
    new QShortcut(QKeySequence(Qt::CTRL + Qt::SHIFT + Qt::Key_S), this, SLOT(on_actionSave_as_triggered()));

    new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_C), this, SLOT(on_actionRGB_triggered()));
    new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_R), this, SLOT(on_actionResizing_triggered()));

    new QShortcut(QKeySequence(Qt::CTRL + Qt::ALT + Qt::Key_O), this, SLOT(on_actionOption_triggered()));
    new QShortcut(QKeySequence(Qt::Key_F10), this, SLOT(on_actionInfo_triggered()));

    scene = new paintScene(this);

    ui->graphicsView->setScene(scene);
    ui->penSize->setValue(5);
    setColorStyle(0,0,0);

    allCheckFalse();

    file = new QFile("LastWorkStation.txt");
}

void MainWindow::ShowContextMenu(const QPoint& pos) // this is a slot
{
    QPoint globalPos = this->mapToGlobal(pos);

    QMenu myMenu;
    myMenu.setStyleSheet("QMenu {color: #fff;background-color: #333;border: 1px solid black;} QMenu::item {background-color: transparent;} QMenu::item:selected {background-color: #555;}");
    myMenu.addAction("Open (Ctrl + O)", this, SLOT(on_actionOpen_triggered()));
    myMenu.addAction("Save (Ctrl + S)", this, SLOT(on_actionSave_triggered()));
    myMenu.addAction("Save as (Ctrl + Shift + S)", this, SLOT(on_actionRGB_triggered()));
    myMenu.addSeparator();
    myMenu.addAction("RGB (Ctrl + C)", this, SLOT(on_actionRGB_triggered()));
    myMenu.addAction("Resize (Ctrl + R)", this, SLOT(on_actionResizing_triggered()));
    myMenu.addSeparator();
    myMenu.addAction("Option (Ctrl + Alt + O)", this, SLOT(on_actionOption_triggered()));
    myMenu.addAction("Infomation (F10)", this, SLOT(on_actionInfo_triggered()));

    QAction* selectedItem = myMenu.exec(globalPos);
    Q_UNUSED(selectedItem);
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

void MainWindow::SetPreviewSize(int arg1)
{
    PreviewSize = arg1;
}

void MainWindow::ThemeSelect(int arg1)
{
    switch (arg1) {
    case 1:
        this->setStyleSheet("QMainWindow { background:#444; } QMessageBox { background:#444; } QMessageBox QLabel { color: #fff; } QDialog { background: #333; } QDialog QLabel{ color:#fff; } QDialog QCheckBox{ color:#fff; } QSlider::handle:horizontal { background: #fff; border: 1px solid #5c5c5c; width: 18px; margin: -2px 0; border-radius: 3px; } QMenuBar { background:#444; color:#fff; } QMenuBar::item:selected { background: #555; } QMenuBar::item:pressed { background: #777; } QMenu { color: #fff; background-color: #333; border: 1px solid black; } QMenu::item { background-color: transparent; } QMenu::item:selected { background-color: #555; } QGraphicsView { background:#222; } QSpinBox { background:#222; color:#fff; } QSpinBox::down-button { subcontrol-origin: border; } QPushButton { background:rgba(0,0,0,.0); color:#aaa; font-weight:bold; text-align:center; } QPushButton:hover { color:#ccc; } QPushButton:pressed { color:#fff; } QPushButton:checked { color:#fff; } QScrollBar:horizontal { border: 0px solid grey; background: #333; height: 15px; margin: 0px 22px 0 22px; } QScrollBar::handle:horizontal { background: #666; min-width: 20px; } QScrollBar::add-line:horizontal { border: 0px solid grey; background: #555; width: 20px; subcontrol-position: right; subcontrol-origin: margin; } QScrollBar::sub-line:horizontal { border: 0px solid grey; background: #555; width: 20px; subcontrol-position: left; subcontrol-origin: margin; } QScrollBar::add-page:horizontal, QScrollBar::sub-page:horizontal { background: none; } QScrollBar:vertical { border: 0px solid grey; background: #333; width: 15px; margin: 22px 0 22px 0; } QScrollBar::handle:vertical { background: #666; min-height: 20px; } QScrollBar::add-line:vertical { border: 0px solid grey; background: #555; height: 20px; subcontrol-position: bottom; subcontrol-origin: margin; } QScrollBar::sub-line:vertical { border: 0px solid grey; background: #555; height: 20px; subcontrol-position: top; subcontrol-origin: margin; } QScrollBar::add-page:vertical, QScrollBar::sub-page:vertical { background: none; }");
        break;
    case 2:
        this->setStyleSheet("QMainWindow { background:#fff; } QMessageBox { background:#fff; } QMessageBox QLabel { color: #000; } QDialog { background: #fff; } QDialog QLabel{ color:#000; } QDialog QCheckBox{ color:#000; } QSlider::handle:horizontal { background: #000; border: 1px solid #c5c5c5; width: 18px; margin: -2px 0; border-radius: 3px; } QMenuBar { background:#fff; color:#000; } QMenuBar::item:selected { background: #eee; } QMenuBar::item:pressed { background: #ccc; } QMenu { color: #000; background-color: #eee; border: 1px solid white; } QMenu::item { background-color: transparent; } QMenu::item:selected { background-color: #aaa; } QGraphicsView { background:#fff; } QSpinBox { background:#222; color:#fff; } QSpinBox::down-button { subcontrol-origin: border; } QPushButton { background:rgba(0,0,0,.0); color:#aaa; font-weight:bold; text-align:center; } QPushButton:hover { color:#666; } QPushButton:pressed { color:#000; } QPushButton:checked { color:#000; } QScrollBar:horizontal { border: 0px solid darkgrey; background: #ccc; height: 15px; margin: 0px 22px 0 22px; } QScrollBar::handle:horizontal { background: #fff; min-width: 20px; } QScrollBar::add-line:horizontal { border: 0px solid darkgrey; background: #aaa; width: 20px; subcontrol-position: right; subcontrol-origin: margin; } QScrollBar::sub-line:horizontal { border: 0px solid darkgrey; background: #aaa; width: 20px; subcontrol-position: left; subcontrol-origin: margin; } QScrollBar::add-page:horizontal, QScrollBar::sub-page:horizontal { background: none; } QScrollBar:vertical { border: 0px solid darkgrey; background: #ccc; width: 15px; margin: 22px 0 22px 0; } QScrollBar::handle:vertical { background: #fff; min-height: 20px; } QScrollBar::add-line:vertical { border: 0px solid darkgrey; background: #aaa; height: 20px; subcontrol-position: bottom; subcontrol-origin: margin; } QScrollBar::sub-line:vertical { border: 0px solid darkgrey; background: #aaa; height: 20px; subcontrol-position: top; subcontrol-origin: margin; } QScrollBar::add-page:vertical, QScrollBar::sub-page:vertical { background: none; }");
        break;
    case 3:
        this->setStyleSheet("QMainWindow { background:#400071; } QMessageBox { background:#400071; } QMessageBox QLabel { color: #fff; } QDialog { background: #400071; } QDialog QLabel{ color:#fff; } QDialog QCheckBox{ color:#fff; } QSlider::handle:horizontal { background: #fff; border: 1px solid #5c5c5c; width: 18px; margin: -2px 0; border-radius: 3px; } QMenuBar { background:#400071; color:#fff; } QMenuBar::item:selected { background: #555; } QMenuBar::item:pressed { background: #777; } QMenu { color: #fff; background-color: #333; border: 1px solid black; } QMenu::item { background-color: transparent; } QMenu::item:selected { background-color: #555; } QGraphicsView { background:#300060; } QSpinBox { background:#222; color:#fff; } QSpinBox::down-button { subcontrol-origin: border; } QPushButton { background:rgba(0,0,0,.0); color:#aaa; font-weight:bold; text-align:center; } QPushButton:hover { color:#ccc; } QPushButton:pressed { color:#fff; } QPushButton:checked { color:#fff; } QScrollBar:horizontal { border: 0px solid grey; background: #510082; height: 15px; margin: 0px 22px 0 22px; } QScrollBar::handle:horizontal { background: #7300a4; min-width: 20px; } QScrollBar::add-line:horizontal { border: 0px solid grey; background: #510082; width: 20px; subcontrol-position: right; subcontrol-origin: margin; } QScrollBar::sub-line:horizontal { border: 0px solid grey; background: #510082; width: 20px; subcontrol-position: left; subcontrol-origin: margin; } QScrollBar::add-page:horizontal, QScrollBar::sub-page:horizontal { background: none; } QScrollBar:vertical { border: 0px solid grey; background: #510082; width: 15px; margin: 22px 0 22px 0; } QScrollBar::handle:vertical { background: #7300a4; min-height: 20px; } QScrollBar::add-line:vertical { border: 0px solid grey; background: #510082; height: 20px; subcontrol-position: bottom; subcontrol-origin: margin; } QScrollBar::sub-line:vertical { border: 0px solid grey; background: #510082; height: 20px; subcontrol-position: top; subcontrol-origin: margin; } QScrollBar::add-page:vertical, QScrollBar::sub-page:vertical { background: none; }");
        break;
    }
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

void MainWindow::on_actionSave_triggered()
{
    if(OpenImage) {
        int Answer = QMessageBox::question(this,
                                           "Really?",
                                           "Existing images will be erased and overwritten!",
                                           QMessageBox::Yes | QMessageBox::No);
        switch (Answer) {
        case QMessageBox::Yes :
            break;
        case QMessageBox::No :
            return;
        }
        QPixmap savePixmap = scanImage();
        savePixmap.save(fileLink);
    } else {
        QMessageBox::information(this, "Please", "The image must be opened first.");
    }
}

void MainWindow::on_actionSave_as_triggered()
{
    if(OpenImage) {
        QPixmap savePixmap = scanImage();
        savePixmap.save(QFileDialog::getSaveFileName(this,"SAVE FILE","",tr("PNG(*.png) ;; JPEG (*.jpg)")));
    } else {
        QMessageBox::information(this,"Please","The image must be opened first.");
    }
}

void MainWindow::on_actionOpen_triggered()
{
    if(OpenImage && scene->runEdit)
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

    if(fileLink!="") {
        OpenImage = true;

        file->open(QIODevice::WriteOnly);
        QTextStream out(file);
        out.setCodec("UTF-8");
        out << fileLink;
        file->close();

        pixmap.load(fileLink);

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
}

void MainWindow::on_actionOption_triggered()
{
    Option op(*this, this);
    op.exec();
}

void MainWindow::on_actionInfo_triggered()
{
    Infomation info(this);
    info.exec();
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
    if(OpenImage) {
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
    } else {
        QMessageBox::information(this,"Please","The image must be opened first.");
    }
}

void MainWindow::on_dotBtn_clicked()
{
    if(OpenImage) {
        allCheckFalse();
        ui->dotBtn->setChecked(true);
        scene->setDrawDot(true);
    } else {
        QMessageBox::information(this,"Please","The image must be opened first.");
    }

}

void MainWindow::on_lineBtn_clicked()
{
    if(OpenImage) {
        allCheckFalse();
        ui->lineBtn->setChecked(true);
        scene->setDrawLine(true);
    } else {
        QMessageBox::information(this,"Please","The image must be opened first.");
    }

}

void MainWindow::on_squreBtn_clicked()
{
    if(OpenImage) {
        allCheckFalse();
        ui->squreBtn->setChecked(true);
        scene->setDrawSqure(true);
    } else {
        QMessageBox::information(this,"Please","The image must be opened first.");
    }

}

void MainWindow::on_roundBtn_clicked()
{
    if(OpenImage) {
        allCheckFalse();
        ui->roundBtn->setChecked(true);
        scene->setDrawRound(true);
    } else {
        QMessageBox::information(this,"Please","The image must be opened first.");
    }

}

/*
 *
 * RGB CHANGE
 *
 */

void MainWindow::on_actionRGB_triggered()
{
    if(OpenImage) {
        rgb_changer rgb(*this, 0, imgRed, imgGreen, imgBlue, this);
        rgb.exec();
    } else {
        QMessageBox::information(this,"Please","The image must be opened first.");
    }
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
    int pre = 1;
    if(PreviewSize < pixmap.size().height()) pre = pixmap.size().height()/PreviewSize;
    QImage image = pixmap.scaled(pixmap.size().width()/pre,pixmap.size().height()/pre).toImage();
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
    preview = QPixmap::fromImage(image.scaled(image.size().width()*pre,image.size().height()*pre));
    item->setPixmap(preview);
}

void MainWindow::Image_Hue_Change()
{
    QImage image = pixmap.toImage();
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

void MainWindow::on_actionResizing_triggered()
{
    if(OpenImage) {
        image_resizer resizer(*this, pixmap.width(), pixmap.height(), this);
        resizer.exec();
    } else {
        QMessageBox::information(this,"Please","The image must be opened first.");
    }
}

void MainWindow::Image_Size_Change(int w, int h)
{
    pixmap = scanImage();
    pixmap = pixmap.scaled(w,h);

    scene = new paintScene(this);
    ui->graphicsView->setScene(scene);

    scene->setPenSize(ui->penSize->value());
    scene->setColor(penRed, penGreen, penBlue);

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

        scene->setPenSize(ui->penSize->value());
        scene->setColor(penRed, penGreen, penBlue);

        item = new QGraphicsPixmapItem(pixmap);
        scene->addItem(item);

        ui->cropBtn->setChecked(false);
        Crop = false;
    }
}

void MainWindow::resizeEvent(QResizeEvent *event) {
    Q_UNUSED(event);
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
