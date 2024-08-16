

#include <SFML/Graphics.hpp>
#include "informant.hpp"
#include "label.hpp"
#include "graph.hpp"


class Manager
{

private:

    Informant *info;

    const uint WindowWidth = 815;
    const uint WindowHeight = 445;

    const uint LabelWidth = 265; // 270
    const uint LabelHeight = 200; // 190

    const uint cpuLabelPosX = 5;
    const uint cpuLabelPosY = 10;

    const uint ramLabelPosX = 5;
    const uint ramLabelPosY = 230;

    const uint GraphCanvasPosX = 295;
    //const uint GraphPosY = ;
    const uint GraphCanvasWidth = 480;

    sf::RenderWindow* window;
    Label *cpuLabel;
    Label *ramLabel;

    sf::Color *backClr;
    sf::Color *outClr;
    sf::Color *textClr;

    sf::Color *cpuTemperatureClr;
    sf::Color *cpuLoadClr;
    sf::Color *ramLoadClr;


    GraphCanvas *cpuGraphCanvas;
    GraphCanvas *ramGraphCanvas;

    void Render();

    void Init(); // ?????

    void UpdateData();

    Graph *cpuTemperatureGraph;
    Graph *cpuLoadGraph;
    Graph *ramLoadGraph;

public:

    Manager();
    
    ~Manager();

    void START();

};