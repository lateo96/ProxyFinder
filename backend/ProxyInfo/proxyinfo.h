#ifndef PROXYINFO_H
#define PROXYINFO_H

#include <QObject>

class ProxyInfo : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString hostName READ getHostName NOTIFY hostNameChanged)
    Q_PROPERTY(QString port READ getPort NOTIFY portChanged)
    Q_PROPERTY(int httpStatusCode READ getHttpStatusCode NOTIFY httpStatusCodeChanged)
    Q_PROPERTY(QString httpReasonPhrase READ getHttpReasonPhrase NOTIFY httpReasonPhraseChanged)

public:
    explicit ProxyInfo(const QString &proxyHostName, unsigned short proxyPort,
                       int proxyHttpStatusCode, const QString &proxyHttpReasonPhrase,
                       QObject *parent = nullptr);

    QString getHostName() const;
    void setHostName(const QString &value);

    unsigned short getPort() const;
    void setPort(unsigned short value);

    int getHttpStatusCode() const;
    void setHttpStatusCode(int value);

    QString getHttpReasonPhrase() const;
    void setHttpReasonPhrase(const QString &value);

signals:
    void hostNameChanged(const QString &newHostName);
    void portChanged(unsigned short newPort);
    void httpStatusCodeChanged(int newHttpStatusCode);
    void httpReasonPhraseChanged(const QString &newHttpReasonPhrase);

public slots:

private:
    QString hostName;
    unsigned short port = 0;
    int httpStatusCode = 0;
    QString httpReasonPhrase;
};

#endif // PROXYINFO_H
