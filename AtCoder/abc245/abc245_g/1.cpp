/*
・なんとか自力AC？TLは見ちゃった後だけど、まあ自分で考えてた方針。
・ダイクストラ応用、多点スタートダイクストラ、2番目の最短路まで持つダイクストラ
・考察としては、人気者L人の側を始点として多点スタートダイクストラ。
　国の区別を考慮しなければこれで各人への最短距離が出せる。
　で、国の区別をどうするか。ようは自分の国じゃなければどこでもいいので、
　自分の国が1つである以上、国を区別した上で、最短から2つの距離を持っておけば、
　そのどちらかは自身の最短路として使えることになる。
　ここまでの考察がちゃんと本番中に出たのは良かった。まあでも、
　そこから30分程度しかない時間でこれを実装するのは全く無理だった訳だけど…。
・いわゆるダイクストラ改造系なんだけど、結構大変。
　普通のやつと比べて、
　1. 多点スタート
　2. 結果の値として、最短距離だけでなく、それを達成した始点の国番号を持つ
　3. 最短路だけでなく、2番目の最短路も持つ
　の3点がある。2,3番目が厄介。2番目はDPで復元用に遷移元持つ時みたいにペアにすればよくて、
　3番目は結果の配列2つ持てばいいんだけど、両方合わさると結構ややこしい。
・更新のロジックが重たかったので、update関数を別に分けて作った。
　ここで何らかの更新が発生すればtrueを返して、それをキューに詰めれるようにしてる。
・これで出してみると、2件TLE。WAはないので、どこかで無駄に回していることになる。
　continue部分を疑う。ここは自分より条件のいいのが既にキューに追加済であれば、
　自身からは遷移を行わないといった趣旨である。(多分)
　で、今回は結果の列が2つあるので、2番目の方だけ見て、
　res2[u].first < d だった所を、1番目も見て、
　res1[u].first < d and res1[u].second == k
　みたいに、国番号まで一致するなら1番目で判定するようにしたら、無事AC。
　試しに2番目の方の条件は外してもACしたので、結局1番目の最短路で
　国も一致してるやつの除外が大事だったんだな、となった。
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

// ダイクストラ
template<typename T>
pair<vector<T>, vector<T>> dijkstra(const vector<vector<pair<int, ll>>> &nodes, vector<pii> src) {

    int N = nodes.size();
    // res1[i] := {頂点iへの最短距離, それを達成した始点の国番号}
    vector<T> res1(N, {INF, -1});
    // res2[i] := {頂点iへの2番目の最短距離(ただし1番目と違う国番号に限る), それを達成した始点の国番号}
    vector<T> res2(N, {INF, -1});
    // 頂点vを値nxtで更新
    auto update = [&](int v, T nxt) -> bool {
        if (res1[v].first > nxt.first) {
            // 同じ国だったら2番目には使えない
            if (res1[v].second == nxt.second) {
                res1[v] = nxt;
                return true;
            // 違う国だったら両方使えるので2番目も更新
            } else {
                res2[v] = res1[v];
                res1[v] = nxt;
                return true;
            }
        } elif (res2[v].first > nxt.first) {
            // 1番目と国が違えば2番目として使う
            if (res1[v].second != nxt.second) {
                res2[v] = nxt;
                return true;
            }
        }
        return false;
    };
    priority_queue<pair<T, int>, vector<pair<T, int>>, greater<pair<T, int>>> que;
    for (auto s : src) {
        if (update(s.first, {0, s.second})) {
            que.push({{0, s.second}, s.first});
        }
    }
    while (!que.empty()) {
        auto [dist, u] = que.top(); que.pop();
        auto [d, k] = dist;
        if (res1[u].first < d and res1[u].second == k) continue;
        for (auto [v, cost] : nodes[u]) {
            if (update(v, {d+cost, k})) {
                que.push({{d+cost, k}, v});
            }
        }
    }
    return {res1, res2};
}

void solve() {
    ll N, M, K, L;
    cin >> N >> M >> K >> L;
    vector<ll> A(N), B(L);
    cin >> A >> B;
    rep(i, L) B[i]--;
    vvpil nodes(N);
    rep(i, M) {
        ll u, v, c;
        cin >> u >> v >> c;
        u--; v--;
        nodes[u].eb(v, c);
        nodes[v].eb(u, c);
    }

    vector<pii> src;
    rep(i, L) {
        // {人番号, 国番号}
        src.eb(B[i], A[B[i]]);
    }
    auto [res1, res2] = dijkstra<pli>(nodes, src);
    vector<ll> ans(N, -1);
    rep(i, N) {
        if (res1[i].first < INF and res1[i].second != A[i]) {
            ans[i] = res1[i].first;
        } elif (res2[i].first < INF and res2[i].second != A[i]) {
            ans[i] = res2[i].first;
        }
    }
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
