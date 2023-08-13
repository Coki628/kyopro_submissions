/*
・自力ならず。。悔しい。
・自己ループありの期待値DP
・まあまあ迷走したけど途中でいい線までは行ってた。
　答え合わなくて別の方針探しに行ってしまったんだけど、
　メモ化配列がldじゃなくてintになってたせいだった。。
　そこ直して色々状況整えたらちゃんと通った。
・でもこれをそもそも一目見てストレートに方針立てれるようじゃなきゃ、
　次のステージにはきっと進めないんだろうとは思う…。
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
    ll N, M;
    cin >> N >> M;
    vector<ll> C(N);
    vvl P(N);
    rep(i, N) {
        cin >> C[i];
        ll sz;
        cin >> sz;
        P[i].resize(sz);
        cin >> P[i];
    }

    vector<ld> memo(M, -1);
    auto rec = [&](auto &&f, ll a) -> ld {
        if (a >= M) {
            return 0;
        }
        if (memo[a] != -1) {
            return memo[a];
        }
        ld res1 = INF;
        rep(i, N) {
            ld res2 = C[i];
            ll sz = P[i].size();
            ll zero = count(ALL(P[i]), 0);
            rep(j, sz) {
                if (P[i][j] == 0) continue;
                res2 += f(f, a + P[i][j]) / (ld)sz;
            }
            res2 *= (ld)sz / (sz - zero);
            chmin(res1, res2);
        }
        return memo[a] = res1;
    };
    ld ans = rec(rec, 0);
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
