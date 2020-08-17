#include<stdio.h>
#include<stdlib.h>
#define MAX 100 //Define o tamanho máximo do nome/caminho do arquivo e de caracteres (por linha) que serão lidos na importação

void imprime_tela_cabecalho()
{
    limpa_tela();
    printf("\n");
    printf(" ###############################################################################\n");
    printf(" #                                                                             #\n");
    printf(" #                                PESQUISA E ORDENAÇÃO                         #\n", 128);
    printf(" #                                      ÁRVORE AVL                             #\n")
    printf(" #                                                                             #\n");
    printf(" ###############################################################################\n\n");
}

typedef struct No
{
    int Id; //Valor que é informado para o nó
    struct No *Esquerda; //Ligação com outro nó(valor) pela esquerda
    struct No *Direita; //Ligação com outro nó(valor) pela direita
    int Altura; //Altura do Nó
} No;

/* Função que retorna o fator de balanceamento do nó */
int Balanceamento(No *Raiz)
{
    if (Raiz == NULL)
    return 0;
    return Altura(Raiz-> Esquerda) - Altura(Raiz-> Direita);
}

/* Função que retorna o maior valor entre dois inteiros (Utilizado pelas rotações */
int Maior(int a, int b);

/* Função que retorna o maior valor entre dois inteiros (Utilizado pelas rotações */
int Maior(int a, int b)
{
    return (a > b)? a : b;
}

/* Função para a rotação da sub-árvore (à direita) */
No *RotDir(No *Raiz)
{
    No *AuxiliarEsquerda = Raiz-> Esquerda;
    No *AuxiliarDireita = AuxiliarEsquerda-> Direita;
 
    // Realizando rotação
    AuxiliarEsquerda-> Direita = Raiz;
    Raiz-> Esquerda = AuxiliarDireita;
 
    // Atualizando alturas
    Raiz-> Altura = Maior(Altura(Raiz-> Esquerda), Altura(Raiz-> Direita))+1;
    AuxiliarEsquerda-> Altura = Maior(Altura(AuxiliarEsquerda-> Esquerda), Altura(AuxiliarEsquerda-> Direita))+1;
 
    // Retornando a nova raiz (Raiz alterada)
    return AuxiliarEsquerda;
}
 
/* Função para a rotação da sub-árvore (à esquerda) */
No *RotEsq(No *Raiz)
{
    No *AuxiliarDireita = Raiz-> Direita;
    No *AuxiliarEsquerda = AuxiliarDireita-> Esquerda;
 
    // Realizando rotação
    AuxiliarDireita-> Esquerda = Raiz;
    Raiz-> Direita = AuxiliarEsquerda;
 
    // Atualizando alturas
    Raiz->Altura = Maior(Altura(Raiz-> Esquerda), Altura(Raiz-> Direita))+1;
    AuxiliarDireita->Altura = Maior(Altura(AuxiliarDireita-> Esquerda), Altura(AuxiliarDireita-> Direita))+1;
 
    // Retornando a nova raiz (Raiz alterada)
    return AuxiliarDireita;
}

/* Função para verificar se o ponteiro Raiz do tipo No (registro) é nulo */
int IsNull(No *Raiz) //Podia ser feito sem ela, mas dava mais trabalho pra fazer toda vez que fosse preciso verificar isso
{
	return (Raiz == (No*)NULL); //Sempre retorna nulo se for
}

/* Função que verifica e imprime na tela a altura da árvore ou do nó */
int Altura(No *Raiz)
{
    if (Raiz == NULL) //Se raiz for nulo
        return -1; //retorna 0
    return Raiz-> Altura; //Senão usa recursividade
}

/* Função auxiliar que aloca um novo nó para a chava informada - Chamada pela função AdicionarNo */
No* NovoNo(int Id)
{
    No* Raiz = (No*)malloc(sizeof(No)); //Aloca espaço na memória para o registro
    Raiz-> Id = Id; //Id de Raiz recebe a chave informada pelo usuário
    Raiz-> Esquerda = NULL; // Como o nó é novo -> Esquerda e -> Direita apontam para nulo
    Raiz-> Direita = NULL;
    Raiz-> Altura = 0;  // O novo nó inserido é inicialmente uma folha portanto sua altura é 1
    return(Raiz); //Retorna a Raiz
}

