/*
・なんとか自力AC！
・区切るDP、組み合わせの遷移
・色の状態も持ちたくなるが、ブロックを区切る所に遷移するようにすれば、
　その位置にいる時の色は一意になるのでその添字は要らなくなる。
　どう遷移するかだが、今いる位置に貰うDPしてくるとして、
　同じ色がK個取れるような最右位置より左からなら全て遷移できる。
　これは色毎に予め隣接リストにindexを詰めておくと分かる。
　また、遷移先C[i]と同じ色がK個より多い区間であればどれを使うか選べるので、
　遷移先の1つは固定するとして、nCr(区間内の色C[i]の個数-1, K-1)を掛ける。
　最大ブロック時の通り数が知りたいので、ブロック数は添字に持って値は通り数とする。
　これで状態N^2の遷移Nで計O(N^3)のDPになる。
　遷移Nを高速化してG2も解きたかったが、二項係数が絡む遷移の高速化はできなかった。
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
    ll N, K;
    cin >> N >> K;
    vector<ll> C(N);
    cin >> C;

    ModTools<mint> mt(N + 1);
    vvl adj(N + 1);
    rep(i, N) {
        adj[C[i]].eb(i);
    }
    // dp[i][j] := i番目まで見て、jブロック作った通り数
    auto dp = listnd(N + 1, N + 1, (mint)0);
    dp[0][0] = 1;
    rep(i, N) {
        ll k = bisect_right(adj[C[i]], i);
        if (k - K < 0) continue;
        ll r = adj[C[i]][k - K];
        rep(j, N) {
            ll cnt = K - 1;
            rep(m, r, -1, -1) {
                if (C[m] == C[i]) cnt++;
                dp[i + 1][j + 1] += dp[m][j] * mt.nCr(cnt - 1, K - 1);
            }
        }
    }
    ll mx = 0;
    rep(i, N + 1) {
        rep(j, 1, N + 1) {
            if (dp[i][j] != 0) {
                chmax(mx, j);
            }
        }
    }
    if (mx == 0) {
        print(1);
        return;
    }
    mint ans = 0;
    rep(i, N + 1) {
        ans += dp[i][mx];
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
