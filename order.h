//---------------------------------------------------------------------------

#ifndef orderH
#define orderH

#include <StdCtrls.hpp>
#include <vector.h> 
#include "product.h"
//---------------------------------------------------------------------------
class Order
{
        public:
                Order(String, String);
                void addProduct(Product*);
                String getCustomer();
        private:
                String numberOrder;
                String customer;
                vector <Product*> listItem;
};
#endif
