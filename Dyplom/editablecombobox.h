// editablecombobox.h
#ifndef EDITABLECOMBOBOX_H
#define EDITABLECOMBOBOX_H

#include <QComboBox>
#include <QSqlQuery>
#include <functional>
#include <QStandardItemModel>

class QCompleter;
class QSortFilterProxyModel;
class ComboBoxEditDelegate;

class EditableComboBox : public QComboBox
{
    Q_OBJECT
public:
    explicit EditableComboBox(QWidget *parent = nullptr);

    enum Mode {
        SearchMode,
        EditMode,
        AddMode
    };

    static constexpr int ADD_ITEM_ID = -999999;

    void setDbHandlers(std::function<QSqlQuery()> load, std::function<void(int, const QString&)> update = nullptr,
                       std::function<void(const QString&)> add = nullptr, std::function<void(int)> remove = nullptr,  bool allowAdd = false);
    void setMode(Mode mode);

private slots:
    void onIndexChanged(int index);
    void onEditingFinished();
    void onEditClicked(int id);

private:
    void reload();
    void setupCompleter();

private:
    QStandardItemModel *m_completerModel = nullptr;
    ComboBoxEditDelegate *m_delegate = nullptr;
    QCompleter *m_completer = nullptr;
    QSortFilterProxyModel *m_proxy = nullptr;
    bool eventFilter(QObject *obj, QEvent *event) override;

    Mode m_mode = SearchMode;
    int currentId = ADD_ITEM_ID;
    int editingId = ADD_ITEM_ID;
    bool m_allowAdd = true;
    QAbstractItemDelegate* m_defaultDelegate = nullptr;

    std::function<QSqlQuery()> loadFunc;
    std::function<void(int, const QString&)> updateFunc;
    std::function<void(const QString&)> addFunc;
    std::function<void(int)> deleteFunc;
};

#endif // EDITABLECOMBOBOX_H