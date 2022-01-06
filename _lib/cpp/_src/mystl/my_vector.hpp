#include "../base.hpp"

// ※なんかコンストラクタが言うこと聞かないので微妙。。
template<typename _Tp, typename _Alloc=std::allocator<_Tp>>
struct my_vector : public vector<_Tp, _Alloc> {
    _Tp pop() {
        auto res = this->back();
        this->pop_back();
        return res;
    }
};
#define vector my_vector
