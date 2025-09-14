// #pragma GCC optimize("O3,unroll-loops")           // Enable specific optimizations
// #pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")  // Enable specific instruction sets

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>
#include <iomanip> // For setprecision
#include <numeric> // For iota, accumulate
#include <map>
#include <set>
#include <queue>
#include <stack>
#include <deque>
#include <bitset>  // For bit manipulation
#include <cassert> // For assert
#include <chrono>  // For timing (optional)
#include <limits>  // For numeric_limits

// For advanced data structures (if needed, uncomment and install if necessary)
// #include <ext/pb_ds/assoc_container.hpp> // Common file
// #include <ext/pb_ds/tree_policy.hpp>     // Including tree_order_statistics_node_update
// using namespace __gnu_pbds;
// template<typename T> using ordered_set = tree<T, null_type, std::less<T>, rb_tree_tag, tree_order_statistics_node_update>;
// template<typename T> using ordered_multiset = tree<T, null_type, std::less_equal<T>, rb_tree_tag, tree_order_statistics_node_update>;
// How to use ordered_set:
// os.find_by_order(k) : K-th element in a set (counting from 0).
// os.order_of_key(X) : Number of items strictly smaller than X.

using namespace std;

// Type Aliases
using ll = long long;
using ld = long double;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using vi = vector<int>;
using vl = vector<ll>;
using vpii = vector<pii>;
using vpll = vector<pll>;
using vvi = vector<vi>;
using vvl = vector<vl>;
using mii = map<int, int>;
using mll = map<ll, ll>;
using si = set<int>;
using sl = set<ll>;

// Constants
const ll INF = 1e18;            // For long long infinity
const int INT_INF = 1e9;        // For int infinity
const ld PI = acos((ld)-1);
const ld EPS = 1e-9;            // For floating point comparisons
const int MOD = 1e9 + 7;        // Common modulo
// const int MOD = 998244353;   // Another common modulo

// Macros
#define fast_io ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL)
#define F first
#define S second
#define PB push_back
#define MP make_pair
#define ALL(x) (x).begin(), (x).end()
#define RALL(x) (x).rbegin(), (x).rend()
#define SZ(x) ((int)(x).size())
#define LAMBDA(ret_type, ...) function<ret_type(__VA_ARGS__)>
#define yes cout << "YES" << endl
#define no cout << "NO" << endl

// Loop Macros
#define rep(i, a, b) for (int i = (a); i <= (b); ++i)
#define F0R(i, a) for (int i = 0; i < (a); ++i)
#define per(i, a, b) for (int i = (a); i >= (b); --i)
#define R0F(i, a) for (int i = (a) - 1; i >= 0; --i)
#define trav(a, x) for (auto& a : x)

// Utility Functions
template<typename T> T gcd(T a, T b) { return b == 0 ? a : gcd(b, a % b); }
template<typename T> T lcm(T a, T b) { return (a / gcd(a, b)) * b; }
template<typename T> T power(T base, T exp, T mod) {
    T res = 1;
    base %= mod;
    while (exp > 0) {
        if (exp % 2 == 1) res = (static_cast<ll>(res) * base) % mod;
        base = (static_cast<ll>(base) * base) % mod;
        exp /= 2;
    }
    return res;
}
template<typename T> T power(T base, T exp) { // No modulo
    T res = 1;
    while (exp > 0) {
        if (exp % 2 == 1) res *= base;
        base *= base;
        exp /= 2;
    }
    return res;
}
template<typename T> T inv(T n, T mod) { return power(n, mod - 2, mod); } // Modular inverse (for prime mod)

// Debugging (compile with -DLOCAL for debug output)
void __print(int x) { cerr << x; }
void __print(long x) { cerr << x; }
void __print(long long x) { cerr << x; }
void __print(unsigned x) { cerr << x; }
void __print(unsigned long x) { cerr << x; }
void __print(unsigned long long x) { cerr << x; }
void __print(float x) { cerr << x; }
void __print(double x) { cerr << x; }
void __print(long double x) { cerr << x; }
void __print(char x) { cerr << '\'' << x << '\''; }
void __print(const char *x) { cerr << '\"' << x << '\"'; }
void __print(const string &x) { cerr << '\"' << x << '\"'; }
void __print(bool x) { cerr << (x ? "true" : "false"); }

template<typename T, typename V>
void __print(const pair<T, V> &x) { cerr << '{'; __print(x.first); cerr << ", "; __print(x.second); cerr << '}'; }
template<typename T>
void __print(const T &x) { int f = 0; cerr << '{'; for (auto &i: x) cerr << (f++ ? ", " : ""), __print(i); cerr << "}"; }
void _print() { cerr << "]\n"; }
template <typename T, typename... V>
void _print(T t, V... v) { __print(t); if (sizeof...(v)) cerr << ", "; _print(v...); }

#ifdef LOCAL
#define debug(x...) cerr << "\e[91m"<<__func__<<":"<<__LINE__<<" [" << #x << "] = ["; _print(x); cerr << "\e[39m" << endl;
#else
#define debug(x...)
#endif

// Global variables (if any)
// const int MAXN = 2e5 + 5;
// int arr[MAXN];
// vector<int> adj[MAXN];

// --- Solution Starts Here ---
void solve([[maybe_unused]] int test_case) {
    // Your solution logic here
    int n;
    cin >> n;
    vi a(n);
    F0R(i, n) cin >> a[i];
    debug(n, a);

    // cout << accumulate(ALL(a), 0LL) << endl;
}
// --- Solution Ends Here ---

int main() {
    fast_io;

    #ifdef LOCAL
        auto start_time = chrono::high_resolution_clock::now();
        // freopen("input.txt", "r", stdin);    // Optional: redirect input from file
        // freopen("output.txt", "w", stdout);  // Optional: redirect output to file
    #endif

    int t = 1;
    cin >> t;  // Comment this line if there's only one test case

    F0R(i, t) {
        // cout << "Case #" << i << ": "; // For problems like Google Kick Start
        solve(i);                         // Pass test case number if needed
    }

    #ifdef LOCAL
        auto end_time = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::milliseconds>(end_time - start_time);
        cerr << "Time elapsed: " << duration.count() << "ms\n";
    #endif

    return 0;
}