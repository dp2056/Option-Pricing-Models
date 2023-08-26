#include "EuropeanOption.h"
#include <cmath>


double EuropeanOption::n(double x) const
{
	double A = 1.0 / sqrt(2.0 * 3.1415); // using pie approx value
	return A * exp(-x * x * 0.5);
}

double EuropeanOption::N(double x) const
{ // The approximation to the cumulative normal distribution

	double a1 = 0.4361836;
	double a2 = -0.1201676;
	double a3 = 0.9372980;

	// Compute k value
	double k = 1.0 / (1.0 + (0.33267 * x));

	if (x >= 0.0)
	{
		// Return the approximation to the cumulative normal distribution
		return 1.0 - n(x) * (a1 * k + (a2 * k * k) + (a3 * k * k * k));
	}
	else
	{
		// If x is negative, use symmetry to approximate the cumulative normal distribution
		return 1.0 - N(-x);
	}
}

double EuropeanOption::CallPrice(double U) const
{
	double tmp = sig * sqrt(T);

	double d1 = (log(U / K) + (b + (sig * sig) * 0.5) * T) / tmp;
	double d2 = d1 - tmp;


	// Calculate and return the price of a call option
	return (U * exp((b - r) * T) * N(d1)) - (K * exp(-r * T) * N(d2));
}

double EuropeanOption::PutPrice(double U) const
{
	double tmp = sig * sqrt(T);
	double d1 = (log(U / K) + (b + (sig * sig) * 0.5) * T) / tmp;
	double d2 = d1 - tmp;

	// Calculate and return the price of a put option
	return (K * exp(-r * T) * N(-d2)) - (U * exp((b - r) * T) * N(-d1));
}

// Call Delta function
double EuropeanOption::CallDelta(double U) const
{
	double dOne = d1(U);
	// Calculate and return the delta of a call option
	return exp((b - r) * T) * N(dOne);
}
double EuropeanOption::PutDelta(double U) const
{
	double dOne = d1(U);
	// Calculate and return the delta of a put option
	return exp((b - r) * T) * (N(dOne) - 1);
}


double EuropeanOption::d1(double U) const
{
	double tmp = sig * sqrt(T);
	double d1 = (log(U / K) + (b + (sig * sig) * 0.5) * T) / tmp;

	return d1;
}

// Calculate the gamma of an option
double EuropeanOption::Gamma(double U) const
{
	double tmp = sig * sqrt(T);
	double d12 = d1(U);
	double gamma = n(d12) * exp((b - r) * T) / (U * tmp);
	return gamma;
}

// Calculate the delta of a call option using divided differences
double EuropeanOption::CallDelta_DD(const double& U, double h) const
{
	double f1 = Price(U - h);
	double f2 = Price(U);
	double f3 = Price(U + h);
	return (f3 - f1) / (2.0 * h);
}

double EuropeanOption::PutDelta_DD(const double& U, double h) const
{
	double f1 = Price(U - h);
	double f2 = Price(U);
	double f3 = Price(U + h);

	double callDelta = (f3 - f1) / (2.0 * h);

	// Use put-call parity to convert call delta to put delta
	double putDelta = callDelta - 1.0;

	return putDelta;
}


// Calculate the Gamma of option using divided differences
double EuropeanOption::Gamma_DD(const double& U, double h) const
{
	double f1 = Price(U - h);
	double f2 = Price(U);
	double f3 = Price(U + h);
	return (f3 - 2.0 * f2 + f1) / (h * h);
}



/////////////////////////////////////////////////////////////////////////////////////

void EuropeanOption::init()
{	// Initialise all default values

	// Default values
	r = 0.05;
	sig = 0.2;

	K = 110.0;
	T = 0.5;

	b = 0;			// Black and Scholes stock option model (1973)

	optType = "C";		// European Call Option (this is the default type)
}

//copying values
void EuropeanOption::copy(const EuropeanOption& o2)
{
	r = o2.r;
	sig = o2.sig;
	K = o2.K;
	T = o2.T;
	b = o2.b;

	optType = o2.optType;
}

EuropeanOption::EuropeanOption()
{ // Default call option
	init();
}

EuropeanOption::EuropeanOption(const EuropeanOption& o2)
{ // Copy constructor
	copy(o2);
}

EuropeanOption::EuropeanOption(const string& optionType)
{	// Create option type
	init();
	optType = optionType;

	if (optType == "c")
		optType = "C";
}


// destructor
EuropeanOption::~EuropeanOption()	{}

// assignment operator definition
EuropeanOption& EuropeanOption::operator = (const EuropeanOption& option2)
{
	if (this == &option2) return *this;

	copy(option2);

	return *this;
}

// Functions that calculate option price and sensitivities
double EuropeanOption::Price(double U) const
{
	if (optType == "C")
	{
		
		return CallPrice(U);
	}
	else
	{
	
		return PutPrice(U);
	}
}

// Delta function that calls either CallDelta or PutDelta based on the option type
double EuropeanOption::Delta(double U) const
{
	if (optType == "C")
	{

		return CallDelta(U);
	}
	else
	{

		return PutDelta(U);
	}
}

double EuropeanOption::DeltaDD(const double& U, double h)
{
	if (optType == "C")
	{

		return CallDelta_DD(U, h);
	}
	else
	{

		return PutDelta_DD(U, h);
	}
}

// Modifier functions
void EuropeanOption::toggle()
{ // Change option type (C/P, P/C)

	if (optType == "C")
		optType = "P";
	else
		optType = "C";
}

//Function to check if put-call parity holds
std::string EuropeanOption::Check(double U) const
{
    double call = CallPrice(U);
    double put = PutPrice(U);

    double putParity = call + K * std::exp(-r * T) - U;
    double callParity = put + U - K * std::exp(-r * T);

    if (std::abs(call - callParity) < 1e-5 && std::abs(put - putParity) < 1e-5)
    {
        return "Put-call parity holds.\n";
    }
    else
    {
        return "Put-call parity does not hold.\n";
    }
}