/* Função que insere um novo Nó - Utiliza a função auxiliar NovoNo */
No* AdicionarNo(No *Raiz, int Id)
{
    /* Passo 1 - Executa a inserção normal */
    if(Raiz == NULL) //Se a Raiz é nula(Vazia)
    {
        return(NovoNo(Id)); //Chama a função auxiliar que insere a chave informada pelo usuário
    }
else
    if(Raiz != NULL) //Se a Raiz não for nula(Vazia)
    {
        if(Id < Raiz-> Id) //Verifica se a chave informada pelo usuário é menor que a chave da Raiz
        {
            Raiz-> Esquerda  = AdicionarNo(Raiz-> Esquerda, Id); //se for menor, chama novamente a função(recursividade), fazendo a última chave(esquerda) apontar para a nova chave
        }
     //Senão (veja linha abaixo)
        if(Id > Raiz-> Id) //Verifica se a chave informada pelo usuário é maior que a chave da Raiz
        {
            Raiz-> Direita = AdicionarNo(Raiz-> Direita, Id); //senão for menor, é maior e chama novamente a função(recursividade), fazendo a última chave(direita) apontar para a nova chave
        }
 
        /* Passo 2 - Atualiza a altura do novo nó (em relação ao anterior) */
        Raiz-> Altura = Maior(Altura(Raiz-> Esquerda), Altura(Raiz-> Direita)) + 1;
 
        /* Passo 3 - Declarada uma váriável inteira que tem por objetivo obter o fator de balanceamento deste nó em relação ao anterior(pai) para saber se a arvore ficou desbalanceada*/
        int fb = Balanceamento(Raiz); //Verifica o fator de balanceamento
 
        //Se o novo nó causou desbalanceamento da árvore, será necessário obter o balanceamento por meio de uma das 4 formas (dependendo do caso)

        //Rotação simples à esquerda
        if (fb > 1 && Id < Raiz-> Esquerda-> Id) //Se o fator de balanceamento da Raiz for maior que 1 e o Id informado pelo usuário for menor que o Id que está na Raiz -> Esquerda
            return RotDir(Raiz); //Retorna a Raiz, depois de aplicada a Rotação à Direita(Função)
 
        //Rotação simples à direita
        if (fb < -1 && Id > Raiz-> Direita-> Id)
            return RotEsq(Raiz);
 
        //Rotação dupla à esquerda
        if (fb > 1 && Id > Raiz-> Esquerda-> Id)
        {
            Raiz-> Esquerda =  RotEsq(Raiz-> Esquerda);
            return RotDir(Raiz);
        }
 
        //Rotação dupla à direita
        if (fb < -1 && Id < Raiz-> Direita-> Id)
        {
            Raiz-> Direita = RotDir(Raiz-> Direita);
            return RotEsq(Raiz);
        } //Fim das rotações
 
        /* Passo 4 - Retorna a nova Raiz(alterada) */
        return Raiz;
    }
}

/* Função para buscar um nó e saber se um valor existe na árvore */
No* BuscarNo(No *Raiz, int Id)
{
    if (Raiz == (No*) NULL) //Se Raiz for igual a nulo
        return NULL; //Retorna Nulo
    
    if (Raiz-> Id == Id) //Se Id de Raiz for igual a Id passado por parâmetro
        return Raiz; //Retorna a própria Raiz pois não há nada a ser feito pois o valor já existe na árvore e não vamos duplicar esse bagulho, he he, tô gostando dessa parada Brendon
    
    if (Id > Raiz-> Id) //Se Id(parâmetro) for maior que Id de Raiz
        return BuscarNo(Raiz-> Direita, Id); //Chama novamente a função (recursividade) para iserir o valor a direita
    else if (Id < Raiz-> Id) //Caso não seja Maior, então é menor e
        return BuscarNo(Raiz-> Esquerda, Id); //chama novamente a função para inserir a esquerda informando os novos parâmetros
}

/* Procedimento para exibir (imprimir) os valores na ordem em que foram inseridos aplicando recursividade */
void PreOrdem(No *NoAtual)
{
    if(NoAtual == (No*) NULL) //Se o ponteiro NoAtual do Tipo No(registro) for nulo
        return; //Retorna Nulo
  //Senão
    printf("%d ", NoAtual->Id ); //Imprime um inteiro Id de Atual
    PreOrdem(NoAtual-> Esquerda); //E chama novamente a função para imprimir esquerda caso não seja nulo
    PreOrdem(NoAtual-> Direita); //E a direita caso não seja nulo
}

