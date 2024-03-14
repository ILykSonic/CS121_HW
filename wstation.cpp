#include <fstream>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <string>

using namespace std;

bool isFloat(string s) {
    if (s == "-9999") {
        return false;
    }
    try {
        stof(s);
        return true;
    } catch (const std::exception& e) {
        return false;
    }
}

int main() {
    ifstream infile(R"(C:\Users\nilan\CLionProjects\untitled\cmake-build-debug\AL_Weather_Stations_Dec_23.txt)");
    ofstream outfile("output.txt");

    if (!infile || !outfile) {
        cerr << "Error opening files!" << endl;
        return 1;
    }

    string line;
    while (getline(infile, line)) {
        istringstream iss(line);
        string station, elevation, latitude, longitude, date, prcp, tmax, tmin;

        iss >> ws;
        getline(iss, station, ',');
        iss >> ws;
        getline(iss, elevation, ',');
        iss >> ws;
        getline(iss, latitude, ',');
        iss >> ws;
        getline(iss, longitude, ',');
        iss >> ws;
        getline(iss, date, ',');
        iss >> ws;
        getline(iss, prcp, ',');
        iss >> ws;
        getline(iss, tmax, ',');
        iss >> ws;
        getline(iss, tmin, ',');

        // Reformatting data
        if (date.length() >= 8) {
            date = date.substr(4, 2) + " " + date.substr(6, 2) + " " + date.substr(0, 4);
        }

        station.erase(0, station.find_first_not_of(' ')); // Remove leading spaces

        // Convert strings to floating-point numbers
        float elevation_f, latitude_f, longitude_f, prcp_f, tmax_f, tmin_f;
        if (isFloat(elevation) && isFloat(latitude) && isFloat(longitude) &&
            isFloat(prcp) && isFloat(tmax) && isFloat(tmin)) {
            elevation_f = stof(elevation);
            latitude_f = stof(latitude);
            longitude_f = stof(longitude);
            prcp_f = stof(prcp);
            tmax_f = stof(tmax);
            tmin_f = stof(tmin);

            // Write to the new file with formatted data
            outfile << line << endl;  // Move this line here
            outfile << left << setw(25) << station << fixed << setprecision(2) << setw(10) << elevation_f
                    << setprecision(4) << setw(10) << latitude_f << setw(10) << longitude_f << " " << date << " "
                    << prcp_f << " " << tmax_f << " " << tmin_f << endl;
        } else {
            // Skip the current line if any conversion fails
            continue;
        }
    }
    infile.close();
    outfile.close();
    return 0;
}


    return 0;
}
