#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>

// SOFTWARE DA PIZZARIA DEGUST
// DESENVOLVIDO POR: SOFTDEV
// LOGAR COMO ADM: login 1 senha 1


// ESTRUTURAS
typedef struct bebida{
    int id;
    char nome[50];
    float preco;
    char descricao[100];
    bool promocao;
    float valorPromocao;
    struct bebida *proximo;
}Bebida;

typedef struct cliente{
    int id;
    char nome[50];
    long int cpf;
    int qtdPizzasCompradas;
    struct cliente *proximo;
}Cliente;

typedef struct data{
    int ano;
    short mes;
    short dia;
}Data;

typedef struct elogio{
    int id;
    char descricao[200];
    struct elogio *proximo; 
}Elogio;

typedef struct pedido{
    int id;
    int idCliente;
    int mesa;
    char endereco[100];
    char nomeCliente[50];
    int status; //1 = em andamento; 2 = finalizado; 3 = cancelado
    int idPizzaria; //1, 2, 3
    struct pedido *proximo;
    struct data dataPedido;
}Pedido;

typedef struct itemPedido{
    int id;
    int idPedido;
    int idItem;
    int tipoItem; //1 = pizza; 2 = bebida
    bool promocao;
    float valorPromocao;
    char nome[50];
    float preco;
    struct itemPedido *proximo;
} ItemPedido;

typedef struct pizza{
    int id;
    char nome[50];
    float preco;
    char descricao[100];
    bool promocao;
    float valorPromocao;
    struct pizza *proximo;
}Pizza;

typedef struct reclamacao{
    int id;
    char descricao[200];
    struct reclamacao *proximo; 
}Reclamacao;

typedef struct qtdPizzasUnidade{
    int idPizza;
    int qtdTotal;
    char nomePizza[50];
}QtdPizzasUnidade;

typedef struct usuario{
    int id;
    char nome[50];
    char login[50];
    char senha[50];
    int tipoLogin;
    int pizzariaTrabalha; // 1, 2, 3
    struct usuario *proximo;
}Usuario;



// VARIÁVEIS GLOBAIS
char *dbBebidas = "./database/bebidas.bin";
char *dbClientes = "./database/clientes.bin";
char *dbElogios = "./database/elogios.bin";
char *dbItensPedidos = "./database/itensPedidos.bin";
char *dbPedidos = "./database/pedidos.bin";
char *dbPizzas = "./database/pizzas.bin";
char *dbReclamacoes = "./database/reclamacoes.bin";
char *dbUsuarios = "./database/usuarios.bin";

Bebida *bebidas = NULL;
Cliente *clientes = NULL;
Elogio *elogios = NULL;
Pedido *pedidos = NULL;
ItemPedido *itensPedidos = NULL;
Pizza *pizzas = NULL;
Reclamacao *reclamacoes = NULL;
Usuario *usuarios = NULL;
Usuario usuarioLogado;


// DECLARANDO FUNÇÕES
int confereLogin(char login[50], char senha[50], int tipoLogin);

void adicionarBebidas();
void adicionarClientes();
void adicionarElogios();
void adicionarItensPedidos();
void adicionarPedidos();
void adicionarPizzas();
void adicionarPromocoes();
void adicionarReclamacoes();
void adicionarUsuarios();
void carregaBebidas();
void carregaClientes();
void carregaElogios();
void carregaItensPedidos();
void carregaPedidos();
void carregaPizzas();
void carregaPromocoes();
void carregaReclamacoes();
void carregaUsuarios();
void editarBebidas();
void editarClientes();
void editarElogios();
void editarPedidos(int statusAlterar);
void editarPizzas();
void editarPromocoes();
void editarReclamacoes();
void editarUsuarios();
void exibirMenuAdministrador();
void exibirMenuBebidas();
void exibirMenuClientes();
void exibirMenuElogios();
void exibirMenuFuncionario();
void exibirMenuLogin();
void exibirMenuPedidos();
void exibirMenuPromocoes();
void exibirMenuReclamacoes();
void exibirMenuRelatorios();
void exibirMenuPizzas();
void exibirMenuUsuarios();
void logarNoSistema(int tipoLogin);
void relatorioUm();
void relatorioDois();
void relatorioTres();
void relatorioQuatro();
void relatorioCinco();
void relatorioSeis();
void removerBebidas();
void removerClientes();
void removerElogios();
void removerItensPedidos();
void removerPizzas();
void removerPromocoes();
void removerReclamacoes();
void removerUsuarios();
void sair();
void salvarBebidas();
void salvarClientes();
void salvarElogios();
void salvarItensPedidos();
void salvarPedidos();
void salvarPizzas();
void salvarPromocoes();
void salvarReclamacoes();
void salvarUsuarios();
void visualizarBebidas();
void visualizarClientes();
void visualizarElogios();
void visualizarPedidos();
void visualizarPizzas();
void visualizarPromocoes();
void visualizarReclamacoes();
void visualizarUsuarios();

Bebida *buscarBebidaPeloId(int idBebida);
Cliente *buscarClientePeloId(int idCliente);
Elogio *buscarElogioPeloId(int idElogio);
ItemPedido *buscarItemPedidoPeloId(int idItemPedido);
Pedido *buscarPedidoPeloId(int idPedido);
Pizza *buscarPizzaPeloId(int idPizza);
Reclamacao *buscarReclamacaoPeloId(int idReclamacao);
Usuario *buscarUsuarioPeloId(int idUsuario);



// FUNÇÕES
int confereLogin(char login[50], char senha[50], int tipoLogin) {
    Usuario *aux = usuarios;
    while(aux != NULL){
        if(strcmp(aux->login, login) == 0 && strcmp(aux->senha, senha) == 0 && aux->tipoLogin == tipoLogin){
            usuarioLogado.id = aux->id;
            usuarioLogado.pizzariaTrabalha = aux->pizzariaTrabalha;
            return 1;
        }
        aux = aux->proximo;
    }

    return 0;
}

// -------------------------------- MENUS --------------------------------

void exibirMenuAdministrador() {
    int opcaoEscolhida;
    do {
        printf("\n\n'-------------------[MENU DE ADMINISTRADOR]----------------------'\n");
        printf("'                                                                '\n");
        printf("'         Digite 1 para acessar o menu de PIZZAS                 '\n");
        printf("'         Digite 2 para acessar o menu de BEBIDAS                '\n");
        printf("'         Digite 3 para acessar o menu de PEDIDOS                '\n");
        printf("'         Digite 4 para acessar o menu de PROMOÇÕES              '\n");
        printf("'         Digite 5 para acessar o menu de CLIENTES               '\n");
        printf("'         Digite 6 para acessar o menu de ELOGIOS                '\n");
        printf("'         Digite 7 para acessar o menu de RECLAMAÇÕES            '\n");
        printf("'         Digite 8 para acessar o menu de USUÁRIOS               '\n");
        printf("'         Digite 9 para acessar o menu de RELATÓRIOS             '\n");
        printf("'                                                                '\n");
        printf("'         Digite 0 para deslogar                                 '\n");
        printf("'                                                                '\n");
        printf("'----------------------------------------------------------------'\n");
        printf("Opção escolhida: ");

        scanf("%d", &opcaoEscolhida);

        system("clear");

        switch(opcaoEscolhida) {
            case 0: //sair
                sair();
                break;
            case 1: //pizzas
                exibirMenuPizzas();
                break;
            case 2: //bebidas
                exibirMenuBebidas();
                break;
            case 3: //pedidos
                exibirMenuPedidos();
                break;
            case 4: //promoções
                exibirMenuPromocoes();
                break;
            case 5: //clientes
                exibirMenuClientes();
                break;
            case 6: //elogios
                exibirMenuElogios();
                break;
            case 7: //reclamações
                exibirMenuReclamacoes();
                break;
            case 8: //usuários
                exibirMenuUsuarios();
                break;
            case 9: //relatórios
                exibirMenuRelatorios();
                break;
            case 10: //logs
                break;
            default:
                printf("\n\nEscolha uma opção válida!");
                break;
        }
    } while(opcaoEscolhida != 0);
}

void exibirMenuBebidas() {
    int opcaoEscolhida;
    do {
        printf("\n\n'---------------------------[BEBIDAS]----------------------------'\n");
        printf("'                                                                '\n");
        printf("'                 1 - Visualizar                                 '\n");
        printf("'                 2 - Adicionar                                  '\n");
        printf("'                 3 - Editar                                     '\n");
        printf("'                 4 - Remover                                    '\n");
        printf("'                                                                '\n");
        printf("'                 0 - Voltar ao menu principal                   '\n");
        printf("'                                                                '\n");
        printf("'----------------------------------------------------------------'\n");
        printf("Opção escolhida: ");

        scanf("%d", &opcaoEscolhida);

        system("clear");

        switch(opcaoEscolhida) {
            case 0:
                break;
            case 1:
                // Visualizar
                visualizarBebidas();
                break;
            case 2:
                // Adicionar
                adicionarBebidas();
                break;
            case 3:
                // Editar
                editarBebidas();
                break;
            case 4:
                // Remover
                removerBebidas();
                break;
            default:
                printf("\n\nEscolha uma opção válida!\n\n");
                break;
        }

    } while(opcaoEscolhida != 0);
}

void exibirMenuClientes() {
    int opcaoEscolhida;
    do {
        printf("\n\n'---------------------------[CLIENTES]---------------------------'\n");
        printf("'                                                                '\n");
        printf("'                 1 - Visualizar                                 '\n");
        printf("'                 2 - Adicionar                                  '\n");
        printf("'                 3 - Editar                                     '\n");
        printf("'                 4 - Remover                                    '\n");
        printf("'                                                                '\n");
        printf("'                 0 - Voltar ao menu principal                   '\n");
        printf("'                                                                '\n");
        printf("'----------------------------------------------------------------'\n");
        printf("Opção escolhida: ");

        scanf("%d", &opcaoEscolhida);

        system("clear");

        switch(opcaoEscolhida) {
            case 0:
                break;
            case 1:
                // Visualizar
                visualizarClientes();
                break;
            case 2:
                // Adicionar
                adicionarClientes();
                break;
            case 3:
                // Editar
                editarClientes();
                break;
            case 4:
                // Remover
                removerClientes();
                break;
            default:
                printf("\n\nEscolha uma opção válida!\n\n");
                break;
        }

    } while(opcaoEscolhida != 0);
}

void exibirMenuElogios() {
    int opcaoEscolhida;
    do {
        printf("\n\n'---------------------------[ELOGIOS]----------------------------'\n");
        printf("'                                                                '\n");
        printf("'                 1 - Visualizar                                 '\n");
        printf("'                 2 - Adicionar                                  '\n");
        printf("'                 3 - Editar                                     '\n");
        printf("'                 4 - Remover                                    '\n");
        printf("'                                                                '\n");
        printf("'                 0 - Voltar ao menu principal                   '\n");
        printf("'                                                                '\n");
        printf("'----------------------------------------------------------------'\n");
        printf("Opção escolhida: ");

        scanf("%d", &opcaoEscolhida);

        system("clear");

        switch(opcaoEscolhida) {
            case 0:
                break;
            case 1:
                // Visualizar
                visualizarElogios();
                break;
            case 2:
                // Adicionar
                adicionarElogios();
                break;
            case 3:
                // Editar
                editarElogios();
                break;
            case 4:
                // Remover
                removerElogios();
                break;
            default:
                printf("\n\nEscolha uma opção válida!\n\n");
                break;
        }
    } while(opcaoEscolhida != 0);
}

void exibirMenuFuncionario() {
    int opcaoEscolhida;
    do {
        printf("\n\n'--------------------[MENU DE FUNCIONÁRIO]-----------------------'\n");
        printf("'                                                                '\n");
        printf("'         Digite 1 para acessar o menu de PIZZAS                 '\n");
        printf("'         Digite 2 para acessar o menu de BEBIDAS                '\n");
        printf("'         Digite 3 para acessar o menu de PEDIDOS                '\n");
        printf("'         Digite 4 para acessar o menu de PROMOÇÕES              '\n");
        printf("'         Digite 5 para acessar o menu de CLIENTES               '\n");
        printf("'         Digite 6 para acessar o menu de ELOGIOS                '\n");
        printf("'         Digite 7 para acessar o menu de RECLAMAÇÕES            '\n");
        printf("'                                                                '\n");
        printf("'         Digite 0 para deslogar                                 '\n");
        printf("'                                                                '\n");
        printf("'----------------------------------------------------------------'\n");
        printf("Opção escolhida: ");

        scanf("%d", &opcaoEscolhida);

        system("clear");

        switch(opcaoEscolhida) {
            case 0: //sair
                sair();
                break;
            case 1: //pizzas
                exibirMenuPizzas();
                break;
            case 2: //bebidas
                exibirMenuBebidas();
                break;
            case 3: //pedidos
                exibirMenuPedidos();
                break;
            case 4: //promoções
                exibirMenuPromocoes();
                break;
            case 5: //clientes
                exibirMenuClientes();
                break;
            case 6: //elogios
                exibirMenuElogios();
                break;
            case 7: //reclamações
                exibirMenuReclamacoes();
                break;
            default:
                printf("\n\nEscolha uma opção válida!");
                break;
        }
    } while(opcaoEscolhida != 0);
}

void exibirMenuLogin() {
    int opcaoEscolhida;
    do {
        printf("'-----------------------[MENU DE LOGIN]--------------------------'\n");
        printf("'                                                                '\n");
        printf("'      Digite 1 para logar-se como ADMINISTRADOR                 '\n");
        printf("'      Digite 2 para logar-se como FUNCIONÁRIO                   '\n");
        printf("'                                                                '\n");
        printf("'      Digite 0 para sair do sistema da pizzaria Degust          '\n");
        printf("'                                                                '\n");
        printf("'----------------------------------------------------------------'\n");
        printf("Opção escolhida: ");

        scanf("%d", &opcaoEscolhida);

        system("clear");

        switch(opcaoEscolhida) {
            case 0:
                sair();
                break;
            case 1: 
                // Logar como administrador
                logarNoSistema(1);
                break;
            case 2:
                //Logar como funcionário
                logarNoSistema(2);
                break;
            default:
                printf("\n\nEscolha uma opção válida!\n\n");
                break;
        }   
    } while(opcaoEscolhida != 0);
}

void exibirMenuPedidos() {
    int opcaoEscolhida;
    do {
        printf("\n\n'---------------------------[PEDIDOS]----------------------------'\n");
        printf("'                                                                '\n");
        printf("'                 1 - Visualizar pedidos                         '\n");
        printf("'                 2 - Adicionar novo pedido                      '\n");
        printf("'                 3 - Adicionar item a um pedido                 '\n");
        printf("'                 4 - Remover item de um pedido                  '\n");
        printf("'                 5 - Finalizar pedido                           '\n");
        printf("'                 6 - Cancelar pedido                            '\n");
        printf("'                                                                '\n");
        printf("'                 0 - Voltar ao menu principal                   '\n");
        printf("'                                                                '\n");
        printf("'----------------------------------------------------------------'\n");
        printf("Opção escolhida: ");

        scanf("%d", &opcaoEscolhida);

        system("clear");

        switch(opcaoEscolhida) {
            case 0:
                break;
            case 1:
                // Visualizar pedidos
                visualizarPedidos();
                break;
            case 2:
                // Adicionar novo pedido
                adicionarPedidos();
                break;
            case 3:
                // Adicionar item a um pedido
                adicionarItensPedidos();
                break;
            case 4:
                // Remover item de um pedido
                removerItensPedidos();
                break;
            case 5:
                // Finalizar pedido
                editarPedidos(2);
                break;
            case 6:
                // Cancelar pedido
                editarPedidos(3);
                break;
            default:
                printf("\n\nEscolha uma opção válida!\n\n");
                break;
        }

    } while(opcaoEscolhida != 0);
}

void exibirMenuPromocoes() {
    int opcaoEscolhida;
    do {
        printf("\n\n'--------------------------[PROMOÇÕES]---------------------------'\n");
        printf("'                                                                '\n");
        printf("'                 1 - Visualizar                                 '\n");
        printf("'                 2 - Adicionar                                  '\n");
        printf("'                 3 - Editar                                     '\n");
        printf("'                 4 - Remover                                    '\n");
        printf("'                                                                '\n");
        printf("'                 0 - Voltar ao menu principal                   '\n");
        printf("'                                                                '\n");
        printf("'----------------------------------------------------------------'\n");
        printf("Opção escolhida: ");

        scanf("%d", &opcaoEscolhida);

        system("clear");

        switch(opcaoEscolhida) {
            case 0:
                break;
            case 1:
                // Visualizar
                visualizarPromocoes();
                break;
            case 2:
                // Adicionar
                adicionarPromocoes();
                break;
            case 3:
                // Editar
                editarPromocoes();
                break;
            case 4:
                // Remover
                removerPromocoes();
                break;
            default:
                printf("\n\nEscolha uma opção válida!\n\n");
                break;
        }
    } while(opcaoEscolhida != 0);
}

void exibirMenuReclamacoes() {
    int opcaoEscolhida;
    do {
        printf("\n\n'-------------------------[RECLAMAÇÕES]--------------------------'\n");
        printf("'                                                                '\n");
        printf("'                 1 - Visualizar                                 '\n");
        printf("'                 2 - Adicionar                                  '\n");
        printf("'                 3 - Editar                                     '\n");
        printf("'                 4 - Remover                                    '\n");
        printf("'                                                                '\n");
        printf("'                 0 - Voltar ao menu principal                   '\n");
        printf("'                                                                '\n");
        printf("'----------------------------------------------------------------'\n");
        printf("Opção escolhida: ");

        scanf("%d", &opcaoEscolhida);

        system("clear");

        switch(opcaoEscolhida) {
            case 0:
                break;
            case 1:
                // Visualizar
                visualizarReclamacoes();
                break;
            case 2:
                // Adicionar
                adicionarReclamacoes();
                break;
            case 3:
                // Editar
                editarReclamacoes();
                break;
            case 4:
                // Remover
                removerReclamacoes();
                break;
            default:
                printf("\n\nEscolha uma opção válida!\n\n");
                break;
        }

    } while(opcaoEscolhida != 0);
}

void exibirMenuRelatorios() {
    int opcaoEscolhida;
    do {
        printf("\n\n'-------------------------[RELATÓRIOS]-------------------------'\n");
        printf("'                                                                '\n");
        printf("'             1 - Sabores mais pedidos por unidade da rede       '\n");
        printf("'             2 - Unidade da rede que mais vende                 '\n");
        printf("'             3 - Faturamento (diário) por unidade               '\n");
        printf("'             4 - Faturamento (mensal) por unidade               '\n");
        printf("'             5 - Faturamento (diário) por total da rede         '\n");
        printf("'             6 - Faturamento (mensal) por total da rede         '\n");
        printf("'                                                                '\n");
        printf("'             0 - Voltar ao menu principal                       '\n");
        printf("'                                                                '\n");
        printf("'----------------------------------------------------------------'\n");
        printf("Opção escolhida: ");

        scanf("%d", &opcaoEscolhida);

        system("clear");

        switch(opcaoEscolhida) {
            case 0:
                break;
            case 1:
                // Sabores mais pedidos por unidade da rede
                relatorioUm();
                break;
            case 2:
                // Unidade da rede que mais vende
                relatorioDois();
                break;
            case 3:
                // Faturamento (diário) por unidade
                relatorioTres();
                break;
            case 4:
                relatorioQuatro();
                // Faturamento (mensal) por unidade
                break;
            case 5:
                relatorioCinco();
                // Faturamento (diário) por total da rede
                break;
            case 6:
                relatorioSeis();
                // Faturamento (mensal) por total da rede
                break;
            default:
                printf("\n\nEscolha uma opção válida!\n\n");
                break;
        }

    } while(opcaoEscolhida != 0);
}

