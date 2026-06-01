#include <iostream>

using namespace std;



bool standardCompare(const char* str1, const char* str2) {
    int i = 0;
    while (str1[i] != '\0' && str2[i] != '\0') {
        if (str1[i] != str2[i]) return false;
        i++;
    }
    return (str1[i] == str2[i]);
}


void standardCopy(char* dest, const char* src) {
    int i = 0;
    while (src[i] != '\0' && i < 49) {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
}



class Vehicle {
private:
    char vehicleID[50];
    char manufacturer[50];
    char model[50];
    int year;

public:
    static int totalVehicles;

    Vehicle() {
        vehicleID[0] = '\0';
        manufacturer[0] = '\0';
        model[0] = '\0';
        year = 0;
        totalVehicles++;
    }

    Vehicle(const char* id, const char* mf, const char* md, int yr) {
        standardCopy(vehicleID, id);
        standardCopy(manufacturer, mf);
        standardCopy(model, md);
        year = yr;
        totalVehicles++;
    }

    const char* getVehicleID() const { return vehicleID; }
    const char* getManufacturer() const { return manufacturer; }
    const char* getModel() const { return model; }
    int getYear() const { return year; }

    virtual void displayInfo() const {
        cout << "ID: " << vehicleID << " | Maker: " << manufacturer << " | Model: " << model << " | Year: " << year;
    }

    virtual ~Vehicle() { 
        totalVehicles--; 
    }
};

int Vehicle::totalVehicles = 0;



class Car : virtual public Vehicle {
protected:
    char fuelType[50];

public:
    Car() : Vehicle() { 
        fuelType[0] = '\0'; 
    }

    Car(const char* id, const char* mf, const char* md, int yr, const char* fuel) 
        : Vehicle(id, mf, md, yr) {
        standardCopy(fuelType, fuel);
    }

    void displayInfo() const override {
        Vehicle::displayInfo();
        cout << " | Fuel: " << fuelType;
    }
};



class ElectricCar : public Car {
protected:
    int batteryCapacity;

public:
    ElectricCar() : Car(), batteryCapacity(0) {}

    ElectricCar(const char* id, const char* mf, const char* md, int yr, const char* fuel, int batteryCap)
        : Vehicle(id, mf, md, yr), Car(id, mf, md, yr, fuel), batteryCapacity(batteryCap) {}

    void displayInfo() const override {
        Car::displayInfo();
        cout << " | Battery: " << batteryCapacity << " kWh";
    }
};



class SportsCar : public ElectricCar {
private:
    int topSpeed;

public:
    SportsCar() : ElectricCar(), topSpeed(0) {}

    SportsCar(const char* id, const char* mf, const char* md, int yr, const char* fuel, int batteryCap, int speed)
        : Vehicle(id, mf, md, yr), ElectricCar(id, mf, md, yr, fuel, batteryCap), topSpeed(speed) {}

    void displayInfo() const override {
        ElectricCar::displayInfo();
        cout << " | Top Speed: " << topSpeed << " km/h [Sports Car]";
    }
};



class Sedan : public Car {
public:
    Sedan() : Car() {}

    Sedan(const char* id, const char* mf, const char* md, int yr, const char* fuel) 
        : Vehicle(id, mf, md, yr), Car(id, mf, md, yr, fuel) {}

    void displayInfo() const override {
        Car::displayInfo();
        cout << " [Type: Sedan]";
    }
};




class SUV : public Car {
public:
    SUV() : Car() {}

    SUV(const char* id, const char* mf, const char* md, int yr, const char* fuel) 
        : Vehicle(id, mf, md, yr), Car(id, mf, md, yr, fuel) {}

    void displayInfo() const override {
        Car::displayInfo();
        cout << " [Type: SUV]";
    }
};



class Aircraft : virtual public Vehicle {
protected:
    int flightRange;

public:
    Aircraft() : Vehicle(), flightRange(0) {}

    Aircraft(const char* id, const char* mf, const char* md, int yr, int range) 
        : Vehicle(id, mf, md, yr), flightRange(range) {}
};


class FlyingCar : public Car, public Aircraft {
public:
    FlyingCar() : Car(), Aircraft() {}

    FlyingCar(const char* id, const char* mf, const char* md, int yr, const char* fuel, int range)
        : Vehicle(id, mf, md, yr), Car(id, mf, md, yr, fuel), Aircraft(id, mf, md, yr, range) {}

    void displayInfo() const override {
        Vehicle::displayInfo();
        cout << " | Fuel: " << fuelType << " | Flight Range: " << flightRange << " km [Flying Car]";
    }
};


class VehicleRegistry {
private:
    Vehicle* registry[100]; 
    int currentSize;

public:
    VehicleRegistry() : currentSize(0) {}

    void addVehicle(Vehicle* v) {
        if (currentSize < 100) {
            registry[currentSize] = v;
            currentSize++;
            cout << "Vehicle Added Successfully!" << endl;
        } else {
            cout << "Registry is Full!" << endl;
        }
    }

    void displayAll() const {
        if (currentSize == 0) {
            cout << "No vehicles registered yet." << endl;
            return;
        }
        cout << "\n--- All Registered Vehicles ---" << endl;
        for (int i = 0; i < currentSize; i++) {
            cout << "[" << i + 1 << "] ";
            registry[i]->displayInfo();
            cout << endl;
        }
        cout << "Total Active Objects: " << Vehicle::totalVehicles << endl;
    }

    void searchByID(const char* id) const {
        bool found = false;
        for (int i = 0; i < currentSize; i++) {
            if (standardCompare(registry[i]->getVehicleID(), id)) {
                cout << "\nVehicle Found Details: " << endl;
                registry[i]->displayInfo();
                cout << endl;
                found = true;
                break;
            }
        }
        if (!found) {
            cout << "Vehicle with ID '" << id << "' Not Found!" << endl;
        }
    }

    ~VehicleRegistry() {
        for (int i = 0; i < currentSize; i++) {
            delete registry[i];
        }
    }
};



