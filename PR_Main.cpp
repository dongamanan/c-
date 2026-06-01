#include "PR.cpp"
#include <iostream>
using namespace std;

int main()
{
    VehicleRegistry myRegistry;
    int choice;

    do
    {
        cout << "\n===== Vehicle Registry Menu =====" << endl;
        cout << "1. Add a Vehicle" << endl;
        cout << "2. View All Vehicles" << endl;
        cout << "3. Search by ID" << endl;
        cout << "4. Exit" << endl;
        cout << "Enter your choice (1-4): ";
        cin >> choice;

        if (choice == 1)
        {
            int type;
            char id[50], mf[50], md[50], fuel[50];
            int yr, optAttr;

            cout << "\nSelect Vehicle Type:\n1. Car\n2. Electric Car\n3. Sports Car\n4. Sedan\n5. SUV\n6. Flying Car\nChoice: ";
            cin >> type;

            cout << "Enter Vehicle ID: ";
            cin >> id;
            cout << "Enter Manufacturer: ";
            cin >> mf;
            cout << "Enter Model: ";
            cin >> md;
            cout << "Enter Year: ";
            cin >> yr;

            if (type == 1)
            {
                cout << "Enter Fuel Type: ";
                cin >> fuel;
                myRegistry.addVehicle(new Car(id, mf, md, yr, fuel));
            }
            else if (type == 2)
            {
                cout << "Enter Fuel Type: ";
                cin >> fuel;
                cout << "Enter Battery Capacity (kWh): ";
                cin >> optAttr;
                myRegistry.addVehicle(new ElectricCar(id, mf, md, yr, fuel, optAttr));
            }
            else if (type == 3)
            {
                cout << "Enter Fuel Type: ";
                cin >> fuel;
                cout << "Enter Battery Capacity (kWh): ";
                cin >> optAttr;
                int speed;
                cout << "Enter Top Speed (km/h): ";
                cin >> speed;
                myRegistry.addVehicle(new SportsCar(id, mf, md, yr, fuel, optAttr, speed));
            }
            else if (type == 4)
            {
                cout << "Enter Fuel Type: ";
                cin >> fuel;
                myRegistry.addVehicle(new Sedan(id, mf, md, yr, fuel));
            }
            else if (type == 5)
            {
                cout << "Enter Fuel Type: ";
                cin >> fuel;
                myRegistry.addVehicle(new SUV(id, mf, md, yr, fuel));
            }
            else if (type == 6)
            {
                cout << "Enter Fuel Type: ";
                cin >> fuel;
                cout << "Enter Flight Range (km): ";
                cin >> optAttr;
                myRegistry.addVehicle(new FlyingCar(id, mf, md, yr, fuel, optAttr));
            }
        }
        else if (choice == 2)
        {
            myRegistry.displayAll();
        }
        else if (choice == 3)
        {
            char searchID[50];
            cout << "Enter Vehicle ID to Search: ";
            cin >> searchID;
            myRegistry.searchByID(searchID);
        }

    } while (choice != 4);

    cout << "\nRegistry Cleaned. Exiting System Application..." << endl;
    return 0;
}
