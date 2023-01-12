/*
Diogo Pereira Almeida - 210126
Hendrew dos Santos Nardim - 210656
Jos� Ant�nio Soares Pinto - 210430
M�nica Alessandra Garcia Beletato Kiyota Moutinho - 190608
*/


#include    <stdio.h>
#include    <stdlib.h>
#include    <locale.h>
#include    <windows.h>
#include    <ctype.h>
#include    <string.h>

//concessionaria.bin
typedef struct endereco{
 char logradouro[80];
 char bairro[15];
 char CEP[10];
 char cidade[15];
 char estado[3];
 char fone[12];
 char email[40];
}endereco;

typedef struct infocarro{
 char sigla;
 int regcarro;
}infocarro;

typedef union dadoscarro{
 char sigla;
 struct infocarro reservado;
}dadoscarro;

typedef struct loja{
 int regloja; //gerar autom�tico
 char nome[30];
 char CNPJ[19];
 struct endereco end;
 int sold;
 int reserved;
 union  dadoscarro  tabela[3];
}loja;
//concessionaria.bin

//carro.bin
typedef struct infoloja{
 char sigla;
 char CNPJ[19];
}infoloja;

union dadosloja {
 char sigla;
 struct infoloja reserva;
};

typedef struct montadora{
 int regcarro; //gerar autom�tico
 char modelo[20];
 char cor[10];
 float  valor;
 union dadosloja status;
}montadora;
//carro.bin


//historico.bin
typedef struct data{ 
	int dia;  
	int mes;  
	int ano;  
}data; 
 
typedef struct historicoVendas{ 
    int reghist; 
    int regcarro; 
    char modelo[20]; 
	char cor[10]; 
	float valor;  
	int regloja; 
	char nome[30]; 
	char cnpj[19]; 
	struct data dataVenda; 
}historicoVendas;
//historico.bin




//menu
void menu();
void cadastros(loja *p, montadora *p2);
void consultas(loja *p, montadora *p2);
void mostra(loja *p, montadora *p2);
//menu

//cadastro de informa��es
void cadastrarLojas(loja *p);
void cadastrarCarros(montadora *p);
//cadastro de informa��es



//prototipos das aloca��es
void alocaLoja(loja **p, int tam);
void alocaMontadora(montadora **p, int tam);
//prototipos das aloca��es



//verifica se h� mem�ria e cria concession�ria.bin e carro.bin
int verificaLoja();
int verificaMontadora();
//verifica se h� mem�ria e cria concession�ria.bin e carro.bin



//recebe valores
void recebeLoja(loja *p,int qtde);
void recebeMontadora(montadora *p, int qtde);
//recebe valores



//grava valores
void gravaLoja(loja *p);
void gravaMontadora(montadora *p);
//grava valores



//procura valores
void procuraConcessionaria(loja *p);
void procuraStatusCarros(montadora *p);
void procuraModeloCarros(montadora *p);
//procura valores



//mostra loja
void mostraLoja(loja *p, int qtde);
//mostra loja



//mostra montadora
void mostraMontadora(montadora *p, int qtde);
//mostra montadora



//reservar carros
void reservar(loja *p, montadora *p2);
int procuraRegCarro(montadora *p, int num_reg);
int procuraCnpj(loja *p,char cnpj2[19]);
gravaReservaM(loja *p, char *str, int pos);
gravaReservaC(montadora *p, char *str, int pos);
//reservar carros



//vende carro
void vender(loja *p, montadora *p2, historicoVendas *p3);
//vende carro


//historico de vendas
void alocaHistorico(historicoVendas **p, int tam);
int verificaHistorico();
void gravaHistorico(historicoVendas *p);
void recebeHistorico(loja *p, montadora *p2, historicoVendas *p3);
void historicoCNPJ(historicoVendas *p);
void historicoModelo(historicoVendas *p);

void alteraCNPJ(loja *p);
void alteraModelo(montadora *p);
//historico de vendas



//inicio main
int main()
{
    setlocale(LC_ALL, "portuguese");
//    keybd_event(VK_MENU  , 0x36, 0, 0);
//    keybd_event(VK_RETURN, 0x1C, 0, 0);
//    keybd_event(VK_RETURN, 0x1C, KEYEVENTF_KEYUP, 0);
//    keybd_event(VK_MENU  , 0x38, KEYEVENTF_KEYUP, 0);
    system ("title Software Facens");
    system("color 0C");
    menu();
    return 0;
}
//fim main



