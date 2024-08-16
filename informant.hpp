#include <iostream>
#include <fstream>
#include <sys/sysinfo.h>
#include <vector>
#include <sstream>

class Informant
{

private:

    std::ifstream CPUModelFile;
    std::ifstream CPUTemperatureFile;
    std::ifstream CPULoadFile;

    std::string CPUModel;
    float CPUTemperature;
    float CPULoad;

    double firstActive;
    double firstIdle;


    uint totalRAM;
    uint freeRAM;
    uint usedRAM;

    float usedRAMpersents;
    
    void UpdateCpuTemperature();
    void UpdateCpuLoad();
    void UpdateRAMValues();

public:

    
    Informant();

    ~Informant();

    void Update();

    std::string getCpuModel();
    float getCpuTemperature();
    float getCpuLoad();


    uint getTotalRAM();
    /* uint getFreeRAM();
    uint getUsedRAM(); */
    float getUsedRAMpersents();

};
