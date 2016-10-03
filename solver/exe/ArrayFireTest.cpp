#include <arrayfire.h>

int main()
{
    af::info();

    float aa[] = {0.0f, 1.0f, 2.0f, 3.0f};
    float ab[] = {4.0f, 5.0f, 6.0f, 7.0f};

    af::array a(2, 2, aa);
    af::array b(2, 2, ab);
	std::cout << a.host<float>()[2] << std::endl;;

    af::array c = af::matmul(a, b);

    af_print(a);
    af_print(b);
    af_print(c);

    return 0;
}
