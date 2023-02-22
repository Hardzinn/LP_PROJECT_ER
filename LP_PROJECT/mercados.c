/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cFiles/main.c to edit this template
 */

/* 
 * File:   mercados.c
 * Author: andre
 *
 * Created on 14 de fevereiro de 2023, 22:14
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "structs.h"
#include "input.h"


/**
 * @brief E iniciado para igualar os varios membros da estrutura mercados para 
 * nao existir qualquer tipo de valor inicialmente nestes membros
 * @param vendedores
 */

void iniciarMercados(Mercados *mercados){
    mercados->contador = 0;
    mercados->tamanho = MIN_MARKETS;
    mercados->mercados = (Mercado*) malloc(MIN_MARKETS * sizeof (Mercado));
}


/**
 * @brief Lista os membros de um mercado
 * @param mercado
 */

void listarMercado(Mercado mercado){
    printf("Mercado: %s\n", mercado.marketName);
    printf("Codigo do mercado: %d\n", mercado.marketCode);
    printf("Estado do mercado: %s\n\n", mercado.estado);
}

/**
 * @brief Lista os varios mercados existentes no array de Mercados. 
 * Utiliza a funcao listar para dar output a cada mercado
 * @param mercados
 */

void listarMercados(Mercados mercados){
    if (mercados.contador > 0){
        for (int i = 0; i < mercados.contador; i++){
            printf("Mercado [%d]:\n", i + 1);
            listarMercado(mercados.mercados[i]);
        }
    } else {
        puts(EMPTY_LIST_MARKET);
    }
}

/**
 * @brief Procura no array atraves do contador, o codigo pedido pelo utilizador.
 * @param mercados
 * @param marketCode
 * @return  returna i se encontrar algum mercado com o codigo fornecido. 
 * -1 caso nao encontre nada .
 */

int procurarMercado(Mercados mercados, int marketCode){
    for(int i = 0; i < mercados.contador; i++){
        if(mercados.mercados[i].marketCode == marketCode){
            return i;
        }
    }
    return -1;
}

/**
 * @brief Carrega os dados dos mercados de um arquivo binário
 * @param vendedores
 * @param ficheiro
 * @return 1 se a operação de carregamento for bem-sucedida;
 * 0 se a operação de carregamento falhar.
 */

int carregarMercados(Mercados *mercados, char *ficheiro) {
    int sucesso = 0;

    FILE *fp = fopen(ficheiro, "rb");
    
    if (fp != NULL) {

        fread(&mercados->contador, sizeof (int), 1, fp);

        if (mercados->contador > 0) {
            mercados->mercados = (Mercado*) malloc(mercados->contador * sizeof (Mercado));
            fread(mercados->mercados, sizeof (Mercado), mercados->contador, fp);

            mercados->tamanho = mercados->contador;

            sucesso = 1;
        }
        fclose(fp);
    }
    
    if(sucesso == 0){
        puts(FILE_ERROR_MERCADOS);
    }
    
    return sucesso;
}

/**
 * @brief Libera a memória alocada dinamicamente armazenarenada no array de vendedores na estrutura "Vendedores".
 * @param vendedores
 */

void libertarMercados(Mercados *mercados){
    free(mercados->mercados);
}

/**
 * @brief Registra um mercado pedindo ao utilizador o codigo. 
 * Caso nao exista nenhum mercado com esse codigo ele 
 * guarda a variavel no marketCode e altera o nome ao gosto do utilizador.
 * 
 * @param mercados
 * @return returna mercados->contador++ caso nao exista nenhum mercado com o codigo pedido.
 * returna -1 caso nao seja possivel/ ja exista algum mercado com esse codigo.
 */

int registarMercado(Mercados *mercados){
    
    int marketCode = obterInt(MIN_MARKET_CODE,MAX_MARKET_CODE,ASK_MARKET_CODE);
    
    if ( procurarMercado(*mercados,marketCode) == -1){
            mercados->mercados[mercados->contador].marketCode = marketCode;
            lerString(mercados->mercados[mercados->contador].marketName,MAX_MARKET_NAME,ASK_MARKET_NAME);
            strcpy(mercados->mercados[mercados->contador].estado,STATUS_A);

            return mercados->contador++;
        
    }
    return -1;
}

