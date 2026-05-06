use std::io::{self, Read};
use std::cmp::min;

fn determineWinner(n: i32, m: i32, numbers: &Vec<i32>) -> i32 {
  let mut prefixSums = vec![0; (n + 1) as usize];
  for i in 0..n as usize {
    prefixSums[i + 1] = prefixSums[i] + numbers[i];
  }

  let mut pavelScore: i64 = 0;
  let mut vikaScore: i64 = 0;
  let mut pavelPrev = -1;	
  let mut vikaPrev = -1;
  let mut currentIndex = 0;
  let mut isPavelTurn = true;

  while currentIndex < n {
    let remainingCount = n - currentIndex;
    let prevMove = if isPavelTurn { pavelPrev } else { vikaPrev };

    let mut maxSum: i64 = -2000000000000000000;	
    let mut bestK = -1;
    let limit = min(m, remainingCount);

    for k in 1..=limit {
      if k == prevMove { continue; }

      let currentTurnSum = (prefixSums[(currentIndex + k) as usize] - prefixSums[currentIndex as usize]) as i64;

      if bestK == -1 || currentTurnSum > maxSum {
        maxSum = currentTurnSum;
        bestK = k;
      }
    }

    if bestK != -1 {
      if isPavelTurn {
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

  return if pavelScore > vikaScore { 1 } else { 0 };
}

fn main() {
  let mut buffer = String::new();
  if io::stdin().read_to_string(&mut buffer).is_err() {
    return;
  }

  let mut tokens = buffer.split_whitespace();
  
  let n: i32 = match tokens.next() {
    Some(s) => s.parse().unwrap_or(0),
    None => return,
  };
  let m: i32 = match tokens.next() {
    Some(s) => s.parse().unwrap_or(0),
    None => return,
  };

  let mut numbers = Vec::with_capacity(n as usize);
  for _ in 0..n {
    if let Some(s) = tokens.next() {
      numbers.push(s.parse().unwrap_or(0));
    }
  }

  println!("{}", determineWinner(n, m, &numbers));
}