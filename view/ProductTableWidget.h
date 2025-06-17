#ifndef PRODUCTTABLEWIDGET_H
#define PRODUCTTABLEWIDGET_H

//////////////////////////////////////////////////////////////////////////
/// includes
//////////////////////////////////////////////////////////////////////////
#include <QWidget>
#include <QJsonObject>
//////////////////////////////////////////////////////////////////////////
/// forward declarations
/////////////////////////////////////////////////////////////////////////////
class ProductModel;
class QTableView;
class ProductDelegate;
class QVBoxLayout;

//////////////////////////////////////////////////////////////////////////
///
/// \brief      A custom widget includes a table widget and its models
///
//////////////////////////////////////////////////////////////////////////
class ProductTableWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ProductTableWidget     (QWidget *in_p_parent = nullptr);
    ~ProductTableWidget             ();
    void        initialize          ();
    void        setData             (QJsonObject in_data);
    void        setModel            (ProductModel *in_p_model);
    QJsonObject data                ();

signals:

private:
    QTableView*                     m_p_table       = nullptr;  ///<    Table view (model based)
    QJsonObject                     m_project_json_object;
    ProductModel*                   m_p_model       = nullptr;  ///<    model/view
    ProductDelegate*                m_p_delegate    = nullptr;  ///<    delegate in model/view
    QVBoxLayout*                    m_p_vlayout     = nullptr;  ///<    layout for tablewidget
};

#endif // PRODUCTTABLEWIDGET_H
