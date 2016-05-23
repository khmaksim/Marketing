//---------------------------------------------------------------------------

#ifndef listproductH
#define listproductH

#include <vector.h> 
#include "product.h"
//---------------------------------------------------------------------------
class ListProduct
{
        public:
                ListProduct();
                void addListProduct(Product);
                TStringList* getListNameProduct();
        private:
                vector <Product> listProduct;
};
#endif
