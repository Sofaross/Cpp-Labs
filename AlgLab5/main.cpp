#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <chrono>

using namespace std;
#define Size 55

//max kol-vo svяzeй
int Sv(int N)
{
  int counter = 0;
  for (int i = 1; i <= N - 1; i++)
  {
    counter += i;
  }
  return counter;
}

//Рандом матрицы
void  Random(vector<vector<int>>& G, int counter, int N)
{
  srand(time(0));
  for (int i = 0; i < N; i++)
  {
    for (int j = 0; j < N; j++)
    {
      G[i][j] = 0;
    }
  }
  int k = counter;
  if ((k % 2) == 0)
    k = (counter) / 2;
  else k = (counter - 1) / 2;
  int k1 = 0;//сколько места есть 
  int k3 = k;//сколько места оставлось
  for (int h = 1; h <= N; h++)
  {
    if ((k1 != k) && (k1 < k3))
    {
      k1 = k1 + N - h;
      for (int i = h; i < N; i++)
      {
        int j = h - 1;
        G[j][i] = 1 + rand() % 10;
      }
    }
  }
  for (int i = 0; i < N; i++)
  {
    for (int j = 0; j < N; j++)
    {
      G[j][i] = G[i][j];
    }
  }
  for (int i = 0; i < N; i++)
  {
    for (int j = 0; j < N; j++)
    {
      cout << G[i][j] << "\t";
    }
    cout << endl;
  }
  //return k;
}

int Counter(vector<vector<int>>& G)
{
  int N = G.size();
  int count = 0;
  for (int i = 0; i < N; i++)
  {
    for (int j = i + 1; j < N; j++)
    {
      if (G[i][j] != 0)
      {
        count++;
      }
    }
  }
  return count;
}

const int maxV = 1000;
int i, j, n;
int GR[maxV][maxV];
//алгоритм Флойда-Уоршелла
void FU(vector<vector<int>>& D, int V)
{
  V = Size;
  int k;
  for (i = 0; i < V; i++) D[i][i] = 0;

  for (k = 0; k < V; k++)
    for (i = 0; i < V; i++)
      for (j = 0; j < V; j++)
        if (D[i][k] && D[k][j] && i != j)
          if (D[i][k] + D[k][j] < D[i][j] || D[i][j] == 0)
            D[i][j] = D[i][k] + D[k][j];
}


//Дейкстра


void Dijkstra(vector<vector<int>>& GR, int st)
{
  int V = Size;
  int distance[Size], count, index, i, u, m = st + 1;
  bool visited[Size];
  for (i = 0; i < V; i++)
  {
    distance[i] = INT_MAX; visited[i] = false;
  }
  distance[st] = 0;
  for (count = 0; count < V - 1; count++)
  {
    int min = INT_MAX;
    for (i = 0; i < V; i++)
      if (!visited[i] && distance[i] <= min)
      {
        min = distance[i]; index = i;
      }
    u = index;
    visited[u] = true;
    for (i = 0; i < V; i++)
      if (!visited[i] && GR[u][i] && distance[u] != INT_MAX &&
        distance[u] + GR[u][i] < distance[i])
        distance[i] = distance[u] + GR[u][i];
  }
}

int main()
{
  setlocale(LC_ALL, "Rus");

  vector < vector <int> > a(Size, vector <int>(Size));

  Random(a, Sv(Size), Size);

  int n = Counter(a);

  cout << "Матрица кратчайших путей:" << endl;

  auto start = chrono::high_resolution_clock::now();
  FU(a, n);
  auto end = chrono::high_resolution_clock::now();
  chrono::duration<float> duration = end - start;


  cout << "===============" << endl;


  start = chrono::high_resolution_clock::now();
  Dijkstra(a, 0);
  end = chrono::high_resolution_clock::now();
  chrono::duration<float> duration2 = end - start;


  cout << duration.count() << " \t" << duration2.count() << endl;
  return 0;
}
