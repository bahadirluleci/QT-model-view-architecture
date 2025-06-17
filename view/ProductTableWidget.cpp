//////////////////////////////////////////////////////////////////////////
//includes
//////////////////////////////////////////////////////////////////////////
#include "ProductTableWidget.h"
#include <QVBoxLayout>
#include <QTableView>
#include <QHeaderView>
#include "ProductModel.h"
#include "ProductDelegate.h"

//////////////////////////////////////////////////////////////////////////
///
/// \brief  Constructor
///
//////////////////////////////////////////////////////////////////////////
ProductTableWidget::ProductTableWidget(QWidget *in_p_parent) : QWidget(in_p_parent)
{
    m_p_vlayout     = new QVBoxLayout(this);
    m_p_table       = new QTableView(this);
    m_p_model       = new ProductModel(this);
    m_p_delegate    = new ProductDelegate(this);

    initialize();
}
//////////////////////////////////////////////////////////////////////////
///
/// \brief  Destructor
///
//////////////////////////////////////////////////////////////////////////
ProductTableWidget::~ProductTableWidget()
{

}
//////////////////////////////////////////////////////////////////////////
///
/// \brief      initialize
/// \return     void
///
//////////////////////////////////////////////////////////////////////////
void ProductTableWidget::initialize()
{
    if (nullptr == m_p_table || nullptr == m_p_vlayout)
        return;

    m_p_vlayout->addWidget(m_p_table);
    m_p_vlayout->setContentsMargins(0, 0, 0, 0);
    m_p_vlayout->setSpacing(1);
    setLayout(m_p_vlayout);

    m_p_table->setAutoFillBackground(true);
    m_p_table->setSelectionBehavior(QAbstractItemView::SelectRows);
    m_p_table->setSelectionMode(QAbstractItemView::SingleSelection);
    m_p_table->setSortingEnabled(false);
    m_p_table->resizeColumnsToContents();
    m_p_table->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
}
//////////////////////////////////////////////////////////////////////////
///
/// \brief      set the json data, update models, and show data on table view
/// \param[out] in_data ... QJSonObject config
/// \return     void
///
//////////////////////////////////////////////////////////////////////////
void ProductTableWidget::setData(QJsonObject in_data)
{
    if(m_p_model == nullptr)
        return;
    m_p_model->clear();
    m_project_json_object = in_data;
    m_p_model->setJson(m_project_json_object);
    setModel(m_p_model);
    for (int i=0; i<m_p_model->rowCount(); i++)
    {
        QModelIndex index = m_p_model->index(i,ProductModel::Value, QModelIndex());
        m_p_table->openPersistentEditor(index);
    }
}

//////////////////////////////////////////////////////////////////////////
///
/// \brief      sets model of table
/// \param[out] in_p_model ... releted model
/// \return     void
///
//////////////////////////////////////////////////////////////////////////
void ProductTableWidget::setModel(ProductModel *in_p_model)
{
    if(nullptr == m_p_table || nullptr == m_p_model)
        return;
    m_p_model = in_p_model;
    m_p_table->setModel(m_p_model);
    m_p_table->setItemDelegateForColumn(ProductModel::Column::Value, m_p_delegate);
}


//////////////////////////////////////////////////////////////////////////
///
/// \brief      Return jsonData used by Table Widgets model
/// \return     QJsonObject
///
//////////////////////////////////////////////////////////////////////////
QJsonObject ProductTableWidget::data()
{
    if( nullptr != m_p_model)
        return m_p_model->jsonData();
    return QJsonObject();
}
