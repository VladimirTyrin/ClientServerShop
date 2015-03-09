#ifndef REQUEST_ARGUMENTS_H
#define REQUEST_ARGUMENTS_H

#include "Purchase.h"

//#include <cstdlib>
#include <cstring>

#define MIN_DATE	"000001010000" // 01.01.0000 00:00
#define MAX_DATE	"235931129999" // 31.12.9999 23:59

using namespace std;

struct RequestArguments
{
	bool		correct;

	int 		useId;
	int		ID;
	
	int		useDate;
	char * 		minDate;
	char * 		maxDate;
	
	RequestArguments()
	{
		correct = true;
			
		useId = 0;
		ID = 0;
		
		useDate = 0;
		minDate = new char[DATE_LEN + 1];
		strcpy(minDate, MIN_DATE);
		maxDate = new char[DATE_LEN + 1];
		strcpy(maxDate, MAX_DATE);
	}
	
	~RequestArguments()
	{
		delete [] minDate;
		delete [] maxDate;
	}
};

#endif
