/*
・ライブラリ：ダブリングサンプル
*/

#include "macros.hpp"


// 一番基本の位置だけ(ABC212_f,ARC060_e,ABC258_e,他多数)
auto f = [](int prev, int power) {
    return power;
};

// 位置とそこまでの和(ABC175d,他多数)
struct Node {
    ll nxt, sm;
    operator ll() const { return nxt; }
};
auto f = [](const Node &prev, const Node &power) {
    Node res;
    res.nxt = power.nxt;
    res.sm = prev.sm + power.sm;
    return res;
};

// 位置と和と、そこまでの最大値(ABC175d)
struct Node {
    ll nxt, sm, mx;
    operator ll() const { return nxt; }
};
auto f = [](const Node &prev, const Node &power) {
    Node res;
    res.nxt = power.nxt;
    res.sm = prev.sm + power.sm;
    res.mx = max(prev.mx, prev.sm + power.mx);
    return res;
};

// 遷移元が違うのでこれはライブラリ側をいじらないと無理そう(AGC036b)
// nxt[k][i] = nxt[k-1][i] + nxt[k-1][(i+nxt[k-1][i])%N]

// 位置とじゃんけんの勝者(ARC109c)
struct Node {
    ll nxt;
    char c;
    operator ll() const { return nxt; }
};
auto f = [](const Node &prev, const Node &power) {
    Node res;
    res.nxt = power.nxt;
    res.c = check(prev.c, power.c);
    return res;
};
