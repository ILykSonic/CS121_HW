#include <fstream>
#include <string>
#include <iostream>

using namespace std;

int main() {
    ifstream inFile(R"(C:\Users\ILykS\CLionProjects\zCS121 HW3\AL_Weather_Stations_Dec_23 (1).txt)");
    ofstream outFile("output.txt");
    string line;
    bool isHeader = true;

    if (inFile.is_open()) {
        while (getline(inFile, line)) {
            if (isHeader) {
                // Process the header line
                string header1 = line.substr(18, 23);
                // all of these skip create my header and skip the first header (Station) and starts with station_name
                string header2 = line.substr(65, 46);
                string header3 = line.substr(128, 6);
                string header4 = line.substr(164, 18);
                string newheader = header1 + header2 + header3 + header4;
                outFile << newheader << '\n';
                isHeader = false;
            } else {
                // Process the content lines
                string part1 = line.substr(18, 50);  //Station_Name
                part1.erase(0, part1.find_first_not_of(" "));  // Remove leading spaces
                string part2 = line.substr(70, 11); // Elevation
                string part3 = line.substr(82, 20); // Latitude and Longitude
                string part4 = line.substr(102, 9);  // Date
                string part5 = line.substr(128, 7);  // PRCP
                string part6 = line.substr(163, 16);  // TMAX/TMIN
                string newLine = part1 + part2 + part3 + part4 + part5 + part6;

                size_t pos;
                string token = "-9999";
                while ((pos = newLine.find(token)) != string::npos) {
                    newLine.erase(pos, token.length());
                }
                outFile << newLine << '\n';
            }
        }
        inFile.close();
        outFile.close();
    } else {
        cout << "Unable to open file";
    }

    return 0;
}
