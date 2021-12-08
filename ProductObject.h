#ifndef PRODUCTOBJECT_H
#define PRODUCTOBJECT_H
//////////////////////////////////////////////////////////////////////////
/// includes
//////////////////////////////////////////////////////////////////////////
#include <QObject>
#include <QJsonObject>

const static QString s_COMMENT_KEY("comment");
const static QString s_CONTAINER_KEY("container");
const static QString s_PRODUCTS_KEY("products");
const static QString s_PRODUCT_KEY("product");
const static QString s_PRODUCT_ID_KEY("product_id");
const static QString s_PRODUCT_NAME_KEY("product_name");
const static QString s_PRICE_KEY("price");
const static QString s_AVAILABLE_KEY("available");

//////////////////////////////////////////////////////////////////////////
///
/// \brief      A custom object which holds all json datas inside.
///
//////////////////////////////////////////////////////////////////////////
class ProductObject : public QObject
{
    Q_OBJECT
public:
    explicit    ProductObject               (QObject *parent = nullptr);
    void        load                       (const QString& in_filepath);
    void        save                       (const QString& in_filepath);
    void        setProductObject            (QJsonObject& in_product_configs);
    QJsonObject getProductObject            () const;

signals:

private:
    QJsonObject m_product_configs;    ///<    whole products
};

#endif // PRODUCTOBJECT_H
