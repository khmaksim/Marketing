//---------------------------------------------------------------------------

#ifndef productH
#define productH

#include <StdCtrls.hpp>
//---------------------------------------------------------------------------
class Product
{
        public:
                Product(String, String, int, String, double);
                String getNameProduct();
        private:
                String nameProduct;
                String article;
                int count;
                String unit;
                double price;
};
#endif
