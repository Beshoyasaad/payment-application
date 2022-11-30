#include "app.h"

extern ST_accountsDB_t accounts[MAXACCOUNTSAVAILABLE];
extern ST_transaction_t tran[MAXACCOUNTSAVAILABLE];

int i, seq;


void appStart(void)
{
	initial_accountDB();
	ST_transaction_t transaction = { 0 };
	uint8_t app_card_error = 0;
	uint8_t app_terminal_error = 0;
	uint8_t app_server_error = 0;




	app_card_error = getCardHolderName(&(transaction.cardHolderData));
	if (WRONG_NAME == app_card_error) {
		printf("\nwrong name error\n");
		return;
	}




	app_card_error = getCardExpiryDate(&(transaction.cardHolderData));
	if (WRONG_EXP_DATE == app_card_error) {
		printf("\nexpiration date error\n");
		return;
	}

	else {
		printf("correct card expiration date\n");
	}


	app_card_error = getCardPAN(&(transaction.cardHolderData));
	if (WRONG_PAN == app_card_error) {
		printf("Wrong pan numbers\n");
		return;

	}
	else {
		printf("correct pan number\n");
	}





	app_terminal_error = getTransactionDate(&(transaction.terminalData));
	if (WRONG_DATE == app_terminal_error) {
		printf("Wrong Transaction Date\n");
		return;
	}

	else {
		printf("correct transaction date\n");

	}


	app_terminal_error = isCardExpired(&(transaction.cardHolderData), &(transaction.terminalData));

	if (EXPIRED_CARD == app_terminal_error) {
		printf(" Card expired Please, go to the bank to activate your card\n");
		return;
	}

	uint8_t t_z = '0';
	uint8_t t_z_buff = '0';
	printf("please enter 0 to block your account or 1 to continue\n");
	t_z = getchar();
	t_z_buff = getchar();

	if (t_z == '0') {
		accounts[i].state = BLOCKED;
		printf("Now your account is blocked\n");

	}
	else
	{
			app_terminal_error = setMaxAmount(&(transaction.terminalData),10000);

			app_terminal_error = getTransactionAmount(&(transaction.terminalData));
		}

			if (INVALID_AMOUNT == app_terminal_error) {
				printf(" Invalid transaction amount, please enter a positive value.\n");
			
			}
			
			else {

			}


			app_terminal_error = isBelowMaxAmount(&(transaction.terminalData));

			if (EXCEED_MAX_AMOUNT == app_terminal_error) {
				printf("Invalid transaction amount, exceeded the max value\n");
				return;
			}
			else {
				printf("the data is processesing now please wait \n");

			}
		

			app_server_error = recieveTransactionData(&transaction);


			app_server_error = saveTransaction(&transaction);
			if (DECLINED_STOLEN_CARD == app_terminal_error || LOW_BALANCE == app_terminal_error)
			{
				printf("\nNot saved\n");
			}
			else
			{
				printf("\nsaved\n");
			}

			return;
			}

