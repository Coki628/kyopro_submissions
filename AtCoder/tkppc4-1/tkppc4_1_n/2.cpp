/*
参考：https://drive.google.com/file/d/11z3CGaxkl73umQm-XuXT-EY_QEyFekqa/view
・dojo set_e_5_g
・セグ木、(MODの)区間積取得、zero sum ranges系
・公式解の方針。すげースッキリ書けた。
・まず区間積取得だけど、普通にセグ木に乗せたらクソデカ数になって死ぬと思って辞めたんだけど、
　倍数の判定がしたいだけだったら、MOD取った値で、乗算もMODでやれば、
　MODに当たった所で0になって以降そのままだから、ちょうどそれが倍数になった判定にもできるし、
　以降ずっと0なのでクソデカ数になることもない。
　言われると確かにそうだけど、この使い方はしたことなかったな。
・ついでに和の方もmap使ったスッキリ実装に。
　区間の形が逆向きで無理かと思ったけど、先に全部詰めといて、
　区間の進行に合わせて抜いていく形にすれば、左端固定右端取得みたくできるね。。
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

#include "segment/WaveletMatrix.hpp"

void solve() {
    ll N, D;
    cin >> N >> D;
    auto A = LIST(N);

    vector<ll> acc(N);
    acc[0] = A[0] % D;
    rep(i, 1, N) {
        acc[i] = (acc[i-1]+A[i]) % D;
    }
    acc.insert(acc.begin(), 0);
    map<ll, ll> mp;
    rep(i, N+1) {
        mp[acc[i]]++;
    }

    auto seg = get_segment_tree(N, [&](ll a, ll b) { return a*b%D; }, 1LL);
    rep(i, N) {
        seg.set(i, A[i]%D);
    }
    seg.build();

    ll r = 0, ans = 0;
    rep(l, N) {
        ll nxt = seg.find_first(l, [](ll x) { return x == 0; });
        if (nxt == -1) break;
        while (r <= nxt) {
            mp[acc[r]]--;
            r++;
        }
        ans += mp[acc[l]];
    }
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
