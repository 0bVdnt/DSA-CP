// https://leetcode.com/problems/count-the-number-of-arrays-with-k-matching-adjacent-elements/submissions/1667113439

const int MOD = 1e9 + 7;
const int MAX_SIZE = 1e5;

long long fact[MAX_SIZE];
long long inv_fact[MAX_SIZE];

long long binaryExponentiation(long long x, int n) {
    long long res = 1;
    while (n) {
        if (n & 1) {
            res = res * x % MOD;
        }
        x = x * x % MOD;
        n >>= 1;
    }
    return res;
}

class Combination {
    long long binExpo(long long x, int n) {
        long long res = 1;
        while (n) {
            if (n & 1) {
                res = res * x % MOD;
            }
            x = x * x % MOD;
            n >>= 1;
        }
        return res;
    }

    long long comb(int n, int m) {
        return fact[n] * inv_fact[m] % MOD * inv_fact[n - m] % MOD;
    }
    void init() {
        if (fact[0]) {
            return;
        }
        fact[0] = 1;
        for (int i = 1; i < MAX_SIZE; i++) {
            fact[i] = fact[i - 1] * i % MOD;
        }

        inv_fact[MAX_SIZE - 1] = binExpo(fact[MAX_SIZE - 1], MOD - 2);
        for (int i = MAX_SIZE - 1; i; i--) {
            inv_fact[i - 1] = inv_fact[i] * i % MOD;
        }
    }

public:
    int retCombination(int n, int r) {
        init();
        return comb(n, r);;
    }
};