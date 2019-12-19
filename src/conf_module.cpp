/* ================================================= */

#include "Config.h"

ConfModule::ConfModule(QString fileName)
{
    file = new QFile;
    file->setFileName(fileName);
}

void ConfModule::save(QString content)
{
    file->open(QIODevice::WriteOnly);
    QTextStream out(file);
    out << content;
    file->close();
}

QString ConfModule::load()
{
    file->open(QIODevice::ReadOnly);
    QTextStream in(file);
    QString result = in.readAll();
    file->close();
    return result;
}

ConfModule::~ConfModule()
{
    delete file;
}

/* ================================================= */

RepoConfig::RepoConfig()
{
    fileName = "repository.info";
    module = new ConfModule(fileName);
}

void RepoConfig::append(QString newRepoDir)
{
    if(module->load() != "")
    {
        module->save(module->load() + '|' + newRepoDir);
    }
    else
    {
        module->save(newRepoDir);
    }
}

QStringList RepoConfig::parse()
{
    return module->load().split('|');
}

/* ================================================= */
