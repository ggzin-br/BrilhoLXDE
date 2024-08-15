#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

// Um programa de automação do Pedro - Livre para modificação e distribuição
/*
Descrição:
Esta parte do código é chamado quando o main() detecta que o programa não está sendo rodado como root.

Método:
Executa o pkexec para elevar o programa por meio gráfico.
Usa o envp para descobrir o DISPLAY= e o XAUTHORITY
*/

void admin(char *env[], char *nome) {

    /* Declaração de variáveis */
    int i = 0, j = 0;
    int xauth, display;
    char ab_path[PATH_MAX];

    /* Obtenção dos índices do env */
    while (env[i] != NULL) { // Não consegui pensar em algo sem ser o if/elseif
        if (strncmp(env[i], "XAUTHORITY=", 11) == 0) {
            xauth = i;
        } else if (strncmp(env[i], "DISPLAY=", 8) == 0) {
            display = i;
        }
        i++;
    }

    /* Obtenção do caminho real do programa */ // -> Correção do bug de execução diretamente do terminal
    if (realpath(nome, ab_path) != NULL) {}
    else {
        perror("caminho absoluto");
    }

    /* Execução do comando */
    char *cmd[] = {"pkexec", "env", env[display], env[xauth], ab_path, NULL};

        execvp("pkexec", cmd);
        perror("pkexec"); // Caso der erro

}
