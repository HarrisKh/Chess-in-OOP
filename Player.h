#pragma once
#include <string>
#include "Helper.h"
using namespace std;

class Player
{
	string name;
	COLOR color;
public:
	Player(string n, COLOR c);
	string getName()const;
	COLOR getColor()const;
};