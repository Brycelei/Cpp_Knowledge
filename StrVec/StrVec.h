/***
 * 1. elements 指向分配内存的首元素
 * 2. first_free 指向最后一个实际元素之后的位置
 * 3. cap 指向分配内存末尾之后的位置

 ***/
#include <iostream>
#include <string>
#include <memory>
class StrVec
{
public:
    StrVec(/* args */) : // allocator 成员进行默认初始化
                         elements(nullptr), first_free(nullptr), cap(nullptr)
    {
    }
    StrVec::StrVec(StrVec &&s) noexcept
        : elements(s.elements), first_free(s.first_free), cap(s.cap)
    {
        s.elements = s.first_free = s.cap = nullptr;
    } // 移动构造函数

    StrVec &operator=(StrVec &&rhs) noexcept; // 移动赋值运算符

    StrVec(const StrVec &);            // 拷贝构造
    StrVec &operator=(const StrVec &); // 拷贝赋值运算符
    ~StrVec();
    void push_back(const std::string &);
    size_t size() const { return first_free - elements; }
    size_t capacity() const { return cap - elements; }
    std::string *begin() const { return elements; }
    std::string *end() const { return first_free; }

private:
    std::string *elements;
    std::string *first_free;
    std::string *cap;
    static std::allocator<std::string> alloc; //分配元素

    void chk_n_alloc() // 被添加元素的函数使用
    {
        if (size() == capacity())
        {
            reallocate();
        }
    }
    std::pair<std::string *, std::string *> alloc_n_copy(const std::string *, const std::string *);
    void reallocate(); //获取更多的内存并拷贝已有元素
    void free();       //销毁元素并释放内存
};
