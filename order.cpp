//---------------------------------------------------------------------------


#pragma hdrstop

#include "order.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)
//�����������
Order::Order(String n, String c)
{
        numberOrder = n;
        customer = c;
}
//���������� �������� � �����
void Order::addProduct(Product *item)
{
        listItem.push_back(item);
}
//���������� ��� ���������
String Order::getCustomer()
{
        return customer;
}




