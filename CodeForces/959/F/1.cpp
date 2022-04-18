/*
参考：https://codeforces.com/blog/entry/58712
・dojo set_e_6_6
・自力ならず。むずい。
・XORの性質、XORの部分和DP
・まともに2乗かけてやるならXOR版の部分和DPみたいのをやればいいけど、
　当然それは間に合わないので何とかする。
・取り得る状態の種類を考える。既に集合に存在する状態であれば、
　それを何とxorしても、それは既にやった操作のはずで、通り数は増えない。
　逆に、これは非自明だと思うんだけど、存在しない状態を、
　今ある状態とXORすると、被りなく全て新しい状態が増える。
　これは、XORがa^b=cであることから、追加する要素をaとして、
　結果として現れるcがもし集合に存在しているなら、
　bも存在していないとおかしい、といった話からなる。(多分)
・で、存在する要素を追加した時、何がどのくらい増えるのかというと、
　全部2倍になる。これは、dp[i+1][x] = dp[i][x] + dp[x^A[i]] みたいな遷移で、
　dp[i][x]とdp[x^A[i]]が常に同じ値を取っているから。
　この先は何かよく分かんないんだけど、新規追加された要素は、
　今まであった要素と同じ数からスタートするみたい。
　多分、部分集合全部やるといい感じに均等になるからだと思うんだけど、お気持ち…。
・さて考察はだいたいこんな感じで、まとめると、
　既存の要素が来たら通り数2倍、新規要素が来たら集合の全要素とxorして集合に全部追加、
　答えはいつものクエリ先読み、ってやればいい。
・でもこの考察導くのはかなり困難な感じがして、結局部分和DPして実験すると、
　答えが全部、0かある2冪のどちらかしかないってのは分かるので、
　そこからどういう時に集合が増えて、どういう時に2倍されるのか、
　みたいのを当たっていくのがまあ現実的な気はする…。
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

void solve() {
    ll N, Q;
    cin >> N >> Q;
    auto A = LIST(N);
    vvpll qs(N);
    rep(i, Q) {
        ll l, x;
        cin >> l >> x;
        l--;
        qs[l].eb(x, i);
    }

    // ll M = 1LL<<bit_length(max(A));
    // auto dp = list2d<mint>(N+1, M, 0);
    // dp[0][0] = 1;
    // rep(i, N) {
    //     rep(j, M) {
    //         dp[i+1][j] += dp[i][j];
    //         dp[i+1][j^A[i]] += dp[i][j];
    //     }
    // }
    // // 答えは全部、0かある2冪のどちらか
    // print(dp[N]);

    ll M = 1LL<<20;
    mint val = 1;
    vector<bool> has(M);
    has[0] = 1;
    vector<ll> cur = {0};
    vector<mint> ans(Q);
    rep(i, N) {
        if (has[A[i]]) {
            // 今あるxの通り数が全て2倍に
            val *= 2;
        } else {
            vector<ll> nxt;
            for (auto x : cur) {
                // 今あるxとのxorは全て新規追加となる
                has[x^A[i]] = 1;
                nxt.eb(x^A[i]);
            }
            cur = concat(cur, nxt);
        }
        for (auto [x, j] : qs[i]) {
            ans[j] = has[x] ? val : 0;
        }
    }
    for (auto a : ans) print(a);
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
