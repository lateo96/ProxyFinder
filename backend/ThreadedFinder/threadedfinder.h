#ifndef THREADEDFINDER_H
#define THREADEDFINDER_H

#include "../ProxyCheckerThreadWrapper/proxycheckerthreadwrapper.h"
#include "../ProxyInfo/proxyinfo.h"
#include <QThread>
#include <QQueue>

class ThreadedFinder : public QThread
{
    Q_OBJECT

    Q_PROPERTY(QString initialAddress READ getInitialAddressString WRITE setInitialAddressString NOTIFY initialAddressStringChanged)
    Q_PROPERTY(QString finalAddress READ getFinalAddressString WRITE setFinalAddressString NOTIFY finalAddressStringChanged)
    Q_PROPERTY(int port READ getPort WRITE setPort NOTIFY portChanged)
    Q_PROPERTY(int maxThreads READ getNumberOfThreads WRITE setNumberOfThreads NOTIFY maxThreadsChanged)
    Q_PROPERTY(int timeout READ getTimeout WRITE setTimeout NOTIFY timeoutChanged)
    Q_PROPERTY(RequestType requestType READ getRequestType WRITE setRequestType NOTIFY requestTypeChanged)
    Q_PROPERTY(QString requestUrl READ getRequestUrl WRITE setRequestUrl NOTIFY requestUrlChanged)
    Q_PROPERTY(QList<QObject *> reportModel READ getReport NOTIFY reportChanged)
    Q_PROPERTY(QVariantList filteredCodes READ getFilteredCodes NOTIFY filteredCodesChanged)
    Q_PROPERTY(bool running READ getRunning NOTIFY runningChanged)
    Q_PROPERTY(bool gettingAddresses READ getGettingAddresses NOTIFY gettingAddressesChanged)
    Q_PROPERTY(bool settingCheckers READ getSettingCheckers NOTIFY settingCheckersChanged)
    Q_PROPERTY(bool scaning READ getScaning NOTIFY scaningChanged)
    Q_PROPERTY(bool validInitialAddress READ getValidInitialAddress NOTIFY validInitialAddressChanged)
    Q_PROPERTY(bool validFinalAddress READ getValidFinalAddress NOTIFY validFinalAddressChanged)
    Q_PROPERTY(double progressTotal READ getProgressTotal NOTIFY progressTotalChanged)
    Q_PROPERTY(double progressPartial READ getProgressPartial NOTIFY progressPartialChanged)
    Q_PROPERTY(double progress READ getProgress NOTIFY progressChanged)

public:

    enum RequestType { HTTP, HTTPS, FTP };
    Q_ENUM(RequestType)

    ThreadedFinder(QObject *parent = nullptr);
    ~ThreadedFinder() override;

    void run() override;

    unsigned int getNumberOfThreads() const;
    void setNumberOfThreads(unsigned int value);

    QHostAddress getInitialAddress() const;
    void setInitialAddress(const QHostAddress &value);

    QHostAddress getFinalAddress() const;
    void setFinalAddress(const QHostAddress &value);

    unsigned short getPort() const;
    void setPort(unsigned short value);

    QList<QObject *> getReport() const;

    QString getInitialAddressString() const;
    void setInitialAddressString(const QString &value);

    QString getFinalAddressString() const;
    void setFinalAddressString(const QString &value);

    bool getScaning() const;
    void setScaning(bool value);

    QVariantList getFilteredCodes() const;
    void setFilteredCodes(const QVariantList &value);

    bool getValidInitialAddress() const;
    void setValidInitialAddress(bool value);

    bool getValidFinalAddress() const;
    void setValidFinalAddress(bool value);

    int getTimeout() const;
    void setTimeout(int value);

    RequestType getRequestType() const;
    void setRequestType(const RequestType &value);

    QString getRequestUrl() const;
    void setRequestUrl(const QString &value);

    double getProgress() const;
    void setProgress(double value);

    bool getSettingCheckers() const;
    void setSettingCheckers(bool value);

    bool getRunning() const;
    void setRunning(bool value);

    bool getGettingAddresses() const;
    void setGettingAddresses(bool value);

    int getProgressTotal() const;
    void setProgressTotal(int value);

    int getProgressPartial() const;
    void setProgressPartial(int value);

signals:
    void replied(QNetworkReply *reply);
    void singleCheckFinished();
    void scanFinished();

    // properties
    void portChanged(unsigned short newPort);
    void maxThreadsChanged(unsigned int newMaxThreads);
    void timeoutChanged(int t);
    void requestTypeChanged(RequestType newType);
    void requestUrlChanged(const QString &newUrl);
    void reportChanged(QList<QObject*> updatedReport);
    void filteredCodesChanged(const QVariantList &updatedFilters);
    void initialAddressStringChanged(const QString &newAddressString);
    void finalAddressStringChanged(const QString &newAddressString);
    void runningChanged(bool isRunning);
    void gettingAddressesChanged(bool isGettingAddresses);
    void settingCheckersChanged(bool isSettingCheckers);
    void scaningChanged(bool isScaning);
    void validInitialAddressChanged(bool isValid);
    void validFinalAddressChanged(bool isValid);
    void progressTotalChanged(int total);
    void progressPartialChanged(int partial);
    void progressChanged(double updatedProgress);

public slots:
    void updateReport();
    void clean();
    void updateProgress();
    bool addressesAreInverted();

private slots:
    void fillQueue();
    void setupNetworkCheckers();
    void launchNetworkCheckers();
    void onReplied(QNetworkReply *reply);

private:
    void addInfoToReportUsingFilters(ProxyInfo *info);

private:
    unsigned int maxThreads = 100;
    int timeout = 2000;
    RequestType requestType = HTTP;
    QString requestUrl = "google.com";
    QHostAddress initialAddress, finalAddress;
    QString initialAddressString, finalAddressString;
    unsigned short port = 0;

    bool running = false;
    bool gettingAddresses = false;
    bool settingCheckers = false;
    bool scaning = false;

    unsigned int launchIndex;
    bool validInitialAddress = false;
    bool validFinalAddress = false;
    int progressTotal = 1;
    int progressPartial = 0;
    double progress = 0.0;
    int totalAddressesToScan = 1;
    QNetworkProxy::ProxyType requestTypeToProxyType[3] = { QNetworkProxy::HttpCachingProxy, QNetworkProxy::HttpCachingProxy, QNetworkProxy::FtpCachingProxy };
    QStringList requestTypeToProtocolString = QStringList() << "http" << "https" << "ftp";

    unsigned int finishedJobs = 0;
    QQueue<QHostAddress> queue;
    QList<ProxyCheckerThreadWrapper*> connectedCheckers;
    QList<ProxyCheckerThreadWrapper*> runningCheckers;
    QList<QObject*> report;
    QList<QObject*> fullReport;
    QVariantList filteredCodes = QVariantList() << 99 << QNetworkReply::NoError
                                                << QNetworkReply::ProxyAuthenticationRequiredError;
};

#endif // THREADEDFINDER_H
