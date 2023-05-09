#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include<iostream>
#define MENU_SIZE 3
#define START_BUTTON 0
#define OPTIONS_BUTTON 1
#define EXIT_BUTTON 2
using namespace std;
using namespace sf;

Sprite animation[30];

Music music;

string options[MENU_SIZE] = { "START", "OPTIONS", "EXIT" };

Texture Tbackground, Tkey, Tcoin, tbutton, opendoor, tslider, tskeleton[6], Ebutton, Tplayer, texture, player_run_tex, player_fall_tex, player_crouch_tex, player_attck_tex,
player_jump_tex, player_crouch_walk_tex, player_idle_tex, player_attack_tex;
Sprite slider, background, key, coin, door, E,button[4];

Font font;
Text Menu[MENU_SIZE], win, volumeb;

RectangleShape ground1, ground2, ground3, ground4, volume;

RenderWindow window(VideoMode(1920, 1080), "SFML");

float xKey = 0, yKey = 0, delayKey = 0.075, xCoin = 0, yCoin = 0, delayCoin = 0.065, f = 0, delay = 0.09f, g = 9.9, v = 7.9, jumpv = 0, 
skeleton_attack_x = 0, skeleton_attack_y = 0, skeleton_attack_delay = 0.06;
bool isground = 0, started = false, paused = false, options_status = 0, level_one_complete = 0, keycollect = 0, ok = false;
int cnt = 0, select = 1;  
struct player
{
	int health = 100;
	Sprite player_sprite;
	Clock player_clock;
	RectangleShape rec;
	void player_movement() 
	{
		player_sprite.setOrigin(Vector2f(player_sprite.getTextureRect().width / 2, player_sprite.getTextureRect().height / 2));
		rec.setPosition(player_sprite.getPosition().x-40,player_sprite.getPosition().y);
		if (Keyboard::isKeyPressed(Keyboard::Key::D) && !(Keyboard::isKeyPressed(Keyboard::Key::C)) && !(Keyboard::isKeyPressed(Keyboard::Key::K))) {
			if (Keyboard::isKeyPressed(Keyboard::Key::Space) && isground == 1) {
				jumpv = 8;
				player_sprite.move(3.0f, 0);
				isground = 0;
			}
			else {
				player_sprite.setTexture(player_run_tex);
				player_sprite.setTextureRect(IntRect((short int)f * 120, 0, 1200 / 10, 80));
				f += delay;
				player_sprite.move(2.0f, 0);
				player_sprite.setScale(2, 2);
			}
		}
		else if (Keyboard::isKeyPressed(Keyboard::Key::A) && !(Keyboard::isKeyPressed(Keyboard::Key::C) && !(Keyboard::isKeyPressed(Keyboard::Key::K)))) {
			if (Keyboard::isKeyPressed(Keyboard::Key::Space) && isground == 1) {
				jumpv = 8;
				player_sprite.move(-3.0f, 0);
				isground = 0;
			}
			else {
				f += delay;
				player_sprite.setTexture(player_run_tex);
				player_sprite.setScale(-2, 2);
				player_sprite.move(-2.0f, 0);
				player_sprite.setTextureRect(IntRect((short int)f * 120, 0, 1200 / 10, 80));

			}
		}
		else if (Keyboard::isKeyPressed(Keyboard::Key::C) && Keyboard::isKeyPressed(Keyboard::Key::D)) {
			player_sprite.setTextureRect(IntRect((short int)f * 120, 0, 1200 / 10, 80));
			f += delay;
			player_sprite.setTexture(player_crouch_walk_tex);
			player_sprite.move(0.5f, 0);
			player_sprite.setScale(2, 2);
			if (f > 7.9) {
				f = 0;
			}
		}
		else if (Keyboard::isKeyPressed(Keyboard::Key::C) && Keyboard::isKeyPressed(Keyboard::Key::A)) {
			player_sprite.setTextureRect(IntRect((short int)f * 120, 0, 1200 / 10, 80));

			f += delay;
			player_sprite.setTexture(player_crouch_walk_tex);
			player_sprite.move(-0.5f, 0);
			player_sprite.setScale(-2, 2);
			if (f > 7.9) {
				f = 0;
			}
		}
		else if (Keyboard::isKeyPressed(Keyboard::Key::C)) {
			player_sprite.setTexture(player_crouch_tex);
			player_sprite.setTextureRect(IntRect((short int)0, 0, 1200 / 10, 80));
		}
		else if (Keyboard::isKeyPressed(Keyboard::Key::Space) && isground == 1) {
			jumpv = 8;
			isground = 0;
		}
		else if (Keyboard::isKeyPressed(Keyboard::Key::D) && Keyboard::isKeyPressed(Keyboard::Key::K)) {
						player_sprite.setTexture(player_attack_tex);
			player_sprite.setTextureRect(IntRect((short int)f * (480 / 4), 0, 480 / 4, 80));
			player_sprite.move(2.0f, 0);
			player_sprite.setScale(2, 2);
			//if (player_sprite.getGlobalBounds().intersects(skeleton.getGlobalBounds()))
			//	skeleton.setScale(0, 0);
			f += 0.06;
			if (f > 3.9) {
				f = 0;
			}
		}
		else if (Keyboard::isKeyPressed(Keyboard::Key::A) && Keyboard::isKeyPressed(Keyboard::Key::K)) {
			player_sprite.setTexture(player_attack_tex);
			player_sprite.setTextureRect(IntRect((short int)f * (480 / 4), 0, 480 / 4, 80));
			player_sprite.move(-2.0f, 0);
			player_sprite.setScale(-2, 2);
			f += 0.06;
			if (f > 3.9) {
				f = 0;
			}
		}
		else if (Keyboard::isKeyPressed(Keyboard::Key::K) && !(Keyboard::isKeyPressed(Keyboard::Key::D))) {
			player_sprite.setTexture(player_attack_tex);
			player_sprite.setTextureRect(IntRect((short int)f * (480 / 4), 0, 480 / 4, 80));
			f += 0.06;
			if (f > 3.9) {
				f = 0;
			}
		}
		else {
			player_sprite.setTexture(player_idle_tex);
			player_sprite.setTextureRect(IntRect((short int)f * 120, 0, 1200 / 10, 80));
			f += delay;
		}
		if (jumpv > 0) {
			player_sprite.setPosition(player_sprite.getPosition().x, player_sprite.getPosition().y - 10.2f);
			jumpv -= 4.8 * player_clock.getElapsedTime().asSeconds();
			player_sprite.setTexture(player_jump_tex);
			player_sprite.setTextureRect(IntRect((short int)f * 120, 0, 360 / 3, 80));
			f += delay;
			if (f > 2.9)
				f = 0;
		}
		else {
			jumpv = 0;
			player_clock.restart();
		}
		if (player_sprite.getGlobalBounds().intersects(ground1.getGlobalBounds()) ||
			player_sprite.getGlobalBounds().intersects(ground2.getGlobalBounds()) ||
			player_sprite.getGlobalBounds().intersects(ground3.getGlobalBounds()) ||
			player_sprite.getGlobalBounds().intersects(ground4.getGlobalBounds())) {
			player_sprite.setPosition(player_sprite.getPosition().x, player_sprite.getPosition().y - 0.001);
			isground = 1;
		}

		else if (jumpv <= 0) {
			isground = 0;
			player_sprite.setPosition(player_sprite.getPosition().x, player_sprite.getPosition().y + 4.8);
			if (Keyboard::isKeyPressed(Keyboard::Key::D)) {
				player_sprite.setTexture(player_fall_tex);
				player_sprite.setTextureRect(IntRect((short int)f * 120, 0, 360 / 3, 80));
				f += delay;
				player_sprite.setScale(2, 2);
				if (f > 2.9)
					f = 0;
			}
			else if (Keyboard::isKeyPressed(Keyboard::Key::A)) {
				player_sprite.setTexture(player_fall_tex);
				player_sprite.setTextureRect(IntRect((short int)f * 120, 0, 360 / 3, 80));
				f += delay;
				player_sprite.setScale(-2, 2);
				if (f > 2.9)
					f = 0;
			}
			else {
				player_sprite.setTexture(player_fall_tex);
				player_sprite.setTextureRect(IntRect((short int)f * 120, 0, 360 / 3, 80));
				f += delay;
				if (f > 2.9)
					f = 0;
			}

		}
		if (f > 9.9) {
			f = 0;
		}
	}
}player;


