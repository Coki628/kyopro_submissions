/*
参考：https://twitter.com/keroru10/status/1512637861308231681
・自力ならず。。
・インタラクティブ、2冪
・N=3で10^9とか出されるの無理じゃんってずっと言ってた。
　N=100固定に気付いたのが終了30分前…。
・まあ最初に誤読で溶かした時間はさておき、2冪をどうにかするんだろうと思いながら、
　結局自力では正解に辿り着けなかったのは残念。
　2冪を適切に選べば任意の数を作れるのは分かってたけど、今回は和を合わせるのが目的なので、
　用意しておいて使わない2冪があったりするとダメ。ここで詰まってしまった。
・終わってみれば結構シンプルで、まず2冪以外は適当に詰める。
　この時差分が10^9を超えないように、その時小さい方に詰める。
　こうすることで、最大要素より差分が大きくなることはなくなる。
　で、その後2冪は値の大きい方から、同じようにその時小さい方の集合に詰める。これだけ。
　これで差分はちゃんと半分ずつ縮まっていき、最終的に0にできる。
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

void answer(const vector<ll>& A) {
    int N = A.size();
    rep(i, N) {
        cout << A[i];
        if (i == N-1) {
            cout << endl;
        } else {
            cout << ' ';
        }
    }
}

vector<ll> pow2s;
void prep() {
    ll a = 1;
    while (a <= 1e9) {
        pow2s.eb(a);
        a *= 2;
    }
    sort(pow2s.rbegin(), pow2s.rend());
}

void solve() {
    ll N;
    cin >> N;
    ll M = pow2s.size();
    vector<ll> others;
    ll a = 3;
    while (others.size() < N-M) {
        if (popcount(a) != 1) {
            others.eb(a);
        }
        a++;
    }
    auto A = concat(pow2s, others);
    answer(A);
    auto B = LIST(N);

    vector<ll> res;
    ll sm1 = 0, sm2 = 0;
    for (auto a : concat(concat(B, others), pow2s)) {
        if (sm1 <= sm2) {
            sm1 += a;
            res.eb(a);
        } else {
            sm2 += a;
        }
    }
    assert(sm1 == sm2);
    answer(res);
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);
    cout << fixed << setprecision(15);

    prep();

    // single test case
    // solve();

    // multi test cases
    int T;
    cin >> T;
    rep(i, 1, T+1) {
        // cout << "Case #" + tostr(i) + ": ";
        solve();
    }
    return 0;
}
