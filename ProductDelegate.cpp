#include "ProductDelegate.h"
#include <QList>
#include <QJsonObject>
#include "ProductModel.h"
#include "ProductItem.h"
#include "ProductObject.h"
#include <QCheckBox>

//////////////////////////////////////////////////////////////////////////
///
/// \brief  Constructor
///
//////////////////////////////////////////////////////////////////////////
ProductDelegate::ProductDelegate(QObject *in_p_parent) : QStyledItemDelegate(in_p_parent)
{

}
//////////////////////////////////////////////////////////////////////////
///
/// \brief  Destructor
///
//////////////////////////////////////////////////////////////////////////
ProductDelegate::~ProductDelegate()
{

}

//////////////////////////////////////////////////////////////////////////
///
/// \brief      create checkbox delegates
/// \param[in]  in_parent   ... parent widget
/// \param[in]  in_option   ...
/// \param[in]  in_index    ... the index used in model
/// \return     QWidget
///
//////////////////////////////////////////////////////////////////////////
QWidget *ProductDelegate::createEditor(QWidget *in_p_parent, const QStyleOptionViewItem &in_option, const QModelIndex &in_index) const
{
    if(in_index.column() == ProductModel::Column::Value)
    {
       QCheckBox *p_checkbox_editor = new QCheckBox(in_p_parent);
       return p_checkbox_editor;
    }
    else
        return QStyledItemDelegate::createEditor(in_p_parent, in_option, in_index);
}

//////////////////////////////////////////////////////////////////////////
///
/// \brief      edit values in the checkbox delegates
///
//////////////////////////////////////////////////////////////////////////
void ProductDelegate::setEditorData(QWidget *in_p_editor, const QModelIndex &in_index) const
{

    if(in_index.column() == ProductModel::Column::Value)
    {
        QModelIndex col_zero_index = in_index.sibling(in_index.row(), ProductModel::Column::ProductId);
        QVariant data_stored = col_zero_index.data(ProductItem::Roles::Data);
        const QJsonObject product_object = QJsonValue::fromVariant( data_stored ).toObject();
        bool value = product_object[s_PRODUCT_KEY].toObject()[s_AVAILABLE_KEY].toBool();
        QCheckBox *checkbox = static_cast<QCheckBox *>(in_p_editor);
        checkbox->setChecked(value);
    }
    else
        return QStyledItemDelegate::setEditorData(in_p_editor, in_index);
}

//////////////////////////////////////////////////////////////////////////
///
/// \brief      modify values in the model for every specific delegates
/// \param[in]  in_editor   ... generic editor
/// \param[in]  in_model    ... the model used
/// \param[in]  in_index    ... the index used in model
/// \return     void
///
//////////////////////////////////////////////////////////////////////////
void ProductDelegate::setModelData(QWidget *in_p_editor, QAbstractItemModel *in_p_model, const QModelIndex &in_index) const
{
    if(in_index.column() == ProductModel::Column::Value)
    {
        QCheckBox *checkbox = static_cast<QCheckBox *>(in_p_editor);
        bool value = checkbox->isChecked();
        in_p_model->setData(in_index, value, Qt::EditRole);
    }
    else
        QStyledItemDelegate::setModelData(in_p_editor,in_p_model,in_index);
}
//////////////////////////////////////////////////////////////////////////
///
/// \brief      updates the editor for the item specified by index according to the style option given.
/// \param[in]  in_editor   ... generic editor
/// \param[in]  in_option   ...
/// \param[in]  in_index    ... the index used in model
/// \return     void
///
//////////////////////////////////////////////////////////////////////////
void ProductDelegate::updateEditorGeometry(QWidget *in_p_editor, const QStyleOptionViewItem &in_option, const QModelIndex &in_index) const
{
    Q_UNUSED(in_index);
    if (Q_NULLPTR != in_p_editor)
        in_p_editor->setGeometry(in_option.rect);
}
//////////////////////////////////////////////////////////////////////////
///
/// \brief      Returns the size needed by the delegate to display the item specified by index,
/// taking into account the style information provided by option.
/// \param[in]  in_option   ...
/// \param[in]  in_index    ... the index used in model
/// \return     QSize
///
//////////////////////////////////////////////////////////////////////////
QSize ProductDelegate::sizeHint(const QStyleOptionViewItem &in_option, const QModelIndex &in_index) const
{
    return QStyledItemDelegate::sizeHint(in_option, in_index).
            expandedTo(QSize(200,in_option.fontMetrics.height() + 10));
}
