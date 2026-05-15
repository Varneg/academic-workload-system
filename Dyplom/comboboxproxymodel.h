#ifndef COMBOBOXPROXYMODEL_H
#define COMBOBOXPROXYMODEL_H

#include <QSortFilterProxyModel>

class ComboBoxProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT

public:
    explicit ComboBoxProxyModel(QObject *parent = nullptr);

    static constexpr int ADD_ITEM_ID = -999999;

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const override;

    QModelIndex mapToSource(const QModelIndex &proxyIndex) const override;
    QModelIndex mapFromSource(const QModelIndex &sourceIndex) const override;
};

#endif // COMBOBOXPROXYMODEL_H