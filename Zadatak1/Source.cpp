#include <iostream>
#include <chrono>
#include "tocka.h"

using namespace std;
using namespace std::chrono;

void draw(tocka& a, tocka& b, tocka& x, const int MAX_REDAKA, const int MAX_STUPACA)
{
	system("cls");
	for (int i = 1; i <= MAX_REDAKA; i++)
	{
		for (int j = 1; j <= MAX_STUPACA; j++)
		{
			if (a.x == i && a.y == j)
			{
				cout << "A";
			}
			else if (x.x == i && x.y == j)
			{
				cout << "x";
			}
			else if (b.x == i && b.y == j)
			{
				cout << "B";
			}
			else
			{
				cout << "-";
			}
		}
		cout << endl;
	}
}

void calculate_next_position(tocka& a, tocka& b, tocka& x)
{
	if (x.y < b.y)
	{
		x.y++;
	}
	else if (x.y > b.y)
	{
		x.y--;
	}
	else
	{
		if (x.x < b.x)
		{
			x.x++;
		}
		else if (x.x > b.x)
		{
			x.x--;
		}
	}
}

int main()
{
	const int MAX_REDAKA = 20;
	const int MAX_STUPACA = 40;

	tocka a;
	tocka b;
	tocka x;

	cout << "A redak: ";
	cin >> a.x;
	cout << "A stupac: ";
	cin >> a.y;
	cout << "B redak: ";
	cin >> b.x;
	cout << "B stupac: ";
	cin >> b.y;

	x = a;

	do
	{
		calculate_next_position(a, b, x);
		draw(a, b, x, MAX_REDAKA, MAX_STUPACA);
		auto begin = high_resolution_clock::now();
		while(true)
		{
			auto end = high_resolution_clock::now();
			if (duration_cast<milliseconds>(end - begin).count() >= 100)
			{
				break;
			}
		}
	} while (x.x!=b.x||x.y!=b.y);

	return 0;
}
