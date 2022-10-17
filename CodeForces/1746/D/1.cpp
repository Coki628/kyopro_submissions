/*
参考：https://twitter.com/AllDirections4/status/1581328992455380992
・自力ならず。。
・木DPっぽいメモ化再帰
・K個のパスを根から始めて、子頂点の数でなるべく均等に割りながら潜っていく。
　こうすると、題意にある同じ兄弟頂点間のパス数の差分が1以内というのが守られる。
　(割り算して商か商+1となるため)
　で、次にどの子頂点にそれぞれ商と商+1を割り当てるかを決める。
　これができなかった。DFS2回やったり木DPこねくり回したけど、結局その方針だとダメだった。
　正解は商と商+1両方試して、両者の差分を持っておき、利得の大きい方から商+1を与える、
　って感じだった。そのために、木DPというよりはメモ化再帰をやる。
　木DPいつも戻り値voidでやってるので、今回メモ化再帰もそっちの感じでやったけど
　ちゃんとうまく動いた。メモ化再帰は戻り値返す方が直感的だと思ってたけど、
　こっちのが遷移先自由に使いまわせるし、案外柔軟にやりやすいかもしれないな。
・普通に全部やったらMLE&TLEして、割り切れる時に商+1を探さないようにしたら通った。
　そこで大差ないと思ったんだけど、結構変わるんだな…。
・むずかったけど、こういう木の問題好きだし、解きたかったなー。
　木で木DPじゃないメモ再帰を使うパターンは初な気がしたのでためになった。
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
    ll N, K;
    cin >> N >> K;
    vvi nodes(N);
    rep(i, 1, N) {
        ll p;
        cin >> p;
        p--;
        nodes[p].eb(i);
    }
    auto A = LIST(N);

    vector<map<int, ll>> memo(N);
    auto rec = [&](auto&& f, ll u, ll k) -> void {
        if (memo[u].count(k)) {
            return;
        }
        memo[u][k] = k * A[u];
        if (nodes[u].empty()) {
            return;
        }
        auto [d, m] = divmod(k, (ll)nodes[u].size());
        vector<pll> vec;
        for (auto v : nodes[u]) {
            if (m) f(f, v, d+1);
            f(f, v, d);
            vec.eb(memo[v][d]-memo[v][d+1], v);
        }
        // dでやった場合とd+1でやった場合の差分を利得として、子頂点をソート
        sort(ALL(vec));
        // 利得の大きいm個にd+1を与えたとする
        rep(i, m) {
            auto [_, v] = vec[i];
            memo[u][k] += memo[v][d+1];
        }
        rep(i, m, nodes[u].size()) {
            auto [_, v] = vec[i];
            memo[u][k] += memo[v][d];
        }
    };
    rec(rec, 0, K);
    ll ans = memo[0][K];
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
