#include "threadedfinder.h"
#include <QDebug>
#include <QEventLoop>

//#define DEBUG

ThreadedFinder::ThreadedFinder(QObject *parent)
    : QThread (parent)
{
    connect(this, &ThreadedFinder::singleCheckFinished, [=] {
        // Exit the finder when the list gets empty
        if (connectedCheckers.isEmpty()) {
            setProgress(0);
            emit scanFinished();
            quit();
            return;
        }

        if (runningCheckers.count() == 0) {
            launchNetworkCheckers();
        }
    });
}

ThreadedFinder::~ThreadedFinder()
{
    clean();
}

void ThreadedFinder::clean()
{
    queue.clear();

    for (auto x : runningCheckers) {
        x->stop();
        connectedCheckers.removeOne(x);
    }
    for (auto x : connectedCheckers) {
        x->stop();
    }

    runningCheckers.clear();
    connectedCheckers.clear();

    for (auto x : fullReport) {
        x->deleteLater();
    }
    fullReport.clear();
    report.clear();

    setScaning(false);
    setProgress(0);
    emit reportChanged(report);
}

void ThreadedFinder::updateProgress()
{
    setProgress(1 - double(queue.count())/totalAddressesToScan);
}

void ThreadedFinder::run()
{
    clean();
    setScaning(true);
    fillQueue();
    setupNetworkCheckers();
    launchNetworkCheckers();
    exec();
    setScaning(false);
}

void ThreadedFinder::fillQueue()
{
    const unsigned int initialIP = initialAddress.toIPv4Address();
    const unsigned int finalIP = finalAddress.toIPv4Address();
    for (unsigned int i = initialIP; i <= finalIP; ++i) {
        queue.enqueue(QHostAddress(i));
    }
    totalAddressesToScan = queue.count();
}

void ThreadedFinder::setupNetworkCheckers()
{
    const unsigned int initialIP = initialAddress.toIPv4Address();
    const unsigned int finalIP = finalAddress.toIPv4Address();
    for (unsigned int i = initialIP; i <= finalIP; ++i) {
        QNetworkProxy p;
        p.setHostName(QHostAddress(i).toString());
        p.setPort(port);
        p.setType(requestTypeToProxyType[requestType]);
        QNetworkConfiguration c(QNetworkConfigurationManager().defaultConfiguration());
        c.setConnectTimeout(timeout);
        ProxyCheckerThreadWrapper *proxyChecker = new ProxyCheckerThreadWrapper(p, c);
        connectedCheckers.append(proxyChecker);
        connect(proxyChecker, &ProxyCheckerThreadWrapper::replied, this, &ThreadedFinder::onReplied);

        // Remove the deleted  proxy thread from the containers
        connect(proxyChecker, &ProxyCheckerThreadWrapper::destroyed, [=](QObject *obj) {
            connectedCheckers.removeOne(static_cast<ProxyCheckerThreadWrapper*>(obj));
            runningCheckers.removeOne(static_cast<ProxyCheckerThreadWrapper*>(obj));
            queue.dequeue(); // Not removes the destroyed address
            updateProgress();

            emit singleCheckFinished();
        });
    }
}

void ThreadedFinder::launchNetworkCheckers()
{
    const unsigned int initialIP = initialAddress.toIPv4Address();
    const unsigned int finalIP = finalAddress.toIPv4Address();
    for (launchIndex = initialIP; launchIndex <= finalIP; ++launchIndex) {
        if (queue.isEmpty()) {
            quit();
        }
        if (unsigned(runningCheckers.count()) >= maxThreads) {
            break;
        }
        for (int j = 0; j < connectedCheckers.count(); ++j) {
            if (connectedCheckers[j]->getHostName() == QHostAddress(launchIndex).toString()) {
                ProxyCheckerThreadWrapper *p = connectedCheckers[j];
                runningCheckers.append(p);
                p->start(QNetworkRequest(QUrl(requestTypeToProtocolString[requestType] + "://" + requestUrl)));
                break; // go to the external loop
            }
        }
    }
}

void ThreadedFinder::onReplied(QNetworkReply *reply)
{
    emit replied(reply);

    // Add proxy info to the report
    QNetworkProxy proxy = reply->manager()->proxy();
    //int httpCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
    int httpCode = reply->error();
    //QString httpReason = reply->attribute(QNetworkRequest::HttpReasonPhraseAttribute).toString();
    QString httpReason = reply->errorString();
    ProxyInfo *info = new ProxyInfo(proxy.hostName(), proxy.port(), httpCode, httpReason);

#ifdef DEBUG
    qDebug() << proxy.hostName() + ':' + QString::number(proxy.port()) << httpCode << httpReason;
#endif
    fullReport.append(info);
    addInfoToReportUsingFilters(info);

    // Schedule the deletion of the proxy thread
    sender()->deleteLater();
}

