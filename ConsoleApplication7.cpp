#include <iostream>
#include <random>
#include <vector>
#include <cstdlib>
#include <windows.h>
using namespace std;
class Maze {
public:
	int height;
	int width;
	int a=-1;
	bool northCheck = false;
	bool westCheck = false;
	vector<vector<int>> maze;
	vector<vector<int>> path;
	vector<vector<bool>> visited;
	int sayac = 1;
	Maze(int x, int y) {
		srand(time(0));
		if (x % 2 == 0) {
			x++;
		}
		if (y % 2 == 0) {
			y++;
		}
		height = x+4;
		width = y+4;
		maze.resize(height, vector<int>(width));
	}
	void cerceve() {
		for (int i = 0; i < width; i++) {
			for (int j = 0; j < height; j++) {
				if (i == 0 || j == 0 || i == width-1 || j == height-1) {
					maze[i][j] = 1;
				}
			}
		}
	}
	void mazeGeneration() {
		maze[2][2] = 1;
		for (int i = 2; i < height-2; i += 2)
		{
			for (int j = 2; j < width-2; j += 2)
			{
				maze[i][j] = 1;
				if (i > 2)
				{
					northCheck = true;
				}
				if (j > 2)
				{
					westCheck = true;
				}
				if (westCheck && northCheck)
				{
					a = rand() % 2;
					if (a == 0)
					{
						maze[i][j - 1] = 1;
					}
					else if (a == 1)
					{
						maze[i - 1][j] = 1;
					}
				}
				else if (westCheck)
				{
					maze[i][j - 1] = 1;
				}
				else if (northCheck)
				{
					maze[i - 1][j] = 1;
				}
				northCheck = false;
				westCheck = false;
			}
		}
	}
	void printMaze() {
		string x="";
		for (int a = 0; a < sayac; a++) {
			x = "";
			system("cls");
			for (int i = 0; i < height; i++)
			{
				for (int j = 0; j < width; j++)
				{
					if (maze[i][j] == 1)
					{
						x += "# ";
					}
					else if (maze[i][j] == 2) {
						x += "* ";
					}
					else if (maze[i][j] == 0)
					{
						x += "  ";
					}
				}
				x+="\n";
			}
			cout << x;
			Sleep(10);
		}
	}
	void pathFinding() {
		visited.resize(height, vector<bool>(width));
		path.resize(height * width, vector<int>(2));
		bool finished = false;
		int searchx;
		int searchy;
		int targetx;
		int targety;
		cout << "Lutfen baslama noktasinin x ve y koordinatlarini giriniz\n";
		cin >> searchx >> searchy;
		cout << "Lutfen bitis noktasinin x ve y koordinatlarini giriniz\n";
		cin >> targetx >> targety;
		searchx += 2;
		searchy += 2;
		targetx += 2;
		targety += 2;
		visited[searchy][searchx] = true;
		while (!finished) {
			if (maze[searchy][searchx - 1]==0 && !visited[searchy][searchx - 1]) {
				searchx--;
				visited[searchy][searchx] = true;
				path[sayac][0] = searchy;
				path[sayac][1] = searchx;
				maze[searchy][searchx] = 2;
				if (searchx == targetx && searchy == targety) {
					finished = true;
				}
				sayac++;
			}
			else if (maze[searchy - 1][searchx]==0 && !visited[searchy - 1][searchx]) {
				searchy--;
				visited[searchy][searchx] = true;
				path[sayac][0] = searchy;
				path[sayac][1] = searchx;
				maze[searchy][searchx] = 2;
				if (searchx == targetx && searchy == targety) {
					finished = true;
				}
				sayac++;
			}
			else if (maze[searchy][searchx + 1]==0 && !visited[searchy][searchx + 1]) {
				searchx++;
				visited[searchy][searchx] = true;
				path[sayac][0] = searchy;
				path[sayac][1] = searchx;
				maze[searchy][searchx] = 2;
				if (searchx == targetx && searchy == targety) {
					finished = true;
				}
				sayac++;
			}
			else if (maze[searchy + 1][searchx]==0 && !visited[searchy + 1][searchx]) {
				searchy++;
				visited[searchy][searchx] = true;
				path[sayac][0] = searchy;
				path[sayac][1] = searchx;
				maze[searchy][searchx] = 2;
				if (searchx == targetx && searchy == targety) {
					finished = true;
				}
				sayac++;
			}
			else {
				maze[searchy][searchx] = 0;
				searchx = path[sayac - 1][1];
				searchy = path[sayac - 1][0];
				sayac--;
			}
			printMaze();
		}
	}
};
int main()
{
	int x, y;
	cout << "Lutfen labirentin x ve y degerlerini giriniz\n";
	cin >> x >> y;
	Maze maze(x, y);
	maze.cerceve();
	maze.mazeGeneration();
	maze.printMaze();
	maze.pathFinding();
}
