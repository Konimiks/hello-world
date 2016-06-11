#pragma once
#ifndef CLASSES_H
#define CLESSES_H
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <sstream>
#include <vector>
#include <list>
#include <math.h>
#include "view.h"
#include "level.h"
#include "menu.h"
#include <conio.h>

using namespace sf;
using namespace std;

class Entity {
private:
    Image image;
    Texture texture;
    float currentFrame;
    string name;
    bool life, onGround;
    bool moveDirection;
public:
    enum { left, right, up, down, jump, stay, agro } state;
    vector <Object> obj;
    Sprite sprite;
    float shieldTimer, attackTimer;
    float dx, dy;
    FloatRect rect;
	int health;

	bool agroStatus;

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

	float getcurrentFrame(){
        return currentFrame;
	}
	void addcurrentFrame(float val){
        currentFrame += val;
	}
	void minuscurrentFrame(float val){
        currentFrame -= val;
	}
	void setcurrentFrame(float val){
        currentFrame = val;
	}

    string getname(){
        return name;
    }

    bool getlife(){
        return life;
    }
    void setlife(bool stm){
        life = stm;
    }
    bool getonGround(){
        return onGround;
    }
    void setonGround(bool stm){
        onGround = stm;
    }
    bool getmoveDirection(){
        return moveDirection;
    }
    void setmoveDirection(bool stm){
        moveDirection = stm;
    }

    void ultimate(){
        dy -= 1.5;
    }
};

class PLAYER : public Entity
{
public:
    bool getDamageStatus;
    int score;
    bool downStatus;
    PLAYER(Image &image, Level &lev, float X, float Y, int W, int H, String Name) : Entity(image,X,Y,W,H,Name)
    {
        getDamageStatus = true;
        shieldTimer = 0;
        downStatus = false;
        health = 100;
        setmoveDirection(true);
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
            setmoveDirection(true);
            state = stay;
        }

        //left move
        else if(Keyboard::isKeyPressed(Keyboard::Left))
        {
            setmoveDirection(false);
            state = left;
            dx -= 0.08;
        }

        //rigth move
        else if(Keyboard::isKeyPressed(Keyboard::Right))
        {
            setmoveDirection(true);
            state = right;
            dx += 0.08;
        }

