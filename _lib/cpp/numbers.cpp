/*
・ライブラリ：整数
*/

#include "_tpl.cpp"


// 素数判定 
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


// 素数列挙(エラトステネスの篩)
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


// 素因数分解(mapベース)
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
vector<pair<ll, int>> factorize(vector<ll> &table, ll x) {

    vector<ll> V;
    while (x != table[x]) {
        V.pb(table[x]);
        x /= table[x];
    }
    if (x != 1) {
        V.pb(x);
    }
    auto res = RLE(V);
    return res;
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
// string dton(ll num, ll n) {
//     string res;
//     while (abs(num) > 0) {
//         ll m = num % abs(n);
//         num -= m;
//         res += tochar(m);
//         num /= n;
//     }
//     reverse(ALL(res));
//     if (res != "") {
//         return res;
//     } else {
//         return "0";
//     }
// }
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


// ピタゴラス数(未整備。重複削除とかgcdで互いに素とか考えてない。)
vector<ll> calc(ll m, ll n) {
    ll a = abs(pow(m, 2) - pow(n, 2));
    ll b = 2*m*n;
    ll c = pow(m, 2) + pow(n, 2);
    vector<ll> res = {a, b, c};
    sort(ALL(res));
    return res;
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