/*
・ライブラリ：数え上げ
*/

#include "_tpl.cpp"


// Mod数え上げnCr
template<typename T>
struct ModTools {

    int MAX;
    vector<T> fact, factinv;

    ModTools() {};

    ModTools(int mx) {
        build(mx);
    }

    void build(int mx) {
        // nCrならn、nHrならn+rまで作る
        MAX = ++mx;
        fact.resize(MAX);
        factinv.resize(MAX);
        fact[0] = fact[1] = 1;
        rep(i, 2, MAX) {
            fact[i] = fact[i-1] * i;
        }
        factinv[MAX-1] = (T)1 / fact[MAX-1];
        rep(i, MAX-2, -1, -1) {
            factinv[i] = factinv[i+1] * (i+1);
        }
    }

    T nCr(int n, int r) {
        if (n < r) return 0;
        r = min(r, n-r);
        T num = fact[n];
        T den = factinv[r] * factinv[n-r];
        return num * den;
    }

    T nHr(int n, int r) {
        return nCr(r+n-1, r);
    }
};


// 任意Mod数え上げnCr
template<typename T>
struct AnyModTools {

    vector<pair<T, int>> factorize(T n) {
        vector<pair<T, int>> ret;
        for(T i=2; i*i<=n; i++) {
            int cnt = 0;
            while(n % i == 0) {
                n /= i;
                cnt++;
            }
            if(cnt) ret.emplace_back(i, cnt);
        }
        if(n > 1) ret.emplace_back(n, 1);
        return ret;
    }

    // 拡張ユークリッドの互除法(ax+by=gcd(a, b)の解を求める)
    T extgcd(T a, T b, T& x, T& y) {
        T d = a;
        if(b != 0){
            d = extgcd(b, a%b, y, x);
            y -= (a/b) * x;
        }else{
            x = 1; y = 0;
        }
        return d;
    }

    // MOD逆元(modが素数でなくても、aとmodが互いに素なら可)
    T inv_mod(T a, T mod) {
        T x, y;
        extgcd(a, mod, x, y);
        return (mod + x%mod) % mod;
    }

    const int64_t mod;
    // 素数冪を (p, c) で表現したもの
    vector<pair<int64_t, int>> primes;
    // 素数冪 p^c の実際の値
    vector<int64_t> ppow;
    // 階乗を (x, y) 形式で表現したもの
    vector<vector<pair<int64_t, int>>> fact;

    AnyModTools(int64_t mod, int MX) : mod(mod) {
        create_composite_mod_table(++MX, mod);
    }

    void add(int64_t& a, int64_t b, int64_t mod) {
        a = (a+b) % mod;
    }
    void mul(int64_t& a, int64_t b, int64_t mod) {
        a = a*b % mod;
    }

    // 素因数分解をして素数冪ごとにfactを前計算：O(√M+N*(Mの素因数の種類数))
    void create_composite_mod_table(int N, int64_t M) {
        primes = factorize(M);
        int sz = primes.size();
        ppow.resize(sz, 1);
        fact.resize(sz);
        for(int pi=0; pi<sz; pi++){
            int64_t p = primes[pi].first, cnt = primes[pi].second;
            while(cnt--) ppow[pi] *= p;

            auto& f = fact[pi];
            f.resize(N+1);
            f[0] = {1, 0};
            for(int i=1; i<=N; i++){
                f[i] = f[i-1];
                int n = i;
                while(n%p == 0){
                    n /= p;
                    f[i].second++;
                }
                mul(f[i].first, n, ppow[pi]);
            }
        }
    }

    // 素因数毎の二項係数を計算
    int64_t comb_mod(int n, int k, int pi) {
        auto &a = fact[pi][n], &b = fact[pi][k], &c = fact[pi][n-k];
        int64_t p = primes[pi].first, cnt = primes[pi].second;
        int64_t pp = ppow[pi];
        int pw = a.second - b.second - c.second;
        if(pw >= cnt) return 0;

        int64_t v = a.first;
        mul(v, inv_mod(b.first, pp), pp);
        mul(v, inv_mod(c.first, pp), pp);
        while(pw--) mul(v, p, pp);
        return v;
    }

