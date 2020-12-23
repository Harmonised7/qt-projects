#ifndef ITEMINFO_H
#define ITEMINFO_H

#include <QString>
#include <QMap>

// Json includes
#include <nlohmann/json.hpp>
using json = nlohmann::json;

struct PrimitiveItem
{
    int id;
    bool members;
    int suggested_price;
    int buy_quantity;
    int sell_quantity;
    int buy_average;
    int sell_average;
    int overall_average;
    int overall_quantity;
};

class Item
{
public:
    Item(PrimitiveItem &primitiveItem);

private:
    PrimitiveItem _pItem;
};

#endif // ITEMINFO_H
