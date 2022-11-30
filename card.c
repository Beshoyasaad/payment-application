#include <stdio.h>
#include "card.h"


#define MaxCardHolderName 24
#define MinCardHolderName 20
#define MaxExpDate 5
#define MaxPanNum 19
#define MinPanNum 16




EN_cardError_t getCardHolderName(ST_cardData_t* cardData)
{

	EN_cardError_t retr= CARD_OK;
	
	printf("Enter your card name : ");
	gets(cardData->cardHolderName); 

	uint8_t length = strlen(cardData->cardHolderName);

	if (NULL == cardData || cardData->cardHolderName == NULL || MaxCardHolderName < length || MinCardHolderName > length)
	{
		retr= WRONG_NAME;
	}
	else {
		printf("Hello, %s\n", cardData->cardHolderName);
		retr= CARD_OK;
	}
	return retr;

}




EN_cardError_t getCardExpiryDate(ST_cardData_t* cardData)
{
	EN_cardError_t retr = CARD_OK;

	printf("\nEnter card expiry date in mm/yy format: ");
	gets(cardData->cardExpirationDate);

	uint8_t length = strlen(cardData->cardExpirationDate);
	if (NULL == cardData || cardData->cardExpirationDate == NULL || MaxExpDate != length || cardData->cardExpirationDate[2] != '/')

	{
		retr = WRONG_EXP_DATE;
		
	}
	else {
		retr = CARD_OK;

	}
	return retr;

		
}



EN_cardError_t getCardPAN(ST_cardData_t* cardData)

{
	EN_cardError_t retr = CARD_OK;

	printf("\nEnter the 16 pan numbers :" );

	gets(cardData->primaryAccountNumber);
	uint8_t lenght = strlen(cardData->primaryAccountNumber);

	if (NULL == cardData || cardData->primaryAccountNumber == NULL || MaxPanNum < lenght || MinPanNum > lenght) {

		retr = WRONG_PAN;
		
	}
	else {
		retr = CARD_OK;
	}
	return retr;


}