//inicio menu
void menu ()
{
	int op, qtde, qtde2, qtde3;
	qtde=qtde2=qtde3=0;
	loja *pd=NULL;
	montadora *pd2=NULL;
	historicoVendas *pd3=NULL;
	alocaLoja(&pd, qtde+1);
	alocaMontadora(&pd2, qtde2+1);
	alocaHistorico(&pd3, qtde3+1);
	system("cls");
    printf("\n-------------------------------Menu-------------------------------\n");
    printf("\n\tCadastrar       [1]");
    printf("\n\tConsultar       [2]");
    printf("\n\tReservar        [3]");
	printf("\n\tVender          [4]");
	printf("\n\tMostrar         [5]");
	printf("\n\tHist�rico       [6]");
    printf("\n\tSair            [7]");
    printf("\n\tPressione qualquer tecla para mudar a o tamanho da tela\n\t");
    scanf ("%i", &op);
    fflush(stdin);
	switch(op)
	{
		case 1: system("cls");
                cadastros(pd, pd2);
		break;//case 1

		case 2: system("cls");
                consultas(pd, pd2);
		break;//case 2

		case 3: system("cls");
				reservar(pd, pd2);
		break;//case 3

		case 4: system("cls");
				vender(pd, pd2, pd3);
		break;//case 4

		case 5: system("cls");
				mostra(pd, pd2);
		break;// case 5
		
		case 6: system("cls");
				printf("\n-------------------------------Menu-------------------------------\n");
                printf("\n\tConsultar hist�rico por modelo    [1]");
                printf("\n\tConsultar hist�rico por CNPJ      [2]");
                printf("\n\tVoltar                            [3]\n\t");
                scanf ("%i", &op);
                fflush(stdin);
				
				switch(op){
					case 1: system("cls");
							historicoModelo(pd3);
					break;
					
					case 2: system("cls");
							historicoCNPJ(pd3);
					break;
					
					case 3: system("cls");
							menu();
					break;
					
					default: printf("\nOp��o inv�lida");
							 Sleep(2000);
							 system("cls");
							 menu();
					break;
				}
		break;

		case 7: printf(" \n\t Saindo .");
                Sleep(1);
                printf(" .");
                Sleep(1);
                printf(" .\n");
                exit(3);
        break;//case 6

        default: printf("\n\tN�mero inv�lido, escolha outra op��o.\n");
			     Sleep(2000);
				 menu();
		break;// default
	}//switch
}
//fim menu



//cadastros
void cadastros(loja *p, montadora *p2)
{
	int op;
    printf("\n-------------------------------Menu-------------------------------\n");
    printf("\n\tCadastrar Concession�ria  [1]");
	printf("\n\tCadastrar Carros          [2]");
	printf("\n\tAlterar cadastro de CNPJ  [3]");
	printf("\n\tAlterar cadastro de carro [4]");
	printf("\n\tVoltar                    [5]\n\t");
    scanf ("%i", &op);
    fflush(stdin);
	switch(op)
	{
	    case 1: system("cls");
                cadastrarLojas(p);
		break;

		case 2: system("cls");
                cadastrarCarros(p2);
		break;
		
		case 3: system("cls");
				alteraCNPJ(p);
		break;

		case 4: system("cls");
				alteraModelo(p2);
		break;		

		case 5: system("cls");
				menu();
		break;

		default: printf("\n\tN�mero inv�lido, escolha outra op��o.\n");
			     Sleep(2000);
				 system("cls");
				 cadastros(p,p2);
		break;
	}//switch
}
//cadastros



//consultas
void consultas(loja *p, montadora *p2)
{
    int op;
	int qtde=verificaLoja(), qtde2=verificaMontadora();
    printf("\n-------------------------------Menu-------------------------------\n");
	printf("\n\tConsultar Concession�rias   [1]");
	printf("\n\tConsultar Carros            [2]");
	printf("\n\tConsultar hist�rico         [3]");
	printf("\n\tVoltar                      [4]\n\t");
    scanf ("%i", &op);
    fflush(stdin);
	switch(op)
	{
		case 1 : system("cls");
				 procuraConcessionaria(p);
		break;//case 1
                    
        case 2 : system("cls");
                 printf("\n-------------------------------Menu-------------------------------\n");
                 printf("\n\tConsulta Total         [1]");
                 printf("\n\tConsulta Parcial       [2]");
                 printf("\n\tVoltar                 [3]\n\t");
                 scanf ("%i", &op);
                 fflush(stdin);
                             switch(op)
                             {
                                case 1: system("cls");
                                        mostraMontadora(p2, qtde2);
                                break;//case 1

                                case 2: system("cls");
                                		printf("\n-------------------------------Menu-------------------------------\n");
                 						printf("\n\tConsulta pelo status         [1]");
                 						printf("\n\tConsulta pelo modelo         [2]");
                 						printf("\n\tVoltar                       [3]\n\t");
                 						scanf ("%i", &op);
                 						fflush(stdin);
										switch(op){
                                        	case 1: system("cls");
													procuraStatusCarros(p2);
                                        			break;
                                        			
                                        	case 2: system("cls");
													procuraModeloCarros(p2);
                                        			break;
                                        			
                                        	case 3: system("cls");
													consultas(p, p2);
                                        			break;
                                        			
                                        	default: system("cls");
													 printf("\n\tN�mero inv�lido, escolha outra op��o.\n");
													 system("cls");
													 consultas(p, p2);
                                        			 break;
										}
                                break;//case 2

                                case 3: system("cls");
                                        consultas(p, p2);
                                break;//case 3

                                default: printf("\n\tN�mero inv�lido, escolha outra op��o.\n");
			                             Sleep(2000);
										 system("cls");
										 consultas(p, p2);
		                        break;//default
                             }//switch
        break;//case 2
				
        case 3: system("cls");
                menu();
        break;//case 3
        
        default: printf("\n\tN�mero inv�lido, escolha outra op��o.\n");
			     Sleep(2000);
				 system("cls");
				 consultas(p, p2);
		break;
	}//switch
}
//consultas



//mostra
void mostra(loja *p, montadora *p2)
{
	int qtde=verificaLoja() ,qtde2=verificaMontadora();
	int op;
	printf("\n-------------------------------Menu-------------------------------\n");
    printf("\n\tMostrar Concession�ria  [1]");
	printf("\n\tMostrar Carros          [2]");
	printf("\n\tVoltar                  [3]\n\t");
    scanf ("%i", &op);
    fflush(stdin);
	switch(op)
	{
		case 1: system("cls");
				mostraLoja(p, qtde);
		break;

		case 2: system("cls");
				mostraMontadora(p2, qtde2);
		break;

		case 3: system("cls");
				menu();
		break;

		default: printf("\n\tN�mero inv�lido, escolha outra op��o.\n");
				 Sleep(2000);
				 system("cls");
				 mostra(p,p2);
		break;
	}//switch
}
//mostra



