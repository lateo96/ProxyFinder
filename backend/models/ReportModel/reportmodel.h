#ifndef REPORTMODEL_H
#define REPORTMODEL_H

#include <QAbstractListModel>
#include "../../ProxyInfo/proxyinfo.h"

class ReportModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit ReportModel(QList<ProxyInfo*> dataReport = QList<ProxyInfo*>(), QObject *parent = nullptr);

    enum Roles { HostNameRole = Qt::UserRole + 1, HttpStatusCodeRole, HttpReasonPhraseRole };
    Q_ENUM(Roles)

    // Pure virtual functions
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    QHash<int, QByteArray> roleNames() const;

    // Others virtual functions
    bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex());
    bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex());

    QList<ProxyInfo *> getReport() const;
    void append(ProxyInfo *info);

signals:

public slots:
    void clear();

private:
    QList<ProxyInfo*> report;
};

#endif // REPORTMODEL_H
