/*
・ライブラリ：整数
*/

#include "_tpl.cpp"


ll gcd(ll a, ll b) { return __gcd(a, b); }
ll lcm(ll x, ll y) { return (x * y) / gcd(x, y); }


// 素因数分解(vectorベース)
template<typename T>
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


// 約数列挙
vector<ll> divisors(ll n) {
    vector<ll> res;
    for (ll i=1; i*i<=n; i++) {
        if (n%i == 0) {
            res.pb(i);
            if (n/i != i) res.pb(n/i);
        }
    }
    // sort(ALL(res));
    return res;
}


// N進数文字列Sを10進数に
ll ntod(string S, ll n) {
    ll res = 0, k = 1;
    reverse(ALL(S));
    for (char &c : S) {
        res += k*toint(c);
        k *= n;
    }
    return res;
}


// 10進数をN進数文字列に(負数対応版)
string dton(ll num, ll n, char base='0') {
    string res;
    while (abs(num) > 0) {
        ll m = num % abs(n);
        num -= m;
        res += base+m;
        num /= n;
    }
    reverse(ALL(res));
    if (res != "") {
        return res;
    } else {
        return res+base;
    }
}
// 旧版
// string dton(ll num, ll n) {
//     string res;
//     ll m;
//     while (num > 0) {
//         tie(num, m) = divmod(num, n);
//         res += tochar(m);
//     }
//     reverse(ALL(res));
//     if (res != "") {
//         return res;
//     } else {
//         return "0";
//     }
// }


// 整数で正確にsqrtを返す
ll isqrt(ll n, bool ceil=false) {
    ll ok = 0;
    ll ng = 3037000500;
    while (ng - ok > 1) {
        ll m = ok + (ng - ok) / 2;
        if (m * m <= n) {
            ok = m;
        } else {
            ng = m;
        }
    }
    if (ceil and ok*ok != n) ok++;
    return ok;
}


// 桁和：O(logN)
ll digit_sum(ll n) {
    ll res = 0;
    while (n > 0) {
        res += n % 10;
        n /= 10;
    }
    return res;
}
// 桁和：O(|S|)(未verify)
ll digit_sum(string S) {
    ll res = 0;
    rep(i, S.size()) {
        res += toint(S[i]);
    }
    return res;
}










////////// end template included here //////////











// エラトステネスの篩
struct Eratosthenes {

    int n;
    bool loglog;
    vector<bool> prime;
    vector<ll> minfactor, cntfactor, cntdivisor, sumdivisor;
    vector<int> mobius;

    Eratosthenes(int n, bool loglog=true) : n(n), loglog(loglog) {
        prime.assign(n+1, true);
        minfactor.assign(n+1, 0);
        cntfactor.assign(n+1, 0);
        mobius.assign(n+1, 1);
        if (not loglog) {
            cntdivisor.assign(n+1, 1);
            sumdivisor.assign(n+1, 1);
        }
        prime[0] = prime[1] = false;
        minfactor[1] = 1;
        rep(i, 2, n+1) {
            if (not loglog) {
                for (ll j=i; j<=n; j+=i) {
                    cntdivisor[j]++;
                    sumdivisor[j] += i;
                }
            }
            if (not prime[i]) continue;
            minfactor[i] = i;
            cntfactor[i]++;
            mobius[i] = -1;
            for (ll j=i+i; j<=n; j+=i) {
                prime[j] = false;
                minfactor[j] = i;
                cntfactor[i]++;
                // iで2回以上割り切れるものを0に
                if (j/i%i == 0) {
                    mobius[j] = 0;
                } else {
                    mobius[j] = -mobius[j];
                }
            }
        }
    }

    bool is_prime(ll x) {
        assert(x <= n);
        return prime[x];
    }

    // 高速素因数分解(osa_k法)
    vector<pair<ll, int>> factorize(ll x) {
        assert(x <= n);
        vector<pair<ll, int>> res;
        while (x > 1) {
            int p = minfactor[x];
            int cnt = 0;
            while (minfactor[x] == p) {
                x /= p;
                cnt++;
            }
            res.pb({p, cnt});
        }
        return res;
    }

    // 高速約数列挙(未verify)
    vector<ll> divisors(int n) {
        vector<ll> res = {1};
        auto fact = factorize(n);
        for (auto [p, cnt] : fact) {
            ll m = res.size();
            rep(i, m) {
                int v = 1;
                rep(j, cnt) {
                    v *= p;
                    res.pb(res[i] * v);
                }
            }
        }
        return res;
    }

    // 素因数の種類数(未verify)
    vector<ll> get_cntfactor() {
        return cntfactor;
    }

    // 約数の個数(未verify)
    vector<ll> get_cntdivisor() {
        assert(not loglog);
        return cntdivisor;
    }