void exibirMenuPizzas() {
    int opcaoEscolhida;
    do {
        printf("\n\n'----------------------------[PIZZAS]----------------------------'\n");
        printf("'                                                                '\n");
        printf("'                 1 - Visualizar                                 '\n");
        printf("'                 2 - Adicionar                                  '\n");
        printf("'                 3 - Editar                                     '\n");
        printf("'                 4 - Remover                                    '\n");
        printf("'                                                                '\n");
        printf("'                 0 - Voltar ao menu principal                   '\n");
        printf("'                                                                '\n");
        printf("'----------------------------------------------------------------'\n");
        printf("Opção escolhida: ");

        scanf("%d", &opcaoEscolhida);

        system("clear");

        switch(opcaoEscolhida) {
            case 0:
                break;
            case 1:
                // Visualizar
                visualizarPizzas();
                break;
            case 2:
                // Adicionar
                adicionarPizzas();
                break;
            case 3:
                // Editar
                editarPizzas();
                break;
            case 4:
                // Remover
                removerPizzas();
                break;
            default:
                printf("\n\nEscolha uma opção válida!\n\n");
                break;
        }

    } while(opcaoEscolhida != 0);
}

void exibirMenuUsuarios() {
    int opcaoEscolhida;
    do {
        printf("\n\n'---------------------------[USUÁRIOS]---------------------------'\n");
        printf("'                                                                '\n");
        printf("'                 1 - Visualizar                                 '\n");
        printf("'                 2 - Adicionar                                  '\n");
        printf("'                 3 - Editar                                     '\n");
        printf("'                 4 - Remover                                    '\n");
        printf("'                                                                '\n");
        printf("'                 0 - Voltar ao menu principal                   '\n");
        printf("'                                                                '\n");
        printf("'----------------------------------------------------------------'\n");
        printf("Opção escolhida: ");

        scanf("%d", &opcaoEscolhida);

        system("clear");

        switch(opcaoEscolhida) {
            case 0:
                break;
            case 1:
                // Visualizar
                visualizarUsuarios();
                break;
            case 2:
                // Adicionar
                adicionarUsuarios();
                break;
            case 3:
                // Editar
                editarUsuarios();
                break;
            case 4:
                // Remover
                removerUsuarios();
                break;
            default:
                printf("\n\nEscolha uma opção válida!\n\n");
                break;
        }

    } while(opcaoEscolhida != 0);
}




// -------------------------------- MANIPULAÇÃO DE RELATÓRIOS --------------------------------
void relatorioUm() { // Sabores mais pedidos por unidade da rede
    Pizza *auxPizzas = pizzas;

    int countPizzas = 0;
    while(auxPizzas != NULL){
        auxPizzas = auxPizzas->proximo;
        countPizzas++;
    }

    QtdPizzasUnidade qtdPizzasUm[countPizzas];
    QtdPizzasUnidade qtdPizzasDois[countPizzas];
    QtdPizzasUnidade qtdPizzasTres[countPizzas];

    auxPizzas = pizzas;

    for (int i = 0; i < countPizzas; i++)
    {
        qtdPizzasUm[i].idPizza = auxPizzas->id;
        strcpy(qtdPizzasUm[i].nomePizza, auxPizzas->nome);
        qtdPizzasUm[i].qtdTotal = 0;

        qtdPizzasDois[i].idPizza = auxPizzas->id;
        strcpy(qtdPizzasDois[i].nomePizza, auxPizzas->nome);
        qtdPizzasDois[i].qtdTotal = 0;

        qtdPizzasTres[i].idPizza = auxPizzas->id;
        strcpy(qtdPizzasTres[i].nomePizza, auxPizzas->nome);
        qtdPizzasTres[i].qtdTotal = 0;

        auxPizzas = auxPizzas->proximo;
    }

    Pedido *auxPedido = pedidos;
    while(auxPedido != NULL) {
        ItemPedido *auxItens = itensPedidos;
        while(auxItens != NULL){

            if(auxItens->idPedido == auxPedido->id) {
                
                if(auxItens->tipoItem == 1) {//pizza

                    if(auxPedido->idPizzaria == 1) {

                        for (int i = 0; i < countPizzas; i++)
                        {
                            if(qtdPizzasUm[i].idPizza == auxItens->idItem) {
                                qtdPizzasUm[i].qtdTotal += 1;
                                break;
                            }
                        }
                    }
                    

                }

            }

            auxItens = auxItens->proximo;

        }
        
        auxPedido = auxPedido->proximo;
    }

    printf("\n\n[-------------- SABORES MAIS PEDIDOS DE CADA PIZZARIA --------------]");
    printf("\n\n");

    printf("\n\n[-------------- RELATÓRIO DA PIZZARIA UM --------------]");
    printf("\n\n");

    printf("%-50s|%-11s", "NOME", "QTD");

    for (int i = 0; i < countPizzas; i++)
    {
        printf("\n%-50s|%-11d", qtdPizzasUm[i].nomePizza, qtdPizzasUm[i].qtdTotal);
    }

    printf("\n\n[-------------- RELATÓRIO DA PIZZARIA DOIS --------------]");
    printf("\n\n");

    printf("%-50s|%-11s", "NOME", "QTD");

    for (int i = 0; i < countPizzas; i++)
    {
        printf("\n%-50s|%-11d", qtdPizzasDois[i].nomePizza, qtdPizzasDois[i].qtdTotal);
    }

    printf("\n\n[-------------- RELATÓRIO DA PIZZARIA TRÊS --------------]");
    printf("\n\n");

    printf("%-50s|%-11s", "NOME", "QTD");

    for (int i = 0; i < countPizzas; i++)
    {
        printf("\n%-50s|%-11d", qtdPizzasTres[i].nomePizza, qtdPizzasTres[i].qtdTotal);
    }

    char qqrTecla[1];
    printf("\n\nDigite qualquer caractere para voltar: ");
    scanf("%s", qqrTecla);
    if(strlen(qqrTecla) > 0) {
        system("clear");
    }
}





void relatorioDois() {// Unidade da rede que mais vende
    int qtdPedidosUm = 0;
    int qtdPedidosDois = 0;
    int qtdPedidosTres = 0;

    Pedido *auxPedido = pedidos;
    while(auxPedido != NULL) {
        if(auxPedido->idPizzaria == 1) {
            qtdPedidosUm++;
        } else if(auxPedido->idPizzaria == 2) {
            qtdPedidosDois++;
        } else if(auxPedido->idPizzaria == 3) {
            qtdPedidosTres++;
        }
        
        auxPedido = auxPedido->proximo;
    }

    printf("\n\n[-------------- RELATÓRIO VENDAS DAS UNIDADES DA REDE --------------]");
    printf("\n\n");

    printf("\n%-10s|%-11s", "PIZZARIA", "QTD PEDIDOS");
    printf("\n%-10d|%-11d", 1, qtdPedidosUm);
    printf("\n%-10d|%-11d", 2, qtdPedidosDois);
    printf("\n%-10d|%-11d", 3, qtdPedidosTres);

    char qqrTecla[1];
    printf("\n\nDigite qualquer caractere para voltar: ");
    scanf("%s", qqrTecla);
    if(strlen(qqrTecla) > 0) {
        system("clear");
    }
}





void relatorioTres() {// Faturamento (diário) por unidade
    float totalPagoUm = 0;
    float totalPagoDois = 0;
    float totalPagoTres = 0;

    Pedido *auxPedido = pedidos;
    while(auxPedido != NULL) {
        ItemPedido *auxItens = itensPedidos;
        float totalGanhosPedidoAtual = 0;

        time_t mytime;
        mytime = time(NULL);
        struct tm tm = *localtime(&mytime);

        if(auxPedido->dataPedido.dia == tm.tm_mday && auxPedido->dataPedido.mes == (tm.tm_mon + 1) && auxPedido->dataPedido.ano == (tm.tm_year + 1900)) {
            while(auxItens != NULL){

                if(auxItens->idPedido == auxPedido->id) {

                    if(auxPedido->status == 3) {

                        totalGanhosPedidoAtual -= (auxItens->preco * 55) / 100;

                    } else if(auxPedido->status == 2) {
                        if(auxItens->promocao == 1) {
                            float valorDesconto = (auxItens->preco * auxItens->valorPromocao) / 100;
                            float precoComDesconto = ((auxItens->preco * 55) / 100) - valorDesconto;

                            totalGanhosPedidoAtual += precoComDesconto;
                        } else {
                            totalGanhosPedidoAtual += (auxItens->preco * 55) / 100;
                        }
                    }

                }

                auxItens = auxItens->proximo;

            }

            if(auxPedido->idPizzaria == 1) {
                totalPagoUm += totalGanhosPedidoAtual;
            } else if(auxPedido->idPizzaria == 2) {
                totalPagoDois += totalGanhosPedidoAtual;
            } else if(auxPedido->idPizzaria == 3) {
                totalPagoTres += totalGanhosPedidoAtual;
            }
        }
        
        auxPedido = auxPedido->proximo;
    }

    printf("\n\n[-------------- RELATÓRIO FATURAMENTO DIÁRIO POR UNIDADE --------------]");
    printf("\n\n");

    printf("\n%-10s|%-11s", "PIZZARIA", "TOTAL GANHOS");
    printf("\n%-10d|R$ %-2.f", 1, totalPagoUm);
    printf("\n%-10d|R$ %-2.f", 2, totalPagoDois);
    printf("\n%-10d|R$ %-2.f", 3, totalPagoTres);

    char qqrTecla[1];
    printf("\n\nDigite qualquer caractere para voltar: ");
    scanf("%s", qqrTecla);
    if(strlen(qqrTecla) > 0) {
        system("clear");
    }
}




void relatorioQuatro() {// Faturamento (mensal) por unidade
    float totalPagoUm = 0;
    float totalPagoDois = 0;
    float totalPagoTres = 0;

    Pedido *auxPedido = pedidos;
    while(auxPedido != NULL) {
        ItemPedido *auxItens = itensPedidos;
        float totalGanhosPedidoAtual = 0;

        time_t mytime;
        mytime = time(NULL);
        struct tm tm = *localtime(&mytime);

        if(auxPedido->dataPedido.mes == (tm.tm_mon + 1) && auxPedido->dataPedido.ano == (tm.tm_year + 1900)) {
            while(auxItens != NULL){

                if(auxItens->idPedido == auxPedido->id) {

                    if(auxPedido->status == 3) {

                        totalGanhosPedidoAtual -= (auxItens->preco * 55) / 100;

                    } else if(auxPedido->status == 2) {
                        if(auxItens->promocao == 1) {
                            float valorDesconto = (auxItens->preco * auxItens->valorPromocao) / 100;
                            float precoComDesconto = ((auxItens->preco * 55) / 100) - valorDesconto;

                            totalGanhosPedidoAtual += precoComDesconto;
                        } else {
                            totalGanhosPedidoAtual += (auxItens->preco * 55) / 100;
                        }
                    }

                }

                auxItens = auxItens->proximo;

            }

            if(auxPedido->idPizzaria == 1) {
                totalPagoUm += totalGanhosPedidoAtual;
            } else if(auxPedido->idPizzaria == 2) {
                totalPagoDois += totalGanhosPedidoAtual;
            } else if(auxPedido->idPizzaria == 3) {
                totalPagoTres += totalGanhosPedidoAtual;
            }
        }
        
        auxPedido = auxPedido->proximo;
    }

    printf("\n\n[-------------- RELATÓRIO FATURAMENTO MENSAL POR UNIDADE --------------]");
    printf("\n\n");

    printf("\n%-10s|%-11s", "PIZZARIA", "TOTAL GANHOS");
    printf("\n%-10d|R$ %-2.f", 1, totalPagoUm);
    printf("\n%-10d|R$ %-2.f", 2, totalPagoDois);
    printf("\n%-10d|R$ %-2.f", 3, totalPagoTres);

    char qqrTecla[1];
    printf("\n\nDigite qualquer caractere para voltar: ");
    scanf("%s", qqrTecla);
    if(strlen(qqrTecla) > 0) {
        system("clear");
    }
}




void relatorioCinco() {// Faturamento (diário) por total da rede
    float totalPagoTodos = 0;

    Pedido *auxPedido = pedidos;
    while(auxPedido != NULL) {
        ItemPedido *auxItens = itensPedidos;
        float totalGanhosPedidoAtual = 0;

        time_t mytime;
        mytime = time(NULL);
        struct tm tm = *localtime(&mytime);

        if(auxPedido->dataPedido.dia == tm.tm_mday && auxPedido->dataPedido.mes == (tm.tm_mon + 1) && auxPedido->dataPedido.ano == (tm.tm_year + 1900)) {
            while(auxItens != NULL){

                if(auxItens->idPedido == auxPedido->id) {

                    if(auxPedido->status == 3) {

                        totalGanhosPedidoAtual -= (auxItens->preco * 55) / 100;

                    } else if(auxPedido->status == 2) {
                        if(auxItens->promocao == 1) {
                            float valorDesconto = (auxItens->preco * auxItens->valorPromocao) / 100;
                            float precoComDesconto = ((auxItens->preco * 55) / 100) - valorDesconto;

                            totalGanhosPedidoAtual += precoComDesconto;
                        } else {
                            totalGanhosPedidoAtual += (auxItens->preco * 55) / 100;
                        }
                    }

                }

                auxItens = auxItens->proximo;

            }

            totalPagoTodos += totalGanhosPedidoAtual;
        }
        
        auxPedido = auxPedido->proximo;
    }

    printf("\n\n[-------------- RELATÓRIO FATURAMENTO DIÁRO POR TOTAL DA REDE --------------]");
    printf("\n\n");

    printf("\n%-10s|%-11s", "PIZZARIA", "TOTAL GANHOS");
    printf("\n%-10s|R$ %-2.f", "TODAS", totalPagoTodos);

    char qqrTecla[1];
    printf("\n\nDigite qualquer caractere para voltar: ");
    scanf("%s", qqrTecla);
    if(strlen(qqrTecla) > 0) {
        system("clear");
    }
}




void relatorioSeis() {// Faturamento (mensal) por total da rede
    float totalPagoTodos = 0;

    Pedido *auxPedido = pedidos;
    while(auxPedido != NULL) {
        ItemPedido *auxItens = itensPedidos;
        float totalGanhosPedidoAtual = 0;

        time_t mytime;
        mytime = time(NULL);
        struct tm tm = *localtime(&mytime);

        if(auxPedido->dataPedido.mes == (tm.tm_mon + 1) && auxPedido->dataPedido.ano == (tm.tm_year + 1900)) {
            while(auxItens != NULL){

                if(auxItens->idPedido == auxPedido->id) {

                    if(auxPedido->status == 3) {

                        totalGanhosPedidoAtual -= (auxItens->preco * 55) / 100;

                    } else if(auxPedido->status == 2) {
                        if(auxItens->promocao == 1) {
                            float valorDesconto = (auxItens->preco * auxItens->valorPromocao) / 100;
                            float precoComDesconto = ((auxItens->preco * 55) / 100) - valorDesconto;

                            totalGanhosPedidoAtual += precoComDesconto;
                        } else {
                            totalGanhosPedidoAtual += (auxItens->preco * 55) / 100;
                        }
                    }

                }

                auxItens = auxItens->proximo;

            }

            totalPagoTodos += totalGanhosPedidoAtual;
        }
        
        auxPedido = auxPedido->proximo;
    }

    printf("\n\n[-------------- RELATÓRIO FATURAMENTO DIÁRO POR TOTAL DA REDE --------------]");
    printf("\n\n");

    printf("\n%-10s|%-11s", "PIZZARIA", "TOTAL GANHOS");
    printf("\n%-10s|R$ %-2.f", "TODAS", totalPagoTodos);

    char qqrTecla[1];
    printf("\n\nDigite qualquer caractere para voltar: ");
    scanf("%s", qqrTecla);
    if(strlen(qqrTecla) > 0) {
        system("clear");
    }
}





// -------------------------------- MANIPULAÇÃO DE ARQUIVOS --------------------------------

// -------------------------------- MANIPULAÇÃO DE ARQUIVOS: BEBIDAS --------------------------------
void adicionarBebidas() {
    printf("\nAdicionar nova bebida");
    Bebida *nova  = (Bebida*) malloc(sizeof(Bebida));

    getchar();

    //Verificar se é nome repetido
    Bebida *auxVerifica = bebidas;
    if(auxVerifica == NULL) {
        printf("\nDigite o nome da bebida: ");
        fgets(nova->nome, sizeof(nova->nome), stdin); 
        strtok(nova->nome, "\n");
    }
    else if(auxVerifica->proximo == NULL) {
        do {
            printf("\nDigite o nome da bebida: ");
            fgets(nova->nome, sizeof(nova->nome), stdin); 
            strtok(nova->nome, "\n");

            if(strcmp(nova->nome, auxVerifica->nome) == 0) {
                system("clear");
                printf("\n\nNome da bebida já existente, entre com outro nome.");
            }
        } while(strcmp(nova->nome, auxVerifica->nome) == 0);
    } else if(bebidas != NULL) {
        bool continua = 0;
        do {
            auxVerifica = bebidas;
            continua = 0;
            printf("\nDigite o nome da bebida: ");
            fgets(nova->nome, sizeof(nova->nome), stdin); 
            strtok(nova->nome, "\n");

            while(auxVerifica != NULL) {
                if(strcmp(nova->nome, auxVerifica->nome) == 0) {
                    system("clear");
                    printf("\nNome da bebida já existente, entre com outro nome.");
                    continua = 1;
                    break;
                }

                auxVerifica = auxVerifica->proximo;
            }
        } while(continua == 1);
    } else {
        printf("\nDigite o nome da bebida: ");
        fgets(nova->nome, sizeof(nova->nome), stdin); 
        strtok(nova->nome, "\n");
    }

    printf("Digite a descrição: ");
    fgets(nova->descricao, sizeof(nova->descricao), stdin);
    strtok(nova->descricao, "\n");

    printf("Digite o preço: ");
    scanf("%f", &nova->preco);

    nova->promocao = 0;
    nova->valorPromocao = 0;

    system("clear");

    if(bebidas == NULL) {
        nova->id = 1;
        bebidas = nova;
        bebidas->proximo = NULL;
    } else {
        Bebida *aux = bebidas;
        while(aux->proximo != NULL) {
            aux = aux->proximo;
        }
        
        nova->id = aux->id + 1;

        aux->proximo = nova;

        aux->proximo->proximo = NULL;
    }
    salvarBebidas();
}

void carregaBebidas() {
    Bebida *bebida; 
    FILE *arq = fopen(dbBebidas,"r+b");    
    if (arq == NULL)
    {
        //printf("Erro ao abrir arquivo\n");
        return;
    }
    
    while (!feof(arq))
    {   
        bebida = (Bebida*) malloc(sizeof(Bebida));
        int qtd = fread(bebida,sizeof(Bebida),1,arq);
        if(qtd > 0){
            if(bebidas == NULL){
                bebidas = bebida;
                bebida->proximo = NULL;
            }        
            else {
                bebida->proximo = NULL;
                Bebida *aux = bebidas;

                while(aux->proximo != NULL) {
                    aux = aux->proximo;
                }

                aux->proximo = bebida;
            }
        }
    }   
    fclose(arq);
}

