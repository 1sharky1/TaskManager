
#include "manager.hpp"



Manager::Manager(){
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    this->window = new sf::RenderWindow(sf::VideoMode(this->WindowWidth, this->WindowHeight), "Task Manager", sf::Style::Close /* , settings */ );
    this->window->setFramerateLimit(30);
    this->window->setPosition(sf::Vector2i(20, 20));

    this->backClr = new sf::Color(30, 30, 30);
    this->outClr = new sf::Color(80, 80, 80);
    this->textClr = new sf::Color(240, 240, 240);

    this->cpuTemperatureClr = new sf::Color(250, 10, 50);
    this->cpuLoadClr = new sf::Color(228, 7, 232);
    this->ramLoadClr = new sf::Color(10, 198, 245);

    this->cpuLabel = new Label(this->window, LabelWidth, LabelHeight, cpuLabelPosX, cpuLabelPosY, *this->backClr, *this->outClr, *this->textClr);
    this->ramLabel = new Label(this->window, LabelWidth, LabelHeight, ramLabelPosX, ramLabelPosY, *this->backClr, *this->outClr, *this->textClr);

    this->cpuGraphCanvas = new GraphCanvas(this->window, *this->backClr, *this->outClr, sf::Color(45, 45, 45), this->GraphCanvasWidth, this->LabelHeight, this->GraphCanvasPosX, this->cpuLabelPosY, 40, 48);
    this->ramGraphCanvas = new GraphCanvas(this->window, *this->backClr, *this->outClr, sf::Color(45, 45, 45), this->GraphCanvasWidth, this->LabelHeight, this->GraphCanvasPosX, this->ramLabelPosY, 40, 48);

    this->info = new Informant();

    this->cpuTemperatureGraph = new Graph(this->window, this->GraphCanvasWidth, this->LabelHeight, this->GraphCanvasPosX, this->cpuLabelPosY, 32, *this->cpuTemperatureClr, "C");
    this->cpuLoadGraph = new Graph(this->window, this->GraphCanvasWidth, this->LabelHeight, this->GraphCanvasPosX, this->cpuLabelPosY, 32, *this->cpuLoadClr, "%");
    this->ramLoadGraph = new Graph(this->window, this->GraphCanvasWidth, this->LabelHeight, this->GraphCanvasPosX, this->ramLabelPosY, 32, *this->ramLoadClr, "%");

}



Manager::~Manager(){
    delete this->cpuTemperatureClr;
    delete this->cpuLoadClr;
    delete this->ramLoadClr;
    delete this->cpuTemperatureGraph;
    delete this->cpuLoadGraph;
    delete this->ramLoadGraph;
    delete this->cpuLabel;
    delete this->ramLabel;
    delete this->backClr;
    delete this->outClr;
    delete this->textClr;
    delete this->cpuGraphCanvas;
    delete this->ramGraphCanvas;
    delete this->window;
    delete this->info;
}




void Manager::START(){

    sf::Time time;
    sf::Clock clock;

    Init();
    clock.restart();
    while(this->window->isOpen())
    {
        sf::Event ev;
        while(this->window->pollEvent(ev)){
            if (ev.type == sf::Event::Closed){
                this->window->close();
            }
        }

        time = clock.getElapsedTime();
        if (time.asMilliseconds() > 1250){
            this->UpdateData();
            clock.restart();
        }
        Render();

    }
    
}


void Manager::Init(){

    std::string scpu = "CPU:\n\n";
    std::string sram = "RAM:\n\n    ";

    this->info->Update();

    this->cpuLabel->setText(scpu + this->info->getCpuModel(), true);
    this->ramLabel->setText(sram + std::to_string(this->info->getTotalRAM()) + " MB", false);

}


void Manager::Render(){
    this->window->clear(*this->backClr);
    this->cpuLabel->Render();
    this->ramLabel->Render();
    this->cpuGraphCanvas->Render();
    this->ramGraphCanvas->Render();
    this->cpuTemperatureGraph->Render();
    this->cpuLoadGraph->Render();
    this->ramLoadGraph->Render();
    this->window->display();
}



void Manager::UpdateData(){
    this->info->Update();
    this->cpuTemperatureGraph->Update( this->info->getCpuTemperature() );
    this->cpuLoadGraph->Update( this->info->getCpuLoad() );
    this->ramLoadGraph->Update( this->info->getUsedRAMpersents() );
}