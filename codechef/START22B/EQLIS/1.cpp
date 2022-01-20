/*
・自力AC！これは考察寄りアドホック感のある構築だったので、珍しく通せてよかった。
　なんかでも似たようなLISの長さを調整するやつみたいのを
　あっとこで見たことある気がするから、それが良かったかも。
・奇数なら簡単で山か谷にする。偶数全部無理をぶん投げてWA。。
　よくよく考察すると、偶数は2以外できる。
　まず後ろ半分を前にして半分ずつ昇順にしたやつを用意。
　すると昇順LISはN/2で降順LISは2、みたいになる。
　で、ここからNの大きさによって片側で適度に昇順を崩すみたいにやる。
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
    ll N;
    cin >> N;

    if (N == 2) {
        NO();
        return;
    }

    YES();
    deque<ll> ans;
    if (N%2 == 1) {
        rep(i, N, 0, -1) {
            if (i%2) {
                ans.push_front(i);
            } else {
                ans.pb(i);
            }
        }
    } else {
        rep(i, N/2+1, N+1) {
            ans.eb(i);
        }
        vector<ll> tmp;
        rep(_, N/2-2) {
            tmp.eb(ans.front());
            ans.pop_front();
        }
        reverse(ALL(tmp));
        rep(i, N/2-2) {
            ans.eb(tmp[i]);
        }
        rep(i, 1, N/2+1) {
            ans.eb(i);
        }
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
