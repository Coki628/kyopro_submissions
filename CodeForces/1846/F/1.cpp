/*
参考：https://www.youtube.com/watch?v=uvmEmaKXKjg
・自力ならず。
・インタラクティブ
・考察というか読解がいまいちできなくて解けなかった。
　こたつがめさんの動画見て、2回までしか同じ姿でいられないとか、
　変化するまで待つみたいな話聞いたら方針は分かった。
　ちゃんと英語読めるようになりたいねー…。
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
// constexpr int MOD = 1000000007;
constexpr int MOD = 998244353;
constexpr long double EPS = 1e-10;
constexpr long double PI = M_PI;

#include "macros.hpp"
#include "combinatorics/ModInt.hpp"
using mint = ModInt<MOD>;
#include "template.hpp"

vector<ll> ask(vector<ll> remove, ll n) {
    remove++;
    cout << "- ";
    if (remove.size()) {
        cout << remove.size() << ' ' << remove << endl;
    }  else {
        cout << 0 << endl;
    }
    vector<ll> res(n - remove.size());
    cin >> res;
    return res;
}

void answer(ll i) {
    cout << "! " << i + 1 << endl;
}

void solve() {
    ll N;
    cin >> N;
    vector<ll> A(N);
    cin >> A;

    map<ll, ll> C1, C2;
    for (auto a : A) C1[a]++;
    ll x = -1;
    // ミミックが変化するまで待つ
    rep(_, 2) {
        A = ask({}, A.size());
        C2.clear();
        for (auto a : A) C2[a]++;
        if (C1 != C2) {
            for (auto [k, v] : C2) {
                if (v > C1[k]) {
                    x = k;
                    break;
                }
            }
            assert(x != -1);
            C1 = C2;
            break;
        }
    }
    assert(x != -1);
    vector<ll> remove;
    rep(i, A.size()) {
        if (A[i] != x) {
            remove.pb(i);
        }
    }
    // 目的の番号x以外全部消す
    A = ask(remove, A.size());
    rep(i, A.size()) {
        // x以外の番号が見つかればそれが答え
        if (A[i] != x) {
            answer(i);
            return;
        }
    }
    A = ask({}, A.size());
    rep(i, A.size()) {
        if (A[i] != x) {
            answer(i);
            return;
        }
    }
    assert(0);
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
