#include <SFML/Graphics.hpp>
#include "map1.h"
#include "view.h"

#define MyRectangleSize 32

using namespace sf;

class PLAYER
{
public:
    String File;
    Image image;
    Texture texture;
    Sprite sprite;
    float dx, dy;
    FloatRect rect; //(x,y,w,h)
    bool onGround;
    float currentFrame;

    PLAYER(String F)
    {
        dx = 0;
        dy = 0;
        File = F;
        rect = FloatRect(50, 50, 29, 29);
        currentFrame = 0;
        image.loadFromFile(File);
        image.createMaskFromColor(Color(255, 255, 255));
        texture.loadFromImage(image);
        sprite.setTexture(texture);
        sprite.setTextureRect(IntRect(90, 4, 29, 29));

    }

    float getplayercoordinateX()
    {
		return rect.left;
	}
	float getplayercoordinateY()
	{
		return rect.top;
	}

    void interactionWithMap(int dir)
	{

			for (int i = rect.top / 32; i < (rect.top + rect.height) / 32; i++)
                for (int j = rect.left/ 32; j<(rect.left + rect.width) / 32; j++)
			{
			    if(TileMap[i][j] == 's')
                {
                    TileMap[i][j] = ' ';
                }
				if(TileMap[i][j] == '0')
				{
				    if (dx > 0 && dir == 0)
					{
						rect.left = j * 32 - rect.width;
					}
					if (dx < 0 && dir == 0)
					{
						rect.left = j * 32 + 32;
					}
					if (dy > 0 && dir == 1)
					{
						rect.top = i * 32 - rect.height;
						onGround = true;
						dy = 0;
					}
					if (dy < 0 && dir == 1)
					{
						rect.top = i * 32 + 32;
                        dy = 0;
					}
				}
			}
	}

    void update(float time)
    {
        rect.left += dx * time;
        interactionWithMap(0);

        if(!onGround)
            dy += 0.0008 * time;
        rect.top += dy * time;
        onGround = false;
        interactionWithMap(1);

        currentFrame += 0.005 * time;
        if(currentFrame > 4)
            currentFrame -= 4;

        if(dx > 0)
            sprite.setTextureRect(IntRect(90 + 30 * (int)currentFrame, 4, 29, 29));
        if(dx < 0)
            sprite.setTextureRect(IntRect(210 - 30 * (int)currentFrame, 4, -29, 29));

        sprite.setPosition(rect.left, rect.top);
        getplayercoordinateforview(getplayercoordinateX(), getplayercoordinateY());
        dx = 0;
    }
};

int main(void)
{
    RenderWindow window(VideoMode (1366, 768), "Chaos Knight Game", Style::Fullscreen);
    view.reset(FloatRect(0, 0, 560, 400));

    PLAYER p("knight.png");

    Clock clock;

    //blocks tileset
    Image map_image;
	map_image.loadFromFile("set1.png");
	Texture map_t;
	map_t.loadFromImage(map_image);
	Sprite s_map;
	s_map.setTexture(map_t);

    //cointile
    Image coin_image;
    coin_image.loadFromFile("coin.png");
    coin_image.createMaskFromColor(Color(255, 255, 255));
    Texture coin_t;
    coin_t.loadFromImage(coin_image);
    Sprite s_coin;
    s_coin.setTexture(coin_t);
    float coinCurrentFrame = 0;


    while(window.isOpen())
    {
        float time = clock.getElapsedTime().asMicroseconds();
        clock.restart();
        time = time/800;

        Event event;

        while(window.pollEvent(event))
        {
            if(event.type == Event::Closed)
                window.close();
        }

        if (Keyboard::isKeyPressed(Keyboard::Escape))
        {
            window.close();
        }

        if(Keyboard::isKeyPressed(Keyboard::Left))
        {
            p.dx -= 0.1;
        }

        if(Keyboard::isKeyPressed(Keyboard::Right))
        {
            p.dx += 0.1;
        }

        if(Keyboard::isKeyPressed(Keyboard::Up))
        {
            if(p.onGround)
            {
                p.dy -= 0.5;
                p.onGround = false;
            }
        }

        p.update(time);

        window.setView(view);
        window.clear(Color::White);

        for(int i = 0; i < HEIGHT_MAP; i++)
            for(int j = 0; j < WIDTH_MAP; j++)
        {
            coinCurrentFrame += 0.0000063* time;
            if(TileMap[i][j] == '0')
            {
                s_map.setTextureRect(IntRect(0, 0, MyRectangleSize, MyRectangleSize));
                s_map.setPosition(j * MyRectangleSize, i * MyRectangleSize);
                window.draw(s_map);
            }
            if(TileMap[i][j] == 's')
            {
                if(coinCurrentFrame > 4)
                    coinCurrentFrame -= 4;
                s_coin.setTextureRect(IntRect(448 + 32 * (int) coinCurrentFrame, 72, MyRectangleSize, MyRectangleSize));
                s_coin.setPosition(j * MyRectangleSize, i * MyRectangleSize);
                window.draw(s_coin);
            }
            if(TileMap[i][j] == ' ')
                continue;

        }

        window.draw(p.sprite);
        window.display();


    }
    return 0;
}

