#include <iostream>
#include <utility>
int main()
{
    int &&r1 = 40;
    /// int &&r2 = r1; error
    int &&r3 = std::move(r1);
    // 调用move意味着对r1赋值或小辉外，我们将不再使用他，在调用move后，我们不能对移后源对象的值做任何假设。
    std::cout << r3 << std::endl;
    printf("%d\n", r1);
    return 0;
}