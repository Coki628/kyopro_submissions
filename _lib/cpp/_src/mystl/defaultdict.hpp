#include "../base.hpp"

// 標準mapを継承したdefaultdict
template<typename _Key, typename _Tp, typename _Compare=less<_Key>, typename _Alloc=allocator<pair<const _Key, _Tp>>>
struct defaultdict : public map<_Key, _Tp, _Compare, _Alloc> {

    const _Tp init;

    defaultdict() : init(_Tp()) {};

    defaultdict(_Tp init) : init(init) {}

    _Tp& operator[](const _Key& k) {
        if (this->count(k)) {
            return map<_Key, _Tp, _Compare, _Alloc>::operator[](k);
        } else {
            return map<_Key, _Tp, _Compare, _Alloc>::operator[](k) = init;
        }
    }

    _Tp& operator[](_Key&& k) {
        if (this->count(k)) {
            return map<_Key, _Tp, _Compare, _Alloc>::operator[](k);
        } else {
            return map<_Key, _Tp, _Compare, _Alloc>::operator[](k) = init;
        }
    }
};
