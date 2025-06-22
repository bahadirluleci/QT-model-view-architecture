//////////////////////////////////////////////////////////////////////////
/// \file ProductItem.cpp
/// \brief Implementation of ProductItem class
//////////////////////////////////////////////////////////////////////////

#include "ProductItem.h"

#include <QJsonObject>
#include <QJsonArray>
#include <QDebug>

ProductItem::ProductItem(int in_role, QVariant in_value)
    : QStandardItem(), m_role(in_role), m_value(std::move(in_value)) {}

int ProductItem::role() const {
    return m_role;
}

void ProductItem::setData(const QVariant &in_value, int32_t in_role) {
    if (in_role == Qt::EditRole) {
        m_value = in_value;
    }
}

QVariant ProductItem::data(int32_t in_role) const {
    if (in_role == Qt::DisplayRole || in_role == Qt::EditRole || in_role == Roles::Data) {
        return m_value;
    }
    return {};
}

void ProductItem::setValue(bool in_value) {
    QJsonValue available_value = QJsonValue::fromVariant(m_value);
    QString json_path = "product.available";
    QJsonValue new_value(in_value);
    modifyJsonValue(available_value, json_path, new_value);
    m_value = QVariant(available_value);
}


//////////////////////////////////////////////////////////////////////////
///
/// \brief      changes old json value in desired json path with new value
/// \param[in]  in_dest_value   ... destination Json value requesting modify or remove of its own value in it based on path in object tree
/// \param[in]  in_path         ... desired json data path
/// \param[in]  in_new_value    ... new Json value
/// \details    usage of this function
///             //modify or add value
///             modifyJsonValue(destinationJsonValue, "attribute1", QJsonValue("related_value"));
///             modifyJsonValue(destinationJsonValue, "attribute1[0][2]", "Disel");
///             modifyJsonValue(destinationJsonValue, "part1.part2.part3.value[2].d", 56);
///             //remove value
///             modifyJsonValue(doc, "attribute1[1][2]");
/// \return     void
///
//////////////////////////////////////////////////////////////////////////
void ProductItem::modifyJsonValue(QJsonValue &in_destination_value, const QString &in_path, const QJsonValue &in_new_value)
{
    const int index_of_dot = in_path.indexOf('.');
    const QString dot_property_name = in_path.left(index_of_dot);
    const QString dot_sub_path = index_of_dot > 0 ? in_path.mid(index_of_dot + 1) : QString();

    const int index_of_square_bracket_open = in_path.indexOf('[');
    const int index_of_square_bracket_close = in_path.indexOf(']');

    const int array_index = QStringView{in_path}.mid(index_of_square_bracket_open + 1,
                                                     index_of_square_bracket_close - index_of_square_bracket_open - 1)
                                .toInt();
    const QString square_bracket_property_name = in_path.left(index_of_square_bracket_open);
    const QString square_bracket_sub_path = index_of_square_bracket_close > 0 ? (in_path.mid(index_of_square_bracket_close + 1)[0] == '.' ? in_path.mid(index_of_square_bracket_close + 2) : in_path.mid(index_of_square_bracket_close + 1)) : QString();

    bool usage_of_dot_in_path = true;
    if (index_of_dot >= 0)
    {
        if (index_of_square_bracket_open >= 0)
        {
            if (index_of_dot > index_of_square_bracket_open)
                usage_of_dot_in_path = false;
            else
                usage_of_dot_in_path = true;
        }
        else
            usage_of_dot_in_path = true;
    }
    else
    {
        if (index_of_square_bracket_open >= 0)
            usage_of_dot_in_path = false;
        else
            usage_of_dot_in_path = true;
    }

    QString used_property_name = usage_of_dot_in_path ? dot_property_name : square_bracket_property_name;
    QString used_sub_path = usage_of_dot_in_path ? dot_sub_path : square_bracket_sub_path;

    QJsonValue sub_value;
    if (in_destination_value.isArray())
        sub_value = in_destination_value.toArray()[used_property_name.toInt()];
    else if (in_destination_value.isObject())
        sub_value = in_destination_value.toObject()[used_property_name];
    else
        qDebug() << "Destination value type is wrong! " << in_destination_value;

    if(used_sub_path.isEmpty())
    {
        sub_value = in_new_value;
    }
    else
    {
        if (sub_value.isArray())
        {
            QJsonArray json_array = sub_value.toArray();
            QJsonValue entry_value_of_array = json_array[array_index];
            modifyJsonValue(entry_value_of_array,used_sub_path,in_new_value);
            json_array[array_index] = entry_value_of_array;
            sub_value = json_array;
        }
        else if (sub_value.isObject())
            modifyJsonValue(sub_value,used_sub_path,in_new_value);
        else
            sub_value = in_new_value;
    }

    if (in_destination_value.isArray())
    {
        QJsonArray destination_json_array = in_destination_value.toArray();
        if (sub_value.isNull())
            destination_json_array.removeAt(array_index);
        else
            destination_json_array[array_index] = sub_value;
        in_destination_value = destination_json_array;
    }
    else if (in_destination_value.isObject())
    {
        QJsonObject destination_json_object = in_destination_value.toObject();
        if (sub_value.isNull())
            destination_json_object.remove(used_property_name);
        else
            destination_json_object[used_property_name] = sub_value;
        in_destination_value = destination_json_object;
    }
    else
        in_destination_value = in_new_value;
}


/*namespace {

struct PathToken {
    QString key;
    std::optional<int> arrayIndex;
};

// Parses "a[0].b[2].c" into PathTokens
QVector<PathToken> parsePath(const QString& path) {
    QVector<PathToken> tokens;
    QString current;
    for (int i = 0; i < path.size(); ++i) {
        if (path[i] == '.' || path[i] == '[') {
            if (!current.isEmpty()) {
                tokens.push_back({ current, std::nullopt });
                current.clear();
            }

            if (path[i] == '[') {
                int close = path.indexOf(']', i);
                if (close > i + 1) {
                    int index = path.mid(i + 1, close - i - 1).toInt();
                    tokens.last().arrayIndex = index;
                    i = close;
                }
            }
        } else {
            current += path[i];
        }
    }

    if (!current.isEmpty())
        tokens.push_back({ current, std::nullopt });

    return tokens;
}

// Navigates to the JsonValue pointer based on path tokens
QJsonValue* navigate(QJsonValue& value, const QVector<PathToken>& tokens, int depth = 0) {
    if (depth >= tokens.size())
        return &value;

    const auto& token = tokens[depth];

    if (value.isObject()) {
        QJsonObject obj = value.toObject();
        QJsonValue child = obj.value(token.key);

        QJsonValue* result = navigate(child, tokens, depth + 1);

        // Reinsert modified value
        obj[token.key] = child;
        value = obj;
        return result;
    } else if (value.isArray() && token.arrayIndex.has_value()) {
        QJsonArray arr = value.toArray();
        int idx = token.arrayIndex.value();

        if (idx < 0 || idx >= arr.size())
            return nullptr;

        QJsonValue child = arr[idx];
        QJsonValue* result = navigate(child, tokens, depth + 1);
        arr[idx] = child;
        value = arr;
        return result;
    }

    return nullptr;
}

} // namespace

/// Modify a JSON value at the given path
void ProductItem::modifyJsonValue(QJsonValue& root, const QString& path, const QJsonValue& newValue) {
    QVector<PathToken> tokens = parsePath(path);
    QJsonValue* target = navigate(root, tokens);
    if (target)
        *target = newValue;
}*/
