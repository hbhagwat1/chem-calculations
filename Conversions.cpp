#include <iostream>
#include <iomanip>
#include <string>
#include <map>
#include <fstream>
#include <vector>
#include <stdio.h>
#include <string.h>
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
        while (form[i] && form[i] >= '0' && form[i] <= '9') {
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

void Values::read_reactants(string chem_equation_in) {
    char equat[100];
    strcpy(equat, chem_equation_in.c_str());
    char *reactants = strtok(equat, ">");
    char *products = strtok(NULL, ">");
    char *compound = strtok(reactants, " +");
    int i = 0;
    while (compound) {
        string new_str(compound);
        if (i % 2 == 0) {
            if (*compound >= '0' && *compound <= '9') {
                r_coefficients.push_back(stoi(new_str));
                compound = strtok(NULL, " +");
            }
            else {
                r_coefficients.push_back(1);
            }
        }
        else {
            r_compounds.push_back(new_str);
            compound = strtok(NULL, " +");
        }
        ++i;
    }
}

void Values::read_products(string chem_equation_in) {
    char equat[100];
    strcpy(equat, chem_equation_in.c_str());
    char *reactants = strtok(equat, ">");
    char *products = strtok(NULL, ">");
    char *compound = strtok(products, " +");
    int i = 0;
    while (compound) {
        string new_str(compound);
        if (i % 2 == 0) {
            if (*compound >= '0' && *compound <= '9') {
                p_coefficients.push_back(stoi(new_str));
                compound = strtok(NULL, " +");
            }
            else {
                p_coefficients.push_back(1);
            }
        }
        else {
            p_compounds.push_back(new_str);
            compound = strtok(NULL, " +");
        }
        ++i;
    }
}

void Values::limiting_reactant() {
    double mass;
    for (int i = 0; i < r_compounds.size(); ++i) {
        cout << "Enter mass of " << r_compounds[i] << " in g: ";
        cin >> mass;
        double mol_calc = mass / calc_molar_mass(r_compounds[i]);
        mol_calc = mol_calc / r_coefficients[i];
        if (mol_calc <= lim_reactant_mol) {
            lim_reactant = r_compounds[i];
            lim_reactant_coeff = r_coefficients[i];
            lim_reactant_mol = mol_calc;
        }
    }
}

void Values::print_limiting_reactant() {
    cout << endl << "Limiting reactant: " << lim_reactant << endl;
}

void Values::theoretical_yield() {
    cout << endl;
    for (int i = 0; i < p_compounds.size(); ++i) {
        cout << p_compounds[i] << ": ";
        double ratio = p_coefficients[i] / static_cast<double>(lim_reactant_coeff);
        theor_yield_mol = lim_reactant_mol * ratio;
        chem_formula = p_compounds[i];
        cout << theor_yield_mol << " mol   " << mol_to_g(theor_yield_mol) 
        << " g" << endl;
    }
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

double Values::g_to_mmol(double grams_in, double molar_mass) {
    return g_to_mol(grams_in, molar_mass) * 1000;
}

double Values::g_to_L(double grams_in) {
    if (density_unit == "g/mL") {
        return grams_in * (1 / density) * (1 / 1000.0);
    }
    else if (density_unit == "g/L") {
        return grams_in * (1 / density);
    }
    else if (density_unit == "M") {
        return grams_in * (1 / calc_molar_mass(chem_formula)) * (1 / density);
    }
    else if (density_unit == "mM") {
        return grams_in * (1 / calc_molar_mass(chem_formula)) * 1000 * (1 / density);
    }
    else {
        return -1;
    }
}

double Values::g_to_L(double grams_in, double molar_mass) {
    if (density_unit == "M") {
        if (molar_mass_unit == "g/mol") {
            return grams_in * (1 / molar_mass) * (1 / density);
        }
        else if (molar_mass_unit == "kg/mol") {
            return grams_in * (1 / 1000.0) * (1 / molar_mass) * (1 / density);
        }
    }
    else if (density_unit == "mM") {
        if (molar_mass_unit == "g/mol") {
            return grams_in * (1 / molar_mass) * 1000 * (1 / density);
        }
        else if (molar_mass_unit == "kg/mol") {
            return grams_in * (1 / 1000.0) * (1 / molar_mass) * 1000 * (1 / density);
        }
    }
    return -1;
}

double Values::g_to_mL(double grams_in) {
    return g_to_L(grams_in) * 1000;
}

double Values::g_to_mL(double grams_in, double molar_mass) {
    return g_to_L(grams_in, molar_mass) * 1000;
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

double Values::mg_to_mmol(double mg_in, double molar_mass) {
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

double Values::mg_to_L(double mg_in, double molar_mass) {
    return g_to_L(mg_in, molar_mass) / 1000.0;
}

double Values::mg_to_mL(double mg_in) {
    return mg_to_L(mg_in) * 1000;
}

double Values::mg_to_mL(double mg_in, double molar_mass) {
    return g_to_L(mg_in, molar_mass);
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
    else if (density_unit == "M") {
        return mol_in * (1 / density);
    }
    else if (density_unit == "mM") {
        return mol_in * 1000 * (1 / density);
    }
    else {
        return -1;
    }
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
    else if (density_unit == "M") {
        return L_in * density * calc_molar_mass(chem_formula);
    }
    else if (density_unit == "mM") {
        return L_in * density * (1 / 1000.0) * calc_molar_mass(chem_formula);
    }
    else {
        return -1;
    }
}
double Values::L_to_g(double L_in, double molar_mass) {
    if (density_unit == "M") {
        return L_in * density * molar_mass;
    }
    else if (density_unit == "mM") {
        return L_in * density * (1 / 1000.0) * molar_mass;
    }
    else {
        return -1;
    }
}
double Values::L_to_mg(double L_in) {
    return L_to_g(L_in) * 1000;
}
double Values::L_to_mg(double L_in, double molar_mass) {
    return L_to_g(L_in, molar_mass) * 1000;
}
double Values::L_to_mol(double L_in) {
    if (density_unit == "g/mL") {
        return L_in * 1000 * density * (1 / calc_molar_mass(chem_formula)); 
    }
    else if (density_unit == "g/L") {
        return L_in * density * (1 / calc_molar_mass(chem_formula));
    }
    else if (density_unit == "M") {
        return L_in * density;
    }
    else if (density_unit == "mM") {
        return L_in * density * (1 / 1000.0);
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
double Values::mL_to_g(double mL_in, double molar_mass) {
    return L_to_g(mL_in, molar_mass) / 1000.0;
}
double Values::mL_to_mg(double mL_in) {
    return L_to_mg(mL_in) / 1000.0;
}
double Values::mL_to_mg(double mL_in, double molar_mass) {
    return L_to_mg(mL_in, molar_mass) / 1000.0;
}
double Values::mL_to_mol(double mL_in) {
    return L_to_mol(mL_in) / 1000.0;
}
double Values::mL_to_mol(double mL_in, double molar_mass) {
    return L_to_mol(mL_in, molar_mass) / 1000.0;
}
double Values::mL_to_mmol(double mL_in) {
    return L_to_mmol(mL_in) / 1000.0;
}
double Values::mL_to_mmol(double mL_in, double molar_mass) {
    return L_to_mmol(mL_in, molar_mass) / 1000.0;
}
double Values::mL_to_L(double mL_in) {
    return mL_in / 1000.0;
}