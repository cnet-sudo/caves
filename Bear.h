#pragma once
#include "Character.h"

class Bear: public Character
{
public:
	// ����������� �������
	Bear();
	//  ���������������� ���������� ����� ��� �������
	bool virtual handleInput();

};

