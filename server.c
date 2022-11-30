#include "server.h"
#include <stdio.h>
int i, seq;

EN_transState_t recieveTransactionData(ST_transaction_t* transData)
{
   
    uint8_t localserver_error;
   
    
    localserver_error = isValidAccount(&(transData->cardHolderData), &(transData->transactionSequenceNumber));
    if (localserver_error == DECLINED_STOLEN_CARD) {
        printf("Invalid account.\n");
        return FRAUD_CARD;
    }
    else
    {

    }



    localserver_error = isAmountAvailable(&(transData->terminalData));
    if (localserver_error == LOW_BALANCE)
    {
        printf("NO ENOUGH BALANCE!\n");
        return DECLINED_INSUFFECIENT_FUND;
    }
    else
    {
       
    }



    localserver_error = saveTransaction(transData);
    if (localserver_error == SAVING_FAILED)
    {
        printf("SOMETHING WENT WRONG!\n");
        return INTERNAL_SERVER_ERROR;
    }
    else
    {

    }

    localserver_error = isBlockedAccount(&(accounts[i]));
    if (localserver_error == BLOCKED_ACCOUNT) {
        printf("sorry, this account is blocked you can't do any operation.\n");
        return DECLINED_INSUFFECIENT_FUND;
    }
    else {
    
    }
    printf( "###########################################################\n\n");
    printf("account is available \n");
    printf("amount is available waitting for calculating.......\n");
    printf("please take the card and wait for money........\n");
    printf("===================================\n");
    printf("###########################################################\n\n");
    printf("-Card Holder Name:- %s\n", transData->cardHolderData);
    printf( "-Card PAN:- %s\n", transData->cardHolderData.primaryAccountNumber);
    printf( "-Card Expiry Date:- %s\n", transData->cardHolderData.cardExpirationDate);
    printf( "-Transaction Date:- %s", transData->terminalData.transactionDate);
    printf( "-Transaction Max Amount:- %.2f\n", transData->terminalData.maxTransAmount);
    printf( "-Transaction Amount:- %.2f\n", transData->terminalData.transAmount);
    printf("balance before transaction = %f ", accounts[i].balance);
    printf("\nwithdraw amount  = %f ", transData->terminalData.transAmount);
    accounts[i].balance -= transData->terminalData.transAmount;
    printf("\nbalance after transaction = %f ", accounts[i].balance);
    printf("\n###########################################################\n\n");

    return APPROVED;

}


EN_serverError_t isValidAccount(ST_cardData_t* cardData,ST_accountsDB_t** accountRefrence)
{
    for (i = 0; i < MAXACCOUNTSAVAILABLE; i++)
    {
        if (!(strcmp((char*)cardData->primaryAccountNumber, (char*)accounts[i].primaryAccountNumber)))
        {
            
            return SERVER_OK;

        }
    }
    *accountRefrence = NULL;
   
    return ACCOUNT_NOT_FOUND;
}



EN_serverError_t isBlockedAccount(ST_accountsDB_t* accountRefrence) {
    if (BLOCKED == accountRefrence->state) {
        return BLOCKED_ACCOUNT;
    }
    else {
        return SERVER_OK;
    }
}



EN_serverError_t isAmountAvailable(ST_terminalData_t* termData) {
    if (accounts[i].balance < termData->transAmount) {
        return LOW_BALANCE;
    }
    
    return SERVER_OK;

}



EN_serverError_t saveTransaction(ST_transaction_t* transData) {
    transData->transactionSequenceNumber = seq;
    seq++;
    if (DECLINED_STOLEN_CARD == transData->transState || LOW_BALANCE == transData->transState) {
       
        return SAVING_FAILED;
    }
    return SERVER_OK;
}



