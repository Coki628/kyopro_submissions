/*
参考：https://atcoder.jp/contests/abc227/editorial
　　　https://www.youtube.com/watch?v=9o4Lbxd3up4
・数え上げ、約数の個数、素因数分解、二項係数、区間篩
・まあ自力ではさっぱりだった訳だけど、解法聞くと整数系の知識を色々問われていて教育的。
　まず約数の個数って言われて、素因数分解して各素因数の個数+1がぱっと出なかったあたりダメ。
　すっかり忘れてた…。それが分かれば、後は二項係数は分解すれば全部掛け算と割り算だから、
　個別の素因数の個数を全部足したり引いたりすればいい。
　問題はこの素因数の個数を知りたい範囲が最大で10^12まであって、
　普通のエラトステネスで列挙できないこと。ここで大昔に蟻本で読んだ知識が出てくる。
　最大値は大きいけど、見たい範囲の区間長は現実的。こういう時に区間篩が使える。
　読んだ時は、こんなん使える場面あんのかねって思ったけどあったね。
・Pythonで昔書いたやつを移植してきたけど、その時使ったのは、
　「区間[l,r)内の各値が持つ(区間の値毎に数えた)素因数の個数」だったけど、
　今回欲しいのは「区間[l,r)内の値の(素因数毎で数えた)各素因数の個数」なので、
　中身をちょっといじった。
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#define CONSTANTS
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

// 区間[l,r)内の各素因数の個数(エラトステネスの区間篩) 
map<ll, ll> segment_sieve(ll l, ll r) {

    int MAX = int(sqrt(r));
    vector<bool> is_prime(MAX+1, true);
    map<ll, ll> C;
    vector<ll> A(r-l);
    iota(ALL(A), l);

    rep(i, 2, MAX+1) {
        ll cnt = 0;
        if (is_prime[i]) {
            rep(j, i*2, MAX+1, i) {
                is_prime[j] = false;
            }
            // 素数が見つかったら、区間内にあるその倍数について素因数分解していく
            rep(j, max(2LL, (l+i-1)/i)*i, r, i) {
                while (A[j-l] % i == 0) {
                    A[j-l] /= i;
                    cnt++;
                }
            }
            C[i] += cnt;
        }
    }
    // 自身が素数であればその分を足す
    rep(i, r-l) {
        if (A[i] > 1) {
            C[A[i]]++;
        }
    }
    return C;
}

void solve() {
    ll N, K;
    cin >> N >> K;

    auto C = segment_sieve(N-K+1, N+1);
    for (auto [k, v] : segment_sieve(1, K+1)) {
        C[k] -= v;
    }

    mint ans = 1;
    for (auto [k, v] : C) {
        ans *= (v+1);
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
