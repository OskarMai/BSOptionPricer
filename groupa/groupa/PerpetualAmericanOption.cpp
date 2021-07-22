//Perpetual american option class source file
//Group AB
#include "PerpetualAmericanOption.h"
#include <iostream>
#include <sstream>
#include <cmath>

namespace omai {
	namespace Options {
		//CONSTRUCTORS
		PerpetualAmericanOption::PerpetualAmericanOption():Option() {};
		PerpetualAmericanOption::PerpetualAmericanOption( double k, double vol, double rate, double B):Option(0, k, vol, rate, B) {};
		PerpetualAmericanOption::PerpetualAmericanOption(double t, double k, double vol, double rate, double B):Option(0, k, vol, rate, B) {};
		PerpetualAmericanOption::PerpetualAmericanOption(double t):Option(t) {};
		PerpetualAmericanOption::PerpetualAmericanOption(const PerpetualAmericanOption& opt):Option(opt) {};
		PerpetualAmericanOption::~PerpetualAmericanOption() {};

		//SELECTOR
		double PerpetualAmericanOption::Price(double S) const {//calls corresponding price func
			if (otype == 0.0) return CallPrice(S);
			else return PutPrice(S);
		};
		double PerpetualAmericanOption::CallPrice(double S) const {
			double y1 = 0.5 - (b / (sig * sig)) + sqrt(((b/(sig*sig))-0.5) * ((b / (sig * sig)) - 0.5) + ((2.0 * r) / (sig * sig)));
			return (K/(y1-1))*pow((((y1-1.0)/y1)*(S/K)),y1);
		}
		double PerpetualAmericanOption::PutPrice(double S) const {
			double y2 = 0.5 - (b / (sig * sig)) - sqrt(((b / (sig * sig)) - 0.5) * ((b / (sig * sig)) - 0.5) + ((2.0 * r) / (sig * sig)));
			return (K / (1.0-y2)) * pow((((y2 - 1.0) / y2) * (S / K)), y2);
		}
		double PerpetualAmericanOption::Delta(double S) const {//DDDelta approximation
			double h = 0.000000000001;//hardcode h in bc we want it to be small and not require two params
			double p1 = (*this).Price(S + h);//V(S+h)
			double p2 = (*this).Price(S - h);//V(S-h)
			return (p1 - p2) / (2 * h);
		};
		double PerpetualAmericanOption::Gamma(double S) const {//DDgamma approximation
			double h = 0.000000000001;//hardcode h in
			double p1 = (*this).Price(S + h);//first part of formual
			double p2 = (*this).Price(S);//second part
			double p3 = (*this).Price(S - h);//third part
			return (p1 - 2 * p2 + p3) / (h * h);
		};


		//ToString
		std::string PerpetualAmericanOption::ToString() const {
			std::stringstream ss;//string stream
			ss << "Opt Type: " << otype << ", r: " << r << ", Volatility: " << sig << ", Strike Price: " << K;
			std::string tmp = ss.str();//storing stream elements
			return tmp;
		};
		//MODIFIER

		//OPERATOR
		PerpetualAmericanOption& PerpetualAmericanOption::operator = (const PerpetualAmericanOption& opt) {
			if (this == &opt) return *this;
			Option::operator=(opt);
			return *this;
		}
	}
}