void editarBebidas() {
    bool continua = 0;
    
    do {
        Bebida *aux = bebidas;
        continua = 0;
        printf("\n\nEditar uma bebida");
        printf("\n\n\n%-5s|%-50s|%-11s|%-100s\n\n", "ID", "NOME", "PREÇO", "DESCRIÇÃO");
        while(aux != NULL){
            printf("%-5d|%-50s|%-11g|%-100s\n", aux->id, aux->nome, aux->preco, aux->descricao);
            aux = aux->proximo;
        }

        int idBebidaEditar;
        printf("\nInforme um ID de bebida para editar ou digite 0 para voltar: ");
        scanf("%d", &idBebidaEditar);
        
        system("clear");

        if(idBebidaEditar != 0) {
            Bebida *retornoBebida = buscarBebidaPeloId(idBebidaEditar);

            if(retornoBebida == NULL) {
                printf("O ID informado (%d) não existe", idBebidaEditar);
                continua = 1;
                continue;
            } else {
                int opcaoEscolhida;

                printf("\nO que você deseja editar?");
                printf("\n\nDigite 1 para PREÇO");
                printf("\nDigite 2 para DESCRIÇÃO");
                printf("\nDigite 0 para voltar");
                printf("\n\nOpção escolhida: ");
                scanf("%d", &opcaoEscolhida);

                system("clear");

                switch (opcaoEscolhida)
                {
                    case 0:
                        continua = 1;
                        break;
                    case 1:
                        printf("\nInsira um novo preço para a bebida %s: ", retornoBebida->nome);
                        
                        scanf("%f", &retornoBebida->preco);

                        system("clear");
                        break;
                    case 2:
                        printf("\nInsira uma nova descrição para a bebida %s: ", retornoBebida->nome);

                        getchar();
                        fgets(retornoBebida->descricao, sizeof(retornoBebida->descricao), stdin);
                        strtok(retornoBebida->descricao, "\n");

                        system("clear");
                        break;
                    default:
                        continua = 1;
                        printf("\nOpção inválida");
                        break;
                }
                
                salvarBebidas();
            }
        } else {
            continua = 0;
        }

    } while(continua == 1);
}

void removerBebidas() {
    bool continua = 0;
    
    do {
        Bebida *aux = bebidas;
        printf("\n\nRemover uma bebida");
        printf("\n\n\n%-5s|%-50s|%-11s|%-100s\n\n", "ID", "NOME", "PREÇO", "DESCRIÇÃO");
        while(aux != NULL){
            printf("%-5d|%-50s|%-11g|%-100s\n", aux->id, aux->nome, aux->preco, aux->descricao);
            aux = aux->proximo;
        }

        int idBebidaRemover;
        printf("\nInforme um ID de bebida para remover ou digite 0 para voltar: ");
        scanf("%d", &idBebidaRemover);
        
        system("clear");

        if(idBebidaRemover != 0) {
            Bebida *retornoBebida = buscarBebidaPeloId(idBebidaRemover);

            if(retornoBebida == NULL) {
                printf("O ID informado (%d) não existe", idBebidaRemover);
                continua = 1;
                continue;
            } else {
                printf("\n*** ATENÇÃO ***");
                printf("\nDeseja realmente remover a bebida %d?", idBebidaRemover);
                printf("\n\n\n%-5s|%-50s|%-11s|%-100s\n\n", "ID", "NOME", "PREÇO", "DESCRIÇÃO");
                printf("%-5d|%-50s|%-11g|%-100s\n", retornoBebida->id, retornoBebida->nome, retornoBebida->preco, retornoBebida->descricao);

                int confirmaRemocao;

                printf("\nDigite 1 para SIM");
                printf("\nDigite 0 para CANCELAR");
                printf("\n\nOpção escolhida: ");
                scanf("%d", &confirmaRemocao);

                system("clear");

                if(confirmaRemocao == 0) {
                    continua = 1;
                    continue;
                } else if(confirmaRemocao == 1) {                    
                    Bebida *aux = bebidas;

                    if(aux->id == idBebidaRemover) {
                        bebidas = aux->proximo;

                    } else {
                        while(aux->proximo != NULL){
                            Bebida *anterior = aux;
                            Bebida *atual = aux->proximo;
                            Bebida *proximo = atual->proximo;
                            
                            if(atual->id == idBebidaRemover) {
                                anterior->proximo = proximo;
                                break;
                            }

                            aux = aux->proximo;
                        }
                    }
                    
                    salvarBebidas();
                } else {
                    continua = 0;
                }
            }
        } else {
            continua = 0;
        }

    } while(continua == 1);
}

void salvarBebidas() {
    Bebida *aux = bebidas;
    FILE *arq = fopen(dbBebidas,"wb");
    if (arq == NULL)
    {
        //printf("Erro ao abrir arquivo\n");
        exit(1);
    }
    while (aux != NULL){        
        fwrite(aux,sizeof(Bebida),1,arq);
        aux = aux->proximo;
    }
    fclose(arq);
}

void visualizarBebidas() {
    Bebida *aux = bebidas;
    printf("\nTodas as bebidas");
    printf("\n\n\n%-5s|%-50s|%-11s|%-100s\n\n", "ID", "NOME", "PREÇO", "DESCRIÇÃO");
    while(aux != NULL){
        printf("%-5d|%-50s|%-11g|%-100s\n", aux->id, aux->nome, aux->preco, aux->descricao);
        aux = aux->proximo;
    }

    char qqrTecla[1];
    printf("\nDigite qualquer caractere para voltar: ");
    scanf("%s", qqrTecla);
    if(strlen(qqrTecla) > 0) {
        system("clear");
    }
}

Bebida *buscarBebidaPeloId(int idBebida) {
    Bebida *aux = bebidas;

    while(aux != NULL){
        if(aux->id == idBebida) {
            return aux;
        }
        
        aux = aux->proximo;
    }

    return NULL;
}




// -------------------------------- MANIPULAÇÃO DE ARQUIVOS: CLIENTES --------------------------------
void adicionarClientes() {
    printf("\nAdicionar novo cliente");
    Cliente *nova  = (Cliente*) malloc(sizeof(Cliente));

    getchar();
    printf("\nDigite o nome do cliente: ");
    fgets(nova->nome, sizeof(nova->nome), stdin);
    strtok(nova->nome, "\n");

    //Verificar se é cpf repetido
    Cliente *auxVerifica = clientes;
    if(auxVerifica == NULL) {
        printf("\nDigite o CPF do cliente (somente números): ");
        scanf("%ld", &nova->cpf);
    }
    else if(auxVerifica->proximo == NULL) {
        do {
            printf("\nDigite o CPF do cliente (somente números): ");
            scanf("%ld", &nova->cpf);

            if(nova->cpf == auxVerifica->cpf) {
                system("clear");
                printf("\n\nCPF já existente, entre com outro CPF.");
            }
        } while(nova->cpf == auxVerifica->cpf);
    } else if(clientes != NULL) {
        bool continua = 0;
        do {
            auxVerifica = clientes;
            continua = 0;
            printf("\nDigite o CPF do cliente (somente números): ");
            scanf("%ld", &nova->cpf);

            while(auxVerifica != NULL) {
                if(nova->cpf == auxVerifica->cpf) {
                    system("clear");
                    printf("\nCPF já existente, entre com outro CPF.");
                    continua = 1;
                    break;
                }

                auxVerifica = auxVerifica->proximo;
            }
        } while(continua == 1);
    } else {
        printf("\nDigite o CPF do cliente: ");
        scanf("%ld", &nova->cpf);
    }

    nova->qtdPizzasCompradas = 0;

    system("clear");

    if(clientes == NULL) {
        nova->id = 1;
        clientes = nova;
        clientes->proximo = NULL;
    } else {
        Cliente *aux = clientes;
        while(aux->proximo != NULL) {
            aux = aux->proximo;
        }
        
        nova->id = aux->id + 1;

        aux->proximo = nova;

        aux->proximo->proximo = NULL;
    }
    salvarClientes();
}

void carregaClientes() {
    Cliente *cliente; 
    FILE *arq = fopen(dbClientes,"r+b");    
    if (arq == NULL)
    {
        //printf("Erro ao abrir arquivo\n");
        return;
    }
    
    while (!feof(arq))
    {   
        cliente = (Cliente*) malloc(sizeof(Cliente));
        int qtd = fread(cliente,sizeof(Cliente),1,arq);
        if(qtd > 0){
            if(clientes == NULL){
                clientes = cliente;
                cliente->proximo = NULL;
            }        
            else {
                cliente->proximo = NULL;
                Cliente *aux = clientes;

                while(aux->proximo != NULL) {
                    aux = aux->proximo;
                }

                aux->proximo = cliente;
            }
        }
    }
    fclose(arq);
}

void editarClientes() {
    bool continua = 0;
    
    do {
        Cliente *aux = clientes;
        continua = 0;
        printf("\n\nEditar um cliente");
        printf("\n\n\n%-5s|%-50s|%-13s|%-11s\n\n", "ID", "NOME", "CPF", "QTD PIZZAS");
        while(aux != NULL){
            printf("%-5d|%-50s|%-13ld|%-11d\n", aux->id, aux->nome, aux->cpf, aux->qtdPizzasCompradas);
            aux = aux->proximo;
        }

        int idClienteEditar;
        printf("\nInforme um ID de cliente para editar ou digite 0 para voltar: ");
        scanf("%d", &idClienteEditar);
        
        system("clear");

        if(idClienteEditar != 0) {
            Cliente *retornoCliente = buscarClientePeloId(idClienteEditar);

            if(retornoCliente == NULL) {
                printf("O ID informado (%d) não existe", idClienteEditar);
                continua = 1;
                continue;
            } else {
                int opcaoEscolhida;

                printf("\nO que você deseja editar?");
                printf("\n\nDigite 1 para NOME");
                printf("\nDigite 0 para voltar");
                printf("\n\nOpção escolhida: ");
                scanf("%d", &opcaoEscolhida);

                system("clear");

                switch (opcaoEscolhida)
                {
                    case 0:
                        continua = 1;
                        break;
                    case 1:
                        printf("\nInsira um novo nome para o cliente %s: ", retornoCliente->nome);

                        getchar();
                        fgets(retornoCliente->nome, sizeof(retornoCliente->nome), stdin);
                        strtok(retornoCliente->nome, "\n");

                        system("clear");
                        break;
                    default:
                        continua = 1;
                        printf("\nOpção inválida");
                        break;
                }
                
                salvarClientes();
            }
        } else {
            continua = 0;
        }

    } while(continua == 1);
}

void removerClientes() {
    bool continua = 0;
    
    do {
        Cliente *aux = clientes;
        printf("\n\nRemover um cliente");
        printf("\n\n\n%-5s|%-50s|%-13s|%-11s\n\n", "ID", "NOME", "CPF", "QTD PIZZAS");
        while(aux != NULL){
            printf("%-5d|%-50s|%-13ld|%-11d\n", aux->id, aux->nome, aux->cpf, aux->qtdPizzasCompradas);
            aux = aux->proximo;
        }

        int idClienteRemover;
        printf("\nInforme um ID de cliente para remover ou digite 0 para voltar: ");
        scanf("%d", &idClienteRemover);
        
        system("clear");

        if(idClienteRemover != 0) {
            Cliente *retornoCliente = buscarClientePeloId(idClienteRemover);

            if(retornoCliente == NULL) {
                printf("O ID informado (%d) não existe", idClienteRemover);
                continua = 1;
                continue;
            } else {
                printf("\n*** ATENÇÃO ***");
                printf("\nDeseja realmente remover o cliente %d?", idClienteRemover);
                printf("\n\n\n%-5s|%-50s|%-13s|%-11s\n\n", "ID", "NOME", "CPF", "QTD PIZZAS");
                printf("%-5d|%-50s|%-13ld|%-11d\n", retornoCliente->id, retornoCliente->nome, retornoCliente->cpf, retornoCliente->qtdPizzasCompradas);

                int confirmaRemocao;

                printf("\nDigite 1 para SIM");
                printf("\nDigite 0 para CANCELAR");
                printf("\n\nOpção escolhida: ");
                scanf("%d", &confirmaRemocao);

                system("clear");

                if(confirmaRemocao == 0) {
                    continua = 1;
                    continue;
                } else if(confirmaRemocao == 1) {                    
                    Cliente *aux = clientes;

                    if(aux->id == idClienteRemover) {
                        clientes = aux->proximo;

                    } else {
                        while(aux->proximo != NULL){
                            Cliente *anterior = aux;
                            Cliente *atual = aux->proximo;
                            Cliente *proximo = atual->proximo;
                            
                            if(atual->id == idClienteRemover) {
                                anterior->proximo = proximo;
                                break;
                            }

                            aux = aux->proximo;
                        }
                    }
                    
                    salvarClientes();
                } else {
                    continua = 0;
                }
            }
        } else {
            continua = 0;
        }

    } while(continua == 1);
}

void salvarClientes() {
    Cliente *aux = clientes;
    FILE *arq = fopen(dbClientes,"wb");
    if (arq == NULL)
    {
        //printf("Erro ao abrir arquivo\n");
        exit(1);
    }
    while (aux != NULL){        
        fwrite(aux,sizeof(Cliente),1,arq);
        aux = aux->proximo;
    }
    fclose(arq);
}

void visualizarClientes() {
    Cliente *aux = clientes;
    printf("\nTodos os clientes");
    printf("\n\n\n%-5s|%-50s|%-13s|%-11s\n\n", "ID", "NOME", "CPF", "QTD PIZZAS");
    while(aux != NULL){
        printf("%-5d|%-50s|%-13ld|%-11d\n", aux->id, aux->nome, aux->cpf, aux->qtdPizzasCompradas);
        aux = aux->proximo;
    }

    char qqrTecla[1];
    printf("\nDigite qualquer caractere para voltar: ");
    scanf("%s", qqrTecla);
    if(strlen(qqrTecla) > 0) {
        system("clear");
    }
}

Cliente *buscarClientePeloId(int idCliente) {
    Cliente *aux = clientes;

    while(aux != NULL){
        if(aux->id == idCliente) {
            return aux;
        }
        
        aux = aux->proximo;
    }

    return NULL;
}





// -------------------------------- MANIPULAÇÃO DE ARQUIVOS: ELOGIOS --------------------------------
void adicionarElogios() {
    printf("\nAdicionar novo elogio");
    Elogio *nova  = (Elogio*) malloc(sizeof(Elogio));

    getchar();
    printf("\nDigite a descrição do elogio: ");
    fgets(nova->descricao, sizeof(nova->descricao), stdin);
    strtok(nova->descricao, "\n");

    system("clear");

    if(elogios == NULL) {
        nova->id = 1;
        elogios = nova;
        elogios->proximo = NULL;
    } else {
        Elogio *aux = elogios;
        while(aux->proximo != NULL) {
            aux = aux->proximo;
        }
        
        nova->id = aux->id + 1;

        aux->proximo = nova;

        aux->proximo->proximo = NULL;
    }
    salvarElogios();
}

void carregaElogios() {
    Elogio *elogio; 
    FILE *arq = fopen(dbElogios,"r+b");    
    if (arq == NULL)
    {
        //printf("Erro ao abrir arquivo\n");
        return;
    }
    
    while (!feof(arq))
    {   
        elogio = (Elogio*) malloc(sizeof(Elogio));
        int qtd = fread(elogio,sizeof(Elogio),1,arq);
        if(qtd > 0){
            if(elogios == NULL){
                elogios = elogio;
                elogio->proximo = NULL;
            }        
            else {
                elogio->proximo = NULL;
                Elogio *aux = elogios;

                while(aux->proximo != NULL) {
                    aux = aux->proximo;
                }

                aux->proximo = elogio;
            }
        }
    }
    fclose(arq);
}

void editarElogios() {
    bool continua = 0;
    
    do {
        Elogio *aux = elogios;
        continua = 0;
        printf("\n\nEditar um elogio");
        printf("\n\n\n%-5s|%-200s\n\n", "ID", "DESCRIÇÃO");
        while(aux != NULL){
            printf("%-5d|%-200s\n", aux->id, aux->descricao);
            aux = aux->proximo;
        }

        int idElogioEditar;
        printf("\nInforme um ID de elogio para editar ou digite 0 para voltar: ");
        scanf("%d", &idElogioEditar);
        
        system("clear");

        if(idElogioEditar != 0) {
            Elogio *retornoElogio = buscarElogioPeloId(idElogioEditar);

            if(retornoElogio == NULL) {
                printf("O ID informado (%d) não existe", idElogioEditar);
                continua = 1;
                continue;
            } else {
                int opcaoEscolhida;

                printf("\nO que você deseja editar?");
                printf("\n\nDigite 1 para DESCRIÇÃO");
                printf("\nDigite 0 para voltar");
                printf("\n\nOpção escolhida: ");
                scanf("%d", &opcaoEscolhida);

                system("clear");

                switch (opcaoEscolhida)
                {
                    case 0:
                        continua = 1;
                        break;
                    case 1:
                        printf("\nInsira uma nova descrição para o elogio %d: ", retornoElogio->id);

                        getchar();
                        fgets(retornoElogio->descricao, sizeof(retornoElogio->descricao), stdin);
                        strtok(retornoElogio->descricao, "\n");

                        system("clear");
                        break;
                    default:
                        continua = 1;
                        printf("\nOpção inválida");
                        break;
                }
                
                salvarElogios();
            }
        } else {
            continua = 0;
        }

    } while(continua == 1);
}

void removerElogios() {
    bool continua = 0;
    
    do {
        Elogio *aux = elogios;
        printf("\n\nRemover um elogio");
        printf("\n\n\n%-5s|%-200s\n\n", "ID", "DESCRIÇÃO");
        while(aux != NULL){
            printf("%-5d|%-200s\n", aux->id, aux->descricao);
            aux = aux->proximo;
        }

        int idElogioRemover;
        printf("\nInforme um ID de elogio para remover ou digite 0 para voltar: ");
        scanf("%d", &idElogioRemover);
        
        system("clear");

        if(idElogioRemover != 0) {
            Elogio *retornoElogio = buscarElogioPeloId(idElogioRemover);

            if(retornoElogio == NULL) {
                printf("O ID informado (%d) não existe", idElogioRemover);
                continua = 1;
                continue;
            } else {
                printf("\n*** ATENÇÃO ***");
                printf("\nDeseja realmente remover o elogio %d?", idElogioRemover);
                printf("\n\n\n%-5s|%-200s\n\n", "ID", "DESCRIÇÃO");
                printf("%-5d|%-200s\n", retornoElogio->id, retornoElogio->descricao);

                int confirmaRemocao;

                printf("\nDigite 1 para SIM");
                printf("\nDigite 0 para CANCELAR");
                printf("\n\nOpção escolhida: ");
                scanf("%d", &confirmaRemocao);

                system("clear");

                if(confirmaRemocao == 0) {
                    continua = 1;
                    continue;
                } else if(confirmaRemocao == 1) {                    
                    Elogio *aux = elogios;

                    if(aux->id == idElogioRemover) {
                        elogios = aux->proximo;

                    } else {
                        while(aux->proximo != NULL){
                            Elogio *anterior = aux;
                            Elogio *atual = aux->proximo;
                            Elogio *proximo = atual->proximo;
                            
                            if(atual->id == idElogioRemover) {
                                anterior->proximo = proximo;
                                break;
                            }

                            aux = aux->proximo;
                        }
                    }
                    
                    salvarElogios();
                } else {
                    continua = 0;
                }
            }
        } else {
            continua = 0;
        }

    } while(continua == 1);
}

void salvarElogios() {
    Elogio *aux = elogios;
    FILE *arq = fopen(dbElogios,"wb");
    if (arq == NULL)
    {
        //printf("Erro ao abrir arquivo\n");
        exit(1);
    }
    while (aux != NULL){        
        fwrite(aux,sizeof(Elogio),1,arq);
        aux = aux->proximo;
    }
    fclose(arq);
}

