#ifndef APPLICATIONMANAGER_H
#define APPLICATIONMANAGER_H

#include "../Settings/settings.h"
#include <QObject>

class ApplicationManager : public QObject
{
    Q_OBJECT

    Q_PROPERTY(Settings* settings READ getSettings WRITE setSettings NOTIFY settingsChanged)

public:
    explicit ApplicationManager(QObject *parent = nullptr);


    Settings* getSettings() const;
    void setSettings(Settings *value);

signals:
    void settingsChanged(const Settings &newSettings);

public slots:
    void toClipboard(const QString &str);

private:
    Settings *settings = new Settings;
};

#endif // APPLICATIONMANAGER_H
