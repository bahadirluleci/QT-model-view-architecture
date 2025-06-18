#include "ProductTableWidget.h"

#include <QVBoxLayout>
#include <QTableView>
#include <QHeaderView>
#include <QJsonObject>

#include "ProductModel.h"
#include "ProductDelegate.h"

ProductTableWidget::ProductTableWidget(QWidget* parent)
    : QWidget(parent),
    m_layout(new QVBoxLayout(this)),
    m_tableView(new QTableView(this)),
    m_model(new ProductModel(this)),
    m_delegate(new ProductDelegate(this))
{
    initialize();
}

void ProductTableWidget::initialize()
{
    if (!m_tableView || !m_layout)
        return;

    m_layout->addWidget(m_tableView);
    m_layout->setContentsMargins(0, 0, 0, 0);
    m_layout->setSpacing(1);
    setLayout(m_layout);

    m_tableView->setAutoFillBackground(true);
    m_tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    m_tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    m_tableView->setSortingEnabled(false);
    m_tableView->resizeColumnsToContents();
    m_tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
}

void ProductTableWidget::setData(const QJsonObject& data)
{
    if (!m_model)
        return;

    m_model->clear();
    m_jsonData = data;
    m_model->setJson(m_jsonData);
    setModel(m_model);

    for (int i = 0; i < m_model->rowCount(); ++i)
    {
        QModelIndex index = m_model->index(i, ProductModel::Value, QModelIndex());
        m_tableView->openPersistentEditor(index);
    }
}

void ProductTableWidget::setModel(ProductModel* model)
{
    if (!m_tableView || !model)
        return;

    m_model = model;
    m_tableView->setModel(m_model);
    m_tableView->setItemDelegateForColumn(ProductModel::Column::Value, m_delegate);
}

QJsonObject ProductTableWidget::data() const
{
    if (m_model)
        return m_model->jsonData();

    return QJsonObject();
}
