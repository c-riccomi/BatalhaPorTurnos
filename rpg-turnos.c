#include <stdio.h>
#include <string.h>
#include <stdlib.h>     // funções rand(), srand() e comunicação com o sistema operacional
#include <conio.h>      // função getch()
#include <time.h>       // função time()

/*  PRÓXIMOS PASSOS:
    funções faltando: atacar, curar, especial, tomarAcoes, vencedor
    finalizar função batalha
    implementar frases de ataque dos personagens
    
    OBSERVAÇÕES:
    após a batalha, entra direto no catálogo
*/

/*
    - batalha de turnos: heróis x vilões DC
    - heróis: superman, mulher maravilha, batman, flash, aquaman
    - vilões: lex luthor, coringa, arlequina, heravenenosa, flash reverso
    - opções: ataque, defesa, habilidade especial (quando disponível pelo cooldown)

    
    HABILIDADES ESPECIAIS:
    superman -> visão de calor (intervalo de 3 golpes, inimigo perde 20% hp)
    mulher maravilha -> laço da verdade (intervalo de 4 golpes, inimigo perde 30% do ataque)
    flash -> soco de massa infinita (intervalo 5 golpes, inimigo perde 40% hp)
    batman -> armadura (dura intervalo de 3 golpes recebidos, aumenta defesa em 40%)
    aquaman -> tridente (intervalo de 3 golpes, inimigo perde 20% hp)
*/


// estrutura dos atributos dos personagens
typedef struct {
	char nome[20];
	char info[3][50];
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
        printf("\n Pressione qualquer tecla para voltar ao menu.\n");
    }
}


// layout dos créditos
void layoutCreditos() {
    system("cls");
    printf("*=============================================================*\n");
    printf("|                                                              \n");
    printf("|       Este programa foi originalmente criado por mim,        \n");
    printf("|                       CAROLINA RICCOMI,                      \n");
    printf("|     e outros quatro colegas de classe para a disciplina      \n");
    printf("|    de Programação Estruturada da graduação em Ciência da     \n");
    printf("|                  Computação em março de 2021.                \n");
    printf("|                                                              \n");
    printf("|    Várias alterações foram realizadas posteriormente para    \n");
    printf("|                     chegar a essa versão.                    \n");
    printf("|                                                              \n");
    printf("|                                                              \n");
    printf("|                                                              \n");
    printf("|        (Pressione qualquer tecla para voltar ao menu)        \n");
    printf("*=============================================================*\n");
}
    

// layout que apresenta a próxima batalha
void layoutInicioBatalha(Personagem *player, Personagem *bot) {
    system("cls");
    printf("*=============================================================*\n");
    printf("|                      PRÓXIMA BATALHA:                        \n");
    printf("|                                                              \n");
    printf("|                                                              \n");
    printf("|    Herói: %s\n", player->nome);
    printf("|    Vida: %d     Ataque: %d     Defesa: %d\n", player->hpMax, player->atk, player->def);
    printf("|    Habilidade especial: %s\n", player->habilidade);
    printf("|                                                              \n");
    printf("|                           VS                                 \n");
    printf("|                                                              \n");
    printf("|    Vilão: %s\n", bot->nome);
    printf("|    Vida: %d     Ataque: %d     Defesa: %d\n", bot->hpMax, bot->atk, bot->def);
    printf("|    Habilidade especial: %s\n", bot->habilidade);
    printf("*=============================================================*\n");
    getch();
}


// layout que mostra o player e bot durante a batalha
void layoutBatalha(Personagem *player, Personagem *bot, int cont, int limite, char *habilidadeAgr) {
    system("cls");
    printf("*=============================================================*\n");
    printf("|                       Turno: %d/%d\n", cont, limite);
    printf("|                                                              \n");
    printf("|                                                              \n");
    printf("|                                     %s: (%d/%d)\n", bot->nome, bot->hp, bot->hpMax);
    printf("|                                                              \n");
    printf("|                                                              \n");
    printf("|                                                              \n");
    printf("|  %s: (%d/%d)\n", player->nome, player->hp, player->hpMax);
    printf("|                                                              \n");
    printf("|--------------------------------------------------------------\n");
    printf("|     (1) Atacar     (2) Curar     (3) %s\n", player->habilidade);
    printf("|                                      %s\n", habilidadeAgr);
    printf("*=============================================================*\n");
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
}


