#include "proxychecker.h"
#include <QDebug>
#include <QEventLoop>

ProxyChecker::ProxyChecker(const QNetworkProxy &proxy, const QNetworkConfiguration &config, QObject *parent) : QNetworkAccessManager(parent)
{
    setProxy(proxy);
    setConfiguration(config);
    if (config.connectTimeout() < 100) {
        qWarning() << "ProxyChecker:" <<
                      "The configured network timeout is less than 100 ms";
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

    QTimer t;
    t.setSingleShot(true);
    t.setInterval(configuration().connectTimeout());

    QEventLoop loop;
    connect(&t, &QTimer::timeout, &loop, &QEventLoop::quit);
    connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);

    t.start();
    loop.exec();

    if (t.isActive()) {
        t.stop();
    } else {
        disconnect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
        reply->abort();
    }
}

void ProxyChecker::stop()
{

}
