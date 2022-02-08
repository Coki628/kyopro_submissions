/*
参考：https://www.youtube.com/watch?v=SG60Cp9pSog
・abc155_f
・やっぱりすぬけさんの解説動画は理解が深まる。
・差分列、累積和の逆、グラフに帰着、全域木、座標圧縮
・すごいむずいんだけど、要点としては典型要素が随所にある。
・まず領域がでかいけど必要な点は限られるので座圧する。
・次にL,Rの区間反転を、差分列にすることで2点反転に帰着させる。
　これはいもすで2点打って累積和取ると区間加算になるやつの逆と言える。
　区間加算ぽい操作を差分列取って2点にするは結構あるっぽい。
・で、2点操作にすると、その2点をつなぐ辺を持ったグラフの捉えることができて、
　このグラフ上で、区間が全0の状態=全頂点が0の状態を目指すことになる。
・これは連結成分毎に見るんだけど、実は全域木取って葉から貪欲に決める、
　でうまくいく時はいくし、ダメな時は無理になって正しい答えになる。
　具体的には、連結成分内に1の頂点が偶数個あると絶対OKだし、奇数個だと無理。
　言われると確かにそれっぽいねって思うけど、自分で考えて確信は持てないな…。
　元々全域木なら確かに葉から決める貪欲で正解な感じするけど、
　実際には辺は他にもたくさんある訳だから、
　全域木1個見るだけでいいのは何か非自明な気がするよね。
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

void solve() {
    ll N, M;
    cin >> N >> M;
    vector<ll> tmp;
    vector<pll> AB(N);
    rep(i, N) {
        cin >> AB[i].first >> AB[i].second;
        AB[i].first--;
        tmp.eb(AB[i].first);
    }
    sort(ALL(AB));
    const int MX = 1e9;
    AB.eb(MX, 0);
    tmp.eb(MX);
    auto [A, B] = zip(AB);
    vector<ll> L(M), R(M);
    rep(i, M) {
        cin >> L[i] >> R[i];
        L[i]--;
    }

    // 爆弾のある座標だけで座圧する
    Compress<ll> cp(tmp);
    A = cp.zip(A);
    // L,Rもその座標に合わせる
    L = cp.zip(L);
    R = cp.zip(R);
    ll N2 = cp.size();

    // 差分列D
    vector<ll> D = {B[0]};
    rep(i, N2-1) {
        D.eb(abs(B[i]-B[i+1]));
    }

    // 差分列の2点をつなぐグラフにする
    vvpll nodes(N2);
    rep(i, M) {
        ll u = L[i], v = R[i];
        nodes[u].eb(v, i);
        nodes[v].eb(u, i);
    }
    vector<bool> visited(N2);
    vector<ll> ans;
    // 連結成分毎にDFS
    auto dfs = [&](auto&& f, ll u) -> ll {
        if (visited[u]) return 0;
        visited[u] = true;
        ll cur = D[u];
        for (auto [v, i] : nodes[u]) {
            ll res = f(f, v);
            // この先が1になってしまうならこの辺を使って0にする
            if (res) {
                ans.eb(i+1);
                cur = 1-cur;
            }
        }
        return cur;
    };
    rep(i, N2) {
        // 戻ってきて1が残ってしまったらNG
        ll res = dfs(dfs, i);
        if (res) {
            print(-1);
            return;
        }
    }
    sort(ALL(ans));
    print(ans.size());
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
