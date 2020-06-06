#include <iostream>
#include <chrono>
#include <queue>
#include <stack>
#include <vector>
#include <algorithm>
#include "tocka.h"

using namespace std;
using namespace std::chrono;

void draw(tocka** playground, tocka& a, tocka& b, tocka& x, const int MAX_REDAKA, const int MAX_STUPACA)
{
	system("cls");
	for (int i = 0; i < MAX_REDAKA; i++)
	{
		for (int j = 0; j < MAX_STUPACA; j++)
		{
			if (x.x == i && x.y == j)
			{
				cout << "x";
			}
			else if (a.x == i && a.y == j)
			{
				cout << "A";
			}
			else if (b.x == i && b.y == j)
			{
				cout << "B";
			}
			else if (playground[i][j].zid)
			{
				cout << "*";
			}
			else
			{
				cout << "-";
			}
		}
		cout << endl;
	}
}

void save_path(vector<tocka> t, stack<tocka>& put)
{
	if (t.size() == 0)
	{
		return;
	}
	save_path(t[0].roditelj, put);
	put.emplace(t[0].x, t[0].y);
	return;
}

void calculate_path(tocka** playground, stack<tocka>& put, tocka& a, tocka& b, const int MAX_REDAKA, const int MAX_STUPACA)
{
	int broj_reda[] = { -1, 1, 0, 0 };
	int broj_stupca[] = { 0, 0, -1, 1 };

	queue<tocka> q;
	b.posjecena = 1;
	q.push(b);

	while (!q.empty())
	{
		tocka temp = q.front();
		q.pop();

		vector<tocka> temp_vektor{ temp };

		if (temp.x == a.x && temp.y == a.y)
		{
			save_path(temp_vektor, put);
			return;
		}

		for (int i = 0; i < 4; i++)
		{
			int x = temp.x + broj_reda[i];
			int y = temp.y + broj_stupca[i];

			if (x >= 0 && x < MAX_REDAKA && y >= 0 && y < MAX_STUPACA && !playground[x][y].zid && !playground[x][y].posjecena)
			{
				playground[x][y].roditelj = temp_vektor;
				q.push(playground[x][y]);
				playground[x][y].posjecena = 1;
			}
		}
	}
}

int main()
{
	const int MAX_REDAKA = 20;
	const int MAX_STUPACA = 40;

	tocka** playground = new tocka*[MAX_REDAKA];
	for (int i = 0; i < MAX_REDAKA; i++)
	{
		playground[i] = new tocka[MAX_STUPACA];
	}

	for (int i = 0; i < MAX_REDAKA; i++)
	{
		for (int j = 0; j < MAX_STUPACA; j++)
		{
			playground[i][j].x = i;
			playground[i][j].y = j;
			playground[i][j].zid = 0;
			playground[i][j].posjecena = 0;
		}
	}

	for (int i = 0; i < 10; i++)
	{
		playground[i][10].zid = 1;
	}

	stack<tocka> put;

	int x;
	int y;
	cout << "A redak: ";
	cin >> x;
	cout << "A stupac: ";
	cin >> y;
	tocka a(x - 1, y - 1, 0, 0);
	cout << "B redak: ";
	cin >> x;
	cout << "B stupac: ";
	cin >> y;
	tocka b(x - 1, y - 1, 0, 0);

	calculate_path(playground, put, a, b, MAX_REDAKA, MAX_STUPACA);

	while (!put.empty())
	{
		tocka x = put.top();
		put.pop();
		draw(playground, a, b, x, MAX_REDAKA, MAX_STUPACA);
		auto begin = high_resolution_clock::now();
		while (true)
		{
			auto end = high_resolution_clock::now();
			if (duration_cast<milliseconds>(end - begin).count() >= 100)
			{
				break;
			}
		}
	}

	for (int i = 0; i < MAX_REDAKA; ++i) {
		delete[] playground[i];
	}
	delete[] playground;

	return 0;
}
