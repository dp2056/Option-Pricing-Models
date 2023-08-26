/*
 * This program demonstrates the pricing and sensitivity analysis of European Call and Put options.
 * It calculates option prices for multiple batches of parameters and examines how changes in asset price, 
 * strike price, and time to maturity affect Delta and Gamma values. Divided difference method is also utilized for analysis.
 */

#include "EuropeanOption.h"
#include "Vector.h"

// Generate a mesh array from start to end
std::vector<double> mesh(double start, double end, double h)
{
	std::vector<double> result;
	for (start; start < end; start += h)
	{
		double i = start;
		result.push_back(i);
	}
	return result;
}

// Function to print a vector
void Print(std::vector<double> V)
{
	for (int i = 0; i < V.size(); i++)
	{
		std::cout << i + 1 << ". " << V.at(i) << " \n";

	}
	std::cout << "\n\n";
}

// Main function
int main()
{
    // --- Group A: Set 1 ---
	// Initialize and calculate European Options for Batch 1
	std::cout << "Batch 1 :" << std::endl;
	const double S1 = 60, K1 = 65, T1 = 0.25, r1 = 0.08, sig1 = 0.3;
	EuropeanOption Batch1;
	Batch1.K = K1;
	Batch1.T = T1;
	Batch1.r = r1;
	Batch1.sig = sig1;
	Batch1.b = r1;
	std::cout << "Call :";
	std::cout << Batch1.Price(S1) << std::endl; // Call  2.13293
	Batch1.optType = "P";
	std::cout << "Put :";
	std::cout << Batch1.Price(S1) << std::endl;
	std::cout << Batch1.Check(S1) << "\n";
	
	// Initialize and calculate European Options for Batch 2
	std::cout << "Batch 2 :" << std::endl;
	const double S2 = 100, K2 = 100, T2 = 1, sig2 = 0.2, r2 = 0;
	EuropeanOption Batch2;
	Batch2.K = K2;
	Batch2.T = T2;
	Batch2.r = r2;
	Batch2.sig = sig2;
	Batch2.b = r2;
	std::cout << "Call :";
	std::cout << Batch2.Price(S2) << std::endl; //7.96632
	Batch2.optType = "P";
	std::cout << "Put :";
	std::cout << Batch2.Price(S2) << std::endl;
	std::cout << Batch2.Check(S2) << "\n";

	// Initialize and calculate European Options for Batch 3
	std::cout << "Batch 3 :" << std::endl;
	const double S3 = 5, K3 = 10, T3 = 1, sig3 = 0.5, r3 = 0.12;
	EuropeanOption Batch3;
	Batch3.K = K3;
	Batch3.T = T3;
	Batch3.r = r3;
	Batch3.sig = sig3;
	Batch3.b = r3;
	std::cout << "Call :";
	std::cout << Batch3.Price(S3) << std::endl; //0.204121
	Batch3.optType = "P";
	std::cout << "Put :";
	std::cout << Batch3.Price(S3) << std::endl;
	std::cout << Batch3.Check(S3) << "\n";

	// Initialize and calculate European Options for Batch 4
	std::cout << "Batch 4 :" << std::endl;
	const double S4 = 100, K4 = 100, T4 = 30, sig4 = 0.3, r4 = 0.08;
	EuropeanOption Batch4;
	Batch4.K = K4;
	Batch4.T = T4;
	Batch4.r = r4;
	Batch4.sig = sig4;
	Batch4.b = r4;
	std::cout << "Call :";
	std::cout << Batch4.Price(S4) << std::endl; // 92.1747
	Batch4.optType = "P";
	std::cout << "Put :";
	std::cout << Batch4.Price(S4) << std::endl;
	std::cout << Batch4.Check(S4) << "\n\n";

	// Analyze option prices for a range of asset prices
	std::vector<double> assetpricevec = mesh(S4, 120, 4);
	OptionCalculator Monoprice;
	std::cout << "Option Price for Monotonically increasing\nrange of asset price from 100 to 120 :\n";
	std::cout << "Put : \n";
	Print(Monoprice.Option(Batch4, S4, assetpricevec, 'S', 'O'));
	Batch4.optType = "C";
	std::cout << "Call : \n";
	Print(Monoprice.Option(Batch4, S4, assetpricevec, 'S', 'O'));

	// Analyze option prices for a range of strike prices
	std::vector<double> strikevec = mesh(K4, 120, 5);
	std::cout << "Option Price for Monotonically increasing\nrange of strike price from 100 to 120 :\n";
	std::cout << "Call : \n";
	Print(Monoprice.Option(Batch4, S4, strikevec, 'K', 'O'));
	Batch4.optType = "P";
	std::cout << "Put : \n";
	Print(Monoprice.Option(Batch4, S4, strikevec, 'K', 'O'));


	//Part A : Set 2

	// Implement Gamma using dataset
	std::cout << "Batch 5 :" << std::endl;
	const double S5 = 105, K5 = 100, T5 = 0.5, sig5 = 0.36, r5 = 0.1;
	EuropeanOption Batch5;
	Batch5.K = K5;
	Batch5.T = T5;
	Batch5.r = r5;
	Batch5.sig = sig5;
	Batch5.b = 0;
	Batch5.optType = "C";
	std::cout << "Gamma for the data provided is : ";
	std::cout << Batch5.Gamma(S5) << std::endl;
	std::cout << "Call Delta : ";
	std::cout << Batch5.Delta(S5) << std::endl;
	std::cout << "Put Delta : ";
	Batch5.optType = "P";
	std::cout << Batch5.Delta(S5) << std::endl;

	// Analyze Delta for a range of asset prices
	OptionCalculator MonoDelta;
	std::vector<double> asstprice5 = mesh(S5, 125, 5);
	std::cout << "\nDelta for Monotonically increasing\nrange of asset price from 100 to 120 :\n";
	std::cout << "Put Delta : \n";
	Print(MonoDelta.Option(Batch5, S5, asstprice5, 'S', 'D'));
	Batch5.optType = "C";
	std::cout << "Call Delta : \n";
	Print(MonoDelta.Option(Batch5, S5, asstprice5, 'S', 'D'));

	// Analyze Delta and Gamma for a range of times to maturity
	OptionCalculator MonoGamma;
	std::vector<double> Tvec = mesh(T5, 1.5, 0.2);
	std::cout << "\nDelta for Monotonically increasing\nrange of T from 0.5 to 1.5 :\n";
	std::cout << "Call Delta : \n";
	Print(MonoGamma.Option(Batch5, S5, Tvec, 'T', 'D'));
	Batch5.optType = "P";
	std::cout << "Put Delta : \n";
	Print(MonoGamma.Option(Batch5, S5, Tvec, 'T', 'D'));
	std::cout << "\nGamma for Monotonically increasing\nrange of T from 0.5 to 1.5 :\n";
	Print(MonoGamma.Option(Batch5, S5, Tvec, 'T', 'G'));

	// Analyze Delta using the Divided Difference method
	OptionCalculator Divideddiff;
	double h = 5.0;
	std::vector<double> hvec = mesh(h, 25, 5);
	std::cout << "Put Delta using divided difference method for\n increasing range of h from 1 to 25 :\n";
	Print(Divideddiff.DDOption(Batch5, S5, hvec));
	Batch5.optType = "C";
	std::cout << "Call Delta using divided difference method for\n increasing range of h from 1 to 25 :\n";
	Print(Divideddiff.DDOption(Batch5, S5, hvec));
	std::cout << "Call Delta using divided difference method for Monotonically\n increasing range of asset price from 100 to 120 :\n";
	Print(Divideddiff.Option(Batch5, S5, asstprice5, 'S', 'F'));

	
	return 0;
}


