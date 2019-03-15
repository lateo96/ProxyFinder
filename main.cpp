#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QIcon>
#include <QDebug>

#include "backend/ThreadedFinder/threadedfinder.h"
#include "backend/ApplicationManager/applicationmanager.h"

void load(ThreadedFinder &finder);
void save(const ThreadedFinder &finder);

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);
    app.setOrganizationName("TheCrowporation");
    app.setApplicationName("Proxy Finder");
    app.setApplicationVersion("0.1-alpha");
    app.setWindowIcon(QIcon(":/images/appIcon.png"));

    qmlRegisterType<ApplicationManager>("ProxyFinder", 0, 1, "ApplicationManager");

    QQmlApplicationEngine engine;
    ThreadedFinder finder;
    load(finder);
    engine.rootContext()->setContextProperty("finder", &finder);
    engine.load(QUrl(QStringLiteral("qrc:/ui/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    int returnCode = app.exec();
    save(finder);

    return returnCode;
}

void load(ThreadedFinder &finder)
{
    Settings s;
    if (!s.contains("network/basic/initialAddress")) {
        return;
    }

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

void save(const ThreadedFinder &finder)
{
    Settings s;

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
