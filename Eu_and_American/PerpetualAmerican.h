#pragma once

#include <vector>
#include <iostream>
#include <string>
using namespace std;


class PerpetualAmerican
{
private:
private:
	// Private member functions
	// Initialize the object with default values
	void init();
	// Copy the object data from another object
	void copy(const PerpetualAmerican& o2);

	// Calculate the price of a perpetual American call option
	double PerpetualCall(double S) const;
	// Calculate the price of a perpetual American put option
	double PerpetualPut(double S) const;

public:
	double K; // Strike price
	double sig; // Volatility
	double r; // Risk-free interest rate
	double b; // Cost of carry

	string optType; // Option name (call, put)
public:
// Public member functions

	// Default constructor
	PerpetualAmerican();
	// Copy constructor
	PerpetualAmerican(const PerpetualAmerican& opt);
	// Constructor to set the option type
	PerpetualAmerican(const string& optType);
	// Destructor
	virtual ~PerpetualAmerican();

	// Assignment operator
	PerpetualAmerican& operator =(const PerpetualAmerican& opt);

	// Calculate the price of a perpetual American option for a given stock price
	double Price(double S) const;
};