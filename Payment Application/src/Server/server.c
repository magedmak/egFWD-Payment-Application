/* 
 * File: server.c
 * 
 * Description:
 * This file contains the declarations and data structures needed for the server component
 * of a card payment system simulation. The component includes functions for checking the
 * validity of an account, checking if an account is blocked, checking if there are sufficient
 * funds for a transaction, saving a transaction to the database, and listing saved transactions.
 * 
 * Author: Maged Magdy Asaad
 * Date: December 25, 2022
 * 
 * Copyright (c) 2022, Maged Magdy. All rights reserved.
 *
 * This work was developed under the supervision of the egFWD scholarship program (Embedded Systems professional Track).
 */


#include "server.h"


#define DB_SIZE 255


/************************************************************
 *                     DATABASE VARIABLES                   *
 ************************************************************/

/* 
- Array of ST_accountsDB_t type variables representing the accounts database
- Each variable has the following fields:
  - balance: the current balance of the account
  - state: the status of the account (RUNNING or BLOCKED)
  - primaryAccountNumber: the Primary Account Number (PAN) of the account
*/
ST_accountsDB_t accountsDB[DB_SIZE] = { 
                                {1000, RUNNING, "789456123123456798"},
                                {5000, RUNNING, "456123789456123789"},
                                {3000, BLOCKED, "123798456123465987"},
                                {2000, RUNNING, "321654987456132798"},
                                {9000, BLOCKED, "654789123654987321"},
                                {7000, RUNNING, "648971248962468452"},
                                {6000, BLOCKED, "654987123456798732"},
                                {1000, BLOCKED, "321546789513654897"},
                                {4000, RUNNING, "136871323216548751"},
                                {8000, RUNNING, "645854132168787654"}};

/* Declares an array of ST_transaction_t type with a size of DB_SIZE and initializes it with 0 */
ST_transaction_t transDB[DB_SIZE] = {0};


/************************************************************
 *                         VARIABLES                        *
 ************************************************************/

/* Declares a pointer to ST_accountsDB_t type and initializes it with NULL */
ST_accountsDB_t *reference = NULL;

/* Declares a variable of uint32_t type and initializes it with 0 */
uint32_t sequenceNum = 0;


/************************************************************
 *                      MAIN FUNCTION                       *
 ************************************************************/

/* 
Function: recieveTransactionData()
- Receives a pointer to an ST_transaction_t type variable
- Calls different helper functions to validate the transaction data
- If the transaction is valid, it updates the account balance and saves the transaction
- Returns the state of the transaction:
  - FRAUD_CARD if the card is not valid
  - DECLINED_INSUFFICIENT_FUND if the balance is insufficient
  - DECLINED_STOLEN_CARD if the account is blocked
  - INTERNAL_SERVER_ERROR if the transaction could not be saved
  - APPROVED if the transaction is valid and successful
*/
EN_transState_t recieveTransactionData(ST_transaction_t *transData){
    if(isValidAccount(&transData->cardHolderData)){
        transData->transState = FRAUD_CARD;
        return FRAUD_CARD;
    } 
    if(isAmountAvailable(&transData->terminalData)){
        transData->transState = DECLINED_INSUFFICIENT_FUND;
        return DECLINED_INSUFFICIENT_FUND;
    } 
    if(isBlockedAccount()){
        transData->transState = DECLINED_STOLEN_CARD;
        return DECLINED_STOLEN_CARD;
    } 
    if(SAVING_FAILED == saveTransaction(transData)){
        transData->transState = INTERNAL_SERVER_ERROR;
        return INTERNAL_SERVER_ERROR;
    } 
    
    /* Updates the account balance by subtracting the transaction amount */
    reference->balance -= transData->terminalData.transAmount; 
    transData->transState = APPROVED; 
    return APPROVED;
}


/************************************************************
 *                     AUXILIARY FUNCTIONS                  *
 ************************************************************/

