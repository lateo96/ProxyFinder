#ifndef SETTINGS_H
#define SETTINGS_H

#include <QSettings>
#include <QString>
#include "../ThreadedFinder/threadedfinder.h"

class Settings : public QSettings
{
    Q_OBJECT

    Q_PROPERTY(QString initialAddress READ getInitialAddress WRITE setInitialAddress NOTIFY initialAddressChanged)
    Q_PROPERTY(QString finalAddress READ getFinalAddress WRITE setFinalAddress NOTIFY finalAddressChanged)
    Q_PROPERTY(int port READ getPort WRITE setPort NOTIFY portChanged)
    // Advanced
    Q_PROPERTY(int timeout READ getTimeout WRITE setTimeout NOTIFY timeoutChanged)
    Q_PROPERTY(int maxThreads READ getMaxThreads WRITE setMaxThreads NOTIFY maxThreadsChanged)
    Q_PROPERTY(ThreadedFinder::RequestType requestType READ getRequestType WRITE setRequestType NOTIFY requestTypeChanged)
    Q_PROPERTY(QString requestUrl READ getRequestUrl WRITE setRequestUrl NOTIFY requestUrlChanged)

public:
    explicit Settings(QObject *parent = nullptr);

    QString getInitialAddress();
    void setInitialAddress(const QString &value);

    QString getFinalAddress();
    void setFinalAddress(const QString &value);

    unsigned short getPort();
    void setPort(unsigned short value);

    int getTimeout();
    void setTimeout(int value);

    int getMaxThreads();
    void setMaxThreads(int value);

    ThreadedFinder::RequestType getRequestType();
    void setRequestType(const ThreadedFinder::RequestType &value);

    QString getRequestUrl();
    void setRequestUrl(const QString &value);

signals:
    //! Properties
    void initialAddressChanged(const QString &address);
    void finalAddressChanged(const QString &address);
    void portChanged(unsigned short newPort);
    // Advanced
    void timeoutChanged(int newTimeout);
    void maxThreadsChanged(int newMaxThreads);
    void requestTypeChanged(const ThreadedFinder::RequestType &newRequestType);
    void requestUrlChanged(const QString &newUrl);

public slots:

private:
    QString initialAddress, finalAddress;
    unsigned short port = 0;

    // Advanced
    int timeout = 2000;
    int maxThreads = 100;
    ThreadedFinder::RequestType requestType;
    QString requestUrl = "google.com";
};

#endif // SETTINGS_H