//cadastrar lojas
void cadastrarLojas(loja *p){
	int qtde;
	char op;
	
	
	qtde  = verificaLoja();
	
	if(qtde<=5){
		do{
			recebeLoja(p, qtde+1);
	
			qtde++;
	
			printf("\nDeseja continuar (No m�ximo 5) <S/N>? ");
			scanf("%c", &op);
			fflush(stdin);
		}while(op != 'n' && op != 'N');
	}
	else
		printf("\nRegistro Lotado!");
		
	printf("\nRegistro realizado!");
	printf("\nDeseja voltar ao menu inicial? <S/N> ");
	scanf("%c", &op);
	fflush(stdin);
	
	if (op != 's' && op != 'S')
		exit(1);
	else
	{
		system("cls");
		menu();
	}//else
}
// cadastrar lojas



//cadastrar carros
void cadastrarCarros(montadora *p){

	int qtde2;
	char op, op2;
	
	qtde2 = verificaMontadora();
	
	if(qtde2<=50){
		do{
			recebeMontadora(p, qtde2+1);
	
			qtde2++;
	
			printf("\nDeseja continuar adicionando carros (No maximo 50) <S/N>? ");
			scanf("%c", &op2);
			fflush(stdin);
	
		}while(op2 != 'n' && op2 != 'N' && qtde2<50);
	}
		else
			printf("\nRegistro de carros lotado!");
	printf("\nRegistro realizado!");
	
	printf("\nDeseja voltar ao menu inicial? <S/N> ");
	scanf("%c", &op);
	fflush(stdin);
	
	if (op != 's' && op != 'S')
		exit(1);
	else
	{
		system("cls");
		menu();
	}//else
}
//cadastrar carros



//aloca��es
void alocaLoja(loja **p, int tam){
	if((*p=(loja*)realloc(*p,tam*sizeof(loja)))==NULL)
		exit(1);
}

void alocaMontadora(montadora **p, int tam){
	if((*p=(montadora*)realloc(*p,tam*sizeof(montadora)))==NULL)
		exit(1);
}
//aloca��es



//verifica
int verificaLoja(){
	FILE *fptr=NULL;
	long int cont=0;
	if((fptr=fopen("concessionaria.bin","rb"))==NULL)
	  return cont;
	else
	  {
	   fseek(fptr,0,2);
	   cont=ftell(fptr)/sizeof(loja);
	   fclose(fptr);
	   return cont;
	  }//else
}

int verificaMontadora(){
	FILE *fptr=NULL;
	long int cont=0;
	if((fptr=fopen("carro.bin","rb"))==NULL)
	  return cont;
	else
	  {
	   fseek(fptr,0,2);
	   cont=ftell(fptr)/sizeof(montadora);
	   fclose(fptr);
	   return cont;
	  }//else
}
//verifica



//recebe valores de loja
void recebeLoja(loja *p,int qtde){
	p->regloja=qtde;

	printf("\nDigite os dados da concessionaria");
	printf("\nRegistro.....: %i\n", p->regloja);

	printf("\nNome.........: ");
	gets(p->nome);
	fflush(stdin);

	printf("\nCNPJ <xx.xxx.xxx/xxxx-xx>....: ");
	gets(p->CNPJ);
	fflush(stdin);

	printf("\n\nDados de endere�o");
	printf("\nLogradouro...................: ");
	gets(p->end.logradouro);
	fflush(stdin);

	printf("\nBairro.......................: ");
	gets(p->end.bairro);
	fflush(stdin);

	printf("\nCEP..........................: ");
	gets(p->end.CEP);
	fflush(stdin);

	printf("\nCidade.......................: ");
	gets(p->end.cidade);
	fflush(stdin);

	printf("\nEstado.......................: ");
	gets(p->end.estado);
	fflush(stdin);

	printf("\nTelefone.....................: ");
	gets(p->end.fone);
	fflush(stdin);

	printf("\nE-mail.......................: ");
	gets(p->end.email);
	fflush(stdin);

	p->sold = 0;
	printf("\nVendidos.....: %i", p->sold);

	p->reserved = 0;
	printf("\nReservados...: %i", p->reserved);

	p->tabela[0].sigla = 'L';
	printf("\nTabela0......: %c\n", p->tabela[0].sigla);
	
	p->tabela[1].sigla = 'L';
	printf("\nTabela1......: %c\n", p->tabela[1].sigla);
	
	p->tabela[2].sigla = 'L';
	printf("\nTabela2......: %c\n", p->tabela[2].sigla);
	
	gravaLoja(p);
}
//recebe valores de loja



//recebe valores de montadora
void recebeMontadora(montadora *p, int qtde){
	p->regcarro = qtde;
	char sigla;

	printf("\nDigite os dados do carro");
	printf("\nRegistro..............................: %i\n", p->regcarro);
	fflush(stdin);

	printf("\nModelo................................: ");
	gets(p->modelo);
	fflush(stdin);

	printf("\nCor...................................: ");
	gets(p->cor);
	fflush(stdin);

	printf("\nValor.................................: ");
	scanf("%f", &p->valor);
	fflush(stdin);
	
	printf("\nStatus Livre/Reservado <L/R>..........: ");
	scanf("%c", &sigla);
	p->status.sigla=toupper(sigla);
	fflush(stdin);

	gravaMontadora(p);
}
//recebe valores de montadora



