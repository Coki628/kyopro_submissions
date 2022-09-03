/*
・なんとか自力AC！
・Bが大きい所から決める。
　B[i]決めたらB[(i+1)%N]=B[i]-1にしてもいいかみたいなチェックを右に向かって進める。
　なんだけど、元々合ってたりで場合分けした。祈りながら投げて無事AC…。
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
    auto A = LIST(N);
    auto B = LIST(N);

    rep(i, N) {
        if (A[i] > B[i]) {
            NO();
            return;
        }
    }

    priority_queue<pll, vector<pll>> que;
    vector<bool> done(N);
    rep(i, N) {
        if (A[i] < B[i]) {
            que.push({B[i], i});
        } else {
            done[i] = true;
        }
    }
    while (que.size()) {
        auto [b, i] = que.top(); que.pop();
        if (done[i]) continue;
        done[i] = true;
        if (A[i] < B[i]) {
            A[i] = b;
            ll j = (i+1)%N;
            ll x = b - 1;
            while (1) {
                if (x > B[j]) {
                    NO();
                    return;
                } elif (A[j] == B[j]) {
                    done[j] = true;
                    break;
                }
                x--;
                j = (j+1)%N;
            }
        }
    }
    YES();
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