/* Procedimento para exibir (imprimir) os valores na ordem (maior e menor ao lado do valor) em que foram inseridos aplicando recursividade */
void PosOrdem(No *NoAtual)
{
    if (NoAtual == (No*) NULL) //Se o ponteiro passado como parâmentro for nulo
        return; //Retorna nulo
  //Senão
    PosOrdem(NoAtual-> Esquerda); //Chama novamente a função apontando para a esquerda
    PosOrdem(NoAtual-> Direita); //E depois para a direita
    printf("%d ", NoAtual->Id ); //imprimindo o valor
}

/* Procedimento para exibir (imprimir) os valores na ordem em que foram inseridos (tipo pré-ordem) aplicando recursividade */
void EmOrdem(No *NoAtual) //Varredura e-r-d (= inorder traversal = percurso em in-ordem) Ordem Raiz-Esquerda_Direita.
{
    if (NoAtual == (No*) NULL) //Se o ponteiro NoAtual do tipo No(registro) for nulo
        return; //Retorna nulo
  //Senão  
    EmOrdem(NoAtual-> Esquerda); //Senão chama novamente a função indo para a esquerda
    printf("%d ", NoAtual->Id ); //Imprimindo o Id
    EmOrdem(NoAtual-> Direita); //E depois chamando novamente a função indo para a direita
}

/* Procedimento para exibir (imprimir) os valores na ordem em que foram inseridos (tipo pós-ordem) aplicando recursividade */
void EmOrdemInversa(No *NoAtual)
{
    if (NoAtual == (No*) NULL) //Se NoAtual é nulo
        return; //Retorna nulo
  //Senão
    EmOrdemInversa(NoAtual-> Direita); //Chama novamente a função indo para a direita
    printf("%d ", NoAtual->Id ); //Imprimindo o Id
    EmOrdemInversa(NoAtual-> Esquerda); //E chama novamente a função indo para a esquerda
}

/* Função auxiliar(será utilizada pela função RemoverNo) que retorna o menor valor(Id, ou chave) encontrado na árvore */
No* MenorId(No *Raiz)
{
    No *Atual = Raiz; //Variável Auxiliar do tipo No(registro) é igual a Raiz
 
    /* Repetição(Laço) para baixo até encontrar a folha mais a esquerda(Menor valor) (A árvore já está balanceada aqui)*/
    while (Atual-> Esquerda != NULL) //Enquanto esquerda de Atual não for Nulo
        Atual = Atual-> Esquerda; //Atual recebe (é igual) a Atual -> Esquerda (desce um nível na árvore)
 
    return Atual; //retorna Atual
}

/* Função para remover o nó da árvore sem ponteiro para ponteiro */
No* RemoverNo(No *Raiz, int Id)
{
    /* Passo 1 - Executa a remoção normal */
    if (Raiz == NULL)
        return Raiz;

    if ( Id < Raiz->Id ) //Verifica se a chave informada pelo usuário é menor que a chave da Raiz
        Raiz->Esquerda = RemoverNo(Raiz->Esquerda, Id); //se for menor, chama novamente a função(recursividade), fazendo a última chave(esquerda) apontar para a nova chave

else //Senão (veja linha abaixo)

    if( Id > Raiz->Id ) //Verifica se a chave informada pelo usuário é maior que a chave da Raiz
        Raiz->Direita = RemoverNo(Raiz->Direita, Id); //senão for menor, é maior e chama novamente a função(recursividade), fazendo a última chave(direita) apontar para a nova chave
 
    else //Se não é nenhum dos casos acima (maior ou menor), então é igual e este será o nó a ser removido
    {
        if( (Raiz->Esquerda == NULL) || (Raiz->Direita == NULL) ) //Verifica se o nó tem pelo menos 1 filho (folha)
        {
            No *Temp = Raiz->Esquerda ? Raiz->Esquerda : Raiz->Direita;
 
            if(Temp == NULL) //Casos de não ter filho
            {
                Temp = Raiz;
                Raiz = NULL;
            }
            else //Senão, caso tenha 1 filho
             *Raiz = *Temp; //Copia o conteúdo do filho não vazi para a Raiz
 
            free(Temp); //Libera o registro (nó) temporário
        }
        else
        {
            //Caso o nó tenha 2 filhos, obter o menor Id da sub-árvore direita (poderia ser o maior da sub-árvore esquerda).
            No *Temp = MenorId(Raiz->Direita);
 
            //Copia o valor de Id de Temp para a Raiz
            Raiz->Id = Temp->Id;
 
            //E a direita de raiz passará a apontar para o resultado da função RemoverNo passando como parâmetros a direita de Raiz e o Id de Temp
            Raiz->Direita = RemoverNo(Raiz->Direita, Temp->Id);
        }
    }

    if (Raiz == NULL) //Se a árvore for nula
      return Raiz; //Retorna ela própria
 
    /* Passo 2 - Atualiza a altura do novo nó (em relação ao anterior) */
    Raiz->Altura = Maior(Altura(Raiz->Esquerda), Altura(Raiz->Direita)) + 1;
 
    /* Passo 3 - Declarada uma váriável inteira que tem por objetivo obter o fator de balanceamento deste nó em relação ao anterior(pai) para saber se a arvore ficou desbalanceada*/
    int fb = Balanceamento(Raiz);
 
    //Se o novo nó causou desbalanceamento da árvore, será necessário obter o balanceamento por meio de uma das 4 formas (dependendo do caso)
 
    //Rotação simples à esquerda
    if (fb > 1 && Balanceamento(Raiz->Esquerda) >= 0)
        return RotDir(Raiz);
 
    //Rotação dupla à esquerda
    if (fb > 1 && Balanceamento(Raiz->Esquerda) < 0)
    {
        Raiz->Esquerda =  RotEsq(Raiz->Esquerda);
        return RotDir(Raiz);
    }
 
    //Rotação simples à direita
    if (fb < -1 && Balanceamento(Raiz->Direita) <= 0)
        return RotEsq(Raiz);
 
    //Rotação dupla à direita
    if (fb < -1 && Balanceamento(Raiz->Direita) > 0)
    {
        Raiz->Direita = RotDir(Raiz->Direita);
        return RotEsq(Raiz);
    }
 
    return Raiz;
}

