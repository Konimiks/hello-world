#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;

View view;

void getplayercoordinateforview(float x,float y)
{
    float tempX = x;
    float tempY = 150;


	if (x < 100) tempX = 100;//������� �� ���� ����� �������
	if (x > 6180) tempX = 6180;
	//if (y < 150) tempY = 150;//������� �������
	//if (y > 150) tempY = 150;//������ �������

	view.setCenter(tempX + 60, tempY);
}




