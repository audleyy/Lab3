#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int determineWinner(int n, int m, const vector<int>& numbers) {
  vector<int> prefixSums(n + 1, 0);
  for (int i = 0; i < n; ++i) {
    prefixSums[i + 1] = prefixSums[i] + numbers[i];
  }

  int pavelScore = 0;
  int vikaScore = 0;
  int pavelPrev = -1;	
  int vikaPrev = -1;
  int currentIndex = 0;
  bool isPavelTurn = true;

  while (currentIndex < n) {
    int remainingCount = n - currentIndex;
    int prevMove = isPavelTurn ? pavelPrev : vikaPrev;

    int maxSum = -2e18;
    int bestK = -1;
    int limit = min(m, remainingCount);

    for (int k = 1; k <= limit; ++k) {
      if (k == prevMove) continue;

      int currentTurnSum = prefixSums[currentIndex + k] - prefixSums[currentIndex];

      if (bestK == -1 || currentTurnSum > maxSum) {
        maxSum = currentTurnSum;
        bestK = k;
      }
    }

    if (bestK != -1) {
      if (isPavelTurn) {
        pavelScore += maxSum;
        pavelPrev = bestK;
      } else {
        vikaScore += maxSum;
        vikaPrev = bestK;
      }
      currentIndex += bestK;
    } else {
      currentIndex = n;
    }

    isPavelTurn = !isPavelTurn;
  }

  return (pavelScore > vikaScore) ? 1 : 0;
}

int main() {
  int n, m;
  if (!(cin >> n >> m)) return 0;

  vector<int> numbers(n);
  for (int i = 0; i < n; ++i) {
    cin >> numbers[i];
  }

  cout << determineWinner(n, m, numbers) << endl;
  return 0;
}