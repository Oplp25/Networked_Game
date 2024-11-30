#include "button.h"

//constructor with a rectangle object
button::button(void (*func)(sf::RenderWindow&), sf::RectangleShape RectangleP) {
	Rectangle = RectangleP;
	hitbox = Rectangle.getGlobalBounds();
	fncPtr = func;
}
//constructor with a sprite object
button::button(void (*func)(sf::RenderWindow&), sf::Sprite spriteP) {
	sprite = spriteP;
	hitbox = sprite.getGlobalBounds();
	fncPtr = func;
}
//constructor without a function pointer object
button::button(sf::RectangleShape RectangleP) {
	Rectangle = RectangleP;
	hitbox = Rectangle.getGlobalBounds();
}
//empty constructor
button::button() {}