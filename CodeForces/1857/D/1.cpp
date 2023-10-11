/*
・自力AC。
・まともな方針は全然検討がつかなかったんだけど、差分が大事そうなのは分かる。
　で、適当にエスパーしてA-Bで差分取ってみると、これが大きい方が良さそうで、
　サンプルを見ると最大値なものだけが選ばれてそうなのでそう信じると通る…。
・今落ち着いて問題見返したら気付いたけど、これ式変形して
　Au-Bu>=Av-Bv の形にしちゃえば、差分列の最大値だけOKってのが見えるのね。。
　ほんとに式変形に弱いな…。まじで気付かない。
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

void solve() {
    ll N;
    cin >> N;
    vector<ll> A(N), B(N);
    cin >> A >> B;

    vector<ll> diff(N);
    rep(i, N) {
        diff[i] = A[i] - B[i];
    }
    ll mx = max(diff);
    vector<ll> ans;
    rep(i, N) {
        if (diff[i] == mx) {
            ans.eb(i);
        }
    }
    ans++;
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
