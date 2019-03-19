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
    Q_PROPERTY(int status READ getStatus NOTIFY statusChanged)
    Q_PROPERTY(bool running READ getRunning NOTIFY runningChanged)
    Q_PROPERTY(bool gettingAddresses READ getGettingAddresses NOTIFY gettingAddressesChanged)
    Q_PROPERTY(bool settingCheckers READ getSettingCheckers NOTIFY settingCheckersChanged)
    Q_PROPERTY(bool scaning READ getScaning NOTIFY scaningChanged)
    Q_PROPERTY(bool validInitialAddress READ getValidInitialAddress NOTIFY validInitialAddressChanged)
    Q_PROPERTY(bool validFinalAddress READ getValidFinalAddress NOTIFY validFinalAddressChanged)
    Q_PROPERTY(unsigned progressTotal READ getProgressTotal NOTIFY progressTotalChanged)
    Q_PROPERTY(unsigned progressPartial READ getProgressPartial NOTIFY progressPartialChanged)
    Q_PROPERTY(double progress READ getProgress NOTIFY progressChanged)

public:

    enum RequestType { HTTP, HTTPS, FTP };
    Q_ENUM(RequestType)
    enum Status { ReadyFirsTime, GettingAddresses, SettingCheckers, Scaning, FinishedAndReady, AbortedAndReady };
    Q_ENUM(Status)

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

    unsigned getProgressTotal() const;
    void setProgressTotal(unsigned value);

    unsigned getProgressPartial() const;
    void setProgressPartial(unsigned value);

    int getStatus() const;
    void setStatus(const Status &value);

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
    void statusChanged(int updatedStatus);
    void runningChanged(bool isRunning);
    void gettingAddressesChanged(bool isGettingAddresses);
    void settingCheckersChanged(bool isSettingCheckers);
    void scaningChanged(bool isScaning);
    void validInitialAddressChanged(bool isValid);
    void validFinalAddressChanged(bool isValid);
    void progressTotalChanged(unsigned total);
    void progressPartialChanged(unsigned partial);
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
    void onReplied(QNetworkReply *reply, ProxyCheckerThreadWrapper *obj);

private:
    void addInfoToReportUsingFilters(ProxyInfo *info);

private:
    unsigned int maxThreads = 300;
    int timeout = 1000;
    RequestType requestType = HTTP;
    QString requestUrl = "google.com";
    QHostAddress initialAddress, finalAddress;
    QString initialAddressString, finalAddressString;
    unsigned short port = 0;

    Status status = ReadyFirsTime;
    bool running = false;
    bool gettingAddresses = false;
    bool settingCheckers = false;
    bool scaning = false;

    unsigned int launchIndex;
    bool validInitialAddress = false;
    bool validFinalAddress = false;
    unsigned int progressTotal = 1;
    unsigned int progressPartial = 0;
    double progress = 0.0;
    int totalAddressesToScan = 1;
    QNetworkProxy::ProxyType requestTypeToProxyType[3] = { QNetworkProxy::HttpCachingProxy, QNetworkProxy::HttpCachingProxy, QNetworkProxy::FtpCachingProxy };
    QStringList requestTypeToProtocolString = QStringList() << "http" << "https" << "ftp";

    unsigned int runningCheckers = 0;
    unsigned int addressesToScan = 0;
    QList<ProxyCheckerThreadWrapper*> connectedCheckers;
    QList<QObject*> checkersToDelete;
    QList<QObject*> report;
    QList<QObject*> fullReport;
    QVariantList filteredCodes = QVariantList() << QNetworkReply::NoError
                                                << QNetworkReply::ProxyAuthenticationRequiredError;
};

#endif // THREADEDFINDER_H
