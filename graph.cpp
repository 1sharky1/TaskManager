#include "graph.hpp"




Graph::Graph(sf::RenderWindow *mainWindow, uint canvasWidth, uint canvasHeight, uint canvasPosX, uint canvasPosY, uint interval, sf::Color lineClr, std::string symbol)
{
    this->window = mainWindow;
    this->canvasWidth = canvasWidth;
    this->canvasHeight = canvasHeight;
    this->interval = interval;
    this->x0 = canvasPosX;
    this->y0 = canvasPosY + canvasHeight - 1;
    this->percentPx = float(canvasHeight) / 100.0;
    font.loadFromFile("Gilroylight.ttf");
    this->text.setFont(font);
    this->text.setCharacterSize(16);
    this->text.setFillColor(lineClr);
    this->symbol = symbol;

    uint linesCount = canvasWidth / interval;
    
    sf::ConvexShape tmpConvex;
    
    tmpConvex.setPointCount(4);
    tmpConvex.setFillColor(lineClr);
    for (int i = 0; i < linesCount; i++){
        this->graphic.push_back(tmpConvex);
    }
    
    for (int i = 0; i < linesCount + 1; i++){
        this->data.push_back(0);
    }
}


void Graph::UpdateData(float newData){
    for (int i = 0; i < this->data.size() - 1; i++){
        this->data[i] = this->data[i + 1];
    }
    this->data[this->data.size() - 1] = newData;
}


void Graph::SetGraph(){

    for (int i = 0; i < this->graphic.size(); i++){

        float valueInPx1 = data[i] * percentPx;
        float valueInPx2 = data[i + 1] * percentPx;
        graphic[i].setPoint(0, sf::Vector2f(x0 + interval * i, y0 - valueInPx1)); // x0 + interval * i, y0 - valueInPx1
        graphic[i].setPoint(1, sf::Vector2f(x0 + interval * (i + 1), y0 - valueInPx2)); // x0 + interval * i, y0 - valueInPx2

        graphic[i].setPoint(2, sf::Vector2f(x0 + interval * (i + 1), y0 - valueInPx2 + 1)); // x0 + interval * i, y0 - valueInPx2 + 3
        graphic[i].setPoint(3, sf::Vector2f(x0 + interval * i, y0 - valueInPx1 + 1)); // x0 + interval * i, y0 - valueInPx1 + 3
        
    }
    this->text.setPosition(x0 + this->canvasWidth + 5, this->graphic[this->graphic.size() - 1].getPoint(1).y - 8);

}


void Graph::Update(float newData){
    this->UpdateData(newData);
    this->text.setString( std::to_string( int(round(newData)) ) + this->symbol );
    this->SetGraph();
}


void Graph::Render(){
    //this->window->draw(text);
    for (int i = 0; i < graphic.size(); i++){
        this->window->draw(graphic[i]);
    }
    this->window->draw(this->text);
}












GraphCanvas::GraphCanvas(sf::RenderWindow *mainWindow, sf::Color backClr, sf::Color outClr, sf::Color linesClr, uint width, uint height, uint posX, uint posY, uint horizontalLinesInterval, uint verticalLinesInterval)
{
    this->window = mainWindow;

    this->canvas = new sf::RectangleShape();
    this->canvas->setSize(sf::Vector2f(width, height));
    this->canvas->setPosition(posX, posY);
    this->canvas->setFillColor(backClr);
    this->canvas->setOutlineColor(outClr);
    this->canvas->setOutlineThickness(2);


    int verticalLinesCount = width / verticalLinesInterval - 1;
    int horizontalLinesCount = height / horizontalLinesInterval - 1;

    sf::RectangleShape tmpLine;
    tmpLine.setFillColor(linesClr);

    tmpLine.setSize(sf::Vector2f(1, height));
    for (int i = 1; i <= verticalLinesCount; i++){
        tmpLine.setPosition(posX + verticalLinesInterval * i, posY);
        verticalLines.push_back(tmpLine);
    }

    tmpLine.setSize(sf::Vector2f(width, 1));
    for (int i = 1; i <= horizontalLinesCount; i++){
        tmpLine.setPosition(posX, posY + horizontalLinesInterval * i);
        horizontalLines.push_back(tmpLine);
    }
}



void GraphCanvas::Render(){
    this->window->draw(*this->canvas);
    for (int i = 0; i < verticalLines.size(); i++){
        this->window->draw(verticalLines[i]);
    }
    for (int i = 0; i < horizontalLines.size(); i++){
        this->window->draw(horizontalLines[i]);
    }
}



GraphCanvas::~GraphCanvas(){
    delete this->canvas;
}