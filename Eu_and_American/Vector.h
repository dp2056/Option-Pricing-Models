#pragma once

#include "EuropeanOption.h"
#include "PerpetualAmerican.h"
#include <vector>

class OptionCalculator {
public:
    // Default constructor
    OptionCalculator();

    // Destructor
    ~OptionCalculator();

    // Calculates option prices using divided difference method
    // Returns a vector of option prices corresponding to the given h values
    std::vector<double> DDOption(EuropeanOption& opt, const double& AssetPrice, const std::vector<double>& hvec);

    // Calculates option prices using either the Black-Scholes
    // depending on the value of the 'function' parameter
    // The 'parameter' parameter determines which parameter to vary in the option pricing formula
    // Returns a vector of option prices corresponding to the given parameter values
    //The 'function' parameter determines which function, call, delta, delta_dd(not varying h) or gamma.
    std::vector<double> Option(EuropeanOption& opt, const double& AssetPrice, const std::vector<double>& vecparameter, const char& parameter, const char& function);

    // The 'parameter' parameter determines which parameter to vary in the option pricing formula
    // Returns a vector of option prices corresponding to the given parameter values
    std::vector<double> AmericanOption(PerpetualAmerican& opt, const double& AssetPrice, const std::vector<double>& vecparameter, const char& parameter);
};
