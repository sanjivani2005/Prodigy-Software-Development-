#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

// Function prototypes
double celsiusToFahrenheit(double celsius);
double celsiusToKelvin(double celsius);
double fahrenheitToCelsius(double fahrenheit);
double fahrenheitToKelvin(double fahrenheit);
double kelvinToCelsius(double kelvin);
double kelvinToFahrenheit(double kelvin);

int main() {
    double temperature;
    string unit;

    cout << "Enter the temperature value: ";
    cin >> temperature;
    
    cout << "Enter the unit of measurement (C for Celsius, F for Fahrenheit, K for Kelvin): ";
    cin >> unit;

    cout << fixed << setprecision(2); // Set precision for output

    if (unit == "C" || unit == "c") {
        // Convert from Celsius
        cout << temperature << " Celsius is equivalent to:\n";
        cout << celsiusToFahrenheit(temperature) << " Fahrenheit\n";
        cout << celsiusToKelvin(temperature) << " Kelvin\n";
    } else if (unit == "F" || unit == "f") {
        // Convert from Fahrenheit
        cout << temperature << " Fahrenheit is equivalent to:\n";
        cout << fahrenheitToCelsius(temperature) << " Celsius\n";
        cout << fahrenheitToKelvin(temperature) << " Kelvin\n";
    } else if (unit == "K" || unit == "k") {
        // Convert from Kelvin
        cout << temperature << " Kelvin is equivalent to:\n";
        cout << kelvinToCelsius(temperature) << " Celsius\n";
        cout << kelvinToFahrenheit(temperature) << " Fahrenheit\n";
    } else {
        cout << "Invalid unit of measurement! Please use C, F, or K." << endl;
    }

    return 0;
}

// Function definitions
double celsiusToFahrenheit(double celsius) {
    return (celsius * 9.0 / 5.0) + 32.0;
}

double celsiusToKelvin(double celsius) {
    return celsius + 273.15;
}

double fahrenheitToCelsius(double fahrenheit) {
    return (fahrenheit - 32.0) * 5.0 / 9.0;
}

double fahrenheitToKelvin(double fahrenheit) {
    return (fahrenheit - 32.0) * 5.0 / 9.0 + 273.15;
}

double kelvinToCelsius(double kelvin) {
    return kelvin - 273.15;
}

double kelvinToFahrenheit(double kelvin) {
    return (kelvin - 273.15) * 9.0 / 5.0 + 32.0;
}
