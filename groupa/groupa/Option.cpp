//Option abstract base class source file
#include "Option.h"
namespace omai {
	namespace Options {
		//SELECTORS
		double Option::type() const {
			return otype;
		}
		//MODIFIERS
		void Option::type(double t) {
			otype = t;
		}
		//OPERATOR
		Option& Option::operator = (const Option& o) {
			if (this == &o) return *this;
			r = o.r;
			sig = o.sig;
			K = o.K;
			T = o.T;
			b = o.b;
			otype = o.otype;
			return *this;
		}
	}
}