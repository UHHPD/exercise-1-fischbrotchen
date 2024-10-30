#include <fstream>
#include <iostream>
#include <cmath>

int main() {
    // Open file for the first time to read data and compute the mean
    std::ifstream fin("datensumme.txt");
    double mean = 0;
    double number_of_entries = 0;

    double gelesene_zahl;

    while (fin >> gelesene_zahl) {
        mean += gelesene_zahl;
        number_of_entries += 1;
    }
    fin.close();

    mean = 1 / number_of_entries * mean;

    std::cout << "Mean = " << mean << std::endl;

    // Open file for the second time as specified in exercise to compute variance
    fin.open("datensumme.txt");
    double variance = 0;

   while (fin >> gelesene_zahl) {
        variance += (gelesene_zahl - mean) * (gelesene_zahl - mean);
    }
    fin.close();
    variance = 1 / number_of_entries * variance;

    std::cout << "Variance = " << variance << std::endl;


    // Compute the standard deviation
    double standard_deviation = sqrt(variance);

    std::cout << "Standard deviation = " << standard_deviation << std::endl;
}