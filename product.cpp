//---------------------------------------------------------------------------


#pragma hdrstop

#include "product.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)
//конструктор
Product::Product(String name, String article, int count, String unit, double price)
{
        nameProduct = name;
        article = article;
        count = count;
        unit = unit;
        price = price;
}
//возвращает название продукции
String Product::getNameProduct()
{
        return nameProduct;
}
