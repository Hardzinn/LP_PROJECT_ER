/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cFiles/main.c to edit this template
 */

/* 
 * File:   input.c
 * Author: andre
 *
 * Created on 13 de fevereiro de 2023, 20:55
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define VALOR_INVALIDO "O valor inserido é inválido. Por favor tente novamente"


void cleanInputBuffer() {
    char ch;
    while ((ch = getchar()) != '\n' && ch != EOF);
}

/**
 * @brief Limita o input do utilizador, recebendo um 
 * valor minimo inteiro e um valor maximo inteiro predefinido e
 * com a possibilidade de integrar uma string. 
 * @param minValor Valor minimo para limitar o input
 * @param maxValor Valor maximo para limitar o input
 * @param msg String desejada para dar output
 * @return Valor desejado
 */


int obterInt(int minValor, int maxValor, char *msg){
    int valor;
    printf(msg);
    while(scanf("%d",&valor) != 1 || valor < minValor || valor > maxValor){
        puts(VALOR_INVALIDO);
        cleanInputBuffer();
        printf(msg);
    }
    cleanInputBuffer();
    return valor;
}

/**
 * @brief Limita o input do utilizador, recebendo um 
 * valor minimo float e um valor maximo float predefinido e
 * com a possibilidade de integrar uma string. 
 * @param minValor Valor minimo para limitar o input
 * @param maxValor Valor maximo para limitar o input
 * @param msg String desejada para dar output
 * @return Valor desejado
 */


float obterFloat(float minValor, float maxValor, char *msg){
    float valor;
    printf(msg);
    while(scanf("%f",&valor) != 1 || valor < minValor || valor > maxValor){
        puts(VALOR_INVALIDO);
        cleanInputBuffer();
        printf(msg);
    }
    cleanInputBuffer();
    return valor;
}


/**
 * Recebe um caracter pelo utilizador, e depois limpa o buffer .
 * @param msgString desejada para dar output
 * @return valor desejado
 */
char obterChar(char *msg){
    printf(msg);
    char valor = getchar();
    cleanInputBuffer();
    return valor;
}

/**
 * Recebe uma string 
 * @param string
 * @param tamanho
 * @param msg
 */
void lerString(char *string, unsigned int tamanho, char *msg) {
    printf(msg);
    if (fgets(string, tamanho, stdin) != NULL) {
        unsigned int len = strlen(string) - 1;
        if (string[len] == '\n') {
            string[len] = '\0';
        } else {
            cleanInputBuffer();
        }
    }
}
