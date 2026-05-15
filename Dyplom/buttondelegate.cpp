#include "buttondelegate.h"
#include <QMouseEvent>
#include <QStyleOptionButton>

ButtonDelegate::ButtonDelegate(TableType type, QObject *parent): QStyledItemDelegate(parent), m_type(type),m_mode(ActionMode::Edit){}

void ButtonDelegate::setMode(ActionMode mode){
    m_mode = mode;
}

void ButtonDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &) const{
    QStyleOptionButton button;
    button.rect = option.rect;

    if (m_mode == ActionMode::Edit)
        button.text = "Редагувати";
    else
        button.text = "Видалити";

    button.state = QStyle::State_Enabled;

    if (m_mode == ActionMode::Delete) {
        button.palette.setColor(QPalette::Button, Qt::red);
    }

    QApplication::style()->drawControl(QStyle::CE_PushButton, &button, painter);
}

bool ButtonDelegate::editorEvent(QEvent *event, QAbstractItemModel *, const QStyleOptionViewItem &, const QModelIndex &index){
    if (event->type() == QEvent::MouseButtonRelease) {

        int id = index.sibling(index.row(), 0).data().toInt();

        if (m_mode == ActionMode::Edit) {
            emit editClicked(id, m_type);
        } else {
            emit deleteClicked(id, m_type);
        }
    }

    return true;
}