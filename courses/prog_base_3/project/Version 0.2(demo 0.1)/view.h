#include <SFML/Graphics.hpp>
using namespace sf;

View view;

void getplayercoordinateforview(float x,float y)
{
    float tempX = x;
    float tempY = 150;


	if (x < 160) tempX = 160;//������� �� ���� ����� �������
	//if (y < 150) tempY = 150;//������� �������
	//if (y > 150) tempY = 150;//������ �������

	view.setCenter(tempX, tempY);
}




