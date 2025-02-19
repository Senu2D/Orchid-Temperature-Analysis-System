#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>

using namespace std;

//Functions call
//menue func
void displayMenu();
//input temp
void inputTemperatureData(vector<float>& dayTemps, vector<float>& nightTemps, int days);
//display temp
void displayTemperatures(const vector<float>& dayTemps, const vector<float>& nightTemps);
//cal fluctuation
void calculateFluctuations(const vector<float>& dayTemps, const vector<float>& nightTemps);
//analyze suitability
void analyzeSuitability(const vector<float>& dayTemps, const vector<float>& nightTemps);
//C to F
float convertToFahrenheit(float celsius);
//F to C
float convertToCelsius(float fahrenheit);
//save data
void saveData(const vector<float>& dayTemps, const vector<float>& nightTemps);
//load data
void loadData(vector<float>& dayTemps, vector<float>& nightTemps);


//main func
int main() {
	//for 30days
	int days = 30;
    vector<float> dayTemps(days), nightTemps(days);
    int choice;

    do {
    	//call to menue func
        displayMenu();
        //display enter the choice 
        cout << "Enter your choice: ";
        cin >> choice;
		//func list
        switch (choice) {
            case 1:
                inputTemperatureData(dayTemps, nightTemps, days);
                break;
            case 2:
                displayTemperatures(dayTemps, nightTemps);
                break;
            case 3:
                calculateFluctuations(dayTemps, nightTemps);
                break;
            case 4:
                analyzeSuitability(dayTemps, nightTemps);
                break;
            case 5: {
                float temp;
                cout << "Enter temperature to convert: ";
                cin >> temp;
                cout << "1. Celsius to Fahrenheit\n2. Fahrenheit to Celsius\nEnter conversion choice: ";
                int convertChoice;
                cin >> convertChoice;
                if (convertChoice == 1) {
                    cout << temp << " Celsius = " << convertToFahrenheit(temp) << " Fahrenheit\n";
                } else {
                    cout << temp << " Fahrenheit = " << convertToCelsius(temp) << " Celsius\n";
                }
                break;
            }
            case 6:
                saveData(dayTemps, nightTemps);
                break;
            case 7:
                loadData(dayTemps, nightTemps);
                break;
            case 8:
                cout << "Exiting program...\n";
                break;
            default:
                cout << "Invalid choice! Please try again.\n";
        }
    } while (choice != 8);

    return 0;
}

// Function Definitions
//main menue
void displayMenu() {
    cout << "\n--- Orchi-Flora Temperature Analysis System ---\n";
    cout << "1. Input Temperature Data\n";
    cout << "2. Display Temperatures\n";
    cout << "3. Calculate Fluctuations\n";
    cout << "4. Analyze Suitability\n";
    cout << "5. Convert Temperature\n";
    cout << "6. Save Data\n";
    cout << "7. Load Data\n";
    cout << "8. Exit\n";
}
//input temp func
void inputTemperatureData(vector<float>& dayTemps, vector<float>& nightTemps, int days) {
    for (int i = 0; i < days; ++i) {
    	//when its equals to days count "i" will add 1
        cout << "Day " << i + 1 << " - Enter Daytime Temperature: ";
        cin >> dayTemps[i];
        cout << "Day " << i + 1 << " - Enter Nighttime Temperature: ";
        cin >> nightTemps[i];
    }
}
//display temp func
void displayTemperatures(const vector<float>& dayTemps, const vector<float>& nightTemps) {
    cout << "\nDay\tDay Temp (°F)\tNight Temp (°F)\n";
    for (int i = 0; i < dayTemps.size(); ++i) {
        cout << i + 1 << "\t" << dayTemps[i] << "\t\t" << nightTemps[i] << "\n";
    }
}
//cal func
void calculateFluctuations(const vector<float>& dayTemps, const vector<float>& nightTemps) {
    float totalFluctuation = 0;
    //all the data assign to 0 and all are eq
    float maxDayTemp = dayTemps[0], minDayTemp = dayTemps[0];
    float maxNightTemp = nightTemps[0], minNightTemp = nightTemps[0];
	
	//"i" is day temp value
    for (int i = 0; i < dayTemps.size(); ++i) {
        float fluctuation = dayTemps[i] - nightTemps[i];
        totalFluctuation += fluctuation;

		//Updates maxDayTemp and minDayTemp if necessary
        if (dayTemps[i] > maxDayTemp) maxDayTemp = dayTemps[i];
        if (dayTemps[i] < minDayTemp) minDayTemp = dayTemps[i];
        if (nightTemps[i] > maxNightTemp) maxNightTemp = nightTemps[i];
        if (nightTemps[i] < minNightTemp) minNightTemp = nightTemps[i];
    }
	//sum for avg
    float avgFluctuation = totalFluctuation / dayTemps.size();//daytempsize means total number of elements 
	//fluc list
    cout << "\nDaily Temperature Fluctuations Calculated.\n";
    cout << "Average Monthly Temperature Fluctuation: " << avgFluctuation << "°F\n";
    cout << "Max Day Temperature: " << maxDayTemp << "°F\n";
    cout << "Min Day Temperature: " << minDayTemp << "°F\n";
    cout << "Max Night Temperature: " << maxNightTemp << "°F\n";
    cout << "Min Night Temperature: " << minNightTemp << "°F\n";
}
//analyze suitability func
void analyzeSuitability(const vector<float>& dayTemps, const vector<float>& nightTemps) {
    bool suitable = true;

    for (int i = 0; i < dayTemps.size(); ++i) {
        float fluctuation = dayTemps[i] - nightTemps[i];
		//if not 10<fluc<15 output false
        if (!(fluctuation >= 10 && fluctuation <= 15)) {
            suitable = false;
            break;
        }
		//if not 60<nighttemp<62 output false
        if (!(nightTemps[i] >= 60 && nightTemps[i] <= 62)) {
            suitable = false;
            break;
        }
		//if not 70<daytemp<80 output false
        if (!(dayTemps[i] >= 70 && dayTemps[i] <= 80)) {
            suitable = false;
            break;
        }
    }
	//output that those are suitable or not
	//if yes
    if (suitable) {
        cout << "Temperature conditions are suitable for orchid flowering.\n";
    } 
    //if not
	else {
        cout << "Temperature conditions are NOT suitable for orchid flowering.\n";
    }
}
//convert C to F
float convertToFahrenheit(float celsius) {
    return (celsius * 9/5) + 32;
}
//convert F to C
float convertToCelsius(float fahrenheit) {
    return (fahrenheit - 32) * 5/9;
}
//save data func
void saveData(const vector<float>& dayTemps, const vector<float>& nightTemps) {
	//you can choose a file as you're wish
    ofstream outFile("temperature_data.txt");
    //if file is available
    if (outFile.is_open()) {
        for (int i = 0; i < dayTemps.size(); ++i) {
            outFile << dayTemps[i] << "         " << nightTemps[i] << "\n";
        }
        outFile.close();
        //show after proccess.if it is done
        cout << "Data saved successfully.\n";
        //if its not done
    } else {
    	//if file wont open
        cout << "Error opening file for saving!\n";
    }
}
//load data
void loadData(vector<float>& dayTemps, vector<float>& nightTemps) {
	//use also above file to contain data
    ifstream inFile("temperature_data.txt");
    if (inFile.is_open()) {
        for (int i = 0; i < dayTemps.size(); ++i) {
            inFile >> dayTemps[i] >> nightTemps[i];
        }
        inFile.close();
        //if it is done
        cout << "Data loaded successfully.\n";
    } else {
    	//if not
        cout << "Error opening file for loading!\n";
    }
}



