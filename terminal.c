
#include "terminal.h"
#include <stdio.h>

typedef unsigned short    uint16_t;


EN_terminalError_t getTransactionDate(ST_terminalData_t* termData)
{

	EN_terminalError_t retr = TERMINAL_OK;

	printf("Enter the transaction date, in DD/MM/YYYY format:");
	gets(termData->transactionDate);

	uint8_t t_lenght = strlen(termData->transactionDate);
	if (NULL == termData || NULL == termData->transactionDate || MaxTransDateSize > t_lenght || termData->transactionDate[2] != '/'
		|| termData->transactionDate[5] != '/')
	{
		retr = WRONG_DATE;
		
	}
	else
	{
		retr = TERMINAL_OK;
	}

	return retr;
}

EN_terminalError_t isCardExpired(ST_cardData_t cardData, ST_terminalData_t termData) 
{
	EN_terminalError_t retr = TERMINAL_OK;
	uint16_t t_expire_year, t_expire_month, t_trans_month, t_trans_year, t_trans_day;
	sscanf(&(cardData.cardExpirationDate), "%d/%d", &t_expire_month, &t_expire_year);
	t_expire_year += 2000;
	sscanf(&(termData.transactionDate), "%d/%d/%d", &t_trans_day, &t_trans_month, &t_trans_year);
	if (t_expire_year < t_trans_year) {
		retr = EXPIRED_CARD;
		printf("EXPIRED\n");
	}
	else if (t_expire_year == t_trans_year && t_expire_month < t_trans_month) {
		retr = EXPIRED_CARD;
		printf("EXPIRED\n");

	}
	else {
		retr = TERMINAL_OK;
		printf("NOT EXPIRED\n");

	}
	return retr;
}

EN_terminalError_t getTransactionAmount(ST_terminalData_t* termData)
{
	EN_terminalError_t retr = TERMINAL_OK;
	uint8_t t_x;
	printf("Enter the transaction amount in postive amount :");

	scanf(" %f", &termData->transAmount);

	scanf("%c", &t_x);

	if (NULL == termData || termData->transAmount <= 0)
	{
		retr = INVALID_AMOUNT;


	}
	else
	{
		retr = TERMINAL_OK;

	}
	return retr;


}



EN_terminalError_t isBelowMaxAmount(ST_terminalData_t* termData)
{
	EN_terminalError_t retr = TERMINAL_OK;
	if (termData->transAmount > termData->maxTransAmount)
	{
		retr = EXCEED_MAX_AMOUNT;
		
	}
	else
	{
		retr = TERMINAL_OK;

	}
	return retr;

}



EN_terminalError_t setMaxAmount(ST_terminalData_t* termData ,float maxAmount)
{
	EN_terminalError_t retr = TERMINAL_OK;
	

	if (maxAmount <= 0)
	{
		retr = INVALID_MAX_AMOUNT;
	
	}
	else
	{
		termData->maxTransAmount = maxAmount;
		printf("MAX AMOUNT WAS SETTED WITH : %f L.E\n", maxAmount);
		retr = TERMINAL_OK;
	}
	return retr;
}





