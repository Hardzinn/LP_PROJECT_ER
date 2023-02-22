/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cFiles/main.c to edit this template
 */

/* 
 * File:   comissoes.c
 * Author: andre
 *
 * Created on 18 de fevereiro de 2023, 14:36
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "structs.h"
#include "input.h" 


/**
 * @brief Inicializa os dados da estrutura comissoes, 
 * para nao haver qualque tipo de erro na passagem de numero.
 * @param comissoes
 */

void iniciarComissoes(Comissoes *comissoes){
    comissoes->contador = 0;
    comissoes->tamanho = MIN_COMISSOES;
    comissoes->comissoes = (Comissao*) malloc(MIN_COMISSOES * sizeof(Comissao));
}


/**
 * @brief Lista as comissoes, com o codigo do mercado, do vendedor, e as datas relativamente 
 * ao inicio e ao fim do periodo que o vendedor colocou uma comissao no mercado
 * @param comissao
 */
void listarComissao(Comissao comissao){
    printf("\nCodigo do mercado: %d\n", comissao.marketCode);
    printf("Codigo do vendedor:%d\n", comissao.sellerCode);
    printf("Percentagem da comissao :%f\n", comissao.percentage_commision);
    printf("Inicio da comissao: %02d/%02d/%04d\n",comissao.date_inicio.dia,comissao.date_inicio.mes,comissao.date_inicio.ano);
    printf("Fim da comissao: %02d/%02d/%04d\n\n",comissao.date_fim.dia,comissao.date_fim.mes,comissao.date_fim.ano);
}

/**
 * @brief Impreme as comissoes existentes na estrura Comissoes atraves da funcao 
 * listarComissao
 * @param comissoes
 */

void imprimirComissoes(Comissoes comissoes){
    if(comissoes.contador > 0){
        for (int i = 0; i < comissoes.contador; i++){
            listarComissao(comissoes.comissoes[i]);
        }
    } else{
        puts(EMPTY_LIST_COMMISSIONS);
    }
}

/**
 * @brief Lista os vendedores existentes num mercado.
 * @param comissoes
 */

void listComissoes(Comissoes comissoes){
    
    int marketCode = obterInt(MIN_MARKET_CODE,MAX_MARKET_CODE,ASK_MARKET_CODE);
    
    if( comissoes.contador > 0){
        if(procurarComMercados(comissoes,marketCode) != -1){
            for (int i =0; i<comissoes.contador; i++){
                if(comissoes.comissoes[i].marketCode == marketCode){
                    listarComissao(comissoes.comissoes[i]);
                }
            }
        }else{
            puts(COMMISION_DOESNT_EXIST);
        } 
    }else{
        puts(EMPTY_LIST_COMMISSIONS);
    }
    
}


/**
 * @brief Procura, atraves do input do utilizador , 
 * se ja existe algum funcionario nas comissoes atraves do seu codigo.
 * @param vendedores 
 * @param comissoes
 * @param codeSeller
 * @return O índice do vendedor no array de comissoes 
 * se ele for encontrado, ou -1 caso contrário.
 */
int procurarComVendedor(Comissoes comissoes, int codeSeller){
    for (int i = 0; i < comissoes.contador; i++) {
        if (comissoes.comissoes[i].sellerCode == codeSeller) {
            return i;
        }
    }
    return -1;
}

/**
 * @brief Procura, atraves do input do utilizador , 
 * se ja existe algum mercado atraves do seu codigo.
 * @param vendedores 
 * @param comissoes
 * @param codeSeller
 * @return O indice do mercado no array de comissoes 
 * se ele for encontrado, ou -1 caso contrário.
 */
int procurarComMercados(Comissoes comissoes, int marketCode){
    for (int i = 0; i < comissoes.contador; i++) {
        if (comissoes.comissoes[i].marketCode == marketCode) {
            return i;
        }
    }
    return -1;
}

/**
 * @brief Carrega as informacoes a partir de um ficheiro binario
 * @param comissoes
 * @param ficheiro
 * @return 0 se houver algum erro na abertura do ficheiro
 * 1 caso for um sucesso a carregar as informacoes
 */

int carregarComissoes(Comissoes *comissoes, char *ficheiro){
    int sucesso = 0;
    
    FILE *fp = fopen(ficheiro,"rb");
    if( fp != NULL){
        
        fread(&comissoes->contador, sizeof(int), 1, fp);
        
        if(comissoes->contador > 0){
            comissoes->comissoes = (Comissao*) malloc(sizeof(Comissao) * comissoes->contador);
            fread(comissoes->comissoes, sizeof(Comissao), 1,fp);
            
            comissoes->tamanho = comissoes->contador;
            
            sucesso = 1;
        }
        
        fclose (fp);
    }
    
    if(sucesso == 0){
        puts(FILE_ERROR_MERCADOS);
    }
    
    return sucesso;
    
}


/**
 * @brief Liberta a memoria da estrutura de comissoes.
 * @param comissoes
 */
void libertarComissoes(Comissoes *comissoes){
    free(comissoes->comissoes);
}

/**
 * @brief Esta função verifica se uma data representada por três valores inteiros (dia, mês e ano) 
 * está antes ou depois da data atual do sistema.
 * @param dia1
 * @param mes1
 * @param ano1
 * @return 1 se a data a ser verificada é posterior à data atual do sistema 
 * -1 se a data a ser verificada é anterior à data atual do sistema 
 * 1 se a data a ser verificada é igual à data atual do sistema ou se ocorreu algum erro na comparação.
 */

