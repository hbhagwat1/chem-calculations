#include <iostream>
#include <string>
#include <map>
#include <fstream>
#include <vector>
#include <stdio.h>
#include <string.h>
#include "Conversions.h"
using namespace std;

class Task {
    public:

    int convert_using;
    double molar_mass;

    /* EFFECTS: Prompts user to enter formula and prints molecular
    weight using Values::calc_molar_mass() */
    void task_calc_mw() {
        Values v;
        v.read_elements();
        cout << "Enter chemical formula (ex. H2O): ";
        string formula;
        cin >> formula;
        cout << "Molecular weight of " << formula << ": " 
        << v.calc_molar_mass(formula)
        << " g/mol   " << v.calc_molar_mass(formula) / 1000.0 <<
        " kg/mol" << endl;
    }
    /* EFFECTS: Prints message with converted values based on units
    provided. Calls formula_or_mass() where user must input molecular 
    weight */
    void task_convert() {
        Values v;
        v.read_elements();
        convert_prompt(v);
        if (v.known_unit == v.unknown_unit) { // same units
            cout << endl << "Answer: " << v.known_amount << " " << v.known_unit 
            << endl;
        }
        else if (v.known_unit == "g" && v.unknown_unit == "mg") {
            cout << endl << "Answer: " << v.g_to_mg(v.known_amount) << " mg" 
            << endl;
        }
        else if (v.known_unit == "g" && v.unknown_unit == "mol") {
            double (Values::*a) (double) = &Values::g_to_mol;
            double (Values::*b) (double, double) = &Values::g_to_mol;
            formula_or_mass(v, a, b);
        }
        else if (v.known_unit == "g" && v.unknown_unit == "mmol") {
            double (Values::*a) (double) = &Values::g_to_mmol;
            double (Values::*b) (double, double) = &Values::g_to_mmol;
            formula_or_mass(v, a, b);
        }
        else if (v.known_unit == "g" && v.unknown_unit == "L") {
            density_prompt(v);
            if (v.density_unit == "M" || v.density_unit == "mM") {
                double (Values::*a) (double) = &Values::g_to_L;
                double (Values::*b) (double, double) = &Values::g_to_L;
                formula_or_mass(v, a, b);
                return;
            }
            cout << endl << "Answer: " << v.g_to_L(v.known_amount) << " L" << endl;
        }
        else if (v.known_unit == "g" && v.unknown_unit == "mL") {
            density_prompt(v);
            if (v.density_unit == "M" || v.density_unit == "mM") {
                double (Values::*a) (double) = &Values::g_to_mL;
                double (Values::*b) (double, double) = &Values::g_to_mL;
                formula_or_mass(v, a, b);
                return;
            }
            cout << endl << "Answer: " << v.g_to_mL(v.known_amount) << " mL" << endl;
        }
        else if (v.known_unit == "mg" && v.unknown_unit == "g") {
            cout << endl << "Answer: " << v.mg_to_g(v.known_amount) << " g" << endl;
        }
        else if (v.known_unit == "mg" && v.unknown_unit == "mol") {
            double (Values::*a) (double) = &Values::mg_to_mol;
            double (Values::*b) (double, double) = &Values::mg_to_mol;
            formula_or_mass(v, a, b);
        }
        else if (v.known_unit == "mg" && v.unknown_unit == "mmol") {
            double (Values::*a) (double) = &Values::mg_to_mmol;
            double (Values::*b) (double, double) = &Values::mg_to_mmol;
            formula_or_mass(v, a, b);
        }
        else if (v.known_unit == "mg" && v.unknown_unit == "L") {
            density_prompt(v);
            if (v.density_unit == "M" || v.density_unit == "mM") {
                double (Values::*a) (double) = &Values::mg_to_L;
                double (Values::*b) (double, double) = &Values::mg_to_L;
                formula_or_mass(v, a, b);
                return;
            }
            cout << endl << "Answer: " << v.mg_to_L(v.known_amount) << " L" << endl;
        }
        else if (v.known_unit == "mg" && v.unknown_unit == "mL") {
            density_prompt(v);
            if (v.density_unit == "M" || v.density_unit == "mM") {
                double (Values::*a) (double) = &Values::mg_to_mL;
                double (Values::*b) (double, double) = &Values::mg_to_mL;
                formula_or_mass(v, a, b);
                return;
            }
            cout << endl << "Answer: " << v.mg_to_mL(v.known_amount) << " mL" << endl;
        }
        else if (v.known_unit == "mol" && v.unknown_unit == "g") {
            double (Values::*a) (double) = &Values::mol_to_g;
            double (Values::*b) (double, double) = &Values::mol_to_g;
            formula_or_mass(v, a, b);
        }
        else if (v.known_unit == "mol" && v.unknown_unit == "mg") {
            double (Values::*a) (double) = &Values::mol_to_mg;
            double (Values::*b) (double, double) = &Values::mol_to_mg;
            formula_or_mass(v, a, b);
        }
        else if (v.known_unit == "mol" && v.unknown_unit == "mmol") {
            cout << endl << "Answer: " << v.mol_to_mmol(v.known_amount) << " mmol" << endl;
        }
        else if (v.known_unit == "mol" && v.unknown_unit == "L") {
            density_prompt(v);
            if (v.density_unit == "g/mL" || v.density_unit == "g/L") {
                double (Values::*a) (double) = &Values::mol_to_L;
                double (Values::*b) (double, double) = &Values::mol_to_L;
                formula_or_mass(v, a, b);
                return;
            }
            cout << endl << "Answer: " << v.mol_to_L(v.known_amount) << " L" << endl;
        }
        else if (v.known_unit == "mol" && v.unknown_unit == "mL") {
            density_prompt(v);
            if (v.density_unit == "g/mL" || v.density_unit == "g/L") {
                double (Values::*a) (double) = &Values::mol_to_mL;
                double (Values::*b) (double, double) = &Values::mol_to_mL;
                formula_or_mass(v, a, b);
                return;
            }
            cout << endl << "Answer: " << v.mol_to_mL(v.known_amount) << " mL" << endl;
        }
        else if (v.known_unit == "mmol" && v.unknown_unit == "g") {
            double (Values::*a) (double) = &Values::mmol_to_g;
            double (Values::*b) (double, double) = &Values::mmol_to_g;
            formula_or_mass(v, a, b);
        }
        else if (v.known_unit == "mmol" && v.unknown_unit == "mg") {
            double (Values::*a) (double) = &Values::mmol_to_mg;
            double (Values::*b) (double, double) = &Values::mmol_to_mg;
            formula_or_mass(v, a, b);
        }
        else if (v.known_unit == "mmol" && v.unknown_unit == "mol") {
            cout << endl << "Answer: " << v.mmol_to_mol(v.known_amount) << " mol" << endl;
        }
        else if (v.known_unit == "mmol" && v.unknown_unit == "L") {
            density_prompt(v);
            if (v.density_unit == "g/mL" || v.density_unit == "g/L") {
                double (Values::*a) (double) = &Values::mmol_to_L;
                double (Values::*b) (double, double) = &Values::mmol_to_L;
                formula_or_mass(v, a, b);
                return;
            }
            cout << endl << "Answer: " << v.mmol_to_L(v.known_amount) << " L" << endl;
        }
        else if (v.known_unit == "mmol" && v.unknown_unit == "mL") {
            density_prompt(v);
            if (v.density_unit == "g/mL" || v.density_unit == "g/L") {
                double (Values::*a) (double) = &Values::mmol_to_mL;
                double (Values::*b) (double, double) = &Values::mmol_to_mL;
                formula_or_mass(v, a, b);
                return;
            }
            cout << endl << "Answer: " << v.mmol_to_mL(v.known_amount) << " mL" << endl;
        }
        else if (v.known_unit == "L" && v.unknown_unit == "g") {
            density_prompt(v);
            if (v.density_unit == "M" || v.density_unit == "mM") {
                double (Values::*a) (double) = &Values::L_to_g;
                double (Values::*b) (double, double) = &Values::L_to_g;
                formula_or_mass(v, a, b);
                return;
            }
            cout << endl << "Answer: " << v.L_to_g(v.known_amount) << " g" << endl;
        }
        else if (v.known_unit == "L" && v.unknown_unit == "mg") {
            density_prompt(v);
            if (v.density_unit == "M" || v.density_unit == "mM") {
                double (Values::*a) (double) = &Values::L_to_mg;
                double (Values::*b) (double, double) = &Values::L_to_mg;
                formula_or_mass(v, a, b);
                return;
            }
            cout << endl << "Answer: " << v.L_to_mg(v.known_amount) << " mg" << endl;
        }
        else if (v.known_unit == "L" && v.unknown_unit == "mol") {
            density_prompt(v);
            if (v.density_unit == "g/L" || v.density_unit == "g/mL") {
                double (Values::*a) (double) = &Values::L_to_mol;
                double (Values::*b) (double, double) = &Values::L_to_mol;
                formula_or_mass(v, a, b);
                return;
            }
            cout << endl << "Answer: " << v.L_to_mol(v.known_amount) << " mol" << endl;
        }
        else if (v.known_unit == "L" && v.unknown_unit == "mmol") {
            density_prompt(v);
            if (v.density_unit == "g/L" || v.density_unit == "g/mL") {
                double (Values::*a) (double) = &Values::L_to_mmol;
                double (Values::*b) (double, double) = &Values::L_to_mmol;
                formula_or_mass(v, a, b);
                return;
            }
            cout << endl << "Answer: " << v.L_to_mmol(v.known_amount) << " mmol" << endl;
        }
        else if (v.known_unit == "L" && v.unknown_unit == "mL") {
            cout << endl << "Answer: " << v.L_to_mL(v.known_amount) << " mL" << endl;
        }
        else if (v.known_unit == "mL" && v.unknown_unit == "g") {
            density_prompt(v);
            if (v.density_unit == "M" || v.density_unit == "mM") {
                double (Values::*a) (double) = &Values::mL_to_g;
                double (Values::*b) (double, double) = &Values::mL_to_g;
                formula_or_mass(v, a, b);
                return;
            }
            cout << endl << "Answer: " << v.mL_to_g(v.known_amount) << " g" << endl;
        }
        else if (v.known_unit == "mL" && v.unknown_unit == "mg") {
            density_prompt(v);
            if (v.density_unit == "M" || v.density_unit == "mM") {
                double (Values::*a) (double) = &Values::mL_to_mg;
                double (Values::*b) (double, double) = &Values::mL_to_mg;
                formula_or_mass(v, a, b);
                return;
            }
            cout << endl << "Answer: " << v.mL_to_mg(v.known_amount) << " mg" << endl;
        }
        else if (v.known_unit == "mL" && v.unknown_unit == "mol") {
            density_prompt(v);
            if (v.density_unit == "g/L" || v.density_unit == "g/mL") {
                double (Values::*a) (double) = &Values::mL_to_mol;
                double (Values::*b) (double, double) = &Values::mL_to_mol;
                formula_or_mass(v, a, b);
                return;
            }
            cout << endl << "Answer: " << v.mL_to_mol(v.known_amount) << " mol" << endl;
        }
        else if (v.known_unit == "mL" && v.unknown_unit == "mmol") {
            density_prompt(v);
            if (v.density_unit == "g/L" || v.density_unit == "g/mL") {
                double (Values::*a) (double) = &Values::mL_to_mmol;
                double (Values::*b) (double, double) = &Values::mL_to_mmol;
                formula_or_mass(v, a, b);
                return;
            }
            cout << endl << "Answer: " << v.mL_to_mmol(v.known_amount) << " mmol" << endl;
        }
        else if (v.known_unit == "mL" && v.unknown_unit == "L") {
            cout << endl << "Answer: " << v.mL_to_L(v.known_amount) << " L" << endl;
        }
        else {
            cout << "ERROR: Invalid units" << endl;
        }
    }
    /* EFFECTS: Calls functions required to calculate and print
    limiting reactant, from inputted chemical formula */
    void task_lim_reactant(Values &val) {
        string chem_equation;
        cout << endl << "** Example format: 6 CO2 + 6 H2O > C6H12O6 + 6 O2 **" 
        << endl;
        cout << "Enter chemical equation: ";
        cin.ignore(1, '\n');
        getline(cin, chem_equation);
        val.read_reactants(chem_equation);
        val.limiting_reactant();
        val.print_limiting_reactant();
    }
    /* EFFECTS: Calls functions to calculate limiting reactant and to
    calculate and print theoretical yield, from inputted chemical formula */
    void task_theor_yield(Values &val) {
        string chem_equation;
        cout << endl << "** Example format: 6 CO2 + 6 H2O > C6H12O6 + 6 O2 **" 
        << endl;
        cout << "Enter chemical equation: ";
        cin.ignore(1, '\n');
        getline(cin, chem_equation);
        val.read_products(chem_equation);
        val.limiting_reactant();
        val.theoretical_yield();
    }

