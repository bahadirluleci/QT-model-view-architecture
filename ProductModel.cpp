#include "ProductModel.h"
#include "ProductObject.h"
#include <QJsonArray>
#include "ProductItem.h"


//////////////////////////////////////////////////////////////////////////
///
/// \brief  Constructor
///
//////////////////////////////////////////////////////////////////////////
ProductModel::ProductModel(QObject *in_p_parent) : QStandardItemModel(in_p_parent)
{

}
//////////////////////////////////////////////////////////////////////////
///
/// \brief  Destructor
///
//////////////////////////////////////////////////////////////////////////
ProductModel::~ProductModel()
{

}
//////////////////////////////////////////////////////////////////////////
///
/// \brief      import a product file to the model
/// \param[in]  in_product_config   ... the product file as QJsonObject
/// \return     void
///
//////////////////////////////////////////////////////////////////////////
void ProductModel::setJson(const QJsonObject &in_product_config)
{
    QJsonArray products = in_product_config[s_CONTAINER_KEY].toObject()[s_PRODUCTS_KEY].toArray();
    if (products.size() <= 0)
        return;
    for (int i = 0; i < products.size(); ++i)
        importProduct(products[i].toObject());
}
//////////////////////////////////////////////////////////////////////////
///
/// \brief      import a single product to the model, append data to the model
/// \param[in]  in_product_config   ... the product as QJsonObject
/// \return     void
///
//////////////////////////////////////////////////////////////////////////
void ProductModel::importProduct(const QJsonObject &in_product_config)
{
    QList<QStandardItem*> product_items_list;
    product_items_list.append(new ProductItem(ProductItem::Data, QVariant(in_product_config)));
    product_items_list.append(new ProductItem(Qt::DisplayRole, QVariant()));
    product_items_list.append(new ProductItem(Qt::DisplayRole, QVariant()));
    product_items_list.append(new ProductItem(Qt::EditRole, QVariant()));
    appendRow(product_items_list);
}
//////////////////////////////////////////////////////////////////////////
///
/// \brief      set data in the model
/// \param[in]  in_index    ... the index used to set data in model
/// \param[in]  in_value    ... the new value to be set
/// \return     bool
///
//////////////////////////////////////////////////////////////////////////
bool ProductModel::setData(const QModelIndex &in_index, const QVariant &in_value, int in_role)
{
    if(false == in_index.isValid())
        return false;
    ProductItem* p_item = static_cast<ProductItem*>(item(in_index.row(),Column::ProductId));
    QJsonObject product_object = QJsonValue::fromVariant( p_item->data(ProductItem::Data)).toObject();
    bool value = product_object[s_PRODUCT_KEY].toObject()[s_AVAILABLE_KEY].toBool();
    bool something_changed = false;

    if(in_value.toBool() != value)
    {
        p_item->setValue(in_value.toBool());
        something_changed = true;
    }
    if(something_changed)
    {
        emit dataChanged(in_index,in_index);
        return true;
    }
    return false;
}
//////////////////////////////////////////////////////////////////////////
///
/// \brief      get data from the model
/// \param[in]  in_index    ... the index used to get data from model
/// \param[in]  in_role     ... the role
/// \return     QVariant
///
//////////////////////////////////////////////////////////////////////////
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
        QJsonObject product_object = json_object[s_PRODUCT_KEY].toObject();

        switch (in_index.column())
        {
            case Column::ProductId:
            {
                int64_t id = product_object[s_PRODUCT_ID_KEY].toString().toLongLong();
                return id;
            }break;
            case Column::ProductName:
            {
                QString product_name = product_object[s_PRODUCT_NAME_KEY].toString();
                return QVariant(product_name);
            }break;
            case Column::ProductPrice:
            {
                int64_t id = product_object[s_PRICE_KEY].toString().toLongLong();
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

//////////////////////////////////////////////////////////////////////////
///
/// \brief      set header data to the model
/// \param[in]  in_section  ... related section from model
/// \param[in]  in_role     ... the role
/// \param[in]  in_orientation     ... vertical or horizontal
/// \return     void
///
//////////////////////////////////////////////////////////////////////////
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
    return QVariant();
}

//////////////////////////////////////////////////////////////////////////
///
/// \brief      returns a product config from the tableview current datas
/// \return     QJsonObject
///
//////////////////////////////////////////////////////////////////////////
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
    inside_container.insert(s_PRODUCTS_KEY, products);
    container.insert(s_COMMENT_KEY, "Testdata ");
    container.insert(s_CONTAINER_KEY, inside_container);
    return container;
    return QJsonObject();
}

//////////////////////////////////////////////////////////////////////////
///
/// \brief      specifies colum is editable or not
/// \param[in]  in_index    ... the index used to get data from model
/// \return     Qt::ItemFlags
///
//////////////////////////////////////////////////////////////////////////
Qt::ItemFlags ProductModel::flags(const QModelIndex &index) const
{
    if(!index.isValid())
          return Qt::NoItemFlags;
      if(index.column() != 3)
      {
          return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
      }
      return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;
}
