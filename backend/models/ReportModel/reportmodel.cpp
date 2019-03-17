#include "reportmodel.h"
#include <QDebug>

ReportModel::ReportModel(QList<ProxyInfo *> dataReport, QObject *parent) : QAbstractListModel(parent)
{
    report = dataReport;
}

int ReportModel::rowCount(const QModelIndex &parent) const
{
    (void)parent;
    //qDebug() << report.count();
    return report.count();
}

QVariant ReportModel::data(const QModelIndex &index, int role) const
{
    switch (role) {
    case HostNameRole:
        return report[index.row()]->getHostName();
    case HttpStatusCodeRole:
        return report[index.row()]->getHttpStatusCode();
    case HttpReasonPhraseRole:
        return report[index.row()]->getHttpReasonPhrase();
    default:
        return QVariant();
    }
}

QHash<int, QByteArray> ReportModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[HostNameRole] = "hostName";
    roles[HttpStatusCodeRole] = "httpStatusCode";
    roles[HttpReasonPhraseRole] = "httpReasonPhrase";
    return roles;
}

bool ReportModel::insertRows(int row, int count, const QModelIndex &parent)
{
    qDebug() << "Insert rows";
    if (row <= 0 || row > report.count()) {
        return false;
    }
    beginInsertRows(parent, row, row + count);
    endInsertRows();
    return true;
}

bool ReportModel::removeRows(int row, int count, const QModelIndex &parent)
{
    qDebug() << "Remove rows";
    if (row < 0 || row >= report.count()) {
        return false;
    }
    beginRemoveRows(parent, row, row + count);
    for (int i = row; i <= row + count; ++i) {
        report.removeAt(i);
    }
    qDebug() << report.count();
    endRemoveRows();
    return true;
}

QList<ProxyInfo *> ReportModel::getReport() const
{
    return report;
}

void ReportModel::append(ProxyInfo *info)
{
    report.append(info);
    insertRow(rowCount());
}

void ReportModel::clear()
{
    removeRows(0, report.count());
    //report.clear();
}
