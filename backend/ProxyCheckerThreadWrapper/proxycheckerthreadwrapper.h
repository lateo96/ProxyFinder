#ifndef PROXYCHECKERTHREADWRAPPER_H
#define PROXYCHECKERTHREADWRAPPER_H

#include "../ProxyChecker/proxychecker.h"
#include <QThread>

class ProxyCheckerThreadWrapper : public QObject
{
    Q_OBJECT
public:
    explicit ProxyCheckerThreadWrapper(const QNetworkProxy &proxy, int connectionTimeout = 2000, QObject *parent = nullptr);
    ~ProxyCheckerThreadWrapper();

    QString getHostName() const;
    unsigned short getPort() const;

protected:

signals:
    void ready(const QNetworkRequest &request);
    void replied(QNetworkReply *reply);

public slots:
    void start(const QNetworkRequest &request);
    void stop();

private:
    QThread paralellThread;
    ProxyChecker proxyChecker;
    QNetworkRequest networkRequest = QNetworkRequest(QUrl("http://google.com"));
};

#endif // PROXYCHECKERTHREADWRAPPER_H
