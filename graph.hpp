#include <SFML/Graphics.hpp>
#include <vector>
#include <math.h>
#include <iostream>




class Graph
{

private:

    sf::RenderWindow *window;

    std::vector <float> data;

    std::vector <sf::ConvexShape> graphic;

    sf::Font font;
    sf::Text text;
    std::string symbol;

    float percentPx;
    float x0;
    float y0;
    uint canvasWidth;
    uint canvasHeight;
    uint interval;

    void UpdateData(float newData);
    void SetGraph();

public:

    Graph(sf::RenderWindow *mainWindow, uint canvasWidth, uint canvasHeight, uint canvasPosX, uint canvasPosY, uint interval, sf::Color lineClr, std::string symbol);

    void Update(float newData);

    void Render();

};









class GraphCanvas
{

private:

    sf::RenderWindow *window;

    sf::RectangleShape *canvas;

    std::vector <sf::RectangleShape> horizontalLines;
    std::vector <sf::RectangleShape> verticalLines;

public:

    GraphCanvas(sf::RenderWindow *mainWindow, sf::Color backClr, sf::Color outClr, sf::Color linesClr, uint width, uint height, uint posX, uint posY, uint horizontalLinesInterval, uint verticalLinesInterval);

    ~GraphCanvas();
    
    void Render();

};