//grava valores da loja em concessionaria.bin
void gravaLoja(loja *p){
	FILE *fptr=NULL;
	if((fptr=fopen("concessionaria.bin", "ab"))==NULL)
		printf("\nErro ao abrir o arquivo");
	else
		fwrite(p,sizeof(loja),1,fptr);
	fclose(fptr);
}
//grava valores da loja em concessionaria.bin

//grava valores dos carros em carro.bin
void gravaMontadora(montadora *p){
	FILE *fptr=NULL;
	if((fptr=fopen("carro.bin", "ab"))==NULL)
		printf("\nErro ao abrir o arquivo");
	else
		fwrite(p,sizeof(montadora),1,fptr);
	fclose(fptr);
}
//grava valores dos carros em carro.bin



//procura montadora
void procuraConcessionaria(loja *p)
{
	int pos;
    char cnpj2[20], op;
    FILE *fptr=NULL;
    int i=0,achou=-1,qtde;

    qtde=verificaLoja();

    printf("Digite o CNPJ da empresa que est� procurando: ");
    gets(cnpj2);
    fflush(stdin);

    if((fptr=fopen("concessionaria.bin","rb"))==NULL)
          printf("\nErro");

    else{
          for(i=0;i<qtde;i++){
              fseek(fptr,i*sizeof(loja),0);
              fread(p,sizeof(loja),1,fptr);

              if(strcmp(p->CNPJ, cnpj2)==0){
                achou=i;   
                i=qtde;    
                 }//if
              }//for
    fclose(fptr);
      }//else

      pos = achou;
      if(pos==-1)
          printf("\nRegistro inexistente\n\n");

    else{
        printf("\nNome......: %s", p->nome);
        printf("\nCNPJ......: %s", p->CNPJ);
        printf("\nVendidos..: %i", p->sold);
        
        if(p->reserved != 0){
        	printf("\nTabela[0]: %c - %i", p->tabela[0].sigla, p->tabela[0].reservado.regcarro);
        	printf("\nTabela[1]: %c - %i", p->tabela[1].sigla, p->tabela[1].reservado.regcarro);
        	printf("\nTabela[2]: %c - %i\n", p->tabela[2].sigla, p->tabela[2].reservado.regcarro);
		}
    }
	printf("\nDeseja voltar ao menu inicial? <S/N> ");
	scanf("%c", &op);
	fflush(stdin);
	
	if (op != 's' && op != 'S')
		exit(1);
	else
	{
		system("cls");
		menu();
	}//else
}
//procura montadora



//procura carros pelo status
void procuraStatusCarros(montadora *p)
{
	char op;
	int pos,j,qtde2;
    char sigla2;
    FILE *fptr=NULL;
    int i=0,achou=-1,qtde;

    qtde=verificaMontadora();

    printf("Digite o status[L/R]: ");
    scanf("%c", &sigla2);
    fflush(stdin);
	sigla2=toupper(sigla2);

    if((fptr=fopen("carro.bin","rb"))==NULL)
          printf("\nErro");

    else{
          for(i=0;i<qtde;i++){
              fseek(fptr,i*sizeof(montadora),0);
              fread(p,sizeof(montadora),1,fptr);

              if(p->status.sigla==sigla2){
			 	achou=i;   
            	printf("\nN.Reg.....: %i", p->regcarro);
				printf("\nModelo....: %s", p->modelo);
				printf("\nCor.......: %s", p->cor);
				printf("\nValor.....: %f", p->valor);
				printf("\nStatus....: %c - %s\n", p->status.sigla, p->status.reserva.CNPJ);
                }//if
              }//for
    fclose(fptr);
    }//else

	printf("\nDeseja voltar ao menu inicial? <S/N> ");
	scanf("%c", &op);
	fflush(stdin);
	
	if (op != 's' && op != 'S')
		exit(1);
	else
	{
		system("cls");
		menu();
	}//else
}
//procura carros pelo status



//procura carros pelo modelo
void procuraModeloCarros(montadora *p)
{
	char op;
	int pos;
    char modelo2[20];
    FILE *fptr=NULL;
    int i=0,achou=-1,qtde;

    qtde=verificaMontadora();

    printf("Digite o modelo que est� procurando: ");
    gets(modelo2);
    fflush(stdin);

    if((fptr=fopen("carro.bin","rb"))==NULL)
          printf("\nErro");

    else{
          for(i=0;i<qtde;i++){
              fseek(fptr,i*sizeof(montadora),0);
              fread(p,sizeof(montadora),1,fptr);

              if(strcmp(p->modelo, modelo2) == 0){
                achou=i;
				printf("\nN.reg.....: %i", p->regcarro);
		        printf("\nModelo....: %s", p->modelo);
		        printf("\nCor.......: %s", p->cor);
				printf("\nValor.....: %.2f", p->valor);
				printf("\nStatus....: %c - %s\n", p->status.sigla, p->status.reserva.CNPJ);
                }//if
            }//for
    fclose(fptr);
    }//else


	printf("\nDeseja voltar ao menu inicial? <S/N> ");
	scanf("%c", &op);
	fflush(stdin);
	
	if (op != 's' && op != 'S')
		exit(1);
	else
	{
		system("cls");
		menu();
	}//else
}
//procura carros pelo modelo