    private:
    /* EFFECTS: Prints accepted units and prompts user to enter
    amount and unit of known value and unit of unknown value */
    void convert_prompt(Values &val) {
        cout << endl << "** Accepted units: g   mg   mol   mmol   L   mL **" << endl;
        cout << "Enter amount of chemical (ex. 3.4 mol): ";
        cin >> val.known_amount >> val.known_unit;
        cout << endl << "Convert to: ";
        cin >> val.unknown_unit;
    }
    /* EFFECTS: Prints accepted units and prompts user to enter
    density with unit */
    void density_prompt(Values &val) {
        cout << endl << "** Accepted units: g/mL   g/L   M   mM **";
        cout << endl << "Enter density or molarity with unit (ex. 2 M): ";
        cin >> val.density >> val.density_unit;
    }
    /* EFFECTS: Prompts user to indicate source of molecular weight.
    Calls corresponding function using pointer to print output */
    void formula_or_mass(Values val, double (Values::*func1)(double), 
    double (Values::*func2)(double, double)) {
        cout << endl << "[1] Use chemical formula" << endl 
            << "[2] Use molar mass";
            cout << endl << "Select [1] or [2]: ";
            cin >> convert_using;
            if (convert_using == 1) {
                cout << endl << "Enter formula: ";
                cin >> val.chem_formula;
                cout << endl << "Answer: " << (val.*func1)(val.known_amount) 
                << " " << val.unknown_unit << endl;
            }
            else if (convert_using == 2) {
                cout << "** Accepted units: g/mol   kg/mol **";
                cout << endl << "Enter molar mass and unit: ";
                cin >> molar_mass >> val.molar_mass_unit;
                cout << endl << "Answer: " << (val.*func2)(val.known_amount, molar_mass) 
                << " " << val.unknown_unit << endl;
            }
    }
};

int main() {
    Task t;
    Values v;
    v.read_elements();
    cout << "#### CHEMISTRY CALCULATOR ####" << endl << endl;
    cout << "[1] Molecular weight from formula" << endl <<
            "[2] Unit conversion" << endl <<
            "[3] Limiting reactant" << endl <<
            "[4] Theoretical yield" << endl <<
            "Select task number: ";
    int task_num;
    cin >> task_num;
    if (task_num == 1) {
        t.task_calc_mw();
    }
    else if (task_num == 2) {
        t.task_convert();
    }
    else if (task_num == 3) {
        t.task_lim_reactant(v);
    }
    else if (task_num == 4) {
        t.task_theor_yield(v);
    }
    else {
        cout << "ERROR: Invalid task number" << endl;
        return 1;
    }
    return 0;
}