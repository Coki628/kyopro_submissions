/*
参考：https://blog.hamayanhamayan.com/entry/2017/05/24/154618
　　　https://twitter.com/kyopro_friends/status/1523300806547881984
　　　https://atcoder.jp/contests/abc250/submissions/31552731
・Zobrist Hash
・名前は聞いたことあったけど初めて使った。集合の管理に有用らしい。
・基本的な使い方は思った以上に簡単。各値に乱数を振って累積XORするだけ。
　ただし今回は同値が含まれるので、そこはスキップする必要がある。(XOR打ち消されて消えるもんね)
　座圧してmap使わないようにすると、速度もかなりいい感じに出る。(AC0.19秒)
・左端も動く任意区間でもできるそうだが、そうなるとスキップする位置が変わってしまうので、
　おそらくちょっと面倒。多分だけど、予め各値で出現indexを取っておいて、
　左端を1つずらした時にその値を消して次の出現位置に足す、みたいのをXORのBITとかでやって、
　クエリ先読みしといて左端順で処理していく、みたいな感じだと思われる。
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
using mint = ModInt<MOD>;
#include "template.hpp"

#include "common/randrange.hpp"

void solve() {
    ll N;
    cin >> N;
    auto A = LIST(N);
    auto B = LIST(N);

    Compress<ll> cp(concat(A, B));
    ll M = cp.size();
    A = cp.zip(A);
    B = cp.zip(B);

    vector<ll> hash(M);
    rep(i, M) {
        hash[i] = randrange(1, INF);
    }
    vector<bool> useda(M), usedb(M);
    vector<ll> tablea(N+1), tableb(N+1);
    rep(i, N) {
        if (useda[A[i]]) {
            tablea[i+1] = tablea[i];
        } else {
            useda[A[i]] = true;
            tablea[i+1] = tablea[i] ^ hash[A[i]];
        }
    }
    rep(i, N) {
        if (usedb[B[i]]) {
            tableb[i+1] = tableb[i];
        } else {
            usedb[B[i]] = true;
            tableb[i+1] = tableb[i] ^ hash[B[i]];
        }
    }

    ll Q;
    cin >> Q;
    rep(i, Q) {
        ll x, y;
        cin >> x >> y;
        if (tablea[x] == tableb[y]) {
            Yes();
        } else {
            No();
        }
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