        //jump
        if(Keyboard::isKeyPressed(Keyboard::Up))
        {
            if(getonGround())
            {
                dy -= 0.42;
                setonGround(false);
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
            for (unsigned int i = 0; i<obj.size(); i++)
               if (getRect().intersects(obj[i].rect))
               {
                   if (obj[i].name == "solid")
                   {
                       if (dy>0 && dir == 1)	{ rect.top = obj[i].rect.top - rect.height;  dy = 0; setonGround(true);}
                       if (dy<0 && dir == 1)	{ rect.top = obj[i].rect.top + obj[i].rect.height;   dy = 0;}
                       if (dx>0 && dir == 0)	{ rect.left = obj[i].rect.left - rect.width; }
                       if (dx<0 && dir == 0)	{ rect.left = obj[i].rect.left + obj[i].rect.width; }
                   }
                   if (obj[i].name == "death"){
                        health = 0;
                   }
               }
	}

    void update(float time)
    {
        if(health <= 0)
            setlife(false);
        if(shieldTimer > 0 && getlife()){
            shieldTimer -= 0.001 * time;
            if(getDamageStatus){
                sprite.setColor(Color(255,0,0));
                getDamageStatus = !getDamageStatus;
            }
            else{
                sprite.setColor(Color(255,255,255));
                getDamageStatus = !getDamageStatus;
            }
        }
        else
            sprite.setColor(Color(255,255,255));

        rect.left += dx * time;
        interactionWithMap(0);

        if(!getonGround())
            dy += 0.0008 * time;
        rect.top += dy * time;
        setonGround(false);
        interactionWithMap(1);

        addcurrentFrame(0.0065 * time);
        if(getcurrentFrame() > 4)
            minuscurrentFrame(4.0);

        if(dy == 0 && rect.top > 5){
            downStatus = false;
        }

        if(!getlife())
            sprite.setTextureRect(IntRect(80, 816, 34, 34));
        else if(downStatus)
        {
            sprite.setTextureRect(IntRect(0, 223, 34, 34));
        }
        else if(dy != 0 && !getonGround() && getmoveDirection())
            sprite.setTextureRect(IntRect(23, 401, 34, 34));
        else if(dy != 0 && !getonGround() && !getmoveDirection())
            sprite.setTextureRect(IntRect(56, 401, -34, 34));
        else if(state == stay && getmoveDirection())
        {
            sprite.setTextureRect(IntRect(2, 0, 34, 34));
            setcurrentFrame(0);
        }
        else if(state == stay && !getmoveDirection())
        {
            sprite.setTextureRect(IntRect(35, 0, -34, 34));
            setcurrentFrame(0);
        }
        else if(state == right)
            sprite.setTextureRect(IntRect(2 + 42 * (int)getcurrentFrame(), 77, 34, 34));
        else if(state == left)
            sprite.setTextureRect(IntRect(162 - 42 * (int)getcurrentFrame(), 77, -34, 34));

        sprite.setPosition(rect.left, rect.top);
        if (getlife())
            getplayercoordinateforview(getplayercoordinateX(), getplayercoordinateY());
        dx = 0;
    }
};

class Enemy : public Entity{
public:
	Enemy(Image &image, Level &lev,float X, float Y,int W,int H,String Name):Entity(image,X,Y,W,H,Name){
		obj = lev.GetAllObjects();
		shieldTimer = 0;
		if (getname() == "EasyEnemy")
        {
            health = 3;
			sprite.setTextureRect(IntRect(2, 2, rect.width, rect.height));
			dx = -0.015;
		}
		if (getname() == "MediumEnemy")
        {
            health = 5;
            setonGround(true);
			sprite.setTextureRect(IntRect(2, 2, rect.width, rect.height));
			dx = -0.02;
		}
        if (getname() == "HardEnemy")
        {
            health = 10;
            sprite.setTextureRect(IntRect(2, 2, rect.width, rect.height));
            dx = - 0.01;
        }
        if (getname() == "polarKnight")
        {
            health = 25;
            sprite.setTextureRect(IntRect(0, 80, rect.width, rect.height));
            dx = -0.035;
            attackTimer = 20;
        }
        if(getname() == "Samurai")
        {
            health = 4;
            state = stay;
            rect.width = 19;
            rect.height = 15;
            sprite.setTextureRect(IntRect(2, 2, rect.width, rect.height));
            dx = - 0.02;
        }
	}

