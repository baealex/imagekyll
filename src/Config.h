#ifndef CONFIG_H
#define CONFIG_H

#include <QFile>
#include <QTextStream>

class ConfModule {
private:
    QFile *file;
public:
    ConfModule(QString fileName);
    void save(QString content);
    QString load();
    ~ConfModule();
};

class RepoConfig {
    QString fileName;
    ConfModule *module;
public:
    RepoConfig();
    void append(QString newRepoDir);
    QStringList parse();
};

#endif // CONFIG_H
