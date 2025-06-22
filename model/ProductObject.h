#ifndef PRODUCTOBJECT_H
#define PRODUCTOBJECT_H

#include <QObject>
#include <QJsonObject>


/**
 * @class ProductObject
 * @brief Manages loading, saving, and manipulating product data in JSON format.
 *
 * This class encapsulates a QJsonObject that stores the entire product structure,
 * provides file I/O operations, and exposes methods for integration with the model.
 */
class ProductObject : public QObject
{
    Q_OBJECT

public:
    /**
     * @brief Constructor.
     * @param parent Optional parent QObject.
     */
    explicit ProductObject(QObject *parent = nullptr);

    /**
     * @brief Loads product configuration from the given file path.
     * @param in_filepath Path to the JSON file.
     * @return True if loading succeeded; false otherwise.
     */
    bool load(const QString& in_filepath);

    /**
     * @brief Saves current product configuration to a file.
     * @param in_filepath File path to write the JSON to.
     * @return True if saving succeeded; false otherwise.
     */
    bool save(const QString& in_filepath) const;

    /**
     * @brief Sets the internal product JSON object.
     * @param in_product_configs A QJsonObject containing product data.
     */
    void setProductObject(QJsonObject& in_product_configs);

    /**
     * @brief Retrieves the current product JSON object.
     * @return The internal QJsonObject representing product data.
     */
    QJsonObject getProductObject() const;

    /**
     * @brief Clears the internal JSON object.
     */
    void clear();

private:
    QJsonObject m_product_configs; ///< Internal JSON object storing product data.
};

#endif // PRODUCTOBJECT_H
