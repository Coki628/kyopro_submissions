/*
・なんとか自力AC！通し切った！
・インタラクティブ
・基本方針は最初の4つで最大と最小の初期候補を作ってから、
　残りを見ていって大きい差分が出せたらそこを更新、って感じ。
　なんだけど細部で考察詰めミスってて7WAからのAC。
　インタラクティブはどうしてもサブミットデバッグになっちゃう。。
・結構実装まとめるの大変(インタラクティブはだいたいそうだけど)だったし、
　詳細はソース内コメントにて。
・例えば列の最初が0,9,9,1だと、cand1=0,cand2=1,dummy1=9 ってなるはずで、
　dummyに最大値が来ちゃってるパターンのチェックが必要だと思ったんだけど、
　0さえ当たればいいので最大値別に要らなかった。。
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#define CONSTANTS
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
ll ask(ll i, ll j, ll k) {
    ll res;
    cout << "? " << i+1 << ' ' << j+1 << ' ' << k+1 << endl;
    cin >> res;
    return res;
}

void answer(ll i, ll j) {
    cout << "! " << i+1 << ' ' << j+1 << endl;
}

void solve() {
    ll N;
    cin >> N;

    ll M = 4;
    map<ll, vector<ll>> mp;
    rep(i, M) {
        ll res = ask(i, (i+1)%M, (i+2)%M);
        mp[res].eb(i);
        mp[res].eb((i+1)%M);
        mp[res].eb((i+2)%M);
    }
    // クエリ返答の最大値
    ll mx = mp.rbegin()->first;
    // 最大値で出現したindexの出現数を集計
    auto C = Counter(mp.rbegin()->second);
    vector<pll> V;
    for (auto [k, v] : C) {
        V.eb(v, k);
    }
    // 出現数が多かった方から最初の最大最小に
    sort(V.rbegin(), V.rend());
    ll cand1 = V[0].second;
    ll cand2 = V[1].second;
    ll dummy1 = V[2].second;
    ll dummy2 = V[3].second;

    rep(i, M, N) {
        ll res1 = ask(i, dummy1, cand2);
        ll res2 = ask(cand1, dummy1, i);
        // 差分が大きい方を更新候補にする
        if (res1 >= res2) {
            if (chmax(mx, res1)) {
                cand1 = i;
            }
        } else {
            if (chmax(mx, res2)) {
                cand2 = i;
            }
        }
    }
    // dummy1に最大値が来ちゃってるパターン (いらなかった)
    // ll res = ask(cand1, dummy1, dummy2);
    // if (res >= mx) {
    //     cand2 = dummy1;
    // }
    answer(cand1, cand2);
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
