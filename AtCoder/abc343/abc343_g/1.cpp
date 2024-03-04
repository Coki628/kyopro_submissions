/*
・終了後自力AC？ではないな。TL見ちゃったし…。
・文字列、連続部分列、最適化、ロリハ、bitDP
・制約が小さく、順列全部見れば解けそうな内容で、しかし20なので順列は無理。
　となればbitDPがしたくなる。けど3つに跨って重複するみたいなやつの扱いが
　ぱっと見えずに、とりあえずスキップ。本番中はそれ以降見なかった。
　終了後TL見て、包含なやつは消していい、と聞いて確かにー、となった。
　自力で気付けたかは今となっては分からない。
　けどもうちょい考えたら気付けたんじゃないかなー。。
　で、そこが分かれば、ペアでの前後関係だけ見ればよくなるので、
　先に全ペアでコスト(必要な文字数)を数えてからbitDPすればOK。
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#define CONSTANTS
#define __LOCAL
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

#include "string/RollingHash.hpp"

void solve() {
    ll N;
    cin >> N;
    vector<string> S(N);
    cin >> S;

    // 完全な重複は先に消しとく
    UNIQUE(S);
    N = S.size();
    RollingHash rh;
    vv<ull> table(N);
    rep(i, N) {
        table[i] = rh.build(S[i]);
    }
    // 包含の確認
    vector<int> use(N, true);
    rep(i, N) {
        rep(j, N) {
            if (i == j) continue;
            ll n = S[i].size(), m = S[j].size();
            if (n < m) {
                rep(l, m - n + 1) {
                    ll r = l + n;
                    if (rh.query(table[j], l, r) == rh.query(table[i], 0, n)) {
                        use[i] = false;
                    }
                }
            }
        }
    }
    vector<string> S2;
    ll N2 = 0;
    rep(i, N) {
        if (use[i]) {
            S2.eb(S[i]);
            N2++;
        }
    }
    assert(N2 > 0);

    vv<ull> table2(N2);
    rep(i, N2) {
        table2[i] = rh.build(S2[i]);
    }
    // cost[i][j] := iの後ろにjを置いた時に必要な文字数
    auto cost = listnd(N2, N2, 0);
    rep(i, N2) {
        rep(j, N2) {
            if (i == j) continue;
            ll m = min(S2[i].size(), S2[j].size());
            ll mx = 0;
            rep(k, 1, m + 1) {
                auto hasha = rh.query(table2[i], S2[i].size() - k, S2[i].size());
                auto hashb = rh.query(table2[j], 0, k);
                if (hasha == hashb) {
                    chmax(mx, k);
                }
            }
            assert(mx < m);
            cost[i][j] = S2[j].size() - mx;
        }
    }

    auto dp = listnd(1LL << N2, N2, INF);
    rep(i, N2) {
        dp[1LL << i][i] = S2[i].size();
    }
    rep(bit, 1, 1LL << N2) {
        rep(i, N2) {
            if (!(bit >> i & 1)) continue;
            rep(j, N2) {
                if (bit >> j & 1) continue;
                chmin(dp[bit | 1LL << j][j], dp[bit][i] + cost[i][j]);
            }
        }
    }
    ll ans = min(dp[(1LL << N2) - 1]);
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
