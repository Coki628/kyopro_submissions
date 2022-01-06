#include "../base.hpp"

template<typename _Tp, typename _Sequence=vector<_Tp>, typename _Compare=less<typename _Sequence::value_type>>
struct my_priority_queue : public priority_queue<_Tp, _Sequence, _Compare> {
    _Tp pop() {
        auto res = this->top();
        priority_queue<_Tp, _Sequence, _Compare>::pop();
        return res;
    }
};
#define priority_queue my_priority_queue
