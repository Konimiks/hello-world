#include <SFML/Graphics.hpp>
#include "view.h"
#include "level.h"

using namespace sf;
using namespace std;

class Entity {
public:
    vector <Object> obj;
    float currentFrame;
    Image image;
    Texture texture;
    Sprite sprite;
    float dx, dy;
    FloatRect rect;
	//int health;
	bool life, onGround;
	String name;
	Entity(Image &image, float X, float Y,int W,int H,String Name){
	    currentFrame = 0;
		rect.left = X;
		rect.top = Y;
		rect.width = W;
		rect.height = H;
		dx = 0; dy = 0;
		name = Name;
		life = true;
		onGround = false;
		texture.loadFromImage(image);
		sprite.setTexture(texture);
	}

	FloatRect getRect(){
        return FloatRect(rect.left, rect.top, rect.width, rect.height);
	}
};

class PLAYER : public Entity
{
public:
    int score;
    enum { left, right, up, down, jump, stay } state;
    PLAYER(Image &image, Level &lev, float X, float Y, int W, int H, String Name) : Entity(image,X,Y,W,H,Name)
    {
        state = stay;
        score = 0;
        obj = lev.GetAllObjects();
        rect = FloatRect(X, Y, W, H);
        sprite.setTextureRect(IntRect(2, 77, W, H));
    }

    void control()
    {
        if(Keyboard::isKeyPressed(Keyboard::Left))
        {
            state = left;
            dx -= 0.1;
        }

        if(Keyboard::isKeyPressed(Keyboard::Right))
        {
            state = right;
            dx += 0.1;
        }

        if(Keyboard::isKeyPressed(Keyboard::Up))
        {
            if(onGround)
            {
                state = jump;
                dy -= 0.4;
                onGround = false;
            }
        }
        if(!Keyboard::isKeyPressed(Keyboard::Up) && !Keyboard::isKeyPressed(Keyboard::Right) && !Keyboard::isKeyPressed(Keyboard::Left))
        {
            state = stay;
        }
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
            for (int i = 0; i<obj.size(); i++)
               if (getRect().intersects(obj[i].rect))
               {
                   if (obj[i].name == "solid")
                   {
                       if (dy>0 && dir == 1)	{ rect.top = obj[i].rect.top - rect.height;  dy = 0; onGround = true; }
                       if (dy<0 && dir == 1)	{ rect.top = obj[i].rect.top + obj[i].rect.height;   dy = 0; }
                       if (dx>0 && dir == 0)	{ rect.left = obj[i].rect.left - rect.width; }
                       if (dx<0 && dir == 0)	{ rect.left = obj[i].rect.left + obj[i].rect.width; }
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

        /*if(state == stay){
            sprite.setTextureRect(IntRect(2, 77, 34, 34));
            currentFrame = 0;
        }*/
        if(state == right)
            sprite.setTextureRect(IntRect(2 + 42 * (int)currentFrame, 77, 34, 34));
        if(state == left)
            sprite.setTextureRect(IntRect(162 - 42 * (int)currentFrame, 77, -34, 34));

        sprite.setPosition(rect.left, rect.top);
        if (life)
            getplayercoordinateforview(getplayercoordinateX(), getplayercoordinateY());
        dx = 0;
    }
};

class Enemy :public Entity{
public:
	Enemy(Image &image, Level &lev,float X, float Y,int W,int H,String Name):Entity(image,X,Y,W,H,Name){
		obj = lev.GetObjects("solid");
		if (name == "EasyEnemy"){
			sprite.setTextureRect(IntRect(0, 0, rect.width, rect.height));
			dx = -0.01;
		}
	}

	void interactionWithMap(int dir)
	{
			for (int i = 0; i<obj.size(); i++)
               if (getRect().intersects(obj[i].rect))
               {
                   if (obj[i].name == "solid")
                   {
                       if (dy>0 && dir == 1)	{ rect.top = obj[i].rect.top - rect.height;  dy = 0; onGround = true; }
                       if (dy<0 && dir == 1)	{ rect.top = obj[i].rect.top + obj[i].rect.height;   dy = 0; }
                       if (dx>0 && dir == 0)	{ rect.left = obj[i].rect.left - rect.width; }
                       if (dx<0 && dir == 0)	{ rect.left = obj[i].rect.left + obj[i].rect.width; }
                   }
               }
	}

	void update(float time)
	{
		if (name == "EasyEnemy"){
			rect.left += dx * time;
			interactionWithMap(0);

            if(!onGround)
            dy += 0.0008 * time;
            rect.top += dy * time;
            onGround = false;
            interactionWithMap(1);

            sprite.setPosition(rect.left, rect.top);
		}
	}
};

int main(void)
{
    RenderWindow window(VideoMode (1366, 768), "Chaos Knight Game", Style::Fullscreen);
    view.reset(FloatRect(0, 0, 320, 240));

    Level lvl;
    lvl.LoadFromFile("lvl1.tmx");
    Object player = lvl.GetObject("player");
	Object easyEnemyObject = lvl.GetObject("easyEnemy");

    Clock clock;

    /*
    Image enemy_image;
    enemy_image.loadFromFile("knight.png");
	enemy_image.createMaskFromColor(Color(255, 255, 255));
    Enemy e(enemy_image, lvl, 100, 100, 29, 29, "EasyEnemy");
    */

    Image hero_image;
	hero_image.loadFromFile("knight2.png");
	hero_image.createMaskFromColor(Color(0, 255, 0));
	hero_image.createMaskFromColor(Color(255, 0, 0));
	hero_image.createMaskFromColor(Color(0, 128, 128));
    PLAYER p(hero_image, lvl, 50, 50, 34, 34, "Chaos Knight");

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

        p.control();
        p.update(time);
        //e.update(time);

        window.setView(view);
        window.clear(Color::White);

        lvl.Draw(window);

        //window.draw(e.sprite);
        window.draw(p.sprite);
        window.display();

    }
    return 0;
}

