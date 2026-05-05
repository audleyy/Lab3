#include <iostream>
#include <vector>
#include <cmath>
#include <random>
#include <iomanip>

using namespace std;

typedef __int128_t int128;

ostream& operator<<(ostream& os, int128 n) {
  if (n == 0) return os << "0";
  string s;
  while (n > 0) {
    s += (char)('0' + (n % 10));
    n /= 10;
  }
  for (int i = 0; i < s.size() / 2; i++) swap(s[i], s[s.size() - 1 - i]);
  return os << s;
}

int128 power(int128 a, int128 b, int128 m) {
  int128 res = 1;
  a %= m;
  while (b > 0) {
    if (b % 2 == 1) res = (int128)res * a % m;
    a = (int128)a * a % m;
    b /= 2;
  }
  return res;
}

vector<int> smallPrimes;
void sieve(int limit) {
  vector<bool> isPrime(limit + 1, true);
  isPrime[0] = isPrime[1] = false;
  for (int p = 2; p * p <= limit; p++) {
    if (isPrime[p]) {
      for (int i = p * p; i <= limit; i += p)
        isPrime[i] = false;
    }
  }
  for (int p = 2; p <= limit; p++) {
    if (isPrime[p]) smallPrimes.push_back(p);
  }
}

int128 getSmallPrime(int bits) {
  int128 minVal = (int128)1 << (bits - 1);
  int128 maxVal = ((int128)1 << bits) - 1;
  vector<int> candidates;
  for (int p : smallPrimes) {
    if (p >= minVal && p <= maxVal) candidates.push_back(p);
  }
  static mt19937 gen(random_device{}());
  if (candidates.empty()) return 251;
  return candidates[gen() % candidates.size()];
}

int rejectedCount = 0;

int128 generateGostPrime(int t) {
  if (t <= 8) return getSmallPrime(t);

  int qBits = (t + 1) / 2;
  int128 q = generateGostPrime(qBits);

  static mt19937_64 gen(random_device{}());
  uniform_real_distribution<double> dist(0.0, 1.0);

  int128 powTMinus1 = (int128)1 << (t - 1);

  while (true) {
    double xi = dist(gen);
    int128 N = (powTMinus1 + q - 1) / q + (int128)(powTMinus1 * xi) / q;
    
    if (N % 2 != 0) N++;

    for (int128 u = 0; ; u += 2) {
      int128 p = (N + u) * q + 1;

      if (p >= ((int128)1 << t)) break;

      if (power(2, p - 1, p) == 1 && power(2, N + u, p) != 1) {
        return p;
      }
      rejectedCount++;
    }
  }
}

int main() {
  int bits;
  cin >> bits;

  if (bits > 120) {
    return 1;
  }

  sieve(500);

  for (int i = 1; i <= 10; ++i) {
    int currentRejected = rejectedCount;
    int128 p = generateGostPrime(bits);
    
    cout << p << " | " << (rejectedCount - currentRejected) << endl;
  }
  
  cout << "rejected: " << rejectedCount << endl;

  return 0;
}