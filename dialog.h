#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QtCharts>
#include <QChart>
#include <QElapsedTimer>
#include "plotdataprovider.h"

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog();

private slots:
    void on_buttonTest_clicked();
    void on_buttonStart_clicked();
    void plotData(QVector<double> data);

private:
    Ui::Dialog *ui;
    QChart *m_chart;
    QValueAxis *axisX;
    QValueAxis *axisY;
//    QLineSeries *m_series;
    QScatterSeries *m_series;
    double m_xRange;
    double m_yRange;

    QThread *m_thread;
    PlotDataProvider *m_dataProvider;
    int m_sample_count;
};

#endif // DIALOG_H
