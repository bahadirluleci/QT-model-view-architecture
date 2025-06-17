#include "ProductObject.h"
#include <QFile>
#include <QJsonDocument>
#include <QDebug>


//////////////////////////////////////////////////////////////////////////
///
/// \brief  Constructor
///
//////////////////////////////////////////////////////////////////////////
ProductObject::ProductObject(QObject *parent) : QObject(parent)
{

}

//////////////////////////////////////////////////////////////////////////
///
/// \brief      load json-file containing product or product-config file
/// \param[in]  in_filepath ... path to the json-file for loading
/// \return     void
///
//////////////////////////////////////////////////////////////////////////
void ProductObject::load(const QString &in_filepath)
{
    QFile file(in_filepath);
    if(false == file.open((QIODevice::ReadOnly | QIODevice::Text)))
    {
         qWarning() << "File open error!";
         return;;
    }
    QString file_contents = file.readAll();
    file.close();
    QJsonDocument document = QJsonDocument::fromJson(file_contents.toUtf8());
    m_product_configs = document.object();
}


//////////////////////////////////////////////////////////////////////////
///
/// \brief      save containing product or product-config file to json-file
/// \param[in]  in_filepath ... path to the json-file for saving
/// \return     void
///
//////////////////////////////////////////////////////////////////////////
void ProductObject::save(const QString &in_filepath)
{
    QFile file(in_filepath);
    if(true == m_product_configs.empty())
    {
        qWarning() << "QJsonObject is empty";
        return;
    }
    QJsonDocument document(m_product_configs);
    if(false == file.open(QIODevice::WriteOnly))
    {
        qWarning() << "File can not open";
        return;
    }
    file.write(document.toJson());
    file.close();
    qDebug() << "Save completed!";
}


//////////////////////////////////////////////////////////////////////////
///
/// \brief      set product-config file
/// \param[in]  in_product_configs ... the product as QJsonObject
/// \return     void
///
//////////////////////////////////////////////////////////////////////////
void ProductObject::setProductObject(QJsonObject &in_product_configs)
{
    m_product_configs = in_product_configs;
}

//////////////////////////////////////////////////////////////////////////
///
/// \brief      get product-config file
/// \return     QJsonObject
///
//////////////////////////////////////////////////////////////////////////
QJsonObject ProductObject::getProductObject() const
{
    return m_product_configs;
}
