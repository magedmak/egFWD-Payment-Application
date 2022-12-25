/* 
 * File: terminal.c
 * 
 * Description:
 * This file contains the declarations and data structures needed for the terminal component
 * of a card payment system simulation. The component includes functions for getting and
 * validating the transaction date, amount, and card primary account number, as well as
 * setting and checking the maximum transaction amount.
 * 
 * Author: Maged Magdy Asaad
 * Date: December 25, 2022
 * 
 * Copyright (c) 2022, Maged Magdy. All rights reserved.
 *
 * This work was developed under the supervision of the egFWD scholarship program (Embedded Systems professional Track).
 */


#include "terminal.h"


/************************************************************
 *                      INPUT FUNCTIONS                     *
 ************************************************************/

/* 
Function: getTransactionDate()
- Receives a pointer to an ST_terminalData_t type variable
- Asks the user to input the transaction date
- Validates the input by checking its length
- Returns:
  - TERMINAL_OK if the date is valid
  - WRONG_DATE if the date is invalid
*/
EN_terminalError_t getTransactionDate(ST_terminalData_t *termData){
    printf("Enter the Transaction Date: ");
    gets(termData->transactionDate);
    if(termData->transactionDate == NULL || strlen(termData->transactionDate)<10 || strlen(termData->transactionDate)>10) return WRONG_DATE;
    else return TERMINAL_OK;
}

/* 
Function: getTransactionAmount()
- Receives a pointer to an ST_terminalData_t type variable
- Asks the user to input the transaction amount
- Validates the input by checking if it is a positive number
- Returns:
  - TERMINAL_OK if the amount is valid
  - INVALID_AMOUNT if the amount is invalid
*/
EN_terminalError_t getTransactionAmount(ST_terminalData_t *termData){
    printf("Enter the Transaction Amount: ");
    scanf("%f", &termData->transAmount);
    if(termData->transAmount <= 0) return INVALID_AMOUNT;
    else return TERMINAL_OK;
}


/************************************************************
 *                        VALIDATION                        *
 ************************************************************/

/* 
Function: isCardExpired()
- Receives pointers to ST_cardData_t and ST_terminalData_t type variables
- Extracts the expiration date and transaction date from the respective variables
- Compares the expiration date and transaction date
- Returns:
  - TERMINAL_OK if the card has not expired
  - EXPIRED_CARD if the card has expired
*/
EN_terminalError_t isCardExpired(ST_cardData_t *cardData, ST_terminalData_t *termData){
    uint8_t cardExpMonth = ((cardData->cardExpirationDate[0] - '0') * 10) + (cardData->cardExpirationDate[1] - '0'); //MM
    uint8_t cardExpYear  = ((cardData->cardExpirationDate[3] - '0') * 10) + (cardData->cardExpirationDate[4] - '0'); //YY
    
    uint8_t transDataMonth = ((termData->transactionDate[3] - '0') * 10) + (termData->transactionDate[4] - '0'); //MM
    uint8_t transDataYear  = ((termData->transactionDate[8] - '0') * 10) + (termData->transactionDate[9] - '0'); //YY

    if(cardExpYear < transDataYear){
        return EXPIRED_CARD;
    }else if(cardExpYear == transDataYear){
        if (cardExpMonth < transDataMonth) return EXPIRED_CARD;
    }
    return TERMINAL_OK;
}

/*
Function: isBelowMaxAmount()
- Receives a pointer to an ST_terminalData_t type variable
- Validates the transaction amount by checking if it is above the maximum allowed amount
- Returns:
  - TERMINAL_OK if the amount is below the maximum allowed amount
  - EXCEED_MAX_AMOUNT if the amount is above the maximum allowed amount
*/
EN_terminalError_t isBelowMaxAmount(ST_terminalData_t *termData){
    if(termData->transAmount > termData->maxTransAmount) return EXCEED_MAX_AMOUNT;
    else return TERMINAL_OK;
}

/*
Function:  isValidCardPAN()
- Receives a pointer to an ST_cardData_t type variable
- Validates the Primary Account Number (PAN) of the card by performing a Luhn check
- Returns:
  - TERMINAL_OK if the PAN is valid
  - INVALID_CARD if the PAN is invalid
*/
EN_terminalError_t isValidCardPAN(ST_cardData_t *cardData){
    uint8_t temp, sum = 0, i = 0;
    const uint8_t PAN_SIZE = strlen(cardData->primaryAccountNumber) - 1;

    while(i<PAN_SIZE+1){
        if(i&1){
            temp = (cardData->primaryAccountNumber[PAN_SIZE - i++] - '0');
            temp *= 2;
            temp > 9? (temp -= 9):(temp -= 0);
            sum += temp;            
        }else{
            temp = (cardData->primaryAccountNumber[PAN_SIZE - i++] - '0');
            sum += temp;
        }
    }
    
    if(sum%10) return INVALID_CARD;
    else return TERMINAL_OK;
}


/************************************************************
 *                         SETTINGS                         *
 ************************************************************/

/* 
Function: setMaxAmount()
- Receives a pointer to an ST_terminalData_t type variable and a float value
- Sets the maximum transaction amount
- Validates the maximum amount by checking if it is a positive number
- Returns:
  - TERMINAL_OK if the maximum amount is valid
  - INVALID_MAX_AMOUNT if the maximum amount is invalid
*/
EN_terminalError_t setMaxAmount(ST_terminalData_t *termData, float maxAmount){
    termData->maxTransAmount = maxAmount;
    if(termData->maxTransAmount <= 0) return INVALID_MAX_AMOUNT;
    else return TERMINAL_OK;
}