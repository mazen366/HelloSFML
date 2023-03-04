#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
using namespace std;
using namespace sf;

int main()
{

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
	//ground4.setFillColor(Color::Green);


	Texture Tbackground, Tkey, Tcoin, button;
	Tbackground.loadFromFile("D:\SFMLProject2.png");
	Tkey.loadFromFile("D:\key2.png");
	Tcoin.loadFromFile("D:\spinning coin2.png");
	button.loadFromFile("button_ui.png");

	Sprite background(Tbackground), key(Tkey, IntRect(0, 0, 39, 39)), coin(Tcoin, IntRect(0, 0, 26, 22));
	background.setPosition(Vector2f(0, 250));
	key.setPosition(790, 555);
	coin.setPosition(1290, 590);
	float xKey = 0, yKey = 0, delayKey = 0.075;
	float xCoin = 0, yCoin = 0, delayCoin = 0.065;


	Sprite sbutton1(button), sbutton2(button), sbutton3(button);
	sbutton1.scale(2, 2);
	sbutton1.setPosition(850, 400);
	sbutton2.scale(2, 2);
	sbutton2.setPosition(850, 600);
	sbutton3.scale(2, 2);
	sbutton3.setPosition(850, 800);

	Font font;
	font.loadFromFile("Nightmare_Before_Christmas.ttf");



	Text start;
	start.setFont(font);
	start.setCharacterSize(60);
	start.setString("START");
	start.setPosition(860 + 50, 400);
	start.setFillColor(Color::White);



	Text options;
	options.setFont(font);
	options.setCharacterSize(60);
	options.setString("OPTIONS");
	options.setPosition(850 + 50, 600);
	options.setFillColor(Color::White);


	Text exit;
	exit.setFont(font);
	exit.setCharacterSize(60);
	exit.setString("EXIT");
	exit.setPosition(870 + 50, 800);
	exit.setFillColor(Color::White);

	int cnt = 0, select = 1;
	bool started = false, paused = false;

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
			if (select == 1) 
			{
				start.setFillColor(Color::Red);

				options.setFillColor(Color::White);

				exit.setFillColor(Color::White);

				if (Keyboard::isKeyPressed(Keyboard::Key::Enter))
				{
					started = 1;
					start.setString("CONTINUE");
					start.setPosition(890, 400);
				}
			}
			else if (select == 2) 
			{
				options.setFillColor(Color::Red);

				start.setFillColor(Color::White);

				exit.setFillColor(Color::White);
			}
			else if (select == 3) {
				exit.setFillColor(Color::Red);

				start.setFillColor(Color::White);

				options.setFillColor(Color::White);
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

			window.draw(sbutton1);
			window.draw(sbutton2);
			window.draw(sbutton3);
			window.draw(start);
			window.draw(options);
			window.draw(exit);
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
			if (select == 1) 
			{

				start.setFillColor(Color::Red);
				options.setFillColor(Color::White);
				exit.setFillColor(Color::White);

				if (Keyboard::isKeyPressed(Keyboard::Key::Enter)) 
					paused = 0;
			}
			else if (select == 2) 
			{
				options.setFillColor(Color::Red);
				start.setFillColor(Color::White);
				exit.setFillColor(Color::White);
			}
			else if (select == 3) 
			{
				exit.setFillColor(Color::Red);
				start.setFillColor(Color::White);
				options.setFillColor(Color::White);

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
			window.draw(background);
			window.draw(key);
			window.draw(coin);
			window.draw(sbutton1);
			window.draw(sbutton2);
			window.draw(sbutton3);
			window.draw(start);
			window.draw(options);
			window.draw(exit);
		}
		window.display();
	}
}