void visualizarElogios() {
    Elogio *aux = elogios;
    printf("\nTodos os elogios");
    printf("\n\n\n%-5s|%-200s\n\n", "ID", "DESCRIÇÃO");
    while(aux != NULL){
        printf("%-5d|%-200s\n", aux->id, aux->descricao);
        aux = aux->proximo;
    }

    char qqrTecla[1];
    printf("\nDigite qualquer caractere para voltar: ");
    scanf("%s", qqrTecla);
    if(strlen(qqrTecla) > 0) {
        system("clear");
    }
}

Elogio *buscarElogioPeloId(int idElogio) {
    Elogio *aux = elogios;

    while(aux != NULL){
        if(aux->id == idElogio) {
            return aux;
        }
        
        aux = aux->proximo;
    }

    return NULL;
}





// -------------------------------- MANIPULAÇÃO DE ARQUIVOS: PEDIDOS --------------------------------
void adicionarPedidos() {
    int tipoPedido;

    do {
        printf("\nAdicionar novo pedido");
        Pedido *nova  = (Pedido*) malloc(sizeof(Pedido));

        printf("\n\nQual será o tipo de pedido?");
        printf("\nDigite 1 para mesa");
        printf("\nDigite 2 para entrega no endereço");
        printf("\nDigite 3 para viagem");
        printf("\nDigite 0 para voltar");
        printf("\n\nOpção escolhida: ");

        scanf("%d", &tipoPedido);

        system("clear");

        if(tipoPedido == 1) {
            int contaCadastrada;
            do {
                printf("\nO cliente tem uma conta cadastrada?");
                printf("\nDigite 1 para SIM");
                printf("\nDigite 2 para NÃO");
                printf("\n\nOpção escolhida: ");
                
                scanf("%d", &contaCadastrada);
                system("clear");

                if(contaCadastrada == 1) {
                    Cliente *aux = clientes;
                    printf("\nTodos os clientes");
                    printf("\n\n\n%-5s|%-50s|%-13s|%-11s\n\n", "ID", "NOME", "CPF", "QTD PIZZAS");
                    while(aux != NULL){
                        printf("%-5d|%-50s|%-13ld|%-11d\n", aux->id, aux->nome, aux->cpf, aux->qtdPizzasCompradas);
                        aux = aux->proximo;
                    }

                    printf("\n\nEscolha o ID referente ao cliente ou digite 0 caso o cliente não esteja cadastrado: ");
                    scanf("%d", &nova->idCliente);   
                    system("clear");                 
                } else if(contaCadastrada == 2){
                    nova->idCliente = 0;
                } else {
                    system("clear");
                    printf("Opção inválida. Entre com uma opção válida.");
                    continue;
                }

                printf("\n\nInsira o número da mesa do cliente: ");
                scanf("%d", &nova->mesa);

                strcpy(nova->endereco, "");
                nova->status = 1;

                tipoPedido = 0;

            }while(contaCadastrada != 1 && contaCadastrada != 2);
        } else if(tipoPedido == 2) {
            int contaCadastrada;
            do {
                printf("\nO cliente tem uma conta cadastrada?");
                printf("\nDigite 1 para SIM");
                printf("\nDigite 2 para NÃO");
                printf("\n\nOpção escolhida: ");
                
                scanf("%d", &contaCadastrada);
                system("clear");

                if(contaCadastrada == 1) {
                    Cliente *aux = clientes;
                    printf("\nTodos os clientes");
                    printf("\n\n\n%-5s|%-50s|%-13s|%-11s\n\n", "ID", "NOME", "CPF", "QTD PIZZAS");
                    while(aux != NULL){
                        printf("%-5d|%-50s|%-13ld|%-11d\n", aux->id, aux->nome, aux->cpf, aux->qtdPizzasCompradas);
                        aux = aux->proximo;
                    }

                    printf("\n\nEscolha o ID referente ao cliente ou digite 0 caso o cliente não esteja cadastrado: ");
                    scanf("%d", &nova->idCliente);
                    system("clear");
                } else if(contaCadastrada == 2){
                    nova->idCliente = 0;
                } else {
                    system("clear");
                    printf("Opção inválida. Entre com uma opção válida.");
                    continue;
                }

                printf("\n\nInsira o endereço completo para entrega: ");
                getchar();
                fgets(nova->endereco, sizeof(nova->endereco), stdin);
                strtok(nova->endereco, "\n");

                nova->mesa = 0;
                nova->status = 1;

                tipoPedido = 0;
            }while(contaCadastrada != 1 && contaCadastrada != 2);
        } else if(tipoPedido == 3) {
            int contaCadastrada;
            do {
                printf("\nO cliente tem uma conta cadastrada?");
                printf("\nDigite 1 para SIM");
                printf("\nDigite 2 para NÃO");
                printf("\n\nOpção escolhida: ");
                
                scanf("%d", &contaCadastrada);
                system("clear");

                if(contaCadastrada == 1) {
                    Cliente *aux = clientes;
                    printf("\nTodos os clientes");
                    printf("\n\n\n%-5s|%-50s|%-13s|%-11s\n\n", "ID", "NOME", "CPF", "QTD PIZZAS");
                    while(aux != NULL){
                        printf("%-5d|%-50s|%-13ld|%-11d\n", aux->id, aux->nome, aux->cpf, aux->qtdPizzasCompradas);
                        aux = aux->proximo;
                    }

                    printf("\n\nEscolha o ID referente ao cliente ou digite 0 caso o cliente não esteja cadastrado: ");
                    scanf("%d", &nova->idCliente);   
                    system("clear");                 
                } else if(contaCadastrada == 2){
                    nova->idCliente = 0;
                } else {
                    system("clear");
                    printf("Opção inválida. Entre com uma opção válida.");
                    continue;
                }

                printf("\n\nDigite o nome do cliente: ");
                getchar();
                fgets(nova->nomeCliente, sizeof(nova->nomeCliente), stdin);
                strtok(nova->nomeCliente, "\n");

                nova->mesa = 0;
                nova->status = 1;
                strcpy(nova->endereco, "");
                tipoPedido = 0;
            }while(contaCadastrada != 1 && contaCadastrada != 2);
        } else if(tipoPedido != 0) {
            system("clear");
            printf("\nOpção inválida. Escolha uma opção valida.");
            continue;
        } else {
            system("clear");
            continue;
        }

        system("clear");
        
        nova->idPizzaria = usuarioLogado.pizzariaTrabalha;

        time_t mytime;
        mytime = time(NULL);
        struct tm tm = *localtime(&mytime);
        nova->dataPedido.ano = tm.tm_year + 1900;
        nova->dataPedido.mes = tm.tm_mon + 1;
        nova->dataPedido.dia = tm.tm_mday;

        if(pedidos == NULL) {
            nova->id = 1;
            pedidos = nova;
            pedidos->proximo = NULL;
        } else {
            Pedido *aux = pedidos;
            while(aux->proximo != NULL) {
                aux = aux->proximo;
            }
            
            nova->id = aux->id + 1;

            aux->proximo = nova;

            aux->proximo->proximo = NULL;
        }
        salvarPedidos();
    } while(tipoPedido != 0);
}

void adicionarItensPedidos() {
    int idPedido;
    do {
        Pedido *aux = pedidos;
        printf("\nTodos os pedidos em andamento");
        printf("\n\n\n%-5s|%-10s|%-6s|%-50s|%-50s|%11s\n\n", "ID", "ID CLIENTE", "MESA", "NOME DO CLIENTE", "ENDEREÇO", "DATA PEDIDO");
        while(aux != NULL){
            if(aux->status == 1 && aux->idPizzaria == usuarioLogado.pizzariaTrabalha) {
                printf("%-5d|%-10d|%-6d|%-50s|%-50s|%d%s%d%s%d\n", aux->id, aux->idCliente, aux->mesa, aux->nomeCliente, aux->endereco, aux->dataPedido.dia, "/", aux->dataPedido.mes, "/", aux->dataPedido.ano);
            }
            
            aux = aux->proximo;
        }

        printf("\nDigite um ID para adicionar itens ou digite 0 para voltar: ");
        scanf("%d", &idPedido);
        system("clear");
        
        if(idPedido == 0) {
            continue;
        } else {

            Pedido *retornoPedido = buscarPedidoPeloId(idPedido);

            if(retornoPedido == NULL || retornoPedido->status != 1) {
                printf("O ID informado (%d) não existe", idPedido);
                continue;
            } else {

                int tipoItem;
                do {
                    printf("\n\nAdicionar item a um pedido");
                    printf("\n\nDigite 1 para adicionar pizza");
                    printf("\nDigite 2 para adicionar bebida");
                    printf("\nDigite 0 para voltar");
                    printf("\n\nOpção escolhida: ");
                    scanf("%d", &tipoItem);
                    system("clear");

                    if(tipoItem == 0) {
                        continue;
                    } else if(tipoItem == 1) {
                        int idPizza;
                        do {
                            Pizza *aux = pizzas;
                            printf("\nTodas as pizzas");
                            printf("\n\n\n%-5s|%-50s|%-11s|%-11s|%-12s|%-100s\n\n", "ID", "NOME", "PREÇO", "PROMOÇÃO", "DESCONTO(%%)", "DESCRIÇÃO");
                            while(aux != NULL){
                                char promocaoEscrita[5] = "Não";
                                if(aux->promocao == 1) {
                                    strcpy(promocaoEscrita, "Sim");
                                }

                                printf("%-5d|%-50s|%-11g|%-11s|%-12g|%-100s\n", aux->id, aux->nome, aux->preco, promocaoEscrita, aux->valorPromocao, aux->descricao);
                                aux = aux->proximo;
                            }

                            printf("\n\nEscolha um ID de pizza para adicionar ao pedido %d ou digite 0 para voltar: ", retornoPedido->id);
                            scanf("%d", &idPizza);
                            system("clear");

                            if(idPizza == 0) {
                                continue;
                            } else {
                                Pizza *retornoPizza = buscarPizzaPeloId(idPizza);

                                if(retornoPizza == NULL) {
                                    printf("O ID informado (%d) não existe", idPizza);
                                    continue;
                                } else {
                                    ItemPedido *novo  = (ItemPedido*) malloc(sizeof(ItemPedido));

                                    novo->idPedido = retornoPedido->id;
                                    novo->tipoItem = tipoItem;
                                    novo->idItem = retornoPizza->id;
                                    novo->promocao = retornoPizza->promocao;
                                    novo->valorPromocao = retornoPizza->valorPromocao;
                                    strcpy(novo->nome, retornoPizza->nome);
                                    novo->preco = retornoPizza->preco;

                                    if(itensPedidos == NULL) {
                                        novo->id = 1;
                                        itensPedidos = novo;
                                        itensPedidos->proximo = NULL;
                                    } else {
                                        ItemPedido *aux = itensPedidos;
                                        while(aux->proximo != NULL) {
                                            aux = aux->proximo;
                                        }
                                        
                                        novo->id = aux->id + 1;

                                        aux->proximo = novo;

                                        aux->proximo->proximo = NULL;
                                    }

                                    salvarItensPedidos();

                                    printf("Pizza adicionada ao pedido com sucesso!\n");

                                    printf("\n[----------------------------------- Itens do pedido em andamento %d -----------------------------------]\n", retornoPedido->id);

                                    if(retornoPedido->mesa != 0) { printf("\nMesa do pedido: %d", retornoPedido->mesa); }
                                    if(strlen(retornoPedido->endereco) > 0) { printf("\nEndereço do pedido: %s", retornoPedido->endereco); }
                                    if(strlen(retornoPedido->nomeCliente) > 0) { printf("\nNome informado para o pedido: %s", retornoPedido->nomeCliente); }

                                    if(retornoPedido->idCliente != 0) {
                                        Cliente *retornoCliente = buscarClientePeloId(retornoPedido->idCliente);
                                        printf("\nNome do cliente cadastrado no sistema: %s", retornoCliente->nome);
                                        printf("\nQuantidade de pizzas compradas: %d", retornoCliente->qtdPizzasCompradas);
                                    }
                                    
                                    printf("\nStatus do pedido: em andamento");

                                    ItemPedido *itemAux = itensPedidos;
                                    float totalPagar = 0;
                                    printf("\n\n\n%-5s|%-7s|%-30s|%-7s|%-11s|%-12s\n\n", "ID", "TIPO", "NOME", "PREÇO", "PROMOÇÃO", "DESCONTO(%%)");
                                    while(itemAux != NULL){
                                        if(itemAux->idPedido == retornoPedido->id) {
                                            if(itemAux->tipoItem == 1) {//pizza

                                                char promocaoEscrita[5];
                                                if(itemAux->promocao == 1) {
                                                    strcpy(promocaoEscrita, "Sim");
                                                    float valorDesconto = (itemAux->preco * itemAux->valorPromocao) / 100;
                                                    float precoComDesconto = itemAux->preco - valorDesconto;

                                                    totalPagar += precoComDesconto;
                                                } else {
                                                    strcpy(promocaoEscrita, "Não");
                                                    totalPagar += itemAux->preco;
                                                }

                                                printf("%-5d|%-7s|%-30s|%-7g|%-11s|%-12g\n\n", itemAux->id, "PIZZA", itemAux->nome, itemAux->preco, promocaoEscrita, itemAux->valorPromocao);

                                            } else if(itemAux->tipoItem == 2) {//bebida

                                                char promocaoEscrita[5];
                                                if(itemAux->promocao == 1) {
                                                    strcpy(promocaoEscrita, "Sim");
                                                    float valorDesconto = (itemAux->preco * itemAux->valorPromocao) / 100;
                                                    float precoComDesconto = itemAux->preco - valorDesconto;

                                                    totalPagar += precoComDesconto;
                                                } else {
                                                    strcpy(promocaoEscrita, "Não");
                                                    totalPagar += itemAux->preco;
                                                }

                                                printf("%-5d|%-7s|%-30s|%-7g|%-11s|%-12g\n\n", itemAux->id, "BEBIDA", itemAux->nome, itemAux->preco, promocaoEscrita, itemAux->valorPromocao);

                                            }
                                        }

                                        itemAux = itemAux->proximo;
                                    }

                                    printf("\nValor total: %g\n", totalPagar);

                                    char qqrTecla[1];
                                    printf("\nDigite qualquer caractere para voltar: ");
                                    scanf("%s", qqrTecla);
                                    system("clear");
                                    idPizza = 0;
                                }
                            }
                        } while(idPizza != 0);

                    } else if(tipoItem == 2) {

                        int idBebida;
                        do {
                            Bebida *aux = bebidas;
                            printf("\nTodas as bebidas");
                            printf("\n\n\n%-5s|%-50s|%-11s|%-11s|%-12s|%-100s\n\n", "ID", "NOME", "PREÇO", "PROMOÇÃO", "DESCONTO(%%)", "DESCRIÇÃO");
                            while(aux != NULL){
                                char promocaoEscrita[5] = "Não";
                                if(aux->promocao == 1) {
                                    strcpy(promocaoEscrita, "Sim");
                                }

                                printf("%-5d|%-50s|%-11g|%-11s|%-12g|%-100s\n", aux->id, aux->nome, aux->preco, promocaoEscrita, aux->valorPromocao, aux->descricao);
                                aux = aux->proximo;
                            }

                            printf("\n\nEscolha um ID de bebida para adicionar ao pedido %d ou digite 0 para voltar: ", retornoPedido->id);
                            scanf("%d", &idBebida);
                            system("clear");

                            if(idBebida == 0) {
                                continue;
                            } else {
                                Bebida *retornoBebida = buscarBebidaPeloId(idBebida);

                                if(retornoBebida == NULL) {
                                    printf("O ID informado (%d) não existe", idBebida);
                                    continue;
                                } else {
                                    ItemPedido *novo  = (ItemPedido*) malloc(sizeof(ItemPedido));

                                    novo->idPedido = retornoPedido->id;
                                    novo->tipoItem = tipoItem;
                                    novo->idItem = retornoBebida->id;
                                    novo->promocao = retornoBebida->promocao;
                                    novo->valorPromocao = retornoBebida->valorPromocao;
                                    strcpy(novo->nome, retornoBebida->nome);
                                    novo->preco = retornoBebida->preco;

                                    if(itensPedidos == NULL) {
                                        novo->id = 1;
                                        itensPedidos = novo;
                                        itensPedidos->proximo = NULL;
                                    } else {
                                        ItemPedido *aux = itensPedidos;
                                        while(aux->proximo != NULL) {
                                            aux = aux->proximo;
                                        }
                                        
                                        novo->id = aux->id + 1;

                                        aux->proximo = novo;

                                        aux->proximo->proximo = NULL;
                                    }

                                    salvarItensPedidos();

                                    system("clear");

                                    printf("Bebida adicionada ao pedido com sucesso!\n");

                                    printf("\n[----------------------------------- Itens do pedido em andamento %d -----------------------------------]\n", retornoPedido->id);

                                    if(retornoPedido->mesa != 0) { printf("\nMesa do pedido: %d", retornoPedido->mesa); }
                                    if(strlen(retornoPedido->endereco) > 0) { printf("\nEndereço do pedido: %s", retornoPedido->endereco); }
                                    if(strlen(retornoPedido->nomeCliente) > 0) { printf("\nNome informado para o pedido: %s", retornoPedido->nomeCliente); }

                                    if(retornoPedido->idCliente != 0) {
                                        Cliente *retornoCliente = buscarClientePeloId(retornoPedido->idCliente);
                                        printf("\nNome do cliente cadastrado no sistema: %s", retornoCliente->nome);
                                        printf("\nQuantidade de pizzas compradas: %d", retornoCliente->qtdPizzasCompradas);
                                    }
                                    
                                    printf("\nStatus do pedido: em andamento");

                                    ItemPedido *itemAux = itensPedidos;
                                    float totalPagar = 0;
                                    printf("\n\n\n%-5s|%-7s|%-30s|%-7s|%-11s|%-12s\n\n", "ID", "TIPO", "NOME", "PREÇO", "PROMOÇÃO", "DESCONTO(%%)");
                                    while(itemAux != NULL){
                                        if(itemAux->idPedido == retornoPedido->id) {
                                            if(itemAux->tipoItem == 1) {//pizza

                                                char promocaoEscrita[5];
                                                if(itemAux->promocao == 1) {
                                                    strcpy(promocaoEscrita, "Sim");
                                                    float valorDesconto = (itemAux->preco * itemAux->valorPromocao) / 100;
                                                    float precoComDesconto = itemAux->preco - valorDesconto;

                                                    totalPagar += precoComDesconto;
                                                } else {
                                                    strcpy(promocaoEscrita, "Não");
                                                    totalPagar += itemAux->preco;
                                                }

                                                printf("%-5d|%-7s|%-30s|%-7g|%-11s|%-12g\n\n", itemAux->id, "PIZZA", itemAux->nome, itemAux->preco, promocaoEscrita, itemAux->valorPromocao);

                                            } else if(itemAux->tipoItem == 2) {//bebida

                                                char promocaoEscrita[5];
                                                if(itemAux->promocao == 1) {
                                                    strcpy(promocaoEscrita, "Sim");
                                                    float valorDesconto = (itemAux->preco * itemAux->valorPromocao) / 100;
                                                    float precoComDesconto = itemAux->preco - valorDesconto;

                                                    totalPagar += precoComDesconto;
                                                } else {
                                                    strcpy(promocaoEscrita, "Não");
                                                    totalPagar += itemAux->preco;
                                                }

                                                printf("%-5d|%-7s|%-30s|%-7g|%-11s|%-12g\n\n", itemAux->id, "BEBIDA", itemAux->nome, itemAux->preco, promocaoEscrita, itemAux->valorPromocao);

                                            }
                                        }

                                        itemAux = itemAux->proximo;
                                    }

                                    printf("\nValor total: %g\n", totalPagar);

                                    char qqrTecla[1];
                                    printf("\nDigite qualquer caractere para voltar: ");
                                    scanf("%s", qqrTecla);
                                    system("clear");
                                    idBebida = 0;

                                }
                            }
                        } while(idBebida != 0);

                    } else {
                        printf("\nOpção inválida. Escolha uma opção válida.");
                    }
                    
                }while(tipoItem != 0);

            }

        }
    } while(idPedido != 0);
}

