#ifndef JEKYLLREPO_H
#define JEKYLLREPO_H

#define not !

#include <QMainWindow>
#include <QFileDialog>
#include <QMessageBox>
#include <QDirIterator>
#include <QMimeData>
#include <QDate>

#include "Config.h"
#include "ImageEditor.h"

namespace Ui {
class JekyllRepo;
}

class JekyllRepo : public QMainWindow
{
    Q_OBJECT

public:
    explicit JekyllRepo(QWidget *parent = nullptr);
    void createRepoButton(QString dirName);
    QString createTodayDirectory();
    bool isJekyll(QString dirName);
    bool isOverlab(QString dirName);
    ~JekyllRepo();

private slots:
    void repoOpen();
    void on_appendRopoButton_clicked();
    void on_openImageEditor_clicked();
    void on_listWidget_itemSelectionChanged();

protected:
    void dragEnterEvent(QDragEnterEvent* event);
    void dropEvent(QDropEvent* event);

private:
    Ui::JekyllRepo *ui;
    RepoConfig repoConfig;
    int nextButtonPos[4] = { 0, 50, 190, 50 };
    QString seletedPath;
};

#endif // BLOGREPO_H
