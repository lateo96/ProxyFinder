#include "proxycheckerthreadwrapper.h"

ProxyCheckerThreadWrapper::ProxyCheckerThreadWrapper(const QNetworkProxy &proxy, const QNetworkConfiguration &config, QObject *parent) :
    QObject(parent), proxyChecker(proxy, config, parent)
{
    proxyChecker.moveToThread(&paralellThread);
    connect(this, &ProxyCheckerThreadWrapper::ready, &proxyChecker, &ProxyChecker::start);
    connect(&proxyChecker, &ProxyChecker::finished, this, &ProxyCheckerThreadWrapper::replied);
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
