#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#define MENU_SIZE 3
#define START_BUTTON 0
#define OPTIONS_BUTTON 1
#define EXIT_BUTTON 2

using namespace std;
using namespace sf;

int main()
{
	string options[MENU_SIZE] = {"START", "OPTIONS", "EXIT"};



	RenderWindow window(VideoMode(1920, 1080), "SFML");
	window.setFramerateLimit(120);

	RectangleShape ground1(Vector2f(450, 150));
	ground1.setPosition(0, 696);

	RectangleShape ground2(Vector2f(205, 100));
	ground2.setPosition(653, 593);

	RectangleShape ground3(Vector2f(955, 100));
	ground3.setPosition(960, 710);

	RectangleShape ground4(Vector2f(35, 70));
	ground4.setPosition(617, 635);
	ground4.setFillColor(Color::Green);

	RectangleShape volume(Vector2f(200, 20));
	volume.setPosition(850, 540);



	Texture Tbackground, Tkey, Tcoin, tbutton;
	Tbackground.loadFromFile("SFMLProject2.png");
	Tkey.loadFromFile("key2.png");
	Tcoin.loadFromFile("spinning coin2.png");
	tbutton.loadFromFile("button_ui.png");

	Sprite background(Tbackground), key(Tkey, IntRect(0, 0, 39, 39)), coin(Tcoin, IntRect(0, 0, 26, 22));
	background.setPosition(Vector2f(0, 250));
	key.setPosition(790, 555);
	coin.setPosition(1290, 590);
	float xKey = 0, yKey = 0, delayKey = 0.075;
	float xCoin = 0, yCoin = 0, delayCoin = 0.065;


	Sprite button[3];
	for (int i = 0; i < 3; i++)
	{
		button[i].setTexture(tbutton);
		button[i].setScale(2, 2);
		button[i].setPosition(850, 400 + 200 * i);
	}

	Font font;
	font.loadFromFile("Nightmare_Before_Christmas.ttf");



	Text Menu[MENU_SIZE];
	
	for (int i = 0; i < MENU_SIZE; i++)
	{
		Menu[i].setFont(font);
		Menu[i].setCharacterSize(60);
		Menu[i].setString(options[i]);
		Menu[i].setPosition((i == 0 ? 910 : 900), 400 + 200 * i);
		Menu[i].setFillColor(Color::White);
	}

	Music music;
	music.openFromFile("Dame Tu Tormento.wav");

	int cnt = 0, select = 1;
	bool started = false, paused = false, options_status = 0;

	while (window.isOpen())
	{
		window.clear();
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}

		if (!started) 
		{
			if (options_status)
			{
				window.clear();
				window.draw(volume);
				if (Keyboard::isKeyPressed(Keyboard::Key::Escape))
					options_status = false;
			}

			else if (select == 1) 
			{
				Menu[START_BUTTON].setFillColor(Color::Red);
				Menu[OPTIONS_BUTTON].setFillColor(Color::White);
				Menu[EXIT_BUTTON].setFillColor(Color::White);

				if (Keyboard::isKeyPressed(Keyboard::Key::Enter))
				{
					started = 1;
					Menu[START_BUTTON].setString("CONTINUE");
					Menu[START_BUTTON].setPosition(890, 400);
				}
			}
			else if (select == 2) 
			{
				Menu[OPTIONS_BUTTON].setFillColor(Color::Red);
				Menu[START_BUTTON].setFillColor(Color::White);
				Menu[EXIT_BUTTON].setFillColor(Color::White);

				if (Keyboard::isKeyPressed(Keyboard::Key::Enter))
					options_status = true;

			}
			else if (select == 3) 
			{
				Menu[EXIT_BUTTON].setFillColor(Color::Red);
				Menu[START_BUTTON].setFillColor(Color::White);
				Menu[OPTIONS_BUTTON].setFillColor(Color::White);

				if (Keyboard::isKeyPressed(Keyboard::Key::Enter)) 
					window.close();

			}
			if (select > 3) select = 1;
			if (select < 1) select = 3;

			if (Keyboard::isKeyPressed(Keyboard::Key::Down)) 
			{
				if (cnt == 0)
					select++;
				cnt++;

			}
			else if (Keyboard::isKeyPressed(Keyboard::Key::Up)) 
			{
				if (cnt == 0)
					select--;
				cnt++;
			}
			else cnt = 0;
			if (!options_status)
			{
				for (int i = 0; i < 3; i++)
					window.draw(button[i]);
				for (int i = 0; i < 3; i++)
					window.draw(Menu[i]);
			}
		}



		else if (started && !paused)
		{
			if (Keyboard::isKeyPressed(Keyboard::Key::Escape))
				paused = 1;


			xKey += delayKey;
			key.setTextureRect(IntRect(short(xKey) * 39, short(yKey) * 39, 39, 39));
			if (xKey >= 2)
			{
				yKey++;
				xKey = 0;
			}


			if (yKey >= 1.9 && xKey >= 0.9)
				xKey = yKey = 0;

			coin.setTextureRect(IntRect(short(xCoin) * 26, 0, 26, 22));
			xCoin += delayCoin;
			if (xCoin >= 5)
				xCoin = 0;

			window.draw(background);
			window.draw(key);
			window.draw(coin);
		}
		
		else if (paused && started) 
		{
			
			if (options_status)
			{
				window.clear();
				window.draw(volume);
				if (Keyboard::isKeyPressed(Keyboard::Key::Escape))
					options_status = false;
			}
			if (select == 1) 
			{

				Menu[START_BUTTON].setFillColor(Color::Red);
				Menu[OPTIONS_BUTTON].setFillColor(Color::White);
				Menu[EXIT_BUTTON].setFillColor(Color::White);

				if (Keyboard::isKeyPressed(Keyboard::Key::Enter)) 
					paused = 0;
			}
			else if (select == 2) 
			{
				Menu[OPTIONS_BUTTON].setFillColor(Color::Red);
				Menu[START_BUTTON].setFillColor(Color::White);
				Menu[EXIT_BUTTON].setFillColor(Color::White);

				if (Keyboard::isKeyPressed(Keyboard::Key::Enter))
					options_status = true;
			}
			else if (select == 3) 
			{
				Menu[EXIT_BUTTON].setFillColor(Color::Red);
				Menu[START_BUTTON].setFillColor(Color::White);
				Menu[OPTIONS_BUTTON].setFillColor(Color::White);

				if (Keyboard::isKeyPressed(Keyboard::Key::Enter)) 
					window.close();
			}
			if (select > 3) select = 1;
			if (select < 1)select = 3;

			if (Keyboard::isKeyPressed(Keyboard::Key::Down)) {
				if (cnt == 0)
					select++;
				cnt++;

			}
			else if (Keyboard::isKeyPressed(Keyboard::Key::Up)) {
				if (cnt == 0)
					select--;
				cnt++;
			}
			else cnt = 0;

			if (!options_status)
			{
				window.draw(background);
				window.draw(key);
				window.draw(coin);

				for (int i = 0; i < 3; i++)
					window.draw(button[i]);
				for (int i = 0; i < 3; i++)
					window.draw(Menu[i]);
			}
		}
		window.display();
	}
}
