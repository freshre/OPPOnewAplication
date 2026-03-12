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


int main() {
    Planet new_Planet;
    vector<Planet> planets;

    string filename;
    string filename2;
    cout << "Enter filename: ";
    getline(cin, filename);
    cout << endl;
    cout << "Enter filename2: ";
    getline(cin, filename2);
    cout << endl;

    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Faile is not open: " << filename << endl;
        return 1;
    }


    string line;
    bool Type_Planet = false;

    ofstream outputFile(filename2);
    if (!outputFile.is_open()) {
        cout << "Could not open output file for writing.\n";
        return 1;
    }

    while (getline(file, line)) {

        if (new_Planet.parseInput(line)) {
            new_Planet.print(cout);
            new_Planet.print(outputFile);
            planets.push_back(new_Planet);
            Type_Planet = true;
        }
    }

    if (!Type_Planet) {
        cout << "No valid planets found in the file.\n";
    }

    cout << endl;

    sort(planets.begin(), planets.end(), compareByRadius);

    for (size_t i = 0; i < planets.size(); i++) {
        planets[i].print(cout);
        planets[i].print(outputFile);
    }


    return 0;
}

