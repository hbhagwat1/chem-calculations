#include <iostream>
#include <string>
#include <map>
#include <fstream>
#include "Conversions.h"
using namespace std;

void Values::read_elements() {
    string key;
    double value;
    ifstream ins;
    ins.open("elements.txt");
    while (ins >> key >> value) {
        molar_masses[key] = value;
    }
    ins.close();
}

// Grams functions
double Values::g_to_mg(double grams_in) {
    return grams_in * 1000;
}

double Values::g_to_mol(double grams_in) {
    return grams_in * (1 / calc_molar_mass(chem_formula));
}

double Values::g_to_mol(double grams_in, double molar_mass) {
    if (molar_mass_unit == "g/mol") {
        return grams_in * (1 / molar_mass);
    }
    else if (molar_mass_unit == "kg/mol") {
        return grams_in * (1 / 1000.0) * (1 / molar_mass);
    }
    return -1;
}

double Values::g_to_mmol(double grams_in) {
    return g_to_mol(grams_in) * 1000;
}

double Values::g_to_L(double grams_in) {
    if (density_unit == "g/mL") {
        return grams_in * (1 / density) * (1 / 1000.0);
    }
    else if (density_unit == "g/L") {
        return grams_in * (1 / density);
    }
    return -1;
}

double Values::g_to_mL(double grams_in) {
    return g_to_L(grams_in) * 1000;
}

// Milligrams functions
double Values::mg_to_g(double mg_in) {
    return mg_in / 1000;
}

double Values::mg_to_mol(double mg_in) {
    return mg_in * (1 / 1000.0) * (1 / calc_molar_mass(chem_formula));
}

double Values::mg_to_mol(double mg_in, double molar_mass) {
    if (molar_mass_unit == "g/mol") {
        return mg_in * (1 / 1000.0) * (1 / molar_mass);
    }
    else if (molar_mass_unit == "kg/mol") {
        return mg_in * (1 / 1000.0) * (1 / 1000.0) * (1 / molar_mass);
    }
    return -1;
}

double Values::mg_to_mmol(double mg_in) {
    return mg_to_mol(mg_in) * 1000;
}

double Values::mg_to_L(double mg_in) {
    if (density_unit == "g/mL") {
        return mg_in * (1 / 1000.0) * (1 / density) * (1 / 1000.0);
    }
    else if (density_unit == "g/L") {
        return mg_in * (1 / 1000.0) * (1 / density);
    }
    return -1;
}

double Values::mg_to_mL(double mg_in) {
    return mg_to_L(mg_in) * 1000;
}

