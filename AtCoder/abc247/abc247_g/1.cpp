/*
・一応、自分で通したけど、まあTLで色々ヒント聞いてたから…。
・フロー、最小費用流、二部グラフの最大重みマッチング、slope
・フローだと聞いてしまっていれば、そういう目で見れば、見えやすい。
　2つの条件を頂点、人を辺として二部グラフを作る。
　今回は利得最大化なので、適当に下駄を履かす。流量は決まっているので差し引く値も分かる。
・ここまでは良かった。がしかし、流量を変えて各流量での利得を得るのが結構大変だった。
　1ずつ流したらTLEだしWAだし(ACLの最小費用流は何回も流す仕様になってないぽい)、
　slopeっていうそれっぽいものがあって使ったらやっぱりちょっとWAだし。
　でもここでTLの会話で誰かがslope使ってハマったみたいなこと言ってたのを思い出して、
　公式docsをよく読んで考えた。そしたら折れ線グラフだから、
　途中の値は省かれているとのこと。「3点が同一線上にあることはない」ってしっかり書いてある。
　これを踏まえて、足りない場所を補完すると、無事AC。
・このslope、今回は列挙に使ったけど、流量任意で最大利得求めるのにも使えるっぽいな。
　すげー速いし、まじでACLどうなってんだって感じ。
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

#include "acl/mincostflow.hpp"
using namespace atcoder;

void solve() {
    ll N;
    cin >> N;
    ll M = 150;
    ll offset = 1e9;
    mcf_graph<ll, ll> mcf(M*2+2);
    ll s = M * 2;
    ll t = M * 2 + 1;
    rep(i, N) {
        ll a, b, c;
        cin >> a >> b >> c;
        a--; b--;
        mcf.add_edge(a, M+b, 1, offset-c);
    }
    rep(i, M) {
        mcf.add_edge(s, i, 1, 0);
        mcf.add_edge(M+i, t, 1, 0);
    }

    auto res = mcf.slope(s, t);
    vector<ll> ans;
    rep(i, 1, res.size()) {
        if (res[i-1].first+1 != res[i].first) {
            ll a = (res[i].second-res[i-1].second) / (res[i].first-res[i-1].first);
            ll k = 1;
            rep(j, res[i-1].first+1, res[i].first) {
                ans.eb(offset*j - (res[i-1].second+a*k));
                k++;
            }
        }
        ans.eb(offset*res[i].first - res[i].second);
    }
    print(ans.size());
    for (ll a : ans) {
        print(a);
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