    // 二項係数nCrの計算：O(modの素因数の種類数)
    int64_t nCr(int n, int k) {
        int64_t res = 1;
        rep(i, primes.size()) {
            mul(res, comb_mod(n, k, i), mod);
        }
        return res;
    }
};


// 順列全列挙
template<typename T>
vector<vector<T>> permutations(vector<T> &A, int N=-1) {

    if (N == -1) N = A.size();
    int M = A.size();
    vector<vector<T>> comb;
    rep(bit, 0, 1<<M) {
        if (popcount(bit) != N) continue;
        vector<T> res;
        rep(i, 0, M) {
            if (bit>>i & 1) {
                res.pb(A[i]);
            }
        }
        comb.pb(res);
    }

    vector<vector<T>> res;
    for (auto &perm : comb) {
        sort(ALL(perm));
        do {
            res.pb(perm);
        } while (next_permutation(ALL(perm)));
    }
    return res;
}


// 組み合わせ全列挙
template<typename T>
vector<vector<T>> combinations(vector<T> &A, int N) {
    int M = A.size();
    vector<vector<T>> res;
    auto rec = [&](auto&& f, vector<T> &cur, ll x, ll n) -> void {
        if (n == N) {
            res.pb(cur);
            return;
        }
        rep(i, x, M) {
            cur.pb(A[i]);
            f(f, cur, i+1, n+1);
            cur.pop_back();
        }
    };
    vector<T> cur;
    rec(rec, cur, 0, 0);
    return res;
}


// 重複組み合わせ全列挙
template<typename T>
vector<vector<T>> combinations_with_replacement(vector<T> &A, int N) {
    int M = A.size();
    vector<vector<T>> res;
    auto rec = [&](auto&& f, vector<T> &cur, ll x, ll n) -> void {
        if (n == N) {
            res.pb(cur);
            return;
        }
        rep(i, x, M) {
            cur.pb(A[i]);
            f(f, cur, i, n+1);
            cur.pop_back();
        }
    };
    vector<T> cur;
    rec(rec, cur, 0, 0);
    return res;
}


// 階乗(modなし)
template<typename T>
T factorial(T x) {
    T res = 1;
    for (T i=1; i<=x; i++) res *= i;
    return res;
}


// nCr(modなし)
ll nCr(int n, int r) {
    auto dp = list2d(n+1, r+1, 0LL);
    dp[0][0] = 1;
    rep(i, 1, n+1) {
        dp[i][0] = 1;
        rep(j, 1, r+1) {
            dp[i][j] = (dp[i-1][j-1] + dp[i-1][j]);
        }
    }
    return dp[n][r];
}


// スターリング数(玉区別あり、箱区別なし、1個以上) ※未Verify
ll stirling(int N, int K) {
    auto dp = list2d(N+1, K+1, 0LL);
    dp[0][0] = 1;
    rep(i, 1, N+1) {
        rep(k, 1, K+1) {
            dp[i][k] = dp[i-1][k-1] + k*dp[i-1][k];
        }
    }
    return dp[N][K];
}


// ベル数(玉区別あり、箱区別なし、制限なし) ※未Verify
ll bell(int N, int K) {
    ll ans = 0;
    rep(i, K+1) {
        ans += stirling(N, i);
    }
    return ans;
}


// ベル数(玉区別あり、箱区別なし、制限なし) ※未Verify
mint bell(int N, int K) {

    ModTools<mint> mt(max(N, K));

    // 前計算しておく
    vector<mint> prev(K+1);
    rep(i, 0, K+1) {
        prev[i] = (mint)1/mt.fact[i];
    }
    // 累積和
    rep(i, 1, K+1) {
        prev[i] += prev[i-1];
    }

    mint ans = 0;
    rep(i, 0, K+1) {
        ans += (mint)pow(i, N, MOD)/mt.fact[i]*prev[K-i];
    }
    return ans;
}


// 分割数(玉区別なし、箱区別なし、制限なし) ※未Verify
ll partition(int N, int K) {
    // dp[i][j] := jのi分割の総数
    auto dp = list2d(K+1, N+1, 0LL);
    dp[0][0] = 1;
    rep(i, 1, K+1) {
        rep(j, 0, N+1) {
            dp[i][j] += dp[i-1][j];
            if (j - i >= 0) {
                dp[i][j] += dp[i][j-i];
            }
            dp[i][j] %= MOD;
        }
    }
    return dp[K][N];
}