//mostra valores da concessionaria.bin
void mostraLoja(loja *p, int qtde){
	montadora *p2;
	int i;
	char op;
	FILE *fptr=NULL;
	

	if((fptr=fopen("concessionaria.bin", "rb"))==NULL)
		printf("\nErro ao abrir o arquivo");
	else{
		for(i=0;i<qtde;i++){
			fseek(fptr, i*sizeof(loja), 0);
			fread(p,sizeof(loja),1,fptr);

			printf("\nRegistro das concessionarias");
			printf("\nRegistro................: %i", p->regloja);
			printf("\nNome da concessionaria..: %s", p->nome);
			printf("\nCNPJ....................: %s", p->CNPJ);


			printf("\nDados de endere�o");
			printf("\nLogradouro..............: %s", p->end.logradouro);
			printf("\nBairro..................: %s", p->end.bairro);
			printf("\nCEP.....................: %s", p->end.CEP);
			printf("\nCidade..................: %s", p->end.cidade);
			printf("\nEstado..................: %s", p->end.estado);
			printf("\nFone....................: %s", p->end.fone);
			printf("\nEmail...................: %s", p->end.email);


			printf("\nVendidos................: %i", p->sold);
			printf("\nReservados..............: %i", p->reserved);
			
			printf("\ntabela 0................: %c - %i", p->tabela[0].sigla, p->tabela[0].reservado.regcarro);
			printf("\ntabela 1................: %c - %i", p->tabela[1].sigla, p->tabela[1].reservado.regcarro);
			printf("\ntabela 2................: %c - %i\n", p->tabela[2].sigla, p->tabela[2].reservado.regcarro);
		}
		fclose(fptr);
	}

	printf("\nDeseja voltar ao menu inicial? <S/N> ");
	scanf("%c", &op);
	fflush(stdin);

	if (op != 's' && op != 'S')
		exit(1);
	else
	{
		system("cls");
		menu();
	}//else
}
//mostra valores da concessionaria.bin



//mostra valores de carro.bin
void mostraMontadora(montadora *p, int qtde){
	int i;
	FILE *fptr=NULL;
	char op;

	if((fptr=fopen("carro.bin", "rb"))==NULL)
		printf("\nErro ao abrir o arquivo");
	else{
		for(i=0;i<qtde;i++){
			fseek(fptr, i*sizeof(montadora), 0);
			fread(p,sizeof(montadora),1,fptr);


			printf("\nRegistro dos carros");
			printf("\nRegistro................: %i",   p->regcarro);
			printf("\nModelo..................: %s",   p->modelo);
			printf("\nCor.....................: %s",   p->cor);
			printf("\nValor...................: %.2f", p->valor);
			printf("\nStatus..................: %c - %s\n", p->status.sigla, p->status.reserva.CNPJ);
		}
		fclose(fptr);
	}
	printf("\nDeseja voltar ao menu inicial? <S/N> ");
	scanf("%c", &op);
	fflush(stdin);
	
	if (op != 's' && op != 'S')
		exit(1);
	else
	{
		system("cls");
		menu();
	}//else
}
//mostra valores de carro.bin



//reservar carros
void reservar(loja *p, montadora *p2){
	int num_reg, pos, pos2, i;
	char cnpj2[19], op, op2;
	
	printf("\nDigite o CNPJ da empresa que deseja reservar um carro: ");
	gets(cnpj2);
	fflush(stdin);
	pos2 = procuraCnpj(p, cnpj2);
	
	if(pos2 == -1){
		printf("\nCNPJ n�o encontrado!");
		Sleep(2000);
		system("cls");
		reservar(p, p2);
	}
	else{
		if(p->reserved<=3){
			printf("\nDigite o n�mero de registro do carro que deseja reservar: ");
			scanf("%i", &num_reg);
			fflush(stdin);
			
			pos = procuraRegCarro(p2,num_reg);
			
			if(pos==-1){
				printf("\nRegistro inexistente\n\n");
				Sleep(2000);
				system("cls");
				reservar(p, p2);
			}
			else{
				printf("\nRegistro......: %i",   p2->regcarro);
				printf("\nModelo........: %s",   p2->modelo);
				printf("\nCor...........: %s",   p2->cor);
				printf("\nValor.........: %.2f", p2->valor);
				printf("\nStatus........: %c\n", p2->status.sigla);
				
				
				if(p2->status.sigla == 'R'){
					printf("\nCarro j� reservado");
					Sleep(2000);
					system("cls");
					reservar(p, p2);
				}
				else{
					printf("\nDigite <L> para deixar livre ou <R> para reservar: ");
					scanf("%c", &(p2->status.sigla));
					fflush(stdin);
					p2->status.sigla = toupper(p2->status.sigla);
					printf("\nConfirme o CNPJ da empresa: ");
					gets(p2->status.reserva.CNPJ);
					
					printf("\nTabela[0]: %c - %i", p->tabela[0].sigla, p->tabela[0].reservado.regcarro);					
					printf("\nTabela[1]: %c - %i", p->tabela[1].sigla, p->tabela[1].reservado.regcarro);
					printf("\nTabela[2]: %c - %i\n", p->tabela[2].sigla, p->tabela[2].reservado.regcarro);
									
					printf("\nDigite a tabela que voc� deseja alterar (0, 1 ou 2): ");
					scanf("%i", &i);
					fflush(stdin);
					
					printf("\nTabela[%i]: %c - %i\n", i, p->tabela[i].sigla, p->tabela[i].reservado.regcarro);
					
					printf("\nDeseja alterar est� tabela? <S/N>");
					scanf("%c", &op2);
					fflush(stdin);
					op2 = toupper(op2);
					
					p->reserved++;
					
					if(op2 == 'N'){
						reservar(p, p2);
					}
					else{
						p->tabela[i].sigla = 'R';
						p->tabela[i].reservado.regcarro = num_reg;
						gravaReservaM(p, "rb+", pos2);
						gravaReservaC(p2, "rb+", pos);
						printf("\nCarro reservado!");
					}
				}
			}
		}
		else{
			printf("\nN�mero de reserva m�ximo atingido!");
			reservar(p, p2);
		}
	}
			
	printf("\nDeseja voltar ao menu inicial? <S/N> ");
	scanf("%c", &op);
	fflush(stdin);
	
	if (op != 's' && op != 'S')
		exit(1);
	else
	{
		system("cls");
		menu();
	}//else
}
//reservar carros