/**
 * @brief Expande o array de mercados realocando memoria sempre que necessario.
 * @param vendedores
 */
void expandirMercados(Mercados *mercados){
    Mercado *temp = (Mercado*) realloc(mercados->mercados, sizeof(Mercado) *(mercados->tamanho*2));
    if(temp != NULL){
        mercados->tamanho *= 2;
        mercados->mercados = temp;
    }
}

/**
 * @brief Registro de mercados
 * @param mercados
 */

void registarMercados(Mercados *mercados){
    
    if ( mercados->contador == mercados-> tamanho){
        expandirMercados(mercados);
    }
    
    if( mercados->contador < mercados->tamanho){
        if(registarMercado(mercados) == -1){
            puts(MARKET_ALREADY_EXISTS);
        } else {
            puts(SUCCESS_MARKET_CREATION);
        }
    } else{
        puts(FULL_LIST_MARKET);
    }

}



/**
 * @brief Atualiza as informacoes que o utilizador deseja editar.
 * Neste caso, o nome do mercado existente.
 * @param mercado
 */

void atualizarMercado(Mercado *mercado){
    lerString(mercado->marketName,MAX_MARKET_NAME,ASK_MARKET_NAME);
}

/**
 * @brief Edita um mercado atraves do codigo do mercado. caso exista  
 * um mercado com esse nome atualiza o mercado que o utilizador deseja, 
 * senao da output que nao existe nenhum mercado .
 * @param mercados
 */

void editarMercados(Mercados *mercados){
    int marketCode = procurarMercado(*mercados,obterInt(MIN_MARKET_CODE,MAX_MARKET_CODE,ASK_MARKET_CODE));
    
    if(marketCode != -1){
        atualizarMercado(&mercados->mercados[marketCode]);
    } else {
        puts(MARKET_DOESNT_EXIST);
    }
    
}

/**
 * @brief Elimina as informacoes de um mercado
 * @param mercado
 */

void eliminarMercado(Mercado *mercado){
    mercado->marketCode = 0;
    strcpy(mercado->marketName,"");
    strcpy(mercado->estado,"");
}

/**
 * @brief Altera o estado de um mercado para desativodo
 * @param mercado
 */
void mercadoInativo(Mercado *mercado){
    strcpy(mercado->estado,STATUS_D);
}

/**
 * @brief Elimina um mercado atraves do seu codigo, utiliza a funcao eliminarMercado 
 * para eliminar as informacoes do mesmo. 
 * caso exista decrementa o contador de mercados.
 * @param mercados
 */

void eliminarMercados(Mercados *mercados, Comissoes *comissoes){
    
    int marketCode = obterInt(MIN_MARKET_CODE,MAX_MARKET_CODE,ASK_MARKET_CODE);
    int numero = procurarMercado(*mercados,marketCode);

    if (numero != -1) {
        if(procurarComMercados(*comissoes,marketCode) == -1){
            for (int i = numero; i < mercados->contador - 1; i++) {
                mercados->mercados[i] = mercados->mercados[i + 1];
            }
            eliminarMercado(&mercados->mercados[numero]);
            mercados->contador--;
        } else{
            mercadoInativo(&mercados->mercados[numero]);
            puts(MARKET_DESACTIVATE);
        }    
    } else {
        puts(MARKET_DOESNT_EXIST);
    }
}


/**
 * @brief Guarda as informacoes dos vendedores num ficheiro binario.
 * @param vendedores
 * @param ficheiro
 */

void guardarMercados(Mercados *mercados, char *ficheiro){
    
    FILE *fp = fopen(ficheiro, "wb+");
    
    if(fp == NULL){
        puts(FILE_ERROR_MERCADOS);
        exit(EXIT_FAILURE);
    }
    
    fwrite(&mercados->contador, sizeof(int),1,fp);
    
    for(int i = 0; i < mercados->contador;i++ ){
        fwrite(&mercados->mercados[i], sizeof(Mercado), 1, fp);
    }
    
    fclose(fp);
}