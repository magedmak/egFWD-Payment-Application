/* 
 * File: card.c
 * 
 * Description:
 * This file contains the declarations and data structures needed for the card component
 * of a card payment system simulation. The component includes functions for getting
 * and validating the card holder's name, expiry date, and primary account number.
 * 
 * Author: Maged Magdy Asaad
 * Date: December 25, 2022
 * 
 * Copyright (c) 2022, Maged Magdy. All rights reserved.
 *
 * This work was developed under the supervision of the egFWD scholarship program (Embedded Systems professional Track).
 */
 

#include "card.h"


/* 
Function: getCardHolderName()
- Prompts the user to enter the cardholder's name
- Reads the input and stores it in the cardData struct
- Validates the name:
  - Not empty
  - Length between 20 and 24 characters
- Returns:
  - CARD_OK if the name is valid
  - WRONG_NAME if the name is invalid
*/
EN_cardError_t getCardHolderName(ST_cardData_t *cardData){
    printf("Enter Cardholder's Name: ");
    gets(cardData->cardHolderName);
    if(cardData->cardHolderName == NULL || strlen(cardData->cardHolderName)<20 || strlen(cardData->cardHolderName)>24) return WRONG_NAME;
    else return CARD_OK;
}

/* 
Function: getCardExpiryDate()
- Prompts the user to enter the card expiry date
- Reads the input and stores it in the cardData struct
- Validates the expiry date:
  - Not empty
  - Length of 5 characters
- Returns:
  - CARD_OK if the expiry date is valid
  - WRONG_EXP_DATE if the expiry date is invalid
*/
EN_cardError_t getCardExpiryDate(ST_cardData_t *cardData){
    printf("Enter Card Expiry Date: ");
    gets(cardData->cardExpirationDate);
    if(cardData->cardExpirationDate == NULL || strlen(cardData->cardExpirationDate)<5 || strlen(cardData->cardExpirationDate)>5) return WRONG_EXP_DATE;
    else return CARD_OK;
}

/* 
Function: getCardPAN()
- Prompts the user to enter the card primary account number (PAN)
- Reads the input and stores it in the cardData struct
- Validates the PAN:
  - Not empty
  - Length between 16 and 19 characters
- Returns:
  - CARD_OK if the PAN is valid
  - WRONG_PAN if the PAN is invalid
*/
EN_cardError_t getCardPAN(ST_cardData_t *cardData){
    printf("Enter Card Primary Account Number: ");
    gets(cardData->primaryAccountNumber);
    if(cardData->primaryAccountNumber == NULL || strlen(cardData->primaryAccountNumber)<16 || strlen(cardData->primaryAccountNumber)>19) return WRONG_PAN;
    else return CARD_OK;
}