void carregaItensPedidos() {
    ItemPedido *itemPedido; 
    FILE *arq = fopen(dbItensPedidos,"r+b");    
    if (arq == NULL)
    {
        //printf("Erro ao abrir arquivo\n");
        return;
    }
    
    while (!feof(arq))
    {   
        itemPedido = (ItemPedido*) malloc(sizeof(ItemPedido));
        int qtd = fread(itemPedido,sizeof(ItemPedido),1,arq);
        if(qtd > 0){
            if(itensPedidos == NULL){
                itensPedidos = itemPedido;
                itemPedido->proximo = NULL;
            }
            else {
                itemPedido->proximo = NULL;
                ItemPedido *aux = itensPedidos;

                while(aux->proximo != NULL) {
                    aux = aux->proximo;
                }

                aux->proximo = itemPedido;
            }
        }
    }   
    fclose(arq);
}

void carregaPedidos() {
    Pedido *pedido; 
    FILE *arq = fopen(dbPedidos,"r+b");    
    if (arq == NULL)
    {
        //printf("Erro ao abrir arquivo\n");
        return;
    }
    
    while (!feof(arq))
    {   
        pedido = (Pedido*) malloc(sizeof(Pedido));
        int qtd = fread(pedido,sizeof(Pedido),1,arq);
        if(qtd > 0){
            if(pedidos == NULL){
                pedidos = pedido;
                pedido->proximo = NULL;
            }
            else {
                pedido->proximo = NULL;
                Pedido *aux = pedidos;

                while(aux->proximo != NULL) {
                    aux = aux->proximo;
                }

                aux->proximo = pedido;
            }
        }
    }   
    fclose(arq);
}

void editarPedidos(int statusAlterar) {
    bool continua = 0;
    
    do {
        Pedido *aux = pedidos;
        continua = 0;

        if(statusAlterar == 2) { printf("\n\nFinalizar um pedido em andamento"); }
        if(statusAlterar == 3) { printf("\n\nCancelar um pedido em andamento"); }

        int idPedidoAlterarStatus;

        if(statusAlterar == 2) {

            Pedido *aux = pedidos;
            printf("\n\n\n%-5s|%-10s|%-6s|%-50s|%-50s|%11s\n\n", "ID", "ID CLIENTE", "MESA", "NOME DO CLIENTE", "ENDEREÇO", "DATA PEDIDO");
            while(aux != NULL){
                if(aux->status == 1 && aux->idPizzaria == usuarioLogado.pizzariaTrabalha) {
                    printf("%-5d|%-10d|%-6d|%-50s|%-50s|%d%s%d%s%d\n", aux->id, aux->idCliente, aux->mesa, aux->nomeCliente, aux->endereco, aux->dataPedido.dia, "/", aux->dataPedido.mes, "/", aux->dataPedido.ano);
                }
                
                aux = aux->proximo;
            }

            printf("\nDigite um ID para visualizar os itens e finalizar o pedido ou digite 0 para voltar: ");
            scanf("%d", &idPedidoAlterarStatus);
            system("clear");
            
            if(idPedidoAlterarStatus == 0) {
                continue;
            } else {

                Pedido *retornoPedido = buscarPedidoPeloId(idPedidoAlterarStatus);

                if(retornoPedido == NULL) {
                    printf("O ID informado (%d) não existe", idPedidoAlterarStatus);
                    continue;
                } else {
                    printf("\n[----------------------------------- Itens do pedido em andamento %d -----------------------------------]\n", retornoPedido->id);

                    if(retornoPedido->mesa != 0) { printf("\nMesa do pedido: %d", retornoPedido->mesa); }
                    if(strlen(retornoPedido->endereco) > 0) { printf("\nEndereço do pedido: %s", retornoPedido->endereco); }
                    if(strlen(retornoPedido->nomeCliente) > 0) { printf("\nNome informado para o pedido: %s", retornoPedido->nomeCliente); }

                    if(retornoPedido->idCliente != 0) {
                        Cliente *retornoCliente = buscarClientePeloId(retornoPedido->idCliente);
                        printf("\nNome do cliente cadastrado no sistema: %s", retornoCliente->nome);
                        printf("\nQuantidade de pizzas compradas: %d", retornoCliente->qtdPizzasCompradas);
                    }
                    
                    printf("\nStatus do pedido: em andamento");

                    ItemPedido *itemAux = itensPedidos;
                    float totalPagar = 0;
                    printf("\n\n\n%-5s|%-7s|%-30s|%-7s|%-11s|%-12s\n\n", "ID", "TIPO", "NOME", "PREÇO", "PROMOÇÃO", "DESCONTO(%%)");
                    while(itemAux != NULL){
                        if(itemAux->idPedido == retornoPedido->id) {
                            if(itemAux->tipoItem == 1) {//pizza

                                char promocaoEscrita[5];
                                if(itemAux->promocao == 1) {
                                    strcpy(promocaoEscrita, "Sim");
                                    float valorDesconto = (itemAux->preco * itemAux->valorPromocao) / 100;
                                    float precoComDesconto = itemAux->preco - valorDesconto;

                                    totalPagar += precoComDesconto;
                                } else {
                                    strcpy(promocaoEscrita, "Não");
                                    totalPagar += itemAux->preco;
                                }

                                printf("%-5d|%-7s|%-30s|%-7g|%-11s|%-12g\n\n", itemAux->id, "PIZZA", itemAux->nome, itemAux->preco, promocaoEscrita, itemAux->valorPromocao);

                            } else if(itemAux->tipoItem == 2) {//bebida

                                char promocaoEscrita[5];
                                if(itemAux->promocao == 1) {
                                    strcpy(promocaoEscrita, "Sim");
                                    float valorDesconto = (itemAux->preco * itemAux->valorPromocao) / 100;
                                    float precoComDesconto = itemAux->preco - valorDesconto;

                                    totalPagar += precoComDesconto;
                                } else {
                                    strcpy(promocaoEscrita, "Não");
                                    totalPagar += itemAux->preco;
                                }

                                printf("%-5d|%-7s|%-30s|%-7g|%-11s|%-12g\n\n", itemAux->id, "BEBIDA", itemAux->nome, itemAux->preco, promocaoEscrita, itemAux->valorPromocao);

                            }
                        }

                        itemAux = itemAux->proximo;
                    }

                    printf("\nValor total: %g\n", ceilf(totalPagar * 100) / 100);

                    printf("\nDeseja realmente finalizar este pedido?");
                    printf("\nDigite 1 para SIM");
                    printf("\nDigite qualquer outro caractere para CANCELAR");
                    printf("\nOpção escolhida: ");

                    char qqrTecla[1];
                    scanf("%s", qqrTecla);
                    system("clear");
                    
                    if(strcmp(qqrTecla, "1") == 0) {
                        float valorCliente;
                        do {

                            printf("\n\nFinalizar pedido");
                            printf("\nValor total: %g\n", ceilf(totalPagar * 100) / 100);
                            printf("\nValor em dinheiro dado pelo cliente: ");
                            
                            scanf("%f", &valorCliente);

                            if(ceilf(totalPagar * 100) / 100 > valorCliente) {
                                system("clear");
                                printf("O valor dado pelo cliente deve ser maior ou igual ao valor total da conta");
                                continue;
                            }

                            retornoPedido->status = 2;
                            salvarPedidos();

                            printf("\n\nTroco: %g", (valorCliente - ceilf(totalPagar * 100) / 100));
                            printf("\n\nDigite qualquer caractere para voltar: ");

                            char qqrTecla[1];
                            scanf("%s", qqrTecla);
                            system("clear");
                        } while(ceilf(totalPagar * 100) / 100 > valorCliente);
                    }
                    
                }

            }

        } else if(statusAlterar == 3){
            Pedido *aux = pedidos;
            printf("\n\n\n%-5s|%-10s|%-6s|%-50s|%-50s|%11s\n\n", "ID", "ID CLIENTE", "MESA", "NOME DO CLIENTE", "ENDEREÇO", "DATA PEDIDO");
            while(aux != NULL){
                if(aux->status == 1 && aux->idPizzaria == usuarioLogado.pizzariaTrabalha) {
                    printf("%-5d|%-10d|%-6d|%-50s|%-50s|%d%s%d%s%d\n", aux->id, aux->idCliente, aux->mesa, aux->nomeCliente, aux->endereco, aux->dataPedido.dia, "/", aux->dataPedido.mes, "/", aux->dataPedido.ano);
                }
                
                aux = aux->proximo;
            }

            printf("\nDigite um ID para visualizar os itens e finalizar o pedido ou digite 0 para voltar: ");
            scanf("%d", &idPedidoAlterarStatus);
            system("clear");
            
            if(idPedidoAlterarStatus == 0) {
                continue;
            } else {

                Pedido *retornoPedido = buscarPedidoPeloId(idPedidoAlterarStatus);

                if(retornoPedido == NULL) {
                    printf("O ID informado (%d) não existe", idPedidoAlterarStatus);
                    continue;
                } else {
                    printf("\n[----------------------------------- Itens do pedido em andamento %d -----------------------------------]\n", retornoPedido->id);

                    if(retornoPedido->mesa != 0) { printf("\nMesa do pedido: %d", retornoPedido->mesa); }
                    if(strlen(retornoPedido->endereco) > 0) { printf("\nEndereço do pedido: %s", retornoPedido->endereco); }
                    if(strlen(retornoPedido->nomeCliente) > 0) { printf("\nNome informado para o pedido: %s", retornoPedido->nomeCliente); }

                    if(retornoPedido->idCliente != 0) {
                        Cliente *retornoCliente = buscarClientePeloId(retornoPedido->idCliente);
                        printf("\nNome do cliente cadastrado no sistema: %s", retornoCliente->nome);
                        printf("\nQuantidade de pizzas compradas: %d", retornoCliente->qtdPizzasCompradas);
                    }
                    
                    printf("\nStatus do pedido: em andamento");

                    ItemPedido *itemAux = itensPedidos;
                    float totalPagar = 0;
                    printf("\n\n\n%-5s|%-7s|%-30s|%-7s|%-11s|%-12s\n\n", "ID", "TIPO", "NOME", "PREÇO", "PROMOÇÃO", "DESCONTO(%%)");
                    while(itemAux != NULL){
                        if(itemAux->idPedido == retornoPedido->id) {
                            if(itemAux->tipoItem == 1) {//pizza

                                char promocaoEscrita[5];
                                if(itemAux->promocao == 1) {
                                    strcpy(promocaoEscrita, "Sim");
                                    float valorDesconto = (itemAux->preco * itemAux->valorPromocao) / 100;
                                    float precoComDesconto = itemAux->preco - valorDesconto;

                                    totalPagar += precoComDesconto;
                                } else {
                                    strcpy(promocaoEscrita, "Não");
                                    totalPagar += itemAux->preco;
                                }

                                printf("%-5d|%-7s|%-30s|%-7g|%-11s|%-12g\n\n", itemAux->id, "PIZZA", itemAux->nome, itemAux->preco, promocaoEscrita, itemAux->valorPromocao);

                            } else if(itemAux->tipoItem == 2) {//bebida

                                char promocaoEscrita[5];
                                if(itemAux->promocao == 1) {
                                    strcpy(promocaoEscrita, "Sim");
                                    float valorDesconto = (itemAux->preco * itemAux->valorPromocao) / 100;
                                    float precoComDesconto = itemAux->preco - valorDesconto;

                                    totalPagar += precoComDesconto;
                                } else {
                                    strcpy(promocaoEscrita, "Não");
                                    totalPagar += itemAux->preco;
                                }

                                printf("%-5d|%-7s|%-30s|%-7g|%-11s|%-12g\n\n", itemAux->id, "BEBIDA", itemAux->nome, itemAux->preco, promocaoEscrita, itemAux->valorPromocao);

                            }
                        }

                        itemAux = itemAux->proximo;
                    }

                    printf("\nValor total: %g\n", ceilf(totalPagar * 100) / 100);

                    printf("\nDeseja realmente CANCELAR este pedido?");
                    printf("\nDigite 1 para SIM");
                    printf("\nDigite qualquer outro caractere para VOLTAR AO MENU");
                    printf("\nOpção escolhida: ");

                    char qqrTecla[1];
                    scanf("%s", qqrTecla);
                    system("clear");
                    
                    if(strcmp(qqrTecla, "1") == 0) {
                        retornoPedido->status = 3;
                        salvarPedidos();
                    }
                    
                }

            }
        }

    } while(continua == 1);
}

void removerItensPedidos() {
    int idPedido;
    do {
        Pedido *aux = pedidos;
        printf("\nTodos os pedidos em andamento");
        printf("\n\n\n%-5s|%-10s|%-6s|%-50s|%-50s|%11s\n\n", "ID", "ID CLIENTE", "MESA", "NOME DO CLIENTE", "ENDEREÇO", "DATA PEDIDO");
        while(aux != NULL){
            if(aux->status == 1 && aux->idPizzaria == usuarioLogado.pizzariaTrabalha) {
                printf("%-5d|%-10d|%-6d|%-50s|%-50s|%d%s%d%s%d\n", aux->id, aux->idCliente, aux->mesa, aux->nomeCliente, aux->endereco, aux->dataPedido.dia, "/", aux->dataPedido.mes, "/", aux->dataPedido.ano);
            }
            
            aux = aux->proximo;
        }

        printf("\nDigite um ID para remover itens ou digite 0 para voltar: ");
        scanf("%d", &idPedido);
        system("clear");
        
        if(idPedido == 0) {
            continue;
        } else {

            Pedido *retornoPedido = buscarPedidoPeloId(idPedido);

            if(retornoPedido == NULL || retornoPedido->status != 1) {
                printf("O ID informado (%d) não existe", idPedido);
                continue;
            } else {
                int idItemPedidoRemover;
                do {
                    printf("\n[----------------------------------- Itens do pedido em andamento %d -----------------------------------]\n", retornoPedido->id);

                    if(retornoPedido->mesa != 0) { printf("\nMesa do pedido: %d", retornoPedido->mesa); }
                    if(strlen(retornoPedido->endereco) > 0) { printf("\nEndereço do pedido: %s", retornoPedido->endereco); }
                    if(strlen(retornoPedido->nomeCliente) > 0) { printf("\nNome informado para o pedido: %s", retornoPedido->nomeCliente); }

                    if(retornoPedido->idCliente != 0) {
                        Cliente *retornoCliente = buscarClientePeloId(retornoPedido->idCliente);
                        printf("\nNome do cliente cadastrado no sistema: %s", retornoCliente->nome);
                        printf("\nQuantidade de pizzas compradas: %d", retornoCliente->qtdPizzasCompradas);
                    }
                    
                    printf("\nStatus do pedido: em andamento");

                    ItemPedido *itemAux = itensPedidos;
                    float totalPagar = 0;
                    printf("\n\n\n%-5s|%-7s|%-30s|%-7s|%-11s|%-12s\n\n", "ID", "TIPO", "NOME", "PREÇO", "PROMOÇÃO", "DESCONTO(%%)");
                    while(itemAux != NULL){
                        if(itemAux->idPedido == retornoPedido->id) {
                            if(itemAux->tipoItem == 1) {//pizza

                                char promocaoEscrita[5];
                                if(itemAux->promocao == 1) {
                                    strcpy(promocaoEscrita, "Sim");
                                    float valorDesconto = (itemAux->preco * itemAux->valorPromocao) / 100;
                                    float precoComDesconto = itemAux->preco - valorDesconto;

                                    totalPagar += precoComDesconto;
                                } else {
                                    strcpy(promocaoEscrita, "Não");
                                    totalPagar += itemAux->preco;
                                }

                                printf("%-5d|%-7s|%-30s|%-7g|%-11s|%-12g\n\n", itemAux->id, "PIZZA", itemAux->nome, itemAux->preco, promocaoEscrita, itemAux->valorPromocao);

                            } else if(itemAux->tipoItem == 2) {//bebida

                                char promocaoEscrita[5];
                                if(itemAux->promocao == 1) {
                                    strcpy(promocaoEscrita, "Sim");
                                    float valorDesconto = (itemAux->preco * itemAux->valorPromocao) / 100;
                                    float precoComDesconto = itemAux->preco - valorDesconto;

                                    totalPagar += precoComDesconto;
                                } else {
                                    strcpy(promocaoEscrita, "Não");
                                    totalPagar += itemAux->preco;
                                }

                                printf("%-5d|%-7s|%-30s|%-7g|%-11s|%-12g\n\n", itemAux->id, "BEBIDA", itemAux->nome, itemAux->preco, promocaoEscrita, itemAux->valorPromocao);

                            }
                        }

                        itemAux = itemAux->proximo;
                    }

                    printf("\nValor total: %g\n", totalPagar);
                    
                    printf("\nDigite um ID de item para removê-lo do pedido ou digite 0 para voltar: ");
                    scanf("%d", &idItemPedidoRemover);
                    system("clear");

                    ItemPedido *retornoItemPedidoRemover = buscarItemPedidoPeloId(idItemPedidoRemover);

                    if(retornoItemPedidoRemover == NULL) {
                        printf("O ID informado (%d) não existe", idItemPedidoRemover);
                        continue;
                    } else {

                        printf("\n*** ATENÇÃO ***");
                        printf("\nDeseja realmente remover o item %d?", idItemPedidoRemover);
                        printf("\n\n\n%-5s|%-50s|%-11s|%-15s\n\n", "ID", "NOME", "PREÇO", "TIPO ITEM");
                        char tipoItemEscrito[11];
                        if(retornoItemPedidoRemover->tipoItem == 1) {
                            strcpy(tipoItemEscrito, "Pizza");
                        } else if(retornoItemPedidoRemover->tipoItem == 2) {
                            strcpy(tipoItemEscrito, "Bebida");
                        }

                        printf("%-5d|%-50s|%-11g|%-15s\n", retornoItemPedidoRemover->id, retornoItemPedidoRemover->nome, retornoItemPedidoRemover->preco, tipoItemEscrito);

                        char confirmaRemocao[1];

                        printf("\nDigite 1 para SIM");
                        printf("\nDigite qualquer outro caractere para CANCELAR");
                        printf("\n\nOpção escolhida: ");
                        scanf("%s", confirmaRemocao);

                        system("clear");

                        if(strcmp(confirmaRemocao, "1") == 0) {                 
                            ItemPedido *aux = itensPedidos;

                            if(aux->id == idItemPedidoRemover) {
                                itensPedidos = aux->proximo;

                            } else {
                                while(aux->proximo != NULL){
                                    ItemPedido *anterior = aux;
                                    ItemPedido *atual = aux->proximo;
                                    ItemPedido *proximo = atual->proximo;
                                    
                                    if(atual->id == idItemPedidoRemover) {
                                        anterior->proximo = proximo;
                                        break;
                                    }

                                    aux = aux->proximo;
                                }
                            }
                            
                            salvarItensPedidos();
                        } else {
                            idItemPedidoRemover = 0;
                        }
                        
                    }
                }while(idItemPedidoRemover != 0);
            }

        }
    } while(idPedido != 0);
}

void salvarItensPedidos() {
    ItemPedido *aux = itensPedidos;
    FILE *arq = fopen(dbItensPedidos,"wb");
    if (arq == NULL)
    {
        //printf("Erro ao abrir arquivo\n");
        exit(1);
    }
    while (aux != NULL){        
        fwrite(aux,sizeof(ItemPedido),1,arq);
        aux = aux->proximo;
    }
    fclose(arq);
}

