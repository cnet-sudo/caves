#pragma once
#include "Character.h"

class Bear: public Character
{
public:
	// конструктор медведя
	Bear();
	//  Переопределенный обработчик ввода для медведя
	bool virtual handleInput();

};

