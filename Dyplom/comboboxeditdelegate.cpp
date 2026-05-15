// comboboxeditdelegate.cpp
#include "comboboxeditdelegate.h"

#include <QPainter>
#include <QMouseEvent>
#include <QApplication>
#include <QStyle>
#include <QIcon>

ComboBoxEditDelegate::ComboBoxEditDelegate(int addItemId, QObject *parent)
    : QStyledItemDelegate(parent)
    , m_addItemId(addItemId)
{
}

void ComboBoxEditDelegate::paint(QPainter *p, const QStyleOptionViewItem &option, const QModelIndex &index) const{
    QStyledItemDelegate::paint(p, option, index);

    const int id = index.data(Qt::UserRole).toInt();
    if (id == m_addItemId)
        return;

    QRect rect = option.rect;

    QRect btnRect(rect.right() - BUTTON_W - BUTTON_MARGIN, rect.top() + (rect.height() - 16) / 2, 16, 16);

    static const QIcon editIcon(":/res/img/pencil.svg");

    editIcon.paint(p, btnRect, Qt::AlignCenter, QIcon::Normal);
}

bool ComboBoxEditDelegate::editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index){
    const int id = index.data(Qt::UserRole).toInt();

    if (id == m_addItemId)
        return QStyledItemDelegate::editorEvent(event, model, option, index);

    if (event->type() == QEvent::MouseButtonPress) {
        auto *e = static_cast<QMouseEvent*>(event);

        QRect rect = option.rect;
        QRect btnRect(rect.right() - BUTTON_W - BUTTON_MARGIN,
                      rect.top() + 4,
                      BUTTON_W,
                      rect.height() - 8);

        if (btnRect.contains(e->position().toPoint())) {
            emit editClicked(id);
            return true;
        }
    }

    return QStyledItemDelegate::editorEvent(event, model, option, index);
}