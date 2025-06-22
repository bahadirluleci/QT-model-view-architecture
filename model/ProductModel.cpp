#include "ProductModel.h"
#include "Constants.h"
#include "ProductItem.h"
#include <QJsonArray>


ProductModel::ProductModel(QObject *in_p_parent) : QStandardItemModel(in_p_parent)
{

}

void ProductModel::setJson(const QJsonObject &in_product_config)
{
    QJsonArray products = in_product_config[qstr(ProductKeys::Container)].toObject()[qstr(ProductKeys::Products)].toArray();
    if (products.size() <= 0)
        return;
    for (int i = 0; i < products.size(); ++i)
        importProduct(products[i].toObject());
}

void ProductModel::importProduct(const QJsonObject &in_product_config)
{
    auto *idItem      = new ProductItem(ProductItem::Data, in_product_config);
    auto *nameItem    = new ProductItem(Qt::EditRole, QVariant());
    auto *priceItem   = new ProductItem(Qt::EditRole, QVariant());
    auto *valueItem   = new ProductItem(Qt::EditRole, QVariant());

    QList<QStandardItem*> row;
    row << idItem << nameItem << priceItem << valueItem;

    appendRow(row);
}


bool ProductModel::setData(const QModelIndex& in_index, const QVariant& in_value, int in_role)
{
    if (!in_index.isValid() || in_role != Qt::EditRole)
        return false;

    // Retrieve the root item holding JSON data (column 0)
    ProductItem* p_root_item = static_cast<ProductItem*>(item(in_index.row(), Column::ProductId));
    if (!p_root_item)
        return false;

    QJsonObject product_object = QJsonValue::fromVariant(p_root_item->data(ProductItem::Data)).toObject();
    QJsonObject inner_product = product_object[qstr(ProductKeys::Product)].toObject();

    QString targetKey;
    switch (in_index.column()) {
    case Column::ProductName:
        targetKey = qstr(ProductKeys::ProductName);
        break;
    case Column::ProductPrice:
        targetKey = qstr(ProductKeys::Price);
        break;
    case Column::Value:
        targetKey = qstr(ProductKeys::Available);
        break;
    default:
        return false;
    }

    // Only update if changed
    if (inner_product[targetKey] != QJsonValue::fromVariant(in_value)) {
        QString fullPath = QString("%1.%2").arg(qstr(ProductKeys::Product), targetKey);
        p_root_item->setValue(in_value, fullPath);
        emit dataChanged(in_index, in_index);
        return true;
    }

    return false;
}


QVariant ProductModel::data(const QModelIndex &in_index, int in_role) const
{
    if (in_index.isValid() == false)
        return QVariant();
    ProductItem* p_item = static_cast<ProductItem*>(item(in_index.row(),Column::ProductId));
    if (nullptr == p_item)
        return QVariant();
    if(in_role == Qt::DisplayRole || in_role == Qt::EditRole)
    {
        QJsonObject json_object = QJsonValue::fromVariant( p_item->data(in_role) ).toObject();
        QJsonObject product_object = json_object[qstr(ProductKeys::Product)].toObject();

        switch (in_index.column())
        {
            case Column::ProductId:
            {
                int64_t id = product_object[qstr(ProductKeys::ProductId)].toString().toLongLong();
                return id;
            }break;
            case Column::ProductName:
            {
                QString product_name = product_object[qstr(ProductKeys::ProductName)].toString();
                return QVariant(product_name);
            }break;
            case Column::ProductPrice:
            {
                int64_t id = product_object[qstr(ProductKeys::Price)].toString().toLongLong();
                return id;
            }break;
            case  Column::Value:
            {
                return QVariant();
            }break;
        }
    }
    return p_item->data(in_role);
}


QVariant ProductModel::headerData(int in_section, Qt::Orientation in_orientation, int in_role) const
{
    if(in_role != Qt::DisplayRole)
            return QVariant();
    if (in_orientation == Qt::Horizontal)
    {
        switch(in_section)
        {
            case 0:
                return QString(tr("Id"));
            case 1:
                return QString(tr("ProductName"));
            case 2:
                return QString(tr("Price"));
            case 3:
                return QString(tr("Value"));
        }
    }
    return QString("%1").arg(in_section + 1);
}


QJsonObject ProductModel::jsonData() const
{
    QJsonArray products;
    for(int i=0; i<rowCount(); i++)
    {
        ProductItem* p_item = static_cast<ProductItem*>(item(i,Column::ProductId));
        QJsonObject product_json_object = QJsonValue::fromVariant( p_item->data(ProductItem::Data) ).toObject();
        products.append(product_json_object);
    }
    QJsonObject container;
    QJsonObject inside_container;
    inside_container.insert(qstr(ProductKeys::Products), products);
    container.insert(qstr(ProductKeys::Comment), "Testdata ");
    container.insert(qstr(ProductKeys::Container), inside_container);
    return container;
}

Qt::ItemFlags ProductModel::flags(const QModelIndex &index) const {
    if (!index.isValid())
        return Qt::NoItemFlags;
    if (index.column() == ProductName | index.column() == ProductPrice | index.column() == Value)
        return Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsEditable;
    else
        return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}

