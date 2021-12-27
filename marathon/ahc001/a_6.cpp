/*
参考：https://www.terry-u16.net/entry/ahc001-how-to
・ヒューリスティック履修
・山登り、長方形の重複判定、焼きなまし
・引き続きてりーさんのを参考に。温度管理の方法とかはintroコンでwataさんがやってたやつとほぼ同じだった。
　T0,T1の値は違ってたから、それはてりーさんのに合わせた。
・色々バグ取りというか、設定値とか間違えてたから直して、さっきよりちょっとだけ上がって467億。
　とりあえず焼きなましまでやれたし、これでOKかな。
・温度の計算方法、gasinさんのやつに変えてみたらちょっと上がった。469億。
*/

#pragma region mytemplate

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#define _USE_MATH_DEFINES
#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ull = unsigned long long;
using ld = long double;
using pll = pair<ll, ll>;
using pii = pair<int, int>;
using pil = pair<int, ll>;
using vvl = vector<vector<ll>>;
using vvi = vector<vector<int>>;
using vvpll = vector<vector<pll>>;
using vvpil = vector<vector<pil>>;
#define name4(i, a, b, c, d, e, ...) e
#define rep(...) name4(__VA_ARGS__, rep4, rep3, rep2, rep1)(__VA_ARGS__)
#define rep1(i, a) for (ll i = 0, _aa = a; i < _aa; i++)
#define rep2(i, a, b) for (ll i = a, _bb = b; i < _bb; i++)
#define rep3(i, a, b, c) for (ll i = a, _bb = b; (c > 0 && a <= i && i < _bb) or (c < 0 && a >= i && i > _bb); i += c)
#define rrep(i, a, b) for (ll i=(a); i>(b); i--)
#define pb push_back
#define eb emplace_back
#define mkp make_pair
#define ALL(A) A.begin(), A.end()
#define UNIQUE(A) sort(ALL(A)), A.erase(unique(ALL(A)), A.end())
#define elif else if
#define tostr to_string
constexpr ll INF = 1e18;
// constexpr ll INF = LONG_LONG_MAX;
constexpr int MOD = 1000000007;
// constexpr int MOD = 998244353;

template<typename T> vector<vector<T>> list2d(int N, int M, T init) { return vector<vector<T>>(N, vector<T>(M, init)); }
template<typename T> vector<vector<vector<T>>> list3d(int N, int M, int L, T init) { return vector<vector<vector<T>>>(N, vector<vector<T>>(M, vector<T>(L, init))); }
template<typename T> vector<vector<vector<vector<T>>>> list4d(int N, int M, int L, int O, T init) { return vector<vector<vector<vector<T>>>>(N, vector<vector<vector<T>>>(M, vector<vector<T>>(L, vector<T>(O, init)))); }

template<typename T=ll> vector<T> LIST(ll N) { vector<T> A(N); rep(i, N) cin >> A[i]; return A; }

void print() { cout << '\n'; }
template<typename T> void print(T out) { cout << out << '\n'; }
template<typename T1, typename T2> void print(pair<T1, T2> out) { cout << out.first << ' ' << out.second << '\n'; }
template<typename T> void print(const vector<T> &A) { rep(i, A.size()) { cout << A[i]; if (i != A.size()-1) cout << ' '; } cout << '\n'; }
template<typename T> void print(const deque<T> &A) { vector<T> V(A.begin(), A.end()); print(V); }
template<typename T> void print(const set<T> &S) { vector<T> A(S.begin(), S.end()); print(A); }
#define debug(x) (cout << #x << ": ", print(x));

void Yes() { print("Yes"); }
void No() { print("No"); }
void YES() { print("YES"); }
void NO() { print("NO"); }

#pragma endregion

// [l,r)の範囲で乱数生成
mt19937_64 mt(chrono::steady_clock::now().time_since_epoch().count());
ll randrange(ll l, ll r) {
    uniform_int_distribution<ll> rand(l, r-1);
    return rand(mt);
}

const ll MX = 10000;

// 2つの閉区間seg1[l,r],seg2[l,r]から、重複を除いた長さを返す
ll merge_segment(pll seg1, pll seg2) {
    auto& [l1, r1] = seg1;
    auto& [l2, r2] = seg2;
    if (l1 > l2) {
        swap(l1, l2);
        swap(r1, r2);
    }
    ll ln1 = r1-l1+1;
    ll ln2 = r2-l2+1;
    if (ln1 <= 0 and ln2 <= 0) {
        return 0;
    } elif (ln2 <= 0 or l2 <= r1 and r2 <= r1) {
        return ln1;
    } elif (l2 <= r1 and r2 > r1) {
        return ln1 + ln2 - (r1-l2+1);
    } else {
        return ln1 + ln2;
    }
}

bool check(vector<array<ll, 4>> &ans, ll i) {
    auto [sx, sy, tx, ty] = ans[i];
    if (tx > MX or ty > MX) {
        return false;
    }
    rep(j, ans.size()) {
        auto [x1, y1, x2, y2] = ans[j];
        if (i == j) continue;
        if (
            merge_segment({sx, tx-1}, {x1, x2-1}) < (tx-sx)+(x2-x1) and
            merge_segment({sy, ty-1}, {y1, y2-1}) < (ty-sy)+(y2-y1)
        ) {
            return false;
        }
    }
    return true;
}

ll get_s(ll sx, ll sy, ll tx, ll ty) {
    return (tx-sx)*(ty-sy);
}
ll get_s(array<ll, 4> &v) {
    return get_s(v[0], v[1], v[2], v[3]);
}