/* Procedimento para remoção da árvore completa utilizando ponteiro para ponteiro*/
No* RemoverAVL(No *Raiz)
{
    if(Raiz != NULL)
    {
    	No *Menor = MenorId(Raiz);
    	Raiz = RemoverNo(Raiz, Menor->Id);
    	Raiz = RemoverAVL(Raiz);
    }
else
	free(Raiz);
    return NULL;
}
/* Fim do código das funções e procedimentos do menu */

/* Início do código das funções de importação e exportação */
/* Cria o arquivo que conterá os dados exportados PreOrdem */
GravaPreOrdem(No *Raiz)
{
    char Exporta;
    printf("\n\n   Deseja exportar estes dados? [s=Sim / Qualquer tecla = N%co]: ", 198);
    Exporta = getch(Exporta);
    Exporta = tolower(Exporta);

    if(Exporta == 's')
    {
    	char NomeArq[] = "preordem.txt";
    
    	FILE *Arq = fopen (NomeArq, "w"); //abre o arquivo para escrita, e devolve o endereco em memoria para Arq
    	
        ExportaPreOrdem(Raiz, Arq); //Chama a função recursiva que irá inserir os dados no arquivo
        
        fclose(Arq); //Fecha o arquivo
        
		printf("\n\n                       Exporta%c%co realizada com sucesso!\n", 135, 198); //Mensagem de confirmação da exportação
        printf("           (Um arquivo preordem.txt foi gerado na pasta do aplicativo)\n\n\n   "); //Nome do arquivo gerado
    }
else
	if(Exporta != 's')
	{
		printf("\n\n\n\n\n\n   ");
	}
}

/* Cria o arquivo que conterá os dados exportados PosOrdem */
GravaPosOrdem(No *Raiz)
{
    char Exporta;
    printf("\n\n   Deseja exportar estes dados? [s=Sim / Qualquer tecla = N%co]: ", 198);
    Exporta = getch(Exporta);
    Exporta = tolower(Exporta);

    if(Exporta == 's')
    {
        char NomeArq[] = "posordem.txt";
    
	    FILE *Arq = fopen (NomeArq, "w"); //abre o arquivo para escrita, e devolve o endereco em memoria para Arq

        ExportaPosOrdem(Raiz, Arq); //Chama a função recursiva que irá inserir os dados no arquivo

		fclose(Arq); //Fecha o arquivo
        
    	printf("\n\n                       Exporta%c%co realizada com sucesso!\n", 135, 198); //Mensagem de confirmação da exportação
    	printf("           (Um arquivo posordem.txt foi gerado na pasta do aplicativo)\n\n\n   "); //Nome do arquivo gerado
    }
else
	if(Exporta != 's')
	{
		printf("\n\n\n\n\n\n   ");
	}
}

