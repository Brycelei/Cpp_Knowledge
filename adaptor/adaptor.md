# 容器选择
- 除非有更好的选择，否则应使用`vector`
- 如果程序有很多小的元素，且空间的额外开销很重要，则不要使用`list`或者`forward_lsit`
- 如果程序要求支持随机访问元素，应使用`vector`或者`deque`
- 如果要求在容器的中间位置插入或删除元素，应使用`list`或`forward_lsit`
- 如果程序需要在头尾位置插入或者删除元素，且不会在中间位置进行插入和删除操作，应使用`deque`
- 如果程序只有在读取输入时候才需要在容器中间位置插入元素，随后需要随机访问元素，则
  * 处理数据，很容易在`vector`里添加元素，然后再调用sort方法来重新排容器中的元素，从而避免
    在中间位置插入元素。
  * 如果必须在中间插入元素，考虑在输入阶段使用`list`，一旦输入完成，将`list`中的内容拷贝到
    一个`vector`中。

# 顺序容器适配器
- stack
- queue
- priority_queue

# 所有容器适配器都支持的操作和类型
* size_type 一种类型，足以保存当前类型的最大对象的大小
* value_type 元素类型
* container_type 实现适配器的底层容器类型
* A a; 
* A a(c);
* 关系运算符
* a.empty()
* a.size()
* swap(a,b)
* a.swap(b)

- stack 除了array和forward_list之外的任何容器类型来构造stack。
  * 支持push_back(), pop_back(), back()
- queue适配器可构造于list或者deque之上，不能基于Vector构造。
  * 支持push_back(), front(), push_front()
- priority_queue除了front,push_back()和pop_back()操作外，还需要支持随机访问的能力
  因此它可以构造与vector或者deque之上，但不能基于list。