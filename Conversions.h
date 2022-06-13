#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <fstream>
using namespace std;

class Values {
    public:
    string chem_formula;
    string known_unit;
    string unknown_unit;
    double known_amount;
    double density;
    string density_unit;
    string molar_mass_unit;

    vector<int> r_coefficients;
    vector<int> p_coefficients;
    vector<string> r_compounds;
    vector<string> p_compounds;

    string lim_reactant;
    int lim_reactant_coeff;
    double lim_reactant_mol = 1000;
    double theor_yield_mol;

    /* EFFECTS: Reads elements and their molar masses from text file
    into molar_masses map */
    void read_elements();

    /* EFFECTS: Adds molar mass of each element from chemical formula to
    calculate total molar mass */
    double calc_molar_mass(string chem_formula_in);

    /* EFFECTS: Reads a chemical equation with the appropriate format 
    (6 CO2 + 6 H2O > C6H12O6 + 6 O2), storing reactant coefficients and
    compounds in member vectors */
    void read_reactants(string chem_equation_in);

    /* EFFECTS: Reads a chemical equation with the appropriate format 
    (6 CO2 + 6 H2O > C6H12O6 + 6 O2), storing product coefficients and
    compounds in member vectors */
    void read_products(string chem_equation_in);

    /* EFFECTS: Calculates limiting reactant based on masses of each
    reactant, storing data in member variables */
    void limiting_reactant();

    /* EFFECTS: Prints limiting reactant to standard output */
    void print_limiting_reactant();

    /* EFFECTS: Prints theoretical yield of each product in mol and g
    using limiting reactant data */
    void theoretical_yield();

    // Grams functions
    double g_to_mg(double grams_in);
    double g_to_mol(double grams_in);
    double g_to_mol(double grams_in, double molar_mass);
    double g_to_mmol(double grams_in);
    double g_to_mmol(double grams_in, double molar_mass);
    double g_to_L(double grams_in);
    double g_to_L(double grams_in, double molar_mass);
    double g_to_mL(double grams_in);
    double g_to_mL(double grams_in, double molar_mass);

    // Milligrams functions
    double mg_to_g(double mg_in);
    double mg_to_mol(double mg_in);
    double mg_to_mol(double mg_in, double molar_mass);
    double mg_to_mmol(double mg_in);
    double mg_to_mmol(double mg_in, double molar_mass);
    double mg_to_L(double mg_in);
    double mg_to_L(double mg_in, double molar_mass);
    double mg_to_mL(double mg_in);
    double mg_to_mL(double mg_in, double molar_mass);

    // Moles functions
    double mol_to_g(double mol_in);
    double mol_to_g(double mol_in, double molar_mass);
    double mol_to_mg(double mol_in);
    double mol_to_mg(double mol_in, double molar_mass);
    double mol_to_mmol(double mol_in);
    double mol_to_L(double mol_in);
    double mol_to_L(double mol_in, double molar_mass);
    double mol_to_mL(double mol_in);
    double mol_to_mL(double mol_in, double molar_mass);

    // Millimoles functions
    double mmol_to_g(double mmol_in);
    double mmol_to_g(double mmol_in, double molar_mass);
    double mmol_to_mg(double mmol_in);
    double mmol_to_mg(double mmol_in, double molar_mass);
    double mmol_to_mol(double mmol_in);
    double mmol_to_L(double mmol_in);
    double mmol_to_L(double mmol_in, double molar_mass);
    double mmol_to_mL(double mmol_in);
    double mmol_to_mL(double mmol_in, double molar_mass);

    // Liters functions
    double L_to_g(double L_in);
    double L_to_g(double L_in, double molar_mass);
    double L_to_mg(double L_in);
    double L_to_mg(double L_in, double molar_mass);
    double L_to_mol(double L_in);
    double L_to_mol(double L_in, double molar_mass);
    double L_to_mmol(double L_in);
    double L_to_mmol(double L_in, double molar_mass);
    double L_to_mL(double L_in);

    // Milliliters functions
    double mL_to_g(double mL_in);
    double mL_to_g(double mL_in, double molar_mass);
    double mL_to_mg(double mL_in);
    double mL_to_mg(double mL_in, double molar_mass);
    double mL_to_mol(double mL_in);
    double mL_to_mol(double mL_in, double molar_mass);
    double mL_to_mmol(double mL_in);
    double mL_to_mmol(double mL_in, double molar_mass);
    double mL_to_L(double mL_in);

    private:
    /* EFFECTS: Map of each element with corresponding molar mass */
    map<string, double> molar_masses;
};