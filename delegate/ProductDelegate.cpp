#include "ProductDelegate.h"
#include <QList>
#include <QJsonObject>
#include "ProductModel.h"
#include "ProductItem.h"
#include "Constants.h"
#include <QCheckBox>


ProductDelegate::ProductDelegate(QObject *in_p_parent) : QStyledItemDelegate(in_p_parent)
{

}

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

void ProductDelegate::setEditorData(QWidget *in_p_editor, const QModelIndex &in_index) const
{

    if(in_index.column() == ProductModel::Column::Value)
    {
        QModelIndex col_zero_index = in_index.sibling(in_index.row(), ProductModel::Column::ProductId);
        QVariant data_stored = col_zero_index.data(ProductItem::Roles::Data);
        const QJsonObject product_object = QJsonValue::fromVariant( data_stored ).toObject();
        bool value = product_object[qstr(ProductKeys::Product)].toObject()[qstr(ProductKeys::Available)].toBool();
        QCheckBox *checkbox = static_cast<QCheckBox *>(in_p_editor);
        checkbox->setChecked(value);
    }
    else
        return QStyledItemDelegate::setEditorData(in_p_editor, in_index);
}

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

void ProductDelegate::updateEditorGeometry(QWidget *in_p_editor, const QStyleOptionViewItem &in_option, const QModelIndex &in_index) const
{
    Q_UNUSED(in_index);
    if (Q_NULLPTR != in_p_editor)
        in_p_editor->setGeometry(in_option.rect);
}

QSize ProductDelegate::sizeHint(const QStyleOptionViewItem &in_option, const QModelIndex &in_index) const
{
    return QStyledItemDelegate::sizeHint(in_option, in_index).
            expandedTo(QSize(200,in_option.fontMetrics.height() + 10));
}