void salvarPedidos() {
    Pedido *aux = pedidos;
    FILE *arq = fopen(dbPedidos,"wb");
    if (arq == NULL)
    {
        //printf("Erro ao abrir arquivo\n");
        exit(1);
    }
    while (aux != NULL){        
        fwrite(aux,sizeof(Pedido),1,arq);
        aux = aux->proximo;
    }
    fclose(arq);
}

void visualizarPedidos() {
    int visualizarPedidosTipo;
    do {
        printf("\nVisualizar pedidos");
        printf("\nDigite 1 para pedidos em andamento");
        printf("\nDigite 2 para pedidos finalizados");
        printf("\nDigite 3 para pedidos cancelados");
        printf("\nDigite 0 para voltar");
        printf("\n\nOpção escolhida: ");
        scanf("%d", &visualizarPedidosTipo);

        system("clear");

        if(visualizarPedidosTipo == 1) {

            int idPedido;
            do {
                Pedido *aux = pedidos;
                printf("\nTodos os pedidos em andamento");
                printf("\n\n\n%-5s|%-10s|%-6s|%-50s|%-50s|%11s\n\n", "ID", "ID CLIENTE", "MESA", "NOME DO CLIENTE", "ENDEREÇO", "DATA PEDIDO");
                while(aux != NULL){
                    if(aux->status == 1 && aux->idPizzaria == usuarioLogado.pizzariaTrabalha) {
                        printf("%-5d|%-10d|%-6d|%-50s|%-50s|%d%s%d%s%d\n", aux->id, aux->idCliente, aux->mesa, aux->nomeCliente, aux->endereco, aux->dataPedido.dia, "/", aux->dataPedido.mes, "/", aux->dataPedido.ano);
                    }
                    
                    aux = aux->proximo;
                }

                printf("\nDigite um ID para visualizar os itens ou digite 0 para voltar: ");
                scanf("%d", &idPedido);
                system("clear");
                
                if(idPedido == 0) {
                    continue;
                } else {

                    Pedido *retornoPedido = buscarPedidoPeloId(idPedido);

                    if(retornoPedido == NULL) {
                        printf("O ID informado (%d) não existe", idPedido);
                        continue;
                    } else {

                        printf("\n[----------------------------------- Itens do pedido em andamento %d -----------------------------------]\n", idPedido);

                        if(retornoPedido->mesa != 0) { printf("\nMesa do pedido: %d", retornoPedido->mesa); }
                        if(strlen(retornoPedido->endereco) > 0) { printf("\nEndereço do pedido: %s", retornoPedido->endereco); }
                        if(strlen(retornoPedido->nomeCliente) > 0) { printf("\nNome informado para o pedido: %s", retornoPedido->nomeCliente); }

                        if(retornoPedido->idCliente != 0) {
                            Cliente *retornoCliente = buscarClientePeloId(retornoPedido->idCliente);
                            printf("\nNome do cliente cadastrado no sistema: %s", retornoCliente->nome);
                            printf("\nQuantidade de pizzas compradas: %d", retornoCliente->qtdPizzasCompradas);
                        }
                        
                        printf("\nStatus do pedido: em andamento");

                        ItemPedido *aux = itensPedidos;
                        float totalPagar = 0;
                        printf("\n\n\n%-5s|%-7s|%-30s|%-7s|%-11s|%-12s\n\n", "ID", "TIPO", "NOME", "PREÇO", "PROMOÇÃO", "DESCONTO(%%)");
                        while(aux != NULL){
                            if(aux->idPedido == retornoPedido->id) {
                                if(aux->tipoItem == 1) {//pizza

                                    char promocaoEscrita[5];
                                    if(aux->promocao == 1) {
                                        strcpy(promocaoEscrita, "Sim");
                                        float valorDesconto = (aux->preco * aux->valorPromocao) / 100;
                                        float precoComDesconto = aux->preco - valorDesconto;

                                        totalPagar += precoComDesconto;
                                    } else {
                                        strcpy(promocaoEscrita, "Não");
                                        totalPagar += aux->preco;
                                    }

                                    printf("%-5d|%-7s|%-30s|%-7g|%-11s|%-12g\n\n", aux->id, "PIZZA", aux->nome, aux->preco, promocaoEscrita, aux->valorPromocao);

                                } else if(aux->tipoItem == 2) {//bebida

                                    char promocaoEscrita[5];
                                    if(aux->promocao == 1) {
                                        strcpy(promocaoEscrita, "Sim");
                                        float valorDesconto = (aux->preco * aux->valorPromocao) / 100;
                                        float precoComDesconto = aux->preco - valorDesconto;

                                        totalPagar += precoComDesconto;
                                    } else {
                                        strcpy(promocaoEscrita, "Não");
                                        totalPagar += aux->preco;
                                    }

                                    printf("%-5d|%-7s|%-30s|%-7g|%-11s|%-12g\n\n", aux->id, "BEBIDA", aux->nome, aux->preco, promocaoEscrita, aux->valorPromocao);

                                }
                            }

                            aux = aux->proximo;
                        }

                        printf("\nValor total: %g\n", totalPagar);

                        char qqrTecla[1];
                        printf("\nDigite qualquer caractere para voltar: ");
                        scanf("%s", qqrTecla);
                        if(strlen(qqrTecla) > 0) {
                            system("clear");
                        }
                    }

                }
            } while(idPedido != 0);

        } else if(visualizarPedidosTipo == 2) {

            int idPedido;
            do {
                Pedido *aux = pedidos;
                printf("\nTodos os pedidos finalizados");
                printf("\n\n\n%-5s|%-10s|%-6s|%-50s|%-50s|%11s\n\n", "ID", "ID CLIENTE", "MESA", "NOME DO CLIENTE", "ENDEREÇO", "DATA PEDIDO");
                while(aux != NULL){
                    if(aux->status == 2 && aux->idPizzaria == usuarioLogado.pizzariaTrabalha) {
                        printf("%-5d|%-10d|%-6d|%-50s|%-50s|%d%s%d%s%d\n", aux->id, aux->idCliente, aux->mesa, aux->nomeCliente, aux->endereco, aux->dataPedido.dia, "/", aux->dataPedido.mes, "/", aux->dataPedido.ano);
                    }
                    
                    aux = aux->proximo;
                }

                printf("\nDigite um ID para visualizar os itens ou digite 0 para voltar: ");
                scanf("%d", &idPedido);
                system("clear");
                
                if(idPedido == 0) {
                    continue;
                } else {

                    Pedido *retornoPedido = buscarPedidoPeloId(idPedido);

                    if(retornoPedido == NULL) {
                        printf("O ID informado (%d) não existe", idPedido);
                        continue;
                    } else {

                        printf("\n[----------------------------------- Itens do pedido finalizado %d -----------------------------------]\n", idPedido);

                        if(retornoPedido->mesa != 0) { printf("\nMesa do pedido: %d", retornoPedido->mesa); }
                        if(strlen(retornoPedido->endereco) > 0) { printf("\nEndereço do pedido: %s", retornoPedido->endereco); }
                        if(strlen(retornoPedido->nomeCliente) > 0) { printf("\nNome informado para o pedido: %s", retornoPedido->nomeCliente); }

                        if(retornoPedido->idCliente != 0) {
                            Cliente *retornoCliente = buscarClientePeloId(retornoPedido->idCliente);
                            printf("\nNome do cliente cadastrado no sistema: %s", retornoCliente->nome);
                            printf("\nQuantidade de pizzas compradas: %d", retornoCliente->qtdPizzasCompradas);
                        }
                        
                        printf("\nStatus do pedido: em andamento");

                        ItemPedido *aux = itensPedidos;
                        float totalPagar = 0;
                        printf("\n\n\n%-5s|%-7s|%-30s|%-7s|%-11s|%-12s\n\n", "ID", "TIPO", "NOME", "PREÇO", "PROMOÇÃO", "DESCONTO(%%)");
                        while(aux != NULL){
                            if(aux->idPedido == retornoPedido->id) {
                                if(aux->tipoItem == 1) {//pizza

                                    char promocaoEscrita[5];
                                    if(aux->promocao == 1) {
                                        strcpy(promocaoEscrita, "Sim");
                                        float valorDesconto = (aux->preco * aux->valorPromocao) / 100;
                                        float precoComDesconto = aux->preco - valorDesconto;

                                        totalPagar += precoComDesconto;
                                    } else {
                                        strcpy(promocaoEscrita, "Não");
                                        totalPagar += aux->preco;
                                    }

                                    printf("%-5d|%-7s|%-30s|%-7g|%-11s|%-12g\n\n", aux->id, "PIZZA", aux->nome, aux->preco, promocaoEscrita, aux->valorPromocao);

                                } else if(aux->tipoItem == 2) {//bebida

                                    char promocaoEscrita[5];
                                    if(aux->promocao == 1) {
                                        strcpy(promocaoEscrita, "Sim");
                                        float valorDesconto = (aux->preco * aux->valorPromocao) / 100;
                                        float precoComDesconto = aux->preco - valorDesconto;

                                        totalPagar += precoComDesconto;
                                    } else {
                                        totalPagar += aux->preco;
                                        strcpy(promocaoEscrita, "Não");
                                    }

                                    printf("%-5d|%-7s|%-30s|%-7g|%-11s|%-12g\n\n", aux->id, "BEBIDA", aux->nome, aux->preco, promocaoEscrita, aux->valorPromocao);

                                }
                            }

                            aux = aux->proximo;
                        }

                        printf("\nValor total: %g\n", totalPagar);

                        char qqrTecla[1];
                        printf("\nDigite qualquer caractere para voltar: ");
                        scanf("%s", qqrTecla);
                        if(strlen(qqrTecla) > 0) {
                            system("clear");
                        }
                    }

                }
            } while(idPedido != 0);

        } else if(visualizarPedidosTipo == 3) {

            int idPedido;
            do {
                Pedido *aux = pedidos;
                printf("\nTodos os pedidos cancelados");
                printf("\n\n\n%-5s|%-10s|%-6s|%-50s|%-50s|%11s\n\n", "ID", "ID CLIENTE", "MESA", "NOME DO CLIENTE", "ENDEREÇO", "DATA PEDIDO");
                while(aux != NULL){
                    if(aux->status == 3 && aux->idPizzaria == usuarioLogado.pizzariaTrabalha) {
                        printf("%-5d|%-10d|%-6d|%-50s|%-50s|%d%s%d%s%d\n", aux->id, aux->idCliente, aux->mesa, aux->nomeCliente, aux->endereco, aux->dataPedido.dia, "/", aux->dataPedido.mes, "/", aux->dataPedido.ano);
                    }
                    
                    aux = aux->proximo;
                }

                printf("\nDigite um ID para visualizar os itens ou digite 0 para voltar: ");
                scanf("%d", &idPedido);
                system("clear");
                
                if(idPedido == 0) {
                    continue;
                } else {

                    Pedido *retornoPedido = buscarPedidoPeloId(idPedido);

                    if(retornoPedido == NULL) {
                        printf("O ID informado (%d) não existe", idPedido);
                        continue;
                    } else {

                        printf("\n[----------------------------------- Itens do pedido cancelado %d -----------------------------------]\n", idPedido);

                        if(retornoPedido->mesa != 0) { printf("\nMesa do pedido: %d", retornoPedido->mesa); }
                        if(strlen(retornoPedido->endereco) > 0) { printf("\nEndereço do pedido: %s", retornoPedido->endereco); }
                        if(strlen(retornoPedido->nomeCliente) > 0) { printf("\nNome informado para o pedido: %s", retornoPedido->nomeCliente); }

                        if(retornoPedido->idCliente != 0) {
                            Cliente *retornoCliente = buscarClientePeloId(retornoPedido->idCliente);
                            printf("\nNome do cliente cadastrado no sistema: %s", retornoCliente->nome);
                            printf("\nQuantidade de pizzas compradas: %d", retornoCliente->qtdPizzasCompradas);
                        }
                        
                        printf("\nStatus do pedido: em andamento");

                        ItemPedido *aux = itensPedidos;
                        float totalPagar = 0;
                        printf("\n\n\n%-5s|%-7s|%-30s|%-7s|%-11s|%-12s\n\n", "ID", "TIPO", "NOME", "PREÇO", "PROMOÇÃO", "DESCONTO(%%)");
                        while(aux != NULL){
                            if(aux->idPedido == retornoPedido->id) {
                                if(aux->tipoItem == 1) {//pizza

                                    char promocaoEscrita[5];
                                    if(aux->promocao == 1) {
                                        strcpy(promocaoEscrita, "Sim");
                                        float valorDesconto = (aux->preco * aux->valorPromocao) / 100;
                                        float precoComDesconto = aux->preco - valorDesconto;

                                        totalPagar += precoComDesconto;
                                    } else {
                                        strcpy(promocaoEscrita, "Não");
                                        totalPagar += aux->preco;
                                    }

                                    printf("%-5d|%-7s|%-30s|%-7g|%-11s|%-12g\n\n", aux->id, "PIZZA", aux->nome, aux->preco, promocaoEscrita, aux->valorPromocao);

                                } else if(aux->tipoItem == 2) {//bebida

                                    char promocaoEscrita[5];
                                    if(aux->promocao == 1) {
                                        strcpy(promocaoEscrita, "Sim");
                                        float valorDesconto = (aux->preco * aux->valorPromocao) / 100;
                                        float precoComDesconto = aux->preco - valorDesconto;

                                        totalPagar += precoComDesconto;
                                    } else {
                                        totalPagar += aux->preco;
                                        strcpy(promocaoEscrita, "Não");
                                    }

                                    printf("%-5d|%-7s|%-30s|%-7g|%-11s|%-12g\n\n", aux->id, "BEBIDA", aux->nome, aux->preco, promocaoEscrita, aux->valorPromocao);

                                }
                            }

                            aux = aux->proximo;
                        }

                        printf("\nValor total: %g\n", totalPagar);

                        char qqrTecla[1];
                        printf("\nDigite qualquer caractere para voltar: ");
                        scanf("%s", qqrTecla);
                        if(strlen(qqrTecla) > 0) {
                            system("clear");
                        }
                    }

                }
            } while(idPedido != 0);

            
        } else if(visualizarPedidosTipo == 0) {
            system("clear");
            continue;
        } else {
            system("clear");
            printf("\nOpção inválida. Escolha uma opção válida.");
            continue;
        }
    } while(visualizarPedidosTipo != 0);
}

ItemPedido *buscarItemPedidoPeloId(int idItemPedido) {
    ItemPedido *aux = itensPedidos;

    while(aux != NULL){
        if(aux->id == idItemPedido) {
            return aux;
        }
        
        aux = aux->proximo;
    }

    return NULL;
}

Pedido *buscarPedidoPeloId(int idPedido) {
    Pedido *aux = pedidos;

    while(aux != NULL){
        if(aux->id == idPedido) {
            return aux;
        }
        
        aux = aux->proximo;
    }

    return NULL;
}





// -------------------------------- MANIPULAÇÃO DE ARQUIVOS: PIZZAS --------------------------------
void adicionarPizzas() {
    printf("\nAdicionar nova pizza");
    Pizza *nova  = (Pizza*) malloc(sizeof(Pizza));

    getchar();

    //Verificar se é nome repetido
    Pizza *auxVerifica = pizzas;
    if(auxVerifica == NULL) {
        printf("\nDigite o nome da pizza: ");
        fgets(nova->nome, sizeof(nova->nome), stdin); 
        strtok(nova->nome, "\n");
    }
    else if(auxVerifica->proximo == NULL) {
        do {
            printf("\nDigite o nome da pizza: ");
            fgets(nova->nome, sizeof(nova->nome), stdin); 
            strtok(nova->nome, "\n");

            if(strcmp(nova->nome, auxVerifica->nome) == 0) {
                system("clear");
                printf("\n\nNome da pizza já existente, entre com outro nome.");
            }
        } while(strcmp(nova->nome, auxVerifica->nome) == 0);
    } else if(pizzas != NULL) {
        bool continua = 0;
        do {
            auxVerifica = pizzas;
            continua = 0;
            printf("\nDigite o nome da pizza: ");
            fgets(nova->nome, sizeof(nova->nome), stdin); 
            strtok(nova->nome, "\n");

            while(auxVerifica != NULL) {
                if(strcmp(nova->nome, auxVerifica->nome) == 0) {
                    system("clear");
                    printf("\nNome da pizza já existente, entre com outro nome.");
                    continua = 1;
                    break;
                }

                auxVerifica = auxVerifica->proximo;
            }
        } while(continua == 1);
    } else {
        printf("\nDigite o nome da pizza: ");
        fgets(nova->nome, sizeof(nova->nome), stdin); 
        strtok(nova->nome, "\n");
    }

    printf("Digite a descrição: ");
    fgets(nova->descricao, sizeof(nova->descricao), stdin);
    strtok(nova->descricao, "\n");

    printf("Digite o preço: ");
    scanf("%f", &nova->preco);

    nova->promocao = 0;
    nova->valorPromocao = 0;

    system("clear");

    if(pizzas == NULL) {
        nova->id = 1;
        pizzas = nova;
        pizzas->proximo = NULL;
    } else {
        Pizza *aux = pizzas;
        while(aux->proximo != NULL) {
            aux = aux->proximo;
        }
        
        nova->id = aux->id + 1;

        aux->proximo = nova;

        aux->proximo->proximo = NULL;
    }
    salvarPizzas();
}

void carregaPizzas() {
    Pizza *pizza; 
    FILE *arq = fopen(dbPizzas,"r+b");    
    if (arq == NULL)
    {
        //printf("Erro ao abrir arquivo\n");
        return;
    }
    
    while (!feof(arq))
    {   
        pizza = (Pizza*) malloc(sizeof(Pizza));
        int qtd = fread(pizza,sizeof(Pizza),1,arq);
        if(qtd > 0){
            if(pizzas == NULL){
                pizzas = pizza;
                pizza->proximo = NULL;
            }        
            else {
                pizza->proximo = NULL;
                Pizza *aux = pizzas;

                while(aux->proximo != NULL) {
                    aux = aux->proximo;
                }

                aux->proximo = pizza;
            }
        }
    }   
    fclose(arq);
}

void editarPizzas() {
    bool continua = 0;
    
    do {
        Pizza *aux = pizzas;
        continua = 0;
        printf("\n\nEditar uma pizza");
        printf("\n\n\n%-5s|%-50s|%-11s|%-100s\n\n", "ID", "NOME", "PREÇO", "DESCRIÇÃO");
        while(aux != NULL){
            printf("%-5d|%-50s|%-11g|%-100s\n", aux->id, aux->nome, aux->preco, aux->descricao);
            aux = aux->proximo;
        }

        int idPizzaEditar;
        printf("\nInforme um ID de pizza para editar ou digite 0 para voltar: ");
        scanf("%d", &idPizzaEditar);
        
        system("clear");

        if(idPizzaEditar != 0) {
            Pizza *retornoPizza = buscarPizzaPeloId(idPizzaEditar);

            if(retornoPizza == NULL) {
                printf("O ID informado (%d) não existe", idPizzaEditar);
                continua = 1;
                continue;
            } else {
                int opcaoEscolhida;

                printf("\nO que você deseja editar?");
                printf("\n\nDigite 1 para PREÇO");
                printf("\nDigite 2 para DESCRIÇÃO");
                printf("\nDigite 0 para voltar");
                printf("\n\nOpção escolhida: ");
                scanf("%d", &opcaoEscolhida);

                system("clear");

                switch (opcaoEscolhida)
                {
                    case 0:
                        continua = 1;
                        break;
                    case 1:
                        printf("\nInsira um novo preço para a pizza de %s: ", retornoPizza->nome);
                        
                        scanf("%f", &retornoPizza->preco);

                        system("clear");
                        break;
                    case 2:
                        printf("\nInsira uma nova descrição para a pizza de %s: ", retornoPizza->nome);

                        getchar();
                        fgets(retornoPizza->descricao, sizeof(retornoPizza->descricao), stdin);
                        strtok(retornoPizza->descricao, "\n");

                        system("clear");
                        break;
                    default:
                        continua = 1;
                        printf("\nOpção inválida");
                        break;
                }
                
                salvarPizzas();
            }
        } else {
            continua = 0;
        }

    } while(continua == 1);
}