	void interactionWithMap(int dir)
	{
			for (unsigned int i = 0; i<obj.size(); i++)
               if (getRect().intersects(obj[i].rect))
               {
                   if (obj[i].name == "samuraiWall" && getname() == "Samurai")
                   {
                       if (dx>0 && dir == 0)	{ rect.left = obj[i].rect.left - rect.width; dx = -dx;}
                       else if (dx<0 && dir == 0)	{ rect.left = obj[i].rect.left + obj[i].rect.width; dx = -dx;}
                   }
                   if (obj[i].name == "henemyWall" && getname() == "HardEnemy")
                   {
                       if (dx>0 && dir == 0)	{ rect.left = obj[i].rect.left - rect.width; dx = -dx;}
                       else if (dx<0 && dir == 0)	{ rect.left = obj[i].rect.left + obj[i].rect.width; dx = -dx;}
                   }
                   if (obj[i].name == "menemyWall" && getname() == "MediumEnemy")
                   {
                       if (dx>0 && dir == 0)	{ rect.left = obj[i].rect.left - rect.width; dx = -dx;}
                       else if (dx<0 && dir == 0)	{ rect.left = obj[i].rect.left + obj[i].rect.width; dx = -dx;}
                   }
                   if (obj[i].name == "enemyWall" && getname() == "EasyEnemy")
                   {
                       if (dx>0 && dir == 0)	{ rect.left = obj[i].rect.left - rect.width; dx = -dx;}
                       else if (dx<0 && dir == 0)	{ rect.left = obj[i].rect.left + obj[i].rect.width; dx = -dx;}
                   }
                   if (getname() != "polarKnight" && obj[i].name == "solid")
                   {
                       if (dy>0 && dir == 1)	{ rect.top = obj[i].rect.top - rect.height;  dy = 0; setonGround(true); }
                       if (dy<0 && dir == 1)	{ rect.top = obj[i].rect.top + obj[i].rect.height;   dy = 0; }
                       if (dx>0 && dir == 0)	{ rect.left = obj[i].rect.left - rect.width; }
                       if (dx<0 && dir == 0)	{ rect.left = obj[i].rect.left + obj[i].rect.width; }
                   }
                   if (getname() == "polarKnight" && obj[i].name == "solidBoss")
                   {
                       if (dy>0 && dir == 1)	{ rect.top = obj[i].rect.top - rect.height;  dy = 0; setonGround(true); }
                       if (dy<0 && dir == 1)	{ rect.top = obj[i].rect.top + obj[i].rect.height;   dy = 0; }
                       if (dx>0 && dir == 0)	{ rect.left = obj[i].rect.left - rect.width; }
                       if (dx<0 && dir == 0)	{ rect.left = obj[i].rect.left + obj[i].rect.width; }
                   }
                   if (getname() == "polarKnight" && obj[i].name == "wallBoss")
                   {
                       if (dx>0 && dir == 0)	{ rect.left = obj[i].rect.left - rect.width; dx = -dx;}
                       else if (dx<0 && dir == 0)	{ rect.left = obj[i].rect.left + obj[i].rect.width; dx = -dx;}
                   }
               }
	}

