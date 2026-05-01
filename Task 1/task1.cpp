#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

double calculate(double x) {
	if (x >= -9 && x <= -5) {
		return 2 - sqrt(4 - pow(x + 7, 2));
	} else if (x > -5 && x <= -4) {
		return 2.0;
	} else if (x > -4 && x <= 0) {
    return -0.5 * x;
  } else if (x > 0 && x <= 3) {
    return -0.5 * pow(x, 2) + 1.5 * x;
	} else if (x > 3) {
    return x - 3;
  }
  return 0;
}

void printValues(double xStart, double xEnd, double dx) {
	cout << "X\tY" << endl;
	cout << "------------" << endl;

	for (double x = xStart; x <= xEnd + dx / 2; x += dx) {
		double y = calculate(x);

		if (abs(y) < 1e-7) y = 0.0;
    if (abs(x) < 1e-7) x = 0.0;

		cout << fixed << setprecision(2) << x << "\t" << y << endl;
	}
}

int main() {
	double xStart, xEnd, dx;

	cin >> xStart >> xEnd >> dx;

	if (dx <= 0) {
		return 1;
	}

	printValues(xStart, xEnd, dx);
	return 0;
}