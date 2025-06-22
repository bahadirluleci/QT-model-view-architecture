#ifndef PRODUCTMODEL_H
#define PRODUCTMODEL_H

#include <QObject>
#include <QStandardItemModel>
#include <QJsonObject>

/**
 * @class ProductModel
 * @brief A custom item model for displaying and editing product data in tabular form.
 *
 * This class supports loading and importing product data from JSON,
 * and customizing editing/display logic via overridden Qt model functions.
 */
class ProductModel : public QStandardItemModel
{
    Q_OBJECT
public:

    /**
     * @enum Column
     * @brief Enumeration for product table columns.
     */
    enum Column
    {
        ProductId = 0,   ///< ID column
        ProductName,     ///< Name column
        ProductPrice,    ///< Price column
        Value            ///< Generic value column
    };

    /**
     * @brief Constructor.
     * @param in_p_parent Optional parent QObject.
     */
    explicit        ProductModel        (QObject *in_p_parent = nullptr);

    /**
     * @brief Destructor.
     */
    virtual ~ProductModel                       () = default;

    /**
     * @brief Overwrites model data with the given JSON configuration.
     * @param in_product_config JSON object representing the full product list.
     */
    void            setJson             (const QJsonObject& in_product_config);

    /**
     * @brief Appends new data to the existing model from a JSON object.
     * @param in_product_config JSON object with one or more product entries.
     */
    void            importProduct       (const QJsonObject& in_product_config);


    /**
     * @brief Reimplements QAbstractItemModel::setData to handle edits.
     * @param in_index The model index to edit.
     * @param in_value The new value.
     * @param in_role The edit role (default: Qt::EditRole).
     * @return true if the data was set; false otherwise.
     */
    bool            setData             (
                                        const QModelIndex& in_index,
                                        const QVariant& in_value,
                                        int in_role = Qt::EditRole
                                        ) Q_DECL_OVERRIDE;

    /**
     * @brief Reimplements QAbstractItemModel::data to return item content.
     * @param in_index The index to retrieve data for.
     * @param in_role The role for which data is requested.
     * @return QVariant containing the item data.
     */
    QVariant        data                (
                                        const QModelIndex& in_index,
                                        int in_role = Qt::DisplayRole
                                        ) const Q_DECL_OVERRIDE;




    /**
     * @brief Reimplements QAbstractItemModel::headerData to provide custom headers.
     * @param in_section The section number (column or row).
     * @param in_orientation Qt::Horizontal or Qt::Vertical.
     * @param in_role The role for which the header data is requested.
     * @return The header label for the given section and role.
     */
    QVariant        headerData          (
                                        int in_section,
                                        Qt::Orientation in_orientation,
                                        int in_role
                                        ) const override;

    /**
     * @brief Serializes the current model data into a QJsonObject.
     * @return A QJsonObject containing the current product table content.
     */
    QJsonObject     jsonData            ()const;

    /**
     * @brief Reimplements QAbstractItemModel::flags to customize item behavior.
     * @param index The index to get item flags for.
     * @return Flags indicating item capabilities (editable, selectable, etc.).
     */
    Qt::ItemFlags   flags               (const QModelIndex &index) const override;

signals:

};

#endif // PRODUCTMODEL_H
