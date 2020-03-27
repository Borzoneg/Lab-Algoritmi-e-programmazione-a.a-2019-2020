#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>


#define N 20

int conta(char s [N], int n){
    int i, g = 0, voc = 0;
    while(s[g+n-1]!= '\n') {
        for (i = (0 + g); s[i] != '\n' && i < (n + g); i++) {
            if (s[i] == 'a' || s[i] == 'e' || s[i] == 'i' || s[i] == 'o' || s[i] == 'u' ||
                s[i] == 'A' || s[i] == 'E' || s[i] == 'I' || s[i] == 'O' || s[i] == 'U')
                voc++;
        }
        if (voc == 2) {

            for (int k = n - 1; k >= 0; k--) {
                printf("%c", s[i - (k+1)]);
            }
            printf("\n");
        }
        voc = 0;
        g++;
    }
}


int main() {
    FILE *fp;
    char filename[N];
    char line[N];
    int  n, j, lenght,i = 0;

    printf("Inserire nome del file ");
    scanf("%s",&filename);

    fp = fopen(filename,"r");

    char c = getc(fp);
    getc(fp);
    n = atoi(&c);
    char testo[n][N];

    while((fgets(line, 20, fp)) != NULL) {
        j = 0;
        while(line[j]!='\n'){
            testo[i][j] = line[j];
            j++;
        }
        testo[i][j] = line[j];
        i++;
    }

    printf("Quanto devono essere lunghe le sottostringhe? ");
    scanf("%d", &lenght);
    for(i=0; i<n; i++){
        conta(testo[i], lenght);
    }


    return 0;
}