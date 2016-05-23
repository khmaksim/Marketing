//---------------------------------------------------------------------------

#ifndef listorderH
#define listorderH

#include <vector.h> 
#include "order.h"
//---------------------------------------------------------------------------
class ListOrder
{
        public:
                ListOrder();
                void addListOrder(Order);
                TStringList* getListCustomer();
        private:
                vector <Order> listOrder;
};
#endif
