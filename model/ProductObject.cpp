#include "ProductObject.h"
#include <QFile>
#include <QJsonDocument>
#include <QDebug>


ProductObject::ProductObject(QObject *parent) : QObject(parent)
{

}

bool ProductObject::load(const QString &in_filepath)
{
    QFile file(in_filepath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning() << "Failed to open file for reading:" << in_filepath;
        return false;
    }

    QByteArray file_contents = file.readAll();
    file.close();

    QJsonParseError parseError;
    QJsonDocument document = QJsonDocument::fromJson(file_contents, &parseError);
    if (parseError.error != QJsonParseError::NoError || !document.isObject()) {
        qWarning() << "Invalid JSON:" << parseError.errorString();
        return false;
    }

    m_product_configs = document.object();
    return true;
}

bool ProductObject::save(const QString &in_filepath) const
{
    QFile file(in_filepath);
    if(true == m_product_configs.empty())
    {
        qWarning() << "QJsonObject is empty";
        return false;
    }
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qWarning() << "Failed to open file for writing:" << in_filepath;
        return false;
    }

    QJsonDocument document(m_product_configs);
    file.write(document.toJson(QJsonDocument::Indented));
    file.close();
    qDebug() << "Save completed!";

    return true;
}



void ProductObject::setProductObject(QJsonObject &in_product_configs)
{
    m_product_configs = in_product_configs;
}

QJsonObject ProductObject::getProductObject() const
{
    return m_product_configs;
}

void ProductObject::clear()
{
    m_product_configs = QJsonObject();
}
