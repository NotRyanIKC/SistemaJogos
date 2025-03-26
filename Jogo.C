#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
    int furia;
    int ativa;
} Gousma;

void exibirStatus(Gousma gousmas[], int totalGousmas) {
    for (int i = 0; i < totalGousmas; i++) {
        if (gousmas[i].ativa)
            printf("Gousma %d - Furia: %d\n", i + 1, gousmas[i].furia);
    }
}

void atacar(Gousma *atacante, Gousma *defensor) {
    if (!atacante->ativa) {
        printf("Esta Gousma nao pode atacar!\n");
        return;
    }
    defensor->furia += atacante->furia;
    atacante->furia = 0;
    atacante->ativa = 0;

    printf("A Gousma atacada agora tem %d de furia.\n", defensor->furia);
    if (defensor->furia > 5) {
        printf("A Gousma desintegrou devido a furia excessiva!\n");
        defensor->furia = 0;
        defensor->ativa = 0;
    }
}

void dividir(Gousma *gousma1, Gousma *gousma2) {
    if (!gousma1->ativa || gousma1->furia < 2) {
        printf("Nao ha furia suficiente para dividir!\n");
        return;
    }
    int transferencia = gousma1->furia / 2;
    gousma2->furia = transferencia;
    gousma2->ativa = 1;
    gousma1->furia -= transferencia;

    printf("Gousma 1 agora tem %d de furia e Gousma 2 tem %d de furia.\n", gousma1->furia, gousma2->furia);
}

int verificaDerrota(Gousma gousmas[]) {
    return !(gousmas[0].ativa || gousmas[1].ativa);
}

void jogoGousmas() {
    Gousma jogador1Gousmas[2] = {{1, 1}, {1, 1}};
    Gousma jogador2Gousmas[2] = {{1, 1}, {1, 1}};
    int turno = 1;

    while (1) {
        printf("\nTurno do jogador %d\n", turno);
        printf("Status das Gousmas:\n");
        exibirStatus(turno == 1 ? jogador1Gousmas : jogador2Gousmas, 2);
        
        char acao;
        printf("\nEscolha uma acao:\n");
        printf("a) Atacar\nb) Dividir uma Gousma\nc) Passar o turno\n");
        printf("Digite sua opcao: ");
        scanf(" %c", &acao);

        if (acao == 'a') {
            int atacando, atacado;
            printf("Escolha sua Gousma para atacar (1 ou 2): ");
            scanf("%d", &atacando);
            printf("Escolha a Gousma adversaria para atacar (1 ou 2): ");
            scanf("%d", &atacado);
            atacar(&jogador1Gousmas[atacando - 1], &jogador2Gousmas[atacado - 1]);
        } else if (acao == 'b') {
            int gousmaParaDividir;
            printf("Escolha a Gousma para dividir (1 ou 2): ");
            scanf("%d", &gousmaParaDividir);
            dividir(&jogador1Gousmas[gousmaParaDividir - 1], &jogador1Gousmas[1 - (gousmaParaDividir - 1)]);
        }
        
        if (verificaDerrota(jogador1Gousmas)) {
            printf("Jogador 2 venceu!\n");
            break;
        } else if (verificaDerrota(jogador2Gousmas)) {
            printf("Jogador 1 venceu!\n");
            break;
        }

        turno = (turno == 1) ? 2 : 1;
    }
}

void perguntaEResposta() {
    char *perguntas[5] = {
        "Qual a capital da Alemanha?\n1. Berlim\n2. Madrid\n3. Paris\n4. Roma",
        "Qual foi o Ano do inicio da Revolucao Francesa ?\n1. 1780\n2. 1789\n3. 1790\n4. 1785",
        "Quem escreveu 'Dom Quixote'?\n1. Shakespeare\n2. Cervantes\n3. Camoes\n4. Dante",
        "Qual e o maior planeta do sistema solar?\n1. Terra\n2. Marte\n3. Jupiter\n4. Saturno",
        "Quem pintou a Mona Lisa?\n1. Van Gogh\n2. Picasso\n3. Leonardo da Vinci\n4. Michelangelo"
    };
    int respostas[5] = {1, 2, 2, 3, 3};
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

int main() {
    int escolha;
    do {
        printf("\nMenu Principal\n");
        printf("1. Pergunta e Resposta\n");
        printf("2. Cobra na Caixa!\n");
        printf("3. GousmasWar\n");
        printf("4. Sair\n");
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
                jogoGousmas();
                break;
            case 4:
                printf("Saindo do jogo...\n");
                break;
            default:
                printf("Opcao inválida! Tente novamente.\n");
        }
    } while (escolha != 4);
    return 0;
}
