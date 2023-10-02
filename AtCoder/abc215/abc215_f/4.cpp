/*
参考：https://qiita.com/keroru/items/6e0a22e8c9bf2a24dc68
・尺取りのキュー実装
・短く動かすタイプ。でも今回は外側の集合が目的なので、両側を2つのキューで持つ。
　でもこれ整理してて思ったけど、左のキュー要らないな。
　1個ずつ順番に詰めてくだけだもんね。。
　でも両方持った方が直感的には流れが整理しやすそうなので、一応このままにしておく。
・この問題は結構計算量きつめだけど、速度面で添字でやる時より悪いこともなかった。
　最初遅くてちょっと直したんだけど、原因は座圧だった。
　(座圧後Y配列の取得処理を前もってやらないでにぶたん内で毎回やると遅い。
　llを全部intにするのも試したけどそれは意外と変化なしだった。)
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
    vector<pll> XY;
    rep(i, N) {
        ll x, y;
        cin >> x >> y;
        XY.eb(x, y);
    }

    sort(ALL(XY));
    vector<ll> X, Y;
    tie(X, Y) = zip(XY);
    Compress<ll> cp(Y);
    ll M = cp.size();
    auto cpy = cp.zip(Y);
    ll res = bisearch_max(0, 1e9 + 7, [&](ll k) {
        BIT<ll> bitl(M), bitr(M);
        deque<ll> quel, quer;
        rep(i, N) {
            bitr.add(cpy[i], 1);
            quer.eb(i);
        }
        rep(i, N) {
            // 左集合に1個詰める
            bitl.add(cpy[i], 1);
            quel.eb(i);
            // 空になるか条件を満たすまで右集合から取り除く
            while (quer.size() and X[quer.front()] - X[quel.back()] < k) {
                bitr.add(cpy[quer.front()], -1);
                quer.pop_front();
            }
            if (quer.size()) {
                ll bitlmn = cp.unzip(bitl.bisearch_fore(0, M - 1, 1));
                ll bitlmx = cp.unzip(bitl.bisearch_back(0, M - 1, 1));
                ll bitrmn = cp.unzip(bitr.bisearch_fore(0, M - 1, 1));
                ll bitrmx = cp.unzip(bitr.bisearch_back(0, M - 1, 1));
                if (bitlmx - bitrmn >= k or bitrmx - bitlmn >= k) {
                    return true;
                }
            } else {
                break;
            }
        }
        return false;
    });
    print(res);
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
