//---------------------------------------------------------------------------


#pragma hdrstop

#include "listorder.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)
//�����������
ListOrder::ListOrder()
{

}
//���������� � ������ �������
void ListOrder::addListOrder(Order order)
{
        listOrder.push_back(order);
}
//������ ����������
TStringList* ListOrder::getListCustomer()
{
        TStringList *listCustomer = new TStringList;
        vector <Order>::iterator it;
        for(it = listOrder.begin(); it != listOrder.end(); ++it)
                listCustomer->Add(((Order*)it)->getCustomer());
        return listCustomer;
}