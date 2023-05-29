#pragma once
#include "Character.h"

class Masha : public Character
{
public:
	// конструктор медведя
	Masha();
	//  Переопределенный обработчик ввода для медведя
	bool virtual handleInput();

};

