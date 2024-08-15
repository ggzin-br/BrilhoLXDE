#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <math.h>

// Um programa de automação do Pedro - Livre para modificação e distribuição
/*
Objetivo: Automatizar o ajuste do brilho nos sistemas Linux e *nix compatíveis;
Entrada: Porcentagem do brilho total disponível no max_brightness
Saída: Modificação do brilho e retorno de 0
*/

char *leitura(FILE *fp) {

    /*Declaração de variáveis*/
    char *buf = malloc(sizeof(char));
    char *pont = buf;
    char letra;
    //
    int i = 0;

    /*Leitura de letra por letra*/
    do {
        // Realocamento de acordo com o a quantidade de loop
        buf = realloc(buf, (i+1)*sizeof(char));

        // Salvamento de letra por letra no ponteiro do *buf
        letra = fgetc(fp);
        pont[i] = letra; // pont[0] <- Retorna o *buf

        i++; // Isso é legal para o loop kkkkk
    } while (letra != EOF);

    return buf;
}

void troca_valor(double valor) {

    /* Declaração de variáveis */
    // Declaração dos arquivos do sistema
    FILE *arq_brilho = NULL;
    FILE *arq_brilhomax = NULL;
    // Declaração de valores importantes
    unsigned short int brilho;
    char *brilhomax;

    /* Abertura dos arquivos do sistema */
    arq_brilhomax = fopen("/sys/class/backlight/intel_backlight/max_brightness", "r");
    arq_brilho = fopen("/sys/class/backlight/intel_backlight/brightness", "r+");
    if (arq_brilhomax == NULL || arq_brilho == NULL) {
        perror("Erro nos arquivos"); return EXIT_FAILURE;
    }

    /* Execução do objetivo principal */
    brilhomax = leitura(arq_brilhomax);
    brilho = (unsigned short int) ( (valor/100) * atoi(brilhomax) );
    brilho = (brilho == 0) ? brilho += 1 : brilho; // Evita que a tela apague completamente

    rewind(arq_brilho);
    fprintf(arq_brilho, "%hu\n", brilho);

    /*Limpeza da memória*/
    free(brilhomax);
    //
    fcl:
    fclose(arq_brilho);
    fclose(arq_brilhomax);
    // Caso não seja fechado o FILE*, restos de memória serão deixados para trás

}

