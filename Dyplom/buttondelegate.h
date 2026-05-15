#ifndef BUTTONDELEGATE_H
#define BUTTONDELEGATE_H

#include <QStyledItemDelegate>
#include <QPainter>
#include <QApplication>

enum class TableType {
    Group,
    Teacher,
    Speciality,
    Discipline
};

enum class ActionMode {
    Edit,
    Delete
};

class ButtonDelegate : public QStyledItemDelegate
{
    Q_OBJECT

public:
    explicit ButtonDelegate(TableType type, QObject *parent = nullptr);

    void setMode(ActionMode mode);

signals:
    void editClicked(int id, TableType type);
    void deleteClicked(int id, TableType type);

protected:
    void paint(QPainter *painter,
               const QStyleOptionViewItem &option,
               const QModelIndex &index) const override;

    bool editorEvent(QEvent *event,
                     QAbstractItemModel *model,
                     const QStyleOptionViewItem &option,
                     const QModelIndex &index) override;

private:
    TableType m_type;
    ActionMode m_mode;
};

#endif // BUTTONDELEGATE_H