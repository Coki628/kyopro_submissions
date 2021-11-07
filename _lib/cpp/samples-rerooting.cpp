/*
・ライブラリ：全方位木DPサンプル
*/

#include "_tpl.cpp"


// ・だいたいf2で済ませて、f1は演算だけくらいのがうまくいきそう。
// ・辺の遷移で値を操作する。単位元は自由に設定できるDPの初期値と異なり、
// 　本当に演算の単位元だと思った方がいい。+演算のやつで初期値1とかやるとバグる。
// ・根側の状態が遷移に絡むようなものも、f1でうまくやればできるようだ。(ABC160f)
// ・頂点属性は、葉側の頂点の属性を辺属性として割り当てる。(joisc2008day1-1,cf1324f)

// aoj1595_uapc2016
ll f1(ll a, ll b) {
    return max(a, b);
}
ll f2(ll a, ll x) {
    return a+1;
}
// chmax(dp[u], dp[v]+1);

// GRL_5_A,ABC222_f
// dp[i] := 頂点iを根とした部分木の各頂点への距離の最大値と2番目
vector<ll> tmp(4);
auto f1 = [](pll a, pll b) -> pll {
    tmp[0] = a.first;
    tmp[1] = a.second;
    tmp[2] = b.first;
    tmp[3] = b.second;
    sort(ALL(tmp));
    return mkp(tmp[3], tmp[2]);
};
auto f2 = [](pll a, ll c) -> pll {
    return mkp(a.first+c, 0);
};

// GRL_5_B,ABC222_f
// dp[i] := 頂点iを根とした部分木の各頂点への距離の最大値
auto f1 = [](ll a, ll b) {
    return max(a, b);
};
auto f2 = [](ll a, ll c) {
    return a+c;
};
// chmax(dp[u], dp[v]+c);

// ABC149f
// ・pow(2, a.sz+1, MOD)-1部分をどちらに置いてもできる。
auto f1 = [](Node a, Node b) -> Node {
    return {a.sz+b.sz, a.cnt+b.cnt};
};
auto f2 = [](Node a, ll x) -> Node {
    return {a.sz+1, pow(2, a.sz+1, MOD)-1};
};
// これでもOK
auto f1 = [](Node a, Node b) -> Node {
    return {a.sz+b.sz, a.cnt+pow(2, b.sz, MOD)-1};
};
auto f2 = [](Node a, ll x) -> Node {
    return {a.sz+1, a.sz};
};
// sz[u] += sz[v]+1;
// dp[u] += pow(2, sz[v]+1, MOD)-1;

// ABC160f
// ・遷移先uの状態が絡むような遷移でもできる。
pll f1(pll a, pll b) {
    return mkp(a.first * b.first % MOD * mt.nCr(a.second + b.second, a.second) % MOD, a.second + b.second);
}

pll f2(pll a, ll v) {
    return mkp(a.first, a.second + 1);
}
// dp[u].first *= dp[v].first * mt.nCr(dp[u].second + dp[v].second + 1, dp[v].second + 1);
// dp[u].second += dp[v].second + 1;

// ABC201_e
auto f1 = [](Node a, Node b) -> Node {
    a.zero += b.zero;
    a.one += b.one;
    return a;
};
auto f2 = [](Node a, ll c) -> Node {
    a.zero += 1;
    if (c) swap(a.zero, a.one);
    return a;
};
// if (c) {
//     zero[u] += one[v];
//     one[u] += zero[v]+1;
// } else {
//     zero[u] += zero[v]+1;
//     one[u] += one[v];
// }

// edpc_p
pll f1(pll a, pll b) {
    return mkp(a.first * b.first % MOD, a.second * b.second % MOD);
}
pll f2(pll a, ll x) {
    return mkp((a.first + a.second) % MOD, a.first);
}
// dp[u].first *= dp[v].first + dp[v].second;
// dp[u].second *= dp[v].first;
// dp[u].first %= MOD;
// dp[u].second %= MOD;

// edpc_v
ll f1(ll a, ll b) {
    return a * b % M;
}
ll f2(ll a, ll v) {
    return (a + 1) % M;
}
// dp[u] *= dp[v] + 1;
// dp[u] %= M;

// joisc2008day1-1
// ・頂点属性。葉側の頂点の属性を辺属性として割り当てる。
// rr.add_edge_bi(par, i, V[i], V[par]);
ll f1(ll a, ll b) {
    return a + b;
}
// 頂点xとその先を取り込む or この先は使わない
ll f2(ll a, ll x) {
    return max(a + x, 0LL);
}
// DP遷移は書いてなかったけど多分こう
// dp[u] += max(dp[v]+val[v], 0LL);

// typical90_039,ABC220_f
// dp[i] := 頂点iを根とした部分木の全頂点への距離の総和
struct Node {
    ll sz, sm;
};
auto f1 = [](Node a, Node b) -> Node {
    a.sz += b.sz;
    a.sm += b.sm;
    return a;
};
auto f2 = [](Node a, ll v) -> Node {
    a.sz++;
    a.sm += a.sz;
    return a;
};
// sz[u] += sz[v]+1;
// sm[u] += sm[v]+sz[v]+1;

// cf1324f
// ・頂点属性。ここでは頂点番号を渡して、関数側でリストを読んでた。これでもいい。
// rr.add_edge_bi(a, b, b, a);
ll f1(ll a, ll b) {
    return a + b;
}
ll f2(ll a, ll v) {
    if (A[v]) {
        return ++a;
    } else {
        return max(--a, 0LL);
    }
}
// DP遷移は多分こう
// if (A[v]) {
//     dp[u] += dp[v]+1;
// } else [
//     dp[u] += max(dp[v]-1, 0LL);
// ]

// yukico872
pll f1(pll a, pll b) {
    return mkp(a.first + b.first, a.second + b.second);
}
pll f2(pll a, ll x) {
    return mkp(a.first+1, a.second + (a.first+1)*x);
}
// dp[u].first += dp[v].first + 1;
// dp[u].second += dp[v].second + (dp[v].first+1)*x;

// cf1593_e
// ・これ、遠い方は距離の最大値でやったことあったけど、近い方はちょっと工夫が必要だった。
// 　詳細は該当の問題を参照。
// dp[i] := 頂点iを根とした部分木の根から一番近い葉への距離
auto f1 = [](ll a, ll b) {
    return min(a, b);
};
auto f2 = [](ll a, bool is_leaf) -> ll {
    if (is_leaf) return 1;
    else return a+1;
};
// chmin(dp[u], is_leaf[v] ? 1 : dp[v]+1);