//procura regcarro
int procuraRegCarro(montadora *p, int num_reg){
	int pos,j,qtde2;
    FILE *fptr=NULL;
    int i=0,achou=-1,qtde;

    qtde=verificaMontadora();

    if((fptr=fopen("carro.bin","rb"))==NULL)
          printf("\nErro");

    else{
		for(i=0;i<qtde;i++){
      		fseek(fptr,i*sizeof(montadora),0);  //caminho com fptr dentro do arquivo
      		fread(p,sizeof(montadora),1,fptr);
      		
      		if(p->regcarro==num_reg){
      			achou=i;
      			i=qtde;
			  }
		}
	fclose(fptr);
	}
	return achou;
}
//procura regcarro



//procura cnpj
int procuraCnpj(loja *p,char cnpj2[19]){
	int pos;
    FILE *fptr=NULL;
    int i=0,achou=-1,qtde;

    qtde=verificaLoja();

    if((fptr=fopen("concessionaria.bin","rb"))==NULL)
          printf("\nErro");

    else{
          for(i=0;i<qtde;i++){
              fseek(fptr,i*sizeof(loja),0);
              fread(p,sizeof(loja),1,fptr);

              if(strcmp(p->CNPJ, cnpj2)==0){
                achou=i;   
                i=qtde;    
                 }//if
              }//for
    fclose(fptr);
    }//else

    pos = achou;
    if(pos==-1){
		return achou;
	}
    else{
    	return achou;   
    }
}
//procura cnpj



//grava valores
gravaReservaM(loja *p, char *str, int pos){
	FILE *fptr=NULL;
	
	if((fptr=fopen("concessionaria.bin",str))==NULL)
		printf("\nErro ao abrir o arquivo");
	
	else{
		if(strcmp(str,"rb+")==0)
	    	fseek(fptr,pos*sizeof(loja),0);
			fwrite(p,sizeof(loja),1,fptr);
	}//else
	fclose(fptr);   //fora do else - por conta do ab ou rb+
}

gravaReservaC(montadora *p, char *str, int pos){
	FILE *fptr=NULL;
	
	if((fptr=fopen("carro.bin",str))==NULL)
		printf("\nErro ao abrir o arquivo");
	
	else{
		if(strcmp(str,"rb+")==0)
	    	fseek(fptr,pos*sizeof(montadora),0);
			fwrite(p,sizeof(montadora),1,fptr);
	}//else
	fclose(fptr);   //fora do else - por conta do ab ou rb+
}
//grava valores



//vende carro
void vender(loja *p, montadora *p2, historicoVendas *p3)
{
	int num_reg, pos, pos2, i, op2, qtde3;
	char cnpj2[19], op;

	printf("\nDigite o n�mero de registro do carro : ");
	scanf("%i", &num_reg);
	fflush(stdin);
	pos2 = procuraRegCarro(p2,num_reg);
	if(pos2==-1)
	{
		printf("\nRegistro inexistente\n\n");
		Sleep(2000);
		system("cls");
		vender(p, p2, p3);
	}//if
	else
	{
		printf("\nRegistro......: %i",   p2->regcarro);
		printf("\nModelo........: %s",   p2->modelo);
		printf("\nCor...........: %s",   p2->cor);
		printf("\nValor.........: %.2f", p2->valor);
		printf("\nStatus........: %c\n", p2->status.sigla);
		strcpy(cnpj2, p2->status.reserva.CNPJ);
		pos=procuraCnpj(p, cnpj2);
		if(pos==-1)
		{
			printf("\nCNPJ n�o encontrado!");
			Sleep(2000);
			system("cls");
			vender(p, p2, p3);
		}
		else
		{
			if(p2->status.sigla == 'R')
			{
				printf("\nDeseja vender ou liberar o carro?[1-Vender, 2-Liberar]\n");
				scanf("%i", &op2);
				fflush(stdin);
				switch(op2)
				{
					case 1: printf("\nInicio do processo de Venda.\n");
							printf("\nQual tabela deseja alterar?");
							printf("\nTabela[0]: %c - %i", p->tabela[0].sigla, p->tabela[0].reservado.regcarro);
        					printf("\nTabela[1]: %c - %i", p->tabela[1].sigla, p->tabela[1].reservado.regcarro);
        					printf("\nTabela[2]: %c - %i\n", p->tabela[2].sigla, p->tabela[2].reservado.regcarro);
							scanf("%i", &i);
							fflush(stdin);
							recebeHistorico(p, p2, p3);
							p2->status.sigla='L';
							memset(p2->cor,0,strlen(p2->cor));
							memset(p2->modelo,0,strlen(p2->modelo));
							p2->valor=0;					
							p->tabela[i].sigla='L';
							p->tabela[i].reservado.regcarro=0;
							p->reserved--;
							p->sold++;
							printf("\nDigite a data <dd mm aa>:  ");
							scanf("%i %i %i", &p3->dataVenda.dia, &p3->dataVenda.mes, &p3->dataVenda.ano);
							fflush(stdin);
							gravaHistorico(p3);
							gravaReservaM(p, "rb+", pos);
							gravaReservaC(p2, "rb+", pos2);
							printf("\nVenda completa");
							printf("\nDeseja voltar ao menu inicial? <S/N> ");
							scanf("%c", &op);
							fflush(stdin);
							if (op != 's' && op != 'S')
							exit(1);
							else
							{
								system("cls");
								menu();
							}//else
					break;//case 1

					case 2: printf("\nInicio do processo de libera��o.\n");
							printf("\nQual tabela deseja alterar?");
							printf("\nTabela[0]: %c - %i", p->tabela[0].sigla, p->tabela[0].reservado.regcarro);
        					printf("\nTabela[1]: %c - %i", p->tabela[1].sigla, p->tabela[1].reservado.regcarro);
        					printf("\nTabela[2]: %c - %i\n", p->tabela[2].sigla, p->tabela[2].reservado.regcarro);
							scanf("%i", &i);
							fflush(stdin);
							p2->status.sigla='L';
							memset(p2->status.reserva.CNPJ,0,sizeof(p2->status.reserva.CNPJ));
							p->tabela[i].sigla='L';
							p->tabela[i].reservado.regcarro=0;
							p->reserved--;
							gravaReservaM(p, "rb+", pos);
							gravaReservaC(p2, "rb+", pos2);
							printf("\nLibera��o completa");
							printf("\nDeseja voltar ao menu inicial? <S/N> ");
							scanf("%c", &op);
							fflush(stdin);
							if (op != 's' && op != 'S')
							exit(1);
							else
							{
								system("cls");
								menu();
							}//else
					break;//case 2

					default: printf("\n\tN�mero inv�lido, escolha outra op��o.\n");
					vender(p, p2, p3);
					break;//default
				}//switch
			}//if
			else
			{
				printf("O carro n�o est� reservado.");
				Sleep(2000);
				system("cls");
				vender(p, p2, p3);
			}//else
		}//else
	}//else
}//void
//vende carro


