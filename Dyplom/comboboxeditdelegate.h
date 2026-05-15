// comboboxeditdelegate.h
#ifndef COMBOBOXEDITDELEGATE_H
#define COMBOBOXEDITDELEGATE_H

#include <QStyledItemDelegate>

class ComboBoxEditDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit ComboBoxEditDelegate(int addItemId, QObject *parent = nullptr);

signals:
    void editClicked(int id);

protected:
    void paint(QPainter *p, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    bool editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index) override;

private:
    static constexpr int BUTTON_W = 20;
    static constexpr int BUTTON_MARGIN = 20;

    int m_addItemId;
};

#endif // COMBOBOXEDITDELEGATE_H