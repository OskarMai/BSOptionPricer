//Mesh global function header file
#ifndef MESH_HPP
#define MESH_HPP
#include <algorithm>
#include <vector>
#include "Option.h"
#include "EuroOption.h"
#include "Forwarder.h"
namespace omai {
	namespace Options {
		//MESH ARRAY
		//takes as input a EuroOption opt, start double, end double, and step(h) double
		//outputs a double vector of option prices
		std::vector<double> Mesh(const Option& opt, double start, double end, double h,double (*f)(const Option&, double)) {
			//takes func as a param so we can switch out diff funcs. More flexible.
			//we can use Delta() or Price()
			std::vector<double> mesh;//create a vector to store option prices
			mesh.reserve(100);
			for (start; start < end; start += h) {//iterate at start till end by steps of size h
				mesh.push_back(f(opt,start));//add computed value to array
			}
			return mesh;//return computed vector<double>
		};
	}
}
#endif
