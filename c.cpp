/* if you have mutiple construtors that have the same funtionality, use delegating construtors to
    avoid duplicate code
*/
#include <iostream>
using namespace std;
class class_c
{

public:
    int max;
    int min;
    int middle;
    class_c(int my_max)
    {
        max = my_max > 0 ? my_max : 10;
    }
    class_c(int my_max, int my_min) : class_c(my_max)
    {
        min = my_min > 0 && my_min < max ? my_min : 1;
    }
    class_c(int my_max, int my_min, int my_middle) : class_c(my_max, my_min)
    {
        middle = my_middle < max && my_middle > min ? my_middle : 5;
    }
};
int main()
{
    class_c c1{1, 3, 2};
    std::cout << c1.middle <<"\n"<<c1.max<<"\n"<<c1.min;
    return 0;
}
