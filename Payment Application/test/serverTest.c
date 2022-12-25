/* 
 * File: serverTest.c
 * 
 * Description:
 * Unit testing of server functions
 * 
 * Author: Maged Magdy Asaad
 * Date: December 25, 2022
 * 
 * Copyright (c) 2022, Maged Magdy. All rights reserved.
 *
 * This work was developed under the supervision of the egFWD scholarship program (Embedded Systems professional Track).
 */


#include "../src/Server/server.h"

ST_transaction_t transData;

void recieveTransactionDataTest(void);
void isValidAccountTest(void);
void isBlockedAccountTest(void);
void isAmountAvailableTest(void);
void saveTransactionTest(void); // to run this test you should comment the listSavedTransaction CALL from  server.c
void listSavedTransactionsTest(void);

int main(void){
    //recieveTransactionDataTest();
    //isValidAccountTest();
    //isBlockedAccountTest();
    //isAmountAvailableTest();
    //saveTransactionTest(); 
    listSavedTransactionsTest();

    return 0;
}

void recieveTransactionDataTest(void){
    printf("\nTester Name: Maged Magdy\n");
    printf("Function Name: recieveTransactionData()\n");
    EN_serverError_t error;
    for(int i=1; i<5; i++){
        printf("------------------------------------------------------------------\n");
        printf("Test Case %d:\n", i);
        switch(i){
            case 1:
                strcpy(transData.cardHolderData.primaryAccountNumber, "164926588962466498");
                error = recieveTransactionData(&transData);
                printf("Input Data: \n");
                printf("PAN = %s \n", transData.cardHolderData.primaryAccountNumber);
                printf("Expected Result: %d\n", FRAUD_CARD);
                printf("Actual Result: %d\n", error); 
                break;
            case 2:
                strcpy(transData.cardHolderData.primaryAccountNumber, "321654987456132798");
                transData.terminalData.transAmount = 3000;
                error = recieveTransactionData(&transData);
                printf("Input Data: \n");
                printf("PAN = %s \n", transData.cardHolderData.primaryAccountNumber);
                printf("Transaction Amount = %.2f \n", transData.terminalData.transAmount);
                printf("Expected Result: %d\n", DECLINED_INSUFFICIENT_FUND);
                printf("Actual Result: %d\n", error);
                break;
            case 3:
                strcpy(transData.cardHolderData.primaryAccountNumber, "123798456123465987");
                transData.terminalData.transAmount = 2000;
                error = recieveTransactionData(&transData);
                printf("Input Data: \n");
                printf("PAN = %s \n", transData.cardHolderData.primaryAccountNumber);
                printf("Transaction Amount = %.2f \n", transData.terminalData.transAmount);
                printf("Account State is Blocked.\n");
                printf("Expected Result: %d\n", DECLINED_STOLEN_CARD);
                printf("Actual Result: %d\n", error);
                break;
            case 4:
                strcpy(transData.cardHolderData.primaryAccountNumber, "456123789456123789");
                transData.terminalData.transAmount = 2000;
                error = recieveTransactionData(&transData);
                printf("Input Data: \n");
                printf("PAN = %s \n", transData.cardHolderData.primaryAccountNumber);
                printf("Transaction Amount = %.2f \n", transData.terminalData.transAmount);
                printf("Account State is Running.\n");
                printf("Expected Result: %d\n", APPROVED);
                printf("Actual Result: %d\n", error);
                break;
        }
    }
}

void isValidAccountTest(void){
    printf("\nTester Name: Maged Magdy\n");
    printf("Function Name: isValidAccount()\n");
    EN_serverError_t error;
    for(int i=1; i<=2; i++){
        printf("------------------------------------------------------------------\n");
        printf("Test Case %d:\n", i);
        switch(i){
            case 1:
                strcpy(transData.cardHolderData.primaryAccountNumber, "164926588962466498");
                error = isValidAccount(&transData.cardHolderData);
                printf("Input Data: %s\n", transData.cardHolderData.primaryAccountNumber);
                printf("Expected Result: %d\n", ACCOUNT_NOT_FOUND);
                printf("Actual Result: %d\n", error); 
                break;
            case 2:
                strcpy(transData.cardHolderData.primaryAccountNumber, "654987123456798732");
                error = isValidAccount(&transData.cardHolderData);
                printf("Input Data: %s\n", transData.cardHolderData.primaryAccountNumber);
                printf("Expected Result: %d\n", SERVER_OK);
                printf("Actual Result: %d\n", error);
                break;
        }
    }
}

