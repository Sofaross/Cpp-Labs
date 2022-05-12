#include<iostream>
#include<cstdlib>
#include<ctime>
#include <vector>
#include <algorithm>
#include <chrono>
#include <fstream>
using namespace std;
// Создание собственного лабиринта 

const int wall = -1, pass = -2, blank = -2;

// Вспомогательная функция, определяет тупики
bool deadend(int x, int y, const vector<vector<int>>& maze, int height, int width) {
	int a = 0;

	if (x != 1) {
		if (maze[y][x - 2] == pass)
			a += 1;
	}
	else a += 1;

	if (y != 1) {
		if (maze[y - 2][x] == pass)
			a += 1;
	}
	else a += 1;

	if (x != width - 2) {
		if (maze[y][x + 2] == pass)
			a += 1;
	}
	else a += 1;

	if (y != height - 2) {
		if (maze[y + 2][x] == pass)
			a += 1;
	}
	else a += 1;

	if (a == 4)
		return 1;
	else
		return 0;
}

// Изображение результата с помощью консольной графики
void visual(vector<vector<int>>& maze, int height, int width) {
	int ex = width - 1, ey = height - 2;
	int	x = 0, y = 1;
	maze[y][x] = pass;
	maze[ey][ex] = pass;
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++)
			switch (maze[i][j]) {
			case wall: cout << "0 "; break;
			case pass: cout << "  "; break;
			}
		cout << endl;
	}
	//cout << endl;
	//cout << " ==============="<<endl;

	//for (int i = 0; i < height; i++) 
	//{
	//	for (int j = 0; j < width; j++)
	//	{
	//		cout << maze[i][j] << " ";
	//	}
	//	cout << endl;
	//}
	maze[y][x] = wall;
	//maze[ey][ex] = wall;
}


// Собственно алгоритм
void mazemake(vector<vector<int>>& maze, int height, int width) {
	int x, y, c, a;
	int ex, ey;
	bool b;

	for (int i = 0; i < height; i++) // Массив заполняется землей-ноликами
		for (int j = 0; j < width; j++)
			maze[i][j] = wall;

	x = 1; y = 1; a = 0; // Точка приземления крота и счетчик


	while (a < 10000) { // Да, простите, костыль, иначе есть как, но лень
		maze[y][x] = pass; a++;
		//	maze[ey][ex] = pass; a++;
		while (1) { // Бесконечный цикл, который прерывается только тупиком
			c = rand() % 4; // Напоминаю, что крот прорывает
			switch (c) {  // по две клетки в одном направлении за прыжок
			case 0: if (y != 1)
				if (maze[y - 2][x] == wall) { // Вверх
					maze[y - 1][x] = pass;
					maze[y - 2][x] = pass;
					y -= 2;
				}
			case 1: if (y != height - 2)
				if (maze[y + 2][x] == wall) { // Вниз
					maze[y + 1][x] = pass;
					maze[y + 2][x] = pass;
					y += 2;
				}
			case 2: if (x != 1)
				if (maze[y][x - 2] == wall) { // Налево
					maze[y][x - 1] = pass;
					maze[y][x - 2] = pass;
					x -= 2;
				}
			case 3: if (x != width - 2)
				if (maze[y][x + 2] == wall) { // Направо
					maze[y][x + 1] = pass;
					maze[y][x + 2] = pass;
					x += 2;
				}
			}
			if (deadend(x, y, maze, height, width))
				break;
		}

		if (deadend(x, y, maze, height, width)) // Вытаскиваем крота из тупика
			do {
				x = 2 * (rand() % ((width - 1) / 2)) + 1;
				y = 2 * (rand() % ((height - 1) / 2)) + 1;
			} while (maze[y][x] != pass);
	} // На этом и все.

}