// define o vilão gerando um número aleatório de 0 a 4
int gerarVilao() {
    srand(time(NULL));
    return (rand() % 4);
}


// obtém a ação do player no turno atual
int obterAcaoPlayer(Personagem *player, int *acaoValida) {
    // parâmetro acaoValida: é 1 quando uma das opções disponíveis é escolhida
    int acao;
    scanf("%i", &acao);
    
    if (acao < 1 || acao > 4) {
        printf("\nPor favor, escolha uma ação válida!\n");
        getch();
    } else if (acao == 3 && player->cooldown > 0){
  	    printf("\nA habilidade especial não está disponivel!\nra estar disponivel novamente.\n");
  	    printf("\nFaltam %d turnos para estar disponivel novamente.\n", player->cooldown);
  	    printf("\nPor favor, escolha uma ação válida!\n");
  	    getch();
    } else {
        *acaoValida = 1;
    }

    return acao;
}


// gera uma ação para o bot no turno atual
int gerarAcaoBot(Personagem *bot) {
    // caso em que a habilidade especial não está disponivel    
    if (bot->cooldown > 0){
  	    srand(time(NULL));
		return (rand() % 2) + 1;   
    } else {
        srand(time(NULL));
		return (rand() % 3) + 1; 
    }
}


void main(){
    Personagem heroi[5];
    Personagem vilao[5];
    
	// definindo heróis
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
	heroi[2].hpMax = 120;
	heroi[2].hp = heroi[2].hpMax;
	heroi[2].atk = 11;
	heroi[2].def = 10;
	heroi[2].cooldown = 0;
	
	strcpy(heroi[3].nome, "Flash");
	strcpy(heroi[3].info[0], "333");
	strcpy(heroi[3].info[1], "333");
	strcpy(heroi[3].info[2], "333");
	strcpy(heroi[3].habilidade, "soco de massa infinita");
	heroi[3].hpMax = 150;
	heroi[3].hp = heroi[3].hpMax;
	heroi[3].atk = 13;
	heroi[3].def = 12;
	heroi[3].cooldown = 0;
	
	strcpy(heroi[4].nome, "Aquaman");
    strcpy(heroi[4].info[0], "444");
	strcpy(heroi[4].info[1], "444");
	strcpy(heroi[4].info[2], "444");
	strcpy(heroi[4].habilidade, "Tridente de Netuno");
	heroi[4].hpMax = 150;
	heroi[4].hp = heroi[4].hpMax;
	heroi[4].atk = 15;
	heroi[4].def = 12;
	heroi[4].cooldown = 0;
	
	
	// definindo vilões
	strcpy(vilao[0].nome, "Lex Luthor");
	strcpy(vilao[0].info[0], "aaa");
	strcpy(vilao[0].info[1], "aaa");
	strcpy(vilao[0].info[2], "aaa");
	strcpy(vilao[0].habilidade, "armas de última tecnologia");
	vilao[0].hpMax = 110;
	vilao[0].hp = vilao[0].hpMax;
	vilao[0].atk = 15;
	vilao[0].def = 12;
	vilao[0].cooldown = 0;
	
	strcpy(vilao[1].nome, "Arlequina");
	strcpy(vilao[1].info[0], "bbb");
	strcpy(vilao[1].info[1], "bbb");
	strcpy(vilao[1].info[2], "bbb");
	strcpy(vilao[1].habilidade, "acrobacias e inteligência");
	vilao[1].hpMax = 120;
	vilao[1].hp = vilao[1].hpMax;
	vilao[1].atk = 18;
	vilao[1].def = 10;
	vilao[1].cooldown = 0;
	
	strcpy(vilao[2].nome, "Coringa");
	strcpy(vilao[2].info[0], "ccc");
	strcpy(vilao[2].info[1], "ccc");
	strcpy(vilao[2].info[2], "ccc");
	strcpy(vilao[2].habilidade, "imprevisibilidade e loucura");
	vilao[2].hpMax = 125;
	vilao[2].hp = vilao[2].hpMax;
	vilao[2].atk = 19;
	vilao[2].def = 15;
	vilao[2].cooldown = 0;
	
	strcpy(vilao[3].nome, "Hera Venenosa");
	strcpy(vilao[3].info[0], "ddd");
	strcpy(vilao[3].info[1], "ddd");
	strcpy(vilao[3].info[2], "ddd");
	strcpy(vilao[3].habilidade, "hipnose");
	vilao[3].hpMax = 160;
	vilao[3].hp = vilao[3].hpMax;
	vilao[3].atk = 20;
	vilao[3].def = 13;
	vilao[3].cooldown = 0;
	
	strcpy(vilao[4].nome, "Flash Reverso");
    strcpy(vilao[4].info[0], "eee");
	strcpy(vilao[4].info[1], "eee");
	strcpy(vilao[4].info[2], "eee");
	strcpy(vilao[4].habilidade, "manipulação temporal");
	vilao[4].hpMax = 150;
	vilao[4].hp = vilao[4].hpMax;
	vilao[4].atk = 19;
	vilao[4].def = 16;
	vilao[4].cooldown = 0;

	int sair = 0, verificaPersonagem = 0;
	int comando, heroiEscolhido;
	
	// início do programa
	layoutMenu(0);

	// loop principal do menu
	do {
	    scanf("%i", &comando);
	    
		switch (comando) {
			// usuário escolhe sair do programa
			case 0: 
		        sair++;
		        break;
			
			// usuário escolhe selecionar personagem
		    case 1: 
		        layoutHeroi(heroi[0], 0);
		        heroiEscolhido = escolherHeroi(heroi);
		        verificaPersonagem = 1;
		        layoutMenu(0);
		        break;

			// usuário escolhe iniciar a batalha
		    case 2: 
		        if (verificaPersonagem = 0) layoutMenu(2);
		        else{
		            // cria os dois jogadores e dá início à batalha
		            Personagem player = heroi[heroiEscolhido];
		            int defineVilao = gerarVilao();
		            Personagem bot = vilao[defineVilao];
		            batalha(&player, &bot);
		        }
		       	break;

			// usuário escolhe ver os créditos
		    case 3:
		        layoutCreditos();
		        getch();
		        layoutMenu(0);
		        break;

			// usuário escolhe um comando não existente
		    default:
		        layoutMenu(1);
		        break;
		}
	} while (sair == 0);
}


void batalha(Personagem *player, Personagem *bot) {
    layoutInicioBatalha(player, bot);
    
    int turno = 0, turnoLimite = 20;
    
    while (player->hp > 0 && bot->hp > 0 && turno < turnoLimite) {
        turno++;
        int acaoPlayer = 0, acaoValida = 0, acaoBot = 0;
        
        char habilidadeAgr[15] = "(disponível)";
        if (player->cooldown > 0) {
            for (int i = 12; i > 0; i--) {
	            habilidadeAgr[i+2] = habilidadeAgr[i];
	        }
	        habilidadeAgr[1] = 'i';
	        habilidadeAgr[2] = 'n';
        }
        
        while (acaoValida == 0) {
            layoutBatalha(player, bot, turno, turnoLimite, habilidadeAgr);
            acaoPlayer = obterAcaoPlayer(player, &acaoValida);
        }
        
        acaoBot = gerarAcaoBot(bot);
        printf("\n acao player: %i, acao bot: %i \n", acaoPlayer, acaoBot);    
    }
}
