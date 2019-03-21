#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QIcon>
#include <QDir>
#include <QFont>
#include <QDebug>

#include "backend/ThreadedFinder/threadedfinder.h"
#include "backend/ApplicationManager/applicationmanager.h"

void load(Settings &s, ThreadedFinder &finder);
void save(Settings &s, const ThreadedFinder &finder);

//! TODO: Caught exceptions to allow saving even if the app crashes

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);
    app.setOrganizationName("TheCrowporation");
    app.setApplicationName("Proxy Finder");
    app.setApplicationVersion("0.2-alpha");
    app.setWindowIcon(QIcon(":/images/appIcon.png"));

#ifdef Q_OS_WIN
    QFont applicationFont("Sans Serif", -1, QFont::Normal);
    applicationFont.setStyleHint(QFont::SansSerif);
    app.setFont(applicationFont);
#endif

    qmlRegisterType<ApplicationManager>("ProxyFinder", 0, 2, "ApplicationManager");

    QQmlApplicationEngine engine;
    ThreadedFinder finder;
    QString settingsPath = app.applicationDirPath();
    QSettings::setPath(QSettings::IniFormat, QSettings::UserScope, settingsPath);
    QSettings::setDefaultFormat(QSettings::IniFormat);
    Settings s;
    load(s, finder);
    engine.rootContext()->setContextProperty("finder", &finder);
    engine.load(QUrl(QStringLiteral("qrc:/ui/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    int returnCode = app.exec();
    save(s, finder);

    return returnCode;
}

void load(Settings &s, ThreadedFinder &finder)
{
    // Basic
    finder.setInitialAddressString(s.getInitialAddress());
    finder.setFinalAddressString(s.getFinalAddress());
    finder.setPort(s.getPort());

    // Advanced
    finder.setTimeout(s.getTimeout());
    finder.setNumberOfThreads(s.getMaxThreads());
    finder.setRequestType(s.getRequestType());
    finder.setRequestUrl(s.getRequestUrl());
}

void save(Settings &s, const ThreadedFinder &finder)
{
    if (!s.getRetryFirstTime()) {
        s.setFirstTime(false);
    }

    // Basic
    s.setInitialAddress(finder.getInitialAddressString());
    s.setFinalAddress(finder.getFinalAddressString());
    s.setPort(finder.getPort());

    // Advanced
    s.setTimeout(finder.getTimeout());
    s.setMaxThreads(finder.getNumberOfThreads());
    s.setRequestType(finder.getRequestType());
    s.setRequestUrl(finder.getRequestUrl());
}
