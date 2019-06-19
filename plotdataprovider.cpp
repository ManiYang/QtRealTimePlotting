#include <QRandomGenerator>
#include <QDebug>
#include "plotdataprovider.h"

PlotDataProvider::PlotDataProvider(QThread *thread, QObject *parent)
    : QObject(parent),
      stop(false),
      m_thread(thread)
{
    connect(m_thread, SIGNAL(started()), this, SLOT(run()));
}

void PlotDataProvider::run()
{
    //qDebug() << "PlotDataProvider started running.";
    QVector<double> data;
    while(!stop)
    {
        m_thread->msleep(200);
        for(int i=0; i<40; i++)
            data.push_back(QRandomGenerator::global()->generateDouble());
        emit dataReady(data);
        data.clear();
    }
    //qDebug() << "PlotDataProvider about to stop.";
}
