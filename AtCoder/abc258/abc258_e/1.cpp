/*
・時間外なんとか自力AC？キーワード見ちゃってたけど、まあ時間をかければ…。
・周期、累積和にぶたん、ダブリング
・ある位置iから詰め始めると、X以上になる位置は常に一定。
　これは割り算して余りで累積和にぶたんみたいにすると分かる。
　この時その箱に何個のジャガイモを詰めれたかも同様に分かる。
　この、次の開始位置とその時に入ったジャガイモの数を前計算しておけば、
　次の開始位置をダブリングに乗せて大きいKに答えられるようになる。
・ダブリングに乗せるもの自体は次の位置だけで良かったけど、
　それに至るまでにそれなりに考察要素が結構あった気がして、
　これ水diff上位程度なんかぁ、となった。
　Gじゃなくてこっち取り組んでたとして、時間内に詰め切れたかどうか…。
・よく考えたらnxt配列はllいらないと思ってintにしてみたら、
　思った以上に速くなってAC0.41秒→0.22秒。
　と思ったらもう1回投げたら0.32秒だったのでまあ誤差もありそう。
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

#include "common/Doubling.hpp"

auto f = [](int prev, int power) {
    return power;
};

void solve() {
    ll N, Q, X;
    cin >> N >> Q >> X;
    auto W = LIST(N);
    auto qs = LIST(Q);

    ll all = sum(W);
    ll d, m;
    tie(d, m) = divmod(X, all);
    Accumulate<ll> acc(concat(W, W));
    vector<int> nxt(N);
    vector<ll> ans(N);
    rep(i, N) {
        ll j = bisearch_min(i-1, N*2, [&](ll r) {
            return acc.query(i, r) >= m;
        });
        assert(j != -1);
        assert(j-i <= N);
        ans[i] = d*N + (j-i);
        nxt[i] = j % N;
    }
    auto db = get_doubling(40, nxt, -1, f);
    for (auto k : qs) {
        k--;
        auto res = db.get(0, k);
        print(ans[res]);
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
