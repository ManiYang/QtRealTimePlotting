#ifndef PLOTDATAPROVIDER_H
#define PLOTDATAPROVIDER_H

#include <QObject>
#include <QThread>

class PlotDataProvider : public QObject
{
    Q_OBJECT
public:
    explicit PlotDataProvider(QThread *thread, QObject *parent = nullptr);
    bool stop;

signals:
    void dataReady(QVector<double> data);

public slots:
    void run();

private:
    QThread *m_thread;
};

#endif // PLOTDATAPROVIDER_H
