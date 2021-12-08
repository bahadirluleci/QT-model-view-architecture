#ifndef PRODUCTMODEL_H
#define PRODUCTMODEL_H
//////////////////////////////////////////////////////////////////////////
/// includes
//////////////////////////////////////////////////////////////////////////
#include <QObject>
#include <QStandardItemModel>
#include <QJsonObject>

//////////////////////////////////////////////////////////////////////////
///
/// \brief      The ProductModel for the ProductTableWidget
///
//////////////////////////////////////////////////////////////////////////
class ProductModel : public QStandardItemModel
{
    Q_OBJECT
public:

    enum Column
    {
        ProductId = 0,
        ProductName,
        ProductPrice,
        Value
    };
    explicit        ProductModel        (QObject *in_p_parent = nullptr);
    ~ProductModel                       ();
    void            setJson             (const QJsonObject& in_product_config);
    void            importProduct       (const QJsonObject& in_product_config);

    bool            setData             (
                                        const QModelIndex& in_index,
                                        const QVariant& in_value,
                                        int in_role = Qt::EditRole
                                        ) Q_DECL_OVERRIDE;
    QVariant        data                (
                                        const QModelIndex& in_index,
                                        int in_role = Qt::DisplayRole
                                        ) const Q_DECL_OVERRIDE;
    QVariant        headerData          (
                                        int in_section,
                                        Qt::Orientation in_orientation,
                                        int in_role
                                        ) const override;
    QJsonObject     jsonData            ()const;
    Qt::ItemFlags   flags               (const QModelIndex &index) const override;

signals:

};

#endif // PRODUCTMODEL_H
