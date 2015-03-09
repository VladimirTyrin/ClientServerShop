#ifndef PURCHASE_H
#define PURCHASE_H

#define DATE_LEN		12
// Date format : HHMMDDMMYYYY
// H - hours
// M - minutes, then months
// D - days
// Y - years

struct Purchase
{
	int	user_id;
	char *	item;
	double	price;
	char	date[DATE_LEN + 1];
};

#endif
