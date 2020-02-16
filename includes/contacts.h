#ifndef __CONTACTSH__
#define __CONTACTSH__

/*LIbraries*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

struct contact {
	unsigned long phone_number;
	long first_name_posn;
	long last_name_posn;
	long company_name_posn;
	long email_posn;
	long next;
};

struct contactInfo {
	long phone_num;
	char *first_name;
	char *last_name;
	char *company_name;
 	char *email;
	int deleteMe;/*0 = keep, 1 = delete*/
};

/*FUNCTION PROTOTYPES*/
int compare_name_ascending( const void *, const void * );
void listAllContacts(struct contactInfo*, int);
int addNewContact(struct contactInfo *, int);
int printOutContactInfo(struct contactInfo *, int, int);
void deleteContact(struct contactInfo *, int);
int editContact(struct contactInfo *, int, int);
void saveContactToFIle(FILE *, struct contactInfo*);
void getContactString(FILE *, long, char*);

#endif
