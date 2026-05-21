#include <SFML/Graphics.hpp>
#include "Personagens.h"

class Ninja : public Personagens {
    private:
    // embelezar depois
    //sf::Sprite sprite;
    //sf::Texture texture;
    sf::RectangleShape corpo;
public:
    Ninja(float x, float y);
    void update();
    void render(sf::RenderWindow& window);

};