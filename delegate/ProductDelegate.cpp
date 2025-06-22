#include "ProductDelegate.h"
#include "ProductModel.h"
#include "ProductItem.h"
#include "Constants.h"

#include <QList>
#include <QJsonObject>
#include <QCheckBox>
#include <QStyleOptionButton>
#include <QMouseEvent>
#include <QApplication>



ProductDelegate::ProductDelegate(QObject *in_p_parent) : QStyledItemDelegate(in_p_parent)
{

}

QWidget *ProductDelegate::createEditor(QWidget *, const QStyleOptionViewItem &, const QModelIndex &) const
{
    return nullptr;  // No editor for checkboxes — handle directly
}


void ProductDelegate::paint(QPainter *in_painter, const QStyleOptionViewItem &in_option, const QModelIndex &in_index) const
{
    if (in_index.column() == ProductModel::Column::Value)
    {
        QModelIndex idIndex = in_index.sibling(in_index.row(), ProductModel::Column::ProductId);
        QJsonObject json = QJsonValue::fromVariant(idIndex.data(ProductItem::Data)).toObject();
        bool checked = json[qstr(ProductKeys::Product)].toObject()[qstr(ProductKeys::Available)].toBool();

        QStyleOptionButton checkboxOption;
        checkboxOption.state |= QStyle::State_Enabled;
        checkboxOption.state |= checked ? QStyle::State_On : QStyle::State_Off;
        checkboxOption.rect = in_option.rect;

        QApplication::style()->drawControl(QStyle::CE_CheckBox, &checkboxOption, in_painter);
    }
    else
    {
        QStyledItemDelegate::paint(in_painter, in_option, in_index);
    }
}

bool ProductDelegate::editorEvent(QEvent *in_event, QAbstractItemModel *in_model,
                                  const QStyleOptionViewItem &in_option, const QModelIndex &in_index)
{
    if (in_index.column() == ProductModel::Column::Value &&
        (in_event->type() == QEvent::MouseButtonRelease || in_event->type() == QEvent::MouseButtonDblClick))
    {
        QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(in_event);
        if (in_option.rect.contains(mouseEvent->pos()))
        {
            QModelIndex idIndex = in_index.sibling(in_index.row(), ProductModel::Column::ProductId);
            QJsonObject json = QJsonValue::fromVariant(idIndex.data(ProductItem::Data)).toObject();
            bool checked = json["product"].toObject()["available"].toBool();

            return in_model->setData(in_index, !checked, Qt::EditRole);
        }
    }

    return QStyledItemDelegate::editorEvent(in_event, in_model, in_option, in_index);
}

QSize ProductDelegate::sizeHint(const QStyleOptionViewItem &in_option, const QModelIndex &in_index) const
{
    return QStyledItemDelegate::sizeHint(in_option, in_index).expandedTo(QSize(200,in_option.fontMetrics.height() + 10));
}
