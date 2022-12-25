/* 
 * File: cardTest.c
 * 
 * Description:
 * Unit testing of card functions
 * 
 * Author: Maged Magdy Asaad
 * Date: December 25, 2022
 * 
 * Copyright (c) 2022, Maged Magdy. All rights reserved.
 *
 * This work was developed under the supervision of the egFWD scholarship program (Embedded Systems professional Track).
 */


#include<stdio.h>
#include<string.h>
#include "../src/LIB/STD_TYPES.h"
#include "../src/Card/card.h"


#define TEST_CASES_N 4

ST_cardData_t cardData;

void getCardHolderNameTest(void);
void getCardExpiryDateTest(void);
void getCardPANTest(void);

int main(void){
    // getCardHolderNameTest();
    // getCardExpiryDateTest();
    getCardPANTest();

    return 0;
}

void getCardHolderNameTest(void){
    printf("\nTester Name: Maged Magdy\n");
    printf("Function Name: getCardHolderName()\n");
    for(int i=1; i<=TEST_CASES_N; i++){
        printf("------------------------------------------------------------------\n");
        printf("Test Case %d:\n", i);
        EN_cardError_t error = getCardHolderName(&cardData);
        switch(i){
            case 1:
                printf("Input Data: NULL\n");
                printf("Expected Result: %d\n", WRONG_NAME);
                printf("Actual Result: %d\n", error); 
                break;
            case 2:
                printf("Input Data: Maged Magdy\n");
                printf("Expected Result: %d\n", WRONG_NAME);
                printf("Actual Result: %d\n", error);
                break;
            case 3:
                printf("Input Data: Maged Magdy Asaad Kamel Asaad\n");
                printf("Expected Result: %d\n", WRONG_NAME);
                printf("Actual Result: %d\n", error);
                break;
            case 4:
                printf("Input Data: Maged Magdy Asaad Kamel\n");
                printf("Expected Result: %d\n", CARD_OK);
                printf("Actual Result: %d\n", error);
                break;
        }
    }
}

void getCardExpiryDateTest(void){
    printf("\nTester Name: Maged Magdy\n");
    printf("Function Name: getCardExpiryDate()\n");
    for(int i=1; i<=TEST_CASES_N; i++){
        printf("------------------------------------------------------------------\n");
        printf("Test Case %d:\n", i);
        EN_cardError_t error = getCardExpiryDate(&cardData);
        switch(i){
            case 1:
                printf("Input Data: NULL\n");
                printf("Expected Result: %d\n", WRONG_EXP_DATE);
                printf("Actual Result: %d\n", error); 
                break;
            case 2:
                printf("Input Data: 05/2\n");
                printf("Expected Result: %d\n", WRONG_EXP_DATE);
                printf("Actual Result: %d\n", error);
                break;
            case 3:
                printf("Input Data: 05/25/2022\n");
                printf("Expected Result: %d\n", WRONG_EXP_DATE);
                printf("Actual Result: %d\n", error);
                break;
            case 4:
                printf("Input Data: 05/25\n");
                printf("Expected Result: %d\n", CARD_OK);
                printf("Actual Result: %d\n", error);
                break;
        }
    }
}

void getCardPANTest(void){
    printf("\nTester Name: Maged Magdy\n");
    printf("Function Name: getCardPAN()\n");
    for(int i=1; i<=TEST_CASES_N; i++){
        printf("------------------------------------------------------------------\n");
        printf("Test Case %d:\n", i);
        EN_cardError_t error = getCardPAN(&cardData);
        switch(i){
            case 1:
                printf("Input Data: NULL\n");
                printf("Expected Result: %d\n", WRONG_PAN);
                printf("Actual Result: %d\n", error); 
                break;
            case 2:
                printf("Input Data: 123456789876532\n");
                printf("Expected Result: %d\n", WRONG_PAN);
                printf("Actual Result: %d\n", error);
                break;
            case 3:
                printf("Input Data: 12345678987653212345\n");
                printf("Expected Result: %d\n", WRONG_PAN);
                printf("Actual Result: %d\n", error);
                break;
            case 4:
                printf("Input Data: 1234567898765321\n");
                printf("Expected Result: %d\n", CARD_OK);
                printf("Actual Result: %d\n", error);
                break;
        }
    }
}