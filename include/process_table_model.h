#pragma once
#include <QAbstractTableModel>
#include <vector>
#include "system_info.h"

class ProcessTableModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit ProcessTableModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;

    ProcessInfo processAt(int row) const;
    void refresh();
    void sort(int column, Qt::SortOrder order = Qt::AscendingOrder) override;

private:
    std::vector<ProcessInfo> m_processes;
    int m_lastSortColumn = -1;
    Qt::SortOrder m_lastSortOrder = Qt::AscendingOrder;
};
