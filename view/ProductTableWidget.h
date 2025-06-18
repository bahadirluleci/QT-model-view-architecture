#ifndef PRODUCTTABLEWIDGET_H
#define PRODUCTTABLEWIDGET_H

#include <QWidget>
#include <QJsonObject>

// Forward declarations
class QVBoxLayout;
class QTableView;
class ProductModel;
class ProductDelegate;

/**
 * @class ProductTableWidget
 * @brief Custom QWidget that displays and edits JSON data using a table view (MVC pattern).
 */
class ProductTableWidget : public QWidget
{
    Q_OBJECT

public:
    /**
     * @brief Constructor
     * @param parent Parent widget
     */
    explicit ProductTableWidget(QWidget* parent = nullptr);

    /**
     * @brief Destructor
     */
    ~ProductTableWidget() = default;

    /**
     * @brief Loads JSON data into the table model.
     * @param data JSON object to be displayed
     */
    void setData(const QJsonObject& data);

    /**
     * @brief Sets a custom model for the table view.
     * @param model Pointer to a ProductModel instance
     */
    void setModel(ProductModel* model);

    /**
     * @brief Retrieves the current JSON data from the model.
     * @return QJsonObject representing the current data
     */
    QJsonObject data() const;

private:
    /**
     * @brief Initializes the layout and view configuration.
     */
    void initialize();

    QTableView*      m_tableView = nullptr;    ///< Table view for displaying product data
    QVBoxLayout*     m_layout = nullptr;       ///< Main layout of the widget
    ProductModel*    m_model = nullptr;        ///< Model containing JSON data
    ProductDelegate* m_delegate = nullptr;     ///< Delegate for cell rendering/editing
    QJsonObject      m_jsonData;               ///< Holds the raw JSON object
};

#endif // PRODUCTTABLEWIDGET_H
