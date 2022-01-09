#include "../base.hpp"

template<typename _Tp, typename _Sequence=vector<_Tp>, typename _Compare=less<typename _Sequence::value_type>>
struct my_priority_queue : priority_queue<_Tp, _Sequence, _Compare> {
    using my_priority_queue<_Tp, _Sequence, _Compare>::my_priority_queue;
    _Tp pop() {
        _Tp res = this->top();
        priority_queue<_Tp, _Sequence, _Compare>::pop();
        return res;
    }
};
