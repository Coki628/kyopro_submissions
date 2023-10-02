/*
・セグ木に乗せる各種素材置き場
*/

#include "macros.hpp"


///// 一般セグ木用の各種素材(変わり種だけ) /////
// 区間合成関数取得
struct Node {
    ld a = 1, b = 0;
    operator ld() const { return a+b; }
};
auto f = [](Node f1, Node f2) -> Node {
    return { f1.a*f2.a, f1.b*f2.a + f2.b };
};
const Node T = {1, 0};
// 1次関数(ax+b)同士の合成関数
// f2(f1(x))
// c*f1(x) + d
// c*(ax+b) + d
// c*ax + c*b + d
// {c*a, c*b + d}

// +-が交互になる(連続しなくていい)部分列の最大値取得
// 参考：cf1420c2
struct Node {
    // ++, +-, -+, --
    ll pp, pm, mp, mm;
    operator ll() const { return max({pp, pm, mp, mm}); }
};
auto f = [](Node a, Node b) -> Node {
    Node res;
    // + xxx +
    res.pp = max(a.pp + b.pp, a.pm + b.mp);
    // + xxx -
    res.pm = max(a.pp + b.pm, a.pm + b.mm);
    // - xxx +
    res.mp = max(a.mp + b.pp, a.mm + b.mp);
    // - xxx -
    res.mm = max(a.mp + b.pm, a.mm + b.mm);
    return res;
};
const Node T = {0, 0, 0, 0};

// 区間行列積取得(これは4*4)
// 参考：cf_edu_seg1_4b, abc_256_f, cf1743F
struct Node {
    // 2次元arrayの初期化は{}をひとつ多く括る
    array<array<mint, 4>, 4> mat{{
        {1, 0, 0, 0},
        {0, 1, 0, 0},
        {0, 0, 1, 0},
        {0, 0, 0, 1},
    }};
    Node(const array<array<mint, 4>, 4> &mat) : mat(mat) {};
    Node() {}
};
auto f = [](const Node &a, const Node &b) -> Node {
    // マージ方向をb,aにする
    return mat_dot(b.mat, a.mat);
};
const Node T = Node();

// 区間転倒数取得(40以下の値)
// 参考：cf_edu_seg1_4c
struct Node {
    // その区間が持つ各値の個数
    array<int, 41> C{};
    // 転倒数
    ll inv = 0;

    Node(array<int, 41> &C, ll inv) : C(C), inv(inv) {};

    Node(array<int, 41> &C) : C(C) {};

    Node() {};

    operator ll() const { return inv; }
};
auto f = [](Node &a, Node &b) -> Node {
    array<int, 41> C{}, acc{};
    // 個数のマージと累積和
    rep(i, 1, 41) {
        C[i] = a.C[i]+b.C[i];
        acc[i] = acc[i-1]+b.C[i];
    }
    // 両方の転倒数を足してから、マージした時増える転倒数を数える
    ll inv = a.inv+b.inv;
    rep(i, 2, 41) {
        // bでi-1以下の数と、aの各値iがペアを組める
        inv += acc[i-1]*a.C[i];
    }
    return Node(C, inv);
};
const Node T = Node();

// 区間の異なる数の個数を取得(40以下の値)
// 参考：cf_edu_seg1_4d
struct Node {
    // どの値を持っているかの集合
    array<bool, 41> C{};
    // その区間が持つ重複した数
    ll cnt = 0;

    Node(array<bool, 41> &C, ll cnt) : C(C), cnt(cnt) {};

    Node(array<bool, 41> &C) : C(C) {};

    Node() {};

    operator ll() const { return cnt; }
};
auto f = [](Node &a, Node &b) -> Node {
    array<bool, 41> C{};
    ll cnt = a.cnt+b.cnt;
    rep(i, 1, 41) {
        // 両方の区間が持つ値があったら、重複数を増やす
        if(a.C[i] & b.C[i]) {
            cnt++;
        }
        C[i] = a.C[i] | b.C[i];
    }
    return Node(C, cnt);
};
const Node T = Node();

// XOR基底(abc223_h)
auto f = [](xorbasis a, xorbasis b) { return a.merge(b); };
const xorbasis T;


