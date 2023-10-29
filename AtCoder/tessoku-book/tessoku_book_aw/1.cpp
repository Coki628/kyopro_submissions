/*
・ビームサーチ
・とりあえずビーム幅1で本の貪欲想定スコアと同じだけ出ることを確認。
　それから本と同様にビーム幅を10000まで広げて、
　こちらも本と同等のスコアが無事出せた。
　ビームサーチはあんまりちゃんと使えた覚えがない
　(いい感じにスコア改善した覚えがあまりない)ので、ここでverifyできて良かったかな。
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

void solve() {
    const int N = 20;
    int T;
    cin >> T;
    vector<int> P(T), Q(T), R(T);
    rep(i, T) {
        cin >> P[i] >> Q[i] >> R[i];
        P[i]--, Q[i]--, R[i]--;
    }

    auto calc = [&](vector<int> &vec) {
        assert(vec.size() == N);
        return count(ALL(vec), 0);
    };
    auto restore = [&](vector<int> &ops) {
        int t = ops.size();
        vector<int> X(N);
        rep(i, t) {
            if (ops[i] == 0) {
                X[P[i]]++;
                X[Q[i]]++;
                X[R[i]]++;
            } else {
                X[P[i]]--;
                X[Q[i]]--;
                X[R[i]]--;
            }
        }
        return X;
    };

    int mxscore = 0;
    vector<int> mxops;
    const int BEAM_WIDTH = 10000;
    using state = pair<int, vector<int>>;
    priority_queue<state, vector<state>> cur_beam;
    cur_beam.push({0, {}});
    while (1) {
        priority_queue<state, vector<state>> nxt_beam;
        rep(_, BEAM_WIDTH) {
            if (cur_beam.empty()) break;
            auto [score, ops] = cur_beam.top();
            cur_beam.pop();
            int t = ops.size();
            // 既に終了状態
            if (t == T) continue;
            // 現在の配列Xの状態を作る
            auto X = restore(ops);
            // 今回の操作
            // op A
            auto nxx = X;
            nxx[P[t]]++;
            nxx[Q[t]]++;
            nxx[R[t]]++;
            int nxscore = score + calc(nxx);
            ops.pb(0);
            nxt_beam.push({nxscore, ops});
            ops.pop_back();
            // op B
            nxx = X;
            nxx[P[t]]--;
            nxx[Q[t]]--;
            nxx[R[t]]--;
            nxscore = score + calc(nxx);
            ops.pb(1);
            nxt_beam.push({nxscore, ops});
        }
        if (nxt_beam.empty()) break;
        cur_beam = nxt_beam;
        // 今一番いい状態を確認
        auto [score, ops] = cur_beam.top();
        if (ops.size() == T and mxscore < score) {
            mxscore = score;
            mxops = ops;
        }
    }

    vector<char> ans;
    rep(i, T) {
        if (mxops[i] == 0) {
            ans.pb('A');
        } else {
            ans.pb('B');
        }
    }
    print(ans, '\n');
    debug(mxscore);
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
