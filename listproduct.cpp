//---------------------------------------------------------------------------


#pragma hdrstop
#include "listproduct.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)
//�����������
ListProduct::ListProduct()
{

}
//���������� � ������ ���������
void ListProduct::addListProduct(Product item)
{
        listProduct.push_back(item);
}
//������ �������� ���������
TStringList* ListProduct::getListNameProduct()
{
        TStringList *listNameProduct = new TStringList;
        vector <Product>::iterator it;
        for(it = listProduct.begin(); it != listProduct.end(); ++it)
                listNameProduct->Add(((Product*)it)->getNameProduct());
        return listNameProduct;
}