// 参考：https://ei1333.github.io/library/math/combinatorics/mod-int.cpp
// ModInt
template<int mod>
struct ModInt {
    int x;

    ModInt() : x(0) {}

    ModInt(int64_t y) : x(y >= 0 ? y % mod : (mod - (-y) % mod) % mod) {}

    ModInt &operator+=(const ModInt &p) {
        if((x += p.x) >= mod) x -= mod;
        return *this;
    }

    ModInt &operator-=(const ModInt &p) {
        if((x += mod - p.x) >= mod) x -= mod;
        return *this;
    }

    ModInt &operator*=(const ModInt &p) {
        x = (int) (1LL * x * p.x % mod);
        return *this;
    }

    ModInt &operator/=(const ModInt &p) {
        *this *= p.inverse();
        return *this;
    }

    ModInt operator-() const { return ModInt(-x); }

    ModInt operator+(const ModInt &p) const { return ModInt(*this) += p; }

    ModInt operator-(const ModInt &p) const { return ModInt(*this) -= p; }

    ModInt operator*(const ModInt &p) const { return ModInt(*this) *= p; }

    ModInt operator/(const ModInt &p) const { return ModInt(*this) /= p; }

    bool operator==(const ModInt &p) const { return x == p.x; }

    bool operator!=(const ModInt &p) const { return x != p.x; }

    ModInt inverse() const {
        int a = x, b = mod, u = 1, v = 0, t;
        while(b > 0) {
            t = a / b;
            swap(a -= t * b, b);
            swap(u -= t * v, v);
        }
        return ModInt(u);
    }

    ModInt pow(int64_t n) const {
        ModInt ret(1), mul(x);
        while(n > 0) {
            if(n & 1) ret *= mul;
            mul *= mul;
            n >>= 1;
        }
        return ret;
    }

    friend ostream &operator<<(ostream &os, const ModInt &p) {
        return os << p.x;
    }

    friend istream &operator>>(istream &is, ModInt &a) {
        int64_t t;
        is >> t;
        a = ModInt< mod >(t);
        return (is);
    }

    static int get_mod() { return mod; }
};
using mint = ModInt<MOD>;


// 参考：https://ei1333.github.io/library/math/combinatorics/arbitrary-mod-int.cpp
// 任意ModInt
struct ArbitraryModInt {

    int x;

    ArbitraryModInt() : x(0) {}

    ArbitraryModInt(int64_t y) : x(y >= 0 ? y % get_mod() : (get_mod() - (-y) % get_mod()) % get_mod()) {}

    static int &get_mod() {
        static int mod = 0;
        return mod;
    }

    static void set_mod(int md) {
        get_mod() = md;
    }

    ArbitraryModInt &operator+=(const ArbitraryModInt &p) {
        if((x += p.x) >= get_mod()) x -= get_mod();
        return *this;
    }

    ArbitraryModInt &operator-=(const ArbitraryModInt &p) {
        if((x += get_mod() - p.x) >= get_mod()) x -= get_mod();
        return *this;
    }

    ArbitraryModInt &operator*=(const ArbitraryModInt &p) {
        unsigned long long a = (unsigned long long) x * p.x;
        unsigned xh = (unsigned) (a >> 32), xl = (unsigned) a, d, m;
        asm("divl %4; \n\t" : "=a" (d), "=d" (m) : "d" (xh), "a" (xl), "r" (get_mod()));
        x = m;
        return *this;
    }

    ArbitraryModInt &operator/=(const ArbitraryModInt &p) {
        *this *= p.inverse();
        return *this;
    }

    ArbitraryModInt operator-() const { return ArbitraryModInt(-x); }

    ArbitraryModInt operator+(const ArbitraryModInt &p) const { return ArbitraryModInt(*this) += p; }

    ArbitraryModInt operator-(const ArbitraryModInt &p) const { return ArbitraryModInt(*this) -= p; }

    ArbitraryModInt operator*(const ArbitraryModInt &p) const { return ArbitraryModInt(*this) *= p; }

