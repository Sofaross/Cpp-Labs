#include<iostream>
#include<vector>
#include<algorithm>
#include <chrono>
#include <ctime>
#include <vector>
using namespace std;

#define Size 90


//max kol-vo svяzeй
int Sv(int N)
{
	int counter=0;
	for (int i = 1; i <= N - 1; i++)
	{
		counter+=i;
	}
	return counter;
}

//random matrix k=2 
void  Random(vector<vector<int>>& G,int counter,int N)
{
	srand(time(0));
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			G[i][j] = 0;
		}
	}
	int k=counter;
	if ((k % 2) == 0)
		k = (counter) / 2;
	else k = (counter - 1) / 2;
	int k1=0;//сколько места есть 
	int k3 = k;//сколько места осталось
	for (int h = 1; h <=N; h++)
	{
		if ((k1 != k) && (k1 < k3))
		{
			k1 =k1+ N - h;
			for (int i = h ; i < N; i++)
			{
				int j = h-1;
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
}


//Algoritm Kraskola

int Counter(vector<vector<int>>& G)
{
	int N = Size;
	int count=0 ;
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
struct Node 
{
	int start;
	int end;
	int length;
};
bool compare(Node a, Node b)
{
	return a.length < b.length;
}
auto Kruskal(vector<vector<int>>& G, vector<Node>& arr, vector<bool>& visited, int size)
{
	int M, N;
	M = visited.size();
	N = arr.size();
	int k = 0;
		for (int i = 0; i < size; i++)
		{
			for (int j = i + 1; j < size; j++)
			{
				if(G[i][j] != 0) 
				{
				arr[k].start = i;
				arr[k].end = j;
				arr[k].length = G[i][j];
				k++;
				}
			}
	}
	sort(arr.begin(), arr.end(), compare);
	auto start = chrono::high_resolution_clock::now();
	int weight = 0;
	for (int i = 0; i < N; i++)
	{
		if ((visited[arr[i].start] == 0) || (visited[arr[i].end] == 0))
		{
			weight += arr[i].length;
			visited[arr[i].start] = true;
			visited[arr[i].end] = true;
		}
	}
	auto end = chrono::high_resolution_clock::now();

	chrono::duration<float> duration = end - start;
	cout << "Минимальный вес связующего дерева:";
	cout << weight;
	return duration;
}

//Algoritm Prima
auto Prima(vector<vector<int>>& G, int N)
{
	int count = 0;
	int no_edge;
	int selected[Size];
	auto start = chrono::high_resolution_clock::now();
	memset(selected, false, sizeof(selected));
	no_edge = 0;
	selected[0] = true;
	int x,y;
	while (no_edge < N - 1)
	{
		int min = 99999;
		x = 0;
		y = 0;
		for (int i = 0; i < N; i++) 
		{
			if (selected[i]) 
			{
				for (int j = 0; j < N; j++)
				{
					if (selected[j]==0 && G[i][j]) 
					{
						if (min > G[i][j]) 
						{
							min = G[i][j];
							x = i;
							y = j;
						}
					}
				}
			}
		}
		//cout << x << " - " << y << " :  " << G[x][y] << endl;
		count += G[x][y];
		selected[y] = true;
		no_edge++;
	}

	cout << "Минимальный вес связующего дерева:"<< count;

	return start;
}



int main()
{
	auto result = chrono::high_resolution_clock::now();
	setlocale(LC_ALL, "Russian");
	vector < vector <int> > a(Size, vector <int>(Size));


	Random(a, Sv(Size), Size);

	
	int M = Counter(a);
	
	
	vector<Node> arr(M);
	vector<bool> visited(Size);

	auto duration = Kruskal(a, arr, visited, Size);
	
	cout << "\nruntime Kruskal\t = " << duration.count()  << endl;

	cout << endl << endl;


	auto start = Prima(a, Size);
	auto end = chrono::high_resolution_clock::now();

	chrono::duration<float> duration2 = end - start;
	cout << "\nruntime Prima\t = " << duration2.count()  << endl;

	
	
	return (0);
}
