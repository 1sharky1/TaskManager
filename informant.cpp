
#include "informant.hpp"



Informant::Informant(){

    std::string line;
    this->CPUModel = "Unknown";
    this->CPUModelFile.open("/proc/cpuinfo");
    if (this->CPUModelFile.is_open()){
        while(std::getline(this->CPUModelFile, line)){
            if(line.find("model name") != std::string::npos){

                this->CPUModel = line;
                break;
            }
        }
        this->CPUModelFile.close();
        this->CPUModel.erase(0, 13);
    }
    else{
        std::cerr<<"Error getting CPU Model"<<std::endl;
    }

    this->firstActive = 0;
    this->firstIdle = 0;

}

Informant::~Informant(){

    if (this->CPUTemperatureFile.is_open())
        this->CPUTemperatureFile.close();

    if (this->CPULoadFile.is_open())
        this->CPULoadFile.close();

}



void Informant::Update(){
    this->UpdateCpuTemperature();
    this->UpdateCpuLoad();
    this->UpdateRAMValues();
}



std::string Informant::getCpuModel(){
    return this->CPUModel;
}


void Informant::UpdateCpuTemperature(){

    this->CPUTemperatureFile.open("/sys/class/thermal/thermal_zone0/temp");
    if (!this->CPUTemperatureFile.is_open()){
        std::cerr<<"Error getting CPU Temperature"<<std::endl;
        return;
    }


    std::string temp;
    std::getline(this->CPUTemperatureFile, temp);
    this->CPULoadFile.close();
    this->CPUTemperature = std::stod(temp) / 1000.0;
    this->CPUTemperatureFile.close();
    std::cout<<CPUTemperature<<" | ";
}


void Informant::UpdateCpuLoad(){

    this->CPULoadFile.open("/proc/stat");
    if (!this->CPULoadFile.is_open()){
        std::cerr<<"Error getting CPU Load"<<std::endl;
        return;
    }


    std::string line;

    std::getline(CPULoadFile, line);
    line.erase(0, 5);
    //std::cout << line << std::endl;
    std::istringstream iss(line);
    std::vector<double> nums; // Вектор для хранения чисел
    double number;
    while (iss >> number) {
        nums.push_back(number);
    }
    /* for (int i = 0; i < nums.size(); i++){
        std::cout<<"|"<<nums[i]<<"|"<<std::endl;
    } */


    double secondActive = nums[0] + nums[1] + nums[2] + nums[5] + nums[6] + nums[7] + nums[8] + nums[9];
    double active = secondActive - this->firstActive;

    double secondIdle = nums[3] + nums[4];
    double idle = secondIdle - firstIdle;

    double general = active + idle;
    this->CPULoad = active / general * 100;

    this->firstActive = secondActive;
    this->firstIdle = secondIdle;
    
    this->CPULoadFile.close();
    std::cout<<CPULoad<<" | ";
}




void Informant::UpdateRAMValues(){
    struct sysinfo sInfo;
    if (sysinfo(&sInfo) != 0){
        std::cerr << "Error getting RAM info" << std::endl;
        this->totalRAM = 0;
        this->freeRAM = 0;
        this->usedRAM = 0;
        this->usedRAMpersents = 0;
        return;
    }

    this->totalRAM = sInfo.totalram / (1024 * 1024);
    this->freeRAM = sInfo.freeram / (1024 * 1024);
    this->usedRAM = (sInfo.totalram - sInfo.freeram) / (1024 * 1024);
    this->usedRAMpersents = double(this->usedRAM) / double(this->totalRAM) * 100;
    std::cout<<usedRAMpersents<<"\n";
}

uint Informant::getTotalRAM(){
    return this->totalRAM;
}

/* uint Informant::getFreeRAM(){
    return this->freeRAM;
}

uint Informant::getUsedRAM(){
    return this->usedRAM;
} */

float Informant::getUsedRAMpersents(){
    return this->usedRAMpersents;
}

float Informant::getCpuLoad(){
    return this->CPULoad;
}

float Informant::getCpuTemperature(){
    return this->CPUTemperature;
}
