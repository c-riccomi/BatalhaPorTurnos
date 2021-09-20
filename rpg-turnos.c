#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>

// usar getch (biblioteca conio, c++?) ou getchar (biblioteca padrão)?

/*
    - batalha de turnos: heróis x vilões DC
    - heróis: superman, woderwoman, batman, flash, aquaman
    - vilões: lexluthor, coringa, arlequina, heravenenosa, pinguim
    - opções: ataque, defesa, habilidade especial (quando disponível pelo cooldown)

    
    HABILIDADES ESPECIAIS:

    superman -> visão de calor (intervalo de 3 golpes, inimigo perde 20% hp)
    wondewoman -> laço da verdade (intervalo de 4 golpes, inimigo perde 10% do ataque)
    flash -> soco de massa infinita (intervalo 5 golpes, inimigo perde 40% hp)
    batman -> armadura (dura intervalo de 3 golpes recebidos, aumenta defesa em 40%)
    aquaman -> tridente (intervalo de 3 golpes, inimigo perde 20% hp)

    coringa/arlequina -> faz civis de refém, explode edifícios
    lexluthor -> armas de última tecnologia, criptonita APENAS CONTRA SUPERMAN (intervalo de 8 golpes, superman perde 80% defesa)
    heravenenosa -> hipnose
    pinguim -> armadilhas 

*/

// estrutura dos atributos dos personagens
typedef struct {
	char nome[20];
	char info[3][50];
	char frase[3][50];
	char habilidade[30];
	int hpMax;
	int hp;
	int atk;
	int def;
	int cooldown;
} Personagem;


// layout do menu e possíveis erros
void layoutMenu(int erro) {
    // parâmetro erro: 0 = sem erro, 1 = opção inválida, 2 = tentou iniciar sem personagem
	system("cls");
	printf("*=============================================================*\n");
	printf("|                      BATALHA POR TURNOS                      \n");
	printf("|                     DC: Heróis vs. Vilões                    \n");
	printf("|                                                              \n");
	printf("|                                                              \n");
	printf("| (1) Selecionar personagem                                    \n");
	printf("| (2) Iniciar                                                  \n");
	printf("| (3) Créditos                                                 \n");
	printf("|                                                              \n");
	printf("|                                                              \n");
	printf("|                                                              \n");
	printf("|                                                              \n");
	printf("|                                                 (0) Sair     \n");
	printf("*=============================================================*\n");
	
	if (erro == 1) printf("\n Comando inválido!\n");
	if (erro == 2) printf("\n Por favor, escolha um personagem antes de iniciar o jogo!\n");
	printf("\n Digite uma das opções acima e pressione enter:  ");
}


// layout do menu, mensagem de erro e de confirmação do personagem
void layoutHeroi(Personagem heroi, int erro) {
    // parâmetro erro: 0 = sem erro, 1 = opção inválida, 2 = personagem é confirmado
    system("cls");
    printf("*=============================================================*\n");
    printf("|  Personagem: %s\n", heroi.nome);
    printf("|                                                              \n");
    printf("|  Vida: %d     Ataque: %d     Defesa: %d\n", heroi.hpMax, heroi.atk, heroi.def);
    printf("|                                                              \n");
    printf("|  Habilidade especial: %s\n", heroi.habilidade);
    printf("|                                                              \n");
    printf("|  %s\n", heroi.info[0]);
    printf("|  %s\n", heroi.info[1]);
    printf("|  %s\n", heroi.info[2]);
    printf("|------------------------------------------------------------- \n");
    printf("|              (1) Avançar        (3) Confirmar                \n");
    printf("|              (2) Voltar         (0) Menu                     \n");
    printf("*=============================================================*\n");

    if (erro == 0) printf("\n Digite uma das opções acima e pressione enter:  ");
    if (erro == 1) {
        printf("\n Por favor digite um comando válido!\n");
        printf("\n Digite uma das opções acima e pressione enter:  ");
    }
    if (erro == 2) {
        printf("\n Você escolheu o personagem: %s!\n", heroi.nome);
        printf("\n Pressione qualquer tecla para voltar para o menu.\n");
    }
}