/* 
Function: isValidAccount()
- Receives a pointer to an ST_cardData_t type variable
- Loops through the accountsDB array and checks if the primary account number of the cardData matches any of the elements
- If a match is found, it sets the reference pointer to the matching element
- Returns:
  - SERVER_OK if a matching element is found
  - ACCOUNT_NOT_FOUND if no matching element is found
*/
EN_serverError_t isValidAccount(ST_cardData_t *cardData){
    for(int i=0; i<DB_SIZE; i++){
        if(strcmp(cardData->primaryAccountNumber, accountsDB[i].primaryAccountNumber)==0){
            reference = &accountsDB[i];
            return SERVER_OK;
        }
    }
    return ACCOUNT_NOT_FOUND;
}

/* 
Function: isBlockedAccount()
- Checks the state of the account pointed by the reference pointer
- Returns:
  - SERVER_OK if the account state is RUNNING
  - BLOCKED_ACCOUNT if the account state is BLOCKED
*/
EN_serverError_t isBlockedAccount(void){
    if(reference->state == RUNNING) return SERVER_OK;
    return BLOCKED_ACCOUNT;
}

/* 
Function: isAmountAvailable()
- Receives a pointer to an ST_terminalData_t type variable
- Compares the transaction amount with the account balance pointed by the reference pointer
- Returns:
  - SERVER_OK if the balance is sufficient
  - LOW_BALANCE if the balance is insufficient
*/
EN_serverError_t isAmountAvailable(ST_terminalData_t *termData){
    if(termData->transAmount > reference->balance) return LOW_BALANCE;
    return SERVER_OK;
}

/* 
Function: saveTransaction()
- Receives a pointer to an ST_transaction_t type variable
- Copies the transaction data to the transDB array
- Updates the transaction state and sequence number
- Calls the listSavedTransactions function to print the saved transaction
- Returns:
  - SERVER_OK if the transaction was saved successfully
  - SAVING_FAILED if the transaction could not be saved
*/
EN_serverError_t saveTransaction(ST_transaction_t *transData){
    if(sequenceNum >= DB_SIZE) return SAVING_FAILED;
    transDB[sequenceNum].cardHolderData = transData->cardHolderData;
    transDB[sequenceNum].terminalData = transData->terminalData;
    transDB[sequenceNum].transState = transData->transState;
    transData->transactionSequenceNumber = sequenceNum;
    transDB[sequenceNum].transactionSequenceNumber = transData->transactionSequenceNumber;
    listSavedTransactions();
    sequenceNum++;
    return SERVER_OK;
}

/*
Function: listSavedTransactions()
- Lists the saved transactions in the transaction database
- Prints the transaction details to the console
*/
void listSavedTransactions(void){
    printf("#########################\n");
	printf("Transaction Sequence Number: %ld\n", transDB[sequenceNum].transactionSequenceNumber);
	printf("Transaction Date: %s\n", transDB[sequenceNum].terminalData.transactionDate);
	printf("Transaction Amount: %.2f\n", transDB[sequenceNum].terminalData.transAmount);
	printf("Transaction State: %s\n", getTransactionStatus(transDB[sequenceNum].transState));
	printf("Terminal Max Amount: %.2f\n", transDB[sequenceNum].terminalData.maxTransAmount);
	printf("Cardholder Name: %s\n", transDB[sequenceNum].cardHolderData.cardHolderName);
	printf("PAN: %s\n", transDB[sequenceNum].cardHolderData.primaryAccountNumber);
	printf("Card Expiration Date: %s\n", transDB[sequenceNum].cardHolderData.cardExpirationDate);
	printf("#########################\n");
}

/* 
Function: getTransactionStatus()
- Receives an EN_transState_t type variable
- Returns a string representation of the transaction state
*/
char* getTransactionStatus(EN_transState_t transState){
    switch(transState){
        case APPROVED: return "Approved";
        case DECLINED_INSUFFICIENT_FUND: return "Declined (Insufficient fund)";
        case DECLINED_STOLEN_CARD: return "Declined (Blocked Account)";
        case FRAUD_CARD: return "Declined (Fraud Card)";
        case INTERNAL_SERVER_ERROR: return "Declined (Internal Server Error)";
        default: return "UNKNOWN";
    }
}