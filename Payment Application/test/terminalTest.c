/* 
 * File: terminalTest.c
 * 
 * Description:
 * Unit testing of terminal functions
 * 
 * Author: Maged Magdy Asaad
 * Date: December 25, 2022
 * 
 * Copyright (c) 2022, Maged Magdy. All rights reserved.
 *
 * This work was developed under the supervision of the egFWD scholarship program (Embedded Systems professional Track).
 */


#include "../src/Terminal/terminal.h"

ST_cardData_t cardData;
ST_terminalData_t termData;

void getTransactionDateTest(void);
void isCardExpiredTest(void);
void getTransactionAmountTest(void);
void isBelowMaxAmountTest(void);
void setMaxAmountTest(void);
void isValidCardPANTest(void);

int main(void){
    //getTransactionDateTest();
    //isCardExpiredTest();
    //getTransactionAmountTest();
    //isBelowMaxAmountTest();
    //setMaxAmountTest();
    isValidCardPANTest();

    return 0;
}

void getTransactionDateTest(void){
    printf("\nTester Name: Maged Magdy\n");
    printf("Function Name: getTransactionDate()\n");
    for(int i=1; i<=4; i++){
        printf("------------------------------------------------------------------\n");
        printf("Test Case %d:\n", i);
        EN_terminalError_t error = getTransactionDate(&termData);
        switch(i){
            case 1:
                printf("Input Data: NULL\n");
                printf("Expected Result: %d\n", WRONG_DATE);
                printf("Actual Result: %d\n", error); 
                break;
            case 2:
                printf("Input Data: 25/2/2022\n");
                printf("Expected Result: %d\n", WRONG_DATE);
                printf("Actual Result: %d\n", error);
                break;
            case 3:
                printf("Input Data: 25//02//2022\n");
                printf("Expected Result: %d\n", WRONG_DATE);
                printf("Actual Result: %d\n", error);
                break;
            case 4:
                printf("Input Data: 25/02/2022\n");
                printf("Expected Result: %d\n", TERMINAL_OK);
                printf("Actual Result: %d\n", error);
                break;
        }
    }
}

void isCardExpiredTest(void){
    strcpy(cardData.cardExpirationDate, "02/21");
    printf("\nTester Name: Maged Magdy\n");
    printf("Function Name: isCardExpired()\n");
    for(int i=1; i<=3; i++){
        printf("------------------------------------------------------------------\n");
        printf("Test Case %d:\n", i);
        EN_terminalError_t error; 
        switch(i){
            case 1:
                strcpy(termData.transactionDate, "20/01/2022");
                error = isCardExpired(&cardData, &termData);
                printf("Input Data: %s\n", termData.transactionDate);
                printf("Expected Result: %d\n", EXPIRED_CARD);
                printf("Actual Result: %d\n", error); 
                break;
            case 2:
                strcpy(termData.transactionDate, "20/03/2021");
                error = isCardExpired(&cardData, &termData);
                printf("Input Data: %s\n", termData.transactionDate);
                printf("Expected Result: %d\n", EXPIRED_CARD);
                printf("Actual Result: %d\n", error);
                break;
            case 3:
                strcpy(termData.transactionDate, "20/01/2021");
                error = isCardExpired(&cardData, &termData);
                printf("Input Data: %s\n", termData.transactionDate);
                printf("Expected Result: %d\n", TERMINAL_OK);
                printf("Actual Result: %d\n", error);
                break;
        }
    }
}

void getTransactionAmountTest(void){
    printf("\nTester Name: Maged Magdy\n");
    printf("Function Name: getTransactionAmount()\n");
    for(int i=1; i<=3; i++){
        printf("------------------------------------------------------------------\n");
        printf("Test Case %d:\n", i);
        EN_terminalError_t error = getTransactionAmount(&termData);
        switch(i){
            case 1:
                printf("Input Data: 0\n");
                printf("Expected Result: %d\n", INVALID_AMOUNT);
                printf("Actual Result: %d\n", error); 
                break;
            case 2:
                printf("Input Data: -0.5\n");
                printf("Expected Result: %d\n", INVALID_AMOUNT);
                printf("Actual Result: %d\n", error);
                break;
            case 3:
                printf("Input Data: 50.5\n");
                printf("Expected Result: %d\n", TERMINAL_OK);
                printf("Actual Result: %d\n", error);
                break;
        }
    }
}

void isBelowMaxAmountTest(void){
    printf("\nTester Name: Maged Magdy\n");
    printf("Function Name: isBelowMaxAmount()\n");
    termData.maxTransAmount = 1000;
    for(int i=1; i<=2; i++){
        printf("------------------------------------------------------------------\n");
        printf("Test Case %d:\n", i);
        EN_terminalError_t error;
        switch(i){
            case 1:
                termData.transAmount = 2000;
                error = isBelowMaxAmount(&termData);
                printf("Input Data: %.2f\n", termData.transAmount);
                printf("Expected Result: %d\n", EXCEED_MAX_AMOUNT);
                printf("Actual Result: %d\n", error); 
                break;
            case 2:
                termData.transAmount = 500;
                error = isBelowMaxAmount(&termData);
                printf("Input Data: %.2f\n", termData.transAmount);
                printf("Expected Result: %d\n", TERMINAL_OK);
                printf("Actual Result: %d\n", error);
                break;
        }
    }
}

void setMaxAmountTest(void){
    printf("\nTester Name: Maged Magdy\n");
    printf("Function Name: setMaxAmount()\n");
    EN_terminalError_t error;
    for(int i=1; i<=3; i++){
        printf("------------------------------------------------------------------\n");
        printf("Test Case %d:\n", i);
        switch(i){
            case 1:
                printf("Input Data: 0\n");
                error = setMaxAmount(&termData, 0);
                printf("Expected Result: %d\n", INVALID_MAX_AMOUNT);
                printf("Actual Result: %d\n", error); 
                break;
            case 2:
                printf("Input Data: -0.5\n");
                error = setMaxAmount(&termData, -0.5);
                printf("Expected Result: %d\n", INVALID_MAX_AMOUNT);
                printf("Actual Result: %d\n", error);
                break;
            case 3:
                printf("Input Data: 1000\n");
                error = setMaxAmount(&termData, 1000);
                printf("Expected Result: %d\n", TERMINAL_OK);
                printf("Actual Result: %d\n", error);
                break;
        }
    }
}

void isValidCardPANTest(void){
    printf("\nTester Name: Maged Magdy\n");
    printf("Function Name: isValidCardPAN()\n");
    EN_terminalError_t error;
    for(int i=1; i<=2; i++){
        printf("------------------------------------------------------------------\n");
        printf("Test Case %d:\n", i);
        switch(i){
            case 1:
                strcpy(cardData.primaryAccountNumber, "321654987456132798");
                error = isValidCardPAN(&cardData);
                printf("Input Data: %s\n", cardData.primaryAccountNumber);
                printf("Expected Result: %d\n", INVALID_CARD);
                printf("Actual Result: %d\n", error); 
                break;
            case 2:
                strcpy(cardData.primaryAccountNumber, "3216549874561327987");
                error = isValidCardPAN(&cardData);
                printf("Input Data: %s\n", cardData.primaryAccountNumber);
                printf("Expected Result: %d\n", TERMINAL_OK);
                printf("Actual Result: %d\n", error);
                break;
        }
    }
}