
#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>

class Label
{

private:
    
    sf::RenderWindow *window;
    
    sf::RectangleShape *rect;

    sf::Text *text;
    sf::Font font;

public:

    Label(sf::RenderWindow *mainWindow, uint width, uint height, uint posX, uint posY, sf::Color fillColor, sf::Color OutColor, sf::Color textColor);

    ~Label();

    void Render();

    void setText(std::string string, bool wrap);

};
