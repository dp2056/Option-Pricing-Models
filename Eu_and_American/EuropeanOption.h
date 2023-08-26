#ifndef EuropeanOption_h
#define EuropeanOption_h

#include <iostream>
#include <vector>
#include <string>
using namespace std;

class EuropeanOption
{
private:

	// Initializes all default values
	void init();

	// Copy constructor
	void copy(const EuropeanOption& o2);

	// 'Kernel' functions for option calculations
	// Calculates the price of a call option
	double CallPrice(double U) const;

	// Calculates the price of a put option
	double PutPrice(double U) const;

	// Calculates the delta of a call option
	double CallDelta(double U) const;

	//Calculates the delta of a put option
	double PutDelta(double U) const;

	// Calculates the first derivative of delta for a call option using divided differences
	double CallDelta_DD(const double& U, double h) const;

	// Calculates the first derivative of delta for a call option using divided differences
	double PutDelta_DD(const double& U, double h) const;

	// Calculates the second derivative of a call option using divided differences
	double Gamma_DD(const double& U, double h) const;

	// Gaussian functions
	// The probability density function of a standard normal distribution
	double n(double x) const;

	// The cumulative distribution function of a standard normal distribution
	double N(double x) const;



public:

	double r;		// Interest rate
	double sig;		// Volatility
	double K;		// Strike price
	double T;		// Expiry date
	double b;		// Cost of carry

	string optType;	// Option name (call, put)
	string unam;	// Name of underlying asset

public:	// Public functions
	// Default constructor creates a call option
	EuropeanOption();

	// Copy constructor
	EuropeanOption(const EuropeanOption& option2);

	// Constructor to create an option of a specific type
	EuropeanOption(const string& optionType);

	// Destructor
	virtual ~EuropeanOption();

	// Assignment operator
	EuropeanOption& operator = (const EuropeanOption& option2);

	// Functions that calculate option price and sensitivities
	// Calculates the option price
	double Price(double U) const;

	// Calculates the delta
	double Delta(double U) const;

	// Calculates d1, which is used in the Black-Scholes formula
	double d1(double U) const;

	// Calculates the gamma
	double Gamma(double U) const;

	// Calculates the second derivative of delta using central finite differences
	double DeltaDD(const double& U, double h);

	// Parity functions
	// Checks the call-put parity relationship
	std::string Check(double U) const;

	// Modifier functions
	// Changes the option type (C/P, P/C)
	void toggle();
};



#endif