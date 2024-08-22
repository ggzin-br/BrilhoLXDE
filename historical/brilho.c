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
    char **pont = &buf;
    //
    int i = 0;
    char letra;

    /*Leitura de letra por letra*/
    do {
        // Realocamento de acordo com o a quantidade de loop
        buf = realloc(buf, (i+1)*sizeof(char));

        // Salvamento de letra por letra no ponteiro do *buf
        letra = fgetc(fp);
        pont[0][i] = letra; // pont[0] <- Retorna o endereço do único espaço de memória apontado pelo *buf

        i++; // Isso é legal para o loop kkkkk
    } while (letra != EOF);

    return buf;
}

int main(int argc, char *argv[]) {

    /*Declaração de variáveis*/
    // Declaração dos arquivos do sistema
    FILE *arq_brilho, *arq_brilhomax;
    arq_brilhomax = fopen("/sys/class/backlight/intel_backlight/max_brightness", "r");
    arq_brilho = fopen("/sys/class/backlight/intel_backlight/brightness", "r+");
    // Declaração de valores importantes
    char *brilhomax;
    unsigned short int brilho;

    /*Verificação de erros diversos*/
    if (arq_brilhomax == NULL || arq_brilho == NULL) {
        perror("Erro nos arquivos");
        return EXIT_FAILURE;
    } else if (argc != 2) {
        printf("Sintaxe correta:\t%s +-(0-100)%s\n", argv[0], "%");
        goto fcl;
    }


    /*Execução do objetivo principal*/
    brilhomax = leitura(arq_brilhomax);

    brilho = sin(M_PI/2 * atoi(argv[1])/100) * atoi(brilhomax); // 90º * (100)=>1 -> 1
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

return EXIT_SUCCESS;
}