    // 約数の総和(未verify)
    vector<ll> get_sumdivisor() {
        assert(not loglog);
        return sumdivisor;
    }

    // メビウス関数
    vector<int> get_mobius() {
        return mobius;
    }
};


// 等差数列の和：(初項l, 末項r, 項数n)
template<typename T> 
T arithmetic_sequence_sum(T l, T r, T n) {
    return (l+r)*n/2;
}
// 等差数列の和：(初項a, 公差d, 項数n)
template<typename T> 
T arithmetic_sequence_sum(T a, T d, T n) {
    return (a*2+(n-1)*d)*n/2;
}


// 素数判定：O(√num)
bool is_prime(ll num) {
    if (num < 2) {
        return false;
    }
    if (set<ll>({2, 3, 5}).count(num)) {
        return true;
    }
    if (num%2 == 0 or num%3 == 0 or num%5 == 0) {
        return false;
    }
    // 疑似素数(2でも3でも割り切れない数字)で次々に割っていく
    ll prime = 7;
    ll step = 4;
    ll num_sqrt = sqrt(num);
    while (prime <= num_sqrt) {
        if (num%prime == 0) {
            return false;
        }
        prime += step;
        step = 6-step;
    }
    return true;
}


// 素数列挙(エラトステネスの篩)(旧)
vector<ll> eratosthenes_sieve(ll n) {
    vector<bool> table(n+1);
    vector<ll> primes;
    rep(i, 2, n+1) {
        if (table[i] == 0) {
            primes.pb(i);
            for (ll j=i+i; j<=n; j+=i) {
                table[j] = 1;
            }
        }
    }
    return primes;
}


// 素因数分解(mapベース)(旧)
map<ll, ll> factorize(ll x) {
    map<ll, ll> res;
    for (ll i=2; i*i<=x; i++) {
        while (x%i == 0) {
            x /= i;
            res[i]++;
        }
        if (x == 1) break;
    }
    if (x != 1) res[x]++;
    return res;
}


// 高速素因数分解(osa_k法)、前計算
vector<ll> eratosthenes_sieve(ll n) {
    vector<ll> table(n+1);
    table[1] = 1;
    rep(i, 2, n+1) {
        if (table[i] == 0) {
            for (ll j=i; j<=n; j+=i) {
                table[j] = i;
            }
        }
    }
    return table;
}

// 高速素因数分解(osa_k法)(mapベース)
map<ll, ll> factorize(vector<ll> &table, ll x) {
    map<ll, ll> res;
    while (x != table[x]) {
        res[table[x]]++;
        x /= table[x];
    }
    if (x != 1) {
        res[x]++;
    }
    return res;
}

// 高速素因数分解(osa_k法)(vectorベース)
vector<pair<ll, int>> factorize(const vector<ll> &minfactor, ll x) {
    vector<pair<ll, int>> res;
    while (x > 1) {
        int p = minfactor[x];
        int cnt = 0;
        while (minfactor[x] == p) {
            x /= p;
            cnt++;
        }
        res.pb({p, cnt});
    }
    return res;
}


// ピタゴラス数(未整備。重複削除とかgcdで互いに素とか考えてない。)
vector<ll> calc(ll m, ll n) {
    ll a = abs(pow(m, 2) - pow(n, 2));
    ll b = 2*m*n;
    ll c = pow(m, 2) + pow(n, 2);
    vector<ll> res = {a, b, c};
    sort(ALL(res));
    return res;
}


// 拡張ユークリッドの互除法(ax+by=gcd(a, b)の解を求める)
template<typename T>
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
template<typename T>
T inv_mod(T a, T mod) {
    T x, y;
    extgcd(a, mod, x, y);
    return (mod + x%mod) % mod;
}


// 添字GCD畳み込み(計算量：O(NloglogN))
template<typename T>
vector<T> gcd_convolution(vector<T> F, vector<T> G) {
    int N = max(F.size(), G.size());

    // 高速ゼータ変換
    auto fast_zeta = [&](vector<T> &a) {
        int n = a.size();
        vector<bool> sieve(n, false);
        for (int p = 2; p < n; ++p) {
            if (sieve[p]) continue;
            for (int k=(n-1)/p; k>=0; k--) sieve[k*p]=true, a[k]+=a[k*p];
        }
    };
    // 高速メビウス変換
    auto fast_mobius = [&](vector<T> &a) {
        int n = a.size();
        vector<bool> sieve(n, false);
        for (int p = 2; p < n; ++p) {
            if (sieve[p]) continue;
            else {
                for (int k=0; k*p<n; k++) sieve[k*p]=true, a[k]-=a[k*p];
            }
        }
    };

    fast_zeta(F);
    fast_zeta(G);

    vector<T> H(N);
    rep(i, min(F.size(), G.size())) {
        H[i] = F[i]*G[i];
    }

    fast_mobius(H);

    return H;
}
