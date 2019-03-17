#ifndef REPORTMODEL_H
#define REPORTMODEL_H

#include <QObject>

class ReportModel : public QObject
{
    Q_OBJECT
public:
    explicit ReportModel(QObject *parent = nullptr);

signals:

public slots:
};

#endif // REPORTMODEL_H