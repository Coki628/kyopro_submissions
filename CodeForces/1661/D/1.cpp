/*
参考：https://twitter.com/SSRS_cp/status/1512832013199626243
　　　https://codeforces.com/contest/1661/submission/153174390
・自力ならず。。
・後ろから見る、1次いもす法、区間1次関数加算
・セグ木に等差数列乗せるやつでやろうとしたけど、複数回分まとめて足すのができなくて断念。
　うまくモノイド作り直せばできるんだろうか。
・結果的には、tkppc4_2_fで2次関数やったのとほぼ同じアプローチが使える。
　ただし今回は後ろから決めていきたくて、添字の面倒を減らしたいのでリバースして前からやる。
　それに合わせて、公差も1じゃなくて-1にする。初項K公差-1の等差数列。
　で、後ろから見れば、そこを0以下にするのに最低限必要な回数が分かるので、やる。
・後半、初項に持ってこれない位置はちょっと別の形が必要で、
　一番必要な回数が多くなる場所に合わせてまとめてやる。
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
    auto B = LIST(N);

    // D次関数の列を作る
    int D = 1;
    vector<ll> F;
    // -K,-(K-1)...-1
    rep(i, K, 0, -1) {
        F.eb(-i);
    }
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

    reverse(ALL(B));
    ll ans = 0;
    rep(i, N-K+1) {
        if (i > 0) {
            // D+1回累積
            rep(j, 1, D+2) {
                imos[i][j] = imos[i-1][j] + imos[i][j-1];
            }
        }
        ll rest = B[i] + imos[i][D+1];
        if (rest > 0) {
            ll need = ceil(rest, K);
            ans += need;
            add(i, need);
            // 今回の更新分(初項*回数)を累積にも反映させておく
            rep(j, 1, D+2) {
                imos[i][j] += -K*need;
            }
        }
    }
    // 初項にできない位置は一番必要な回数が多くなる場所に合わせてまとめてやる
    ll mx = 0;
    rep(k, 1, K) {
        ll i = N-K+k;
        rep(j, 1, D+2) {
            imos[i][j] = imos[i-1][j] + imos[i][j-1];
        }
        ll rest = B[i] + imos[i][D+1];
        if (rest > 0) {
            ll need = ceil(rest, K-k);
            chmax(mx, need);
        }
    }
    ans += mx;
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
