/*
・JOI埋め
・なんとか自力AC！
　半年前くらいに解けなくて撤退した形跡があったので、リベンジできて良かった。
・45度回転、重複を除く、式変形
・最近やってたのもあり、45度回転を早めに検討できたのは良かった。
　これで角っぽい動きが飛車っぽくなるので、縦横で考えられる。
　各行列について、見張りが存在していればまずはその行列のマスを全部足す。
　ここから重複を引いていく。まず偶奇が違うと絶対交わらないので分けて考える。
　変換したU,V座標の全ての交差点であれば行数*列数をやるだけなのだが、
　これだとL*Lグリッドの枠外まで数えてしまうので、ここからさらに引く。
　幸いこのU,V座標はひし形みたいになっており、元のグリッドから見て、
　x,y両方にはみ出る箇所というのはなく、上下左右のいずれかの領域にのみ、はみ出る。
　よってx,yでダブルカウントしてしまう心配がない。
　後は式変形で、まずは連立方程式からu,vをx=,y=の形にして、
　x,yに0未満とL以上の条件を代入する。
　x = u+v → 0 > u+v → -u > v
　x = u+v → L <= u+v → 2L-u <= v
　yも同じ感じで。
　この式が作れれば、条件を満たす個数を二分探索で探せる。
　前述の通りここに重複はないので、答えから引きたい分からこの個数を全部引けばOK。
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
    ll L, N;
    cin >> L >> N;
    vector<ll> U, V;
    rep(i, N) {
        ll x, y;
        cin >> x >> y;
        U.eb(x-y);
        V.eb(x+y);
    }

    UNIQUE(U);
    UNIQUE(V);
    // 偶奇違いは干渉し合わないので分ける
    vector<ll> oddu, evenu, oddv, evenv;
    for (auto u : U) {
        if (u%2 == 0) {
            evenu.eb(u);
        } else {
            oddu.eb(u);
        }
    }
    for (auto v : V) {
        if (v%2 == 0) {
            evenv.eb(v);
        } else {
            oddv.eb(v);
        }
    }

    ll ans = 0;
    // その行,列にある全マス分
    for (auto u : U) {
        ans += L - abs(u);
    }
    for (auto v : V) {
        ans += L - abs((L-1)-v);
    }
    // U,Vの重複分(行,列が交わる場所の個数)
    ll evensub = evenu.size() * (ll)evenv.size();
    ll oddsub = oddu.size() * (ll)oddv.size();
    // 重複分のうち不要なもの(L*Lの枠外)を引く
    for (auto u : evenu) {
        // v < -u
        evensub -= bisect_left(evenv, -u);
        // v >= 2L-u
        evensub -= evenv.size() - bisect_left(evenv, L*2-u);
        // v < u
        evensub -= bisect_left(evenv, u);
        // v >= 2L+u
        evensub -= evenv.size() - bisect_left(evenv, L*2+u);
    }
    for (auto u : oddu) {
        oddsub -= bisect_left(oddv, -u);
        oddsub -= oddv.size() - bisect_left(oddv, L*2-u);
        oddsub -= bisect_left(oddv, u);
        oddsub -= oddv.size() - bisect_left(oddv, L*2+u);
    }
    ans -= evensub;
    ans -= oddsub;
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
