#ifndef CODER_H
#define CODER_H

#include <cstdlib>
#include <cstring>
#include <iostream>

#include "Purchase.h"

class Coder
{
public:
	char * 		getCodeByPurchase(Purchase purchase);
	Purchase	getPurchaseByCode(char * code);	
};

#endif
