#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QIcon>

#include "backend/ThreadedFinder/threadedfinder.h"
#include "backend/ApplicationManager/applicationmanager.h"

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
    engine.rootContext()->setContextProperty("finder", &finder);
    engine.load(QUrl(QStringLiteral("qrc:/ui/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
