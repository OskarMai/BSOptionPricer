//Group A 
//Euor Option class source file
#include "EuroOption.h"
#include <iostream>
#include <string.h>
#include <boost/random.hpp>
#include <boost/math/distributions.hpp>
#include <cmath>
#include <sstream>

namespace omai {
	namespace Options {
		//CONSTRUCTORS
		EuroOption::EuroOption() :Option() {};//colon syntax
		EuroOption::EuroOption(double t, double k, double vol, double rate,double B) :Option(t,k,vol,rate,B) {};//initializing constructor
		EuroOption::EuroOption(double t) :Option(t) {};
		EuroOption::EuroOption(const EuroOption& opt) :Option(opt) {};//copy constructor
		EuroOption::~EuroOption() {};//destructor

		//SELECTORS

		double EuroOption::CallPrice(double S) const {//returns call price
			//defining d1 and d2
			double d1 = (log(S / K) + ((b + (sig * sig) / 2.0) * T)) / (sig * sqrt(T));//d1 formula (4) on pdf
			double d2 = d1 - (sig * sqrt(T));
			return (S)*exp((b-r)*T)*N(d1) - K * exp(-r * T) * N(d2);//return call price formula
		}
		double EuroOption::PutPrice(double S) const {//returns put price
			//defining d1 and d2
			double d1 = (log(S / K) + ((b + (sig * sig) / 2.0) * T)) / (sig * sqrt(T));//d1 formula (4) on pdf
			double d2 = d1 - (sig * sqrt(T));
			return K * exp(-r * T) * N(-d2) - S*exp((b-r)*T) * N(-d1);//return call price formula
		}
		double EuroOption::n(double x) const {//pdf
			double PI = 2 * acos(0.0);
			double A = 1.0 / sqrt(2.0 * PI);
			return A * exp(-x * x * 0.5);
		}

		double EuroOption::N(double x) const {//cdf
			boost::math::normal_distribution<> norm;//boost normal (gaussian) distribution
			if (x >= 0.0) { return boost::math::cdf(norm, x); };
			return 1 - boost::math::cdf(norm, -x);//returns this is x negative
		}

		//GREEKS
		double EuroOption::Gamma(double S) const {
			double d1 = (log(S / K) + ((b + (sig * sig) / 2.0) * T)) / (sig * sqrt(T));
			return n(d1)*exp((b-r)*T)/(S*sig*sqrt(T));
		}
		double EuroOption::CallDelta(double S) const {
			double d1 = (log(S / K) + ((b + (sig * sig) / 2.0) * T)) / (sig * sqrt(T));
			return exp((b-r)*T)*N(d1);
		}
		double EuroOption::PutDelta(double S) const {
			double d1 = (log(S / K) + ((b + (sig * sig) / 2.0) * T)) / (sig * sqrt(T));
			return exp((b - r) * T) * (N(d1) - 1.0);
		}
		double EuroOption::Delta(double S) const {
			if (otype == 0) return CallDelta(S);
			else return PutDelta(S);
		}
		double EuroOption::DDGamma(double S, double h) const {
			double p1 = (*this).Price(S + h);//first part of formual
			double p2 = (*this).Price(S);//second part
			double p3 = (*this).Price(S - h);//third part
			return (p1-2*p2+p3)/(h*h);
		}
		double EuroOption::DDDelta(double S, double h) const {
			if (otype == 0) return DDCallDelta(S, h);//if it is a call, call DDCallDelta
			return DDPutDelta(S, h);//if above cond not hit then return putdelta
		}
		double EuroOption::DDCallDelta(double S, double h) const {
			double p1 = (*this).CallPrice(S+h);//V(S+h)
			double p2 = (*this).CallPrice(S-h);//V(S-h)
			return (p1-p2)/(2*h);
		}
		double EuroOption::DDPutDelta(double S, double h) const {
			double p1 = (*this).PutPrice(S + h);//V(S+h)
			double p2 = (*this).PutPrice(S - h);//V(S-h)
			return (p1 - p2) / (2 * h);
		}
		//PRICE
		double EuroOption::Price(double S) const {//calls different member func depending on opt type
			if (otype == 0.0) {//if a call option
				return CallPrice(S);//return call price
			}
			return PutPrice(S);//else put price
		}

		//PARITY
		double EuroOption::PutCallParity(double S) const {//should compute price of the oppsite option
			//i.e. euro call option will return equivalent euro put option value
			if ((*this).otype == 0.0) { return PutPrice(S); }
			return CallPrice(S);//if not type "C", then must be a put, so return CallPrice()
		}
		bool EuroOption::InParity(double S) const {
			if (otype == 0.0) { return ((*this).Price(S) + K * exp(-r * T) == (*this).PutCallParity(S) + S); }//following formula
			return((*this).PutCallParity(S) + K * exp(-r * T) == (*this).Price(S) + S);//if option is a put
			//(*this).Price() gives curr option price while (*this).PutCallParity() gives opposite option price
		}

		//TOSTRING
		std::string EuroOption::ToString() const {
			std::stringstream ss;//string stream
			ss << "Opt Type: " << otype << ", r: " << r << ", Volatility: " << sig << ", Strike Price: " << K << ", Expiry Time: " << T;
			std::string tmp = ss.str();//storing stream elements
			return tmp;
		};

		//MODIFIERS

		//OPERATORS
		EuroOption& EuroOption::operator=(const EuroOption& o) {
			if (this == &o) return *this;
			Option::operator=(o);
			return *this;
		}
	}
}