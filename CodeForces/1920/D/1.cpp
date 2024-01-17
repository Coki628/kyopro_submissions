/*
参考：https://codeforces.com/blog/entry/122560
・自力ならず。むずい。
・数列コピー、K番目の値、再帰探索、オーバーフロー対策
・同じようなのが増殖してく系なので、ルンルンバーガーっぽく解けそうと思うも
　何も詰めれず。こういう系なーんか解けないんだよね…。
・公式解説よく読んだ。答えを求めるには、
　last[i] := i番目まで見た時の末尾の値
　cnt[i] := i番目まで見た時の要素数
　があれば良くて、これは事前に取っておく。オーバーフローに注意。
　で、クエリに対しては、このcnt数列をにぶたんして値を探して、
　ぴったりがあれば、そこで末尾の値であるlast[i]が答え。(これはまあ分かる)
　なければ、cnt[i - 1]個ずつの中のどこかにあるので、
　k mod cnt[i - 1]して繰り返しやる。ただしこの時0になったら、last[i - 1]が答え。
　これ分かんなくて、なんでだよって感じでしばらく考えてたんだけど、
　まあそこで0になるってことは、直前でぴったり合ったってことでしょ、
　くらいのふんわりした理解しかできなかった。
　今後自力で類題解ける気しね～。
　なお、MODを取ることで値は大きく減っていくので、
　再帰探索の回数はせいぜいlog回くらいで済むとのこと。
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#define CONSTANTS
#define __LOCAL
#include "base.hpp"

// constexpr long long INF = 1e18;
constexpr long long INF = LONG_LONG_MAX;
// constexpr int MOD = 1000000007;
constexpr int MOD = 998244353;
constexpr long double EPS = 1e-10;
constexpr long double PI = M_PI;

#include "macros.hpp"
#include "combinatorics/ModInt.hpp"
using mint = ModInt<MOD>;
#include "template.hpp"

void solve() {
    ll N, Q;
    cin >> N >> Q;
    vector<ll> last(N + 1, -1), cnt(N + 1);
    rep(i, N) {
        ll op, x;
        cin >> op >> x;
        if (op == 1) {
            last[i + 1] = x;
            if (add_overflow(cnt[i], 1LL)) {
                cnt[i + 1] = INF;
            } else {
                cnt[i + 1] = cnt[i] + 1;
            }
        } else {
            last[i + 1] = last[i];
            if (mul_overflow(cnt[i], x + 1)) {
                cnt[i + 1] = INF;
            } else {
                cnt[i + 1] = cnt[i] * (x + 1);
            }
        }
    }

    vector<ll> ans(Q);
    rep(i, Q) {
        ll k;
        cin >> k;

        auto rec = [&](auto &&f, ll cur) -> ll {
            ll j = bisect_left(cnt, cur);
            if (cnt[j] == cur) {
                return last[j];
            } else {
                cur %= cnt[j - 1];
                if (cur == 0) {
                    return last[j - 1];
                } else {
                    return f(f, cur);
                }
            }
        };
        ans[i] = rec(rec, k);
    }
    print(ans);
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);
    cout << fixed << setprecision(15);

    // single test case
    // solve();

    // multi test cases
    int T;
    cin >> T;
    while (T--) solve();

    return 0;
}
