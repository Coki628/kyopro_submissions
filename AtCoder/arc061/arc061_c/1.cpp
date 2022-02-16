/*
参考：https://img.atcoder.jp/data/arc/061/editorial.pdf
　　　https://betrue12.hateblo.jp/entry/2019/05/25/134323
・dojo set_d_2_4
・大変だった。。当然自力ではない。
・頂点拡張ダイクストラ、辺の張り方を工夫
・路線の種類を状態に持っても、全頂点合わせてせいぜい辺の数くらいしか状態がないはずなので、
　これはmapとかでその頂点が持ちうるやつだけ作ればできる。ここからが長かった。
・まあTLEとかする。解説を確認すると、これだけだと、たくさんの路線が乗り入れる駅同士とかで
　路線の全ペアがやばい数になる。なので、各駅について「改札の外」みたいな頂点を作って、
　まずそこに遷移、他の路線への乗り換えは全てその頂点経由でやる、とする。
　これを実装したつもりになるが、これでもTLEする。ここからなかなか進めなかった。
・結局、改札の外以外の頂点に来た時でも隣接リストのループを回してたのがダメだった。
　確かにこれだと、その先に遷移することはないとはいえ、辺の数回すループがだいぶ増えてしまいそう。
　そこで、この時は同じ路線の頂点だけ見ればいいので、隣接リストの持ち方の辺コストをいつもと逆にして、
　路線の情報を前にしてソート、こうしておけば、にぶたんで同じ路線の遷移先だけ効率よく探せる。
　これで無事AC。
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

constexpr long long INF = 1e18;
// constexpr long long INF = LONG_LONG_MAX;
constexpr int MOD = 1000000007;
// constexpr int MOD = 998244353;

#include "../../../_lib/cpp/_src/base.hpp"

#include "../../../_lib/cpp/_src/macros.hpp"

#include "../../../_lib/cpp/_src/combinatorics/ModInt.hpp"
using mint = ModInt<MOD>;

#include "../../../_lib/cpp/_src/template.hpp"

// ダイクストラ
vector<defaultdict<int, int>> dijkstra(vector<vector<pair<int, int>>> &nodes, int src, int goal=-1) {

    int N = nodes.size();
    rep(i, N) {
        // 路線毎に探せるように路線cを前にしてソートしておく
        sort(ALL(nodes[i]));
    }
    vector<defaultdict<int, int>> res(N, {MOD});
    priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, greater<tuple<int, int, int>>> que;
    res[src][-1] = 0;
    que.push({0, -1, src});

    while (!que.empty()) {
        auto [dist, c, u] = que.top(); que.pop();
        if (u == goal and c == -1) return res;
        if (res[u][c] < dist) continue;
        if (c != -1) {
            // 改札の外
            int nxc = -1;
            if (chmin(res[u][nxc], dist)) {
                que.push({dist, nxc, u});
            }
            // 同じ路線
            int i = bisect_left(nodes[u], {c, -MOD});
            while (i < nodes[u].size() and nodes[u][i].first == c) {
                auto [nxc, v] = nodes[u][i];
                if (chmin(res[v][nxc], dist)) {
                    que.push({dist, nxc, v});
                }
                i++;
            }
        } else {
            // 違う路線
            for (auto [nxc, v] : nodes[u]) {
                if (c == nxc) continue;
                if (chmin(res[v][nxc], dist+1)) {
                    que.push({dist+1, nxc, v});
                }
            }
        }

    }
    return res;
}

void solve() {
    ll N, M;
    cin >> N >> M;
    vector<vector<pii>> nodes(N);
    rep(i, M) {
        ll u, v, c;
        cin >> u >> v >> c;
        u--; v--;
        nodes[u].eb(c, v);
        nodes[v].eb(c, u);
    }

    auto res = dijkstra(nodes, 0, N-1);
    ll ans = res[N-1].count(-1) ? res[N-1][-1] : -1;
    if (ans >= INF) ans = -1;
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
