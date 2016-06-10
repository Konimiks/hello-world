#include <SFML/Graphics.hpp>
using namespace sf;

View view;

void getplayercoordinateforview(float x,float y)
{
    float tempX = x;
    float tempY = 150;


	if (x < 100) tempX = 100;//убираем из вида левую сторону
	//if (y < 150) tempY = 150;//верхнюю сторону
	//if (y > 150) tempY = 150;//нижнюю сторону

	view.setCenter(tempX + 60, tempY);
}




