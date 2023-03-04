#include <iostream>
#include <fstream>
using namespace std;
#include <vector>

struct Weapons {
    string weaponName = "";
    int weaponFirepower;
    float weaponFloat;
};

struct StarShip {
    string name = "";
    string shipClass = "";
    short lengthShip;
    int shieldCapacity;
    float maxWarpSpeed;
    vector<Weapons> weapons;
    //    vector<int> weaponFirepower;
    //    vector<float> weaponFloat;
    //    vector<float > totalFirePower;

};

void addStarShip(fstream& _file, vector<StarShip>& vecStarShips) {

    StarShip ship;

    //_file.open(file, ios_base::in | ios_base::binary);
    int lenVessel;
    _file.read((char*)(&lenVessel), sizeof(lenVessel));


    char* ptrVessel = new char[lenVessel];
    _file.read(ptrVessel, lenVessel);
    ship.name = ptrVessel;


    int lenClass;
    _file.read((char*)(&lenClass), sizeof(lenClass));

    char* ptrClass = new char[lenClass];
    _file.read(ptrClass, lenClass);
    ship.shipClass = ptrClass;
    delete[] ptrClass;

    short lengthShip;
    _file.read((char*)(&lengthShip), sizeof(lengthShip)); // might have to hard code 2 bytes
    ship.lengthShip = lengthShip;


    int shieldCapacity;
    _file.read((char*)(&shieldCapacity), sizeof(shieldCapacity));  // 4 bytes
    ship.shieldCapacity = shieldCapacity;


    float maxWarpSpeed;
    _file.read((char*)(&maxWarpSpeed), sizeof(maxWarpSpeed)); // 4 bytes
    ship.maxWarpSpeed = maxWarpSpeed;

    int numWeapons;
    _file.read((char*)(&numWeapons), sizeof(numWeapons));


    for (int i = 0; i < numWeapons; i++) {
        Weapons weapon;
        int lenweapName;
        _file.read((char*)(&lenweapName), 4);

        char* ptrweapName = new char[lenweapName];
        _file.read(ptrweapName, lenweapName);
        weapon.weaponName = ptrweapName;
        delete[] ptrweapName;

        int weapfirepower;
        _file.read((char*)(&weapfirepower), sizeof(weapfirepower));
        weapon.weaponFirepower = weapfirepower;

        float weapfloat;
        _file.read((char*)(&weapfloat), sizeof(weapfloat));
        weapon.weaponFloat = weapfloat;

        ship.weapons.push_back(weapon);

    }

    vecStarShips.push_back(ship);

}
int main()
{

    cout << "Which file(s) to open?\n";
    cout << "1. friendlyships.shp" << endl;
    cout << "2. enemyships.shp" << endl;
    cout << "3. Both files" << endl;
    int option;
    cin >> option;

    /* Load files here */
    vector<StarShip> VectorStarShip;
    if (option == 1) {

        fstream file("friendlyships.shp", ios_base::in | ios_base::binary);

        if (file.is_open()) {
            // string fileName = "friendlyships.shp";

            int numStarShips;
            file.read((char*)(&numStarShips), sizeof(numStarShips));
            for (int i = 0; i < numStarShips; i++) {
                addStarShip(file, VectorStarShip);
            }
        }
        else {
            cout << "file could not be opened" << endl;
        }

    }
    else if (option == 2) {
        fstream file("enemyships.shp", ios_base::in | ios_base::binary);
        if (file.is_open()) {

            int numStarShips;
            file.read((char*)(&numStarShips), sizeof(numStarShips));
            for (int i = 0; i < numStarShips; i++) {
                addStarShip(file, VectorStarShip);
            }
        }
        else {
            cout << "file could not be opened" << endl;
        }
    }
    else {
        fstream file("friendlyships.shp", ios_base::in | ios_base::binary);
        if (file.is_open()) {
            // string fileName = "friendlyships.shp";
            int numStarShips;
            file.read((char*)(&numStarShips), sizeof(numStarShips));
            for (int i = 0; i < numStarShips; i++) {
                addStarShip(file, VectorStarShip);
            }
        }
        else {
            cout << "file could not be opened" << endl;
        }
        fstream files("enemyships.shp", ios_base::in | ios_base::binary);
        if (files.is_open()) {

            int numStarShips;
            files.read((char*)(&numStarShips), sizeof(numStarShips));
            for (int i = 0; i < numStarShips; i++) {
                addStarShip(files, VectorStarShip);
            }
        }
        else {
            cout << "file could not be opened" << endl;
        }

    }

    cout << "1. Print all ships" << endl;
    cout << "2. Starship with the strongest weapon" << endl;
    cout << "3. Strongest starship overall" << endl;
    cout << "4. Weakest ship (ignoring unarmed)" << endl;
    cout << "5. Unarmed ships" << endl;

    cin >> option;


    /* Work your magic here */
    if (option == 1) {
        for (StarShip& ship : VectorStarShip) {
            cout << "Name: " << ship.name << endl;
            cout << "Class: " << ship.shipClass << endl;
            cout << "Length: " << ship.lengthShip << endl;
            cout << "Shield capacity: " << ship.shieldCapacity << endl;
            cout << "Maximum Warp: " << ship.maxWarpSpeed << endl;
            cout << "Armaments: " << endl;
            int sumFirePower = 0;
            if (ship.weapons.size() == 0) { cout << "Unarmed"; }
            else {
                for (Weapons& weapon : ship.weapons) {
                    cout << weapon.weaponName;
                    cout << ", " << weapon.weaponFirepower;
                    cout << ", " << weapon.weaponFloat << endl;
                    sumFirePower += weapon.weaponFirepower;
                }

                cout << "Total firepower: " << sumFirePower << endl;
            }
            cout << endl;
        }

    }
    else if (option == 2) {
        int index;
        int largestfirepower = -1;
        for (unsigned int i = 0; i < VectorStarShip.size(); i++) {
            int highFirePower = 0;
            if (VectorStarShip.at(i).weapons.size() != 0) {
                for (unsigned int x = 0; x < VectorStarShip.at(i).weapons.size(); x++) {
                    int temp = VectorStarShip.at(i).weapons.at(x).weaponFirepower;
                    if (temp > highFirePower) {
                        highFirePower = temp;
                    }
                }
            }
            if (largestfirepower == -1) {
                largestfirepower = highFirePower;
                index = i;
            }
            if (highFirePower > largestfirepower) {
                index = i;
                largestfirepower = highFirePower;
            }

        }
        cout << "Name: " << VectorStarShip.at(index).name << endl;
        cout << "Class: " << VectorStarShip.at(index).shipClass << endl;
        cout << "Length: " << VectorStarShip.at(index).lengthShip << endl;
        cout << "Shield capacity: " << VectorStarShip.at(index).shieldCapacity << endl;
        cout << "Maximum Warp: " << VectorStarShip.at(index).maxWarpSpeed << endl;
        cout << "Armaments: " << endl;
        int sumFirePower = 0;
        if (VectorStarShip.at(index).weapons.size() != 0) {
            for (unsigned int x = 0; x < VectorStarShip.at(index).weapons.size(); x++) {
                cout << VectorStarShip.at(index).weapons.at(x).weaponName;
                cout << ", " << VectorStarShip.at(index).weapons.at(x).weaponFirepower;
                cout << ", " << VectorStarShip.at(index).weapons.at(x).weaponFloat << endl;
                sumFirePower += VectorStarShip.at(index).weapons.at(x).weaponFirepower;
            }

            cout << "Total firepower: " << sumFirePower << endl;
        }

    }
    else if (option == 3) {
        int index;
        int largestfirepower = -1;
        for (unsigned int i = 0; i < VectorStarShip.size(); i++) {
            int sumFirePower = 0;
            if (VectorStarShip.at(i).weapons.size() != 0) {
                for (unsigned int x = 0; x < VectorStarShip.at(i).weapons.size(); x++) {

                    sumFirePower += VectorStarShip.at(i).weapons.at(x).weaponFirepower;
                }
                if (largestfirepower == -1) {
                    largestfirepower = sumFirePower;
                    index = i;
                }
                if (sumFirePower > largestfirepower) {
                    index = i;
                    largestfirepower = sumFirePower;
                }
            }


        }
        cout << "Name: " << VectorStarShip.at(index).name << endl;
        cout << "Class: " << VectorStarShip.at(index).shipClass << endl;
        cout << "Length: " << VectorStarShip.at(index).lengthShip << endl;
        cout << "Shield capacity: " << VectorStarShip.at(index).shieldCapacity << endl;
        cout << "Maximum Warp: " << VectorStarShip.at(index).maxWarpSpeed << endl;
        cout << "Armaments: " << endl;
        int sumFirePower = 0;

        if (VectorStarShip.at(index).weapons.size() != 0) {
            for (unsigned int x = 0; x < VectorStarShip.at(index).weapons.size(); x++) {
                cout << VectorStarShip.at(index).weapons.at(x).weaponName;
                cout << ", " << VectorStarShip.at(index).weapons.at(x).weaponFirepower;
                cout << ", " << VectorStarShip.at(index).weapons.at(x).weaponFloat << endl;
                sumFirePower += VectorStarShip.at(index).weapons.at(x).weaponFirepower;
            }

            cout << "Total firepower: " << sumFirePower << endl;
        }


    }
    else if (option == 4) {
        int index;
        int smallestfirepower = -1;
        for (unsigned int i = 0; i < VectorStarShip.size(); i++) {
            int sumFirePower = 0;
            if (VectorStarShip.at(i).weapons.size() != 0) {
                for (unsigned int x = 0; x < VectorStarShip.at(i).weapons.size(); x++) {

                    sumFirePower += VectorStarShip.at(i).weapons.at(x).weaponFirepower;
                }
                if (smallestfirepower == -1) {
                    smallestfirepower = sumFirePower;
                    index = i;
                }
                if (sumFirePower < smallestfirepower) {
                    index = i;
                    smallestfirepower = sumFirePower;
                }
            }


        }
        cout << "Name: " << VectorStarShip.at(index).name << endl;
        cout << "Class: " << VectorStarShip.at(index).shipClass << endl;
        cout << "Length: " << VectorStarShip.at(index).lengthShip << endl;
        cout << "Shield capacity: " << VectorStarShip.at(index).shieldCapacity << endl;
        cout << "Maximum Warp: " << VectorStarShip.at(index).maxWarpSpeed << endl;
        cout << "Armaments: " << endl;
        int sumFirePower = 0;
        if (VectorStarShip.at(index).weapons.size() == 0) { cout << "Unarmed"; }
        else {
            for (unsigned int x = 0; x < VectorStarShip.at(index).weapons.size(); x++) {
                cout << VectorStarShip.at(index).weapons.at(x).weaponName;
                cout << ", " << VectorStarShip.at(index).weapons.at(x).weaponFirepower;
                cout << ", " << VectorStarShip.at(index).weapons.at(x).weaponFloat << endl;
                sumFirePower += VectorStarShip.at(index).weapons.at(x).weaponFirepower;
            }

            cout << "Total firepower: " << sumFirePower << endl;
        }
    }
    else {
        for (unsigned int i = 0; i < VectorStarShip.size(); i++) {
            if (VectorStarShip.at(i).weapons.size() == 0) {

                cout << "Name: " << VectorStarShip.at(i).name << endl;
                cout << "Class: " << VectorStarShip.at(i).shipClass << endl;
                cout << "Length: " << VectorStarShip.at(i).lengthShip << endl;
                cout << "Shield capacity: " << VectorStarShip.at(i).shieldCapacity << endl;
                cout << "Maximum Warp: " << VectorStarShip.at(i).maxWarpSpeed << endl;
                cout << "Armaments: " << endl;
                cout << "Unarmed";
            }
        }
    }
    return 0;
}