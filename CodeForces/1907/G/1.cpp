/*
参考：https://codeforces.com/blog/entry/123012
　　　https://codeforces.com/blog/entry/123012?#comment-1091505
・自力ならず。。まあ発想が出なかったEよりはこっち通したかったな…。
・01フリップ、Functional Graph、SCC
・まず入次数0のスイッチについてはそこを操作するしかないので、必要ならやる。
　同様に依存関係の解消したスイッチの入り切りを確定していき、サイクル部分だけ残す。
　で、これをどうするか自分では(解説読んでも)うまく詰め切れなかったんだけど、
　コメントが助けになった。Functional Graphなのでこの時点で全て入次1出次1の
　きれいなサイクルだけが残っているはずで、これは1点決めてしまえば、
　その参照先のスイッチをどうするべきかは一意になり、順次決めて行けば
　1周して最初のスイッチに戻ってくる。この時最後に決まるライトがOFFになってればOKで、
　最初のスイッチをON/OFF両方試して、妥当なうち入り切りした数の少ない方を採用する。
　まあここの構築がいちいち一時配列に情報逃がしたり状態戻したりでめんどい。
　これを全てのサイクルでやればOK。
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

#include "acl/scc.hpp"

void solve() {
    ll N;
    cin >> N;
    string S;
    cin >> S;
    vector<ll> A(N);
    cin >> A;
    A--;

    vector<ll> B(N);
    rep(i, N) {
        B[i] = S[i] - '0';
    }
    atcoder::scc_graph scc(N);
    rep(i, N) {
        scc.add_edge(i, A[i]);
    }
    auto groups = scc.scc();
    vector<int> used(N), ans;
    for (auto &group : groups) {
        // サイクル以外は先に決める
        if (group.size() == 1) {
            ll u = group[0];
            used[u] = true;
            if (B[u]) {
                ans.eb(u);
                B[u] ^= 1;
                B[A[u]] ^= 1;
            }
        }
    }

    // サイクルはどこか1点決めれば後は定まるので、妥当なうち数の少ない方を採用する
    rep(u, N) {
        if (used[u]) continue;
        ll mn = INF;
        vector<ll> vec, tmp;
        // uを使う
        vec.eb(u);
        B[u] ^= 1;
        B[A[u]] ^= 1;
        ll cur = A[u];
        while (cur != u) {
            if (B[cur]) {
                vec.eb(cur);
                B[cur] ^= 1;
                B[A[cur]] ^= 1;
            }
            cur = A[cur];
        }
        if (B[cur] == 0) {
            mn = vec.size();
            tmp = vec;
        }
        // 状態戻し
        for (auto v : tmp) {
            B[v] ^= 1;
            B[A[v]] ^= 1;
        }
        // uを使わない
        vec.clear();
        cur  = A[u];
        while (cur != u) {
            if (B[cur]) {
                vec.eb(cur);
                B[cur] ^= 1;
                B[A[cur]] ^= 1;
            }
            cur = A[cur];
        }
        if (B[cur] == 0 and vec.size() < mn) {
            mn = vec.size();
            tmp = vec;
        }
        if (mn >= INF) {
            print(-1);
            return;
        }
        for (auto v : tmp) {
            ans.eb(v);
        }
        used[u] = true;
        cur = A[u];
        while (cur != u) {
            used[cur] = true;
            cur = A[cur];
        }
    }
    print(ans.size());
    ans++;
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
