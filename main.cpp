#include "expression.hpp"

int main(void) {
    using Complex = std::complex<double>;

    Expression<Complex> four(Complex(4, 0));
    Expression<Complex> x("x");
    Expression<Complex> three_i(Complex(0, 3));

    Expression<Complex> term1 = four * x;
    Expression<Complex> result = term1 + three_i;

    Expression<Complex> result1 = result.Exp();



    return 0;
}