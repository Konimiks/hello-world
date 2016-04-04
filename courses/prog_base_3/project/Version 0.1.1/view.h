#include <SFML/Graphics.hpp>
using namespace sf;

View view;

void getplayercoordinateforview(float x,float y)
{
    float tempX = x;
    float tempY = y;

	if (x < 280) tempX = 280;//убираем из вида левую сторону
	if (y < 200) tempY = 200;//верхнюю сторону
	if (y > 440) tempY = 440;//нижнюю сторону

	view.setCenter(tempX, tempY);
}




