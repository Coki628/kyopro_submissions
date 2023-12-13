/*
・なんとか自力AC！とはいえ時間かかりすぎた。。
・XOR、最大値の最小化、上位ビットから貪欲、再帰探索
・ふと未ACで目についたのでupsovled。
　割と早い段階で候補が半分ずつになってく再帰探索の方針は立ってたのに、
　合わせるのに時間がかかった。これじゃあ本番間に合わないだろう。
　最後に詰まったのなんて、(1LL << b)の括弧がなくて演算順序がバグってただけ…。
・上位ビットから見て行くと、そのビットを立てるか決めた時に、
　0になることが決まった要素は(その時点での)最上位ビットが消えることから、
　最大値となる候補から外れることができる。つまり以降のビットでは、
　そこで立つことになった要素だけを持てばいい。
　これで、1ビット潜る毎に半分ずつくらい候補を減らしていける。
　途中で立つかどうかの片方だけに全要素が寄った場合、
　全要素そのビットを0にすることに何の損もないので選択が一択になる。
　立つ立たない両方がある時だけ、両方試して小さい方を取る。
　これで再帰探索がかなり早く終わり、答えが求まる。
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
// constexpr int MOD = 1000000007;
constexpr int MOD = 998244353;
constexpr long double EPS = 1e-10;
constexpr long double PI = M_PI;

#include "macros.hpp"
#include "combinatorics/ModInt.hpp"
using mint = ModInt<MOD>;
#include "template.hpp"

void solve() {
    ll N;
    cin >> N;
    vector<ll> A(N);
    cin >> A;

    auto rec = [&](auto &&f, ll b, vector<ll> &vec) -> ll {
        if (b < 0) return 0;
        vector<ll> nxt0, nxt1;
        for (auto i : vec) {
            if (A[i] >> b & 1) {
                nxt1.eb(i);
            } else {
                nxt0.eb(i);
            }
        }
        if (nxt1.empty()) {
            return f(f, b - 1, nxt0);
        }
        if (nxt0.empty()) {
            return f(f, b - 1, nxt1);
        }
        ll res = INF;
        // このビットを立てる
        chmin(res, f(f, b - 1, nxt0) + (1LL << b));
        // 立てない
        chmin(res, f(f, b - 1, nxt1) + (1LL << b));
        return res;
    };
    vector<ll> P(N);
    iota(ALL(P), 0);
    ll res = rec(rec, 30, P);
    print(res);
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);
    cout << fixed << setprecision(15);

    // single test case
    solve();

    // multi test cases
    // int T;
    // cin >> T;
    // while (T--) solve();

    return 0;
}