// navega o catálogo de personagens
int escolherHeroi(Personagem heroi[]) {
    int voltaMenu = 0, navegando = 0, comando;
    
    do {
        scanf("%d", &comando);
    
        switch (comando) {
            // usuário escolhe voltar ao menu
            case 0:
                voltaMenu++;
                break;
                
            // usuário escolhe avançar para o próximo personagem
            case 1:
                navegando++;
                if (navegando > 4) navegando = 0;
                layoutHeroi(heroi[navegando], 0);
                break;
                
            // usuário escolhe voltar ao personagem anterior
            case 2:
                navegando--;
                if (navegando < 0) navegando = 4;
                layoutHeroi(heroi[navegando], 0);
                break;
            
            // usuário confirma personagem    
            case 3:
                layoutHeroi(heroi[navegando], 2);
                getch();
                voltaMenu++;
                return navegando;
                
            default:
                layoutHeroi(heroi[navegando], 1);
                break;
        }
    } while (voltaMenu == 0);

    //return (navegando); // É NECESSÁRIO????????
}


void main(){
    Personagem heroi[5];
    Personagem vilao[5];
    
	// definindo personagens
	strcpy(heroi[0].nome, "Superman");
	strcpy(heroi[0].info[0], "000");
	strcpy(heroi[0].info[1], "000");
	strcpy(heroi[0].info[2], "000");
	strcpy(heroi[0].habilidade, "visão de calor");
	heroi[0].hpMax = 200;
	heroi[0].hp = heroi[0].hpMax;
	heroi[0].atk = 20;
	heroi[0].def = 20;
	heroi[0].cooldown = 0;
	
	strcpy(heroi[1].nome, "Mulher-Maravilha");
	strcpy(heroi[1].info[0], "111");
	strcpy(heroi[1].info[1], "111");
	strcpy(heroi[1].info[2], "111");
	strcpy(heroi[1].habilidade, "laço da verdade");
	heroi[1].hpMax = 200;
	heroi[1].hp = heroi[1].hpMax;
	heroi[1].atk = 15;
	heroi[1].def = 20;
	heroi[1].cooldown = 0;
	
	strcpy(heroi[2].nome, "Batman");
	strcpy(heroi[2].info[0], "222");
	strcpy(heroi[2].info[1], "222");
	strcpy(heroi[2].info[2], "222");
	strcpy(heroi[2].habilidade, "armadura Hellbat");
	heroi[2].hpMax = 100;
	heroi[2].hp = heroi[2].hpMax;
	heroi[2].atk = 10;
	heroi[2].def = 10;
	heroi[2].cooldown = 0;
	
	strcpy(heroi[3].nome, "Flash");
	strcpy(heroi[3].info[0], "333");
	strcpy(heroi[3].info[1], "333");
	strcpy(heroi[3].info[2], "333");
	strcpy(heroi[3].habilidade, "soco de massa infinita");
	heroi[3].hpMax = 150;
	heroi[3].hp = heroi[3].hpMax;
	heroi[3].atk = 12;
	heroi[3].def = 12;
	heroi[3].cooldown = 0;
	
	strcpy(heroi[4].nome, "Aquaman");
    strcpy(heroi[4].info[0], "444");
	strcpy(heroi[4].info[1], "444");
	strcpy(heroi[4].info[2], "444");
	strcpy(heroi[4].habilidade, "Tridente de Netuno");
	heroi[4].hpMax = 150;
	heroi[4].hp = heroi[4].hpMax;
	heroi[4].atk = 12;
	heroi[4].def = 12;
	heroi[4].cooldown = 0;

	int sair = 0, verificaPersonagem = 0;
	int comando, heroiEscolhido;
	
	// início do programa
	layoutMenu(0);

	// loop principal do menu
	do {
	    scanf("%i", &comando);
	    
		switch (comando) {
			// usuario escolhe sair do programa
			case 0: 
		        sair++;
		        break;
			
			//usuario escolhe selecionar personagem
		    case 1: 
		        layoutHeroi(heroi[0], 0);
		        heroiEscolhido = escolherHeroi(heroi);
		        verificaPersonagem = 1;
		        layoutMenu(0);
		        break;

			//usuario escolhe iniciar a batalha
		    case 2: 
		       	printf("escolheu iniciar");
		       	break;

			// usuario escolhe ver os créditos
		    case 3:
		        printf("escolheu créditos");
		        break;

			// usuario escolhe um comando não existente
		    default:
		        layoutMenu(1);
		        break;
		}
	} while (sair == 0);
}
