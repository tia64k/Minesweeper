// Minesweeper.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

void gotoxy(int, int);
void otoczenie(int(&tab)[9][9], int x, int y);
void wypelnij(int tab[9][9], int x, int y);
void wypisz(int tab[9][9]);

int main()
{
	srand(time(NULL));
	int licznik = 0, x = 1, y = 1;
	int pole[9][9];
	char c;

	for (int i = 0; i < 9; i++) 
	{
		for (int j = 0; j < 9; j++)
			cout << " - ";
		cout << endl;
	}

	wypelnij(pole, 5, 5);

	gotoxy(1, 1);

	while (1)
	{ // Dodaæ warunek zakoñczenia
		do 
		{
			c = _getch();
		}
		while (c == -32);

		gotoxy(3 * x, y); // Usuwa zaznaczenie
		cout << " ";
		gotoxy(3 * x + 2, y);
		cout << " ";

		if (c == 72) 
		{ // Góra
			if (y > 0) y--;
		}
		if (c == 80)
		{ // Dó³
			if (y < 8) y++;
		}
		if (c == 75)
		{ // Lewo
			if (x > 0) x--;
		}
		if (c == 77)
		{ // Prawo
			if (x < 8) x++;
		}

		if (c == 13) 
		{ // Enter
			if (pole[x][y] != 9)
			{
				gotoxy(3 * x + 1, y);

				if (pole[x][y]) 
				{
					gotoxy(3 * x + 1, y);
					cout << pole[x][y];
				}
				else 
				{
					otoczenie(pole, x, y);
				}
			}
			else 
			{
				gotoxy(3 * x + 1, y);
				cout << "*";
				gotoxy(0, 10);
				cout << "Przegrales/as" << endl;
				break;
			}
		}
		if (c == 32) 
		{ // Prawo
			gotoxy(3 * x + 1, y);
			cout << "+";
		}

		gotoxy(3 * x, y);
		cout << "[";
		gotoxy(3 * x + 2, y);
		cout << "]";
	}

	system("PAUSE");
	return 0;
}

void gotoxy(int x, int y)
{
	COORD c;

	c.X = x;
	c.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void otoczenie(int(&tab)[9][9], int x, int y)
{
	if (x >= 0 && x < 9 && y >= 0 && y < 9 && tab[x][y] == 0)
	{
		tab[x][y] = -1;
		gotoxy(3 * x + 1, y);
		cout << " ";

		if (x + 1 >= 0 && x + 1 < 9 && tab[x + 1][y] > 0 && tab[x + 1][y] < 9)
		{
			gotoxy(3 * (x + 1) + 1, y);
			cout << tab[x + 1][y];
		}
		if (x - 1 >= 0 && x - 1 < 9 && tab[x - 1][y] > 0 && tab[x - 1][y] < 9)
		{
			gotoxy(3 * (x - 1) + 1, y);
			cout << tab[x - 1][y];
		}
		if (y + 1 >= 0 && y + 1 < 9 && tab[x][y + 1] > 0 && tab[x][y + 1] < 9)
		{
			gotoxy(3 * x + 1, y + 1);
			cout << tab[x][y + 1];
		}
		if (y - 1 >= 0 && y - 1 < 9 && tab[x][y - 1] > 0 && tab[x][y - 1] < 9)
		{
			gotoxy(3 * x + 1, y - 1);
			cout << tab[x][y - 1];
		}

		otoczenie(tab, x - 1, y);
		otoczenie(tab, x + 1, y);
		otoczenie(tab, x, y - 1);
		otoczenie(tab, x, y + 1);
	}
}

void wypelnij(int tab[9][9], int x, int y)
{
	int i, j;
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
			tab[i][j] = 0;
	}

	for (int count = 0; count < 10; count++)
	{
		do 
		{
			i = rand() % 9;
			j = rand() % 9;
		} while (i == x || j == y);

		tab[i][j] = 9; // 9 oznacza minê
	}

	int licznik = 0;

	for (int i = 0; i < 9; i++)
		for (int j = 0; j < 9; j++) 
		{
			for (int k = i - 1; k <= i + 1; k++)
				for (int l = j - 1; l <= j + 1; l++)
					if (!(k == i && l == j) && k >= 0 && k < 9 && l >= 0 && l < 9 && tab[k][l] == 9)
						licznik++;
			if (tab[i][j] != 9)
				tab[i][j] = licznik;
			licznik = 0;
		}
}

void wypisz(int tab[][9])
{
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			if (tab[j][i] == 9) cout << " " << tab[j][i] << " ";
			else if (tab[j][i] == 0) cout << " " << tab[j][i] << " ";
			else cout << " " << tab[j][i] << " ";
		}
		cout << endl;
	}
}
