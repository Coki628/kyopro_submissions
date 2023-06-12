/*
・自力ならず。。これはひどい。
・インタラクティブ、DFS
・終了後ツイートから、戻り時の入力受け取り忘れが発覚。そこ直したらAC。。
・DFSやって2N回で達成できるかどうかは本番中ふわっとしてたけど、
　確かに全域木を構成すると思うと、往復しても2N回以内で達成できそうってなるね。。
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
    ll N, M;
    cin >> N >> M;
    vector<ll> visited(N);
    auto rec = [&](auto &&f, ll u, ll prv) -> void {
        visited[u] = 1;
        ll k;
        cin >> k;
        assert(k != -1);
        vector<ll> V(k);
        cin >> V;
        V--;
        for (auto v : V) {
            if (visited[v]) continue;
            cout << v + 1 << endl;
            if (v == N - 1) {
                string res;
                cin >> res;
                assert(res == "OK");
                exit(0);
            }
            f(f, v, u);
        }
        cout << prv + 1 << endl;
        // 要らないけど移動したのでルール通り入力を受け取る
        cin >> k;
        V.resize(k);
        cin >> V;
    };
    rec(rec, 0, -1);
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