//aloca historico vendas
void alocaHistorico(historicoVendas **p, int tam){
	if((*p=(historicoVendas*)realloc(*p,tam*sizeof(historicoVendas)))==NULL)
		exit(1);
}
//aloca historico vendas


//verifica historico vendas
int verificaHistorico(){
	FILE *fptr=NULL;
	long int cont=0;
	if((fptr=fopen("historico.bin","rb"))==NULL)
	  return cont;
	else
	  {
	   fseek(fptr,0,2);
	   cont=ftell(fptr)/sizeof(historicoVendas);
	   fclose(fptr);
	   return cont;
	  }//else
}
//verifica historico vendas


//grava historico de vendas
void gravaHistorico(historicoVendas *p){	
	FILE *fptr=NULL;
		if((fptr=fopen("historico.bin", "ab"))==NULL)
			printf("\nErro ao abrir o arquivo");
		else
			fwrite(p,sizeof(historicoVendas),1,fptr);
		fclose(fptr);
}
//grava historico de vendas


//mostra historico vendas cnpj
void historicoCNPJ(historicoVendas *p){
	char op;
	int pos;
    char cnpj2[19];
    FILE *fptr=NULL;
    int i=0,achou=-1,qtde;

    qtde=verificaHistorico();

    printf("Digite o CNPJ da concession�ria que est� procurando: ");
    gets(cnpj2);
    fflush(stdin);

    if((fptr=fopen("historico.bin","rb"))==NULL)
          printf("\nErro");

    else{
          for(i=0;i<qtde;i++){
              fseek(fptr,i*sizeof(historicoVendas),0);
              fread(p,sizeof(historicoVendas),1,fptr);

              if(strcmp(p->cnpj, cnpj2) == 0){
                achou=i;
				printf("\nRegHist.....: %i", p->reghist);
        		printf("\nRegCarro....: %i", p->regcarro);
				printf("\nModelo......: %s", p->modelo);
				printf("\nCor.........: %s", p->cor);
				printf("\nValor.......: %.2f", p->valor);
				printf("\nRegLoja.....: %i", p->regloja);
				printf("\nNome........: %s", p->nome);
				printf("\nCNPJ........: %s", p->cnpj);
				printf("\nData........: %i/%i/%i\n", p->dataVenda.dia, p->dataVenda.mes, p->dataVenda.ano);
                }//if
            }//for
    fclose(fptr);
    }//else


	printf("\nDeseja voltar ao menu inicial? <S/N> ");
	scanf("%c", &op);
	fflush(stdin);
	
	if (op != 's' && op != 'S')
		exit(1);
	else
	{
		system("cls");
		menu();
	}//else
}
//mostra historico vendas cnpj



//mostra hitorico vendas modelo
void historicoModelo(historicoVendas *p){
	char op;
	int pos;
    char modelo2[20];
    FILE *fptr=NULL;
    int i=0,achou=-1,qtde;

    qtde=verificaHistorico();

    printf("Digite o modelo do carro que est� procurando: ");
    gets(modelo2);
    fflush(stdin);

    if((fptr=fopen("historico.bin","rb"))==NULL)
          printf("\nErro");

    else{
          for(i=0;i<qtde;i++){
              fseek(fptr,i*sizeof(historicoVendas),0);
              fread(p,sizeof(historicoVendas),1,fptr);

              if(strcmp(p->modelo, modelo2) == 0){
                achou=i;
				printf("\nRegHist.....: %i", p->reghist);
        		printf("\nRegCarro....: %i", p->regcarro);
				printf("\nModelo......: %s", p->modelo);
				printf("\nCor.........: %s", p->cor);
				printf("\nValor.......: %.2f", p->valor);
				printf("\nRegLoja.....: %i", p->regloja);
				printf("\nNome........: %s", p->nome);
				printf("\nCNPJ........: %s", p->cnpj);
				printf("\nData........: %i/%i/%i\n", p->dataVenda.dia, p->dataVenda.mes, p->dataVenda.ano);
                }//if
            }//for
    fclose(fptr);
    }//else


	printf("\nDeseja voltar ao menu inicial? <S/N> ");
	scanf("%c", &op);
	fflush(stdin);
	
	if (op != 's' && op != 'S')
		exit(1);
	else
	{
		system("cls");
		menu();
	}//else
}
//mostra hitorico vendas modelo