void removerPizzas() {
    bool continua = 0;
    
    do {
        Pizza *aux = pizzas;
        printf("\n\nRemover uma pizza");
        printf("\n\n\n%-5s|%-50s|%-11s|%-100s\n\n", "ID", "NOME", "PREÇO", "DESCRIÇÃO");
        while(aux != NULL){
            printf("%-5d|%-50s|%-11g|%-100s\n", aux->id, aux->nome, aux->preco, aux->descricao);
            aux = aux->proximo;
        }

        int idPizzaRemover;
        printf("\nInforme um ID de pizza para remover ou digite 0 para voltar: ");
        scanf("%d", &idPizzaRemover);
        
        system("clear");

        if(idPizzaRemover != 0) {
            Pizza *retornoPizza = buscarPizzaPeloId(idPizzaRemover);

            if(retornoPizza == NULL) {
                printf("O ID informado (%d) não existe", idPizzaRemover);
                continua = 1;
                continue;
            } else {
                printf("\n*** ATENÇÃO ***");
                printf("\nDeseja realmente remover a pizza %d?", idPizzaRemover);
                printf("\n\n\n%-5s|%-50s|%-11s|%-100s\n\n", "ID", "NOME", "PREÇO", "DESCRIÇÃO");
                printf("%-5d|%-50s|%-11g|%-100s\n", retornoPizza->id, retornoPizza->nome, retornoPizza->preco, retornoPizza->descricao);

                int confirmaRemocao;

                printf("\nDigite 1 para SIM");
                printf("\nDigite 0 para CANCELAR");
                printf("\n\nOpção escolhida: ");
                scanf("%d", &confirmaRemocao);

                system("clear");

                if(confirmaRemocao == 0) {
                    continua = 1;
                    continue;
                } else if(confirmaRemocao == 1) {                    
                    Pizza *aux = pizzas;

                    if(aux->id == idPizzaRemover) {
                        pizzas = aux->proximo;

                    } else {
                        while(aux->proximo != NULL){
                            Pizza *anterior = aux;
                            Pizza *atual = aux->proximo;
                            Pizza *proximo = atual->proximo;
                            
                            if(atual->id == idPizzaRemover) {
                                anterior->proximo = proximo;
                                break;
                            }

                            aux = aux->proximo;
                        }
                    }
                    
                    salvarPizzas();
                } else {
                    continua = 0;
                }
            }
        } else {
            continua = 0;
        }

    } while(continua == 1);
}

void salvarPizzas() {
    Pizza *aux = pizzas;
    FILE *arq = fopen(dbPizzas,"wb");
    if (arq == NULL)
    {
        //printf("Erro ao abrir arquivo\n");
        exit(1);
    }
    while (aux != NULL){        
        fwrite(aux,sizeof(Pizza),1,arq);
        aux = aux->proximo;
    }
    fclose(arq);
}

void visualizarPizzas() {
    Pizza *aux = pizzas;
    printf("\nTodas as pizzas");
    printf("\n\n\n%-5s|%-50s|%-11s|%-100s\n\n", "ID", "NOME", "PREÇO", "DESCRIÇÃO");
    while(aux != NULL){
        printf("%-5d|%-50s|%-11g|%-100s\n", aux->id, aux->nome, aux->preco, aux->descricao);
        aux = aux->proximo;
    }

    char qqrTecla[1];
    printf("\nDigite qualquer caractere para voltar: ");
    scanf("%s", qqrTecla);
    if(strlen(qqrTecla) > 0) {
        system("clear");
    }
}

Pizza *buscarPizzaPeloId(int idPizza) {
    Pizza *aux = pizzas;

    while(aux != NULL){
        if(aux->id == idPizza) {
            return aux;
        }
        
        aux = aux->proximo;
    }

    return NULL;
}





// -------------------------------- MANIPULAÇÃO DE ARQUIVOS: PROMOÇÕES --------------------------------
void adicionarPromocoes() {
    int opcaoEscolhida;

    do {
        printf("\nDigite 1 para adicionar nova promoção de PIZZA");
        printf("\nDigite 2 para adicionar nova promoção de BEBIDA");
        printf("\nDigite 0 para voltar ao menu");

        printf("\n\nOpção escolhida: ");

        scanf("%d", &opcaoEscolhida);

        system("clear");

        if(opcaoEscolhida == 1) {

            Pizza *aux = pizzas;
            printf("\nTodas as pizzas");
            printf("\n\n\n%-5s|%-50s|%-11s|%-100s\n\n", "ID", "NOME", "PREÇO", "DESCRIÇÃO");
            while(aux != NULL){
                printf("%-5d|%-50s|%-11g|%-100s\n", aux->id, aux->nome, aux->preco, aux->descricao);
                aux = aux->proximo;
            }

            printf("\n\nInforme um ID de pizza para aplicar a promoção: ");

            int opcaoEscolhidaIdPizza;

            scanf("%d", &opcaoEscolhidaIdPizza);

            printf("\nEscolha a porcentagem de desconto referente à promoção para aplicar a pizza escolhida: ");
            float porcentagemDesconto;
            scanf("%f", &porcentagemDesconto);

            system("clear");

            Pizza *retornoPizza = buscarPizzaPeloId(opcaoEscolhidaIdPizza);
            retornoPizza->promocao = 1;
            retornoPizza->valorPromocao = porcentagemDesconto;

            salvarPizzas();

        } else if(opcaoEscolhida == 2) {

            Bebida *aux = bebidas;
            printf("\nTodas as bebidas");
            printf("\n\n\n%-5s|%-50s|%-11s|%-100s\n\n", "ID", "NOME", "PREÇO", "DESCRIÇÃO");
            while(aux != NULL){
                printf("%-5d|%-50s|%-11g|%-100s\n", aux->id, aux->nome, aux->preco, aux->descricao);
                aux = aux->proximo;
            }

            printf("\n\nInforme um ID de bebida para aplicar a promoção: ");

            int opcaoEscolhidaIdBebida;

            scanf("%d", &opcaoEscolhidaIdBebida);

            printf("\nEscolha a porcentagem de desconto referente à promoção para aplicar a bebida escolhida: ");
            float porcentagemDesconto;
            scanf("%f", &porcentagemDesconto);

            system("clear");

            Bebida *retornoBebida = buscarBebidaPeloId(opcaoEscolhidaIdBebida);
            retornoBebida->promocao = 1;
            retornoBebida->valorPromocao = porcentagemDesconto;

            salvarBebidas();

        } else if(opcaoEscolhida != 0) {
            printf("\nDigite uma opção válida");
        }
    } while(opcaoEscolhida != 0);
}

void editarPromocoes() {
    int opcaoEscolhida;

    do {
        printf("\nDigite 1 para editar uma promoção de PIZZA");
        printf("\nDigite 2 para editar uma promoção de BEBIDA");
        printf("\nDigite 0 para voltar ao menu");

        printf("\n\nOpção escolhida: ");

        scanf("%d", &opcaoEscolhida);

        system("clear");

        if(opcaoEscolhida == 1) {
            bool continua = 0;
            
            do {
                Pizza *aux = pizzas;
                printf("\nEditar uma promoção de pizza");
                printf("\n\n\n%-5s|%-50s|%-11s|%-15s\n\n", "ID", "NOME", "PREÇO", "DESCONTO(%%)");
                while(aux != NULL){
                    if(aux->promocao == 1) {
                        printf("%-5d|%-50s|%-11g|%-15g\n", aux->id, aux->nome, aux->preco, aux->valorPromocao);
                    }
                    aux = aux->proximo;
                }

                int idPromocaoRemover;
                printf("\nInforme um ID de pizza para editar a promoção ou digite 0 para voltar: ");
                scanf("%d", &idPromocaoRemover);
                
                system("clear");

                if(idPromocaoRemover != 0) {
                    Pizza *retornoPizza = buscarPizzaPeloId(idPromocaoRemover);

                    if(retornoPizza == NULL) {
                        printf("O ID informado (%d) não existe", idPromocaoRemover);
                        continua = 1;
                        continue;
                    } else {
                        int opcaoEscolhida;

                        printf("\nO que você deseja editar?");
                        printf("\n\nDigite 1 para VALOR DE DESCONTO(%%)");
                        printf("\nDigite 0 para voltar");
                        printf("\n\nOpção escolhida: ");
                        scanf("%d", &opcaoEscolhida);

                        system("clear");

                        switch (opcaoEscolhida)
                        {
                            case 0:
                                continua = 1;
                                break;
                            case 1:
                                printf("\nInsira um novo desconto para a promoção de pizza %d: ", retornoPizza->id);
                                scanf("%f", &retornoPizza->valorPromocao);

                                system("clear");
                                break;
                            default:
                                continua = 1;
                                printf("\nOpção inválida");
                                break;
                        }
                        
                        salvarPizzas();
                    }
                } else {
                    continua = 0;
                }

            } while(continua == 1);

        } else if(opcaoEscolhida == 2) {
            bool continua = 0;
            
            do {
                Bebida *aux = bebidas;
                printf("\nEditar uma promoção de bebida");
                printf("\n\n\n%-5s|%-50s|%-11s|%-15s\n\n", "ID", "NOME", "PREÇO", "DESCONTO(%%)");
                while(aux != NULL){
                    if(aux->promocao == 1) {
                        printf("%-5d|%-50s|%-11g|%-15g\n", aux->id, aux->nome, aux->preco, aux->valorPromocao);
                    }
                    aux = aux->proximo;
                }

                int idPromocaoRemover;
                printf("\nInforme um ID de bebida para editar a promoção ou digite 0 para voltar: ");
                scanf("%d", &idPromocaoRemover);
                
                system("clear");

                if(idPromocaoRemover != 0) {
                    Bebida *retornoBebida = buscarBebidaPeloId(idPromocaoRemover);

                    if(retornoBebida == NULL) {
                        printf("O ID informado (%d) não existe", idPromocaoRemover);
                        continua = 1;
                        continue;
                    } else {
                        int opcaoEscolhida;

                        printf("\nO que você deseja editar?");
                        printf("\n\nDigite 1 para DESCONTO(%%)");
                        printf("\nDigite 0 para voltar");
                        printf("\n\nOpção escolhida: ");
                        scanf("%d", &opcaoEscolhida);

                        system("clear");

                        switch (opcaoEscolhida)
                        {
                            case 0:
                                continua = 1;
                                break;
                            case 1:
                                printf("\nInsira um novo desconto para a promoção de bebida %d: ", retornoBebida->id);
                                scanf("%f", &retornoBebida->valorPromocao);

                                system("clear");
                                break;
                            default:
                                continua = 1;
                                printf("\nOpção inválida");
                                break;
                        }
                        
                        salvarBebidas();
                    }
                } else {
                    continua = 0;
                }

            } while(continua == 1);
        } else if(opcaoEscolhida != 0) {
            printf("\nDigite uma opção válida");
        }
    } while(opcaoEscolhida != 0);
}

void removerPromocoes() {
    int opcaoEscolhida;

    do {
        printf("\nDigite 1 para remover uma promoção de PIZZA");
        printf("\nDigite 2 para remover uma promoção de BEBIDA");
        printf("\nDigite 0 para voltar ao menu");

        printf("\n\nOpção escolhida: ");

        scanf("%d", &opcaoEscolhida);

        system("clear");

        if(opcaoEscolhida == 1) {
            bool continua = 0;
            
            do {
                Pizza *aux = pizzas;
                printf("\nRemover uma promoção de pizza");
                printf("\n\n\n%-5s|%-50s|%-11s|%-15s\n\n", "ID", "NOME", "PREÇO", "DESCONTO(%%)");
                while(aux != NULL){
                    if(aux->promocao == 1) {
                        printf("%-5d|%-50s|%-11g|%-15g\n", aux->id, aux->nome, aux->preco, aux->valorPromocao);
                    }
                    aux = aux->proximo;
                }

                int idPromocaoRemover;
                printf("\nInforme um ID de pizza para remover a promoção ou digite 0 para voltar: ");
                scanf("%d", &idPromocaoRemover);
                
                system("clear");

                if(idPromocaoRemover != 0) {
                    Pizza *retornoPizza = buscarPizzaPeloId(idPromocaoRemover);

                    if(retornoPizza == NULL) {
                        printf("O ID informado (%d) não existe", idPromocaoRemover);
                        continua = 1;
                        continue;
                    } else {
                        printf("\n*** ATENÇÃO ***");
                        printf("\nDeseja realmente remover a promoção da pizza %d?", idPromocaoRemover);
                        printf("\n\n\n%-5s|%-50s|%-11s|%-15s\n\n", "ID", "NOME", "PREÇO", "DESCONTO(%%)");
                        printf("%-5d|%-50s|%-11g|%-15g\n", retornoPizza->id, retornoPizza->nome, retornoPizza->preco, retornoPizza->valorPromocao);

                        int confirmaRemocao;

                        printf("\nDigite 1 para SIM");
                        printf("\nDigite 0 para CANCELAR");
                        printf("\n\nOpção escolhida: ");
                        scanf("%d", &confirmaRemocao);

                        system("clear");

                        if(confirmaRemocao == 0) {
                            continua = 1;
                            continue;
                        } else if(confirmaRemocao == 1) {                    
                            retornoPizza->promocao = 0;
                            retornoPizza->valorPromocao = 0;
                            
                            salvarPizzas();
                        } else {
                            continua = 0;
                        }
                    }
                } else {
                    continua = 0;
                }
            } while(continua == 1);

        } else if(opcaoEscolhida == 2) {
            bool continua = 0;
            
            do {
                Bebida *aux = bebidas;
                printf("\nRemover uma promoção de bebida");
                printf("\n\n\n%-5s|%-50s|%-11s|%-15s\n\n", "ID", "NOME", "PREÇO", "DESCONTO(%%)");
                while(aux != NULL){
                    if(aux->promocao == 1) {
                        printf("%-5d|%-50s|%-11g|%-15g\n", aux->id, aux->nome, aux->preco, aux->valorPromocao);
                    }
                    aux = aux->proximo;
                }

                int idPromocaoRemover;
                printf("\nInforme um ID de bebida para remover a promoção ou digite 0 para voltar: ");
                scanf("%d", &idPromocaoRemover);
                
                system("clear");

                if(idPromocaoRemover != 0) {
                    Bebida *retornoBebida = buscarBebidaPeloId(idPromocaoRemover);

                    if(retornoBebida == NULL) {
                        printf("O ID informado (%d) não existe", idPromocaoRemover);
                        continua = 1;
                        continue;
                    } else {
                        printf("\n*** ATENÇÃO ***");
                        printf("\nDeseja realmente remover a promoção da bebida %d?", idPromocaoRemover);
                        printf("\n\n\n%-5s|%-50s|%-11s|%-15s\n\n", "ID", "NOME", "PREÇO", "DESCONTO(%%)");
                        printf("%-5d|%-50s|%-11g|%-15g\n", retornoBebida->id, retornoBebida->nome, retornoBebida->preco, retornoBebida->valorPromocao);

                        int confirmaRemocao;

                        printf("\nDigite 1 para SIM");
                        printf("\nDigite 0 para CANCELAR");
                        printf("\n\nOpção escolhida: ");
                        scanf("%d", &confirmaRemocao);

                        system("clear");

                        if(confirmaRemocao == 0) {
                            continua = 1;
                            continue;
                        } else if(confirmaRemocao == 1) {                    
                            retornoBebida->promocao = 0;
                            retornoBebida->valorPromocao = 0;
                            
                            salvarBebidas();
                        } else {
                            continua = 0;
                        }
                    }
                } else {
                    continua = 0;
                }

            } while(continua == 1);
        } else if(opcaoEscolhida != 0) {
            printf("\nDigite uma opção válida");
        }
    } while(opcaoEscolhida != 0);
}

void visualizarPromocoes() {
    int opcaoEscolhida;

    do {
        printf("\nDigite 1 para visualizar as promoções de PIZZA");
        printf("\nDigite 2 para visualizar as promoções de BEBIDA");
        printf("\nDigite 0 para voltar ao menu");

        printf("\n\nOpção escolhida: ");

        scanf("%d", &opcaoEscolhida);

        system("clear");

        if(opcaoEscolhida == 1) {

            Pizza *aux = pizzas;
            printf("\nTodas as pizzas com promoção");
            printf("\n\n\n%-5s|%-50s|%-11s|%-15s\n\n", "ID", "NOME", "PREÇO", "DESCONTO(%%)");
            while(aux != NULL){
                if(aux->promocao == 1) {
                    printf("%-5d|%-50s|%-11g|%-15g\n", aux->id, aux->nome, aux->preco, aux->valorPromocao);
                }
                aux = aux->proximo;
            }

            printf("\nDigite qualquer caractere para voltar: ");
            char qqrTecla[1];
            scanf("%s", qqrTecla);
            
            if(strlen(qqrTecla) > 0) {
                system("clear");
            }

        } else if(opcaoEscolhida == 2) {

            Bebida *aux = bebidas;
            printf("\nTodas as bebidas com promoção");
            printf("\n\n\n%-5s|%-50s|%-11s|%-15s\n\n", "ID", "NOME", "PREÇO", "DESCONTO(%%)");
            while(aux != NULL){
                if(aux->promocao == 1) {
                    printf("%-5d|%-50s|%-11g|%-15g\n", aux->id, aux->nome, aux->preco, aux->valorPromocao);
                }
                aux = aux->proximo;
            }

            printf("\nDigite qualquer caractere para voltar: ");
            char qqrTecla[1];
            scanf("%s", qqrTecla);
            
            if(strlen(qqrTecla) > 0) {
                system("clear");
            }

        } else if(opcaoEscolhida != 0) {
            printf("\nDigite uma opção válida");
        }
    } while(opcaoEscolhida != 0);
}





// -------------------------------- MANIPULAÇÃO DE ARQUIVOS: RECLAMAÇÕES --------------------------------
void adicionarReclamacoes() {
    printf("\nAdicionar nova reclamação");
    Reclamacao *nova  = (Reclamacao*) malloc(sizeof(Reclamacao));

    getchar();
    printf("\nDigite a descrição da reclamação: ");
    fgets(nova->descricao, sizeof(nova->descricao), stdin);
    strtok(nova->descricao, "\n");

    system("clear");

    if(reclamacoes == NULL) {
        nova->id = 1;
        reclamacoes = nova;
        reclamacoes->proximo = NULL;
    } else {
        Reclamacao *aux = reclamacoes;
        while(aux->proximo != NULL) {
            aux = aux->proximo;
        }
        
        nova->id = aux->id + 1;

        aux->proximo = nova;

        aux->proximo->proximo = NULL;
    }

    salvarReclamacoes();
}

void carregaReclamacoes() {
    Reclamacao *reclamacao; 
    FILE *arq = fopen(dbReclamacoes,"r+b");    
    if (arq == NULL)
    {
        //printf("Erro ao abrir arquivo\n");
        return;
    }
    
    while (!feof(arq))
    {   
        reclamacao = (Reclamacao*) malloc(sizeof(Reclamacao));
        int qtd = fread(reclamacao,sizeof(Reclamacao),1,arq);
        if(qtd > 0){
            if(reclamacoes == NULL){
                reclamacoes = reclamacao;
                reclamacao->proximo = NULL;
            }        
            else {
                reclamacao->proximo = NULL;
                Reclamacao *aux = reclamacoes;

                while(aux->proximo != NULL) {
                    aux = aux->proximo;
                }

                aux->proximo = reclamacao;
            }
        }
    }
    fclose(arq);
}

