#ifndef PLOTDATAPROVIDER_H
#define PLOTDATAPROVIDER_H

#include <QObject>
#include <QThread>
#include <QMetaType>
#include <QVector>

typedef QVector<double> VecD;

class PlotDataProvider : public QObject
{
    Q_OBJECT
public:
    explicit PlotDataProvider(QThread *thread, QObject *parent = nullptr);
    bool stop;

signals:
    void dataReady(VecD);

public slots:
    void run();

private:
    QThread *m_thread;
};

#endif // PLOTDATAPROVIDER_H
