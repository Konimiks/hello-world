#include <SFML/Graphics.hpp>
using namespace sf;

View view;

void getplayercoordinateforview(float x,float y)
{
    float tempX = x;
    float tempY = y;

	if (x < 280) tempX = 280;//������� �� ���� ����� �������
	if (y < 200) tempY = 200;//������� �������
	if (y > 440) tempY = 440;//������ �������

	view.setCenter(tempX, tempY);
}




