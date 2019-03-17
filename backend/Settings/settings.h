#ifndef SETTINGS_H
#define SETTINGS_H

#include <QSettings>
#include <QString>
#include "../ThreadedFinder/threadedfinder.h"

class Settings : public QSettings
{
    Q_OBJECT

    // Network Basics
    Q_PROPERTY(QString initialAddress READ getInitialAddress WRITE setInitialAddress NOTIFY initialAddressChanged)
    Q_PROPERTY(QString finalAddress READ getFinalAddress WRITE setFinalAddress NOTIFY finalAddressChanged)
    Q_PROPERTY(int port READ getPort WRITE setPort NOTIFY portChanged)
    // Network Advanced
    Q_PROPERTY(int timeout READ getTimeout WRITE setTimeout NOTIFY timeoutChanged)
    Q_PROPERTY(unsigned maxThreads READ getMaxThreads WRITE setMaxThreads NOTIFY maxThreadsChanged)
    Q_PROPERTY(ThreadedFinder::RequestType requestType READ getRequestType WRITE setRequestType NOTIFY requestTypeChanged)
    Q_PROPERTY(QString requestUrl READ getRequestUrl WRITE setRequestUrl NOTIFY requestUrlChanged)
    // Preferences
    Q_PROPERTY(int theme READ getTheme WRITE setTheme NOTIFY themeChanged)

public:
    explicit Settings(QObject *parent = nullptr);
    enum Theme { Light, Dark, System };
    Q_ENUM(Theme)

    QString getInitialAddress();
    void setInitialAddress(const QString &ip);

    QString getFinalAddress();
    void setFinalAddress(const QString &ip);

    unsigned short getPort();
    void setPort(unsigned short p);

    int getTimeout();
    void setTimeout(int t);

    unsigned int getMaxThreads();
    void setMaxThreads(unsigned int n);

    ThreadedFinder::RequestType getRequestType();
    void setRequestType(const ThreadedFinder::RequestType &type);

    QString getRequestUrl();
    void setRequestUrl(const QString &url);

    int getTheme();
    void setTheme(int newTheme);

signals:
    //! Properties
    // Basics
    void initialAddressChanged(const QString &address);
    void finalAddressChanged(const QString &address);
    void portChanged(unsigned short newPort);
    // Advanced
    void timeoutChanged(int newTimeout);
    void maxThreadsChanged(unsigned int newMaxThreads);
    void requestTypeChanged(const ThreadedFinder::RequestType &newRequestType);
    void requestUrlChanged(const QString &newUrl);
    // Preferences
    void themeChanged(int newTheme);

public slots:

private:
    // Basics
    QString initialAddress, finalAddress;
    unsigned short port = 0;

    // Advanced
    int timeout = 2000;
    unsigned int maxThreads = 300;
    ThreadedFinder::RequestType requestType = ThreadedFinder::HTTP;
    QString requestUrl = "google.com";

    // Preferences
    int theme = System;
};

#endif // SETTINGS_H
