#include<stdio.h>

unsigned long long modulus_exponention(unsigned long long int base, unsigned long long int exp, unsigned long long mod){
    unsigned long long result=1;

    base = base % mod; // to reduce the large number to small number

    while (exp != 0) {
        if(exp % 2 != 0){
            result = (result*base) % mod;
        }
        base = (base*base) % mod;
        exp = exp/2;
    }
    return result;
}

unsigned long long take_input(int limit){
    unsigned long long var;
    while(1){
        if(scanf("%llu", &var) != 1 || var<limit){
            printf("\nInvalid input. Please enter positive integer.\n");
            while (getchar() != '\n');
        }
        else{
            break;
        }
    }

    return var;
}

int main(){
    unsigned long long base,exponent,modulus, result;

    printf("Enter Base: ");
    base = take_input(1); // Base should be positive

    printf("Enter Exponent: ");
    exponent = take_input(0); // exponent should be >=0

    printf("Enter Modulus: ");
    modulus = take_input(2); // modulus should be >=2
    
    result = modulus_exponention(base, exponent, modulus);

    printf("Result: %llu\n", result);


    return 0;
}