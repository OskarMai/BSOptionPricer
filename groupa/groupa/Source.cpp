//Groups A
// main program
//Exact Solutions of One-Factor Plain Options
#include <iostream>
#include "EuroOption.h"
#include "Mesh.h"
#include "Matrix.h"
#include "Option.h"
#include "Forwarder.h"
#include "PerpetualAmericanOption.h"
using namespace std;
int main() {
	using namespace omai::Options;
	//testing string initialization
	EuroOption call(1);
	cout << call.ToString() << endl;
	EuroOption call2(0.25, 65, 0.3, 0.08, 0.08);//T,K,Sig,r,b
	cout << call2.ToString() << endl;
	EuroOption call3(1.0, 100, 0.2, 0.0, 0.0);
	cout << call3.ToString() << endl;
	EuroOption call4(1.0, 10, 0.5, 0.12, 0.12);
	cout << call4.ToString() << endl;
	EuroOption call5(30.0, 100, 0.3, 0.08, 0.08);
	cout << call5.ToString() << endl;

	//Batch 1
	cout << "Batch 1: " << endl;
	cout << call2.Price(60) << endl;//2.13337 call
	call2.type(1);//changed to put
	cout << call2.ToString() << endl;
	cout << call2.Price(60) << endl;//5.84628 put

	//Batch 2
	cout << "Batch 2: " << endl;
	cout << call3.Price(100) << endl;//7.96557 call
	call3.type(1);//changed to put
	cout << call3.ToString() << endl;
	cout << call3.Price(100) << endl;//7.96557 put

	//Batch 3
	cout << "Batch 3: " << endl;
	cout << call4.Price(5) << endl;//0.204058 call
	call4.type(1);//changed to put
	cout << call4.ToString() << endl;
	cout << call4.Price(5) << endl;//4.07326 put

	//Batch 4
	cout << "Batch 4: " << endl;
	cout << call5.Price(100) << endl;//92.17570 call
	call5.type(1);//changed to put
	cout << call5.ToString() << endl;
	cout << call5.Price(100) << endl;//1.24750 put


	//testing put call parity for determine other price
	cout << call5.PutCallParity(100) << endl;//92.17570
	//inParity?
	cout << call5.InParity(100) << endl;

	//Testing Mesh()
	vector<double> arr = Mesh(call5, 0, 100, 0.5,omai::Options::Price);//creates mesh arr
	for (int i = 0; i < arr.size(); i++) {//should print decreasing values since it is a put option
		cout << arr[i] << ", ";
	}
	std::cout << std::endl << std::endl;

	//Testing Matrix() for Price
	vector<double> params1 = { 0,0.25,65,0.3,0.08,60,70,0.5,0.08 };//params from batch tests
	vector<double> params2 = { 0,1.0,100,0.2,0.0,100,110,0.5,0.0 };
	vector<double> params3 = { 0,1.0,10,0.5,0.12,5,15,0.5,0.12 };
	matrix m1 = { params1,params2,params3 };//creating matrix input
	matrix m2 = Matrix<EuroOption>(m1,Price,0);
	for (int i = 0; i < m2.size(); i++) {
		for (int j = 0; j < m2[i].size(); j++) {
			std::cout << m2[i][j] << ", ";
		}
		std::cout << std::endl << std::endl;
	}
	//cout.precision(10);
	//Testing Greek Sensitivies
	EuroOption set1 = EuroOption(0.5, 100, 0.36, 0.1, 0);
	cout << "CallDelta: "<<set1.CallDelta(105) << endl;
	cout << "PutDelta: " << set1.PutDelta(105) << endl;
	cout << "Gamma: " << set1.Gamma(105) << endl;
	cout << "Delta: " << set1.Delta(105) << endl;

	//Testing call delta prices
	EuroOption set2(0.5, 100, 0.36, 0.1, 0);//initializing call option]
	vector<double> arr1 = Mesh(set2, 105, 115, 1.0, Delta);
	for (int i = 0; i < arr1.size();i++) {
		cout << arr1[i] << ", ";
	}
	cout << endl << endl;

	//Delta Matrix
	vector<double> params4 = { 0,0.25,65,0.3,0.08,60,70,0.5,0.08 };//params from batch tests
	vector<double> params5 = { 0,1.0,100,0.2,0.0,100,110,0.5,0.0 };
	vector<double> params6 = { 0,1.0,10,0.5,0.12,5,15,0.5,0.12 };
	matrix m3 = { params4,params5,params6 };//creating matrix input
	matrix m4 = Matrix<EuroOption>(m3, Delta,0);

	for (int i = 0; i < m4.size(); i++) {
		std::cout << "<";
		for (int j = 0; j < m4[i].size(); j++) {
			std::cout << m4[i][j] << ", ";
		}
		std::cout <<">"<< std::endl << std::endl;
	}
	std::cout << std::endl;

	//Testing Divided Difference approach
	cout << "DDCallDelta: " << set1.DDCallDelta(105,0.01) << endl;
	cout << "DDPutDelta: " << set1.DDPutDelta(105,0.01) << endl;
	cout << "DDGamma: " << set1.DDGamma(105,0.01) << endl;
	cout << "DDDelta: " << set1.DDDelta(105,0.01) << endl;

	//Testing Perpetual American Options
	PerpetualAmericanOption data1(100,0.1,0.1,0.02);//K,sig,r,b
	cout << endl << endl<< "Testing Perpetual American Option Price()" << endl;
	cout << data1.ToString() << endl;
	cout << data1.Price(110) << endl;//Testing Price()
	cout << data1.CallPrice(110) << endl;//testing CallPrice()
	cout << data1.PutPrice(110) << endl;//testing PutPrice()
	//Testing Mesh()
	vector<double> dataset1 = Mesh(data1, 110, 120, 1.0, Price);//option obj, start, end, h, func
	cout << "Mesh for Perpetual American Option: " << endl;
	for (int i = 0; i < dataset1.size(); i++) {
		cout << dataset1[i] << ", ";
	}
	cout << endl;
	//Testing Matrix()
	vector<double> params7 = { 0,0,100,0.1,0.1,110,120,1.0,0.02 };//params from batch tests
	vector<double> params8 = { 1,0,100,0.1,0.1,110,120,1.0,0.02 };
	vector<double> params9 = { 0,0,100,0.1,0.1,130,140,1.0,0.02 };
	matrix PAOMat = { params7,params8,params9 };
	matrix PAOMat2 = Matrix<PerpetualAmericanOption>(PAOMat, Price,1.0);
	cout << "Perpetual American Option Price Matrix:" << endl;
	for (int i = 0; i < PAOMat2.size(); i++) {
		std::cout << "<";
		for (int j = 0; j < PAOMat2[i].size(); j++) {
			std::cout << PAOMat2[i][j] << ", ";
		}
		std::cout << ">" << std::endl << std::endl;
	}
	std::cout << std::endl;
	
	
}