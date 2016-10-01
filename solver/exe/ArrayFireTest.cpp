#include <arrayfire.h>

int main()
{
    af::info();

    af::array a = af::randu(4, 4);
    af::array b = af::randu(4, 4);

    af::array c = a + b;

    af_print(a);
    af_print(b);
    af_print(c);

    return 0;
}
