
#include "label.hpp"

Label::Label(sf::RenderWindow *mainWindow, uint width, uint height, uint posX, uint posY, sf::Color fillColor, sf::Color OutColor, sf::Color textColor){

    this->window = mainWindow;

    this->rect = new sf::RectangleShape(sf::Vector2f(width, height));

    this->rect->setPosition(posX, posY);
    this->rect->setFillColor(fillColor);
    this->rect->setOutlineColor(OutColor);
    this->rect->setOutlineThickness(2);
    
    this->text = new sf::Text();
    this->text->setFillColor(textColor);
    this->text->setCharacterSize(20);
    this->text->setPosition(posX + 10, height * 0.2 + posY);
    font.loadFromFile("Gilroylight.ttf");
    this->text->setFont(font);
}


Label::~Label(){
    delete this->text;
    delete this->rect;
}


void Label::setText(std::string string, bool wrap){

    int I = floor(string.length() / 2); // string's center

    // Text wrap
    if (wrap){
        for (int i = 0; /* I - i > 0 && */ I + i < string.length(); i++){
            if (string[I + i] == ' '){
                string[I + i] = '\n';
                break;
            }
            /* else if (string[I - i] == ' '){
                string[I - i] = '\n';
                break;
            } */
        }
    }

    this->text->setString(string);

}



void Label::Render(){
    this->window->draw(*this->rect);
    this->window->draw(*this->text);
    
}
