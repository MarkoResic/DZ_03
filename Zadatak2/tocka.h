#pragma once
#include <vector>

using namespace std;

struct tocka
{
	int x;
	int y;
	bool zid;
	bool posjecena;
	vector<tocka> roditelj; //nisam uspio s pokazivacima rijesiti, pa stavio vektor s jednim elementom
	tocka(){}
	tocka(int x, int y)
	{
		this->x = x;
		this->y = y;
	}
	tocka(int x, int y, bool zid, bool posjecena)
	{
		this->x = x;
		this->y = y;
		this->zid = zid;
		this->posjecena = posjecena;
	}
};
