#include <stdio.h>
#include <string.h>

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
	struct Personagem {
		char nome[20];
		char info[3][50];
		char frase[3][50];
		char habilidade[30];
		int hpMax;
		int hp;
		int atk;
		int def;
		int cooldown;
	} heroi[5], vilao[5];

void main(){

	// definindo personagens
	strcpy(heroi[0].nome, "Superman");
	strcpy(heroi[0].habilidade, "visão de calor");
	heroi[0].hpMax = 200;
	heroi[0].hp = heroi[0].hpMax;
	heroi[0].atk = 20;
	heroi[0].def = 20;
	heroi[0].cooldown = 0;
	
	strcpy(heroi[1].nome, "Mulher-Maravilha");
	strcpy(heroi[1].habilidade, "laço da verdade");
	heroi[1].hpMax = 200;
	heroi[1].hp = heroi[1].hpMax;
	heroi[1].atk = 15;
	heroi[1].def = 20;
	heroi[1].cooldown = 0;
	
	strcpy(heroi[2].nome, "Batman");
	strcpy(heroi[2].habilidade, "armadura Hellbat");
	heroi[2].hpMax = 100;
	heroi[2].hp = heroi[2].hpMax;
	heroi[2].atk = 10;
	heroi[2].def = 10;
	heroi[2].cooldown = 0;
	
	strcpy(heroi[3].nome, "Flash");
	strcpy(heroi[3].habilidade, "soco de massa infinita");
	heroi[3].hpMax = 150;
	heroi[3].hp = heroi[3].hpMax;
	heroi[3].atk = 12;
	heroi[3].def = 12;
	heroi[3].cooldown = 0;
	
	strcpy(heroi[4].nome, "Aquaman");
	strcpy(heroi[4].habilidade, "Tridente de Netuno");
	heroi[4].hpMax = 150;
	heroi[4].hp = heroi[4].hpMax;
	heroi[4].atk = 12;
	heroi[4].def = 12;
	heroi[4].cooldown = 0;
	
	
	printf("%s\n", heroi[3].habilidade);
}