///// 遅延セグ木用の各種素材 /////
// 区間更新・区間最小値取得
auto f = [](ll a, ll b) -> ll { return min(a, b); };
auto g = [](ll a, ll b) -> ll { return b; };
auto h = [](ll a, ll b) -> ll { return b; };
const ll T = INF;
// 要素が取りうる範囲外の値にする
const ll E = -1;

// 区間更新・区間最大値取得
auto f = [](ll a, ll b) -> ll { return max(a, b); };
auto g = [](ll a, ll b) -> ll { return b; };
auto h = [](ll a, ll b) -> ll { return b; };
const ll T = 0;
// 要素が取りうる範囲外の値にする
const ll E = INF;

// 区間加算・区間和取得
struct Node {
    ll val, sz;
    operator ll() const { return val; }
};
auto f = [](Node a, Node b) -> Node { return { a.val+b.val, a.sz+b.sz }; };
auto g = [](Node a, ll b) -> Node { return { a.val+a.sz*b, a.sz }; };
auto h = [](ll a, ll b) -> ll { return a + b; };
const Node T = {0, 0};
const ll E = 0;

// 区間加算・区間最小値取得
auto f = [](ll a, ll b) -> ll { return min(a, b); };
auto g = [](ll a, ll b) -> ll { return a + b; };
auto h = [](ll a, ll b) -> ll { return a + b; };
const ll T = INF;
const ll E = 0;

// 区間加算・区間最大値取得
auto f = [](ll a, ll b) -> ll { return max(a, b); };
auto g = [](ll a, ll b) -> ll { return a + b; };
auto h = [](ll a, ll b) -> ll { return a + b; };
const ll T = -INF;
const ll E = 0;

// 区間更新・区間和取得
// ・座圧とか、各位置に重み付けしたい時もこの区間和取得モノイドが使える。
// 　区間和取得の時にペアで使う要素数の方に、普通は初期値で1にするけど、
// 　ここを座圧した長さに変えると、あとはほぼいつも通りセグ木が使える。(ARC115_e)
struct Node {
    ll val, sz;
    operator ll() const { return val; }
};
auto f = [](Node a, Node b) -> Node { return { a.val+b.val, a.sz+b.sz }; };
auto g = [](Node a, ll b) -> Node { return { a.sz*b, a.sz }; };
auto h = [](ll a, ll b) -> ll { return b; };
const Node T = {0, 0};
// 要素が取りうる範囲外の値にする
const ll E = INF;

// 区間加算・区間更新・区間和取得
// 参考：nikkei2019final_d, ARC115_e
struct Node {
    ll val, sz;
    operator ll() const { return val; }
};
struct Func {
    ll add, assign;
    bool update;
    bool operator==(const Func &f) const {
        return add == f.add and assign == f.assign and update == f.update;
    }
};
auto f = [](Node a, Node b) -> Node { return { a.val+b.val, a.sz+b.sz }; };
auto g = [](Node a, Func b) -> Node {
    if (b.update) {
        return { a.sz*(b.add+b.assign), a.sz };
    } else {
        return { a.val+a.sz*b.add, a.sz };
    }
};
auto h = [](Func a, Func b) -> Func {
    if (b.update) {
        a.update = true;
        a.add = 0;
        a.assign = b.add+b.assign;
    } else {
        a.add += b.add;
    }
    return a;
};
const Node T = {0, 0};
const Func E = {0, 0, 0};

// 区間加算・区間更新・区間最大値取得
struct Func {
    ll add, assign;
    bool update;
    bool operator==(const Func &f) const {
        return add == f.add and assign == f.assign and update == f.update;
    }
};
auto f = [](ll a, ll b) -> ll { return max(a, b); };
auto g = [](ll a, Func b) -> ll {
    if (b.update) {
        return b.add+b.assign;
    } else {
        return a+b.add;
    }
};
auto h = [](Func a, Func b) -> Func {
    if (b.update) {
        a.update = true;
        a.add = 0;
        a.assign = b.add+b.assign; 
    } else {
        a.add += b.add;
    }
    return a;
};
const ll T = 0;
const Func E = {0, 0, 0};

