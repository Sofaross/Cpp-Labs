#include <iostream>
#include <vector>
#include <chrono>
#include <ctime>
#include <fstream>

using namespace std;

void RandomArr(vector<int> &Arr)
{
  srand(time(0));
  for (int i = 0; i < Arr.size(); i++)
  {
    Arr[i] = 100 + rand() % 51;
  }
}

void bubble(int N)
{
  int temp = 0;
  vector<int> Arr(N);
  for (int k = 0; k < 10000; k++)
  {
    RandomArr(Arr);
    for (int i = 0; i < N - 1; i++)
    {
      bool flag = true;
      for (int j = 0; j < N - (i + 1); j++)
      {
        if (Arr[j] > Arr[j + 1])
        {
          flag = false;
          temp = Arr[j];
          Arr[j] = Arr[j + 1];
          Arr[j + 1] = temp;
        }
      }
      if (flag)
      {
        break;
      }
    }
  }
}

void Insert(int N)
{
  int temp = 0;
  vector<int> Arr(N);
  for (int k = 0; k < 10000; k++)
  {
    RandomArr(Arr);
    for (int i = 1, j; i < N; ++i)
    {
      temp = Arr[i];
      for (j = i - 1; j >= 0 && Arr[j] > temp; --j)
      {
        Arr[j + 1] = Arr[j];
      }
      Arr[j + 1] = temp;
    }
  }
}


int main()
{
  cout << "==============================================" << endl;
  ofstream out;
  out.open("D:\\Visual Studio codes\\algoritm,laba1\\result1.txt");
  int End = 1000;
  for (int N = 100; N <= End;)
  {
    auto start = chrono::high_resolution_clock::now();
    bubble(N);
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<float> duration = end - start;

    start = chrono::high_resolution_clock::now();
    Insert(N);
    end = chrono::high_resolution_clock::now();
    chrono::duration<float> duration2 = end - start;
    out << duration.count() << " " << duration2.count() << endl;

    cout << "KekW for " << N << " Ready " << endl;
    cout << "==============================================" << endl;
    N += 100;
  }

  return 0;
}