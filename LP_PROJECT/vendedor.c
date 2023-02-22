/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cFiles/main.c to edit this template
 */

/* 
 * File:   vendedor.c
 * Author: andre
 *
 * Created on 14 de fevereiro de 2023, 21:54
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "structs.h"
#include "input.h"


/**
 * @brief E iniciado para igualar os varios membros da estrutura vendedores para 
 * nao existir qualquer tipo de valor inicialmente nestes membros
 * @param vendedores
 */

void iniciarVendedores(Vendedores *vendedores){
    vendedores->contador = 0;
    vendedores->tamanho = MIN_VENDEDORES;
    vendedores->vendedores = (Vendedor*) malloc(MIN_VENDEDORES * sizeof (Vendedor));
}


/**
 * @brief Imprime um vendedor
 * @param vendedores
 */

void listarVendedor(Vendedor vendedor) {
    printf("Nome : %s\n", vendedor.name);
    printf("Email: %s\n", vendedor.email);
    printf("Codigo de vendedor : %d\n", vendedor.seller_code);
    printf("Numero de telemovel: %d\n", vendedor.phone);
    printf("Estado :%s\n\n", vendedor.estado);
}

/**
 * @brief Imprime varios vendedores utilizando a funcao listarVendedor.
 * @param vendedores 
 */

void listarVendedores(Vendedores vendedores) {
    if (vendedores.contador > 0) {
        for (int i = 0; i < vendedores.contador; i++) {
            if(strcmp(vendedores.vendedores[i].estado,"Desativo")){
            printf("Funcionario [%d]:\n", i + 1);
            listarVendedor(vendedores.vendedores[i]);
            }
        }
    } else {
        puts(EMPTY_LIST);
    }
}

/**
 * @brief Procura, atraves do input do utilizador , 
 * se ja existe algum funcionario atraves do seu codigo.
 * @param vendedores 
 * @param codSeller Codigo do vendedor introduzido.
 * @return O índice do vendedor no array de vendedores 
 * se ele for encontrado, ou -1 caso contrário.
 */

int procurarVendedor(Vendedores vendedores, int codSeller) {
    for (int i = 0; i < vendedores.contador; i++) {
        if (vendedores.vendedores[i].seller_code == codSeller) {
            return i;
        }
    }
    return -1;
}

/**
 * @brief Carrega os dados dos vendedores de um arquivo binário
 * @param vendedores
 * @param ficheiro
 * @return 1 se a operação de carregamento for bem-sucedida;
 * 0 se a operação de carregamento falhar.
 */

int carregarVendedores(Vendedores *vendedores, char *ficheiro) {
    int sucesso = 0;

    FILE *fp = fopen(ficheiro, "rb");
    
    if (fp != NULL) {

        fread(&vendedores->contador, sizeof (int), 1, fp);

        if (vendedores->contador > 0) {
            vendedores->vendedores = (Vendedor*) malloc(vendedores->contador * sizeof (Vendedor));
            fread(vendedores->vendedores, sizeof (Vendedor), vendedores->contador, fp);

            vendedores->tamanho = vendedores->contador;

            sucesso = 1;
        }
        fclose(fp);
    }
    
    if(sucesso == 0){
        puts(FILE_ERROR_SELLER);
    }

    return sucesso;
}

/**
 * @brief Libera a memória alocada dinamicamente para armazenar o array de vendedores na estrutura "Vendedores".
 * @param vendedores
 */
void libertarVendedores(Vendedores *vendedores){
    free(vendedores->vendedores);
}

/**
 * @brief Insere novos vendedores, usando a funcao procurarVendedor para 
 * verificar a existencia de um funcionario com o numero do vendedor,
 * caso nao forem encontrados, insere na estrura um novo vendedor com as informacoes
 * introduzidas
 * @param vendedores
 * @return Returna -1 caso ja exista algum Vendedor com o codigo , 
 * ou returna o aumento do numero de contadores
 */

int registrarVendedor(Vendedores *vendedores) {

    int codSeller = obterInt(MIN_SELLER_CODE, MAX_SELLER_CODE, ASK_SELLER_CODE);

    if (procurarVendedor(*vendedores, codSeller) == -1) {

        vendedores->vendedores[vendedores->contador].seller_code = codSeller;
        lerString(vendedores->vendedores[vendedores->contador].name, MAX_NAME_INPUT, ASK_NAME_INPUT);
        lerString(vendedores->vendedores[vendedores->contador].email, MAX_EMAIL_INPUT, ASK_EMAIL_INPUT);
        vendedores->vendedores[vendedores->contador].phone = obterInt(MIN_PHONE_NUMBER, MAX_PHONE_NUMBER, ASK_PHONE_NUMBER);
        strcpy(vendedores->vendedores[vendedores->contador].estado , STATUS_A);

        return vendedores->contador++;
    }
    return -1;

}