//recebe hist�rico vendas
void recebeHistorico(loja *p, montadora *p2, historicoVendas *p3){
	int qtde3;
	qtde3=verificaHistorico(p3, qtde3+1);
	p3->reghist=qtde3;
	p3->regcarro=p2->regcarro;
	strcpy(p3->modelo, p2->modelo);
	strcpy(p3->cor, p2->cor);
	p3->valor=p2->valor;
	p3->regloja=p->regloja;
	strcpy(p3->nome, p->nome);
	strcpy(p3->cnpj, p->CNPJ);
	
}
//recebe hist�rico vendas



//altera cadastro por CNPJ
void alteraCNPJ(loja *p){
	int pos2, opcao;
	char cnpj2[19], op;
	
	printf("\nDigite o CNPJ da empresa que deseja alterar o cadastro: ");
	gets(cnpj2);
	fflush(stdin);
	pos2 = procuraCnpj(p, cnpj2);
	
	if(pos2 == -1){
		printf("\nCNPJ n�o encontrado!");
	}
	else{
		printf("\nDados da concession�ria");
		printf("\nRegistro: %i", p->regloja);
		printf("\nNome da concessionaria..: %s", p->nome);
		printf("\nCNPJ....................: %s", p->CNPJ);

		printf("\nDados de endere�o");
		printf("\nLogradouro..............: %s", p->end.logradouro);
		printf("\nBairro..................: %s", p->end.bairro);
		printf("\nCEP.....................: %s", p->end.CEP);
		printf("\nCidade..................: %s", p->end.cidade);
		printf("\nEstado..................: %s", p->end.estado);
		printf("\nFone....................: %s", p->end.fone);
		printf("\nEmail...................: %s", p->end.email);

		printf("\nVendidos................: %i", p->sold);
		printf("\nReservados..............: %i", p->reserved);
			
		printf("\ntabela 0................: %c - %i", p->tabela[0].sigla, p->tabela[0].reservado.regcarro);
		printf("\ntabela 1................: %c - %i", p->tabela[1].sigla, p->tabela[1].reservado.regcarro);
		printf("\ntabela 2................: %c - %i\n", p->tabela[2].sigla, p->tabela[2].reservado.regcarro);
		
		printf("\nDeseja alterar o Nome[1] ou o CNPJ[2]? ");
		scanf("%i", &opcao);
		fflush(stdin);
		
		switch(opcao){
			case 1:	printf("\nDigite o novo Nome: ");
					gets(p->nome);
					fflush(stdin);
					gravaReservaM(p, "rb+", pos2);
					printf("\nNome alterado com sucesso!\n");	
			break;
		
			case 2: printf("\nDigite o novo CNPJ: ");
					gets(p->CNPJ);
					fflush(stdin);
					gravaReservaM(p, "rb+", pos2);
					printf("\nCNPJ alterado com sucesso!\n");	
			break;
		
		default:printf("\nOp��o inv�lida!");
				Sleep(2000);
				system("cls");
				alteraCNPJ(p);	
		break; 
		}
	}
	printf("\nDeseja voltar ao menu inicial? <S/N> ");
	scanf("%c", &op);
	fflush(stdin);
	
	if (op != 's' && op != 'S')
		exit(1);
	else
	{
		system("cls");
		menu();
	}//else
}
//altera cadastro por CNPJ


//altera cadastro por modelo
void alteraModelo(montadora *p){
	int pos2, opcao, regcarro2;
	char op;
	
	printf("\nDigite o registro do carro que voc� deseja alterar: ");
	scanf("%i", &regcarro2);
	fflush(stdin);
	pos2 = procuraRegCarro(p, regcarro2);
	
	if(pos2 == -1){
		printf("\nRegistro n�o encontrado!");
	}
	else{
		printf("\nModelo...: %s", p->modelo);
		printf("\nCor......: %s", p->cor);
		printf("\nValor....: %.2f", p->valor);
		printf("\nStatus...: %c\n", p->status.sigla);
		
		printf("\nDeseja alterar o Modelo[1], Cor[2] ou Valor[3]? ");
		scanf("%i", &opcao);
		fflush(stdin);
		
		switch(opcao){
			case 1:	printf("\nDigite o novo Modelo: ");
					gets(p->modelo);
					fflush(stdin);
					gravaReservaC(p, "rb+", pos2);
					printf("\nModelo alterado com sucesso!\n");	
			break;
		
			case 2: printf("\nDigite a nova Cor: ");
					gets(p->cor);
					fflush(stdin);
					gravaReservaC(p, "rb+", pos2);
					printf("\nCor alterada com sucesso!\n");	
			break;
			
			case 3: printf("\nDigite o novo Valor: ");
					scanf("%f", &p->valor);
					fflush(stdin);
					gravaReservaC(p, "rb+", pos2);
					printf("\nValor alterado com sucesso!\n");	
			break;
		
			default:printf("\nOp��o inv�lida!");
					Sleep(2000);
					system("cls");
					alteraCNPJ(p);	
			break; 
		}
		printf("\nDeseja voltar ao menu inicial? <S/N> ");
		scanf("%c", &op);
		fflush(stdin);
		
		if (op != 's' && op != 'S')
			exit(1);
		else
		{
			system("cls");
			menu();
		}//else
	}
}
//altera cadastro por modelo
