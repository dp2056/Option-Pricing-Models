#include "PerpetualAmerican.h"

// Default constructor for PerpetualAmerican objects
PerpetualAmerican::PerpetualAmerican()
{
	init();
}

// Copy constructor for PerpetualAmerican objects
PerpetualAmerican::PerpetualAmerican(const PerpetualAmerican& o2)
{
	copy(o2);
}

// Constructor for PerpetualAmerican objects with specified option type
PerpetualAmerican::PerpetualAmerican(const string& optionType)
{
	init();
	optType = optionType;
}

// Destructor for PerpetualAmerican objects
PerpetualAmerican::~PerpetualAmerican() {}

// Calculates the price of a perpetual call option with specified underlying stock price
double PerpetualAmerican::PerpetualCall(double S) const
{
	// Calculate parameters required for call option price calculation
	double sig2 = sig * sig;
	double fac = b / sig2 - 0.5; fac *= fac;
	double y1 = 0.5 - b / sig2 + sqrt(fac + 2.0 * r / sig2);

	// Calculate call option price using calculated parameters
	if (1.0 == y1)
	{
		return S;
	}
	else
	{
		double fac2 = ((y1 - 1.0) * S) / (y1 * K);
		double c = K * pow(fac2, y1) / (y1 - 1.0);

		return c;
	}
}

// Calculates the price of a perpetual put option with specified underlying stock price
double PerpetualAmerican::PerpetualPut(double S) const
{
	// Calculate parameters required for put option price calculation
	double sig2 = sig * sig;
	double fac = b / sig2 - 0.5; fac *= fac;
	double y2 = 0.5 - b / sig2 - sqrt(fac + 2.0 * r / sig2);

	// Calculate put option price using calculated parameters
	if (0.0 == y2)
	{
		return S;
	}
	else
	{
		double fac2 = ((y2 - 1.0) * S) / (y2 * K);
		double p = K * pow(fac2, y2) / (1.0 - y2);

		return p;
	}
}

// Calculates the price of the perpetual option with the specified underlying stock price
double PerpetualAmerican::Price(double S) const
{
	// Determine which type of option to calculate price for and call appropriate function
	if (optType == "C")
	{
		return PerpetualCall(S);
	}
	else
	{
		return PerpetualPut(S);
	}
}

// Initializes all default values for a PerpetualAmerican object
void PerpetualAmerican::init()
{
	// Set default values for all option parameters
	r = 0.05;
	sig = 0.2;
	K = 110.0;
	b = 0;
	optType = "C";
}

// Copies the option parameters from another PerpetualAmerican object
void PerpetualAmerican::copy(const PerpetualAmerican& o2)
{
	// Copy all option parameters from the other object
	r = o2.r;
	sig = o2.sig;
	K = o2.K;
	b = o2.b;
	optType = o2.optType;
}

// Overloads the assignment operator to copy the option parameters from another PerpetualAmerican object
PerpetualAmerican& PerpetualAmerican::operator = (const PerpetualAmerican& option2)
{
	if (this == &option2) return *this;

	copy(option2);

	return *this;
}