//---------------------------------------------------------------------------


#pragma hdrstop

#include "listorder.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)
//конструктор
ListOrder::ListOrder()
{

}
//добавление в список заказов
void ListOrder::addListOrder(Order order)
{
        listOrder.push_back(order);
}
//список заказчиков
TStringList* ListOrder::getListCustomer()
{
        TStringList *listCustomer = new TStringList;
        vector <Order>::iterator it;
        for(it = listOrder.begin(); it != listOrder.end(); ++it)
                listCustomer->Add(((Order*)it)->getCustomer());
        return listCustomer;
}