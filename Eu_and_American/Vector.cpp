#include "Vector.h"

//default constructor
OptionCalculator::OptionCalculator() {}

//destructor
OptionCalculator::~OptionCalculator() {}



std::vector<double> OptionCalculator::DDOption(EuropeanOption& opt, const double& AssetPrice, const std::vector<double>& hvec)
{
    std::vector<double> result(hvec.size());  //storing result
    for (std::size_t i = 0; i < hvec.size(); ++i)
    {
        result[i] = opt.DeltaDD(AssetPrice, hvec[i]); // at the same S, changing h with vec of values.
    }
    return result;
}

std::vector<double> OptionCalculator::Option(EuropeanOption& opt, const double& AssetPrice, const std::vector<double>& vecparameter, const char& parameter, const char& function)
{
	std::vector<double> result(vecparameter.size());
	for (int i = 0; i < vecparameter.size(); i++)
	{
		switch (function)
		{
		case 'D':  // Delta parameter
			switch (parameter)
			{
			case 'T': // changing time
				opt.T = vecparameter[i];
				result[i] = opt.Delta(AssetPrice);
				break;
			case 'K': // changing strike
				opt.K = vecparameter[i];
				result[i] = opt.Delta(AssetPrice);
				break;
			case 'sig': // changing sigma
				opt.sig = vecparameter[i];
				result[i] = opt.Delta(AssetPrice);
				break;
			case 'r': // changing r
				opt.r = vecparameter[i];
				result[i] = opt.Delta(AssetPrice);
				break;
			case 'b': // changing b
				opt.b = vecparameter[i];
				result[i] = opt.Delta(AssetPrice);
				break;
			default: // keeping default by changing Assetprice 
				double x = opt.Delta(vecparameter[i]);
				result[i] = x;
				break;
			}
			break;

		case 'F': // Divided difference method for delta parameter
			switch (parameter)
			{
			case 'T':
				opt.T = vecparameter[i];
				result[i] = opt.DeltaDD(AssetPrice, AssetPrice * 0.01); // getting h by mult AssetPrice with 0.01 which is an approximation. 
				break;
			case 'K':
				opt.K = vecparameter[i];
				result[i] = opt.DeltaDD(AssetPrice, AssetPrice * 0.01);
				break;
			case 'sig':
				opt.sig = vecparameter[i];
				result[i] = opt.DeltaDD(AssetPrice, AssetPrice * 0.01);
				break;
			case 'r':
				opt.r = vecparameter[i];
				result[i] = opt.DeltaDD(AssetPrice, AssetPrice * 0.01);
				break;
			case 'b':
				opt.b = vecparameter[i];
				result[i] = opt.DeltaDD(AssetPrice, AssetPrice * 0.01);
				break;
			default:
				double x = opt.DeltaDD(vecparameter[i], vecparameter[i] * 0.01);
				result[i] = x;
				break;
			}
			break;
		case 'G': // Gamma parameter
			switch (parameter)
			{
			case 'T':
				opt.T = vecparameter[i];
				result[i] = opt.Gamma(AssetPrice);
				break;
			case 'K':
				opt.K = vecparameter[i];
				result[i] = opt.Gamma(AssetPrice);
				break;
			case 'sig':
				opt.sig = vecparameter[i];
				result[i] = opt.Gamma(AssetPrice);
				break;
			case 'r':
				opt.r = vecparameter[i];
				result[i] = opt.Gamma(AssetPrice);
				break;
			case 'b':
				opt.b = vecparameter[i];
				result[i] = opt.Gamma(AssetPrice);
				break;
			default:
				double x = opt.Gamma(vecparameter[i]);
				result[i] = x;
				break;
			}
			break;

		default: // keeping default for normal call or price option
			switch (parameter)
			{
			case 'T':
				opt.T = vecparameter[i];
				result[i] = opt.Price(AssetPrice);
				break;
			case 'K':
				opt.K = vecparameter[i];
				result[i] = opt.Price(AssetPrice);
				break;
			case 'sig':
				opt.sig = vecparameter[i];
				result[i] = opt.Price(AssetPrice);
				break;
			case 'r':
				opt.r = vecparameter[i];
				result[i] = opt.Price(AssetPrice);
				break;
			case 'b':
				opt.b = vecparameter[i];
				result[i] = opt.Price(AssetPrice);
				break;
			default:
				double x = opt.Price(vecparameter[i]);
				result[i] = x;
				break;
			}
			break;

		}
	}
	return result;

}

//similar function as above but no function parameter because either call or put which is depended upon optType
std::vector<double> OptionCalculator::AmericanOption(PerpetualAmerican& opt, const double& AssetPrice, const std::vector<double>& vecparameter, const char& parameter)
{
	std::vector<double> result(vecparameter.size());
	for (int i = 0; i < vecparameter.size(); i++)
	{
		switch (parameter)
		{
		case 'K':
			opt.K = vecparameter[i];
			result[i] = opt.Price(AssetPrice);
			break;
		case 'sig':
			opt.sig = vecparameter[i];
			result[i] = opt.Price(AssetPrice);
			break;
		case 'r':
			opt.r = vecparameter[i];
			result[i] = opt.Price(AssetPrice);
			break;
		case 'b':
			opt.b = vecparameter[i];
			result[i] = opt.Price(AssetPrice);
			break;
		default:
			double x = opt.Price(vecparameter[i]);
			result[i] = x;
			break;
		}
	}
	return result;

}