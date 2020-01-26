#include "Menu.h"
#include "FAriasSimpleGraphics.h"
#include "Engine.h"
#include "Asteroid.h"
#include "Player.h"

Menu menu;

extern Game game;

char GetAnyKeyPressedInMenu();

void InputMenu();

void UpdateMenu();

void DrawMenu();


void InitMenu() {
	menu.sprite.LoadSprite("Menu.txt");
	menu.inMenu = true;
	menu.lastInputMenu = EInputMenu::NONE;

	//menu.sprite.Location.x = game.screenCenter.x;
	//menu.sprite.Location.y = game.screenCenter.y;
}

void ShowMenu() {
	if (menu.inMenu) {
		InitPlayer();
	}
	while (menu.inMenu) {
		menu.lastInputMenu = EInputMenu::NONE;
		InputMenu();
		UpdateMenu();
		DrawMenu();
		
	}

	
}

char GetAnyKeyPressedInMenu() { // Que devuelve seg�n la tecla presionada
	if (FASG::IsKeyPressed('Z')) {
		return 'Z';
	}
	if (FASG::IsKeyPressed('X')) {
		return 'X';
	}
	else {
		return '\0';
	}
}

void InputMenu() { // Que estado genera seg�n lo que recibe de la tecla presionada
	char key = GetAnyKeyPressedInMenu();

	switch (key)
	{
	case 'Z':
		menu.lastInputMenu = EInputMenu::PLAY;
		break;
	case 'X':
		menu.lastInputMenu = EInputMenu::EXIT;
		break;
	}
}

void UpdateMenu() { // Que hace cada estado 
	switch (menu.lastInputMenu)
	{
	case EInputMenu::PLAY:
		menu.inMenu = false;
		break;
	case EInputMenu::EXIT:
		game.gameOver = true;
		break;
	case EInputMenu::NONE:
		break;
	}
}

void DrawMenu() {
	menu.sprite.Location.x = game.screenCenter.x - (64/2);
	menu.sprite.Location.y = game.screenCenter.y - 17;
	
	FASG::WriteSpriteBuffer(menu.sprite.Location.x, menu.sprite.Location.y, menu.sprite);
	
	FASG::RenderFrame();
}