#include <iostream>
#include <string>
#include <ctime>
#include <chrono>
#include <fstream>

using namespace std;

//Алгоритм поиска для строк обычный
string StrCreate(char alph[],int size)
{
  string str;
  for (int i = 0; i < size; i++)
  {
    str += alph[rand() % strlen(alph)];
  }
  return str;
}

int  Simple_Search(string str, string substr,int global)
{
  int SizeStr = str.length();
  int SizeSub = substr.length();
  int counter = 0;
  int j = 0, k = 0;

  for (int i = 0; i < (SizeStr - SizeSub + 1); i++)
  {
    if (str[i] == substr[j])
    {
      j++;
      k = i + 1;
      counter++;
      while (counter != SizeSub)
      {
        if (str[k] == substr[j])
        {
          counter++;
          j++;
          k++;
        }
        else break;
      }
     
    }
    if (counter == SizeSub) global++;
    counter = 0;
    j = 0;
  }
  return global;
}

// Алгоритм поиска Алгоритм Бойера-Мура-Хорспула

int max(int a, int b)
{
  return (a > b) ? a : b;
}

void badCharHeuristic(string str, int size, int badchar[256])
{
  int i;
  for (i = 0; i < 256; i++)
    badchar[i] = -1;
  for (i = 0; i < size; i++)
    badchar[(int)str[i]] = i; // таблица для сдвига образа
}

int search(string txt, string pat,int global1)
{
  int ss = 0, n = 0, m = 0;
  n = txt.length();
  m = pat.length();
  int badchar[256];

  badCharHeuristic(pat, m, badchar);

  int s = 0;
  while (s <= (n - m))
  {
    int j = m - 1;
    while (j >= 0 && pat[j] == txt[s + j])
      j--;

    if (j < 0)
    {
      s += (s + m < n) ? m - badchar[txt[s + m]] : 1;
      global1++;
    }
    else
      s += max(1, j - badchar[txt[s + j]]);
  }
  return global1;
}



int main() 
{
  cout << "==============================================" << endl;
  ofstream out;
  out.open("D:\\Visual Studio codes\\algoritm.laba2\\result2.txt");
  srand(time(NULL));
  char alph[] = "abcdefq";
  string substr = "abdefdb";
  string str;
  int End = 1300;
  int global = 0;
  int global1 = 0;
  int result = 0;
  int result1 = 0;
  int r = 0, r1 = 0;
  for (int size=200; size <=End;)
  {
    auto start = chrono::high_resolution_clock::now();
    for (int i = 0; i < 60000; i++)
    {
      str = StrCreate(alph, size);
      result=Simple_Search(str, substr,global);
      r += result;
    }
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<float> duration = end - start;

  

    start = chrono::high_resolution_clock::now();
    for (int i = 0; i < 60000; i++)
    {
      str = StrCreate(alph, size);
      result1=search(str, substr,global1);
      r1 += result1;
    }
    end = chrono::high_resolution_clock::now();
    chrono::duration<float> duration2 = end - start;

    out <<size << " " << duration2.count() << " " << duration.count() << " " << r1 / 60000 << " " << r / 60000 << endl;
    
    cout << "KekW for " << size << " Ready " << endl;
    cout << "==============================================" << endl;
    size += 50;
    global = 0; global1 = 0;
    result = 0; result1 = 0; 
    r = 0; r1 = 0;
  }

}