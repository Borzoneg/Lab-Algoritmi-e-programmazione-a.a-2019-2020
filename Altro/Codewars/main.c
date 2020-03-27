#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define N 50
// Who likes it?
char* likes(size_t n, const char *const names[n]);



int main() {

    return 0;
}


char* likes(size_t n, const char *const names[n]) {
    char *risposta = malloc(sizeof(char) * N);
    switch(n){
        case 0:
            sprintf(risposta, "no one likes this");
            break;
        case 1:
            sprintf(risposta,"%s likes this", names[0]);
            break;
        case 2:
            sprintf(risposta, "%s and %s like this", names[0], names[1]);
            break;
        case 3:
            sprintf(risposta, "%s, %s and %s like this", names[0], names[1], names[2]);
            break;
        default:
            sprintf(risposta, "%s, %s and %d other like this", names[0], names[1], n-2);
    }
    return risposta;
}
