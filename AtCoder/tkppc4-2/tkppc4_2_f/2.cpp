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

    // 2次関数の列を作る
    vector<ll> B;
    rep(i, 1, K) {
        B.eb(pow(i, 2));
    }
    rep(i, K, 0, -1) {
        B.eb(pow(i, 2));
    }
    ll M = B.size();
    // 3回差分
    auto diff = B;
    rep(_, 3) {
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

    auto imos = list2d(4, N, 0LL);
    // 区間[l,l+M)に2次関数Bを加算
    auto add = [&](ll l, ll x) {
        for (auto [i, d] : sdiff) {
            if (l+i >= N) break;
            imos[0][l+i] += d*x;
        }
    };
    rep(i, N) {
        if (i > 0) {
            // 3回累積
            rep(j, 1, 4) {
                imos[j][i] = imos[j][i-1] + imos[j-1][i];
            }
        }
        A[i] -= imos[3][i];
        if (A[i] < 0) {
            No();
            return;
        }
        if (i < N-M+1) {
            add(i, A[i]);
            // 今回の更新分を累積にも反映させておく
            rep(j, 1, 4) {
                imos[j][i] += A[i];
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
