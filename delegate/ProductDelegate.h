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
    explicit ProductDelegate(QObject *in_p_parent = nullptr);

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
    QWidget* createEditor(QWidget *in_p_parent,
                          const QStyleOptionViewItem &in_option,
                          const QModelIndex &in_index) const override;

    /**
     * @brief Sets the editor's contents from the model data.
     * @param in_p_editor The editor widget.
     * @param in_index The model index to extract data from.
     */
    void setEditorData(QWidget *in_p_editor,
                       const QModelIndex &in_index) const override;

    /**
     * @brief Applies the editor's data to the model.
     * @param in_p_editor The editor widget.
     * @param in_p_model The target model to write to.
     * @param in_index The model index to update.
     */
    void setModelData(QWidget *in_p_editor,
                      QAbstractItemModel *in_p_model,
                      const QModelIndex &in_index) const override;

    /**
     * @brief Updates the editor's geometry to fit within the cell.
     * @param in_p_editor The editor widget.
     * @param in_option Style options.
     * @param in_index Model index.
     */
    void updateEditorGeometry(QWidget *in_p_editor,
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
};

#endif // PRODUCTDELEGATE_H
