/*
・なんとか自力AC！
・セグ木とBIT
・indexに行、値に列を持つ。
　gatherはセグ木にぶたんでk以上残ってる最小位置。
　scatterはBITで[0,maxRow]で区間和取って、k足りるなら埋める。
　この時、埋まってる行を何回も探しに行かないように、行が埋まったら左端の基準を進めて、
　次回以降はその左端より右から埋めてくみたいにする。
・セグ木とBITをクラス内で使うのがあんまやんないから詰まった…。
　先に宣言だけ書いといて、コンストラクタで初期化するといいね。。
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#define CONSTANTS
#define __LOCAL
// #define CAST_MINT_TO_LL
#include "base.hpp"

constexpr long long INF = 1e18;
// constexpr long long INF = LONG_LONG_MAX;
constexpr int MOD = 1000000007;
// constexpr int MOD = 998244353;
constexpr long double EPS = 1e-10;
constexpr long double PI = M_PI;

#include "macros.hpp"
#include "combinatorics/ModInt.hpp"
using mint = ModInt<MOD>;
#include "template.hpp"

function<ll(ll, ll)> f = [](ll a, ll b) { return max(a, b); };

class BookMyShow {
public:
    int H, W;
    ll L = 0;
    SegmentTree<ll, function<ll(ll, ll)>> seg;
    BIT<ll> bit;

    BookMyShow(int H, int W) :
        H(H),
        W(W),
        seg(SegmentTree<ll, function<ll(ll, ll)>>(H, f, -INF)),
        bit(BIT<ll>(H)
    ) {
        rep(h, H) {
            seg.set(h, W);
            bit.add(h, W);
        }
        seg.build();
    }

    vector<int> gather(int k, int maxRow) {

        ll h = seg.find_first(L, [&](ll x) { return x >= k; });
        if (h == -1 or h > maxRow) {
            return {};
        }
        ll w = seg[h];
        seg.update(h, seg[h] - k);
        bit.add(h, -k);
        return {(int)h, W-(int)w};
    }

    bool scatter(int k, int maxRow) {
        ll sm = bit.query(L, maxRow+1);
        if (sm < k) {
            return false;
        }
        rep(h, L, H) {
            ll use = min((ll)k, seg[h]);
            k -= use;
            seg.update(h, seg[h] - use);
            bit.add(h, -use);
            if (seg[h] == 0) {
                chmax(L, h+1);
            }
            if (k == 0) break;
        }
        return true;
    }
};

/**
 * Your BookMyShow object will be instantiated and called as such:
 * BookMyShow* obj = new BookMyShow(n, m);
 * vector<int> param_1 = obj->gather(k,maxRow);
 * bool param_2 = obj->scatter(k,maxRow);
 */

#ifdef __LOCAL
    int main() {
        // Solution sol;
        // auto res = sol.funcName();
        // print(res);
        return 0;
    }
#endif