// 区間乗算・区間更新・区間和取得
// 参考：tkppc6-1_f
struct Func {
    mint mul, assign;
    bool update;
    bool operator==(const Func &f) const {
        return mul == f.mul and assign == f.assign and update == f.update;
    }
};
auto f = [](mint a, mint b) -> mint { return a+b; };
auto g = [](mint a, Func b) -> mint {
    if (b.update) {
        return b.mul*b.assign;
    } else {
        return a*b.mul;
    }
};
auto h = [](Func a, Func b) -> Func {
    if (b.update) {
        a.update = true;
        a.mul = 1;
        a.assign = b.mul*b.assign;
    } else {
        a.mul *= b.mul;
    }
    return a;
};
const mint T = 0;
const Func E = {1, 0, 0};

// 区間01反転・区間和取得
// 参考：s8pc2_h, joisc2012day3-1
struct Node {
    ll cnt0, cnt1;
    operator ll() const { return cnt0; }
};
auto f = [](Node a, Node b) -> Node {
    a.cnt0 += b.cnt0;
    a.cnt1 += b.cnt1;
    return a;
};
auto g = [](Node a, bool b) -> Node {
    // 偶数回反転したらそのまま
    if (!b) {
        return a;
    } else {
        // 0と1の数が入れ替わる
        return {a.cnt1, a.cnt0};
    }
};
auto h = [](bool a, bool b) -> bool { return a^b; };
// { 区間内の0の個数, 区間内の1の個数 }
const Node T = {0, 0};
const bool E = false;

// 区間を1次関数で更新(ax+b)・区間和取得
// 参考：aclpc_k
struct Node {
    mint val, sz;
    operator mint() const { return val; }
};
struct Func {
    mint a, b;
    // 作用素の方は演算子イコールを定義しておく
    bool operator==(const Func &f) const {return a==f.a && b==f.b;}
};
auto f = [](Node v1, Node v2) -> Node {
    return { v1.val+v2.val, v1.sz+v2.sz };
};
auto g = [](Node v, Func f) -> Node {
    return { v.val*f.a + v.sz*f.b, v.sz };
};
auto h = [](Func f1, Func f2) -> Func {
    return { f1.a*f2.a, f1.b*f2.a + f2.b };
};
const Node T = {0, 0};
const Func E = {1, 0};

// 区間01反転・区間2値転倒数取得
// 参考：aclpc_l
struct Node {
    ll cnt0, cnt1, inv;
    operator ll() const { return inv; }
};
auto f = [](Node a, Node b) -> Node {
    Node res;
    res.cnt0 = a.cnt0+b.cnt0;
    res.cnt1 = a.cnt1+b.cnt1;
    res.inv = a.inv+b.inv;
    // 左の1 * 右の0 だけ転倒数が増える
    res.inv += a.cnt1*b.cnt0;
    return res;
};
auto g = [](Node a, bool swapped) -> Node {
    if (not swapped) {
        return a;
    } else {
        swap(a.cnt0, a.cnt1);
        // 全ペア - 今の転倒数
        a.inv = a.cnt0*a.cnt1-a.inv;
        return a;
    }
};
auto h = [](bool a, bool b) -> bool { return a^b; };
const Node T = {0, 0, 0};
const bool E = false;

// 区間加算・区間GCD取得
// 参考：ARC017_d, cf1459_c
// ※遅延セグ木は使えない。詳しくは該当の問題にて。

// 復元付き(直前の値を持たせる。inplaceに潰してしまう前に、各時点でのprvは別配列で保管する)
// 参考：cf1557_d
struct Node {
    ll val, prv;
    operator ll() const { return val; }
};
// 区間更新・区間最大値取得
auto f = [](Node a, Node b) -> Node {
    if (a.val >= b.val) {
        return a;
    } else {
        return b;
    }
};
auto g = [](Node a, Node b) -> Node { return b; };
auto h = [](Node a, Node b) -> Node { return b; };
const Node T = {-INF, -1};
// 要素が取りうる範囲外の値にする
const Node E = {INF, -1};

// 区間等差数列更新・区間最小値取得
// 参考：ABC177f
// 使い方：更新時に左端の分を引く
struct Node {
    ll val, left;
    operator ll() const { return val; }
};
auto f = [](Node a, Node b) -> Node { return { min(a.val, b.val), min(a.left, b.left) }; };
auto g = [](Node a, ll b) -> Node { return { b+a.left, a.left }; };
auto h = [](ll a, ll b) -> ll { return b; };
const Node T = {INF, INF};
const ll E = INF;