struct Skeleton
{
	int health = 100;
	int last_key_pressed = 1;//1 --> Right || 0 --> left
	Texture skeletonT;
	Sprite skeletonS;
	void setup_enemy(Skeleton skeleton[])
	{
		skeletonT.loadFromFile("SkeletonIdle.png");
		for (int i = 0;i<10;i++)
		{
			skeleton[i].skeletonS.setTexture(skeletonT);
		}
	}
	void Enemy_movment()
	{
		//if (player.player_sprite.getPosition().x < skeleton.getPosition().x)
		//{

		//}
	}
}skeleton[10];
void objects_position()
{
	ground1.setSize(Vector2f(450, 150));
	ground1.setPosition(0, 696);

	ground2.setSize(Vector2f(205, 100));
	ground2.setPosition(653, 593);

	ground3.setSize(Vector2f(955, 100));
	ground3.setPosition(960, 710);

	ground4.setSize(Vector2f(35, 70));
	ground4.setPosition(617, 635);

	volume.setSize(Vector2f(200, 20));
	volume.setPosition(850, 540);
}

//void animation(int index ,int frame,int leftrect,int rightrect,float delay)
//{
//
//}

void set_texture()
{
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

	player_idle_tex.loadFromFile("_Idle.png");
	player_fall_tex.loadFromFile("_Fall.png");
	player_jump_tex.loadFromFile("Jump.png");
	player_attack_tex.loadFromFile("_AttackNoMovement.png");
	player_crouch_tex.loadFromFile("Crouch.png");
	player_crouch_walk_tex.loadFromFile("_CrouchWalk.png");
	player_run_tex.loadFromFile("_Run.png");
}

