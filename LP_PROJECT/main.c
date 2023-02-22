/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cFiles/main.c to edit this template
 */

/* 
 * File:   main.c
 * Author: andre
 *
 * Created on 13 de fevereiro de 2023, 15:02
 */

#include <stdio.h>
#include <stdlib.h>

#include "structs.h"
#include "input.h"




/*
 * @brief Inicialização do programa  
 */
int main(int argc, char** argv) {
    int choice;
    
    Vendedores vendedores;
    Mercados mercados;
    Comissoes comissoes;
    
    iniciarVendedores(&vendedores);
    iniciarMercados(&mercados);
    iniciarComissoes(&comissoes);
    
    do {
        printf("Bem Vindo!! Insira o que deseja fazer:\n");
        printf("------------Funcionarios------------\n");
        printf("1.Criar Vendedor.\n");
        printf("2.Editar Vendedor.\n");
        printf("3.Remover Vendedor.\n");
        printf("4.Listar Vendedor.\n");
        printf("--------------Mercados--------------\n");
        printf("5.Criar Mercado.\n");
        printf("6.Editar Mercado.\n");
        printf("7.Remover Mercado.\n");
        printf("8.Listar Mercado.\n");  
        printf("--------------Comissoes-------------\n");
        printf("9.Inserir Comissao.\n");
        printf("10.Listar vendedores num mercado.\n");
        printf("11.Guardar informações.\n");
        printf("12.Carregar informações.\n");
        printf("\n0.Sair do programa.\n");

        choice = obterInt(0, 12, "->");

        switch (choice) {
            case 1:
                registrarVendedores(&vendedores);   
                break;
            case 2:
                editarVendedores(&vendedores);
                break;
            case 3:
                removerVendedor(&vendedores,&comissoes);
                break;
            case 4:
                listarVendedores(vendedores);
                break;
            case 5:
                registarMercados(&mercados);
                break;
            case 6:
                editarMercados(&mercados);
                break;
            case 7:
                eliminarMercados(&mercados,&comissoes);
                break;
            case 8:
                listarMercados(mercados);
                break;
            case 9:
                registrarComissoes(&comissoes,&vendedores,&mercados);
                break;
            case 10:
                listComissoes(comissoes);
                break;
            case 11:
                guardarVendedores(&vendedores,SELLER_DB_FILE);
                guardarMercados(&mercados,MARKET_DB_FILE);
                guardarComissoes(&comissoes,COMMISION_DB_FILE);
                break;
            case 12:
                carregarVendedores(&vendedores,SELLER_DB_FILE);
                carregarMercados(&mercados,MARKET_DB_FILE);
                carregarComissoes(&comissoes,COMMISION_DB_FILE);
                break;
            case 0:
                return 0;
            default:
                printf(INVALID_OPTION);
        }

    } while (choice != 0);

    libertarVendedores(&vendedores);
    libertarMercados(&mercados);
    libertarComissoes(&comissoes);
    
    return (EXIT_SUCCESS);
}

