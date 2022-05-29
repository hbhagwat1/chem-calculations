#include <iostream>
#include <string>
#include <map>
#include <fstream>
#include "Conversions.h"
using namespace std;

int main() {
    Values v;
    v.read_elements();

    cout << endl << "** Possible units: g   mg   mol   mmol   L   mL **" << endl;
    cout << "Enter amount of chemical (ex. 3.4 mol): ";
    cin >> v.known_amount >> v.known_unit;
    cout << endl << "Convert to: ";
    cin >> v.unknown_unit;

    if (v.known_unit == v.unknown_unit) { // same units
        cout << endl << "Answer: " << v.known_amount << " " << v.known_unit << endl;
    }
    else if (v.known_unit == "g" && v.unknown_unit == "mg") {
        cout << endl << "Answer: " << v.g_to_mg(v.known_amount) << " mg" << endl;
    }
    else if (v.known_unit == "g" && v.unknown_unit == "mol") {
        int convert_using;
        cout << endl << "[1] Use chemical formula" << endl << "[2] Use molar mass";
        cout << endl << "Enter [1] or [2]: ";
        cin >> convert_using;
        if (convert_using == 1) {
            cout << endl << "Enter formula: ";
            cin >> v.chem_formula;
            cout << endl << "Answer: " << v.g_to_mol(v.known_amount) << " mol" 
            << endl;
        }
        else if (convert_using == 2) {
            double molar_mass;
            cout << endl << "Enter molar mass (ex. 1 g/mol or 1 kg/mol): ";
            cin >> molar_mass >> v.molar_mass_unit;
            cout << endl << "Answer: " << v.g_to_mol(v.known_amount, molar_mass) 
            << " mol" << endl;
        }
    }
    else if (v.known_unit == "g" && v.unknown_unit == "L") {
        cout << endl << "Enter density (ex. 2 g/mL, 2 g/L) or molarity (ex. 2 M, 2 mM): ";
        cin >> v.density >> v.density_unit;
        cout << endl << "Answer: " << v.g_to_L(v.known_amount) << " L" << endl;
    }
    else if (v.known_unit == "g" && v.unknown_unit == "mL") {
        cout << endl << "Enter density (ex. 2 g/mL, 2 g/L) or molarity (ex. 2 M, 2 mM): ";
        cin >> v.density >> v.density_unit;
        cout << endl << "Answer: " << v.g_to_mL(v.known_amount) << " mL" << endl;
    }
    else if (v.known_unit == "mg" && v.unknown_unit == "g") {
        cout << endl << "Answer: " << v.mg_to_g(v.known_amount) << " g" << endl;
    }

    return 0;
}