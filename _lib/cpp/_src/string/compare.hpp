#include "../macros.hpp"
#include "zfill.hpp"

// 文字列を数値として大小比較する
bool compare(const string &a, const string &b) {
    if (a == "*") return true;
    int n = max(a.size(), b.size());
    return zfill(a, n) < zfill(b, n);
}
