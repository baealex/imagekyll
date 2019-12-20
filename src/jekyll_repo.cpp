#include "JekyllRepo.h"
#include "ui_jekyll_repo.h"

enum QtLayout {
    X, Y, Width, Height
};

JekyllRepo::JekyllRepo(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::JekyllRepo)
{
    ui->setupUi(this);

    ConfModule module(":/new/prefix1/style.css");
    this->setStyleSheet(module.load());

    ui->appendRopoButton->setText(tr("Append Blog Repo"));

    QStringList repoLists = repoConfig.parse();
    if(repoLists.length() > 0)
    {
        for(int i = 0; i < repoLists.length(); i++)
        {
            createRepoButton(repoLists[i]);
            nextButtonPos[Y] += 60;
        }
    }
}

void JekyllRepo::on_appendRopoButton_clicked()
{
    QString dirName = QFileDialog::getExistingDirectory(this, tr("Select blog repository"));
    if(dirName == "") return;

    if(isJekyll(dirName))
    {
        if( not isOverlab(dirName))
        {
            createRepoButton(dirName);
            repoConfig.append(dirName);
        }
        else QMessageBox::information(this, tr("Notify"), tr("Aleady append repo."));
    }
    else QMessageBox::information(this, tr("Notify"), tr("Cannot find '_config.yml'."));
}

void JekyllRepo::update()
{
    QListWidgetItem *selectedItem = ui->listWidget->currentItem();
    ui->listWidget->setItemSelected(selectedItem, false);
    ui->listWidget->setItemSelected(selectedItem, true);
}

void JekyllRepo::on_openImageEditor_clicked()
{
    ImageEditor *editor = new ImageEditor(ui->listWidget->currentItem()->text(), this);
    editor->show();
    update();
}

void JekyllRepo::on_openImageCompressor_clicked()
{
    QString nowFile = ui->listWidget->currentItem()->text();
    QString ext = Parser::extParse(nowFile).toLower();

    if(ext == "jpg")
    {

    }
    else if(ext == "png")
    {
        QMessageBox::information(this, tr("Notify"), tr("Compression is possible but may damage the image."));
    }
    else
    {
        QMessageBox::information(this, tr("Notify"), tr("is not allow ext"));
    }
    ImageCompressor compressor(ui->listWidget->currentItem()->text(), this);
    compressor.exec();
    update();
}

void JekyllRepo::createRepoButton(QString dirName)
{
    QPushButton *newButton = new QPushButton(dirName, this);
    newButton->setGeometry(
        nextButtonPos[X], nextButtonPos[Y], nextButtonPos[Width], nextButtonPos[Height]);
    newButton->show();
    QObject::connect(newButton, SIGNAL(clicked()), this, SLOT(repoOpen()));
}

QString JekyllRepo::createTodayDirectory()
{
    QDir dir(seletedPath);
    if(dir.isEmpty()) {
        dir.mkpath("assets");
    }
    dir.setPath(dir.path() + "/assets");
    if(dir.isEmpty()) {
        dir.mkpath("images");
    }

    QDate now     = QDate::currentDate();
    QString year  = QString::number(now.year());
    QString month = QString::number(now.month());
    QString day   = QString::number(now.day());

    dir.setPath(dir.path() + "/images");
    if(dir.isEmpty()) {
        dir.mkpath("posts");
    }
    dir.setPath(dir.path() + "/posts");
    if(dir.isEmpty()) {
        dir.mkpath(year);
    }
    dir.setPath(dir.path() + "/" + year);
    if(dir.isEmpty()) {
        dir.mkpath(month);
    }
    dir.setPath(dir.path() + "/" + month);
    if(dir.isEmpty()) {
        dir.mkpath(day);
    }
    dir.setPath(dir.path() + "/" + day);
    return dir.path();
}

void JekyllRepo::repoOpen()
{
    setAcceptDrops(true);
    QPushButton* clickedButton = qobject_cast<QPushButton*>(sender());

    QStringList strFilters;
    strFilters += "*.jpg";
    strFilters += "*.JPG";
    strFilters += "*.jpeg";
    strFilters += "*.JPEG";
    strFilters += "*.png";
    strFilters += "*.PNG";
    strFilters += "*.gif";
    strFilters += "*.GIF";
    strFilters += "*.mp4";
    strFilters += "*.MP4";

    seletedPath = clickedButton->text();
    QDirIterator iterDir(seletedPath, strFilters, QDir::Files | QDir::NoSymLinks, QDirIterator::Subdirectories);
    while (iterDir.hasNext())
    {
        iterDir.next();
        ui->listWidget->addItem(iterDir.filePath());
    }
}

void JekyllRepo::on_listWidget_itemSelectionChanged()
{
    QString fileFullPath = ui->listWidget->currentItem()->text();
    QString jekyllPath = "{{ site.image }}" + fileFullPath.split("images")[1];
    ui->fileLink->setText(jekyllPath);

    ui->imagePreview->setPixmap(QPixmap(fileFullPath).scaled(
        ui->imagePreview->width(), ui->imagePreview->height(), Qt::KeepAspectRatio));

    ui->imageSize->setText(QString::number((double)QFile(fileFullPath).size()/1048576, 'f', 2) + "MB");
}

bool JekyllRepo::isOverlab(QString dirName)
{
    return repoConfig.parse().contains(dirName);
}

bool JekyllRepo::isJekyll(QString dirName)
{
    return QFileInfo::exists(dirName + "/_config.yml");
}

void JekyllRepo::dragEnterEvent(QDragEnterEvent* event) {
    event->acceptProposedAction();
}

void JekyllRepo::dropEvent(QDropEvent* event)
{
    const QMimeData* mimeData = event->mimeData();
    if (mimeData->hasUrls())
    {
        QList<QUrl> paths = mimeData->urls();
        foreach(QUrl path, paths)
        {
            QString ext = Parser::extParse(path.toLocalFile()).toLower();
            QString fileName = Parser::nameParse(path.toLocalFile()).replace(' ', '-').replace("." + ext, "");

            if(ext == "jpg" || ext == "jpeg" || ext == "png" || ext == "gif" || ext == "mp4")
            {
                ConfModule module("counter");
                QString copyPath = createTodayDirectory() + "/" + fileName + "." + ext;
                QFile::copy(path.toLocalFile(), copyPath);
                ui->listWidget->addItem(copyPath);
            }
            else QMessageBox::information(this, tr("Notify"), tr("is not allow ext"));
        }
    }
}

JekyllRepo::~JekyllRepo()
{
    delete ui;
}
