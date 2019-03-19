#include "settings.h"

// Begin implementations
Settings::Settings(const QString &organization, const QString &application, QObject *parent)
    : QSettings (organization, application, parent)
{
    initialize();
}

Settings::Settings(const QString &fileName, QSettings::Format format, QObject *parent)
    : QSettings (fileName, format, parent)
{
    initialize();
}

Settings::Settings(QObject *parent) : QSettings(parent)
{
    connect(&net, &QNetworkAccessManager::networkAccessibleChanged, this, &Settings::networkAvailableChanged);
    initialize();
}

Settings::~Settings()
{
}

//! Properties
bool Settings::getFirstTime()
{
    firstTime = value(".").toBool() == false;
    return firstTime;
}

void Settings::setFirstTime(bool isFirstTime)
{
    if (firstTime != isFirstTime) {
        firstTime = isFirstTime;
        setValue(".", !isFirstTime);
        emit firstTimeChanged(isFirstTime);
    }
}

bool Settings::getNetworkAvailable()
{
    networkAvailable = net.networkAccessible();
    return networkAvailable;
}

void Settings::setNetworkAvailable(bool isAvailable)
{
    if (networkAvailable != isAvailable) {
        networkAvailable = isAvailable;
        emit networkAvailableChanged(isAvailable);
    }
}

// Basics
QString Settings::getInitialAddress()
{
    if (contains("network/basic/initialAddress")) {
        initialAddress = value("network/basic/initialAddress").toString();
    }
    return initialAddress;
}

void Settings::setInitialAddress(const QString &ip)
{
    if (initialAddress != ip) {
        initialAddress = ip;
        setValue("network/basic/initialAddress", ip);
        emit initialAddressChanged(ip);
    }
}

QString Settings::getFinalAddress()
{
    if (contains("network/basic/finalAddress")) {
        finalAddress = value("network/basic/finalAddress").toString();
    }
    return finalAddress;
}

void Settings::setFinalAddress(const QString &ip)
{
    if (finalAddress != ip) {
        finalAddress = ip;
        setValue("network/basic/finalAddress", ip);
        emit finalAddressChanged(ip);
    }
}

unsigned short Settings::getPort()
{
    if (contains("network/basic/port")) {
        port = value("network/basic/port").value<unsigned short>();
    }
    return port;
}

void Settings::setPort(unsigned short p)
{
    if (port != p) {
        port = p;
        setValue("network/basic/port", p);
        emit portChanged(p);
    }
}

// Advanced
int Settings::getTimeout()
{
    if (contains("network/advanced/timeout")) {
        timeout = value("network/advanced/timeout").toInt();
    }
    return timeout;
}

void Settings::setTimeout(int t)
{
    if (timeout != t) {
        timeout = t;
        setValue("network/advanced/timeout", t);
        emit timeoutChanged(t);
    }
}

unsigned int Settings::getMaxThreads()
{
    if (contains("network/advanced/maxThreads")) {
        maxThreads = value("network/advanced/maxThreads").toUInt();
    }
    return maxThreads;
}

void Settings::setMaxThreads(unsigned int n)
{
    if (maxThreads != n) {
        maxThreads = n;
        setValue("network/advanced/maxThreads", n);
        emit maxThreadsChanged(n);
    }
}

ThreadedFinder::RequestType Settings::getRequestType()
{
    if (contains("network/advanced/requestType")) {
        requestType = ThreadedFinder::RequestType(value("network/advanced/requestType").toInt());
    }
    return requestType;
}

void Settings::setRequestType(const ThreadedFinder::RequestType &type)
{
    if (requestType != type) {
        requestType = type;
        setValue("network/advanced/requestType", int(type));
        emit requestTypeChanged(type);
    }
}

QString Settings::getRequestUrl()
{
    if (contains("network/advanced/requestUrl")) {
        requestUrl = value("network/advanced/requestUrl").toString();
    }
    return requestUrl;
}

void Settings::setRequestUrl(const QString &url)
{
    if (requestUrl != url) {
        requestUrl = url;
        setValue("network/advanced/requestUrl", url);
        emit requestUrlChanged(url);
    }
}

// Preferences
int Settings::getTheme()
{
    if (contains("preferences/style/theme")) {
        theme = value("preferences/style/theme").toInt();
    }
    return theme;
}

void Settings::setTheme(int newTheme)
{
    if (theme != newTheme) {
        theme = newTheme;
        setValue("preferences/style/theme", newTheme);
        emit themeChanged(newTheme);
    }
}

QString Settings::getOperatingSystem() const
{
    return operatingSystem;
}

void Settings::setOperatingSystem(const QString &systemName)
{
    if (operatingSystem != systemName) {
        operatingSystem = systemName;
        emit operatingSystemChanged(systemName);
    }
}

// Functions
void Settings::initialize()
{
#ifdef Q_OS_WIN
    setOperatingSystem("Windows");
#endif
#ifdef Q_OS_LINUX
    setOperatingSystem("Linux");
#endif
#ifdef Q_OS_MACOS
    setOperatingSystem("MacOS");
#endif

    getFirstTime();
    if (firstTime) {
        // Basics
        setValue("network/basic/initialAddress", initialAddress);
        setValue("network/basic/finalAddress", finalAddress);
        setValue("network/basic/port", port);
        // Advanced
        setValue("network/advanced/timeout", timeout);
        setValue("network/advanced/maxThreads", maxThreads);
        setValue("network/advanced/requestType", int(requestType));
        setValue("network/advanced/requestUrl", requestUrl);
        // Preferences
        setValue("preferences/style/theme", theme);
    } else {
        // Basic
        getInitialAddress();
        getFinalAddress();
        getPort();

        // Advanced
        getTimeout();
        getMaxThreads();
        getRequestType();
        getRequestUrl();

        // Preferences
        getTheme();
    }
}
