/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cFiles/file.h to edit this template
 */

/* 
 * File:   structs.h
 * Author: andre
 *
 * Created on 19 de fevereiro de 2023, 16:57
 */

#ifndef STRUCTS_H
#define STRUCTS_H

//macros relativamente ao vendedor
#define MAX_NAME_INPUT 32
#define ASK_NAME_INPUT "Insira o nome do vendedor:"

#define STATUS_MAX_INPUT 11
#define STATUS_A "Ativo"
#define STATUS_D "Desativado"

#define MAX_PHONE_INPUT 9
#define MAX_PHONE_NUMBER 999999999 
#define MIN_PHONE_NUMBER 900000000 
#define ASK_PHONE_NUMBER "Insira o numero de telemovel do vendedor:"

#define MAX_EMAIL_INPUT 15
#define ASK_EMAIL_INPUT "Insira o e-mail do vendedor:"

#define MAX_SELLER_CODE 5000
#define MIN_SELLER_CODE 1000
#define ASK_SELLER_CODE "Codigo do vendedor :"
#define SELLER_DOESNT_EXIST "Nao existe nenhum vendedor com esse codigo"
#define SELLER_DESACTIVATION "Vendedor desativado\n"

#define EMPTY_LIST "Lista vazia"
#define FULL_LIST_SELLER "Lista cheia"

#define ALREADY_EXISTES_SELLER "Já existe um vendedor com o código fornecido."
#define SUCCESS_SELLER_CREATION "Vendedor criado com sucesso"
#define MIN_VENDEDORES 1

#define SELLER_DB_FILE "vendedores.bin"
#define FILE_ERROR_SELLER "Erro ao abrir o ficheiro vendedores"


//Macros relativemente ao mercados

#define MAX_MARKET_NAME 64
#define ASK_MARKET_NAME "Insira o nome do mercado:"

#define MAX_MARKET_CODE 193
#define MIN_MARKET_CODE 1
#define ASK_MARKET_CODE "Codigo do mercado :"

#define MARKET_ALREADY_EXISTS "Mercado ja existe"
#define SUCCESS_MARKET_CREATION "Mercado criado com sucesso"
#define FULL_LIST_MARKET "Lista de mercados cheia"
#define EMPTY_LIST_MARKET "Lista de mercados vazia"
#define MARKET_DOESNT_EXIST "Mercado nao existe"
#define MARKET_DESACTIVATE "Mercado desativado"
#define MIN_MARKETS 1

#define MARKET_DB_FILE "mercados.bin"
#define FILE_ERROR_MERCADOS "Erro ao abrir o ficheiro mercados"

// Macros relativamente as comissoes

#define FULL_COMMISION_LIST "Lista de comissoes cheia\n"
#define EMPTY_LIST_COMMISSIONS "Lista de comissoes vazia\n"
#define COMMISION_DOESNT_EXIST "Comissao nao existe\n"

#define COMMISION_REGISTRED_SUCCESS "Comissao registrado com sucesso\n"
#define COMMISSION_ALREADY_EXIST "Comissao ja existe\n"

#define ASK_PERCENTAGE_COMMISION "Qual e a percentagem que deseja ter sobre o mercado?(0-100):"

#define COMMISION_DB_FILE "comissoes.bin"
#define FILE_ERROR_COMMISION "Erro ao abrir o ficheiro das comissoes."

#define MIN_COMMISION_DAY 1
#define MAX_COMMISION_DAY 365
#define ASK_COMMISSION_TIME "Insira quantos dias quer ter a comissao neste mercado:"

#define COMMISION_SELLER_DOESNT_EXIST "O vendedor nao tem nenhuma comissao ativa"

#define MIN_COMISSOES 5



//Estrutura que representa um vendedor
typedef struct {
    char name[MAX_NAME_INPUT];
    int phone;
    char email[MAX_PHONE_INPUT];
    int seller_code;
    char estado[STATUS_MAX_INPUT];
}Vendedor;


//Representa varios vendedores, utilizando o contador para gerenciar os mesmos.
typedef struct {
    int contador ,tamanho;
    Vendedor *vendedores;  
}Vendedores;

//define um estrutura para um mercado
typedef struct {
    int marketCode;
    char marketName[MAX_MARKET_NAME];
    char estado[STATUS_MAX_INPUT];
}Mercado;

//define varios mercados, utilizando o contador para gerenciar os mesmos
typedef struct {
    int contador,tamanho;
    Mercado *mercados;
}Mercados;

//estrura de duas datas
typedef struct{
    int dia,mes,ano;
} Date1,Date2;

//define uma comissao
typedef struct {
    int sellerCode, marketCode;
    float percentage_commision;
    Date1 date_inicio;
    Date2 date_fim;
} Comissao;

//define varias comissoes, utilizando o contador para gerenciar as mesmas
typedef struct {
    int contador, tamanho;
    Comissao *comissoes;
} Comissoes;

//funcoes relativamente ao vendedores

void iniciarVendedores(Vendedores *vendedores);
int procurarVendedor(Vendedores vendedores, int codSeller);
int carregarVendedores(Vendedores *vendedores, char *ficheiro);
void listarVendedores(Vendedores vendedores);
void registrarVendedores(Vendedores *vendedores);
void editarVendedores(Vendedores *vendedores);
void removerVendedor(Vendedores *vendedores,Comissoes *comissoes);
void guardarVendedores(Vendedores *vendedores,char *ficheiro);
void libertarVendedores(Vendedores *vendedores);


//funcoes relativamente aos mercados

void iniciarMercados(Mercados *mercados);
void listarMercados(Mercados mercados);
int procurarMercado(Mercados mercados, int marketCode);
int carregarMercados(Mercados *mercados, char *ficheiro);
void expandirMercados(Mercados *mercados);
void registarMercados(Mercados *mercados);
void editarMercados(Mercados *mercados);
void eliminarMercados(Mercados *mercados, Comissoes *comissoes);
void libertarMercados(Mercados *mercados);
void guardarMercados(Mercados *mercados, char *ficheiro);

//funcoes das comissoes

void iniciarComissoes(Comissoes *comissoes);
void imprimirComissoes(Comissoes comissoes);
void listComissoes(Comissoes comissoes);
int procurarComVendedor(Comissoes comissoes, int codeSeller);
int procurarComMercados(Comissoes comissoes, int marketCode);
int carregarComissoes(Comissoes *comissoes, char *ficheiro);
int verificarSobreposicaoDatas(int dia1, int mes1, int ano1);
int registrarComissao(Comissoes *comissoes, Vendedores *vendedores, Mercados *mercados);
void expandirComissoes(Comissoes *comissoes);
void registrarComissoes(Comissoes *comissoes, Vendedores *vendedores, Mercados *mercados);
void libertarComissoes(Comissoes *comissoes);
void guardarComissoes(Comissoes *comissoes,char *ficheiro);


#endif /* STRUCTS_H */

