#include <QRandomGenerator>
#include <QDebug>
#include <QElapsedTimer>
#include "dialog.h"
#include "ui_dialog.h"

#define INIT_X_RANGE 1000.0
#define INIT_Y_RANGE 2.0

Dialog::Dialog(QWidget *parent) :
    QDialog(parent), ui(new Ui::Dialog),
    m_chart(new QChart),
//    m_series(new QLineSeries),
    m_series(new QScatterSeries),
    m_xRange(INIT_X_RANGE), m_yRange(INIT_Y_RANGE),
    m_thread(new QThread(this)),
    m_dataProvider(new PlotDataProvider(m_thread)),
    m_sample_count(0)
{
    ui->setupUi(this);

    QChartView *chartView = new QChartView(m_chart);
    chartView->setMinimumSize(600, 400);
    ui->hLayoutTop->addWidget(chartView);

    m_series->setMarkerSize(5);
    m_chart->addSeries(m_series);
    m_chart->createDefaultAxes();

    axisX = static_cast<QValueAxis *>(
                m_chart->axes(Qt::Horizontal, m_series).at(0));
    axisY = static_cast<QValueAxis *>(
                m_chart->axes(Qt::Vertical, m_series).at(0));
    axisX->setRange(0, m_xRange);
    axisX->setLabelFormat("%g");
    axisX->setTitleText("sample count");
    axisY->setRange(0, m_yRange);
    axisY->setTitleText("Y");

    m_chart->legend()->hide();
    m_chart->setTitle("Chart 1");

    //
    m_dataProvider->moveToThread(m_thread);
    connect(m_dataProvider, SIGNAL(dataReady(QVector<double>)),
            this, SLOT(plotData(QVector<double>)));
}

Dialog::~Dialog()
{
    m_dataProvider->stop = true;
    m_thread->quit();
    m_thread->wait();
    //qDebug() << "m_thread stopped";
    m_dataProvider->deleteLater();
    delete ui;
}

void Dialog::on_buttonTest_clicked()
{
    double y = QRandomGenerator::global()->generateDouble();
    m_series->append(m_series->count(), y);

    if(m_series->count() > m_xRange)
      axisX->setRange(m_series->count()-m_xRange, m_series->count());
}

void Dialog::on_buttonStart_clicked()
{
    m_thread->start();
    ui->buttonStart->setEnabled(false);
}

void Dialog::plotData(QVector<double> data)
{
    static QElapsedTimer timer;
    timer.start();

    if(m_series->count() <= m_xRange)
    {
        foreach(double v, data)
        {
            m_series->append(m_sample_count, v);
            m_sample_count++;
        }
    }
    else
    {
        foreach(double v, data)
        {
            m_series->append(m_sample_count, v);
            m_series->remove(0);
            m_sample_count++;
        }
    }

    if(m_sample_count > m_xRange)
        axisX->setRange(m_sample_count-m_xRange, m_sample_count);

    qDebug() << "plotData() spent" << timer.elapsed() << "ms";
}
