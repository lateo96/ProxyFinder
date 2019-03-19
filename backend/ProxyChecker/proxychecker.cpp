#include "proxychecker.h"
#include <QDebug>
#include <QEventLoop>

ProxyChecker::ProxyChecker(const QNetworkProxy &proxy, int connectionTimeout, QObject *parent) : QNetworkAccessManager(parent)
{
    setProxy(proxy);
    timeout = connectionTimeout;
    if (timeout < 100) {
        qWarning() << "ProxyChecker: The configured network timeout is less than 100 ms";
    }
}

QString ProxyChecker::getHostName() const
{
    return proxy().hostName();
}

unsigned short ProxyChecker::getPort() const
{
    return proxy().port();
}

void ProxyChecker::start(const QNetworkRequest &request)
{
    QNetworkReply *reply = get(request);

    QTimer *t = new QTimer;
    t->setSingleShot(true);

    connect(t, &QTimer::timeout, reply, &QNetworkReply::abort);
    connect(t, &QTimer::timeout, t, &QTimer::deleteLater);
    connect(reply, &QNetworkReply::finished, t, &QTimer::stop);

    t->start(timeout);
}

void ProxyChecker::stop()
{

}