// 区間等差数列加算・区間最小値取得
// 参考：aoj3165_hupc2020
// 使い方：要素に {値, 左端}、作用素に {その位置を更新した回数cnt, 差し引きしたい量sub}
// 　　　　を持たせる。
// 初期化：数列の先頭を初項0とした公差dの等差数列でleftを初期化
// 　　　　seg.set(i, {値の初期値, i*d});
// 更新　：位置lを初項aとした公差dの等差数列を[l,r)に加算
// 　　　　seg.update(l, r, {1, a-l*公差d});
struct Node {
    ll val, left;
    operator ll() const { return val; }
};
struct Func {
    ll cnt, sub;
    bool operator==(const Func &f) const {
        return cnt == f.cnt and sub == f.sub;
    }
};
auto f = [](const Node &a, const Node &b) -> Node { 
    return { min(a.val, b.val), min(a.left, b.left) };
};
auto g = [](const Node &a, const Func &b) -> Node {
    return { a.val+b.cnt*a.left+b.sub, a.left }; 
};
auto h = [](const Func &a, const Func &b) -> Func {
    return { a.cnt+b.cnt, a.sub+b.sub };
};
const Node T = {INF, INF};
const Func E = {0, 0};

// 区間等差数列加算・区間最大値取得
struct Node {
    ll val, left;
    operator ll() const { return val; }
};
struct Func {
    ll cnt, sub;
    bool operator==(const Func &f) const {
        return cnt == f.cnt and sub == f.sub;
    }
};
auto f = [](const Node &a, const Node &b) -> Node { 
    return { max(a.val, b.val), min(a.left, b.left) };
};
auto g = [](const Node &a, const Func &b) -> Node {
    return { a.val+b.cnt*a.left+b.sub, a.left }; 
};
auto h = [](const Func &a, const Func &b) -> Func {
    return { a.cnt+b.cnt, a.sub+b.sub };
};
const Node T = {-INF, -INF};
const Func E = {0, 0};

// 区間等差数列加算・区間和取得
// 参考：https://null-mn.hatenablog.com/entry/2021/08/22/064325
// 　　　abc256_f,abc268_e
// 使い方
// ・こっちのがめちゃ簡単。ほぼ直感的に操作できる。
// ・この加算が対応できるのは和だけで、min,maxには拡張できないようなので注意。
// 初期化：{初期値, 左端i, 右端i+1}
// 更新　：区間[l,r)に{a,b}=関数ax+bを加算
mint inv2 = (mint)1 / 2;
struct Node {
    mint val;
    ll left, right;
    operator mint() const { return val; }
};
struct Func {
    mint a, b;
    bool operator==(const Func &f) const {
        return a == f.a and b == f.b;
    }
};
auto f = [](const Node &a, const Node &b) -> Node { 
    return { a.val+b.val, min(a.left, b.left), max(a.right, b.right) };
};
auto g = [](const Node &a, const Func &func) -> Node {
    return {
        a.val+(func.a*(a.left+a.right-1)+func.b*2)*(a.right-a.left)*inv2,
        a.left, a.right
    };
};
auto h = [](const Func &f1, const Func &f2) -> Func {
    return { f1.a+f2.a, f1.b+f2.b };
};
const Node T = {0, INF, -INF};
const Func E = {0, 0};

// 区間等差数列更新・最小値取得
// 参考：https://null-mn.hatenablog.com/entry/2021/08/22/064325
struct Node {
    ll val, left, right;
    operator ll() const { return val; }
};
struct Func {
    ll a, b;
    bool operator==(const Func &f) const {
        return a == f.a and b == f.b;
    }
};
auto f = [](const Node &a, const Node &b) -> Node { 
    return { min(a.val, b.val), min(a.left, b.left), max(a.right, b.right) };
};
auto g = [](const Node &a, const Func &func) -> Node {
    if (func.a == INF) {
        return a;
    } elif (func.a >= 0) {
        return { func.a*a.left+func.b, a.left, a.right };
    } else {
        return { func.a*(a.right-1)+func.b, a.left, a.right };
    }
};
auto h = [](const Func &f1, const Func &f2) -> Func {
    return f2;
};
const Node T = {INF, INF, -INF};
const Func E = {INF, INF};

