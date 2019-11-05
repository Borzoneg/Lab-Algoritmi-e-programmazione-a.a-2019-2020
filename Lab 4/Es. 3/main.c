#include <stdio.h>
#include <string.h>
#include <ctype.h>

char *cercaRegexp(char *src, char *regexp);
int lettereEscluse(char bersaglio, char* iniziolettere);
int lettereincluse(char bersaglio, char* iniziolettere);
int trovaLunghRege(char *regexp);
void aumentaJ(int *j, char* quadra);

int main() {
    char a[] = {"moto Noto voto foto"};
    char b1[] = {".oto"};
    char b2[] = {"[^mN]oto"};
    char b3[] = {"[f]oto"};
    char b4[] = {"\\aoto"};
    char b5 [] = {"\\Aoto"};


    char* asd;
    asd = cercaRegexp(a, b1);
    printf("%c\n", *asd);
    asd = cercaRegexp(a, b2);
    printf("%c\n", *asd);
    asd = cercaRegexp(a, b3);
    printf("%c\n", *asd);
    asd = cercaRegexp(a, b4);
    printf("%c\n", *asd);
    asd = cercaRegexp(a, b5);
    printf("%c\n", *asd);
    return 0;
}


char *cercaRegexp(char *src, char *regexp){
    int i, j, k, lettOk, lunghrege;

    lunghrege = trovaLunghRege(regexp);

    for(i=0, j=0, k=0; i<strlen(src); i++){
        lettOk = 1;

        if(regexp[j] == '[' && regexp[j+1] == '^') {
            lettOk = lettereEscluse(src[i], &regexp[j+2]);
            aumentaJ(&j, &regexp[j]);
        }

        else if(regexp[j] == '['){
            lettOk = lettereincluse(src[i], &regexp[j+1]);
            aumentaJ(&j, &regexp[j]);
        }

        else if(regexp[j] == '\\') {
            if (regexp[j + 1] == 'a'){
                if(!islower(src[i]))
                    lettOk = 0;
            }
            else{
                if(!isupper(src[i]))
                    lettOk = 0;
            }
            j++;
        }

        else if(regexp[j] != src[i] && regexp[j] != '.')
            lettOk = 0;

        if(lettOk) {
            j++;
            k++;
        }
        else {
            j = 0;
            k = 0;
        }

        if(k== lunghrege) {
            i = i - lunghrege + 1;
            return &src[i];
        }
    }
    return NULL;
}


int lettereEscluse(char bersaglio, char* iniziolettere){
while(*iniziolettere != ']'){
    if(bersaglio == *iniziolettere)
        return 0;
    iniziolettere++;
}
return 1;
}


int lettereincluse(char bersaglio, char* iniziolettere){
    while(*iniziolettere != ']'){
        if(bersaglio == *iniziolettere)
            return 1;
        iniziolettere++;
    }
    return 0;
}


int trovaLunghRege(char *regexp){
    int i, lenght;
    for(i=0, lenght= 0; i<strlen(regexp); i++) {
        if (isalpha(regexp[i]))
            lenght++;
        if (regexp[i] == '[') {
            lenght++;
            while (regexp[i] != ']')
                i++;
        }
        if(regexp[i] == '.')
            lenght++;
        if(regexp[i] == '\\') {
            i++;
            lenght++;
        }
    }
    return lenght;
}


void aumentaJ(int *j, char* quadra){
    while(*quadra != ']') {
        *j = *j + 1;
        quadra++;
    }
}