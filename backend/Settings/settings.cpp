#include "settings.h"

// Begin implementations
Settings::Settings(QObject *parent) : QSettings(parent) {

}

//! Properties
QString Settings::getInitialAddress()
{
    initialAddress = value("network/basic/initialAddress").toString();
    return initialAddress;
}

void Settings::setInitialAddress(const QString &value)
{
    if (initialAddress != value) {
        initialAddress = value;
        setValue("network/basic/initialAddress", initialAddress);
        emit initialAddressChanged(value);
    }
}

QString Settings::getFinalAddress()
{
    finalAddress = value("network/basic/finalAddress").toString();
    return finalAddress;
}

void Settings::setFinalAddress(const QString &value)
{
    if (finalAddress != value) {
        finalAddress = value;
        setValue("network/basic/finalAddress", finalAddress);
        emit finalAddressChanged(value);
    }
}

unsigned short Settings::getPort()
{
    port = value("network/basic/port").value<unsigned short>();
    return port;
}

void Settings::setPort(unsigned short value)
{
    if (port != value) {
        port = value;
        setValue("network/basic/port", port);
        emit portChanged(value);
    }
}

// Advanced
int Settings::getTimeout()
{
    timeout = value("network/advanced/timeout").toInt();
    return timeout;
}

void Settings::setTimeout(int value)
{
    if (timeout != value) {
        timeout = value;
        setValue("network/advanced/timeout", timeout);
        emit timeoutChanged(value);
    }
}

int Settings::getMaxThreads()
{
    maxThreads = value("network/advanced/maxThreads").toInt();
    return maxThreads;
}

void Settings::setMaxThreads(int value)
{
    if (maxThreads != value) {
        maxThreads = value;
        setValue("network/advanced/maxThreads", maxThreads);
        emit maxThreadsChanged(value);
    }
}

ThreadedFinder::RequestType Settings::getRequestType()
{
    requestType = ThreadedFinder::RequestType(value("network/advanced/requestType").toInt());
    return requestType;
}

void Settings::setRequestType(const ThreadedFinder::RequestType &value)
{
    if (requestType != value) {
        requestType = value;
        setValue("network/advanced/requestType", int(requestType));
        emit requestTypeChanged(value);
    }
}

QString Settings::getRequestUrl()
{
    requestUrl = value("network/advanced/requestUrl").toString();
    return requestUrl;
}

void Settings::setRequestUrl(const QString &value)
{
    if (requestUrl != value) {
        requestUrl = value;
        setValue("network/advanced/requestType", requestUrl);
        emit requestUrlChanged(value);
    }
}
