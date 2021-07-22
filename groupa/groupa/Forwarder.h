//Forwarder functions to help use member functions as input to global functions
#ifndef FORWARDER_HPP
#define FORWARDER_HPP
#include "Option.h"
namespace omai {
	namespace Options {
		//forwarder functions
		//takes an Option Obj and calls its member functions price or delta
		double Price(const Option& opt, double S){
			//since Option.Price() is a pure vitual func, it will call the dervied class to make implementation
			//we just need to call the option class's Price()
			return opt.Price(S);
		}
		//we will use the same format for Delta and Gamma
		double Delta(const Option& opt, double S) {
			return opt.Delta(S);
		}
		double Gamma(const Option& opt, double S) {
			return opt.Gamma(S);
		}
	}
}
#endif
