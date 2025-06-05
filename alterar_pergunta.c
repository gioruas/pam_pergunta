#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pwd.h>
#include <sys/stat.h>

#define CONFIG_DIR ".pam_questions"
#define CONFIG_FILE "config"
#define MAX_LINE 128
#define MAX_ANSWER 128

void aparar(char *str) {
    size_t len = strlen(str);
    if (len > 0 && str[len - 1] == '\n') str[len - 1] = '\0';
}

void configurarCaminho(char *out_path, size_t size) {
    const char *home = getenv("HOME");
    snprintf(out_path, size, "%s/%s/%s", home, CONFIG_DIR, CONFIG_FILE);
}

int salvarArquivoPergunta(const char *filepath, const char *pergunta, const char *resposta) {
    FILE *file = fopen(filepath, "w");
    if (!file) return -1;

    fprintf(file, "pergunta=%s\nresposta=%s\n", pergunta, resposta);
    fclose(file);
    chmod(filepath, 0600);
    return 0;
}

void configurarDiretorio() {
    char caminho[512];
    snprintf(caminho, sizeof(caminho), "%s/%s", getenv("HOME"), CONFIG_DIR);
    mkdir(caminho, 0700);
}

int main() {
    configurarDiretorio();
    char pergunta[MAX_LINE], resposta[MAX_ANSWER];
    char filepath[512];

    configurarCaminho(filepath, sizeof(filepath));

    printf("Nova pergunta de segurança: ");
    if (!fgets(pergunta, sizeof(pergunta), stdin)) return 1;
    aparar(pergunta);

    printf("Nova resposta: ");
    if (!fgets(resposta, sizeof(resposta), stdin)) return 1;
    aparar(resposta);

    if (salvarArquivoPergunta(filepath, pergunta, resposta) != 0) {
        fprintf(stderr, "Erro ao salvar a nova pergunta.\n");
        return 1;
    }

    printf("Pergunta de segurança atualizada com sucesso.\n");
    return 0;
}