void set_sprite()
{
	background.setTexture(Tbackground);
	background.setPosition(Vector2f(0, 250));

	key.setTexture(Tkey);
	key.setTextureRect(IntRect(0, 0, 39, 39));
	key.setPosition(790, 555);

	coin.setTexture(Tcoin);
	coin.setPosition(1290, 590);
	coin.setTextureRect(IntRect(0, 0, 26, 22));

	door.setTexture(opendoor);
	door.setPosition(1224.2, 530.4);
	door.scale(2.14, 2.14);

	slider.setTexture(tslider);
	slider.setPosition(850, 540);

	//skeleton.setTexture(tskeleton[0]);
	//skeleton.setTextureRect(IntRect(0, 0, 150, 150));
	//skeleton.setScale(-1.5, 1.5);
	//skeleton.setPosition(1320, 550);

	E.setTexture(Ebutton);
	E.setPosition(1290, 500);
	E.scale(1.6, 1.6);

	player.player_sprite.setPosition(Vector2f(0, 500));
	player.player_sprite.scale(2, 2);
	player.player_sprite.setOrigin(Vector2f(player.player_sprite.getTextureRect().width / 2, player.player_sprite.getTextureRect().height / 2));
	player.rec.setSize(Vector2f(60, 80));
	for (int i = 0; i < 3; i++)
	{
		button[i].setTexture(tbutton);
		button[i].setScale(2, 2);
		button[i].setPosition(850, 400 + 200 * i);
	}

	button[3].setTexture(tbutton);
	button[3].setScale(2, 2);
	button[3].setPosition(400, 520);
}

void set_font()
{
	font.loadFromFile("Nightmare_Before_Christmas.ttf");
}

void set_text()
{
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

	volumeb.setFont(font);
	volumeb.setCharacterSize(60);
	volumeb.setString("VOLUME");
	volumeb.setPosition(435, 520);
	volumeb.setFillColor(Color::Green);

}

void set_music()
{
	music.openFromFile("Dame Tu Tormento.wav");
	music.play();
	music.setLoop(true);
}

void set_window()
{
	window.setFramerateLimit(120);
}

void set_movement()
{

}

void collision()
{

}

void gravity()
{

}
void player_animation()
{

}

int main()
{
	set_window();
	objects_position();
	set_texture();
	set_sprite();
	set_font();
	set_text();
	set_music();

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
			player.player_movement();
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

			/*if (skeleton.getGlobalBounds().intersects(player.player_sprite.getGlobalBounds()))
			{
				skeleton.setTexture(tskeleton[2]);
				skeleton.setTextureRect(IntRect(short(skeleton_attack_x) * 150, 0, 150, 150));
				skeleton_attack_x += skeleton_attack_delay;
				if (skeleton_attack_x >= 7.9)
					skeleton_attack_x = 0;
			}*/
			
			
			if (player.player_sprite.getGlobalBounds().intersects(coin.getGlobalBounds())) {
				coin.setPosition(Vector2f(10000, 10000));
			}

			if (player.player_sprite.getGlobalBounds().intersects(key.getGlobalBounds())) {
				keycollect = 1;
				key.setPosition(Vector2f(10000, 10000));
			}




			window.draw(background);
			window.draw(key);
			window.draw(coin);
			//window.draw(skeleton);

			if (player.player_sprite.getGlobalBounds().intersects(door.getGlobalBounds()) && keycollect == 1) {
				window.draw(door);
				window.draw(E);
				if (Keyboard::isKeyPressed(Keyboard::Key::E)) {
					level_one_complete = 1;

				}
			}
			window.draw(player.rec);
			window.draw(player.player_sprite);
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
				window.draw(player.player_sprite);


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