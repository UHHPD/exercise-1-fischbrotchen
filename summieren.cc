#include <fstream>
#include <iostream>

int main() {
    std::ifstream fin("daten.txt");
    std::ofstream fout("datensumme.txt");

    for (int i = 0; i < 234; i += 1) {
        int zahl_1;
        int zahl_2;
        fin >> zahl_1;
        fin >> zahl_2;
        int summe = zahl_1 + zahl_2;
        fout << summe << std::endl;
        std::cout << "Summe von " << zahl_1 << " und " << zahl_2 << " = " << summe << std::endl;
    }
    fin.close();
    fout.close();

}