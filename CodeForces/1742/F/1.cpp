/*
・自力AC。
・前から各文字何個あるか集計しながら進める。
　各回での判定は文字種26個でガチャガチャ比較すればいいので、
　愚直っぽい感じでいける(けど場合分けめんどかった)。
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
    ll Q;
    cin >> Q;

    ll L = 26;
    auto C = listnd(2, L, 0LL);
    C[0][0] = C[1][0] = 1;
    auto compare = [&]() -> bool {
        vvpll res(2);
        rep(i, L) {
            if (C[0][i]) {
                res[0].eb(i, C[0][i]);
            }
        }
        rep(i, L-1, -1, -1) {
            if (C[1][i]) {
                res[1].eb(i, C[1][i]);
            }
        }
        ll i = 0;
        while (i < min(res[0].size(), res[1].size())) {
            if (res[0][i].first < res[1][i].first) {
                return true;
            } elif (res[0][i].first > res[1][i].first) {
                return false;
            } else {
                if (res[0][i].second < res[1][i].second) {
                    // ここでS終わり
                    if (i+1 == res[0].size()) {
                        return true;
                    // 次があるなら大きくなる
                    } else {
                        return false;
                    }
                } elif (res[0][i].second > res[1][i].second) {
                    // ここでT終わり
                    if (i+1 == res[1].size()) {
                        return false;
                    // 次があるなら小さくなる
                    } else {
                        return false;
                    }
                } else {
                    i++;
                }
            }
        }
        return false;
    };
    rep(i, Q) {
        ll d, k;
        string s;
        cin >> d >> k >> s;
        d--;
        rep(j, s.size()) {
            C[d][s[j]-'a'] += k;
        }
        if (compare()) {
            YES();
        } else {
            NO();
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
