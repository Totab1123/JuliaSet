#include <complex>
#include <iostream>

#define CHECK 100

int julia(double x, double y, double real, double ima){
    const std::complex<double> i(0.0, 1.0);
    std::complex<double> c(real, ima);
    std::complex<double> z;

    z = x + i * y;
    for(int i = 0; i < CHECK; i++){
        z = z*z + c;
         if(std::abs(z)>10){
            break;
        }
        if(i>CHECK-2){
            return 1;
        }
    }
    return 0;
}

int main(){
    double n, m;

    double r, i;

    std::cout << "input real part: ";
    std::cin >> r;
    std::cout << "input imaginary part: ";
    std::cin >> i;

    for(m = -2; m <= 2; m += 0.05){
        for(n = -2; n <= 2; n += 0.05){
            if(julia(n, m, r, i)==1){
                std::cout<<"○ ";
            }else{
                std::cout<<"● ";
            }
        }
        std::cout<<std::endl;
    }
    
    return 0;
}