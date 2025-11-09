#include "process_table_model.h"
#include <algorithm>
#include <QString>

ProcessTableModel::ProcessTableModel(QObject *parent)
    : QAbstractTableModel(parent)
{
    refresh();
}

int ProcessTableModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return static_cast<int>(m_processes.size());
}

int ProcessTableModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return 5; // PID, Name, CPU, MEM, Kill Button
}

QVariant ProcessTableModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || role != Qt::DisplayRole)
        return QVariant();

    const auto &p = m_processes[index.row()];
    switch (index.column())
    {
    case 0: return p.pid;
    case 1: return QString::fromStdString(p.name);
    case 2: return QString::number(p.cpuPercent, 'f', 2);
    case 3: return QString::number(p.memPercent, 'f', 2);
    case 4: return ""; // Kill button handled by delegate
    default: return QVariant();
    }
}

QVariant ProcessTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole || orientation != Qt::Horizontal)
        return QVariant();

    switch (section)
    {
    case 0: return "PID";
    case 1: return "Name";
    case 2: return "CPU%";
    case 3: return "MEM%";
    case 4: return "Kill";
    default: return QVariant();
    }
}

Qt::ItemFlags ProcessTableModel::flags(const QModelIndex &index) const
{
    Qt::ItemFlags defaultFlags = QAbstractTableModel::flags(index);
    if (index.column() == 4)
        return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
    return defaultFlags;
}

ProcessInfo ProcessTableModel::processAt(int row) const
{
    if (row < 0 || static_cast<size_t>(row) >= m_processes.size())
        return {0, "", 0.0, 0.0};
    return m_processes[row];
}

void ProcessTableModel::refresh()
{
    beginResetModel();
    m_processes = getProcessList();
    endResetModel();

    // re-apply previous sort if any
    if (m_lastSortColumn >= 0)
        sort(m_lastSortColumn, m_lastSortOrder);
}

void ProcessTableModel::sort(int column, Qt::SortOrder order)
{
    if (column >= 0)
    {
        m_lastSortColumn = column;
        m_lastSortOrder = order;
    }

    if (column == 0) // PID
    {
        std::sort(m_processes.begin(), m_processes.end(), [order](const ProcessInfo &a, const ProcessInfo &b) {
            return (order == Qt::AscendingOrder) ? a.pid < b.pid : a.pid > b.pid;
        });
    }
    else if (column == 2) // CPU
    {
        std::sort(m_processes.begin(), m_processes.end(), [order](const ProcessInfo &a, const ProcessInfo &b) {
            return (order == Qt::AscendingOrder) ? a.cpuPercent < b.cpuPercent : a.cpuPercent > b.cpuPercent;
        });
    }
    else if (column == 3) // MEM
    {
        std::sort(m_processes.begin(), m_processes.end(), [order](const ProcessInfo &a, const ProcessInfo &b) {
            return (order == Qt::AscendingOrder) ? a.memPercent < b.memPercent : a.memPercent > b.memPercent;
        });
    }

    emit dataChanged(index(0,0), index(rowCount()-1, columnCount()-1));
}
