#include <iostream>
#include <math.h>
#include <iomanip>
using namespace std;

long double coshFormula(double x) {
    return (pow(M_E, x) + pow(M_E, -x)) / 2;
}

long double sinhFormula(double x) {
    return (pow(M_E, x) - pow(M_E, -x)) / 2;
}

long double formula1(double distance, double sag, double mid) {
    long double answer1 = sag + mid;
    long double answer2 = mid * coshFormula(distance / (2*mid));
    return answer1 - answer2;
}

int main() {
    long double distance, sag;
    cin >> distance >> sag;
    
    long double low = 0.0;
    long double high = pow(10, 9);
    
    while (high - low > 0.00000000001) {
        long double mid = (high + low) / 2;
        if (formula1(distance, sag, mid) > 0) {
            high = mid;
        }
        else {
            low = mid;
        }
    }
    
    long double a = low;
    long double final = 2 * a * sinhFormula(distance / (2*a));
    cout << fixed << setprecision(9) << final << endl;
    
    return 0;
}