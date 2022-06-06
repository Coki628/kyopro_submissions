/*
参考：https://atcoder.jp/contests/abc254/editorial
・別解。これが自分的には一番辿り着きやすそうかも。
・素因数分解、素因数から約数列挙、再帰全探索
・平方数sqを決め打ちして、1^2~N^2まで全探索する。
　この時、自分では2乗を陽に約数列挙にかけてしまったので計算量が無理になったが、
　2乗と分かっているなら元の数で素因数分解して、
　全素因数を倍にすれば素因数分解としては正しく成り立つ。
　これを再帰全探索で素因数の選び方全通りやると、約数全列挙になる。
　これで約数列挙ができたので、後は条件を満たすか1つずつチェックすればOK。
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

void solve() {
    ll N;
    cin >> N;

    ll ans = 0;
    rep(a, 1, N+1) {
        ll sq = a * a;
        auto fact = factorize(a);
        // a^2(平方数)の素因数にする
        for (auto& [k, v] : fact) {
            v *= 2;
        }
        // 素因数から、再帰全探索で約数を全列挙
        ll m = fact.size();
        vector<ll> divs;
        auto rec = [&](auto&& f, ll i, ll val) {
            if (i == m) {
                divs.eb(val);
                return;
            }
            rep(j, fact[i].second+1) {
                f(f, i+1, val*pow(fact[i].first, j));
            }
        };
        rec(rec, 0, 1);
        // i,j<=Nの条件を確認
        for (auto i : divs) {
            ll j = sq / i;
            if (i <= N and j <= N) {
                ans++;
            }
        }
    }
    print(ans);
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
