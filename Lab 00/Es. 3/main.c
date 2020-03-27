#include <stdio.h>
#define MAXN 30
void ruota(int v[MAXN], int N, int P, int dir){
    int f, i;
    int copia[N];

    while(P != 0){
        for(int i=0; i<N; i++){
            copia[i] = v[i];
        }
        if(dir == 1) {
            for(i = 0; i < N; i++) {
                if(i == (N - 1))
                    v[i] = copia[0];
                else
                    v[i] = copia[i+1];
            }
        }
        else if(dir == -1){
            for(i=(N-1); i >= 0; i--){
                if(i == 0)
                    v[i] = copia[N-1];
                else
                    v[i] = copia[i-1];
            }
        }
        P--;
    }
}

int main() {
    int a[] = {1, 2, 3, 4, 5, 6};
    ruota(a, 6, 2, -1);
    return 0;
}