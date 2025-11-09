#pragma once
#include <QStyledItemDelegate>
#include <QPushButton>
#include <QApplication>
#include <QPainter>
#include <QMouseEvent>
#include <signal.h>
#include "process_table_model.h"
#include <QMessageBox> 

class KillButtonDelegate : public QStyledItemDelegate {
    Q_OBJECT
    ProcessTableModel *m_model;
public:
    KillButtonDelegate(ProcessTableModel *model, QObject *parent = nullptr)
        : QStyledItemDelegate(parent), m_model(model) {}

    void paint(QPainter *painter, const QStyleOptionViewItem &option,
               const QModelIndex &index) const override {
        QStyleOptionButton button;
        button.rect = option.rect.adjusted(4, 4, -4, -4);
        button.text = "Kill";
        button.state = QStyle::State_Enabled;
        QApplication::style()->drawControl(QStyle::CE_PushButton, &button, painter);
    }

    bool editorEvent(QEvent *event, QAbstractItemModel *model,
                     const QStyleOptionViewItem &option, const QModelIndex &index) override {
        if (event->type() == QEvent::MouseButtonRelease) {
            auto me = static_cast<QMouseEvent*>(event);
            if (option.rect.contains(me->pos())) {
                ProcessTableModel *ptm = static_cast<ProcessTableModel*>(model);
                int pid = ptm->processAt(index.row()).pid;

                if (kill(pid, SIGKILL) == 0) {
                    // Refresh model after killing
                    ptm->refresh();
                } else {
                    // Show error message
                    QMessageBox::warning(nullptr, "Error", "Failed to kill process (Permission denied?)");
                }
            }
        }
        return true;
    }
};
