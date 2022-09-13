/*
・なんとか自力AC！
・インタラクティブ
・にぶたんやるだけかと思ったらクエリ回数が…。
　ある頂点a,bのパスが両方分かれば、その和が答え。
　でも同じクエリ何回飛ばしても同じことしか言ってくれないそうなので、
　適当に違う頂点間でも聞いたら通った。
　(でもこれ頂点3つしかない時とか聞ける回数少なすぎてうまくいくとは限らなくないかね)
・終了後、TLより。N小さい時は普通に-1返った時に境界分かるじゃんね。
　よくオレのやつ通ったな…。
・上記踏まえて、直した版。これなら任意のケースに通用するはず。
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

// インタラクティブ用
ll ask(ll a, ll b) {
    ll res;
    cout << "? " << a  << ' ' << b << endl;
    cin >> res;
    return res;
}
void answer(ll n) {
    cout << "! " << n << endl;
}

void solve() {
    rep(i, 1, 25) {
        ll res1 = ask(i, i+1);
        ll res2 = ask(i+1, i);
        if (res1 == -1) {
            answer(i);
            return;
        } elif (res1 != res2) {
            answer(res1+res2);
            return;
        }
    }
    assert(0);
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
