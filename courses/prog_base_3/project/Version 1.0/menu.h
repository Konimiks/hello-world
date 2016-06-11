#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

using namespace sf;

int menu(RenderWindow & window) {
	Texture menuBackground, menuTexture;
	menuBackground.loadFromFile("backgr.jpg");
	Image menuimage;
	menuimage.loadFromFile("lvlsnew.png");
	menuimage.createMaskFromColor(Color(255,255,255));
	menuTexture.loadFromImage(menuimage);
	Sprite exitButton(menuTexture), menuBg(menuBackground), lvl1(menuTexture),
            lvl2(menuTexture), lvl3(menuTexture);
    menuBg.setScale(0.7, 0.7);

    Music music;
    if(!music.openFromFile("menumusic.wav")){
        std::cout << "No such music file";
    }
    music.setLoop(true);
    music.play();

	exitButton.setTextureRect(IntRect(0, 205, 75, 50));
	lvl1.setTextureRect(IntRect(0, 55, 200, 50));
	lvl2.setTextureRect(IntRect(0, 105 , 230, 50));
	lvl3.setTextureRect(IntRect(0, 155, 95, 50));
	bool isMenu = true;
	int menuNum = 0;

	lvl1.setPosition(50, 200);
	lvl2.setPosition(50, 250);
	lvl3.setPosition(50, 300);
	exitButton.setPosition(50, 350);
	menuBg.setPosition(0, 0);

    int rc = 0;

	while (isMenu)
	{
	    lvl1.setScale(1,1);
	    lvl2.setScale(1,1);
	    lvl3.setScale(1,1);
	    exitButton.setScale(1,1);

		menuNum = 0;

        if (Keyboard::isKeyPressed(Keyboard::Escape))
        {
            rc = 1;
            isMenu = false;
        }
        if (Keyboard::isKeyPressed(Keyboard::Num1))
        {
            rc = 101;
        }
        else if (Keyboard::isKeyPressed(Keyboard::Num2))
        {
            rc = 102;
        }
        else if (Keyboard::isKeyPressed(Keyboard::Num3))
        {
            rc = 103;
        }
        if (Keyboard::isKeyPressed(Keyboard::Space) && rc > 100)
        {
            isMenu = false;
        }


        if (IntRect(50, 200, 200, 50).contains(Mouse::getPosition(window)))
        {
            menuNum = 101;
            lvl1.setScale(1.2, 1.2);
        }
        if (IntRect(50, 250, 230, 50).contains(Mouse::getPosition(window)))
        {
            menuNum = 102;
            lvl2.setScale(1.2, 1.2);
        }
        if (IntRect(50, 300, 95, 50).contains(Mouse::getPosition(window)))
        {
            menuNum = 103;
            lvl3.setScale(1.2, 1.2);
        }
        if (IntRect(50, 350, 95, 50).contains(Mouse::getPosition(window)))
        {
            menuNum = 2;
            exitButton.setScale(1.2, 1.2);
        }

		if (Mouse::isButtonPressed(Mouse::Left))
		{
			if (menuNum == 2)
			{
			    rc = 1;
                isMenu = false;
			}
			if(menuNum == 101)
            {
                rc = 101;
                isMenu = false;
            }
            if(menuNum == 102)
            {
                rc = 102;
                isMenu = false;
            }
            if(menuNum == 103)
            {
                rc = 103;
                isMenu = false;
            }
		}

		window.draw(menuBg);
		window.draw(exitButton);
		window.draw(lvl1);
		window.draw(lvl2);
		window.draw(lvl3);

		window.display();
	}
	return rc;
}