/* Cria o arquivo que conterá os dados exportados EmOrdem */
GravaEmOrdem(No *Raiz)
{
    char Exporta;
    printf("\n\n   Deseja exportar estes dados? [s=Sim / Qualquer tecla = N%co]: ", 198);
    Exporta = getch(Exporta);
    Exporta = tolower(Exporta);

    if(Exporta == 's')
    {
    	char NomeArq[] = "emordem.txt";
    
    	FILE *Arq = fopen (NomeArq, "w"); //abre o arquivo para escrita, e devolve o endereco em memoria para Arq
    	
        ExportaEmOrdem(Raiz, Arq); //Chama a função recursiva que irá inserir os dados no arquivo
        
        fclose(Arq); //Fecha o arquivo
        
		printf("\n\n                       Exporta%c%co realizada com sucesso!\n", 135, 198); //Mensagem de confirmação da exportação
    	printf("           (Um arquivo emordem.txt foi gerado na pasta do aplicativo)\n\n\n   "); //Nome do arquivo gerado
    }
else
	if(Exporta != 's')
	{
		printf("\n\n\n\n\n\n   ");
	}
}

/* Cria o arquivo que conterá os dados exportados em EmOrdemInversa */
GravaEmOrdemInversa(No *Raiz)
{
    char Exporta;
    printf("\n\n   Deseja exportar estes dados? [s=Sim / Qualquer tecla = N%co]: ", 198);
    Exporta = getch(Exporta);
    Exporta = tolower(Exporta);

    if(Exporta == 's')
    {
    	char NomeArq[] = "emordeminversa.txt";
    
    	FILE *Arq = fopen (NomeArq, "w"); //abre o arquivo para escrita, e devolve o endereco em memoria para Arq

        ExportaEmOrdemInversa(Raiz, Arq); //Chama a função recursiva que irá inserir os dados no arquivo
        
        fclose(Arq); //Fecha o arquivo
        
    	printf("\n\n                       Exporta%c%co realizada com sucesso!\n", 135, 198); //Mensagem de confirmação da exportação
    	printf("           (Um arquivo emordeminversa.txt foi gerado na pasta do aplicativo)\n\n\n   "); //Nome do arquivo gerado
    }
else
	if(Exporta != 's')
	{
		printf("\n\n\n\n\n\n   ");
	}
}

/* Procedimento para exportar os valores na ordem em que foram inseridos aplicando recursividade */
ExportaPreOrdem(No *Raiz, FILE *Arq)
{    
    if(Raiz != (No*) NULL) //Se o ponteiro Raiz do Tipo No(registro) for nulo
    {
        fprintf(Arq, "%d", Raiz->Id ); //Imprime um inteiro Id de Atual
        fprintf(Arq,"\n"); //Quebra de linha (Enter)
        ExportaPreOrdem(Raiz-> Esquerda, Arq); //E chama novamente a função para imprimir esquerda caso não seja nulo
        ExportaPreOrdem(Raiz-> Direita, Arq); //E a direita caso não seja nulo
    }
}

/* Procedimento para exportar os valores na ordem (maior e menor ao lado do valor) em que foram inseridos aplicando recursividade */
ExportaPosOrdem(No *Raiz, FILE *Arq)
{    
    if (Raiz != (No*) NULL) //Se o ponteiro passado como parâmentro for nulo
    {
        ExportaPosOrdem(Raiz-> Esquerda, Arq); //Chama novamente a função apontando para a esquerda
        ExportaPosOrdem(Raiz-> Direita, Arq); //E depois para a direita
        fprintf(Arq, "%d ", Raiz->Id ); //imprimindo o valor
        fprintf(Arq,"\n"); //Tabulação
    }
}

/* Procedimento para exportar os valores na ordem em que foram inseridos (tipo pré-ordem) aplicando recursividade */
ExportaEmOrdem(No *Raiz, FILE *Arq) //Varredura e-r-d (= inorder traversal = percurso em in-ordem) Ordem Raiz-Esquerda_Direita.
{
    if (Raiz != (No*) NULL) //Se o ponteiro passado como parâmentro for nulo
    {
        ExportaEmOrdem(Raiz-> Esquerda, Arq); //Senão chama novamente a função indo para a esquerda
        fprintf(Arq, "%d ", Raiz->Id ); //Imprimindo o Id
        fprintf(Arq,"\n"); //Tabulação
        ExportaEmOrdem(Raiz-> Direita, Arq); //E depois chamando novamente a função indo para a direita
    }
}

