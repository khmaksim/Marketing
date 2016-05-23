//---------------------------------------------------------------------------


#pragma hdrstop

#include "order.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)
//конструктор
Order::Order(String n, String c)
{
        numberOrder = n;
        customer = c;
}
//добавление продукта в заказ
void Order::addProduct(Product *item)
{
        listItem.push_back(item);
}
//возвращает имя заказчика
String Order::getCustomer()
{
        return customer;
}




