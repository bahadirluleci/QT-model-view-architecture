#ifndef PRODUCTDELEGATE_H
#define PRODUCTDELEGATE_H
//////////////////////////////////////////////////////////////////////////
// includes
//////////////////////////////////////////////////////////////////////////
#include <QObject>
#include <QStyledItemDelegate>

//////////////////////////////////////////////////////////////////////////
///
/// \brief      The delegate class for showing delegates in the table Widget
///
//////////////////////////////////////////////////////////////////////////
class ProductDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit        ProductDelegate     (QObject *in_p_parent = nullptr);
    ~ProductDelegate                  ();

    // QAbstractItemDelegate interface
public:
    QWidget*        createEditor        (QWidget *in_p_parent, const QStyleOptionViewItem &in_option, const QModelIndex &in_index) const override;
    void            setEditorData(QWidget *in_p_editor, const QModelIndex &in_index) const override;
    void            setModelData        (QWidget *in_p_editor, QAbstractItemModel *in_p_model, const QModelIndex &in_index) const override;
    void            updateEditorGeometry(QWidget *in_p_editor, const QStyleOptionViewItem &in_option, const QModelIndex &in_index) const override;
    QSize           sizeHint            (const QStyleOptionViewItem &in_option, const QModelIndex &in_index) const override;

signals:

};

#endif // PRODUCTDELEGATE_H
