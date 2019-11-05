#include <stdio.h>

int gcd(int a, int b);

int main() {
    printf("%d", gcd(16, 8));
    return 0;
}

int gcd(int a, int b){
    // condizione di terminazione
    if(a%b == 0)
        return b;
    else if((a%2)==0 && (b%2)==0)
        return 2*(gcd(a/2, b/2));
    else if((a%2)!=0 && (b%2)==0)
        return (gcd(a, b/2));
    else if((a%2)!=0 && (b%2)!=0)
        return (gcd((a-b)/2, b));
//    else if((a%2)==0 && (b%2)!=0)
//        return a;
}