#include <QRandomGenerator>
#include <QDebug>
#include "plotdataprovider.h"


/*
Args:
    thread: the thread where this object is moved to
    parent: parent of this object
*/
PlotDataProvider::PlotDataProvider(QThread *thread, QObject *parent)
    : QObject(parent),
      stop(false), pause(false)
      m_thread(thread)
{
    connect(m_thread, SIGNAL(started()), this, SLOT(run()));
    connect(m_thread, SIGNAL(finished()), this, SLOT(cleanUp()));
    
    // initialization codes here:

}

PlotDataProvider::~PlotDataProvider()
{
}

void PlotDataProvider::cleanUp()
{
    // finishing (clean-up) codes here:

}

/*
This is the function containing codes executed in the thread.
*/
void PlotDataProvider::run()
{
    //qDebug() << "PlotDataProvider started running.";
    VecD data;
    while(!stop)
    {
        m_thread->msleep(200);
        if(!pause)
        {
            for(int i=0; i<40; i++)
                data.push_back(QRandomGenerator::global()->generateDouble());
            emit dataReady(data);
            data.clear();
        }
    }
    //qDebug() << "PlotDataProvider about to stop.";
}
