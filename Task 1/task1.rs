use std::io;

fn calculate(x: f64) -> f64 {
  if x >= -9.0 && x <= -5.0 {
    2.0 - (4.0 - (x + 7.0).powi(2)).sqrt()
  } else if x > -5.0 && x <= -4.0 {
    2.0
  } else if x > -4.0 && x <= 0.0 {
    -0.5 * x
  } else if x > 0.0 && x <= 3.0 {
    -0.5 * x.powi(2) + 1.5 * x
  } else if x > 3.0 {
    x - 3.0
  } else {
    0.0
  }
}

fn print_values(x_start: f64, x_end: f64, dx: f64) {
  println!("X\tY");
  println!("------------");

  let mut x = x_start;
  while x <= x_end + dx / 2.0 {
    let mut y = calculate(x);
    let mut display_x = x;

    if y.abs() < 1e-7 { y = 0.0; }
    if display_x.abs() < 1e-7 { display_x = 0.0; }

    println!("{:.2}\t{:.2}", display_x, y);
    
    x += dx;
  }
}

fn main() {
  let mut input = String::new();

  io::stdin()
    .read_line(&mut input)
    .expect("Error");

  let parts: Vec<f64> = input
    .split_whitespace()
    .filter_map(|s| s.parse().ok())
    .collect();

  if parts.len() < 3 {
    return;
  }

  let x_start = parts[0];
  let x_end = parts[1];
  let dx = parts[2];

  if dx <= 0.0 {
    return;
  }

  print_values(x_start, x_end, dx);
}