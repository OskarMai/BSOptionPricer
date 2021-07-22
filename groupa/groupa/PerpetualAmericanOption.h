//Perpetual American Option Class header file
#ifndef PERPETUAL_HPP
#define PERPETUAL_HPP
#include "Option.h"
#include <iostream>
#include <string.h>
namespace omai {
	namespace Options {
		class PerpetualAmericanOption : public Option {
		public:
			//CONSTRUCTORS
			PerpetualAmericanOption();//default constructor
			PerpetualAmericanOption( double k, double vol, double rate, double B);//initializing constructor
			PerpetualAmericanOption(double t, double k, double vol, double rate, double B);//if we want to initialize t value, but it does not matter what value t is
			//only added for compatibility with Matrix() template
			PerpetualAmericanOption(double t);//initializing type=
			PerpetualAmericanOption(const PerpetualAmericanOption& opt);//copy constructor
			~PerpetualAmericanOption();//default destructor

			//SELECTOR
			double Price(double S) const;//calls corresponding price func
			double Delta(double S) const;//gives DDDelta approximation
			double Gamma(double S) const;//gives DDGamama approximation
			double CallPrice(double S) const;//gives call price
			double PutPrice(double S) const;//gives put price
			//ToString
			std::string ToString() const;
			//MODIFIER

			//OPERATOR
			PerpetualAmericanOption& operator = (const PerpetualAmericanOption& opt);
		};
	}
}
#endif
