#include <QApplication>
#include <QTableView>
#include <QHeaderView>
#include <QTimer>
#include <QHBoxLayout>
#include <QWidget>
#include "process_table_model.h"
#include "kill_button_delegate.h"
#include "usage_graph.h"  // <-- include the new graph widget

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    // Main window
    QWidget mainWindow;

    // Create table view and model
    QTableView *table = new QTableView;
    auto *model = new ProcessTableModel(table);
    table->setModel(model);

    // Enable column sorting
    table->setSortingEnabled(true);
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    // Kill button delegate for last column
    auto *delegate = new KillButtonDelegate(model, table);
    table->setItemDelegateForColumn(4, delegate);

    // Create the usage graph widget
    UsageGraph *graph = new UsageGraph;

    // Layout: table on left, graph on right
    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(table, 2);   // stretch factor 2
    layout->addWidget(graph, 1);   // stretch factor 1

    mainWindow.setLayout(layout);
    mainWindow.setWindowTitle("System Monitor with Real-Time Graph");
    mainWindow.resize(1000, 500);
    mainWindow.show();

    // Refresh timer (every 2 seconds)
    QTimer timer;
    QObject::connect(&timer, &QTimer::timeout, [model]() {
        model->refresh();
    });
    timer.start(2000);

    return app.exec();
}