bool Wave(const vector<vector<int>>& maze, int ax, int ay, int bx, int by, int height, int width)
{
	int len;

	vector<vector<int> > grid(width, vector<int>(height));
	grid = maze;

	vector<int> px(height * width);
	vector<int> py(height * width);
	int dx[4] = { 1, 0, -1, 0 };   // смещения, соответствующие соседям ячейки
	int dy[4] = { 0, 1, 0, -1 };   // справа, снизу, слева и сверху
	int d, x, y, k;
	bool stop;

	if (grid[ay][ax] == -1 || grid[by][bx] == -1) return false;  // ячейка (ax, ay) или (bx, by) - стена

	// распространение волны
	d = 0;
	grid[ay][ax] = 0;            // стартовая ячейка помечена 0
	do {
		stop = true;               // предполагаем, что все свободные клетки уже помечены
		for (y = 0; y < height; ++y)
			for (x = 0; x < width; ++x)
				if (grid[y][x] == d)                         // ячейка (x, y) помечена числом d
				{
					for (k = 0; k < 4; ++k)                    // проходим по всем непомеченным соседям
					{
						int iy = y + dy[k], ix = x + dx[k];
						if (iy >= 0 && iy < height && ix >= 0 && ix < width && grid[iy][ix] == -2)
						{
							stop = false;              // найдены непомеченные клетки
							grid[iy][ix] = d + 1;      // распространяем волну
						}
					}
				}
		d++;
	} while (!stop && grid[by][bx] == -2);

	if (grid[by][bx] == -2) return false;  // путь не найден


	// восстановление пути
	len = grid[by][bx];            // длина кратчайшего пути из (ax, ay) в (bx, by)
	cout << "Min len=" << len + 2 << endl;
	cout << "--------------------------------------" << endl;
	grid[height-2][width-1] = -1;
	//for (int i = 0; i < height; i++) {
	//	for (int j = 0; j < width; j++)
	//	{
	//	cout << grid[i][j] << "\t";
	//	}
	//cout << endl;
	//}
	// 
	//x = bx;
	//y = by;
	//d = len+2;
	//while (d > 0)
	//{
	//	px[d] = x;
	//	py[d] = y;                   // записываем ячейку (x, y) в путь
	//	d--;
	//	for (k = 0; k < 4; ++k)
	//	{
	//		int iy = y + dy[k], ix = x + dx[k];
	//		if (iy >= 0 && iy < height && ix >= 0 && ix < width && grid[iy][ix] == d)
	//		{
	//			x = x + dx[k];
	//			y = y + dy[k];           // переходим в ячейку, которая на 1 ближе к старту
	//			break;
	//		}
	//	}
	//}
	//px[0] = ax;
	//py[0] = ay;
	//// теперь px[0..len] и py[0..len] - координаты ячеек пути
	//cout << "--------------------------------------" << endl;
	return true;

}


void block(vector<vector<int>>& grid, int lx, int ly, int bx, int by, int height, int width)
{
	int k = 0;
	grid[lx][ly] = 0;
again:
	for (int y = height - 2; y >= 1; y--)
		for (int x = width - 2; x >= 1; x--)
		{
			if ((grid[x][y] == -2) && (x != 0) && (y != 0) && (x != height - 1) && (y != height - 1))
			{
				if (grid[x - 1][y] == -1) { k += 1; }
				if (grid[x][y - 1] == -1) { k += 1; }
				if (grid[x + 1][y] == -1) { k += 1; }
				if (grid[x][y + 1] == -1) { k += 1; }
			}

			if (k == 3)
			{
				grid[x][y] = -1;
				/*	cout << "==================" << endl;
					for (int i = 0; i < height; i++)
					{
						for (int j = 0; j < width; j++)
						{
							cout << grid[i][j] << "\t";
						}
						cout << endl;
					}*/
				goto again;
			}
			k = 0;
		}
	grid[lx][ly] = pass;
	cout << "yes" << endl;
	//visual(grid, height, width);

}

int main() {
	ofstream out;
	out.open("D:\\Visual Studio codes\\algoritm.laba.6\\result2.txt");

	srand((unsigned)time(NULL));
	int End =180;

	for(int n = 9; n < End;) 
	{
	//int n = 49;
		int height = n, width = n;
		vector<vector<int> > maze(width, vector<int>(height));
		mazemake(maze, height, width);
		visual(maze, height, width);
		int ex = (width - 2), ey = (height - 2);
		int x = 1, y = 1;
		vector<vector<int> > grid(width, vector<int>(height));
		grid = maze;


		auto start = chrono::high_resolution_clock::now();
		Wave(grid, x, y, ex, ey, height, width);
		auto end = chrono::high_resolution_clock::now();
		chrono::duration<float> duration = end - start;

		start = chrono::high_resolution_clock::now();
		block(maze, x, y, ex, ey, height, width);
		end = chrono::high_resolution_clock::now();
		chrono::duration<float> duration2 = end - start;
		out << n << "\t" << duration.count() << "\t" << duration2.count() << endl;
		cout << "KekW for " << n << " Ready " << endl;
		cout << "==============================================" << endl;
		n += 10;
	}

	return 0;
}