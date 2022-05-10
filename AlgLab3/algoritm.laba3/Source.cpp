#include <iostream>
#include <chrono>
using namespace std;

int iterative(int n)
{
  int res = 0, b = 1;
  while (n != 0)
  {
    res = res + b;
    b = res - b;
    n = n - 1;
  }
  return res;
}


unsigned long  recursive(int n)
{
  if (n == 0 || n == 1) return n;
  else return recursive(n - 1) + recursive(n-2);
}




int main()
{
  int N = 45;
  unsigned long gg;
  auto start = chrono::high_resolution_clock::now();
  gg= iterative(N);
  cout << gg;
  auto end = chrono::high_resolution_clock::now();
  chrono::duration<float> duration = end - start;
  cout << "\n runtime = " << duration.count() << endl;

  cout << "=======================" << endl;

  start = chrono::high_resolution_clock::now();
  gg = recursive(N);
  cout << gg;
  end = chrono::high_resolution_clock::now();
  chrono::duration<float> duration2 = end - start;
  cout << "\n runtime2 = " << duration2.count() << endl;
  return 0;
}