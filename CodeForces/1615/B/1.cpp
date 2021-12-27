/*
・これはTLE。
・クエリ先読み、Mo、ビット毎に見る
・区間長20万に√掛かったとして、2秒間に合わなかった。
　まあ内側でビット18個回してるから、logもう1つ乗ってるようなもんか。。
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

constexpr long long INF = 1e18;
// constexpr long long INF = LONG_LONG_MAX;
constexpr int MOD = 1000000007;
// constexpr int MOD = 998244353;

#include "../../../_lib/cpp/template.hpp"

struct Mo {
    int n;
    vector< pair< int, int > > lr;

    explicit Mo(int n) : n(n) {}

    // クエリを半開区間[l,r)で順番に追加
    void add(int l, int r) {
        lr.emplace_back(l, r);
    }

    template< typename AL, typename AR, typename EL, typename ER, typename O >
    void build(const AL &add_left, const AR &add_right, const EL &erase_left, const ER &erase_right, const O &out) {
        int q = (int) lr.size();
        int bs = n / min< int >(n, sqrt(q));
        vector< int > ord(q);
        iota(begin(ord), end(ord), 0);
        sort(begin(ord), end(ord), [&](int a, int b) {
            int ablock = lr[a].first / bs, bblock = lr[b].first / bs;
            if(ablock != bblock) return ablock < bblock;
            return (ablock & 1) ? lr[a].second > lr[b].second : lr[a].second < lr[b].second;
        });
        int l = 0, r = 0;
        for(auto idx : ord) {
            while(l > lr[idx].first) add_left(--l);
            while(r < lr[idx].second) add_right(r++);
            while(l < lr[idx].first) erase_left(l++);
            while(r > lr[idx].second) erase_right(--r);
            out(idx);
        }
    }

    // add:   区間が伸びる時の処理(引数はmoのindex)
    // erase: 区間が縮む時の処理(引数はmoのindex)
    // out:   クエリに回答する処理(引数はクエリのindex)
    // 伸縮時に左右で処理に違いがなければadd,eraseは1つずつでOK
    template< typename A, typename E, typename O >
    void build(const A &add, const E &erase, const O &out) {
        build(add, add, erase, erase, out);
    }
};

int L[10007], R[10007], ans[10007];
const int M = 18;
const int N = 10e5*2;
int C[M];
Mo mo(N+1);

void solve() {
    int Q;
    cin >> Q;
    rep(i, Q) {
        cin >> L[i] >> R[i];
        R[i]++;
        mo.add(L[i], R[i]);
    }

    auto add = [&](int a) {
        rep(k, M) {
            if (a>>k == 0) break;
            if (a>>k & 1) {
                C[k]++;
            }
        }
    };
    auto erase = [&](int a) {
        rep(k, M) {
            if (a>>k == 0) break;
            if (a>>k & 1) {
                C[k]--;
            }
        }
    };
    auto out = [&](int i) {
        int mx = 0;
        rep(j, M) chmax(mx, C[j]);
        ans[i] = R[i]-L[i]-mx;
    };
    mo.build(add, erase, out);

    rep(i, Q) print(ans[i]);
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
