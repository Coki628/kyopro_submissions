/*
・cf1360_F
・結構悩んだけど自力AC！
・仮に全てOKにするためには、ある1つの文字列を取って、
　この文字列からも差分が1文字である必要がある。
　制約が小さいので、この1文字変える文字列を全ての位置とアルファベット26文字全部見て、
　その内側でN個の文字列を全て、1文字ずつチェックする形でも間に合う。
　妥当な文字列が1つでも見つかればOK、なければNG。
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#define CONSTANTS
#include "../../../_lib/cpp/_src/base.hpp"

constexpr long long INF = 1e18;
// constexpr long long INF = LONG_LONG_MAX;
constexpr int MOD = 1000000007;
// constexpr int MOD = 998244353;
constexpr long double EPS = 1e-10;
constexpr long double PI = M_PI;

#include "../../../_lib/cpp/_src/macros.hpp"

#include "../../../_lib/cpp/_src/combinatorics/ModInt.hpp"
using mint = ModInt<MOD>;

#include "../../../_lib/cpp/_src/template.hpp"

void solve() {
    ll N, M;
    cin >> N >> M;
    vector<string> S(N);
    rep(i, N) {
        cin >> S[i];
    }

    const ll L = 26;
    auto base = S[0];
    rep(i, M) {
        rep(c, L) {
            auto cur = base;
            cur[i] = 'a'+c;
            bool ok = true;
            rep(j, 1, N) {
                ll diff = 0;
                rep(k, M) {
                    if (cur[k] != S[j][k]) {
                        diff++;
                    }
                }
                if (diff > 1) {
                    ok = false;
                    break;
                }
            }
            if (ok) {
                print(cur);
                return;
            }
        }
    }
    print(-1);
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
