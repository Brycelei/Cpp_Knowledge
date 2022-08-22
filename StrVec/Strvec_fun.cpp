#include "StrVec.h"

void StrVec::push_back(const std::string &s)
{
    chk_n_alloc();                    // 确保有足够空间容纳新元素
    alloc.construct(first_free++, s); // 在first_free指向的元素中构造s的副本
}

std::pair<std::string *, std::string *> StrVec::alloc_n_copy(const std::string *b, const std::string *e)
{
    auto data = alloc.allocate(e - b);
    return {data, uninitialized_copy(b, e, data)}; // 从迭代器b和e指出的输入范围中拷贝元素到迭代器data指定未构造的原始内存中，
    // b2指向的内存必须足够大，能够容纳输入序列中元素的拷贝
    //其返回值为指向最后一个构造元素之后的位置
}

/*
    首先destroy元素，然后释放StrVec自己分配的内存空间，for循环调用allocator的destroy成员。逆序销毁所有元素
*/
void StrVec::free()
{
    if (elements) //不能传递给dellocate空指针，如果element为0，函数什么也不做
    {
        for (auto p = first_free; p != elements; alloc.destroy(--p))
        {
            alloc.deallocate(elements, cap - elements);
        }
        //一旦元素销毁，就调用dellocate来释放本StrVec对象分配的内存空间
        // 传递给dellocate的指针必须是之前某次allocate调用返回的指针，所以需要检查elements是否为空
    }
}

StrVec::StrVec(const StrVec &s)
{
    auto newdata = alloc_n_copy(s.begin(), s.end());
    elements = newdata.first;
    first_free = cap = newdata.second;
}

StrVec::~StrVec()
{
    free();
}

StrVec &StrVec::operator=(const StrVec &rhs)
{
    auto newdata = alloc_n_copy(rhs.begin(), rhs.end());
    free();
    elements = newdata.first;
    first_free = cap = newdata.second;
    return *this;
}

void StrVec::reallocate()
{
    auto newcapacity = size() ? 2 * size() : 1;
    auto newdata = alloc.allocate(newcapacity);
    auto dest = newdata;
    auto elem = elements;
    for (size_t i = 0; i != size(); i++)
    {
        alloc.construct(dest++, std::move(*elem++));
    }
    free();
    elements = newdata;
    first_free = dest;
    cap = elements + newcapacity;
}

StrVec &StrVec::operator=(StrVec &&rhs) noexcept
{
    if (this != &rhs)
    {
        free();
        elements = rhs.elements;
        first_free = rhs.first_free;
        cap = rhs.cap;
        rhs.elements = rhs.first_free = rhs.cap = nullptr;
    }
    return *this;
}
