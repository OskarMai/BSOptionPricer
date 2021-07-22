//Matrix global function header file
#ifndef MATRIX_HPP
#define MATRIX_HPP
#include <vector>
#include "EuroOption.h"
#include "Mesh.h"
#include "Forwarder.h"
#include "PerpetualAmericanOption.h"
#include "Option.h"
#include <boost/shared_ptr.hpp>

typedef std::vector<std::vector<double>> matrix;
namespace omai {
	namespace Options {
		//input:matrix in the form < <otype,T,K,sig,r,start,end,h>,<>,<>, ... >
		//output:Matrix in the form < <p1,p2,p3,... >, < ... >, ... > where p is the price
		template <typename T>
		matrix Matrix(matrix input,double (*f)(const Option&,double),double type) {
			//type is to differentiate which option, perpetual or euro
			//0 =EuroOption
			//1 = PerpetualAmericanOption
			matrix mat;//declaring matrix to hold vectors
			mat.reserve(100);//extend space

			for (int i = 0; i < input.size(); i++) {//iterates through matrix elements
				/*each element in the matrix is a vector
				index:
				0 = otype
				1 = T
				2 = K
				3 = vol/sig
				4 = r
				5 = start
				6 = end
				7 = h
				8 = b
				//<double type, double t, double k, double vol, double rate, double start, double end, double h,double B>
				*/

				T curr = T(input[i][1], input[i][2], input[i][3], input[i][4], input[i][8]);//temporary holder
				curr.type(input[i][0]);//changing option type
				mat.push_back(Mesh(curr, input[i][5], input[i][6], input[i][7], f));//uses mesh to compute price vector
			}
			return mat;
			
		}
	}
}
#endif
