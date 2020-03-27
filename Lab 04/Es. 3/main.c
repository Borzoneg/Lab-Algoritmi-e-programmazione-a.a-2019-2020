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
    // i sarà l'indice della stringa in cui stiamo ceercando, aumenterà di 1 in 1 mano mano che i caratteri vengono confrontati
    // j sarà l'indice della regex, aumenterà di 1 se l'elemento j della redex era un punto o un carattere o di altri numeri
    // in altri casi (es: [asd], dopo aver confrontato tutte le 3 lettere j deve aumetare di 5 per "puntare" al carattere succ)
    // k aumenterà ogni volta che troviamo una corrispondenza
    int i, j, k, lettOk, lunghrege;

    // Trovo la lunghezza effettiva della regex, .oto avrà lunhgezza 4 [mno]oto avrà lunghezza sempre 4 e così via
    // mi servirà per individuare correttamente i casi in cui la regex sia nella parola
    lunghrege = trovaLunghRege(regexp);

    // CIclo per ogni carattere della stringa
    for(i=0, j=0, k=0; i<strlen(src); i++){
        // lettOk è un flag, inizialmente è vero quindi voglio trovare i casi in cui lil carattere non vada bene
        lettOk = 1;

        // Caso dove la regex vuole escludere delle lettere
        if(regexp[j] == '[' && regexp[j+1] == '^') {
            lettOk = lettereEscluse(src[i], &regexp[j+2]);
            aumentaJ(&j, &regexp[j]);
        }

        // Caso in cui la reegex si "accontenta" di più lettere in uno stesso posto
        else if(regexp[j] == '['){
            lettOk = lettereincluse(src[i], &regexp[j+1]);
            aumentaJ(&j, &regexp[j]);
        }

        // Casi maiuscole e minuscole
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

        // Caso in cui il carattere della regex a cui siamo arrivati per il confronto non è né uguale al carattere della
        // parola né un punto
        else if(regexp[j] != src[i] && regexp[j] != '.')
            lettOk = 0;
        // Se lettOk è ancora vero ci va bene il carattere k e j aumentano di 1
        if(lettOk) {
            j++;
            k++;
        }
        // Altrimenti j e k ripartono da 0
        else {
            j = 0;
            k = 0;
        }

        // Se k è uguale alla lunghezza della regex abbiamo trovato una corrispondenza, ritorniamo il carattere da cui
        // parte la corrispondenza
        if(k== lunghrege) {
            i = i - lunghrege + 1;
            return &src[i];
        }
    }
    return NULL;
}


int lettereEscluse(char bersaglio, char* iniziolettere){
    // ciclo finchè non trovo la chiusura della quadra che mi indica la fine delle lettere da escludere
    while(*iniziolettere != ']'){
        // Se trovo una lettera dentro la quadra che è uguale alla lettera che sto confrontando non va bene, ritorno 0
        if(bersaglio == *iniziolettere)
            return 0;
        iniziolettere++;
    }
    // se arrivo in fondo vuol dire che sono uscito dalla quadra e che nessuna lettera è uguale alla lettera che sto
    // confrontando, ritorno 1
    return 1;
}


int lettereincluse(char bersaglio, char* iniziolettere){
    while(*iniziolettere != ']'){
        // appena arrivo a un caso in cui la lettera confrontata è uguale a una delle lettere all'interno ritorno 1
        if(bersaglio == *iniziolettere)
            return 1;
        iniziolettere++;
    }
    // altrimenti ritorno 0
    return 0;
}


int trovaLunghRege(char *regexp){
    int i, lenght;
    // ciclo per la lunghezza della regex
    for(i=0, lenght= 0; i<strlen(regexp); i++) {
        // per ogni carattere aumento la lunghezza di uno
        if (isalpha(regexp[i]))
            lenght++;
        // quando trovo una quadra, sia con che senza '^' aumento la lunghezza di 1 e poi salto a dopo le quadre
        if (regexp[i] == '[') {
            lenght++;
            while (regexp[i] != ']')
                i++;
        }
        if(regexp[i] == '.')
            lenght++;
        // se trovo il backslash aumento di uno la lunghezza e i per saltare il carattere 'a' o 'A'
        if(regexp[i] == '\\') {
            i++;
            lenght++;
        }
    }
    return lenght;
}


void aumentaJ(int *j, char* quadra){
    // finché non raggiungo la fine della quadra
    while(*quadra != ']') {
        // il valore di j aumenta di 1
        *j = *j + 1;
        // il puntatore punta al caratter successivo
        quadra++;
    }
}