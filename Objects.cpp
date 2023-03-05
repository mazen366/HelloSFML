#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include<iostream>
#define MENU_SIZE 3
#define START_BUTTON 0
#define OPTIONS_BUTTON 1
#define EXIT_BUTTON 2
 

using namespace std;
using namespace sf;

int main()
{
	string options[MENU_SIZE] = { "START", "OPTIONS", "EXIT" };



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



	Texture Tbackground, Tkey, Tcoin, tbutton, opendoor, tslider, tskeleton[6], Ebutton;
	Tbackground.loadFromFile("SFMLProject2.png");
	Tkey.loadFromFile("key2.png");
	Tcoin.loadFromFile("spinning coin2.png");
	tbutton.loadFromFile("button_ui.png");
	opendoor.loadFromFile("opened_door.png");
	tslider.loadFromFile("slider.png");
	tskeleton[0].loadFromFile("SkeletonIdle.png");
	tskeleton[1].loadFromFile("SkeletonWalk.png");
	tskeleton[2].loadFromFile("SkeletonAttack.png");
	Ebutton.loadFromFile("E.png");



	Sprite skeleton, slider(tslider), background(Tbackground), key(Tkey, IntRect(0, 0, 39, 39)), coin(Tcoin, IntRect(0, 0, 26, 22)), door(opendoor), E(Ebutton);
	background.setPosition(Vector2f(0, 250));
	key.setPosition(790, 555);
	coin.setPosition(1290, 590);
	door.setPosition(1224.2, 530.4);
	door.scale(2.14, 2.14);
	slider.setPosition(850, 540);
	skeleton.setTexture(tskeleton[0]);
	skeleton.setTextureRect(IntRect(0, 0, 150, 150));
	skeleton.setScale(-1.5, 1.5);
	skeleton.setPosition(1320, 550);
	E.setPosition(1290, 500);
	E.scale(1.6, 1.6);

	float xKey = 0, yKey = 0, delayKey = 0.075;
	float xCoin = 0, yCoin = 0, delayCoin = 0.065;
	float f = 0, delay = 0.09f, g = 9.9, v = 7.9, jumpv = 0;
	bool isground = 0;

	Clock time;
	Texture texture;
	Sprite player(texture, IntRect(0, 0, 1200 / 10, 80));
	player.setPosition(Vector2f(0, 500));
	player.scale(2, 2);
	player.setOrigin(Vector2f(player.getTextureRect().width / 2, player.getTextureRect().height / 2));
	Sprite button[4];
	for (int i = 0; i < 3; i++)
	{
		button[i].setTexture(tbutton);
		button[i].setScale(2, 2);
		button[i].setPosition(850, 400 + 200 * i);
	}

	button[3].setTexture(tbutton);
	button[3].setScale(2, 2);
	button[3].setPosition(400, 520);

	Font font;
	font.loadFromFile("Nightmare_Before_Christmas.ttf");



	Text Menu[MENU_SIZE], win;

	for (int i = 0; i < MENU_SIZE; i++)
	{
		Menu[i].setFont(font);
		Menu[i].setCharacterSize(60);
		Menu[i].setString(options[i]);
		Menu[i].setPosition((i == 0 ? 910 : 900), 400 + 200 * i);
		Menu[i].setFillColor(Color::White);
	}
	win.setFont(font);
	win.setCharacterSize(100);
	win.setString("Level One Complete");
	win.setPosition(560, 500);
	win.setFillColor(Color::Red);

	Text volumeb;
	volumeb.setFont(font);
	volumeb.setCharacterSize(60);
	volumeb.setString("VOLUME");
	volumeb.setPosition(435, 520);
	volumeb.setFillColor(Color::Green);

	Music music;
	music.openFromFile("Dame Tu Tormento.wav");
	music.play();
	music.setLoop(true);

	int cnt = 0, select = 1;
	float skeleton_attack_x = 0, skeleton_attack_y = 0, skeleton_attack_delay = 0.06;
	bool started = false, paused = false, options_status = 0, level_one_complete = 0;
	bool keycollect = 0;
	bool ok = false;
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
				window.draw(slider);
				window.draw(volume);
				window.draw(button[3]);
				window.draw(volumeb);
				if (Keyboard::isKeyPressed(Keyboard::Key::Escape))
					options_status = false;

				if (Mouse::isButtonPressed(Mouse::Left))
				{

					Vector2i mousePos = Mouse::getPosition(window);
					if (mousePos.x >= 850 && mousePos.x <= 1050 && mousePos.y >= 540 && mousePos.y <= 550)
					{
						volume.setSize(Vector2f(200 - (1050 - mousePos.x), 20));
						music.setVolume(0.5 * volume.getSize().x);
					}
				}
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



		else if (started && !paused && !level_one_complete)
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

			cout << skeleton.getPosition().x - player.getPosition().x << endl;
			if (skeleton.getPosition().x - player.getPosition().x <= 330 && skeleton.getPosition().x - player.getPosition().x >= 0)
				cout << '.';

			if (skeleton.getGlobalBounds().intersects(player.getGlobalBounds()))
			{
				skeleton.setTexture(tskeleton[2]);
				skeleton.setTextureRect(IntRect(short(skeleton_attack_x) * 150, 0, 150, 150));
				skeleton_attack_x += skeleton_attack_delay;
				if (skeleton_attack_x >= 7.9)
					skeleton_attack_x = 0;
			}
			
			if (Keyboard::isKeyPressed(Keyboard::Key::D) && !(Keyboard::isKeyPressed(Keyboard::Key::C)) && !(Keyboard::isKeyPressed(Keyboard::Key::K))) {
				if (Keyboard::isKeyPressed(Keyboard::Key::Space) && isground == 1) {
					jumpv = 8;
					player.move(3.0f, 0);
					isground = 0;
				}
				else {
					player.setTextureRect(IntRect((short int)f * 120, 0, 1200 / 10, 80));
					f += delay;
					texture.loadFromFile("_Run.png");
					player.move(2.0f, 0);
					player.setScale(2, 2);
				}
			}
			else if (Keyboard::isKeyPressed(Keyboard::Key::A) && !(Keyboard::isKeyPressed(Keyboard::Key::C) && !(Keyboard::isKeyPressed(Keyboard::Key::K)))) {
				if (Keyboard::isKeyPressed(Keyboard::Key::Space) && isground == 1) {
					jumpv = 8;
					player.move(-3.0f, 0);
					isground = 0;
				}
				else {
					f += delay;
					texture.loadFromFile("_Run.png");
					player.setScale(-2, 2);
					player.move(-2.0f, 0);
					player.setTextureRect(IntRect((short int)f * 120, 0, 1200 / 10, 80));

				}
			}
			else if (Keyboard::isKeyPressed(Keyboard::Key::C) && Keyboard::isKeyPressed(Keyboard::Key::D)) {
				player.setTextureRect(IntRect((short int)f * 120, 0, 1200 / 10, 80));
				f += delay;
				texture.loadFromFile("_CrouchWalk.png");
				player.move(0.5f, 0);
				player.setScale(2, 2);
				if (f > 7.9) {
					f = 0;
				}
			}
			else if (Keyboard::isKeyPressed(Keyboard::Key::C) && Keyboard::isKeyPressed(Keyboard::Key::A)) {
				player.setTextureRect(IntRect((short int)f * 120, 0, 1200 / 10, 80));

				f += delay;
				texture.loadFromFile("_CrouchWalk.png");
				player.move(-0.5f, 0);
				player.setScale(-2, 2);
				if (f > 7.9) {
					f = 0;
				}
			}
			else if (Keyboard::isKeyPressed(Keyboard::Key::C)) {
				texture.loadFromFile("Crouch.png");
				player.setTextureRect(IntRect((short int)0, 0, 1200 / 10, 80));
			}
			else if (Keyboard::isKeyPressed(Keyboard::Key::Space) && isground == 1) {
				jumpv = 8;
				isground = 0;
			}
			else if (Keyboard::isKeyPressed(Keyboard::Key::D) && Keyboard::isKeyPressed(Keyboard::Key::K)) {
				texture.loadFromFile("_AttackNoMovement.png");
				player.setTextureRect(IntRect((short int)f * (480 / 4), 0, 480 / 4, 80));
				player.move(2.0f, 0);
				player.setScale(2, 2);
				if(player.getGlobalBounds().intersects(skeleton.getGlobalBounds()))
					skeleton.setScale(0, 0);
				f += 0.06;
				if (f > 3.9) {
					f = 0;
				}
			}
			else if (Keyboard::isKeyPressed(Keyboard::Key::A) && Keyboard::isKeyPressed(Keyboard::Key::K)) {
				texture.loadFromFile("_AttackNoMovement.png");
				player.setTextureRect(IntRect((short int)f * (480 / 4), 0, 480 / 4, 80));
				player.move(-2.0f, 0);
				player.setScale(-2, 2);
				f += 0.06;
				if (f > 3.9) {
					f = 0;
				}
			}
			else if (Keyboard::isKeyPressed(Keyboard::Key::K) && !(Keyboard::isKeyPressed(Keyboard::Key::D))) {
				texture.loadFromFile("_AttackNoMovement.png");
				player.setTextureRect(IntRect((short int)f * (480 / 4), 0, 480 / 4, 80));
				f += 0.06;
				if (f > 3.9) {
					f = 0;
				}
			}
			else {
				texture.loadFromFile("_Idle.png");
				player.setTextureRect(IntRect((short int)f * 120, 0, 1200 / 10, 80));
				f += delay;
			}
			if (player.getGlobalBounds().intersects(coin.getGlobalBounds())) {
				coin.setPosition(Vector2f(10000, 10000));
			}

			if (player.getGlobalBounds().intersects(key.getGlobalBounds())) {
				keycollect = 1;
				key.setPosition(Vector2f(10000, 10000));
			}


			if (jumpv > 0) {
				player.setPosition(player.getPosition().x, player.getPosition().y - 10.2f);
				jumpv -= 4.8 * time.getElapsedTime().asSeconds();
				texture.loadFromFile("Jump.png");
				player.setTextureRect(IntRect((short int)f * 120, 0, 360 / 3, 80));
				f += delay;
				if (f > 2.9)
					f = 0;
			}
			else {
				jumpv = 0;
				time.restart();
			}
			if (player.getGlobalBounds().intersects(ground1.getGlobalBounds()) ||
				player.getGlobalBounds().intersects(ground2.getGlobalBounds()) ||
				player.getGlobalBounds().intersects(ground3.getGlobalBounds()) ||
				player.getGlobalBounds().intersects(ground4.getGlobalBounds())) {
				player.setPosition(player.getPosition().x, player.getPosition().y - 0.001);
				isground = 1;
			}

			else if (jumpv <= 0) {
				isground = 0;
				player.setPosition(player.getPosition().x, player.getPosition().y + 4.8);
				if (Keyboard::isKeyPressed(Keyboard::Key::D)) {
					texture.loadFromFile("_Fall.png");
					player.setTextureRect(IntRect((short int)f * 120, 0, 360 / 3, 80));
					f += delay;
					player.setScale(2, 2);
					if (f > 2.9)
						f = 0;
				}
				else if (Keyboard::isKeyPressed(Keyboard::Key::A)) {
					texture.loadFromFile("_Fall.png");
					player.setTextureRect(IntRect((short int)f * 120, 0, 360 / 3, 80));
					f += delay;
					player.setScale(-2, 2);
					if (f > 2.9)
						f = 0;
				}
				else {
					texture.loadFromFile("_Fall.png");
					player.setTextureRect(IntRect((short int)f * 120, 0, 360 / 3, 80));
					f += delay;
					if (f > 2.9)
						f = 0;
				}

			}
			if (f > 9.9) {
				f = 0;
			}

			window.draw(background);
			window.draw(key);
			window.draw(coin);
			window.draw(skeleton);

			if (player.getGlobalBounds().intersects(door.getGlobalBounds()) && keycollect == 1) {
				window.draw(door);
				window.draw(E);
				if (Keyboard::isKeyPressed(Keyboard::Key::E)) {
					level_one_complete = 1;

				}
			}

			window.draw(player);
		}

		else if (paused && started && !level_one_complete)
		{

			if (options_status)
			{
				window.clear();
				window.draw(slider);
				window.draw(volume);
				window.draw(button[3]);
				window.draw(volumeb);
				if (Keyboard::isKeyPressed(Keyboard::Key::Escape))
					options_status = false;

				if (Mouse::isButtonPressed(Mouse::Left))
				{

					Vector2i mousePos = Mouse::getPosition(window);
					if (mousePos.x >= 850 && mousePos.x <= 1050 && mousePos.y >= 540 && mousePos.y <= 550)
					{
						volume.setSize(Vector2f(200 - (1050 - mousePos.x), 20));
						music.setVolume(0.5 * volume.getSize().x);
					}
				}
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
				window.draw(player);


				for (int i = 0; i < 3; i++)
					window.draw(button[i]);
				for (int i = 0; i < 3; i++)
					window.draw(Menu[i]);
			}
		}
		else if (level_one_complete) {
			window.draw(win);
		}
		window.display();
	}
}