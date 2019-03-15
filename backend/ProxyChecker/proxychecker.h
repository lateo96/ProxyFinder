#ifndef PROXYCHECKER_H
#define PROXYCHECKER_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkConfiguration>
#include <QNetworkConfigurationManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QHostAddress>
#include <QNetworkProxy>
#include <QTimer>

class ProxyChecker : public QNetworkAccessManager
{
    Q_OBJECT

public:
    explicit ProxyChecker(const QNetworkProxy &proxy, const QNetworkConfiguration &config = QNetworkConfigurationManager().defaultConfiguration(), QObject *parent = nullptr);

    QString getHostName() const;
    unsigned short getPort() const;

signals:

public slots:
    void start(const QNetworkRequest &request);
    void stop();

private:
};

#endif // PROXYCHECKER_H
