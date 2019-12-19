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
    for(int i = 0; i < repoLists.length(); i++)
    {
        createRepoButton(repoLists[i]);
        nextButtonPos[Y] += 60;
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

void JekyllRepo::on_openImageEditor_clicked()
{
    ImageEditor *editor = new ImageEditor(ui->listWidget->currentItem()->text(), this);
    editor->show();
}

void JekyllRepo::createRepoButton(QString dirName)
{
    QPushButton *newButton = new QPushButton(dirName, this);
    newButton->setGeometry(
        nextButtonPos[X], nextButtonPos[Y], nextButtonPos[Width], nextButtonPos[Height]);
    newButton->show();
    QObject::connect(newButton, SIGNAL(clicked()), this, SLOT(repoOpen()));
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
            QStringList extParser = path.toLocalFile().split('.');
            QString ext = extParser[extParser.length() - 1];
            ext = ext.toLower();
            if(ext == "jpg" || ext == "jpeg" || ext == "png" || ext == "gif" || ext == "mp4")
            {
                QDate nowDate = QDate::currentDate();
                QFile::copy(
                    path.toLocalFile(),
                    seletedPath + "/assets/images/" + QString::number(nowDate.year()) + "/" + QString::number(nowDate.day()) + "1");
                path.toLocalFile();
            }
            else QMessageBox::information(this, "Notify", "is not allow ext");
        }
    }
}

JekyllRepo::~JekyllRepo()
{
    delete ui;
}
