#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main(void){
    // int num, primo, posicao, nPrimos = 0, *primos, *potencia;
    int num, primo, nPrimos = 0;
    
    scanf("%d", &num);
    
    for(primo = 2; primo <= num; primo++){
        int i;
        for(i = 2; i < primo && primo % i != 0; i++);
        if (i == primo) nPrimos++;
    }
    /*
    primos = (int *)malloc(nPrimos * sizeof(int));
    potencia = (int *)malloc(nPrimos * sizeof(int));
    memset(primos, 0, nPrimos);
    memset(potencia, 0, nPrimos);
    */
    //int auxiliar1 = 0;
    for(primo = 2; primo <= num; primo++){
        //int check2 = 0;
        int auxiliar2;
        for(auxiliar2 = 0; num % primo == 0; num /= primo)//{
            //primos[auxiliar1] = primo;
            //num /= primo;
            auxiliar2++;
            //potencia[auxiliar1] = auxiliar2;
            //potencia[auxiliar1]++;
            //check2 = 1;
            //printf("%d  %d  %d\n", num, primos[auxiliar1], potencia[auxiliar1] );
        //}
        if (auxiliar2 > 0) //{
            //primos[auxiliar1] = primo;
            //auxiliar1++;
            printf("%d %d\n", primo, auxiliar2);
        //}
    }
    /*
    for (posicao = 0; posicao < auxiliar1; posicao++){
        printf("%d ", potencia[posicao]);
    }
    printf("\n");
    for (posicao = 0; posicao < auxiliar1; posicao++){
        printf("%d ", primos[posicao]);
    }
    */       

    return 0;
}  