/**
 * @brief Expande o array de vendedores realocando memoria sempre que necessario.
 * @param vendedores
 */
void expandirVendedores(Vendedores *vendedores){
    Vendedor *temp = (Vendedor*) realloc(vendedores->vendedores, sizeof(Vendedor)*(vendedores->tamanho * 2));
    if(temp != NULL){
        vendedores->tamanho *= 2;
        vendedores->vendedores = temp;
    }
}

/**
 * @brief Registra os vendedores, caso o contador for igual ao numero maximo de vendedores 
 * a funcao expande para ser possivel ter mais vendedores no array. 
 * @param vendedores
 */

void registrarVendedores(Vendedores *vendedores) {

    if (vendedores->contador == vendedores->tamanho) {
        expandirVendedores(vendedores);
    }

    if (vendedores->contador < vendedores->tamanho) {
        if (registrarVendedor(vendedores) == -1) {
            puts(ALREADY_EXISTES_SELLER);
        } else {
            puts(SUCCESS_SELLER_CREATION);
        }
    } else {
        puts(FULL_LIST_SELLER);
    }
}

/**
 * @brief Atualiza um vendedor. Utilizado na funcao editarVendedores. 
 * Serve para atualizar os novos valores.
 * @param vendedor
 */

void atualizarVendedor(Vendedor *vendedor) {
    lerString(vendedor->name, MAX_NAME_INPUT, ASK_NAME_INPUT);
    lerString(vendedor->email, MAX_EMAIL_INPUT, ASK_EMAIL_INPUT);
    vendedor->phone = obterInt(MIN_PHONE_NUMBER, MAX_PHONE_NUMBER, ASK_PHONE_NUMBER);
    strcpy(vendedor->estado,STATUS_A);
}

/**
 * @brief Edita um vendedor utilizando a funcao atualizarVendedor, primeiro pede pelo numero do vendedor, 
 * apos isso procura se existe algum vendedor com esse codigo e 
 * caso exista prossegue caso nao exista devolve a string SELLER_DOESNT_EXIST.
 * @param vendedores
 */

void editarVendedores(Vendedores *vendedores) {
    int codeSeller = obterInt(MIN_SELLER_CODE, MAX_SELLER_CODE, ASK_SELLER_CODE);
    int numero = procurarVendedor(*vendedores, codeSeller);

    if (numero != -1) {
        atualizarVendedor(&vendedores->vendedores[numero]);
    } else {
        puts(SELLER_DOESNT_EXIST);
    }
}

/**
 * @brief Apaga vendedor. Serve apenas para eliminar os dados do vendedor 
 * que ira ser selecionado na funcao removerVendedor.
 * @param vendedor
 */

void apagarVendedor(Vendedor *vendedor) {
    strcpy(vendedor->name, "");
    strcpy(vendedor->email, "");
    vendedor->phone = 0;
    vendedor->seller_code = 0;
    strcpy(vendedor->estado,"");
}

/**
 *@brief Altera o estado de um vendedor para desativado
 * @param vendedor
 */
void vendedorInativo(Vendedor *vendedor){
    strcpy(vendedor->estado,STATUS_D);
}

/**
 * @brief Remove um vendedor. Obtem o numero do cliente, e depois utiliza a funcao procruarVendedor para verificar a existencia do mesmo .
 * Caso exista reduz o numero de vendedores existente. 
 * @param vendedores
 */

void removerVendedor(Vendedores *vendedores,Comissoes *comissoes) {

    int codSeller = obterInt(MIN_SELLER_CODE, MAX_SELLER_CODE, ASK_SELLER_CODE);
    int numero = procurarVendedor(*vendedores, codSeller);

    if (numero != -1) {
        if(procurarComVendedor(*comissoes,codSeller) == -1){
            for (int i = numero; i < vendedores->contador - 1; i++) {
                vendedores->vendedores[i] = vendedores->vendedores[i + 1];
            }
            apagarVendedor(&vendedores->vendedores[numero]);
            vendedores->contador--;
        } else{
            vendedorInativo(&vendedores->vendedores[numero]);
            puts(SELLER_DESACTIVATION);
        }

    } else {
        puts(SELLER_DOESNT_EXIST);
    }
}

/**
 * @brief Guarda as informacoes dos vendedores num ficheiro binario.
 * @param vendedores
 * @param ficheiro
 */
void guardarVendedores(Vendedores *vendedores,char *ficheiro){
    
    FILE *fp = fopen(ficheiro,"wb+");
    
    if(fp == NULL){
        printf(FILE_ERROR_SELLER);
        exit(EXIT_FAILURE);
    }
    
    fwrite(&vendedores->contador, sizeof(int),1, fp);
    
    for( int i = 0; i< vendedores->contador; i++){
        fwrite(&vendedores->vendedores[i], sizeof(Vendedor),1, fp);
    }
    
    fclose(fp);
}