/* Procedimento para exportar os valores na ordem em que foram inseridos (tipo pós-ordem) aplicando recursividade */
ExportaEmOrdemInversa(No *Raiz, FILE *Arq)
{
    if (Raiz != (No*) NULL) //Se o ponteiro passado como parâmentro for nulo
    {
        ExportaEmOrdemInversa(Raiz-> Direita, Arq); //Chama novamente a função indo para a direita
        fprintf(Arq,"%d ", Raiz->Id ); //Imprimindo o Id
        fprintf(Arq,"\n"); //Tabulação
        ExportaEmOrdemInversa(Raiz-> Esquerda, Arq); //E chama novamente a função indo para a esquerda
    }
}

/* Função para importar os valores a partir de um arquivo */
No *Importa(No *Raiz)
{
	char NomeArq[MAX]; //O nome/caminho do arquivo conterá a quantidade máxima de caracteres definida em MAX
	char linha[MAX]; //Guardará até a quantidade máxima de caracteres lidos por linha
  	char *resultado;
  	int i; //Incrementado para a contagem de linha
  	int valor; //Conterá uma string convertida para inteiro e será inserido na árvore
	
	FILE *Arq;
	
	printf("\n   Informe o nome/caminho do arquivo: ");
	gets(NomeArq);
	fflush(stdin); //Limpa o bufer de teclado evitando erros na coleta dos próximos comandos
	
	Arq = fopen (NomeArq, "r"); //abre para leitura, guardando o endereco no ponteiro Arq

	if(Arq != NULL)
	{
		i = 1; //Inicia o contador com 1, afinal ele começa a ler na linha 1.
	
    	while (!feof(Arq)) //while (fscanf(Arq, "%s", conteudo) != EOF) //enquanto nao for o final do arquivo (enquanto não for nulo)
    	{
    		// Lê uma linha (inclusive com o '\n')
    	  	resultado = fgets(linha, MAX, Arq);  // o 'fgets' lê até a quantidade máxima de caracteres definida ou até o '\n' (o que ocorrer primeiro)
      		if(resultado)  // Se foi possível ler, retorna o resultado
	  		//printf("Linha %d : %s",i,linha); //Imprime o valor da linha adquidira
	  		valor = atoi(linha);
	  		Raiz = AdicionarNo(Raiz, valor);
      		i++; //Incrementa o contado de linha
    	}
    	fclose(Arq); //Fecha o arquivo
    	return Raiz; //Retorna a Raiz com os valores inseridos
    	printf("\n\n                         Impora%c%co realizada com sucesso!\n\n\n\n\n   ", 135, 198);
    	system("pause");
	}
	
    if(Arq == NULL) //Se não conseguir abrir o arquivo (pode ser escrito if ((Arq = fopen(NomeArq, "r")) == NULL))
    {
        printf("\n\n                             Arquivo n%co encontrado!\n\n\n\n\n   ", 198); //Exibe uma mensagem de erro para usuário
        system("pause");
        return;
    }
}
/* Fim do código das funções de importação e exportação */

/* Início do código para impressão da AVL */
/* Procedimento que imprime na tela a árvore completa com as ligações de cada nó */
void ImprimeAVL(No *Raiz) //O nó principal é impresso antes da chamada no próprio menu
{  
    if(Raiz == NULL) //Se chegou a um nó nulo
    {
        return; //Retorna sem nada a fazer
    }
    
    if(Raiz != NULL) //Se ainda não encontrou um nó nulo
    {
        if(Raiz->Esquerda == NULL && Raiz->Direita == NULL) //Verifica se não há nós descendentes
        {
            printf("\n   %d n%co tem filhos", Raiz->Id, 198); //E constatado retorna a mensagem de que o nó não tem filhos
        }
        
        if(Raiz->Esquerda != NULL && Raiz->Direita != NULL) //Verifica se há filho somente na esquerda
        {
            printf("\n   %d tem %d %c esquerda e %d %c direita", Raiz->Id, Raiz->Esquerda->Id, 133, Raiz->Direita->Id, 133);
        }
        
        if(Raiz->Esquerda != NULL && Raiz->Direita == NULL) //Verifica se há filho somente na direita
        {
            printf("\n   %d tem %d %c esquerda e n%co tem filho %c direita", Raiz->Id, Raiz->Esquerda->Id, 133, 198, 133);
        }
        
        if(Raiz->Esquerda == NULL && Raiz->Direita != NULL) //Verifica se há os dois filhos (direita e esquerda)
        {
            printf("\n   %d n%co tem filho %c esquerda e tem %d %c direita", Raiz->Id, 198, 133, Raiz->Direita->Id, 133);
        }
       
        ImprimeAVL(Raiz->Esquerda); //Recursão à esquerda
        ImprimeAVL(Raiz->Direita); //Recursão à direita
    }
}

