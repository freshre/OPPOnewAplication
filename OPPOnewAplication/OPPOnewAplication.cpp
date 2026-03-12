#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <regex>
#include <vector>
#include <algorithm>

using namespace std;

class Planet {
    string name;
    string date;
    double value_R = 0.0;
public:


    void print(ostream& ost) {
        ost << "Planet" << " " << "\"" << name << "\"" << " " << date << " " << value_R << " " << endl;

    }


    bool parseInput(const string& inputLine) {

        if (inputLine.find("Planet") == string::npos) {
            cout << "Invalid entry: Not a Planet data\n";
            return false;
        }

        smatch match;
        regex nameRegex(R"(\"([^\"]+)\")");          // Имя планеты в кавычках
        regex dateRegex(R"(\d{4}\.\d{2}\.\d{2})");   // Дата в формате ГГГГ.MM.ДД
        regex radiusRegex(R"(\d+(?:\.\d+)?)");       // Просто число (целое или с плавающей точкой)

        string tempLine = inputLine;


        if (regex_search(tempLine, match, nameRegex)) {
            name = match[1];
        }


        if (regex_search(tempLine, match, dateRegex)) {
            date = match[0];
            tempLine = regex_replace(tempLine, dateRegex, "", regex_constants::format_first_only);
        }


        if (regex_search(tempLine, match, radiusRegex)) {
            value_R = stod(match[0]);
        }


        if (date.empty()) {
            cout << "Date not found or incorrect input. Please use format: YYYY.MM.DD\n";
            return false;
        }

        return true;
    }

    double getRadius() {
        return value_R;
    }


};

bool compareByRadius(Planet& a, Planet& b) {
    return a.getRadius() < b.getRadius();
}

void sortirovkaPlanet(vector<Planet>& planets) {
    if (planets.empty()) {
        cout << "Net planet for sort.\n";
        return;
    }

    sort(planets.begin(), planets.end(), compareByRadius);

    for (size_t i = 0; i < planets.size(); i++) {
        planets[i].print(cout);
    }
}

void displayAllPlanets(vector<Planet>& planets, string& outputFileName) {
    if (planets.empty()) {
        cout << "Pusto.\n";
        return;
    }

    if (!outputFileName.empty()) {
        ofstream outputFile(outputFileName);
        if (!outputFile.is_open()) {
            cout << "Could not open output file for writing.\n";
            return;
        }

        for (size_t i = 0; i < planets.size(); i++) {
            planets[i].print(outputFile);
        }
    }



    for (size_t i = 0; i < planets.size(); i++) {
        planets[i].print(cout);
    }
}

void addNewPlanet(vector<Planet>& planets, string& filename) {
    Planet new_Planet;
    string line;
    cout << "Enter planet data (example: Planet \"Earth\" 2026.03.11 6371.0): ";
    getline(cin, line);

    if (new_Planet.parseInput(line)) {
        new_Planet.print(cout);
        ofstream outputFile(filename, ios::app); // Append mode
        if (!outputFile.is_open()) {
            cout << "Failed open faile.\n";
            return;
        }
        new_Planet.print(outputFile);
        planets.push_back(new_Planet);
    }
}

int main() {
    string filename, filename2;
    vector<Planet> planets;

    cout<<"Enter filename for reading: ";
    getline(cin, filename);
    cout << "Enter filename2 for waiting: ";
    getline(cin, filename2);

    ifstream file(filename);
    if (!file.is_open()) {
        cout << "File is not open: " << filename << endl;
        return 1;
    }

    

    string line;
    bool Type_Planet = false;
    while (getline(file, line)) {
        Planet new_Planet;
        if (new_Planet.parseInput(line)) {
            new_Planet.print(cout);
            planets.push_back(new_Planet);
            Type_Planet = true;
        }
    }

   

    if (!Type_Planet) {
        cout << "No valid planets found in the file.\n";
    }

    int choice;
    do {
        cout << "\nMenu:\n";
        cout << "1. Creation new planet and add to file\n";
        cout << "2. Print all planets\n";
        cout << "3. Sort and display planets by radius\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore(); // Ignore the newline after the number input

        if (choice == 1) {
            addNewPlanet(planets, filename2);
        }
        else if (choice == 2) {
            string outputFileName;
            cout << "Enter filename: ";
            getline(cin, outputFileName);
            displayAllPlanets(planets, outputFileName);
        }
        else if (choice == 3) {
            sortirovkaPlanet(planets);
        }
        else if (choice == 4) {
            cout << "Exiting program.\n";
        }
        else {
            cout << "Invalid choice. Please try again.\n";
        }

    } while (choice != 4);

    return 0;


    return 0;
}

