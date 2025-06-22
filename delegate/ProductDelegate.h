#ifndef PRODUCTDELEGATE_H
#define PRODUCTDELEGATE_H

#include <QObject>
#include <QStyledItemDelegate>

/**
 * @class ProductDelegate
 * @brief Custom delegate for rendering and editing product table items.
 *
 * This delegate is responsible for providing specialized editors and rendering logic
 * for specific columns in the product table view, such as checkboxes for boolean values.
 */
class ProductDelegate : public QStyledItemDelegate
{
    Q_OBJECT

public:
    /**
     * @brief Constructor.
     * @param in_p_parent Parent object.
     */
    explicit ProductDelegate(QObject *in_parent = nullptr);

    /**
     * @brief Destructor.
     */
    ~ProductDelegate() = default;

    /**
     * @brief Creates an editor widget for the given model index.
     * @param in_p_parent Parent widget of the editor.
     * @param in_option Style options.
     * @param in_index Model index for which the editor is created.
     * @return Pointer to the created editor widget.
     */
    QWidget* createEditor(QWidget *in_parent,
                          const QStyleOptionViewItem &in_option,
                          const QModelIndex &in_index) const override;


    /**
     * @brief Provides the preferred size for a given cell.
     * @param in_option Style options.
     * @param in_index Model index.
     * @return Suggested size for rendering.
     */
    QSize sizeHint(const QStyleOptionViewItem &in_option,
                   const QModelIndex &in_index) const override;

    /**
     * @brief Renders the delegate's content (e.g., checkbox) for the specified cell.
     *
     * If the current index refers to a checkbox column (e.g., `ProductModel::Column::Value`),
     * a checkbox is drawn using the data stored in the first column (`ProductId`) as a JSON object.
     *
     * @param painter Painter used to render the delegate.
     * @param option Style options for the item, including rect and state.
     * @param index The model index for the item being painted.
     */
    void paint(QPainter *painter, const QStyleOptionViewItem &in_option, const QModelIndex &in_index) const override;

    /**
     * @brief Handles mouse events for the delegate (e.g., toggling checkboxes).
     *
     * For boolean values, this method toggles the checkbox state based on mouse click inside the cell.
     * The new state is passed to the model via `setData()` using the `EditRole`.
     *
     * @param event The event triggered (e.g., mouse release).
     * @param model The model associated with the view.
     * @param option The visual rectangle and state for the cell.
     * @param index The index being interacted with.
     * @return true if the event was handled and data updated; otherwise false.
     */
    bool editorEvent(QEvent *in_event, QAbstractItemModel *in_model, const QStyleOptionViewItem &in_option, const QModelIndex &in_index) override;
};

#endif // PRODUCTDELEGATE_H
