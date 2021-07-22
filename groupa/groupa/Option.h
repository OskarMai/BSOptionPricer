//Option Base Class Header File
#ifndef OPTION_HPP
#define OPTION_HPP
namespace omai {
	namespace Options {
		class Option {//abstract base class
		protected:
			//common to all options
			double K;//strike price
			double T;//Exercise date
			double r;//risk-free interest rate
			double sig;//constant volatility
			double b;
			double otype;//call and puts are very similar so we make one class and use otype to diff
			//otype=0 is a call
			//any other value is a put
		public:

			//CONSTRUCTORS
			Option():r(0.05), sig(0.2), K(110), T(0.5), otype(0), b(r) {};//default constructor
			Option(double t, double k, double vol, double rate,double B):T(t),K(k),sig(vol),r(rate),b(B),otype(0) {};//initializing constructor
			Option(double type) :r(0.05), sig(0.2), K(110), T(0.5), otype(type), b(r) {};//type constructor
			Option(const Option& opt):T(opt.T), K(opt.K), sig(opt.sig), r(opt.r), b(opt.b),otype(opt.otype) {};//copy constructor
			virtual ~Option() {};//destrctors

			//SELECTOR
			double type() const;
			virtual double Price(double S) const = 0;//pure virtual member func
			virtual double Delta(double S) const = 0;//force derived class to make own implementation
			virtual double Gamma(double S) const = 0;


			//MODIFIER
			void type(double t);
			//OPERATOR
			Option& operator = (const Option& o);

		};
	}
}
#endif
