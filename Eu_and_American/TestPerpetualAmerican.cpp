
#include "Vector.h"

std::vector<double> mesh(double start, double end, double h)
{
	std::vector<double> result;
	for (; start < end; start += h)
	{
		result.push_back(start);
	}
	return result;
}
void Print(std::vector<double> V)
{
	for (int i = 0; i < V.size(); i++)
	{
		std::cout << i + 1 << ". " << V.at(i) << " \n";

	}
	std::cout << "\n\n";
}

int main()
{
	//Group B
	//Data
	const double K1 = 100, sig1 = 0.1, r1 = 0.1, b1 = 0.02, S1 = 110;
	PerpetualAmerican Data;
	Data.K = K1;
	Data.sig = sig1;
	Data.r = r1;
	Data.b = b1;
	Data.optType = "C";

	//Question A&B
	//Call
	std::cout << "Perpetual American Call Option price is: ";
	std::cout << Data.Price(S1) << std::endl;
	//Put
	Data.optType = "P";
	std::cout << "Perpetual American Put Option price is: ";
	std::cout << Data.Price(S1) << std::endl;

	//Question C
	//Monotonically increasing S
	Data.optType = "C";
	std::cout << "\n\nCall option price for monotonically increasing asset price is : \n";
	std::vector<double> asstpr = mesh(S1, 130, 5);
	OptionCalculator callpvc;
	Print(callpvc.AmericanOption(Data, S1, asstpr, 'S'));
	
	//Question D
	//Matrix of option parameter
	std::cout << "\nCall Option price for monotonically increasing strike price is : \n";
	std::vector<double> strike = mesh(K1, 110, 2);
	OptionCalculator callstrvc;
	Print(callstrvc.AmericanOption(Data, S1, strike, 'K'));

	return 0;
}