// 区間等差数列更新・最大値取得(未verify)
// 参考：https://null-mn.hatenablog.com/entry/2021/08/22/064325
struct Node {
    ll val, left, right;
    operator ll() const { return val; }
};
struct Func {
    ll a, b;
    bool operator==(const Func &f) const {
        return a == f.a and b == f.b;
    }
};
auto f = [](const Node &a, const Node &b) -> Node { 
    return { max(a.val, b.val), min(a.left, b.left), max(a.right, b.right) };
};
auto g = [](const Node &a, const Func &func) -> Node {
    if (func.a == INF) {
        return a;
    } elif (func.a >= 0) {
        return { func.a*(a.right-1)+func.b, a.left, a.right };
    } else {
        return { func.a*a.left+func.b, a.left, a.right };
    }
};
auto h = [](const Func &f1, const Func &f2) -> Func {
    return f2;
};
const Node T = {-INF, INF, -INF};
const Func E = {INF, INF};

// 区間or・区間最小値取得
auto f = [](ll a, ll b) -> ll { return min(a, b); };
auto g = [](ll a, ll b) -> ll { return a | b; };
auto h = [](ll a, ll b) -> ll { return a | b; };
const ll T = INF;
const ll E = 0;

// 区間chmin・区間最小値取得
auto f = [](ll a, ll b) -> ll { return min(a, b); };
auto g = [](ll a, ll b) -> ll { return min(a, b); };
auto h = [](ll a, ll b) -> ll { return min(a, b); };
const ll T = INF;
const ll E = INF;

// 区間行列更新・区間行列積取得(未verify)
struct Node {
    // 2次元arrayの初期化は{}をひとつ多く括る
    array<array<mint, 2>, 2> mat{{
        {1, 0},
        {0, 1},
    }};
    Node(const array<array<mint, 2>, 2> &mat) : mat(mat) {};
    Node() {}
    bool operator==(const Node &f) const {
        return mat == f.mat;
    }
    operator array<array<mint, 2>, 2>() const { return mat; }
};
auto f = [](const Node &a, const Node &b) -> Node {
    // マージ方向をb,aにする
    return mat_dot(b.mat, a.mat);
};
auto g = [](Node a, Node b) -> Node { return b; };
auto h = [](Node a, Node b) -> Node { return b; };
const Node T = Node();
// 要素が取りうる範囲外の値にする
const Node E = Node({{
    {-1, -1},
    {-1, -1},
}});

// 区間01反転・区間01最大連長取得
// 参考：abc322_f
struct Node {
    // 最大連長0, 最大連長1, 左端から続く0の個数, 左端から続く1の個数, 右端から続く0の個数, 右端から続く1の個数, 区間長
    ll mx0, mx1, llen0, llen1, rlen0, rlen1, sz;
    operator ll() const {
        return mx1;
    }
};
auto f = [](Node a, Node b) -> Node {
    Node res;
    res.llen0 = a.llen0;
    res.llen1 = a.llen1;
    res.rlen0 = b.rlen0;
    res.rlen1 = b.rlen1;
    res.sz = a.sz + b.sz;
    res.mx0 = max({a.mx0, b.mx0, a.rlen0 + b.llen0});
    res.mx1 = max({a.mx1, b.mx1, a.rlen1 + b.llen1});
    if (a.rlen0 == a.sz) {
        res.llen0 = a.sz + b.llen0;
    }
    if (a.rlen1 == a.sz) {
        res.llen1 = a.sz + b.llen1;
    }
    if (b.llen0 == b.sz) {
        res.rlen0 = a.rlen0 + b.sz;
    }
    if (b.llen1 == b.sz) {
        res.rlen1 = a.rlen1 + b.sz;
    }
    return res;
};
auto g = [](Node a, bool b) -> Node {
    // 偶数回反転したらそのまま
    if (!b) {
        return a;
    } else {
        // 0と1の関係が入れ替わる
        return {a.mx1, a.mx0, a.llen1, a.llen0, a.rlen1, a.rlen0, a.sz};
    }
};

auto h = [](bool a, bool b) -> bool { return a ^ b; };
const Node T = {0, 0, 0, 0, 0, 0, 1};
const bool E = false;

// Beatsでできる。
// 区間chgcd・区間和取得 (yuki880)
// 区間chmod2・区間和取得 (yuki879)
// 区間chfloor・区間和取得 (abc256_h)
