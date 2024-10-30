#include <fstream>
#include <iostream>
#include <cmath>

int main() {
    // Open file for the first time to read data and compute the mean
    std::ifstream fin("datensumme.txt");
    double mean = 0;
    double variance = 0;
    

    std::string line;
    double number_of_entries = 0;

    while (std::getline(fin, line)) {
        number_of_entries += 1;
    }
    fin.close();

    // Calculate number of "bins":
    double bin_size = 9;
    double n_bins = number_of_entries / bin_size;

    // Open output file for means:
    std::ofstream fout_mean("mittelwerte.txt");
    fin.open("datensumme.txt");

    double gelesene_zahl;
    for (int i = 0; i < n_bins; i += 1){
        mean = 0;
        for (int bin_idx = 0; bin_idx < bin_size; bin_idx += 1){
            fin >> gelesene_zahl;
            mean += gelesene_zahl;
            if (bin_idx == bin_size - 1){
                mean = 1 / bin_size * mean;
                fout_mean << mean << std::endl;
            }
        }
    }
    fin.close();
    fout_mean.close();

    // Compute variances
    std::ofstream fout_variance("varianzen.txt");
    std::ifstream fin_mean("mittelwerte.txt");
    fin.open("datensumme.txt");

    double binned_mean = 0;
    for (int i = 0; i < n_bins; i += 1){
        variance = 0;
        fin_mean >> binned_mean;
        for (int bin_idx = 0; bin_idx < bin_size; bin_idx += 1){
            fin >> gelesene_zahl;
            variance += (gelesene_zahl - binned_mean) * (gelesene_zahl - binned_mean);
            if (bin_idx == bin_size - 1){
                variance = 1 / bin_size * variance;
                fout_variance << variance << std::endl;
            }
        }
    }
    fin.close();
    fin_mean.close();
    fout_variance.close();

    // Compute mean of the mean of the binned means and the binned variances
    std::ifstream fin_variance("varianzen.txt");
    fin_mean.open("mittelwerte.txt");

    double mean_of_means = 0;
    double mean_of_variances = 0;
    for (int i = 0; i < n_bins; i += 1) {
        fin_mean >> gelesene_zahl;
        mean_of_means += gelesene_zahl;
        fin_variance >> gelesene_zahl;
        mean_of_variances += gelesene_zahl;
    }
    fin_mean.close();
    fin_variance.close();

    mean_of_means = 1 / n_bins * mean_of_means;
    mean_of_variances = 1 / n_bins * mean_of_variances;

    double mean_from_ex1 = 3.11538;
    double variance_from_ex1 = 2.73455;

    std::cout << "Mean of means from ex2 = " << mean_of_means << ". For comparison: Mean from ex1 = " << mean_from_ex1 << std::endl;
    std::cout << "Mean of variances from ex2 = " << mean_of_variances << ". For comparison: Variance from ex1 = " << variance_from_ex1 << std::endl;

    // Use Bessel's correction: Use n_bins - 1 in the calculation for the sample variance
    fin_mean.open("mittelwerte.txt");
    fin.open("datensumme.txt");

    binned_mean = 0;
    mean_of_variances = 0;
    for (int i = 0; i < n_bins; i += 1){
        variance = 0;
        fin_mean >> binned_mean;
        for (int bin_idx = 0; bin_idx < bin_size; bin_idx += 1){
            fin >> gelesene_zahl;
            variance += (gelesene_zahl - binned_mean) * (gelesene_zahl - binned_mean);
            if (bin_idx == bin_size - 1){
                variance = 1 / (bin_size-1) * variance;
            }
        }
        mean_of_variances += variance;
    }
    fin.close();
    fin_mean.close();

    mean_of_variances = 1 / n_bins * mean_of_variances;
    std::cout << "Mean of variances after Bessel's correction = " << mean_of_variances << ". For comparison: Variance from ex1 = " << variance_from_ex1 << std::endl;
}