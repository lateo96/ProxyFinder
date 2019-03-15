#include "proxyinfo.h"

ProxyInfo::ProxyInfo(const QString &proxyHostName, unsigned short proxyPort,
                     int proxyHttpStatusCode, const QString &proxyHttpReasonPhrase,
                     QObject *parent) : QObject(parent)
{
    hostName = proxyHostName;
    port = proxyPort;
    httpStatusCode = proxyHttpStatusCode;
    httpReasonPhrase = proxyHttpReasonPhrase;
}

QString ProxyInfo::getHostName() const
{
    return hostName;
}

void ProxyInfo::setHostName(const QString &value)
{
    if (hostName != value) {
        hostName = value;
        hostNameChanged(value);
    }
}

unsigned short ProxyInfo::getPort() const
{
    return port;
}

void ProxyInfo::setPort(unsigned short value)
{
    if (port != value) {
        port = value;
        portChanged(value);
    }
}

int ProxyInfo::getHttpStatusCode() const
{
    return httpStatusCode;
}

void ProxyInfo::setHttpStatusCode(int value)
{
    if (httpStatusCode != value) {
        httpStatusCode = value;
        httpStatusCodeChanged(value);
    }
}

QString ProxyInfo::getHttpReasonPhrase() const
{
    return httpReasonPhrase;
}

void ProxyInfo::setHttpReasonPhrase(const QString &value)
{
    if (httpReasonPhrase != value) {
        httpReasonPhrase = value;
        httpReasonPhraseChanged(value);
    }
}
