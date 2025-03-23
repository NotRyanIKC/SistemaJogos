#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void perguntaEResposta();
void cobraNaCaixa();

int main() {
    int escolha;
    do {
        printf("\nMenu Principal\n");
        printf("1. Pergunta e Resposta\n");
        printf("2. Cobra na Caixa!\n");
        printf("3. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &escolha);

        switch (escolha) {
            case 1:
                perguntaEResposta();
                break;
            case 2:
                cobraNaCaixa();
                break;
            case 3:
                printf("Saindo do jogo...\n");
                break;
            default:
                printf("Opcao invalida! Tente novamente.\n");
        }
    } while (escolha != 3);
    return 0;
}

void perguntaEResposta() {
    char *perguntas[5] = {
        "Qual a capital da Alemanha?\n1. Berlim\n2. Madrid\n3. Paris\n4. Roma",
        "Qual foi o Ano do inicio da Revolucao Francesa ?\n1. 1780\n2. 1789\n3. 1790\n4. 1785",
        "Quem escreveu 'Dom Quixote'?\n1. Shakespeare\n2. Cervantes\n3. Camoes\n4. Dante",
        "Qual e o maior planeta do sistema solar?\n1. Terra\n2. Marte\n3. Jupiter\n4. Saturno",
        "Quem pintou a Mona Lisa?\n1. Van Gogh\n2. Picasso\n3. Leonardo da Vinci\n4. Michelangelo"
    };
    int respostas[5] = {3, 2, 2, 3, 3};
    int respostaUsuario, i, pontuacao = 0;

    for (i = 0; i < 5; i++) {
        printf("\n%s\n", perguntas[i]);
        printf("Sua resposta: ");
        scanf("%d", &respostaUsuario);
        if (respostaUsuario == respostas[i]) {
            printf("Correto!\n");
            pontuacao++;
        } else {
            printf("Incorreto! A resposta correta era %d.\n", respostas[i]);
        }
    }
    printf("\nVoce acertou %d de 5 perguntas.\n", pontuacao);
}

void cobraNaCaixa() {
    srand(time(NULL));
    int jogadorIndex, cobra, botao, escolha, turno;
    char jogador1[20], jogador2[20];

    printf("Escolha um nome pra cada Jogador\n");
    printf("Jogador 1: ");
    scanf("%s", jogador1);
    printf("Jogador 2: ");
    scanf("%s", jogador2);

    jogadorIndex = rand() % 2;
    printf("%s comeca!\n", jogadorIndex == 0 ? jogador1 : jogador2);

    turno = jogadorIndex;
    do {
        cobra = rand() % 5 + 1;
        botao = rand() % 5 + 1;
        while (cobra == botao) {
            botao = rand() % 5 + 1;
        }

        printf("%s, escolha uma caixa (1-5): ", turno == 0 ? jogador1 : jogador2);
        scanf("%d", &escolha);

        if (escolha == cobra) {
            printf("%s encontrou a cobra! %s perdeu!\n", turno == 0 ? jogador1 : jogador2, turno == 0 ? jogador1 : jogador2);
            break;
        } else if (escolha == botao) {
            printf("%s encontrou o botao! %s venceu!\n", turno == 0 ? jogador1 : jogador2, turno == 0 ? jogador1 : jogador2);
            break;
        } else {
            printf("A caixa esta vazia! Proximo turno.\n");
            turno = 1 - turno;
        }
    } while (1);
}
