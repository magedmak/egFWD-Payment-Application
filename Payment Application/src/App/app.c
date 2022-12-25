/* 
 * File: app.c
 * 
 * Description:
 * This code implements the main application for processing transactions. 
 * It receives cardholder information and terminal data, validates them, 
 * and sends them to the server for further processing. 
 * If the transaction is approved, it returns APP_OK, 
 * otherwise it returns TRY_AGAIN and saves the transaction data in the server database.
 * 
 * Author: Maged Magdy Asaad
 * Date: December 25, 2022
 * 
 * Copyright (c) 2022, Maged Magdy. All rights reserved.
 *
 * This work was developed under the supervision of the egFWD scholarship program (Embedded Systems professional Track).
 */


#include "app.h"


#define MAX_AMOUNT 3000
ST_cardData_t userCardData;
ST_terminalData_t userTermData;
ST_transaction_t userTransData;

EN_appError_t startApp(void){
    // Receive cardholder information
    if(getCardHolderName(&userCardData) == WRONG_NAME) {printf("Declined (Wrong Name)!\n"); return TRY_AGAIN;}
    if(getCardExpiryDate(&userCardData) == WRONG_EXP_DATE) {printf("Declined (Wrong Expiration Date)!\n"); return TRY_AGAIN;} 
    if(getCardPAN(&userCardData) == WRONG_PAN) {printf("Declined (Wrong PAN)!\n"); return TRY_AGAIN;}

    // Recieve terminal data and validate them
    if(getTransactionDate(&userTermData) == WRONG_DATE) {printf("Declined (Wrong Transaction Date)!\n"); return TRY_AGAIN;}
    if(isCardExpired(&userCardData, &userTermData) == EXPIRED_CARD) {printf("Declined (Expired Card)!\n"); return TRY_AGAIN;}
    if(getTransactionAmount(&userTermData) == INVALID_AMOUNT) {printf("Declined (Invalid Transaction Amount)!\n"); return TRY_AGAIN;}
    if(setMaxAmount(&userTermData, MAX_AMOUNT) == INVALID_MAX_AMOUNT) {printf("Declined (Invalid Max Amount)!\n"); return TRY_AGAIN;}
    if(isBelowMaxAmount(&userTermData) == EXCEED_MAX_AMOUNT) {printf("Declined (Exceed Max Amount)!\n"); return TRY_AGAIN;}

    // Send the data to server
    userTransData.cardHolderData = userCardData; // Set cardholder data in transaction data
    userTransData.terminalData = userTermData; // Set terminal data in transaction data
    // Check if transaction is approved by the server
    EN_transState_t transactionStatus = recieveTransactionData(&userTransData);
    if(transactionStatus == APPROVED) return APP_OK;
    else puts(getTransactionStatus(userTransData.transState));
    return TRY_AGAIN;
}