int verificarSobreposicaoDatas(int dia1, int mes1, int ano1) {
    int dia2, mes2, ano2;
    time_t mytime;
    mytime = time(NULL);
    struct tm tm = *localtime(&mytime);

    dia2 = tm.tm_mday;
    mes2 = tm.tm_mon + 1;
    ano2 = tm.tm_year + 1900;


    if (ano1 > ano2 || ano1 == ano2 && (mes1 > mes2 || (mes1 == mes2 && dia1 > dia2))) {
        return 1;
    } else if (ano1 < ano2 || ano1 == ano2 && (mes1 < mes2 || (mes1 == mes2 && dia1 < dia2))) {
        return -1;
    }
    return 1;
}

/**
 * @brief Registra uma comissao de um vendedor no mercado.pede ao utilizador tanto o
 * codigo do mercado como o do vendedor, e verifica se estes existem.
 * A condição verifica se o vendedor tem uma comissão de vendas ativa e se 
 * estiver ativa esteja dentro do prazo, 
 * ou se o vendedor não tem uma comissão de vendas ativa no momento.
 * @param comissoes
 * @param vendedores
 * @param mercados
 * @return -1 caso ja se encontre um mercado com aquele codigo, 
 * e comissoes->contador++ caso nao exista
 */

int registrarComissao(Comissoes *comissoes, Vendedores *vendedores, Mercados *mercados) {
    int marketCode , codSeller, codComSeller;
    marketCode = 0;
    codSeller = 0;
    codComSeller = 0;
    
    time_t t;
    struct tm *tmp;

    marketCode = obterInt(MIN_MARKET_CODE,MAX_MARKET_CODE,ASK_MARKET_CODE);
    
    if (procurarMercado(*mercados,marketCode) != -1){
        codSeller = obterInt(MIN_SELLER_CODE, MAX_SELLER_CODE, ASK_SELLER_CODE);
        
        if (procurarVendedor(*vendedores,codSeller) != -1){
            codComSeller = procurarComVendedor(*comissoes,codSeller);
            
            if (codComSeller != -1 && verificarSobreposicaoDatas(comissoes->comissoes[codComSeller].date_fim.dia, 
                    comissoes->comissoes[codComSeller].date_fim.mes, comissoes->comissoes[codComSeller].date_fim.ano) == -1 || codComSeller == -1){
                comissoes->comissoes[comissoes->contador].marketCode = marketCode;
                comissoes->comissoes[comissoes->contador].sellerCode = codSeller;
                comissoes->comissoes[comissoes->contador].percentage_commision = obterFloat(0,100,ASK_PERCENTAGE_COMMISION);
                
                int days = obterInt(MIN_COMMISION_DAY,MAX_COMMISION_DAY,ASK_COMMISSION_TIME);
                
                //Data final
                time(&t);
                t += days * 24 * 60 * 60;
                tmp = localtime(&t);
              
                comissoes->comissoes[comissoes->contador].date_fim.ano = tmp->tm_year + 1900;
                comissoes->comissoes[comissoes->contador].date_fim.dia = tmp->tm_mday;
                //adicionar 1 pois tm_mon returna valores de 0-11
                comissoes->comissoes[comissoes->contador].date_fim.mes = tmp->tm_mon + 1; 

                
                //Data inicial
                t = time(NULL);
                //transformar dias em segundos
                tmp = localtime(&t);
                
                comissoes->comissoes[comissoes->contador].date_inicio.dia = tmp->tm_mday;
                 //adicionar 1 pois tm_mon returna valores de 0-11
                comissoes->comissoes[comissoes->contador].date_inicio.mes = tmp->tm_mon + 1; 
                //adicionar 1900 pois tm_year returna valores do numero de anos desde 1900
                comissoes->comissoes[comissoes->contador].date_inicio.ano = tmp->tm_year + 1900;              

                return comissoes->contador++;
            }
        } else {
            puts(SELLER_DOESNT_EXIST);
        }
    } else{
        puts(MARKET_DOESNT_EXIST);
    }
    
    return -1;
}

/**
 * @brief Expande a estrutura comissoes atraves do seu tamanho, dinamicamente.
 * @param comissoes
 */

void expandirComissoes(Comissoes *comissoes){
    Comissao *temp = (Comissao*) realloc(comissoes->comissoes, sizeof(Comissao)* (comissoes->tamanho*2));
    if(temp !=NULL){
        comissoes->tamanho *=2;
        comissoes->comissoes = temp;
    }
}

/**
 * @brief Registra as comissoes, utilizando a funcao registrarComissao que 
 * devolve -1 caso nao exista um mercado com aquele codigo.
 * @param comissoes
 * @param vendedores
 * @param mercados
 */

void registrarComissoes(Comissoes *comissoes,Vendedores *vendedores, Mercados *mercados){
    
    if( comissoes->contador == comissoes->tamanho){
        expandirComissoes(comissoes);
    }
    
    if (comissoes->contador < comissoes->tamanho){
        if (registrarComissao(comissoes,vendedores,mercados) == -1){
           puts(COMMISSION_ALREADY_EXIST);
        }else{
           puts(COMMISION_REGISTRED_SUCCESS);
        }
    } else{
       puts(FULL_COMMISION_LIST);
    }

}

/**
 * @brief Guarda num ficheiro binario, as informacoes das comissoes.
 * @param comissoes
 * @param ficheiro
 */

void guardarComissoes(Comissoes *comissoes,char *ficheiro){
    
    FILE *fp = fopen(ficheiro,"wb+");
    
    if (fp == NULL){
        printf(FILE_ERROR_COMMISION);
        exit(EXIT_FAILURE);
    }
    
    fwrite(&comissoes->contador, sizeof(int), 1,fp);
    
    for( int i= 0; i< comissoes->contador; i++){
        fwrite(&comissoes->comissoes[i], sizeof(Comissao), 1 ,fp);
    }
    fclose(fp);
}