ld calc(ll s, ll r) {
    return 1-pow(1-min(r, s)/(ld)max(r, s), 2);
}

bool valid(ll x, ll y, array<ll, 4> &v)  {
    auto& [sx, sy, tx, ty] = v;
    return (
        merge_segment({sx, tx-1}, {x, x}) < (tx-sx)+1 and
        merge_segment({sy, ty-1}, {y, y}) < (ty-sy)+1
    );
}

const int TL = 4900000;
const ld T0 = 0.00001;
const ld T1 = 0.0000001;

// 焼きなましに使う温度の計算
ld calc_temp(int elapsed) {
    ld t = elapsed / (ld)TL;
    if (t >= 1) {
        return -1;
    }
    return T0 + (T1-T0)*t;
    // return pow(T0, (1-t))*pow(T1, t);
}

// 焼きなましを踏まえた採用確率の計算
ld calc_prob(ld score, ld temp) {
    if (score > 0) {
        return 1;
    }
    return exp(score/temp);
}

void solve() {
    ll N;
    cin >> N;
    vector<ll> X(N), Y(N), R(N);
    rep(i, N) {
        cin >> X[i] >> Y[i] >> R[i];
    }
    vector<array<ll, 4>> ans(N);
    vector<ll> S(N, 1);
    ld cur = 0;
    rep(i, N) {
        ans[i] = {X[i], Y[i], X[i]+1, Y[i]+1};
        cur += calc(S[i], R[i]);
    }
    ll opcnt = 0;
    auto start = clock();
    auto elapsed = clock()-start;
    auto temp = calc_temp(elapsed);
    while (1) {
        // 温度の更新
        if (opcnt%100 == 0) {
            elapsed = clock()-start;
            temp = calc_temp(elapsed);
            if (temp == -1) break;
        }
        opcnt++;
        ll i = randrange(0, N);
        ll d = randrange(0, 4);
        ll op = randrange(0, 3);
        // 広げる
        if (op == 0) {
            ll len = randrange(1, 100);
            // 負方向
            if (d < 2) {
                if (ans[i][d]-len < 0) continue;
                ans[i][d] -= len;
                // 空いてるかチェック
                if (check(ans, i)) {
                    ld nxt = cur;
                    nxt -= calc(S[i], R[i]);
                    S[i] = get_s(ans[i]);
                    nxt += calc(S[i], R[i]);
                    // 良くなれば採用
                    if (nxt > cur) {
                        cur = nxt;
                    } else {
                        // 状態戻し
                        ans[i][d] += len;
                        S[i] = get_s(ans[i]);
                    }
                } else {
                    ans[i][d] += len;
                }
            // 正方向
            } else {
                if (ans[i][d]+len > MX) continue;
                ans[i][d] += len;
                if (check(ans, i)) {
                    ld nxt = cur;
                    nxt -= calc(S[i], R[i]);
                    S[i] = get_s(ans[i]);
                    nxt += calc(S[i], R[i]);
                    if (nxt > cur) {
                        cur = nxt;
                    } else {
                        ans[i][d] -= len;
                        S[i] = get_s(ans[i]);
                    }
                } else {
                    ans[i][d] -= len;
                }
            }
        // 移動
        } elif (op == 1) {
            ll len = randrange(1, 10);
            if (d < 2) {
                if (ans[i][d]-len < 0) continue;
                ans[i][d] -= len, ans[i][d+2] -= len;
                if (check(ans, i)) {
                    if (not valid(X[i], Y[i], ans[i])) {
                        ans[i][d] += len, ans[i][d+2] += len;
                    }
                } else {
                    ans[i][d] += len, ans[i][d+2] += len;
                }
            } else {
                if (ans[i][d]+len > MX) continue;
                ans[i][d] += len, ans[i][d-2] += len;
                if (check(ans, i)) {
                    if (not valid(X[i], Y[i], ans[i])) {
                        ans[i][d] -= len, ans[i][d-2] -= len;
                    }
                } else {
                    ans[i][d] -= len, ans[i][d-2] -= len;
                }
            }
        // 縮める
        } else {
            ll len = randrange(1, 10);
            // 正方向
            if (d < 2) {
                if (ans[i][d]+len >= ans[i][d+2]) continue;
                ans[i][d] += len;
                ld nxt = cur;
                nxt -= calc(S[i], R[i]);
                S[i] = get_s(ans[i]);
                nxt += calc(S[i], R[i]);
                // 焼きなましの評価によって採用を決める
                if (valid(X[i], Y[i], ans[i]) and calc_prob(nxt-cur, temp)*100 >= randrange(0, 100)) {
                    cur = nxt;
                } else {
                    // 状態戻し
                    ans[i][d] -= len;
                    S[i] = get_s(ans[i]);
                }
            // 負方向
            } else {
                if (ans[i][d]-len <= ans[i][d-2]) continue;
                ans[i][d] -= len;
                ld nxt = cur;
                nxt -= calc(S[i], R[i]);
                S[i] = get_s(ans[i]);
                nxt += calc(S[i], R[i]);
                if (valid(X[i], Y[i], ans[i]) and calc_prob(nxt-cur, temp)*100 >= randrange(0, 100)) {
                    cur = nxt;
                } else {
                    ans[i][d] += len;
                    S[i] = get_s(ans[i]);
                }
            }
        }
    }
    // print(opcnt);
    // print(cur);
    for (auto& a : ans) {
        rep(i, 4) {
            cout << a[i];
            if (i < 3) cout << ' ';
            else cout << '\n';
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
