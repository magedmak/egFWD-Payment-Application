/* 
 * File: main.c
 * 
 * Description:
 * The main function of the payment application. 
 * It allows the user to enter the required card and transaction data, 
 * processes the entered data and communicates with the server to get the transaction status.
 * 
 * Author: Maged Magdy Asaad
 * Date: December 25, 2022
 * 
 * Copyright (c) 2022, Maged Magdy. All rights reserved.
 *
 * This work was developed under the supervision of the egFWD scholarship program (Embedded Systems professional Track).
 */


#include "src/App/app.h"


int main(void){
    char decision;
    
    while(1){
        printf("\n");
        if(startApp() == TRY_AGAIN) break; // Start the transaction process
        fflush(stdin); // // Clear any input left in the buffer to avoid interference with scanf
        
        // Prompt the user to decide whether to stop the system or not
        printf("Do you want to stop the system? (y/n): ");
        scanf("%c", &decision);
        if(decision == 'y' || decision == 'Y') break;
        fflush(stdin); // Clears the input buffer to remove any unwanted characters like "\n" from the user input
    }
    return 0;
}
