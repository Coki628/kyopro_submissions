/*
・自力ならず。悔しい。。
・スライドbitDP、行列累乗
・見えた方針は正しかったのに、時間内に詰め切れなかった。
　行列の遷移はほぼ作れてたけど、愚直書いて場合分け整えるパートが間に合わなかった。
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

#include "matrix/MatPow.hpp"

ll encode(string s) {
    ll m = s.size();
    ll bit = 0;
    rep(i, m) {
        ll b = s[i] - 'a';
        bit |= b << (m - i - 1);
    }
    return bit;
}

string decode(ll bit, ll sz) {
    string s;
    rep(i, sz) {
        if (bit >> i & 1) {
            s += 'b';
        } else {
            s += 'a';
        }
    }
    reverse(ALL(s));
    return s;
}

void solve() {
    ll N, M;
    cin >> N >> M;
    vector<string> S(M);
    cin >> S;
    set<string> se(ALL(S));

    auto check = [se](string s) -> bool {
        ll n = s.size();
        rep(l, n) {
            rep(r, l + 1, n + 1) {
                if (se.count(s.substr(l, r - l))) {
                    return false;
                }
            }
        }
        return true;
    };

    const ll L = 6;
    ll n = min(N, L);
    vector<string> init_s;
    rep(bit, 1 << n) {
        string res = decode(bit, n);
        if (check(res)) {
            init_s.eb(res);
        }
    }
    if (n < 6) {
        ll ans = init_s.size();
        print(ans);
        return;
    }

    vector<mint> init(1 << L);
    for (auto s : init_s) {
        init[encode(s)]++;
    }
    auto mat = listnd(1 << L, 1 << L, (mint)0);
    ll msk = (1 << L) - 1;
    rep(bit1, 1 << L) {
        auto s1 = decode(bit1, L);
        if (not check(s1)) continue;
        rep(b, 2) {
            ll bit2 = msk & ((bit1 << 1) | b);
            auto s2 = decode(bit2, L);
            if (check(s2)) {
                mat[bit2][bit1] = 1;
            }
        }
    }
    MatPow<mint> mp;
    auto res = mp.solve(mat, init, N - L);
    print(sum(res));
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