void ThreadedFinder::addInfoToReportUsingFilters(ProxyInfo *info)
{
    for (auto code : filteredCodes) {
        if (static_cast<ProxyInfo*>(info)->getHttpStatusCode() == code) {
            report.append(info);
            emit reportChanged(report);
            break;
        }
    }
}

double ThreadedFinder::getProgress() const
{
    return progress;
}

void ThreadedFinder::setProgress(double value)
{
    progress = value;
    emit progressChanged(value);
}

QString ThreadedFinder::getRequestUrl() const
{
    return requestUrl;
}

void ThreadedFinder::setRequestUrl(const QString &value)
{
    if (requestUrl != value) {
        requestUrl = value;
        emit requestUrlChanged(value);
    }
}

ThreadedFinder::RequestType ThreadedFinder::getRequestType() const
{
    return requestType;
}

void ThreadedFinder::setRequestType(const ThreadedFinder::RequestType &value)
{
    if (requestType != value) {
        requestType = value;
        emit requestTypeChanged(value);
    }
}

int ThreadedFinder::getTimeout() const
{
    return timeout;
}

void ThreadedFinder::setTimeout(int value)
{
    if (timeout != value) {
        timeout = value;
        emit timeoutChanged(value);
    }
}

bool ThreadedFinder::getValidFinalAddress() const
{
    return validFinalAddress;
}

void ThreadedFinder::setValidFinalAddress(bool value)
{
    if (validFinalAddress != value) {
        validFinalAddress = value;
        emit validFinalAddressChanged(value);
    }
}

bool ThreadedFinder::getValidInitialAddress() const
{
    return validInitialAddress;
}

void ThreadedFinder::setValidInitialAddress(bool value)
{
    if (validInitialAddress != value) {
        validInitialAddress = value;
        emit validInitialAddressChanged(value);
    }
}

void ThreadedFinder::updateReport()
{
    report.clear();
    for (auto info : fullReport) {
        addInfoToReportUsingFilters(static_cast<ProxyInfo*>(info));
    }
    emit reportChanged(report);
}

QVariantList ThreadedFinder::getFilteredCodes() const
{
    return filteredCodes;
}

void ThreadedFinder::setFilteredCodes(const QVariantList &value)
{
    if (filteredCodes != value) {
        filteredCodes = value;
        emit filteredCodesChanged(value);
    }
}

bool ThreadedFinder::getScaning() const
{
    return scaning;
}

void ThreadedFinder::setScaning(bool value)
{
    if (scaning != value) {
        scaning = value;
        emit scaningChanged(value);
    }
}

QString ThreadedFinder::getFinalAddressString() const
{
    return finalAddressString;
}

void ThreadedFinder::setFinalAddressString(const QString &value)
{
    if (finalAddressString != value) {
        finalAddressString = value;
        setFinalAddress(QHostAddress(value));
        emit finalAddressStringChanged(value);
    }
}

QString ThreadedFinder::getInitialAddressString() const
{
    return initialAddressString;
}

void ThreadedFinder::setInitialAddressString(const QString &value)
{
    if (initialAddressString != value) {
        initialAddressString = value;
        setInitialAddress(QHostAddress(value));
        emit initialAddressStringChanged(value);
    }
}

QList<QObject *> ThreadedFinder::getReport() const
{
    return report;
}

unsigned short ThreadedFinder::getPort() const
{
    return port;
}

void ThreadedFinder::setPort(unsigned short value)
{
    if (port != value) {
        port = value;
        emit portChanged(value);
    }
}

QHostAddress ThreadedFinder::getFinalAddress() const
{
    return finalAddress;
}

void ThreadedFinder::setFinalAddress(const QHostAddress &value)
{
    finalAddress = value;
    setFinalAddressString(value.toString());
    setValidFinalAddress(!value.isNull());
}

QHostAddress ThreadedFinder::getInitialAddress() const
{
    return initialAddress;
}

void ThreadedFinder::setInitialAddress(const QHostAddress &value)
{
    initialAddress = value;
    setInitialAddressString(value.toString());
    setValidInitialAddress(!value.isNull());
}

unsigned int ThreadedFinder::getNumberOfThreads() const
{
    return maxThreads;
}

void ThreadedFinder::setNumberOfThreads(unsigned int value)
{
    if (maxThreads != value) {
        if (value == 0) {
            qWarning() << "Warning: Number of threads:" << value << endl;
        } else if (value > 500) {
            qWarning() << "Warning: Number of threads:" << value << "> 500" << endl;
        }
        maxThreads = value;
        emit maxThreadsChanged(value);
    }
}