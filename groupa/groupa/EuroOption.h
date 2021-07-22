//Options class header file
#ifndef EUROOPTION_HPP
#define EUROOPTION_HPP
#include <string.h>
#include <iostream>
#include "Option.h"
namespace omai {
	namespace Options {
		class EuroOption:public Option{
		public:
			//CONSTRUCTORS
			EuroOption();//constructor
			EuroOption(double t, double k, double vol, double rate, double B);//initializinag construcct
			EuroOption(double t);//initialize type
			EuroOption(const EuroOption& opt);//copy constructor
			virtual ~EuroOption();//virtual destructor

			//SELECTORS
			
			//S = asset price
			double Price(double S) const;
			double CallPrice(double S) const;//computes price of option if a call option
			double PutPrice(double S) const;//computes price of put option

			double n(double x) const;
			double N(double x) const;//cdf

			double Gamma(double S) const;//retunrs gamma val for b=0
			double CallDelta(double S) const;//returns call delta value
			double PutDelta(double S) const;//returns put delta value
			double Delta(double S) const;//calls corresponding delta func depending on opt type
			double DDDelta(double S, double h) const;
			double DDCallDelta(double S, double h) const;//approximates call delta through divided difference approach
			double DDPutDelta(double S, double h) const;//approximates put delta through divided difference approach
			double DDGamma(double S, double h) const;//approximates gamma through divided difference approach
			//CALL DELTA PRICE
			//compute call delta for a monotonically increasing range of underlying values of S
			//output: A vector<double> containing Call Delta values for each S.

			/*
			double Vega(double S) const;//returns vega value. same for put and call
			double CallTheta(double S) const;//returns call theta value
			double PutTheta(double S) const;//returns put theta value
			*/
			std::string ToString() const;
			//putcallparity find other price
			double PutCallParity(double S) const;//needs asset price to compute
			//putcallparity balanced?
			bool InParity(double S) const;//do the options satisfy parity?
			//both options must have the same exp date and strike price

			// MODIFIERS

			//OPERATORS
			EuroOption& operator = (const EuroOption& o);
		};
	}
}
#endif