/* Procedimento que imprime na tela a altura e fator de balanceamento de cada nó */
void Estatistica(No *Raiz) //O nó principal é impresso antes da chamada no próprio menu
{  
    if(Raiz == NULL) //Se chegou a um nó nulo
    {
        return; //Retorna sem nada a fazer
    }
    
    if(Raiz != NULL) //Se ainda não encontrou um nó nulo
    {
        printf("\n   %d tem Altura igual a %d e Fator de Balanceamento igual a %d", Raiz->Id, Raiz->Altura, Balanceamento(Raiz)); //E constatado retorna a mensagem com os valores
    }
    
    Estatistica(Raiz->Esquerda);
    Estatistica(Raiz->Direita);
}
/* Fim do código para impressão da AVL */

/* Incício do corpo principal da aplicação */
int main()
{
    	No *Raiz = (No*) NULL; //Define uma variável (ponteiro) do tipo registro (No) como Nula

    imprime_tela_abertura(); //Imprime o cabeçalho da aplicação
    
    system("pause"); //Pausa do sistema

    int Opt; //Variável que recebe o comando do usuário (Menu)
    do
    {
        int Id; //Recebe o valor a ser inserido na árvore
        
        limpa_tela(); //Limpa tela
        
        imprime_tela_cabecalho(); //Imprime o cabeçalho da aplicação
        
        menu_principal(); //Imprime o menu principal na tela
        
        printf("                              1 - Inserir Manualmente\n");
        printf("                              2 - Inserir do Arquivo\n");
        printf("                              3 - Exibir Pr%c-Ordem\n", 130);
        printf("                              4 - Exibir P%cs-Ordem\n", 162);
        printf("                              5 - Exibir Em-Ordem\n");
        printf("                              6 - Exibir Em-Ordem Inversa\n");
        printf("                              7 - Buscar Elemento\n");
        printf("                              8 - Remover Elemento\n");
        printf("                              9 - Remover %crvore\n", 181);
        printf("                             10 - Altura da %crvore\n", 181);
        printf("                             11 - Exibir %crvore Completa\n", 181);        
        printf("                              0 - Sair\n\n\n");
        
        printf("   Informe a op%c%co: ", 135, 198);
        
        scanf("%d", &Opt);

		fflush(stdin); //Limpa o bufer de teclado evitando erros na coleta dos próximos comandos
        
        if (Opt == 1)
        {
            printf("\n   Informe o Id: ");
            scanf("%d", &Id);
            Raiz = AdicionarNo(Raiz, Id);
        }
        
        if (Opt == 2)
        {
			Raiz = Importa(Raiz);
			//printf("\n\n                                 Op%c%co Indispon%cvel!\n\n\n\n\n\n\n  ", 135, 198, 161);
            //system("pause");
        }
        
        else if (Opt == 3)
        {
            printf("\n   ");
            if(Raiz != (No*) NULL)
            {
                PreOrdem(Raiz); //Chama a função para imprimir os dados na tela
                GravaPreOrdem(Raiz);

            }
            
            if(Raiz == (No*) NULL)
            {
                printf("\n\n                                A %crvore est%c vazia!\n\n\n\n\n\n   ", 160, 160);
            }

			system("pause");
        }
        
        else if (Opt == 4)
        {
            printf("\n   ");
            if(Raiz != (No*) NULL)
            {
                PosOrdem(Raiz);
                GravaPosOrdem(Raiz);
            }

            if(Raiz == (No*) NULL)
            {
            printf("\n\n                                A %crvore est%c vazia!\n\n\n\n\n\n   ", 160, 160);
            }

			system("pause");
        }
        
        else if (Opt == 5)
        {
            printf("\n   ");
            if(Raiz != (No*) NULL)
            {
                EmOrdem(Raiz);
                GravaEmOrdem(Raiz);
            }

            if(Raiz == (No*) NULL)
            {
            	printf("\n\n                                A %crvore est%c vazia!\n\n\n\n\n\n   ", 160, 160);
            }

            system("pause");
        }

        else if (Opt == 6)
        {
            printf("\n   ");
            if(Raiz != (No*) NULL)
            {
                EmOrdemInversa(Raiz);
                GravaEmOrdemInversa(Raiz);
            }

            if(Raiz == (No*) NULL)
            {
            	printf("\n\n                                A %crvore est%c vazia!\n\n\n\n\n\n   ", 160, 160);
            }
            system("pause");
        }

        else if (Opt == 7)
        {
            printf("\n   ");
            if(Raiz != (No*) NULL)
            {
                printf("\n   Informe o Id: ");
                scanf("%d", &Id);

                No *NoLocalizado = BuscarNo(Raiz, Id);
                
                if (NoLocalizado == (No*) NULL)
                    printf("\n                                 N%co localizado!\n\n\n\n\n   ", 198);
                else
                    printf("\n                            Localizado no endere%co %x\n\n\n\n\n   ", 135, NoLocalizado);
            }
            
            if(Raiz == (No*) NULL)
            {
                printf("\n\n                                A %crvore est%c vazia!\n\n\n\n\n\n   ", 160, 160);
            }
            system("pause");
        }
        
        else if (Opt == 8)
        {
            printf("\n   ");
            if(Raiz != (No*) NULL)
            {
                printf("\n   Informe o Id: ");
                scanf("%d", &Id);
                printf("\n\n\n\n\n\n   ");
                Raiz = RemoverNo(Raiz, Id); //Esta linha faz a mesma coisa da linha de baixo, utiliza ponteiro para ponteiro na função
            }
            
            if(Raiz == (No*) NULL)
            {
                printf("\n\n                                A %crvore est%c vazia!\n\n\n\n\n\n   ", 160, 160);
            }
            
        system("pause");
        }
        
        else if (Opt == 9)
        {
            printf("\n   ");
            if(Raiz != (No*) NULL)
            {
            	char RemoveAVL;
                printf("\n\n   Deseja realmente excluir toda a %crvore? [s=Sim / Qualquer tecla = N%co]: ", 160, 198);
                RemoveAVL = getch(RemoveAVL);
                RemoveAVL = tolower(RemoveAVL);

            	if(RemoveAVL == 's')
				{
					while(Raiz != NULL)
                	{
                		Raiz = RemoverAVL(Raiz);
                		printf("\n   ");
                	}
        	    }
        	else
				printf("\n\n\n\n\n\n   ");
            }
            
            if(Raiz == (No*) NULL)
            {
                printf("\n\n                                A %crvore est%c vazia!\n\n\n   ", 160, 160);
            }
            
        	system("pause");
        }

        else if (Opt == 10)
        {
            printf("\n\n                        A %crvore tem a altura igual a %d\n\n\n\n\n\n\n   ", 160, Altura(Raiz));
            system("pause");
        }

        else if (Opt == 11)
        {
        	printf("\n   ");
            if(Raiz != (No*) NULL)
            {
                limpa_tela(); //Limpa tela

                imprime_tela_cabecalho(); //Imprime o cabeçalho da aplicação

                /* Fase 1 - Exibe apenas a árvore completa com todas a ligações */
                printf(" ==================================== LIGA%c%cES =================================\n", -128, -27);
   				printf("\n   %d %c o n%c principal desta %crvore", Raiz->Id, 130, 162, 160);
				ImprimeAVL(Raiz);

				printf("\n\n");

                /* Fase 2 - Exibe apenas a altura e o fator de balanceamento de cada nó da árvore */               
                printf(" ======================== ALTURA E FATOR DE BALANCEAMENTO ======================\n");                
				Estatistica(Raiz);
				printf("\n\n\n   ");
            }
        else
            if(Raiz == (No*) NULL)
            {
            printf("\n\n                                A %crvore est%c vazia!", 160, 160);
            printf("\n                    (a altura de uma %crvore vazia %c igual a -1)\n\n\n\n\n   ", -96, -126);
            }
            system("pause");
        }

        else if (Opt == 0)
        {
            creditos();
        }

        else if (Opt > 11)
        {
            printf("\n\n                                 Op%c%co Inv%clida!\n\n\n\n\n\n\n  ", 135, 198, 160);
            system("pause");
        }

    } while (Opt != 0);

    return 0;
}
/* Fim do corpo principal da aplicação */
