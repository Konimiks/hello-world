#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include <vector>
#include <list>
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
	int health;
	bool life, onGround;
	bool moveDirection;
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

	virtual void update(float time) = 0;

	FloatRect getRect(){
        return FloatRect(rect.left, rect.top, rect.width, rect.height);
	}
};

class PLAYER : public Entity
{
public:
    int score;
    bool downStatus;
    enum { left, right, up, down, jump, stay } state;
    PLAYER(Image &image, Level &lev, float X, float Y, int W, int H, String Name) : Entity(image,X,Y,W,H,Name)
    {
        downStatus = false;
        health = 1000000;
        moveDirection = true;
        obj = lev.GetAllObjects();
        state = stay;
        score = 0;
        rect = FloatRect(X, Y, W, H);
        sprite.setTextureRect(IntRect(2, 77, W, H));
    }

    void control()
    {
        // right and left together == stay!
        if(Keyboard::isKeyPressed(Keyboard::Right) && Keyboard::isKeyPressed(Keyboard::Left))
        {
            moveDirection = true;
            state = stay;
        }

        //left move
        else if(Keyboard::isKeyPressed(Keyboard::Left))
        {
            moveDirection = false;
            state = left;
            dx -= 0.07;
        }

        //rigth move
        else if(Keyboard::isKeyPressed(Keyboard::Right))
        {
            moveDirection = true;
            state = right;
            dx += 0.07;
        }

        //jump
        if(Keyboard::isKeyPressed(Keyboard::Up))
        {
            if(onGround)
            {
                dy -= 0.4;
                onGround = false;
            }
        }

        //down
        if(Keyboard::isKeyPressed(Keyboard::Down))
            {
                if(dy)
                {
                    downStatus = true;
                }
            }
        if(!Keyboard::isKeyPressed(Keyboard::Down) && !Keyboard::isKeyPressed(Keyboard::Up) && !Keyboard::isKeyPressed(Keyboard::Right) && !Keyboard::isKeyPressed(Keyboard::Left))
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
        if(health <= 0)
            life = false;

        rect.left += dx * time;
        interactionWithMap(0);

        if(!onGround)
            dy += 0.0008 * time;
        rect.top += dy * time;
        onGround = false;
        interactionWithMap(1);

        currentFrame += 0.0065 * time;
        if(currentFrame > 4)
            currentFrame -= 4;

        if(dy == 0){
            downStatus = false;
        }

        //if(downStatus)
        //    state = down;

        if(downStatus)
        {
            sprite.setTextureRect(IntRect(0, 223, 34, 34));
        }
        else if(dy != 0 && !onGround && moveDirection)
            sprite.setTextureRect(IntRect(23, 401, 34, 34));
        else if(dy != 0 && !onGround && !moveDirection)
            sprite.setTextureRect(IntRect(56, 401, -34, 34));
        else if(state == stay && moveDirection)
        {
            sprite.setTextureRect(IntRect(2, 0, 34, 34));
            currentFrame = 0;
        }
        else if(state == stay && !moveDirection)
        {
            sprite.setTextureRect(IntRect(35, 0, -34, 34));
            currentFrame = 0;
        }
        else if(state == right)
            sprite.setTextureRect(IntRect(2 + 42 * (int)currentFrame, 77, 34, 34));
        else if(state == left)
            sprite.setTextureRect(IntRect(162 - 42 * (int)currentFrame, 77, -34, 34));

        sprite.setPosition(rect.left, rect.top);
        if (life)
            getplayercoordinateforview(getplayercoordinateX(), getplayercoordinateY());
        dx = 0;
    }
};

class Enemy : public Entity{
public:
	Enemy(Image &image, Level &lev,float X, float Y,int W,int H,String Name):Entity(image,X,Y,W,H,Name){
		obj = lev.GetObjects("solid");
		if (name == "EasyEnemy"){
            health = 1;
			sprite.setTextureRect(IntRect(2, 2, rect.width, rect.height));
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
	    if(health <= 0)
            life = false;
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
    //Style::Fullscreen
    RenderWindow window(VideoMode (1366, 768), "Chaos Knight Game", Style::Fullscreen );
    view.reset(FloatRect(0, 0, 320, 240));

    list<Entity*>  entities;
	list<Entity*>::iterator it;

    Level lvl;
    lvl.LoadFromFile("lvl1.tmx");
    Object player = lvl.GetObject("player");
    vector<Object> eEnemies = lvl.GetObjects("EasyEnemy");

    Clock clock;

    Font font;
    font.loadFromFile("AnkePrint.ttf");
    Text text("", font, 20);
    text.setColor(Color::Red);
    text.setStyle(sf::Text::Bold);

    Image enemy_image_beeto;
    enemy_image_beeto.loadFromFile("Beeto.png");
    enemy_image_beeto.createMaskFromColor(Color(0, 255, 0));
    for (int i = 0; i < eEnemies.size(); i++)
		entities.push_back(new Enemy(enemy_image_beeto, lvl, eEnemies[i].rect.left, eEnemies[i].rect.top, 25, 15, "EasyEnemy"));

    Image hero_image;
	hero_image.loadFromFile("knight2.png");
	hero_image.createMaskFromColor(Color(0, 255, 0));
	hero_image.createMaskFromColor(Color(255, 0, 0));
	hero_image.createMaskFromColor(Color(0, 128, 128));
    PLAYER p(hero_image, lvl, player.rect.left, player.rect.top, 34, 34, "Chaos Knight");

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
        /*for (it = entities.begin(); it != entities.end(); it++)
            {
                (*it)->update(time);
            }
        */
        for (it = entities.begin(); it != entities.end();)
		{
			Entity *b = *it;
			b->update(time);
			if (b->life == false)
                {
                    it = entities.erase(it);
                    delete b;
                }
			else it++;
		}

		for (it = entities.begin(); it != entities.end(); it++)
		{
			if ((*it)->getRect().intersects(p.getRect()))
			{
				if ((*it)->name == "EasyEnemy")
                    {
                        if ((p.dy > 0) && !p.onGround && p.downStatus)
                            {
                                (*it)->dx = 0;
                                p.dy = -0.35;
                                (*it)->health = 0;
                            }
                        else {
                            p.health -= 5;
                        }
                    }
			}
		}

        window.setView(view);
        window.clear(Color::White);

        lvl.Draw(window);

        ostringstream msg;
        msg << "Health:" << p.health;
        text.setString(msg.str());
		text.setPosition(view.getCenter().x - 155, view.getCenter().y - 125);
		window.draw(text);

        for (it = entities.begin(); it != entities.end(); it++){
			window.draw((*it)->sprite);
		}
        window.draw(p.sprite);
        window.display();

    }
    return 0;
}

