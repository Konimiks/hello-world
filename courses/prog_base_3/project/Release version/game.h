#pragma once
#ifndef GAME_H
#define GAME_H
#include "classes.h"

bool startGame(RenderWindow & window){
    SoundBuffer udarbuffer;
    udarbuffer.loadFromFile("Udar.wav");
    Sound udarsound;
    udarsound.setBuffer(udarbuffer);

    Music bgmusic;
    if(!bgmusic.openFromFile("bgmusic2.wav")){
        std::cout << "No such music file";
    }
    bgmusic.setLoop(true);

    window.setView(view);
    int lvlNumber = 1;
    int rc = menu(window);
    switch(rc)
    {
        case 1:
            window.close();
            break;
        case 101: lvlNumber = 1; break;
        case 102: lvlNumber = 2; break;
        case 103: lvlNumber = 3; break;
        case 110: lvlNumber = 0; break;
        default: break;
    }

    list<Entity*>  entities;
	list<Entity*>::iterator it;

    ostringstream lvlName;
    lvlName << "lvl" << lvlNumber <<".tmx";

    Level lvl;
    lvl.LoadFromFile(lvlName.str());
    Object player = lvl.GetObject("player");
    vector<Object> eEnemies = lvl.GetObjects("EasyEnemy");
    vector<Object> mEnemies = lvl.GetObjects("MediumEnemy");
    vector<Object> hEnemies = lvl.GetObjects("HardEnemy");
    vector<Object> platforms = lvl.GetObjects("Platform");
    vector<Object> samurai = lvl.GetObjects("Samurai");

    Clock clock;

    Font font;
    font.loadFromFile("AnkePrint.ttf");
    Text text("", font, 15);
    text.setColor(Color::Red);
    text.setStyle(Text::Bold);

    ostringstream fonmsg;
    fonmsg << "fon" << lvlNumber <<".png";
    Image fon_image;
    fon_image.loadFromFile(fonmsg.str());
    Texture fon_texture;
    fon_texture.loadFromImage(fon_image);
    Sprite fon_sprite;
    fon_sprite.setTexture(fon_texture);
    fon_sprite.setScale(0.5, 0.5);

    Text dead("Game Over", font, 30);
    dead.setColor(Color::Red);
    dead.setStyle(Text::Bold);

    Text pauseText("Pause", font, 30);
    pauseText.setColor(Color::Red);
    pauseText.setStyle(Text::Bold);

    if(lvlNumber == 3)
    {
        vector<Object> boss = lvl.GetObjects("Boss");
        Image boss_image;
        boss_image.loadFromFile("polarKnight.png");
        boss_image.createMaskFromColor(Color(0, 255, 0));
        boss_image.createMaskFromColor(Color(0, 128, 128));
        for (unsigned int i = 0; i < boss.size(); i++)
            entities.push_back(new Enemy(boss_image, lvl, boss[i].rect.left, boss[i].rect.top, 87, 79, "polarKnight"));
    }

    Image samurai_image;
    samurai_image.loadFromFile("samurai.png");
    samurai_image.createMaskFromColor(Color(0, 255, 0));
	samurai_image.createMaskFromColor(Color(0, 128, 128));
	for (unsigned int i = 0; i < samurai.size(); i++)
            entities.push_back(new Enemy(samurai_image, lvl, samurai[i].rect.left, samurai[i].rect.top, 19, 15, "Samurai"));

    Image enemy_image_beeto;
    enemy_image_beeto.loadFromFile("Beeto.png");
    enemy_image_beeto.createMaskFromColor(Color(0, 255, 0));
    for (unsigned int i = 0; i < eEnemies.size(); i++)
		entities.push_back(new Enemy(enemy_image_beeto, lvl, eEnemies[i].rect.left, eEnemies[i].rect.top, 25, 15, "EasyEnemy"));

    Image enemy_image_dragon;
    enemy_image_dragon.loadFromFile("Divedrake.png");
    enemy_image_dragon.createMaskFromColor(Color(0, 255, 0));
    for (unsigned int i = 0; i < mEnemies.size(); i++)
		entities.push_back(new Enemy(enemy_image_dragon, lvl, mEnemies[i].rect.left, mEnemies[i].rect.top, 33, 31, "MediumEnemy"));

    Image enemy_image_goldarmor;
    enemy_image_goldarmor.loadFromFile("Goldarmor.png");
    enemy_image_goldarmor.createMaskFromColor(Color(0, 255, 0));
    for (unsigned int i = 0; i < mEnemies.size(); i++)
		entities.push_back(new Enemy(enemy_image_goldarmor, lvl, hEnemies[i].rect.left, hEnemies[i].rect.top, 30, 37, "HardEnemy"));

    Image hero_image;
	hero_image.loadFromFile("knight2.png");
	hero_image.createMaskFromColor(Color(0, 255, 0));
	hero_image.createMaskFromColor(Color(255, 0, 0));
	hero_image.createMaskFromColor(Color(0, 128, 128));
    PLAYER p(hero_image, lvl, player.rect.left, player.rect.top, 34, 34, "Chaos Knight");

    Image platform_image;
    platform_image.loadFromFile("movingPlatform.png");
    platform_image.createMaskFromColor(Color(0, 255, 0));
    platform_image.createMaskFromColor(Color(0, 128, 128));
    for (unsigned int i = 0; i < platforms.size(); i++)
        entities.push_back(new MovingPlatform(platform_image, lvl, platforms[i].rect.left, platforms[i].rect.top, 47, 15, "Platform"));

    bool game_running = true;
    bool win = false;
    bgmusic.play();
    int musicNum = 0;
    ostringstream musicmsg;

    while(window.isOpen())
    {
        view.reset(FloatRect(0,0,320,240));
        game_running = true;
        if(win){
            game_running = false;
        }
        float time = clock.getElapsedTime().asMicroseconds();
        clock.restart();
        time = time/800;

        Event event;

        while(window.pollEvent(event))
        {
            if(event.type == Event::Closed)
                window.close();
        }

        if (Keyboard::isKeyPressed(Keyboard::Escape)){
            return false;
        }
        if (Keyboard::isKeyPressed(Keyboard::Tab)){
            return true;
        }

        if (Keyboard::isKeyPressed(Keyboard::T)){
            musicmsg.str("");
            musicNum++;
            if(musicNum > 5)
                musicNum -= 5;
            musicmsg << "music" << musicNum << ".wav";
            bgmusic.openFromFile(musicmsg.str());
            bgmusic.play();
        }

        if (Keyboard::isKeyPressed(Keyboard::P))
        {
            game_running = false;
        }

        if(game_running){
                if(p.getlife())
                    p.control();
                p.update(time);

                for (it = entities.begin(); it != entities.end();)
                {
                    Entity *b = *it;
                    b->update(time);
                    if (b->getlife() == false)
                        {
                            if(b->getname() == "EasyEnemy")
                                p.score += 10;
                            else if(b->getname() == "MediumEnemy")
                                p.score += 50;
                            else if(b->getname() == "HardEnemy")
                                p.score += 200;
                            else if(b->getname() == "polarKnight")
                                p.score += 1000;
                            it = entities.erase(it);
                            delete b;
                        }
                    else it++;
                }

        }//game running
		for (it = entities.begin(); it != entities.end(); it++)
		{
		    if (((*it)->getname() == "Platform") && ((*it)->getRect().intersects(p.getRect())))
			{
				Entity *movPlat = *it;
				if ((p.dy>0) || !p.getonGround())
                    if(p.rect.top + p.rect.height >= movPlat->rect.top + movPlat->rect.height)
                    {
                        p.rect.top = movPlat->rect.top + movPlat->rect.height ;
                        p.dy = 0;
                        p.setonGround(false);
                    }
                    else if (p.rect.top + p.rect.height < movPlat->rect.top + movPlat->rect.height)
                    {
                        if(p.state == 0 && movPlat->getmoveDirection())
                            p.dx -= 0.05;
                        else if(p.state == 1 && !movPlat->getmoveDirection())
                            p.dx += 0.05;
                        p.rect.top = movPlat->rect.top - p.rect.height + 1;
                        p.rect.left += movPlat->dx*time;
                        p.dy = 0;
                        p.setonGround(true);
                    }
			}

			if ((*it)->getRect().intersects(p.getRect()))
			{
				if ((*it)->getname() == "EasyEnemy")
                {
                    if (!p.getonGround() && p.downStatus)
                        {
                            p.dy = -0.35;
                            if((*it)->shieldTimer <= 0){
                                udarsound.setPlayingOffset(sf::seconds(0.8));
                                udarsound.play();
                                if((*it)->dx > 0)
                                    (*it)->dx += 0.03;
                                if((*it)->dx < 0)
                                    (*it)->dx -= 0.03;
                                (*it)->dx = -(*it)->dx;
                                (*it)->health -=1;
                                (*it)->shieldTimer += 0.1;
                            }
                        }
                    else if(p.shieldTimer <= 0){
                        p.health -= 5;
                        p.shieldTimer += 1.2;
                    }
                }
                if ((*it)->getname() == "MediumEnemy")
                {
                    if (!p.getonGround() && p.downStatus)
                        {
                            p.dy = -0.35;
                            if((*it)->shieldTimer <= 0){
                                udarsound.setPlayingOffset(sf::seconds(0.8));
                                udarsound.play();
                                if((*it)->dx > 0)
                                    (*it)->dx += 0.01;
                                if((*it)->dx < 0)
                                    (*it)->dx -= 0.01;
                                (*it)->dx = -(*it)->dx;
                                (*it)->shieldTimer += 0.1;
                                (*it)->health -= 1;
                            }
                        }
                    else if(p.shieldTimer <= 0){
                        p.health -= 20;
                        p.shieldTimer += 1.2;
                    }
                }
                if ((*it)->getname() == "HardEnemy")
                {
                    if (!p.getonGround() && p.downStatus)
                        {
                            p.dy = -0.35;
                            if((*it)->shieldTimer <= 0){
                                udarsound.setPlayingOffset(sf::seconds(0.8));
                                udarsound.play();
                                if((*it)->dx > 0)
                                    (*it)->dx += 0.02;
                                if((*it)->dx < 0)
                                    (*it)->dx -= 0.02;
                                (*it)->dx = -(*it)->dx;
                                (*it)->health -=1;
                                (*it)->shieldTimer += 0.1;
                            }

                        }
                    else if(p.shieldTimer <= 0){
                        p.health -= 20;
                        p.shieldTimer += 1.2;
                    }
                }
                if ((*it)->getname() == "Samurai")
                {
                    if(p.shieldTimer <= 0){
                        p.health -= 5;
                        p.shieldTimer += 1.2;
                    }
                }
                if((*it)->getname() == "polarKnight")
                {
                    if ((*it)->dy > 0 && p.shieldTimer <= 0)
                    {
                        p.health -= 30;
                        p.shieldTimer += 1.2;
                    }
                    if (!p.getonGround() && p.downStatus)
                        {
                            p.dy = -0.35;
                            if((*it)->shieldTimer <= 0){
                                (*it)->dx = -(*it)->dx;
                                (*it)->health -= 1;
                                (*it)->shieldTimer += 2;
                                if((*it)->health % 5 == 0){
                                    if((*it)->dx > 0)
                                        (*it)->dx += 0.007;
                                    else (*it)->dx -= 0.007;
                                    (*it)->shieldTimer += 5;
                                    (*it)->ultimate();
                                }
                            }
                        }
                    else if(p.shieldTimer <= 0){
                        p.health -= 10;
                        p.shieldTimer += 1.2;
                    }
                }
            }
		}
        if(lvlNumber == 3)
            view.setCenter(160, 150);
        window.setView(view);
        window.clear(Color::White);

        if(lvlNumber == 3)
        {
            window.draw(fon_sprite);
        }

        lvl.Draw(window);

        ostringstream msg;
        msg << "Health:" << p.health << "     Score:" << p.score;
        text.setString(msg.str());
		text.setPosition(view.getCenter().x - 160, view.getCenter().y - 127);
		window.draw(text);

        if(!p.getlife()){
            window.draw(p.sprite);
        }
        for (it = entities.begin(); it != entities.end(); it++){
			window.draw((*it)->sprite);
		}
		if(p.getlife())
            window.draw(p.sprite);
        if(!p.getlife()){
            dead.setPosition(view.getCenter().x - 70, view.getCenter().y - 25);
            window.draw(dead);
            window.display();
            sleep(seconds(3.5));
            return true;
        }
        if(win){
            pauseText.setString("You WIN");
            pauseText.setPosition(view.getCenter().x - 60, view.getCenter().y - 25);
            window.draw(pauseText);
            window.display();
            sleep(seconds(3.5));
             std::ofstream fout("file.txt");
            if (!fout.is_open())
                std::cout << "File Not Exist\n";
            lvlNumber++;
            fout << lvlNumber;
            return true;
        }
        else if(!game_running){
            pauseText.setString("Pause");
            pauseText.setPosition(view.getCenter().x - 40, view.getCenter().y - 25);
            window.draw(pauseText);
        }
        if(lvlNumber == 1 && p.score == 290){
            win = true;
        }
        if(lvlNumber == 3 && p.score == 1000){
            win = true;
        }
        if(lvlNumber == 2 && p.getplayercoordinateX() > 6300){
            win = true;
        }
        if(lvlNumber == 0 && p.score == 20)
        {
            win = true;
        }

        window.display();

    }
    return false;
}

void gameRunning(RenderWindow & window){
	if (startGame(window)) {
	    view.reset(FloatRect(0,0,320,240));
        window.setView(view);
        gameRunning(window);
	}
}


#endif // GAME_H
