/*
参考：https://qiita.com/tsukammo/items/7041a00e429f9f5ac4ae
・マラソン精進
・山登り、高速化、グリッド斜め移動
・更新の再計算パートを改善。ツカモさんの記事でやり方見た。
　中心からそこを囲むように、ダイヤ型の領域は更新する値が一緒なので、
　そこに沿って進めるような4方向のdx,dyを用意しておく。
　で、値の大きさによって、どのくらい外側までそれを広げるかを調整。
　添字合わせがめちゃだるくて泣きそうになった。
・でも4方向のループを外側に置くことで、回る長さを大きくしながら進んでいくのは
　言われたら確かにそれで出来るんだけど、多分やったことなくて新しい知見だったな。
・操作回数が500ないくらいだったのが10万以上に増えた。
　でもスコアはほぼ変わらず、97.7億くらい。
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

ll ceil(ll a, ll b) { if (a >= 0) return (a+b-1) / b; else return a / b; }

#pragma endregion

// [l,r)の範囲で乱数生成
mt19937_64 mt(chrono::steady_clock::now().time_since_epoch().count());
ll randrange(ll l, ll r) {
    uniform_int_distribution<ll> rand(l, r-1);
    return rand(mt);
}

// 斜め移動用(右下→右上→左上→左下みたいにダイヤ型に進む)
const vector<pii> directions = {{1, 1}, {-1, 1}, {-1, -1}, {1, -1}};

const int TL = 5900000;
const int N = 100;
const int Q = 1000;
int A[N][N], B[N][N];

ll calc_all() {
    ll res = 0;
    rep(i, N) {
        rep(j, N) {
            res += abs(B[i][j]-A[i][j]);
        }
    }
    return res;
}

ll add(ll x, ll y, ll h) {
    ll diff = 0;
    diff -= abs(B[x][y]-A[x][y]);
    B[x][y] += h;
    diff += abs(B[x][y]-A[x][y]);
    rep(i, 1, h) {
        ll nx = x;
        ll ny = y-i;
        for (auto [dx, dy] : directions) {
            rep(j, i) {
                nx += dx;
                ny += dy;
                if (nx < 0 or ny < 0 or nx >= N or ny >= N) continue;
                diff -= abs(B[nx][ny]-A[nx][ny]);
                B[nx][ny] += h-i;
                diff += abs(B[nx][ny]-A[nx][ny]);
            }
        }
    }
    return diff;
}
ll add(vector<ll> &v) {
    return add(v[0], v[1], v[2]);
}

ll remove(ll x, ll y, ll h) {
    ll diff = 0;
    diff -= abs(B[x][y]-A[x][y]);
    B[x][y] -= h;
    diff += abs(B[x][y]-A[x][y]);
    rep(i, 1, h) {
        ll nx = x;
        ll ny = y-i;
        for (auto [dx, dy] : directions) {
            rep(j, i) {
                nx += dx;
                ny += dy;
                if (nx < 0 or ny < 0 or nx >= N or ny >= N) continue;
                diff -= abs(B[nx][ny]-A[nx][ny]);
                B[nx][ny] -= h-i;
                diff += abs(B[nx][ny]-A[nx][ny]);
            }
        }
    }
    return diff;
}
ll remove(vector<ll> &v) {
    return remove(v[0], v[1], v[2]);
}

void solve() {
    auto start = clock();
    ll score = 200000000;
    rep(i, N) {
        rep(j, N) {
            cin >> A[i][j];
            score -= A[i][j];
        }
    }

    // 初期解(ランダム)
    vvl ans(Q);
    rep(i, Q) {
        ll x = randrange(0, N);
        ll y = randrange(0, N);
        ll h = randrange(1, N+1);
        ans[i] = {x, y, h};
        score -= add(x, y, h);
    }

    // 山登り
    auto elapsed = clock()-start;
    ll opcnt = 0;
    while (1) {
        if (opcnt%100 == 0) {
            elapsed = clock()-start;
            if (elapsed >= TL) break;
        }
        opcnt++;

        ll i = randrange(0, Q);
        ll x = randrange(0, N);
        ll y = randrange(0, N);
        ll h = randrange(1, N+1);
        ll diff = 0;
        diff += remove(ans[i]);
        diff += add(x, y, h);
        if (diff < 0) {
            ans[i] = {x, y, h};
            score -= diff;
        } else {
            remove(x, y, h);
            add(ans[i]);
        }
    }
    // print(opcnt);
    // print(score);
    print(Q);
    for (auto& a : ans) print(a);
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
