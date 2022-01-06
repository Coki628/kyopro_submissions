#include "../base.hpp"

template<typename _Tp, typename _Sequence=deque<_Tp>>
struct my_stack : public stack<_Tp, _Sequence> {
    _Tp pop() {
        auto res = this->top();
        stack<_Tp, _Sequence>::pop();
        return res;
    }
};
#define stack my_stack