    ArbitraryModInt operator/(const ArbitraryModInt &p) const { return ArbitraryModInt(*this) /= p; }

    bool operator==(const ArbitraryModInt &p) const { return x == p.x; }

    bool operator!=(const ArbitraryModInt &p) const { return x != p.x; }

    ArbitraryModInt inverse() const {
        int a = x, b = get_mod(), u = 1, v = 0, t;
        while(b > 0) {
            t = a / b;
            swap(a -= t * b, b);
            swap(u -= t * v, v);
        }
        return ArbitraryModInt(u);
    }

    ArbitraryModInt pow(int64_t n) const {
        ArbitraryModInt ret(1), mul(x);
        while(n > 0) {
            if(n & 1) ret *= mul;
            mul *= mul;
            n >>= 1;
        }
        return ret;
    }

    friend ostream &operator<<(ostream &os, const ArbitraryModInt &p) {
        return os << p.x;
    }

    friend istream &operator>>(istream &is, ArbitraryModInt &a) {
        int64_t t;
        is >> t;
        a = ArbitraryModInt(t);
        return (is);
    }
};


// 参考：https://ferin-tech.hatenablog.com/entry/2019/08/11/%E3%83%A9%E3%82%B0%E3%83%A9%E3%83%B3%E3%82%B8%E3%83%A5%E8%A3%9C%E9%96%93
// 　　　https://ei1333.github.io/library/math/combinatorics/lagrange-polynomial.cpp
// 使い方
// ・引数：x=0,1,2...の時のyを格納したリストと、求めたいf(t)のt
// ・戻り値：f(t)の時の値
// ・計算量：O(Nlog(mod)) ※階乗逆元をちゃんと前計算してればO(N)っぽい。
// ラグランジュ補間：値を求める
template<typename T>
T lagrange_polynomial(const vector<T> &y, int64_t t) {
    int N = y.size() - 1;
    ModTools<T> mt(N);
    if(t <= N) return y[t];
    T ret(0);
    vector< T > dp(N + 1, 1), pd(N + 1, 1);
    for(int i = 0; i < N; i++) dp[i + 1] = dp[i] * (t - i);
    for(int i = N; i > 0; i--) pd[i - 1] = pd[i] * (t - i);
    for(int i = 0; i <= N; i++) {
        T tmp = y[i] * dp[i] * pd[i] * mt.factinv[i] * mt.factinv[N-i];
        if((N - i) & 1) ret -= tmp;
        else ret += tmp;
    }
    return ret;
}


// 参考：https://ferin-tech.hatenablog.com/entry/2019/08/11/%E3%83%A9%E3%82%B0%E3%83%A9%E3%83%B3%E3%82%B8%E3%83%A5%E8%A3%9C%E9%96%93
// 　　　https://ei1333.github.io/library/math/combinatorics/lagrange-polynomial-2.cpp
// 使い方
// ・引数：y=f(x)の(x,y)のペアを格納したリストX,Y
// ・戻り値：f(x)=ax^0+bx^1+cx^2+...のa,b,c...を格納したリスト
// ・計算量：O(N^2)
// ラグランジュ補間：係数を求める
template<typename T>
vector<T> lagrange_polynomial(const vector<T> &x, const vector<T> &y) {
    int k = (int) x.size() - 1;

    vector<T> f(k + 1), dp(k + 2);
    dp[0] = 1;
    for(int j = 0; j <= k; j++) {
        for(int l = k + 1; l > 0; l--) {
            dp[l] = dp[l] * -x[j] + dp[l - 1];
        }
        dp[0] *= -x[j];
    }

    for(int i = 0; i <= k; i++) {
        T d = 1;
        for(int j = 0; j <= k; j++) {
            if(i != j) {
                d *= x[i] - x[j];
            }
        }
        T mul = y[i] / d;
        if(x[i] == 0) {
            for(int j = 0; j <= k; j++) {
                f[j] += dp[j + 1] * mul;
            }
        } else {
            T inv = T(1) / (-x[i]), pre = 0;
            for(int j = 0; j <= k; j++) {
                T cur = (dp[j] - pre) * inv;
                f[j] += cur * mul;
                pre = cur;
            }
        }
    }
    return f;
}
