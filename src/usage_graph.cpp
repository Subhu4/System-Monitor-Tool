#include "usage_graph.h"
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QValueAxis>
#include <QVBoxLayout>
#include <QTimer>
#include <QString>

UsageGraph::UsageGraph(QWidget *parent) : QWidget(parent)
{
    chart = new QChart();
    cpuSeries = new QLineSeries();
    memSeries = new QLineSeries();

    cpuSeries->setName("CPU%");
    memSeries->setName("Memory%");

    chart->addSeries(cpuSeries);
    chart->addSeries(memSeries);

    axisX = new QValueAxis();
    axisX->setRange(0, 60); // show last 60 seconds
    axisX->setLabelFormat("%d");
    axisX->setTitleText("Time (s)");

    axisY = new QValueAxis();
    axisY->setRange(0, 100); // percentage scale
    axisY->setTitleText("Usage %");

    chart->setAxisX(axisX, cpuSeries);
    chart->setAxisX(axisX, memSeries);
    chart->setAxisY(axisY, cpuSeries);
    chart->setAxisY(axisY, memSeries);

    chart->legend()->setVisible(true);
    chart->setTitle("CPU and Memory Usage");

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(chartView);
    setLayout(layout);

    // Update every 2 seconds to match your refresh
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &UsageGraph::updateData);
    timer->start(2000);
}

void UsageGraph::updateData()
{
    CPUInfo cpu = getCPUInfo();
    MemoryInfo mem = getMemoryInfo();

    cpuSeries->append(timeCounter, cpu.usage);
    memSeries->append(timeCounter, mem.usedPercent);

    // Keep only last 60 points
    if (cpuSeries->count() > 60) {
        cpuSeries->remove(0);
        memSeries->remove(0);
    }

    axisX->setRange(timeCounter > 60 ? timeCounter - 60 : 0, timeCounter);

    timeCounter += 2; // increment by 2s (matching your refresh)
}
