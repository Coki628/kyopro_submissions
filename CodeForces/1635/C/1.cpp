/*
・なんとか自力AC。。
・とりあえず、後ろ2つはいじれないのでそこが逆順なら即NG。
　で、それより手前はA[N-1]が非負なら、全部y=A[N-2],z=A[N-1]で置き換えるといい。
　負だったら、そのままじゃダメなので、非負の要素が来た時にzの候補を置き換える、
　ってやったんだけど、この場合元から昇順じゃなければNG確定らしい。。
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#define CONSTANTS
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
#include "template.hpp"

void solve() {
    ll N;
    cin >> N;
    auto A = LIST(N);

    if (A[N-2] > A[N-1]) {
        print(-1);
        return;
    }
    vector<array<ll, 3>> ans;
    ll mx = A[N-1];
    ll mxi = N-1;
    rep(i, N-3, -1, -1) {
        if (mx < 0 and A[i] >= 0) {
            mx = A[i];
            mxi = i;
        }
        if (A[i] > A[i+1]) {
            if (mx < 0 or mxi == i+1) {
                print(-1);
                return;
            }
        }
        if (mx >= 0 and mxi > i+1) {
            A[i] = A[i+1]-mx;
            ans.pb({i+1, i+2, mxi+1});
        }
    }
    rep(i, N-1) {
        if (A[i] > A[i+1]) {
            print(-1);
            return;
        }
    }
    print(ans.size());
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
