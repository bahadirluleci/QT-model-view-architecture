#ifndef PRODUCTITEM_H
#define PRODUCTITEM_H

#include <QStandardItem>
#include <QJsonValue>
#include <QVariant>

/**
 * @class ProductItem
 * @brief Represents a custom item in the product table with custom roles and JSON integration.
 */
class ProductItem : public QStandardItem
{
public:
    /**
     * @enum Roles
     * @brief Custom roles for handling specific data types.
     */
    enum Roles
    {
        Undefined = Qt::UserRole + 1, ///< Undefined role
        Data                             ///< JSON or QVariant data role
    };

    /**
     * @brief Constructs a ProductItem with the given role and value.
     * @param role The role of the item.
     * @param value The value to store.
     */
    explicit ProductItem(int role, QVariant value);

    /**
     * @brief Returns the item's role.
     * @return The role of the item.
     */
    int role() const;

    /**
     * @brief Sets the item data for a specific role.
     * @param value The value to set.
     * @param role The role to apply the value to. Default is Qt::EditRole.
     */
    void setData(const QVariant& value, int32_t role = Qt::EditRole) override;

    /**
     * @brief Retrieves data for a specific role.
     * @param role The role to retrieve data for. Default is Qt::DisplayRole.
     * @return The value for the specified role.
     */
    QVariant data(int32_t role = Qt::DisplayRole) const override;

    /**
     * @brief Modifies the internal value assuming it is a JSON and replaces a bool at a known path.
     * @param value The boolean value to update inside JSON.
     */
    void setValue(bool value);

    /**
     * @brief Modifies a QJsonValue deeply based on the given path.
     * @param destinationValue The JSON value to modify.
     * @param path The JSON path (e.g., "root.field[0].child").
     * @param newValue The new value to insert.
     */
    void modifyJsonValue(QJsonValue& destinationValue, const QString& path, const QJsonValue& newValue = QJsonValue());

private:
    int m_role = Undefined;       ///< Internal role value
    QVariant m_value;             ///< Stored QVariant value
};

#endif // PRODUCTITEM_H