// Moles functions
double Values::mol_to_g(double mol_in) {
    return mol_in * calc_molar_mass(chem_formula);
}
double Values::mol_to_g(double mol_in, double molar_mass) {
    if (molar_mass_unit == "g/mol") {
        return mol_in * molar_mass;
    }
    else if (molar_mass_unit == "kg/mol") {
        return mol_in * molar_mass * 1000;
    }
    return -1;
}
double Values::mol_to_mg(double mol_in) {
    return mol_to_g(mol_in) * 1000;
}
double Values::mol_to_mg(double mol_in, double molar_mass) {
    return mol_to_g(mol_in, molar_mass) * 1000;
}
double Values::mol_to_mmol(double mol_in) {
    return mol_in * 1000;
}
double Values::mol_to_L(double mol_in) {
    if (density_unit == "g/mL") {
        return mol_in * calc_molar_mass(chem_formula) * (1 / density) * (1 / 1000.0);
    }
    else if (density_unit == "g/L") {
        return mol_in * calc_molar_mass(chem_formula) * (1 / density);
    }
    return -1;
}
double Values::mol_to_L(double mol_in, double molar_mass) {
    if (molar_mass_unit == "g/mol") {
        if (density_unit == "g/mL") {
            return mol_in * molar_mass * (1 / density) * (1 / 1000.0);
        }
        else if (density_unit == "g/L") {
            return mol_in * molar_mass * (1 / density);
        }
    }
    else if (molar_mass_unit == "kg/mol") {
        if (density_unit == "g/mL") {
            return mol_in * molar_mass * 1000 * (1 / density) * (1 / 1000.0);
        }
        else if (density_unit == "g/L") {
            return mol_in * molar_mass * 1000 * (1 / density);
        }
    }
    return -1;
}
double Values::mol_to_mL(double mol_in) {
    return mol_to_L(mol_in) * 1000;
}
double Values::mol_to_mL(double mol_in, double molar_mass) {
    return mol_to_L(mol_in, molar_mass) * 1000;
}
// Millimoles functions
double Values::mmol_to_g(double mmol_in) {
    return mol_to_g(mmol_in) / 1000.0;
}
double Values::mmol_to_g(double mmol_in, double molar_mass) {
    return mol_to_g(mmol_in, molar_mass) / 1000.0;
}
double Values::mmol_to_mg(double mmol_in) {
    return mol_to_g(mmol_in) / 1000.0;
}
double Values::mmol_to_mg(double mmol_in, double molar_mass) {
    return mol_to_g(mmol_in) / 1000.0;
}
double Values::mmol_to_mol(double mmol_in) {
    return mmol_in / 1000.0;
}
double Values::mmol_to_L(double mmol_in) {
    return mol_to_L(mmol_in) / 1000.0;
}
double Values::mmol_to_L(double mmol_in, double molar_mass) {
    return mol_to_L(mmol_in, molar_mass) / 1000.0;
}
double Values::mmol_to_mL(double mmol_in) {
    return mmol_to_L(mmol_in) * 1000;
}
double Values::mmol_to_mL(double mmol_in, double molar_mass) {
    return mmol_to_L(mmol_in, molar_mass) * 1000;
}
// Liters functions
double Values::L_to_g(double L_in) {
    if (density_unit == "g/mL") {
        return L_in * 1000 * density;
    }
    else if (density_unit == "g/L") {
        return L_in * density;
    }
    return -1;
}
double Values::L_to_mg(double L_in) {
    return L_to_g(L_in) * 1000;
}
double Values::L_to_mol(double L_in) {
    if (density_unit == "g/mL") {
        return L_in * 1000 * density * (1 / calc_molar_mass(chem_formula)); 
    }
    else if (density_unit == "g/L") {
        return L_in * density * (1 / calc_molar_mass(chem_formula));
    }
    return -1;
}
double Values::L_to_mol(double L_in, double molar_mass) {
    if (density_unit == "g/mL") {
        if (molar_mass_unit == "g/mol") {
            return L_in * 1000 * density * (1 / molar_mass);
        }
        else if (molar_mass_unit == "kg/mol") {
            return L_in * 1000 * density * (1 / 1000.0) * (1 / molar_mass);
        }
    }
    else if (density_unit == "g/L") {
        if (molar_mass_unit == "g/mol") {
            return L_in * density * (1 / molar_mass);
        }
        else if (molar_mass_unit == "kg/mol") {
            return L_in * density * (1 / 1000.0) * (1 / molar_mass);
        }
    }
    return -1;
}
double Values::L_to_mmol(double L_in) {
    return L_to_mol(L_in) * 1000;
}
double Values::L_to_mmol(double L_in, double molar_mass) {
    return L_to_mol(L_in) * 1000;
}
double Values::L_to_mL(double L_in) {
    return L_in * 1000;
}
double Values::mL_to_g(double mL_in) {
    return L_to_g(mL_in) / 1000.0;
}
double Values::mL_to_mg(double mL_in) {
    return L_to_mg(mL_in) / 1000.0;
}
double Values::mL_to_mol(double mL_in) {
    return L_to_mol(mL_in) / 1000.0;
}
double Values::mL_to_mol(double mL_in, double molar_mass) {
    return L_to_mol(mL_in, molar_mass);
}
double Values::mL_to_L(double mL_in) {
    return mL_in / 1000.0;
}

double Values::calc_molar_mass(string chem_formula_in) {
    const char *form = chem_formula_in.c_str();
    double mass = 0;
    int i = 0;
    while (form[i]) {
        string letters = "";
        if (form[i] && form[i] >= 'A' && form[i] <= 'Z') {
            letters += form[i];
            ++i;
            if (form[i] && form[i] >= 'a' && form[i] <= 'z') {
                letters += form[i];
                ++i;
            }
        }
        string numbers = "";
        if (form[i] && form[i] >= '0' && form[i] <= '9') {
            numbers += form[i];
            ++i;
        }
        if (numbers == "") {
            mass += molar_masses[letters];
        }
        else {
            mass += (molar_masses[letters] * stoi(numbers));
        }
    }
    return mass;
}