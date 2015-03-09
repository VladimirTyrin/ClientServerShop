#include "Coder.h"

using namespace std;

//#define _DEBUG_

/* code length :
id - 		sizeof(int)
strlen(item) - 	sizeof(int)
item - 		strlen(item)
price		sizeof(double)
date		DATE_LEN
*/
char * Coder::getCodeByPurchase(Purchase purchase)
{
	int code_len = sizeof(int) + strlen(purchase.item) + sizeof(int) + sizeof(double) + DATE_LEN;
	char * result = new char[code_len + 1];
	result[code_len] = '\0';
	
	char * position = result;
	
	memcpy(position, &purchase.user_id, sizeof(int));
	position += sizeof(int);
	
	int item_len = strlen(purchase.item);
	memcpy(position, &item_len, sizeof(int));
	position += sizeof(int);
	
	memcpy(position, purchase.item, item_len);
	position += item_len;
	
	memcpy(position, &purchase.price, sizeof(double));
	position += sizeof(double);
	
	memcpy(position, purchase.date, DATE_LEN);
	position += DATE_LEN;
	
	return result;
}

/* ------------------------------------------------------- */

Purchase Coder::getPurchaseByCode(char * code)
{
	Purchase result;
	char * position = code;
	
	#ifdef _DEBUG_
		cout << "Decoding id..." << endl;
	#endif
	memcpy(&result.user_id, code, sizeof(int));
	position += sizeof(int);
	
	#ifdef _DEBUG_
		cout << "Decoding item_len..." << endl;
	#endif
	int item_len;
	memcpy(&item_len, position, sizeof(int));
	position += sizeof(int);
	
	#ifdef _DEBUG_
		cout << "Decoding item... length : " << item_len << endl;
	#endif
	result.item = new char[item_len + 1];
	memcpy(result.item, position, item_len);
	result.item[item_len] = '\0';
	position += item_len;
	
	#ifdef _DEBUG_
		cout << "Decoding price..." << endl;
	#endif
	memcpy(&result.price, position, sizeof(double));
	position += sizeof(double);
	
	#ifdef _DEBUG_
		cout << "Decoding date..." << endl;
	#endif
	memcpy(result.date, position, DATE_LEN);
	result.date[DATE_LEN] = '\0';
	position += DATE_LEN;
	
	#ifdef _DEBUG_
		cout << "Decoding finished." << endl;
	#endif
	return result;
}	
