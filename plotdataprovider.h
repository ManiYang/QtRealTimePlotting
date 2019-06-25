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
    ~PlotDataProvider();
    bool stop;
    bool pause;

signals:
    void dataReady(VecD);

private slots:
    void run();
    void cleanUp();

private:
    QThread *m_thread;
};

#endif // PLOTDATAPROVIDER_H
