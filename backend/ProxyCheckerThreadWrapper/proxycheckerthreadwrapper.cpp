#include "proxycheckerthreadwrapper.h"

ProxyCheckerThreadWrapper::ProxyCheckerThreadWrapper(const QNetworkProxy &proxy, int connectionTimeout, QObject *parent) :
    QObject(parent), proxyChecker(proxy, connectionTimeout, parent)
{
    proxyChecker.moveToThread(&paralellThread);
    connect(this, &ProxyCheckerThreadWrapper::ready, &proxyChecker, &ProxyChecker::start);
    connect(&proxyChecker, &ProxyChecker::finished, this, &ProxyCheckerThreadWrapper::replied);
    connect(&proxyChecker, &ProxyChecker::finished, &paralellThread, &QThread::quit);
}

ProxyCheckerThreadWrapper::~ProxyCheckerThreadWrapper()
{
    paralellThread.quit();
    paralellThread.wait();
}

QString ProxyCheckerThreadWrapper::getHostName() const
{
    return proxyChecker.getHostName();
}

unsigned short ProxyCheckerThreadWrapper::getPort() const
{
    return proxyChecker.getPort();
}

void ProxyCheckerThreadWrapper::start(const QNetworkRequest &request)
{
    paralellThread.start();
    emit ready(request);
}

void ProxyCheckerThreadWrapper::stop()
{
    paralellThread.terminate();
}

QThread* ProxyCheckerThreadWrapper::thread()
{
    return &paralellThread;
}
