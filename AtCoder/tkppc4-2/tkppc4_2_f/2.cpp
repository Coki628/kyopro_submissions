/*
参考：https://blog.hamayanhamayan.com/entry/2019/08/20/111656
　　　https://theory-and-me.hatenablog.com/entry/2020/08/23/182712
　　　https://imoz.jp/algorithms/imos_method.html
・2次いもす法、区間2次関数加算
・グリッドとかの2次元いもすではなく、2次関数を加算するいもす。
　普段やっているいもすは(2次元いもすを含め)通常0次のいもすと呼ばれるもので、
　これを1次関数、2次関数に拡張できるというもの。
・今回は都度その位置の本来の値を取得したいので、
　累積和を動的に取らなければならずちょっとややこしくなってるが、
　ようは定数個の点で加減算をやって、3回累積和を取れば元の値が得られる。
　具体的に加減する点は、今回のように加算する区間長が固定なら
　実際にその2次関数を作って3回差分を取れば得られるし、どうやら一般化もできそう。
　左端から1,4,9,16..となる形で区間長[l,r)への区間加算であれば、
　imos[l] += 1, imos[l+1] += 1,
　imos[r] -= (r-l+1)^2, imos[r+1] += (r-l+1)^2+(r-l)^2-2, imos[r+2] -= (r-l)^2
　の5点でよさそう。逆向きの16,9,4,1でもこれをほぼ反転させたようなものになる。
・最近類題で1次関数のやつ(cf1661D)をやったので、
　ちょっと一般化した版をこっちにも適用してみた。無事AC。
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
    ll N, K;
    cin >> N >> K;
    auto A = LIST(N);

    // D次関数の列を作る
    int D = 2;
    vector<ll> F;
    // 1^2,2^2...2^(K-1)
    rep(i, 1, K) {
        F.eb(pow(i, 2));
    }
    // K^2,(K-1)^2...1^2
    rep(i, K, 0, -1) {
        F.eb(pow(i, 2));
    }
    ll M = F.size();
    // D+1回差分
    auto diff = F;
    rep(_, D+1) {
        diff.eb(0);
        rep(i, diff.size()-1, 0, -1) {
            diff[i] = diff[i] - diff[i-1];
        }
    }
    // sparseな形で持つ
    vector<pll> sdiff;
    rep(i, diff.size()) {
        if (diff[i] != 0) {
            sdiff.eb(i, diff[i]);
        }
    }
    auto imos = list2d(N, D+2, 0LL);
    // i始点としたD次関数Fをc回加算
    auto add = [&](ll i, ll c) {
        for (auto [k, v] : sdiff) {
            if (i+k >= N) break;
            imos[i+k][0] += v*c;
        }
    };

    rep(i, N) {
        if (i > 0) {
            // D+1回累積
            rep(j, 1, D+2) {
                imos[i][j] = imos[i-1][j] + imos[i][j-1];
            }
        }
        A[i] -= imos[i][D+1];
        if (A[i] < 0) {
            No();
            return;
        }
        if (i < N-M+1) {
            add(i, A[i]);
            // 今回の更新分(初項*回数)を累積にも反映させておく
            rep(j, 1, D+2) {
                imos[i][j] += A[i];
            }
            A[i] = 0;
        }
    }
    if (sum(A) == 0) {
        Yes();
    } else {
        No();
    }
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
