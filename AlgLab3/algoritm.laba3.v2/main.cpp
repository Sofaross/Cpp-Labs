#include <iostream>
#include <fstream>
#include <chrono>
#include <math.h>

using namespace std;

int mas_size = 200;
const int min_size = 10;
const int max_size = 30000;
const unsigned int test_times = 10000;
const unsigned int substr_len = 15;
std::string str;
std::string substr(substr_len, ' ');

// Алгоритмы
// рекурсия
double func(double x) {
  return x*x+12*x;
}

double recurs(double x0, double x1, double rtol) {
  double avg = (x1 + x0) / 2;
  if (func(avg) * (x1 - x0) < rtol)
    return func(avg) * (x1 - x0);
  double sum = 0;
  sum += recurs( x0, avg, rtol);
  sum += recurs( avg, x1, rtol);
  return sum;
}



// Итерационный
double sum = 0;
int nseg = 1;

double restart( double x0, double x1, int nseg0) {
  sum = 0.5 * (func(x0) + func(x1));
  double dx = (x1 - x0) / nseg0;
  for (int i = 0; i < nseg0; i++)
    sum += func(x0 + i * dx);
  return sum * dx;
}

double double_nseg(double x0, double x1) {
  double dx = (x1 - x0) / nseg;
  double x = x0 + 0.5 * dx;
  int i = 0;
  for (; i < nseg; i++)
    sum += func(x + i * dx);
  nseg *= 2;
  return sum * 0.5 * dx;
}
// Как это работает? Хер его знает
double simpson(double x0, double x1, double rtol = std::exp(-10), int nseg0 = 1) {
  double old_trapez_sum = restart( x0, x1, nseg0);
  double new_trapez_sum = double_nseg( x0, x1);
  double ans = (4 * new_trapez_sum - old_trapez_sum) / 3;
  double old_ans;
  double err_est = max(1.0, abs(ans));
  while (err_est > std::abs(rtol * ans)) {
    old_ans = ans;
    old_trapez_sum = new_trapez_sum;
    new_trapez_sum = double_nseg( x0, x1);
    ans = (4 * new_trapez_sum - old_trapez_sum) / 3;
    err_est = std::abs(old_ans - ans);
  }
  return ans;
}

int main() {

  double lower_limit = 2.0;
  double Upper_limit = 30.0;
  double res = -1;
  double accuracy = 0.0002;
  int N = 5;

  ofstream out;
  out.open("D:\\Visual Studio codes\\algoritm.laba3.v2\\result3.txt");


    cout << "KEKW for \t" << accuracy << endl;
    auto start = chrono::high_resolution_clock::now();
    res = simpson(lower_limit, Upper_limit, accuracy);
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<float> duration = end - start;

    std::cout << "Trapezoid:\t" << res << '\n';

    start = chrono::high_resolution_clock::now();
    res = recurs(lower_limit, Upper_limit, accuracy);
    end = chrono::high_resolution_clock::now();
    chrono::duration<float> duration2 = end - start;

    std::cout << "Recurs: \t" << res << '\n';

    cout << "Time Iterative \t" << duration.count() << "\nTime Recursion \t" << duration2.count() << endl;


    out << accuracy << "\t" << duration.count() << "\t" << duration2.count() << endl;
    accuracy = accuracy / 10;
    cout << "===========================================" << endl;

  return 0;
}
