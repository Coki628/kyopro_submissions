/*
・自力AC！
・ロリハ、1点更新
・ロリハで殴ったけど、強い人の見たら、
　今差異のある箇所の数、を持って適切に更新してる感じだった。
　確かにそれでいけそう。。
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

#include "string/RollingHash.hpp"

void solve() {
    vector<string> S(2);
    cin >> S[0] >> S[1];
    ll N = S[0].size();
    RollingHash rh;
    vector<uint64_t> hs(2);
    rep(i, 2) {
        hs[i] = rh.get_hash(S[i], 0, N);
    }
    ll T, Q;
    cin >> T >> Q;
    vector<ll> blocked(Q, -1);
    rep(i, Q) {
        if (blocked[i] != -1) {
            rep(j, 2) {
                rh.update(hs[j], N, blocked[i], '*', S[j][blocked[i]]);
            }
        }
        ll op;
        cin >> op;
        if (op == 1) {
            ll pos;
            cin >> pos;
            pos--;
            rep(j, 2) {
                rh.update(hs[j], N, pos, S[j][pos], '*');
            }
            if (i + T < Q) {
                blocked[i + T] = pos;
            }
        } else if (op == 2) {
            ll s1, pos1, s2, pos2;
            cin >> s1 >> pos1 >> s2 >> pos2;
            s1--, s2--, pos1--, pos2--;
            char a = S[s1][pos1];
            char b = S[s2][pos2];
            rh.update(hs[s1], N, pos1, a, b);
            rh.update(hs[s2], N, pos2, b, a);
            swap(S[s1][pos1], S[s2][pos2]);
        } else if (op == 3) {
            if (hs[0] == hs[1]) {
                YES();
            } else {
                NO();
            }
        }
    }
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
