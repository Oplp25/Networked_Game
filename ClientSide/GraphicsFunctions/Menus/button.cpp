#include "button.h"

button::button(void (*func)(sf::RenderWindow&), sf::RectangleShape RectangleP) {
	Rectangle = RectangleP;
	hitbox = Rectangle.getGlobalBounds();
	fncPtr = func;
}
button::button(void (*func)(sf::RenderWindow&), sf::Sprite spriteP) {
	sprite = spriteP;
	hitbox = sprite.getGlobalBounds();
	fncPtr = func;
}
button::button(sf::RectangleShape RectangleP) {
	Rectangle = RectangleP;
	hitbox = Rectangle.getGlobalBounds();
}
button::button() {}