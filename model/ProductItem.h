#ifndef PRODUCTITEM_H
#define PRODUCTITEM_H
//////////////////////////////////////////////////////////////////////////
/// includes
//////////////////////////////////////////////////////////////////////////
#include <QObject>
#include <QJsonValue>
#include <QVariant>
#include <QStandardItem>
#include <assert.h>

//////////////////////////////////////////////////////////////////////////
///
/// \brief      The base item for the product table
///
//////////////////////////////////////////////////////////////////////////
class ProductItem : public QStandardItem
{

public:
    enum Roles
    {
        Undefined = Qt::UserRole + 1,
        Data,

    };
    explicit            ProductItem         (
                                            int in_role,
                                            QVariant in_value
                                            );
    int                 role                () const;
    void                setData             (
                                            const QVariant& in_value,
                                            int32_t in_role = Qt::EditRole
                                            );
    QVariant            data                (int32_t in_role = Qt::DisplayRole) const;
    void                setValue            (bool in_value);
    void                modifyJsonValue     (QJsonValue& in_destination_value,
                                             const QString& in_path,
                                             const QJsonValue& in_new_value = QJsonValue());

private:
    int                 m_role              = Undefined;        ///<    The role of the data
    QVariant            m_value             = QVariant();       ///<    the value of the item

};

#endif // PRODUCTITEM_H
