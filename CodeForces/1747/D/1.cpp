/*
参考：https://twitter.com/kude_coder/status/1588574268744663040
・むずい。これは解けなかったな。
・累積xor、zero sum ranges系、偶奇
・まず、題意の操作を試すと、操作して0以外の値になっても、
　消えなかった値が奇数長個に増えるだけでこれは多分消せないので、
　0にできる操作だけ考えるとよさそう。
　同じ位置を2回操作するのもxorなので意味がなさそうで、
　ある区間を3回かけて消すのは、1回にまとめられる(奇+奇+奇=奇なので)
　のでこれも意味がなさそう。
　ここまでをまとめると、被りのない0～2つの区間で消せるかどうかを
　確認できればよさそう、となる。
　(ここまでは自分でも考えた。かなり憶測の域を出てなかったけど)
・で、区間xorを0にするということで、これはzero sum rangesと同じ感じで、
　累積取っておくと同じ値の所のペアが0みたいのがxorでもできる。
　ここに辿り着けなかったのは残念…。
・値毎の隣接リストにindex入れとくやつを偶奇に分けてやっておくと、
　偶奇逆のリストでにぶたんすることで、
　ある区間内に偶奇逆で同じ値があったかどうかを判断できる。
・あとは色々場合分け頑張る。これもつらい。きっと自分じゃ詰め切れない。
　(ソース内コメントも参照。
　解法ツイートだけだと、答えが1になる2番目の条件が見つけられなかった。)
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
    ll N, Q;
    cin >> N >> Q;
    vector<ll> A(N);
    cin >> A;

    Accumulate<ll> acc(A);
    auto accxor = A;
    accxor.insert(accxor.begin(), 0);
    rep(i, N) {
        accxor[i+1] ^= accxor[i];
    }
    map<ll, vector<ll>> adj[2];
    rep(i, N+1) {
        adj[i%2][accxor[i]].eb(i);
    }

    rep(_, Q) {
        ll l, r;
        cin >> l >> r;
        l--;

        if (acc.query(l, r) == 0) {
            print(0);
        } else {
            ll len = r - l;
            ll val = accxor[r] ^ accxor[l];
            if (val == 0) {
                // 区間長が奇数なら一発で消せる
                if (len%2 == 1) {
                    print(1);
                // 偶数でも左端か右端が0なら1つずらして偶奇を変えられる
                } elif (A[l] == 0 or A[r-1] == 0) {
                    print(1);
                // それ以外
                } else {
                    // index偶奇が逆で(l,r)の範囲に、同じ値があればそこで区切れる
                    auto itr = upper_bound(ALL(adj[!(l%2)][accxor[l]]), l);
                    if (
                        itr != adj[!(l%2)][accxor[l]].end() and
                        *itr < r
                    ) {
                        print(2);
                    } else {
                        print(-1);
                    }
                }
            } else {
                print(-1);
            }
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