void editarReclamacoes() {
    bool continua = 0;
    
    do {
        Reclamacao *aux = reclamacoes;
        continua = 0;
        printf("\n\nEditar uma reclamação");
        printf("\n\n\n%-5s|%-200s\n\n", "ID", "DESCRIÇÃO");
        while(aux != NULL){
            printf("%-5d|%-200s\n", aux->id, aux->descricao);
            aux = aux->proximo;
        }

        int idReclamacaoEditar;
        printf("\nInforme um ID de reclamação para editar ou digite 0 para voltar: ");
        scanf("%d", &idReclamacaoEditar);
        
        system("clear");

        if(idReclamacaoEditar != 0) {
            Reclamacao *retornoReclamacao = buscarReclamacaoPeloId(idReclamacaoEditar);

            if(retornoReclamacao == NULL) {
                printf("O ID informado (%d) não existe", idReclamacaoEditar);
                continua = 1;
                continue;
            } else {
                int opcaoEscolhida;

                printf("\nO que você deseja editar?");
                printf("\n\nDigite 1 para DESCRIÇÃO");
                printf("\nDigite 0 para voltar");
                printf("\n\nOpção escolhida: ");
                scanf("%d", &opcaoEscolhida);

                system("clear");

                switch (opcaoEscolhida)
                {
                    case 0:
                        continua = 1;
                        break;
                    case 1:
                        printf("\nInsira uma nova descrição para a reclamação %d: ", retornoReclamacao->id);

                        getchar();
                        fgets(retornoReclamacao->descricao, sizeof(retornoReclamacao->descricao), stdin);
                        strtok(retornoReclamacao->descricao, "\n");

                        system("clear");
                        break;
                    default:
                        continua = 1;
                        printf("\nOpção inválida");
                        break;
                }
                
                salvarReclamacoes();
            }
        } else {
            continua = 0;
        }

    } while(continua == 1);
}

void removerReclamacoes() {
    bool continua = 0;
    
    do {
        Reclamacao *aux = reclamacoes;
        printf("\n\nRemover uma reclamação");
        printf("\n\n\n%-5s|%-200s\n\n", "ID", "DESCRIÇÃO");
        while(aux != NULL){
            printf("%-5d|%-200s\n", aux->id, aux->descricao);
            aux = aux->proximo;
        }

        int idReclamacaoRemover;
        printf("\nInforme um ID de reclamação para remover ou digite 0 para voltar: ");
        scanf("%d", &idReclamacaoRemover);
        
        system("clear");

        if(idReclamacaoRemover != 0) {
            Reclamacao *retornoReclamacao = buscarReclamacaoPeloId(idReclamacaoRemover);

            if(retornoReclamacao == NULL) {
                printf("O ID informado (%d) não existe", idReclamacaoRemover);
                continua = 1;
                continue;
            } else {
                printf("\n*** ATENÇÃO ***");
                printf("\nDeseja realmente remover a reclamação %d?", idReclamacaoRemover);
                printf("\n\n\n%-5s|%-200s\n\n", "ID", "DESCRIÇÃO");
                printf("%-5d|%-200s\n", retornoReclamacao->id, retornoReclamacao->descricao);

                int confirmaRemocao;

                printf("\nDigite 1 para SIM");
                printf("\nDigite 0 para CANCELAR");
                printf("\n\nOpção escolhida: ");
                scanf("%d", &confirmaRemocao);

                system("clear");

                if(confirmaRemocao == 0) {
                    continua = 1;
                    continue;
                } else if(confirmaRemocao == 1) {                    
                    Reclamacao *aux = reclamacoes;

                    if(aux->id == idReclamacaoRemover) {
                        reclamacoes = aux->proximo;

                    } else {
                        while(aux->proximo != NULL){
                            Reclamacao *anterior = aux;
                            Reclamacao *atual = aux->proximo;
                            Reclamacao *proximo = atual->proximo;
                            
                            if(atual->id == idReclamacaoRemover) {
                                anterior->proximo = proximo;
                                break;
                            }

                            aux = aux->proximo;
                        }
                    }
                    
                    salvarReclamacoes();
                } else {
                    continua = 0;
                }
            }
        } else {
            continua = 0;
        }

    } while(continua == 1);
}

void salvarReclamacoes() {
    Reclamacao *aux = reclamacoes;
    FILE *arq = fopen(dbReclamacoes,"wb");
    if (arq == NULL)
    {
        //printf("Erro ao abrir arquivo\n");
        exit(1);
    }
    while (aux != NULL){        
        fwrite(aux,sizeof(Reclamacao),1,arq);
        aux = aux->proximo;
    }
    fclose(arq);
}

void visualizarReclamacoes() {
    Reclamacao *aux = reclamacoes;
    printf("\nTodas as reclamações");
    printf("\n\n\n%-5s|%-200s\n\n", "ID", "DESCRIÇÃO");
    while(aux != NULL){
        printf("%-5d|%-200s\n", aux->id, aux->descricao);
        aux = aux->proximo;
    }

    char qqrTecla[1];
    printf("\nDigite qualquer caractere para voltar: ");
    scanf("%s", qqrTecla);
    if(strlen(qqrTecla) > 0) {
        system("clear");
    }
}

Reclamacao *buscarReclamacaoPeloId(int idReclamacao) {
    Reclamacao *aux = reclamacoes;

    while(aux != NULL){
        if(aux->id == idReclamacao) {
            return aux;
        }
        
        aux = aux->proximo;
    }

    return NULL;
}




// -------------------------------- MANIPULAÇÃO DE ARQUIVOS: USUÁRIOS --------------------------------
void adicionarUsuarios() {
    printf("\nAdicionar novo usuário");
    Usuario *novo  = (Usuario*) malloc(sizeof(Usuario));

    printf("\nDigite o nome: ");
    getchar();
    fgets(novo->nome, sizeof(novo->nome), stdin); 
    strtok(novo->nome, "\n");

    //Verificar se é login repetido
    Usuario *auxVerifica = usuarios;
    if(auxVerifica == NULL) {
        printf("\nDigite o login: ");
        fgets(novo->login, sizeof(novo->login), stdin); 
        strtok(novo->login, "\n");
    }
    else if(auxVerifica->proximo == NULL) {
        do {
            printf("\nDigite o login: ");
            fgets(novo->login, sizeof(novo->login), stdin); 
            strtok(novo->login, "\n");

            if(strcmp(novo->login, auxVerifica->login) == 0) {
                system("clear");
                printf("\n\nLogin já existente, entre com outro login.");
            }
        } while(strcmp(novo->login, auxVerifica->login) == 0);
    } else if(usuarios != NULL) {
        bool continua = 0;
        do {
            auxVerifica = usuarios;
            continua = 0;
            printf("\nDigite o login: ");
            fgets(novo->login, sizeof(novo->login), stdin); 
            strtok(novo->login, "\n");

            while(auxVerifica != NULL) {
                if(strcmp(novo->login, auxVerifica->login) == 0) {
                    system("clear");
                    printf("\nLogin já existente, entre com outro login.");
                    continua = 1;
                    break;
                }

                auxVerifica = auxVerifica->proximo;
            }
        } while(continua == 1);
    } else {
        printf("\nDigite o login: ");
        fgets(novo->login, sizeof(novo->login), stdin); 
        strtok(novo->login, "\n");
    }

    printf("Digite a senha: ");
    fgets(novo->senha, sizeof(novo->senha), stdin);
    strtok(novo->senha, "\n");

    printf("Digite o tipo de usuário -- [1] para administrador -- [2] para funcionário -- :");
    scanf("%d", &novo->tipoLogin);

    printf("Digite a pizzaria deste usuário (1, 2 ou 3): ");
    scanf("%d", &novo->pizzariaTrabalha);

    system("clear");

    if(usuarios == NULL) {
        novo->id = 1;
        usuarios = novo;
        usuarios->proximo = NULL;
    } else {
        Usuario *aux = usuarios;
        while(aux->proximo != NULL) {
            aux = aux->proximo;
        }
        
        novo->id = aux->id + 1;

        aux->proximo = novo;

        aux->proximo->proximo = NULL;
    }
    salvarUsuarios();
}

void carregaUsuarios() {
   Usuario *usuario; 
    FILE *arq = fopen(dbUsuarios,"r+b");    
    if (arq == NULL)
    {
        //printf("Erro ao abrir arquivo\n");
        return;
    }
    
    while (!feof(arq))
    {   usuario  = (Usuario*) malloc(sizeof(Usuario));
        int qtd = fread(usuario,sizeof(Usuario),1,arq);
        if(qtd > 0){
            if(usuarios == NULL){
                usuarios = usuario;
                usuario->proximo = NULL;
            }        
            else{
                usuario->proximo = NULL;
                Usuario *aux = usuarios;

                while(aux->proximo != NULL) {
                    aux = aux->proximo;
                }

                aux->proximo = usuario;
            }
        }
    }   
    fclose(arq);
}

void editarUsuarios() {
    bool continua = 0;
    
    do {
        Usuario *aux = usuarios;
        continua = 0;
        printf("\n\nEditar um usuário");
        printf("\n\n\n%-11s|%-50s|%-50s|%-50s|%-8s\n\n", "ID", "NOME", "LOGIN", "TIPO", "PIZZARIA");
        while(aux != NULL){
            char tipoLoginEscrito[20] = "Não identificado";

            if(aux->tipoLogin == 1) {
                strcpy(tipoLoginEscrito, "Administrador");
            } else if(aux->tipoLogin == 2){
                strcpy(tipoLoginEscrito, "Funcionário");
            }

            printf("%-11d|%-50s|%-50s|%-50s|%-8d\n", aux->id, aux->nome, aux->login, tipoLoginEscrito, aux->pizzariaTrabalha);
            aux = aux->proximo;
        }

        int idUsuarioEditar;
        printf("\nInforme um ID de usuário para editar ou digite 0 para voltar: ");
        scanf("%d", &idUsuarioEditar);
        
        system("clear");

        if(idUsuarioEditar != 0) {
            Usuario *retornoUsuario = buscarUsuarioPeloId(idUsuarioEditar);

            if(retornoUsuario == NULL) {
                printf("O ID informado (%d) não existe", idUsuarioEditar);
                continua = 1;
                continue;
            } else {
                int opcaoEscolhida;

                printf("\nO que você deseja editar?");
                printf("\n\nDigite 1 para NOME");
                printf("\nDigite 2 para TIPO DE USUÁRIO");
                printf("\nDigite 3 para SENHA");
                printf("\nDigite 4 para PIZZARIA EM QUE TRABALHA");
                printf("\nDigite 0 para voltar");
                printf("\n\nOpção escolhida: ");
                scanf("%d", &opcaoEscolhida);

                system("clear");

                switch (opcaoEscolhida)
                {
                    case 0:
                        continua = 1;
                        break;
                    case 1:
                        printf("\nInsira um novo nome para %s: ", retornoUsuario->nome);

                        getchar();
                        fgets(retornoUsuario->nome, sizeof(retornoUsuario->nome), stdin);
                        strtok(retornoUsuario->nome, "\n");
                        
                        system("clear");
                        break;
                    case 2:
                        printf("\nInsira um novo tipo de usuário para %s: ", retornoUsuario->nome);
                        printf("\nDigite 1 para ADMINISTRADOR");
                        printf("\nDigite 2 para FUNCIONÁRIO");
                        printf("\n\nOpção escolhida: ");
                        
                        int tipoLogin;
                        scanf("%d", &tipoLogin);

                        system("clear");

                        retornoUsuario->tipoLogin = tipoLogin;
                        break;
                    case 3:
                        printf("\nInsira uma nova senha para %s: ", retornoUsuario->nome);

                        getchar();
                        fgets(retornoUsuario->senha, sizeof(retornoUsuario->senha), stdin);
                        strtok(retornoUsuario->senha, "\n");

                        system("clear");
                        break;
                    case 4:
                        printf("\nInsira uma nova pizzaria (1, 2 ou 3) para %s: ", retornoUsuario->nome);
                        printf("\n\nOpção escolhida: ");
                        
                        int pizzariaTrabalha;
                        scanf("%d", &pizzariaTrabalha);

                        system("clear");

                        retornoUsuario->pizzariaTrabalha = pizzariaTrabalha;
                        break;
                    default:
                        continua = 1;
                        printf("\nOpção inválida");
                        break;
                }
                
                salvarUsuarios();
            }
        } else {
            continua = 0;
        }

    } while(continua == 1);
}

void removerUsuarios() {
    bool continua = 0;
    
    do {
        Usuario *aux = usuarios;
        printf("\n\nRemover um usuário");
        printf("\n\n\n%-11s|%-50s|%-50s|%-50s|%-8s\n\n", "ID", "NOME", "LOGIN", "TIPO", "PIZZARIA");
        while(aux != NULL){
            char tipoLoginEscrito[20] = "Não identificado";

            if(aux->tipoLogin == 1) {
                strcpy(tipoLoginEscrito, "Administrador");
            } else if(aux->tipoLogin == 2){
                strcpy(tipoLoginEscrito, "Funcionário");
            }

            printf("%-11d|%-50s|%-50s|%-50s|%-8d\n", aux->id, aux->nome, aux->login, tipoLoginEscrito, aux->pizzariaTrabalha);
            aux = aux->proximo;
        }

        int idUsuarioRemover;
        printf("\nInforme um ID de usuário para remover ou digite 0 para voltar: ");
        scanf("%d", &idUsuarioRemover);
        
        system("clear");

        if(idUsuarioRemover != 0) {
            Usuario *retornoUsuario = buscarUsuarioPeloId(idUsuarioRemover);

            if(retornoUsuario == NULL) {
                printf("O ID informado (%d) não existe", idUsuarioRemover);
                continua = 1;
                continue;
            } else {
                printf("\n*** ATENÇÃO ***");
                printf("\nDeseja realmente remover o usuário %d?", idUsuarioRemover);
                printf("\n\n\n%-11s|%-50s|%-50s|%-50s|%-8s\n\n", "ID", "NOME", "LOGIN", "TIPO", "PIZZARIA");

                char tipoLoginEscrito[20] = "Não identificado";

                if(retornoUsuario->tipoLogin == 1) {
                    strcpy(tipoLoginEscrito, "Administrador");
                } else if(retornoUsuario->tipoLogin == 2){
                    strcpy(tipoLoginEscrito, "Funcionário");
                }

                printf("%-11d|%-50s|%-50s|%-50s|%-8d\n", retornoUsuario->id, retornoUsuario->nome, retornoUsuario->login, tipoLoginEscrito, retornoUsuario->pizzariaTrabalha);

                int confirmaRemocao;

                printf("\nDigite 1 para SIM");
                printf("\nDigite 0 para CANCELAR");
                printf("\n\nOpção escolhida: ");
                scanf("%d", &confirmaRemocao);

                system("clear");

                if(confirmaRemocao == 0) {
                    continua = 1;
                    continue;
                } else if(confirmaRemocao == 1) {                    
                    Usuario *aux = usuarios;

                    if(aux->id == idUsuarioRemover) {
                        usuarios = aux->proximo;

                    } else {
                        while(aux->proximo != NULL){
                            Usuario *anterior = aux;
                            Usuario *atual = aux->proximo;
                            Usuario *proximo = atual->proximo;
                            
                            if(atual->id == idUsuarioRemover) {
                                anterior->proximo = proximo;
                                break;
                            }

                            aux = aux->proximo;
                        }
                    }
                    
                    salvarUsuarios();
                } else {
                    continua = 0;
                }
            }
        } else {
            continua = 0;
        }

    } while(continua == 1);
}

void salvarUsuarios() {
    Usuario *aux = usuarios;
    FILE *arq = fopen(dbUsuarios,"wb");
    if (arq == NULL)
    {
        //printf("Erro ao abrir arquivo\n");
        exit(1);
    }
    while (aux != NULL){        
        fwrite(aux,sizeof(Usuario),1,arq);
        aux = aux->proximo;
    }
    fclose(arq);
}

void visualizarUsuarios() {
    Usuario *aux = usuarios;
    printf("\nTodos os usuários");
    printf("\n\n\n%-11s|%-50s|%-50s|%-15s|%-8s\n\n", "ID", "NOME", "LOGIN", "TIPO", "PIZZARIA");
    while(aux != NULL){
        char tipoLoginEscrito[20] = "Não identificado";

        if(aux->tipoLogin == 1) {
            strcpy(tipoLoginEscrito, "Administrador");
        } else if(aux->tipoLogin == 2){
            strcpy(tipoLoginEscrito, "Funcionário");
        }

        printf("%-11d|%-50s|%-50s|%-15s|%-8d\n", aux->id, aux->nome, aux->login, tipoLoginEscrito, aux->pizzariaTrabalha);
        aux = aux->proximo;
    }

    char qqrTecla[1];
    printf("\nDigite qualquer caractere para voltar: ");
    scanf("%s", qqrTecla);
    if(strlen(qqrTecla) > 0) {
        system("clear");
    }
}

Usuario *buscarUsuarioPeloId(int idUsuario) {
    Usuario *aux = usuarios;

    while(aux != NULL){
        if(aux->id == idUsuario) {
            return aux;
        }
        
        aux = aux->proximo;
    }

    return NULL;
}





// -------------------------------- LOGAR E DESLOGAR DO SISTEMA --------------------------------

void logarNoSistema(int tipoLogin) {
    int statusLogin;
    do {
        char login[50];
        char senha[50];
        int resultLogin; // 1 = tentar novamente;

        if(tipoLogin == 1) {
            printf("\n\n'-----------------[LOGAR COMO ADMINISTRADOR]---------------------'\n");
        }
        else if(tipoLogin == 2) {
            printf("\n\n'--------------------[LOGAR COMO FUNCIONÁRIO]--------------------'\n");
        }
        
        printf("\nNos informe seu login: ");
        getchar();
        fgets(login, sizeof(login), stdin);
        strtok(login, "\n");

        printf("\nNos informe sua senha: ");
        fgets(senha, sizeof(senha), stdin);
        strtok(senha, "\n");

        system("clear");

        resultLogin = confereLogin(login, senha, tipoLogin);

        if(resultLogin == 1) {
            // DEFININDO O USUÁRIO QUE ESTÁ LOGADO
            strcpy(usuarioLogado.login, login);
            strcpy(usuarioLogado.senha, senha);
            usuarioLogado.tipoLogin = tipoLogin;

            if(tipoLogin == 1) {
                exibirMenuAdministrador();
            }
            else if(tipoLogin == 2) {
                exibirMenuFuncionario();
            }
        }
        else {
            printf("\n\n\nERRO: Usuário ou senha incorreto(s)\n");
            printf("\nDigite 1 para tentar novamente");
            printf("\nDigite qualquer outra tecla para voltar ao menu\n");
            printf("\n\nOpção escolhida: ");

            scanf("%d", &statusLogin);

            system("clear");
        }
    } while(statusLogin == 1);
    
}

void sair() {
    if(strlen(usuarioLogado.login) > 0) {
        printf("\n\nBye %s <3\n\n", usuarioLogado.login);
        strcpy(usuarioLogado.login, "");
        strcpy(usuarioLogado.senha, "");
        usuarioLogado.tipoLogin = 0;
    } else {
        printf("\n\nBye <3\n\n");
    }
}

// MAIN
int main(){
    carregaBebidas();
    carregaClientes();
    carregaElogios();
    carregaPedidos();
    carregaItensPedidos();
    carregaPizzas();
    carregaReclamacoes();
    carregaUsuarios();
    printf("\n\nBoas vindas ao sistema da pizzaria Degust.\n\n");

    exibirMenuLogin();
    
    return 0;
}