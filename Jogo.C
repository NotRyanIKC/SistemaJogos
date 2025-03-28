#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_GOUSMAS 2
#define MAX_FURIA 5

typedef struct {
    int furia;
    bool ativa;
} Gousma;

void jogarNovamente(void (*jogo)()) {
    char resposta;
    do {
        printf("Deseja jogar novamente? (s/n): ");
        scanf(" %c", &resposta);
        if (resposta == 's' || resposta == 'S') {
            jogo();
        }
    } while (resposta == 's' || resposta == 'S');
}

typedef struct {
    Gousma gousmas[MAX_GOUSMAS];
} Jogador;

void iniciar_jogador(Jogador *jogador) {
    jogador->gousmas[0].furia = 1;
    jogador->gousmas[0].ativa = true;
    jogador->gousmas[1].furia = 1;
    jogador->gousmas[1].ativa = true;
}

void mostrar_status(Jogador *j1, Jogador *j2) {
    printf("\nStatus:\n");
    printf("Jogador 1: ");
    for (int i = 0; i < MAX_GOUSMAS; i++)
        if (j1->gousmas[i].ativa)
            printf("[G%d: %d] ", i + 1, j1->gousmas[i].furia);
    printf("\n");
    
    printf("Jogador 2: ");
    for (int i = 0; i < MAX_GOUSMAS; i++)
        if (j2->gousmas[i].ativa)
            printf("[G%d: %d] ", i + 1, j2->gousmas[i].furia);
    printf("\n\n");
}

bool atacar(Jogador *atacante, Jogador *defensor) {
    int g_atacante, g_defensor;
    printf("Escolha sua Gousma atacante (1 ou 2): ");
    scanf("%d", &g_atacante);
    printf("Escolha a Gousma inimiga a atacar (1 ou 2): ");
    scanf("%d", &g_defensor);
    
    g_atacante--, g_defensor--;
    if (!atacante->gousmas[g_atacante].ativa || !defensor->gousmas[g_defensor].ativa) {
        printf("Escolha invalida!\n");
        return false;
    }
    
    defensor->gousmas[g_defensor].furia += atacante->gousmas[g_atacante].furia;
    atacante->gousmas[g_atacante].furia = 1;
    
    if (defensor->gousmas[g_defensor].furia >= MAX_FURIA) {
        defensor->gousmas[g_defensor].ativa = false;
    }
    
    return true;
}

void dividirGousma(Jogador *jogador) {
    int g_origem;
    printf("Escolha a Gousma para dividir (1 ou 2): ");
    scanf("%d", &g_origem);
    g_origem--;
    
    if (!jogador->gousmas[g_origem].ativa || jogador->gousmas[g_origem].furia < 2) {
        printf("Divisao impossivel! A Gousma precisa ter pelo menos 2 de furia.\n");
        return;
    }
    
    int g_nova = -1;
    for (int i = 0; i < MAX_GOUSMAS; i++) {
        if (!jogador->gousmas[i].ativa) {
            g_nova = i;
            break;
        }
    }
    
    int furia_transferida;
    printf("Quantos pontos de furia deseja transferir? (1 ate %d): ", jogador->gousmas[g_origem].furia - 1);
    scanf("%d", &furia_transferida);
    
    if (furia_transferida < 1 || furia_transferida >= jogador->gousmas[g_origem].furia) {
        printf("Valor invalido para divisao!\n");
        return;
    }
    
    jogador->gousmas[g_nova].furia = furia_transferida;
    jogador->gousmas[g_nova].ativa = true; 
    jogador->gousmas[g_origem].furia -= furia_transferida; 
    
    printf("Gousma dividida com sucesso! Gousma %d tem %d de fúria, Gousma %d tem %d de fúria.\n", 
           g_origem + 1, jogador->gousmas[g_origem].furia, g_nova + 1, jogador->gousmas[g_nova].furia);
}

bool verificar_fim(Jogador *j1, Jogador *j2) {
    bool j1_vivo = j1->gousmas[0].ativa || j1->gousmas[1].ativa;
    bool j2_vivo = j2->gousmas[0].ativa || j2->gousmas[1].ativa;
    
    if (!j1_vivo) {
        printf("Jogador 2 venceu!\n");
        return true;
    }
    if (!j2_vivo) {
        printf("Jogador 1 venceu!\n");
        return true;
    }
    return false;
}

void iniciar_jogo() {
    Jogador jogador1, jogador2;
    iniciar_jogador(&jogador1);
    iniciar_jogador(&jogador2);
    
    int turno = 1;
    while (true) {
        mostrar_status(&jogador1, &jogador2);
        printf("Vez do Jogador %d. Escolha:\n1 - Atacar\n2 - Passar turno\n3 - Dividir Gousma\n", turno);
        int escolha;
        scanf("%d", &escolha);
        
        if (escolha == 1) {
            if (turno == 1) atacar(&jogador1, &jogador2);
            else atacar(&jogador2, &jogador1);
        } else if (escolha == 2) {
            printf("Turno passado!\n");
        } else if (escolha == 3) {
            if (turno == 1) dividirGousma(&jogador1);
            else dividirGousma(&jogador2);
        } else {
            printf("Opção invalida!\n");
            continue;
        }
        
        if (verificar_fim(&jogador1, &jogador2)) break;
        turno = 3 - turno;
    }
    
    printf("Fim do jogo!\n");
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
    jogarNovamente(perguntaEResposta);
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
    jogarNovamente(cobraNaCaixa);
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
                iniciar_jogo();
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
