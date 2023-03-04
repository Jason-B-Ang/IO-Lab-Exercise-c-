//
// Created by Admin on 2/25/2023.
//

#ifndef BINARY_FILE_IO_LAB_EXTRAFILE_H
#define BINARY_FILE_IO_LAB_EXTRAFILE_H
#include <iostream>
#include <vector>
using namespace std;
#include <fstream>
#include <string>

class StarShip{
public:
    struct{
        vector<string> weaponName;
        vector<int> weaponFirepower;
        vector<float> weaponFloat;
        vector<float > totalFirePower;
    };
    StarShip(string file);
    ~StarShip();
    int lenVessel;
    file.read((char*)(&lenVessel), 4);
    char* ptrVessel = new char [lenVessel];
    file.read(ptrVessel ,lenVessel);
    int lenClass;
    file.read((char*)(&lenClass), 4);
    char* ptrClass = new char [lenClass];
    file.read(ptrClass ,lenClass);
    short lengthShip;
    file.read((char*)(&lengthShip), sizeof(lengthShip)); // might have to hard code 2 bytes
    int shieldCapacity;
    file.read((char*)(&shieldCapacity), sizeof(shieldCapacity));  // 4 bytes
    float maxWarpSpeed;
    file.read((char*)(&maxWarpSpeed), sizeof(maxWarpSpeed)); // 4 bytes
//    delete[] ptrClass;
//    delete[] ptrVessel;
    string _file;

};

StarShip::StarShip(string file) {

    fstream openFile;
    openFile.open(file, ios_base::in | ios_base::binary);
}

StarShip::~StarShip() {
    delete[] ptrClass;
    delete[] ptrVessel;

}


#endif //BI;NARY_FILE_IO_LAB_EXTRAFILE_H