	void update(float time)
	{
	    if(health <= 0)
            setlife(false);
		if (getname() == "EasyEnemy"){
            if(shieldTimer > 0 && getlife()){
                shieldTimer -= 0.001 * time;

            }
			rect.left += dx * time;
			interactionWithMap(0);

            if(!getonGround())
            dy += 0.0008 * time;
            rect.top += dy * time;
            setonGround(false);
            interactionWithMap(1);

            addcurrentFrame(0.0065 * time);
            if(getcurrentFrame() > 4)
                minuscurrentFrame(4.0);

            if(dx > 0)
                state = right;
            else
                state = left;

            if(state == right)
                sprite.setTextureRect(IntRect(2 + 28 * (int)getcurrentFrame(), 2, 25, 15));
            else if(state == left)
                sprite.setTextureRect(IntRect(111 - 28 * (int)getcurrentFrame(), 2, -25, 15));

            sprite.setPosition(rect.left, rect.top);
		}
		if (getname() == "MediumEnemy"){
            if(shieldTimer > 0 && getlife()){
                shieldTimer -= 0.001 * time;

            }
			rect.left += dx * time;
			interactionWithMap(0);

            addcurrentFrame(0.0065 * time);
            if(getcurrentFrame() > 3)
                minuscurrentFrame(3.0);

            if(dx > 0)
                state = right;
            else
                state = left;

            if(state == right)
                sprite.setTextureRect(IntRect(2 + 36 * (int)getcurrentFrame(), 2, 33, 31));
            else if(state == left)
                sprite.setTextureRect(IntRect(107 - 36 * (int)getcurrentFrame(), 2, -33, 31));

            sprite.setPosition(rect.left, rect.top);
		}
		if(getname() == "HardEnemy")
        {
            if(shieldTimer > 0 && getlife()){
                shieldTimer -= 0.001 * time;

            }

            rect.left += dx * time;
			interactionWithMap(0);

            if(!getonGround())
            dy += 0.0008 * time;
            rect.top += dy * time;
            setonGround(false);
            interactionWithMap(1);

            addcurrentFrame(0.0065 * time);
            if(getcurrentFrame() > 4)
                minuscurrentFrame(4.0);

            if(dx > 0)
                state = right;
            else
                state = left;
            if(state == right)
                sprite.setTextureRect(IntRect(2 + 33 * (int)getcurrentFrame(), 42, rect.width, rect.height));
            else if(state == left)
                sprite.setTextureRect(IntRect(131 - 33 * (int)getcurrentFrame(), 42, -rect.width, rect.height));

            sprite.setPosition(rect.left, rect.top);
        }
        if(getname() == "polarKnight")
        {
            if(shieldTimer > 0 && getlife()){
                shieldTimer -= 0.001 * time;
                sprite.setColor(Color(255,255,0));
            }
            else{
                sprite.setColor(Color(255,255,255));
            }

            if(attackTimer > 0){
                attackTimer -= 0.001 * time;
                if(attackTimer < 8){
                    sprite.setColor(Color(255,100,0));
                }
                if(attackTimer < 4){
                    sprite.setColor(Color(255,0,0));
                }
                if(attackTimer < 0.5){
                    ultimate();
                    attackTimer += 20;
                }
            }

            rect.left += dx * time;
			interactionWithMap(0);

            if(!getonGround())
            dy += 0.0008 * time;
            rect.top += dy * time;
            setonGround(false);
            interactionWithMap(1);

            addcurrentFrame(0.0065 * time);
            if(getcurrentFrame() > 10)
                minuscurrentFrame(10.0);
            if(dx > 0)
                state = right;
            else
                state = left;
            if(state == right)
                sprite.setTextureRect(IntRect(0 + 90 * (int)getcurrentFrame(), 80, rect.width, rect.height));
            else if(state == left)
                sprite.setTextureRect(IntRect(899 - 90 * (int)getcurrentFrame(), 80, -rect.width, rect.height));

            sprite.setPosition(rect.left, rect.top);
        }
        if(getname() == "Samurai")
        {
            rect.left += dx * time;
            interactionWithMap(0);

            if(!getonGround())
            dy += 0.0008 * time;
            rect.top += dy * time;
            setonGround(false);
            interactionWithMap(1);

            addcurrentFrame(0.0065 * time);
            if(getcurrentFrame() > 4)
                minuscurrentFrame(4.0);
            if(dx > 0)
                state = right;
            else
                state = left;
            if(state == right)
                sprite.setTextureRect(IntRect(2 + 22 * (int)getcurrentFrame(), 2, rect.width, rect.height));
            else if(state == left)
                sprite.setTextureRect(IntRect(87 - 22 * (int)getcurrentFrame(), 2, -rect.width, rect.height));

            sprite.setPosition(rect.left, rect.top);
        }
	}
};

class MovingPlatform : public Entity{
public:
	MovingPlatform(Image &image, Level &lev,float X, float Y,int W,int H,String Name):Entity(image,X,Y,W,H,Name){
		obj = lev.GetAllObjects();
		sprite.setTextureRect(IntRect(2, 20, W, H));
		dx = -0.025;
		setmoveDirection(false);
	}

    void interactionWithMap()
    {
        for (unsigned int i = 0; i<obj.size(); i++)
               if (getRect().intersects(obj[i].rect))
               {
                   if (obj[i].name == "PlatformWall" && getname() == "Platform")
                   {
                       if (dx>0)	    { rect.left = obj[i].rect.left - rect.width; dx = -dx; setmoveDirection(false);}
                       else if (dx<0)	{ rect.left = obj[i].rect.left + obj[i].rect.width; dx = -dx; setmoveDirection(true);}
                   }
               }
    }

	void update(float time)
	{
	    if(dx >= 0)
            setmoveDirection(true);
        else
            setmoveDirection(false);
		rect.left += dx * time;
		interactionWithMap();
		sprite.setPosition(rect.left, rect.top);
	}
};

#endif // CLASSES_H
