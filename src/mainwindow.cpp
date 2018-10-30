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
    ui->graphicsView->setGeometry(ui->graphicsView->geometry().x(),ui->graphicsView->geometry().y(),pixmap.width(),pixmap.height());
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    QPixmap savePixmap = ui->graphicsView->grab();
    savePixmap.save(QFileDialog::getSaveFileName(this,"SAVE FILE","",tr("JPEG (*.jpg) ;; PNG(*.png)")));
}

void MainWindow::on_actionOpen_triggered()
{
    fileLink = QFileDialog::getOpenFileName(this);

    ui->graphicsView->setScene(scene);

    pixmap.load(fileLink);
    item = new QGraphicsPixmapItem(pixmap);
    scene->addItem(item);
}

void MainWindow::resizeEvent(QResizeEvent *event) {
    ui->graphicsView->setGeometry(ui->graphicsView->geometry().x(),ui->graphicsView->geometry().y(),this->geometry().width()-40,this->geometry().height()-60);
}

void MainWindow::on_zoomoutBtn_clicked(){
    ui->graphicsView->scale(0.8,0.8);
}

void MainWindow::on_zoominBtn_clicked(){
    ui->graphicsView->scale(1.2,1.2);
}

void MainWindow::on_actionRGB_triggered()
{
    rgb_changer rgb(*this, this);
    rgb.exec();
}