void isBlockedAccountTest(void){
    printf("\nTester Name: Maged Magdy\n");
    printf("Function Name: isBlockedAccount()\n");
    EN_serverError_t error;
    for(int i=1; i<=2; i++){
        printf("------------------------------------------------------------------\n");
        printf("Test Case %d:\n", i);
        switch(i){
            case 1:
                strcpy(transData.cardHolderData.primaryAccountNumber, "123798456123465987");
                isValidAccount(&transData.cardHolderData);
                error = isBlockedAccount();
                printf("Input Data: %s\n", transData.cardHolderData.primaryAccountNumber);
                printf("Expected Result: %d\n", BLOCKED_ACCOUNT);
                printf("Actual Result: %d\n", error); 
                break;
            case 2:
                strcpy(transData.cardHolderData.primaryAccountNumber, "136871323216548751");
                isValidAccount(&transData.cardHolderData);
                error = isBlockedAccount();
                printf("Input Data: %s\n", transData.cardHolderData.primaryAccountNumber);
                printf("Expected Result: %d\n", SERVER_OK);
                printf("Actual Result: %d\n", error);
                break;
        }
    }
}

void isAmountAvailableTest(void){
    printf("\nTester Name: Maged Magdy\n");
    printf("Function Name: isAmountAvailable()\n");
    EN_serverError_t error;
    for(int i=1; i<=3; i++){
        printf("------------------------------------------------------------------\n");
        printf("Test Case %d:\n", i);
        switch(i){
            case 1:
                strcpy(transData.cardHolderData.primaryAccountNumber, "321654987456132798");
                isValidAccount(&transData.cardHolderData);
                transData.terminalData.transAmount = 3000;
                error = isAmountAvailable(&transData.terminalData);
                printf("Input Data: %.2f\n", transData.terminalData.transAmount);
                printf("Expected Result: %d\n", LOW_BALANCE);
                printf("Actual Result: %d\n", error); 
                break;
            case 2:
                strcpy(transData.cardHolderData.primaryAccountNumber, "321654987456132798");
                isValidAccount(&transData.cardHolderData);
                transData.terminalData.transAmount = 2000;
                error = isAmountAvailable(&transData.terminalData);
                printf("Input Data: %.2f\n", transData.terminalData.transAmount);
                printf("Expected Result: %d\n", SERVER_OK);
                printf("Actual Result: %d\n", error); 
                break;
            case 3:
                strcpy(transData.cardHolderData.primaryAccountNumber, "321654987456132798");
                isValidAccount(&transData.cardHolderData);
                transData.terminalData.transAmount = 1000;
                error = isAmountAvailable(&transData.terminalData);
                printf("Input Data: %.2f\n", transData.terminalData.transAmount);
                printf("Expected Result: %d\n", SERVER_OK);
                printf("Actual Result: %d\n", error);
                break;
        }
    }
}

void saveTransactionTest(void){
    printf("\nTester Name: Maged Magdy\n");
    printf("Function Name: saveTransaction()\n");
    EN_serverError_t error;
    for(int i=1; i<=2; i++){
        printf("------------------------------------------------------------------\n");
        printf("Test Case %d:\n", i);
        switch(i){
            case 1:
                strcpy(transData.cardHolderData.cardHolderName, "Maged Magdy Asaad Kamel");
                strcpy(transData.cardHolderData.primaryAccountNumber, "321654987456132798");
                strcpy(transData.cardHolderData.cardExpirationDate, "05/22");
                strcpy(transData.terminalData.transactionDate, "25/02/2021");
                transData.terminalData.maxTransAmount = 20000;
                transData.terminalData.transAmount = 500;
                printf("Input Data: sequence number of transaction = 0\n");
                error = saveTransaction(&transData);
                printf("Expected Result: %d\n", SERVER_OK);
                printf("Actual Result: %d\n", error); 
                break;
            case 2:
                strcpy(transData.cardHolderData.cardHolderName, "Maged Magdy Asaad Kamel");
                strcpy(transData.cardHolderData.primaryAccountNumber, "321654987456132798");
                strcpy(transData.cardHolderData.cardExpirationDate, "05/22");
                strcpy(transData.terminalData.transactionDate, "25/02/2021");
                transData.terminalData.maxTransAmount = 20000;
                transData.terminalData.transAmount = 1;
                printf("Input Data: sequence number of transaction = 255\n");
                for(int j=0; j<=255; j++) error = saveTransaction(&transData);
                printf("Expected Result: %d\n", SAVING_FAILED);
                printf("Actual Result: %d\n", error); 
                break;
        }
    }
}

void listSavedTransactionsTest(void){
    printf("\nTester Name: Maged Magdy\n");
    printf("Function Name: listSavedTransactions()\n");
    EN_serverError_t error;
    for(int i=1; i<2; i++){
        printf("------------------------------------------------------------------\n");
        printf("Test Case %d:\n", i);
        switch(i){
            case 1:
                strcpy(transData.cardHolderData.cardHolderName, "Maged Magdy Asaad Kamel");
                strcpy(transData.cardHolderData.primaryAccountNumber, "321654987456132798");
                strcpy(transData.cardHolderData.cardExpirationDate, "05/22");
                strcpy(transData.terminalData.transactionDate, "25/02/2021");
                transData.terminalData.maxTransAmount = 20000;
                transData.terminalData.transAmount = 500;
                error = saveTransaction(&transData);
                break;
        }
    }
}