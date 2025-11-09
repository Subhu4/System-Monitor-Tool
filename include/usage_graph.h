#pragma once
#include <QWidget>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QValueAxis>
#include <QTimer>
#include "system_info.h"

QT_CHARTS_USE_NAMESPACE

class UsageGraph : public QWidget
{
    Q_OBJECT
public:
    UsageGraph(QWidget *parent = nullptr);

public slots:
    void updateData(); // called periodically to update graph

private:
    QChart *chart;
    QLineSeries *cpuSeries;
    QLineSeries *memSeries;
    QValueAxis *axisX;
    QValueAxis *axisY;

    int timeCounter = 0; // x-axis counter
};
