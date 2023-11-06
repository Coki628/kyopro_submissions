/*
・ビームサーチ
・終了後、評価方法を変えるのを試してみる。
　「山の最小値が最大の場所」にしてみた。
　割と良さそうだったけど、たまにアホみたいなことしてた
　(ノーコストで回収できる手をあえて使ってない)ので、原因を探ってみた。
　すると、その次の手番以降で評価がいいとそっちのルートに独占されてしまう
　みたいなことが起きてるっぽくて、ビーム幅を1にしたら想定される貪欲になった。
　こういう時はどうやって対処したらいいんだろうな…。
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#define CONSTANTS
#define __LOCAL
#include "base.hpp"

constexpr long long INF = 1e18;
// constexpr long long INF = LONG_LONG_MAX;
// constexpr int MOD = 1000000007;
constexpr int MOD = 998244353;
constexpr long double EPS = 1e-10;
constexpr long double PI = M_PI;

#include "macros.hpp"

#include "common/input.hpp"
#include "common/print.hpp"
#include "common/listnd.hpp"
#include "common/chmin.hpp"
#include "common/chmax.hpp"
#include "common/randrange.hpp"
#include "common/Timer.hpp"
#include "grid/constants/directions.hpp"
#include "string/zfill.hpp"
#include "string/number_format.hpp"

#include "common/subarray.hpp"
#include "common/min.hpp"

auto solve(int testcase = -1) {
    Timer timer;
#ifdef __LOCAL
#ifdef __DEBUG
    string basedir = "tools/";
#else
    string basedir = "../tools/";
#endif
    // 入力ファイル読み込み
    string filename = basedir + "in/" + zfill(tostr(testcase), 4) + ".txt";
    freopen(filename.c_str(), "r", stdin);
    // 出力ファイル準備
    filename = basedir + "out/" + zfill(tostr(testcase), 4) + ".txt";
    ofstream ofs(filename.c_str());
    if (!ofs) {
        print("error, please check if '" + basedir + "out/' dir exists");
        exit(0);
    }
#endif
    const int N = 200, M = 10, K = N / M;
    int tmp;
    cin >> tmp >> tmp;
    auto box = listnd(M, K, 0);
    rep(i, M) {
        rep(j, K) {
            cin >> box[i][j];
            box[i][j]--;
        }
    }

    vector<pii> ans;
    auto calc = [](int v) {
        return max(1, 10000 - v);
    };
    auto calc_wait = [](vector<int>& pile) -> int {
        if (pile.empty()) {
            return MOD;
        }
        return min(pile) + 1;
    };
    // 箱iを見つける、山jと位置kを返す
    auto find = [&](int i, vvi& box) -> pii {
        rep(j, M) {
            rep(k, box[j].size()) {
                if (box[j][k] == i) {
                    return {j, k};
                }
            }
        }
        assert(0);
    };
    // 山fromのk番目以降を山toへ移動
    auto op1 = [&](int from, int to, int k, vector<pii>& ops, vvi& box) {
        ops.eb(box[from][k] + 1, to + 1);
        int sz = box[from].size();
        auto tmp = subarray(box[from], k, sz);
        for (auto v : tmp) {
            box[to].eb(v);
        }
        rep(_, sz - k) {
            box[from].pop_back();
        }
        // コストを返却
        return tmp.size() + 1;
    };
    // 山mから箱vを回収する
    auto op2 = [&](int m, int v, vector<pii>& ops, vvi& box) {
        ops.eb(v + 1, 0);
        assert(box[m].back() == v);
        box[m].pop_back();
    };

    int mncost = MOD;
    vector<pii> mxops;
    const int BEAM_WIDTH = 1;
    using state = tuple<int, int, int>;
    priority_queue<state, vector<state>> cur_beam;
    cur_beam.push({0, 0, 0});
    vector<pair<vector<pii>, vvi>> vec = {{{}, box}};
    while (1) {
        priority_queue<state, vector<state>> nxt_beam;
        vector<pair<vector<pii>, vvi>> nxvec;
        int nxid = 0;
        rep(_, BEAM_WIDTH) {
            if (cur_beam.empty()) break;
            auto [wait, cost, id] = cur_beam.top();
            auto& [ops, curbox] = vec[id];
            cur_beam.pop();
            // 最後に回収した箱
            int i = ops.size() ? ops.back().first : 0;
            // 既に終了状態
            if (i == N) {
                if (cost < mncost) {
                    mncost = cost;
                    mxops = ops;
                }
                continue;
            }
            // 今回の操作
            auto [m, k] = find(i, curbox);
            if (k < curbox[m].size() - 1) {
                rep(nxt, M) {
                    if (nxt == m) continue;
                    // int nxwait = curbox[nxt].size();
                    int nxwait = calc_wait(curbox[nxt]);
                    auto tmp = curbox;
                    int nxcost = op1(m, nxt, k + 1, ops, curbox);
                    op2(m, i, ops, curbox);
                    nxt_beam.push({nxwait, cost + nxcost, nxid});
                    nxid++;
                    nxvec.eb(ops, curbox);
                    // 状態戻し
                    curbox = tmp;
                    ops.pop_back();
                    ops.pop_back();
                }
            } else {
                op2(m, i, ops, curbox);
                nxt_beam.push({MOD, cost, nxid});
                nxid++;
                nxvec.eb(ops, curbox);
            }
        }
        if (nxt_beam.empty()) break;
        cur_beam = move(nxt_beam);
        vec = move(nxvec);
    }

    ll mxscore = calc(mncost);
    ans = mxops;

    for (auto [v, i] : ans) {
#ifdef __LOCAL
        ofs << v << ' ' << i << endl;
#else
        cout << v << ' ' << i << endl;
#endif
    }

    return mxscore;
}

// テスト番号指定
vector<int> gen_cases1(const vector<int> &T) {
    return T;
}

// sからn件実施
vector<int> gen_cases2(int s, int n) {
    vector<int> T;
    rep(i, s, s + n) {
        T.eb(i);
    }
    return T;
}

// [s,t)を実施
vector<int> gen_cases3(int s, int t) {
    vector<int> T;
    rep(i, s, t) {
        T.eb(i);
    }
    return T;
}

// [s,t)の範囲でランダムにn件実施
vector<int> gen_cases4(int s, int t, int n) {
    vector<int> T;
    rep(i, s, t) {
        T.eb(i);
    }
    shuffle(ALL(T), mt);
    return vector<int>(T.begin(), T.begin() + n);
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);
    cout << fixed << setprecision(15);

#ifdef __LOCAL
    // テスト番号指定
    // auto T = gen_cases1({0});
    // sからn件実施
    auto T = gen_cases2(0, 20);
    // [s,t)を実施
    // auto T = gen_cases3(0, 100);
    // [s,t)の範囲でランダムにn件実施
    // auto T = gen_cases4(0, 100, 20);

    ll totalscore = 0;
    for (int t : T) {
        cout << "case #" << t << " start" << endl;
        auto score = solve(t);
        cout << "case #" << t << " score: ";
        print(number_format(score));
        cout << endl;
        totalscore += score;
    }
    cout << "total score: ";
    print(number_format(totalscore));
#else
    solve();
#endif

    return 0;
}
