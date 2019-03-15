#include "applicationmanager.h"
#include <QGuiApplication>
#include <QClipboard>

ApplicationManager::ApplicationManager(QObject *parent) : QObject(parent)
{

}

void ApplicationManager::toClipboard(const QString &str)
{
    QGuiApplication::clipboard()->setText(str);
}

Settings *ApplicationManager::getSettings() const
{
    return settings;
}

void ApplicationManager::setSettings(Settings *value)
{
    settings = value;
}
