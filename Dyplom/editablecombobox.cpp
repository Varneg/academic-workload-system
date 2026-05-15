#include "editablecombobox.h"
#include "comboboxeditdelegate.h"

#include <QLineEdit>
#include <QCompleter>
#include <QSortFilterProxyModel>
#include <QAbstractItemView>
#include <QMetaObject>
#include <QEvent>
#include <QKeyEvent>
#include <QException>
#include "ErrorHandler.h"

EditableComboBox::EditableComboBox(QWidget *parent)
    : QComboBox(parent)
{
    setEditable(true);

    m_delegate = new ComboBoxEditDelegate(ADD_ITEM_ID, this);
    connect(m_delegate, &ComboBoxEditDelegate::editClicked, this, &EditableComboBox::onEditClicked);

    view()->setItemDelegate(m_delegate);
    connect(this, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &EditableComboBox::onIndexChanged);
    connect(lineEdit(), &QLineEdit::editingFinished, this, &EditableComboBox::onEditingFinished);
    lineEdit()->installEventFilter(this);
    connect(lineEdit(),
            &QLineEdit::textEdited,
            this,
            [this](const QString &text) {
                if (m_mode != SearchMode || !m_completer)
                    return;

                m_completer->setCompletionPrefix(text);
                m_completer->complete();
            });
}

bool EditableComboBox::eventFilter(QObject *obj, QEvent *event){
    if (obj == lineEdit()) {
        if (event->type() == QEvent::KeyPress) {
            auto *ke = static_cast<QKeyEvent*>(event);

            if (ke->key() == Qt::Key_Return || ke->key() == Qt::Key_Enter) {
                onEditingFinished();
                return true;
            }
        }
        else if (event->type() == QEvent::FocusOut) {
            onEditingFinished();
        }
    }

    return QComboBox::eventFilter(obj, event);
}

void EditableComboBox::setDbHandlers(std::function<QSqlQuery()> load, std::function<void(int, const QString&)> update,
                                     std::function<void(const QString&)> add, std::function<void(int)> remove,  bool allowAdd){
    loadFunc = std::move(load);
    updateFunc = std::move(update);
    addFunc = std::move(add);
    deleteFunc = std::move(remove);
    m_allowAdd = allowAdd;

    if (m_allowAdd) {
        view()->setItemDelegate(m_delegate);
    } else {
        view()->setItemDelegate(new QStyledItemDelegate(view()));
    }

    reload();
}

void EditableComboBox::reload(){
    if (!loadFunc)
        return;

    clear();

    addItem("", -1);
    QSqlQuery q = loadFunc();

    while (q.next()) {
        addItem(q.value(1).toString(), q.value(0).toInt());
    }

    if(m_allowAdd)
        addItem("Додати...", ADD_ITEM_ID);

    setupCompleter();
}

void EditableComboBox::setupCompleter(){
    if (!m_proxy) {
        m_proxy = new QSortFilterProxyModel(this);
        m_proxy->setFilterCaseSensitivity(Qt::CaseInsensitive);
    }

    m_proxy->setSourceModel(model());

    if (!m_completer) {
        m_completer = new QCompleter(m_proxy, this);
        m_completer->setWidget(lineEdit());
        m_completer->setCaseSensitivity(Qt::CaseInsensitive);
        m_completer->setFilterMode(Qt::MatchContains);
        m_completer->setCompletionMode(QCompleter::PopupCompletion);

        connect(m_completer,
                QOverload<const QString &>::of(&QCompleter::activated),
                this,
                [this](const QString &text) {
                    int row = findText(text);
                    if (row >= 0)
                        setCurrentIndex(row);
                });
    }

    if (m_mode == SearchMode)
        setCompleter(m_completer);
}

void EditableComboBox::setMode(Mode mode){
    m_mode = mode;

    if (m_mode == SearchMode)
        setCompleter(m_completer);
    else
        setCompleter(nullptr);
}

void EditableComboBox::onIndexChanged(int index){
    if (index < 0)
        return;

    QVariant data = itemData(index);

    if (!data.isValid() || data.isNull()) {
        currentId = -1;
        return;
    }

    currentId = data.toInt();

    if (currentId == ADD_ITEM_ID) {
        m_mode = AddMode;
        setEditText("");
        lineEdit()->setFocus();
        return;
    }

    if (m_mode != EditMode)
        m_mode = SearchMode;
}

void EditableComboBox::onEditingFinished()
{
    if (m_mode == SearchMode)
        return;

    const QString text = currentText().trimmed();

    try {
        if (m_mode == EditMode) {
            if (text.isEmpty()) {
                if (deleteFunc)
                    deleteFunc(currentId);

                reload();
                setCurrentIndex(0);
                currentId = -1;
                m_mode = SearchMode;
                return;
            } else {
                if (updateFunc)
                    updateFunc(currentId, text);
            }
        }
        else if (m_mode == AddMode) {
            if (text.isEmpty()) {
                setCurrentIndex(0);
                currentId = -1;
                m_mode = SearchMode;
                return;
            }

            if (findText(text) != -1) {
                m_mode = SearchMode;
                return;
            }

            if (addFunc)
                addFunc(text);
        }
    }
    catch (const std::exception &e) {
        ErrorHandler::showError(this, "Помилка", e);
        return;
    }

    reload();

    int row = findText(text);
    if (row >= 0)
        setCurrentIndex(row);

    m_mode = SearchMode;
}

void EditableComboBox::onEditClicked(int id){
    int row = findData(id);
    if (row < 0)
        return;

    QMetaObject::invokeMethod(this, [this, row, id]() {
        editingId = id;
        setCurrentIndex(row);
        m_mode = EditMode;

        lineEdit()->setFocus();
        lineEdit()->selectAll();
    }, Qt::QueuedConnection);
}