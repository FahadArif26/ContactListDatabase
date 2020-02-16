#include "contacts.h"

/*this is the compare function to work adjacently wiht the qsorrt
comparing last name or comany name based on what is availible
*/
int compare_name_ascending( const void *x, const void *y ){
	/*Deref struct void pointers into local structs*/
	struct contactInfo data1 = *(struct contactInfo*)x;
	struct contactInfo data2 = *(struct contactInfo*)y;

	/*printf("data 1 %s, data 2 %s.. %s\n", data1.last_name, data2.last_name, data2.company_name);
	printf("stcmp val %d" , (data2.last_name != '\0'));*/

	if(data1.last_name[0]!= '\0' && data2.last_name[0]!= '\0'){
		/*BOTH HAVEA LAST NAME*/
		/*If strcmp returns a postive val return 1 to swap for asceding*/
		if ( strcmp(data1.last_name, data2.last_name) > 0) {
			return (1);
		} else if(strcmp(data1.last_name, data2.last_name) < 0){
			return(-1);
		} else {
			return (0);
		}
	}
	else if(data1.last_name[0]!= '\0' && data2.last_name[0] == '\0'){
		/*if data1 does have a last name and data2 DOESNT*/
		/*printf("cmp last nad comp\n");*/
		if ( strcmp(data1.last_name, data2.company_name) > 0) {
			return (1);
		} else if(strcmp(data1.last_name, data2.company_name) < 0){
			return(-1);
		} else {
			return (0);
		}
	}
	else if(data1.last_name[0] == '\0' && data2.last_name[0] != '\0'){
		/*if data1 DOESNT have a last name and data 2 does*/
		/*printf("cmp comp and last\n");*/
		if ( strcmp(data1.company_name, data2.last_name) > 0) {
			return (1);
		} else if(strcmp(data1.company_name, data2.last_name) < 0){
			return(-1);
		} else {
			return (0);
		}
	}
	else {
		/*BOT DONT HAVE A LAST NAME*/
		/*printf("cmp comp and comp\n");*/
		if ( strcmp(data1.company_name, data2.company_name) > 0) {
			return (1);
		} else if(strcmp(data1.company_name, data2.company_name) < 0){
			return(-1);
		} else {
			return (0);
		}
	}

}

/*this function is to list all the contacts with their number positions
in alphabetivcal order using qsort*/
void listAllContacts(struct contactInfo* memberInfo, int arrayLen){
	int i =0 ;
	/*printf("size is %d\n", arrayLen );*/

	qsort ( memberInfo, arrayLen, sizeof(struct contactInfo), compare_name_ascending);

	for(i=0; i < arrayLen; i++){
		if(memberInfo[i].deleteMe == 0){
			if(memberInfo[i].last_name[0] != '\0'){
				printf("%d. %s %s\n", i+1, memberInfo[i].first_name, memberInfo[i].last_name);
			}
			else{
				printf("%d. %s\n", i+1, memberInfo[i].company_name);
			}
		}
	}

}

/*THis function is to add a new contact and can alllow the user to save it
ie. add to the array, or just reutrn and not save ie. not add to the arrau*/
int addNewContact(struct contactInfo *memberInfo, int arrayLen){
	/*memberInfo = realloc(memberInfo, sizeof (struct contactInfo) * (index + 2));*/
	char *firstName;
	char *lastName;
	char *companyName = malloc(sizeof(char) *1000);
	char *email = malloc(sizeof(char) *1000);
	char *number = malloc(sizeof(char) *1000);
	int i = 0;
	int phoneNumIsOk = 0; /*check while = 0, if  = 1 its good*/
	int phoneNumHasLetter = 0; /*0 if there is no letter in phone number else 1*/

	int emailOk = 0;/*check while = 0, if  = 1 its good*/
	int emailHasIt = 0;
	int j = 0;
	int k = 0;

	char decision[3];
	decision[0] = 'P';

	char *buffer =  malloc(sizeof(char) *1000);

	printf("First Name: ");
	fgets(buffer, 999, stdin);
	buffer[strlen(buffer) - 1] = '\0';
	firstName = malloc(sizeof(char) * strlen(buffer) + 1);/*Allocate space for text*/
	strcpy(firstName, buffer);

	printf("Last Name: ");
	fgets(buffer, 999, stdin);
	buffer[strlen(buffer) - 1] = '\0';
	lastName = malloc(sizeof(char) * strlen(buffer) + 1);/*Allocate space for text*/
	strcpy(lastName, buffer);

	if (strcmp(lastName, "\0") == 0) {
		do{
			printf("Company Name: ");
			fgets(buffer, 999, stdin);
			buffer[strlen(buffer) - 1] = '\0';
			companyName = realloc( companyName, sizeof(char) * strlen(buffer) + 1);/*Allocate space for text*/
			strcpy(companyName, buffer);
		}while( strcmp(companyName, "\0") == 0);
	} else {
		printf("Company Name: ");
		fgets(buffer, 999, stdin);
		buffer[strlen(buffer) - 1] = '\0';
		companyName = realloc(companyName, sizeof(char) * strlen(buffer) + 1);/*Allocate space for text*/
		strcpy(companyName, buffer);
	}

	do{
		printf("Phone Number (enter only numbers): ");
		fgets(buffer, 999, stdin);
		buffer[strlen(buffer) - 1] = '\0';
		number = realloc(number, sizeof(char) * strlen(buffer) + 1);/*Allocate space for text*/
		strcpy(number, buffer);
		/*printf("NUmber len is %lu\n", strlen(number));*/
		if (strcmp(number, "\0") == 0) {
			phoneNumIsOk = 0;
		}
		else if(strlen(number) == 7 || strlen(number) == 10 ){
			phoneNumHasLetter = 0;
			for(i = 0; i < strlen(number); i++){
				if ( isdigit(number[i]) == 0 ){
					phoneNumHasLetter = 1;
				}
			}
			if (phoneNumHasLetter == 1) {
				phoneNumIsOk = 0;
			} else {
				phoneNumIsOk = 1;
			}
			/*printf("letter %d, num ok %d\n", phoneNumHasLetter, phoneNumIsOk);*/
		}
	}while( phoneNumIsOk == 0 );

	do{
		printf("Email: ");
		fgets(buffer, 999, stdin);
		buffer[strlen(buffer) - 1] = '\0';
		email = realloc(email, sizeof(char) * strlen(buffer)+1);/*Allocate space for text*/
		strcpy(email, buffer);

		j = 0;
		k = 0;
		emailHasIt = 0;
		emailOk = 0;

		for(i = 0; i < strlen(email); i++){
			if(emailHasIt == 0){
				if(i == 0 && email[i] == '@'){
					emailOk = 0;
				}
				else if(email[i] == '@'){
					emailHasIt = 1;
				}
			}
			else if(emailHasIt == 1){
				/*printf("poop emailok %d, emailhasit %d\n", emailOk, emailHasIt);
				printf("cur char is %c, j is %d\n", email[i], j);*/
				if(email[i] == '.' && j == 0){
					emailOk = 0;
				}
				else if(email[i] == '.'){
					emailHasIt = 2;
				}
				j++;
			}
			else if (emailHasIt == 2){
				/*printf("cur char is %c, k is %d\n", email[i], k);*/
				if(k >= 0){
					emailOk = 1;
				}
				k++;
			}
			/*printf("emailok %d, emailhasit %d\n", emailOk, emailHasIt);*/
		}
	}while(emailOk == 0);

	while(decision[0] != 'S' && decision[0] != 'R'){

		printf("Action:");
		fgets(decision,3,stdin);

		if(decision[0] == 'R'){
			/*DONT ADD NEW CONTACT AND RETURN TO MAIN*/
			free(buffer);
			free(firstName);
			free(lastName);
			free(companyName);
			free(email);
			free(number);

			return arrayLen;
		}

		if(decision[0] == 'S'){
			/*ADD NEW CONTACT INFO TO ARRAY*/
			memberInfo->first_name = malloc(sizeof(char) * strlen(firstName) + 1);/*Allocate space for text*/
			strcpy(	memberInfo->first_name, firstName);

			memberInfo->last_name = malloc(sizeof(char) * strlen(lastName) + 1);/*Allocate space for text*/
			strcpy(memberInfo->last_name, lastName);

			memberInfo->company_name = malloc(sizeof(char) * strlen(companyName) + 1);/*Allocate space for text*/
			strcpy(memberInfo->company_name, companyName);

			sscanf(number, "%lu", &memberInfo->phone_num);

			memberInfo->email = malloc(sizeof(char) * strlen(email) + 1);/*Allocate space for text*/
			strcpy(memberInfo->email, buffer);

			memberInfo->deleteMe = 0;

			free(buffer);
			free(firstName);
			free(lastName);
			free(companyName);
			free(email);
			free(number);

			return arrayLen + 1;
		}
	}
	return arrayLen;
}

/*this function displays a single contacts entire info when a numbe ris entered
in the main and gives the user to edit, delete or return to the pain */
int printOutContactInfo(struct contactInfo * memberInfo, int index, int arrayLen){

	char decision[3];
	decision[0] = 'P';

	printf("Contact #%d\n", index+1);
	printf("First Name: %s\n", memberInfo[index].first_name);
	printf("Last Name: %s\n", memberInfo[index].last_name);
	printf("Company Name: %s\n", memberInfo[index].company_name);
	printf("Phone Number: %lu\n", memberInfo[index].phone_num);
	printf("Email: %s\n", memberInfo[index].email);

	while(decision[0] != 'E' && decision[0] != 'R' && decision[0] != 'D'){

		printf("Action:");
		fgets(decision,3,stdin);

		if(decision[0] == 'D'){
			/*DELETE CONTACT AND RETURN TO MAIN*/
			memberInfo[index].deleteMe = 1;
			deleteContact(memberInfo, arrayLen);
			return arrayLen -1;
		}
		if(decision[0] == 'E'){
			arrayLen = editContact(memberInfo, index, arrayLen);
		}

	}
	return arrayLen;
}

/*this function to delete a contact from the array list of all of contacts*/
void deleteContact(struct contactInfo * memberInfo, int arrayLen ){
	int i = 0;
	int j = 0;
	for (i = 0; i < arrayLen ; i++){
		/*if the current one is flaaged to be deleted make it equal to the next, and the next equal to one after that*/
		if (memberInfo[i].deleteMe == 1){
			free(memberInfo[i].first_name);
			free(memberInfo[i].last_name);
			free(memberInfo[i].company_name);
			free(memberInfo[i].email);
			for (j = i + 1; j < arrayLen; j++){
				memberInfo[i] = memberInfo[j];
				/*memberInfo[j] = memberInfo[j+1];*/
			}
		}
	}
}

/*this function is to edit the contact's email or phone number, the user
also has the option to delete, save the edit or return
*/
int editContact(struct contactInfo* memberInfo, int index, int arrayLen){
	char *number =  malloc(sizeof(char) *1000);
	char *email =  malloc(sizeof(char) *1000);

	int phoneNumIsOk = 0; /*check while = 0, if  = 1 its good*/
	int phoneNumHasLetter = 0; /*0 if there is no letter in phone number else 1*/
	int emailOk = 0;/*check while = 0, if  = 1 its good*/
	int emailHasIt = 0;

	int i = 0;
	int j = 0;
	int k = 0;

	char *buffer =  malloc(sizeof(char) *1000);

	char decision[3];
	decision[0] = 'p';

	/*print out contact info thats constant*/
	printf("Contact #%d\n", index+1);
	printf("First Name: %s\n", memberInfo[index].first_name);
	printf("Last Name: %s\n", memberInfo[index].last_name);
	printf("Company Name: %s\n", memberInfo[index].company_name);

	/*get new phone number*/
	do{
		printf("Phone Number (enter only numbers): ");
		fgets(buffer, 999, stdin);
		buffer[strlen(buffer) - 1] = '\0';
		number = realloc(number, sizeof(char) * strlen(buffer) + 1);/*Allocate space for text*/
		strcpy(number, buffer);
		/*printf("NUmber len is %lu\n", strlen(number));*/
		if (strcmp(number, "\0") == 0) {
			phoneNumIsOk = 0;
		}
		else if(strlen(number) == 7 || strlen(number) == 10 ){
			phoneNumHasLetter = 0;
			for(i = 0; i < strlen(number); i++){
				if ( isdigit(number[i]) == 0 ){
					phoneNumHasLetter = 1;
				}
			}
			if (phoneNumHasLetter == 1) {
				phoneNumIsOk = 0;
			} else {
				phoneNumIsOk = 1;
			}
			/*printf("letter %d, num ok %d\n", phoneNumHasLetter, phoneNumIsOk);*/
		}
	}while( phoneNumIsOk == 0 );

	/*get new email*/
	do{
		printf("Email: ");
		fgets(buffer, 999, stdin);
		buffer[strlen(buffer) - 1] = '\0';
		email = realloc(email, sizeof(char) * strlen(buffer) + 1);/*Allocate space for text*/
		strcpy(email, buffer);

		j = 0;
		k = 0;
		emailHasIt = 0;/* = 1, email has @ at correct place, =2 @is good . is good*/
		emailOk = 0;

		for(i = 0; i < strlen(email); i++){
			if(emailHasIt == 0){
				if(i == 0 && email[i] == '@'){
					emailOk = 0;
				}
				else if(email[i] == '@'){
					emailHasIt = 1;
				}
			}
			else if(emailHasIt == 1){
				/*printf("poop emailok %d, emailhasit %d\n", emailOk, emailHasIt);
				printf("cur char is %c, j is %d\n", email[i], j);*/
				if(email[i] == '.' && j == 0){
					emailOk = 0;
				}
				else if(email[i] == '.'){
					emailHasIt = 2;
				}
				j++;
			}
			else if (emailHasIt == 2){
				/*printf("cur char is %c, k is %d\n", email[i], k);*/
				if(k >= 0){
					emailOk = 1;
				}
				k++;

			}
			/*printf("emailok %d, emailhasit %d\n", emailOk, emailHasIt);*/
		}
	}while(emailOk == 0);

	/*get user input for what to do*/
	while(decision[0] != 'S' && decision[0] != 'R' && decision[0] != 'D'){

		printf("Action:");
		fgets(decision,3,stdin);

		if(decision[0] == 'R'){
			/*DONT EDIT CONTACT AND RETURN TO MAIN*/
			free(email);
			free(number);
			free(buffer);
			return arrayLen;
		}

		if(decision[0] == 'S'){
			/*ADD NEW CONTACT INFO TO ARRAY*/
			sscanf(number, "%lu", &memberInfo[index].phone_num);

			memberInfo[index].email = realloc(memberInfo[index].email, sizeof(char) * strlen(email) + 1);/*Allocate space for text*/
			strcpy(memberInfo[index].email, buffer);

			free(email);
			free(number);
			free(buffer);

			return arrayLen;
		}

		if(decision[0] == 'D'){
			/*DELETE CONTACT AND RETURN TO MAIN*/
			memberInfo[index].deleteMe = 1;
			deleteContact(memberInfo, arrayLen);
			free(email);
			free(number);
			free(buffer);
			return arrayLen -1 ;
		}

	}
	return arrayLen;
}

/* THis function gets an element of the memberinfo struct array
and calculates the positons in the file for the contact postion
struct and then writes to the file*/
void saveContactToFIle(FILE *fp, struct contactInfo* memberInfo){

	struct contact *member = malloc(sizeof(struct contact) * 1);

	int fNameLen = 0;
	int lNameLen = 0;
	int cNameLen = 0;
	int eLen = 0;

	fseek(fp, 0, SEEK_END);/*ensure writing ot end of file*/

	/*add values to string lengths to if the eleemnt for the contact is not empty*/
	if(strcmp(memberInfo->first_name, "\0") != 0){
		fNameLen = strlen(memberInfo->first_name) + 1;
	}

	if(strcmp(memberInfo->last_name, "\0") != 0){
		lNameLen = strlen(memberInfo->last_name) + 1;
	}

	if(strcmp(memberInfo->company_name, "\0") != 0){
		cNameLen = strlen(memberInfo->company_name) + 1 ;
	}

	member->phone_number = memberInfo->phone_num;

	if(strcmp(memberInfo->email, "\0") != 0){
		eLen = strlen(memberInfo->email) + 1;
	}

	/*Save positions of records to struct*/
	member->first_name_posn =  ftell(fp) + sizeof(struct contact);
	member->last_name_posn =  member->first_name_posn + fNameLen;
	member->company_name_posn =  member->last_name_posn + lNameLen;
	member->email_posn =  member->company_name_posn + cNameLen;
	member->next = member->email_posn + eLen;

	/*Replace positons of the enteries with 0 if strings are mepty*/
	if(fNameLen == 0){
		member->first_name_posn = 0;
	}
	if(lNameLen == 0){
		member->last_name_posn = 0;
	}
	if(cNameLen == 0){
		member->company_name_posn = 0;
	}
	if(eLen == 0){
		member->email_posn = 0;
	}

	/*Write to the file*/
	fwrite(member, sizeof(struct contact), 1, fp);
	/*If the string is empty dont write to the file*/
	if(fNameLen != 0){
		fwrite(memberInfo->first_name, sizeof(char), fNameLen, fp);
	}
	if(lNameLen !=0){
		fwrite(memberInfo->last_name, sizeof(char), lNameLen, fp);
	}
	if(cNameLen != 0){
		fwrite(memberInfo->company_name, sizeof(char), cNameLen, fp);
	}/*fwrite( number, sizeof(char), strlen(number) + 1, fp);*/
	if(eLen != 0){
		fwrite(memberInfo->email, sizeof(char), eLen, fp);
	}

	free(member);

}


/*This function checks if there is an entry stored at the postion sent in
if not then makes the string sent in a null character and ends, else it reads in info from the
file character by character till a null terminator and then print it out*/
void getContactString(FILE *fp, long dataPosn, char *info){

	if(dataPosn == 0){
		info[0] = '\0';
	}
	else{
		char *data = malloc(sizeof(char) *2);
		data[0] = '\0';
		char *element = malloc(sizeof(char) * 3);
		int i = 0;

		fseek(fp, dataPosn , SEEK_SET);

		strcpy(element, "A");

		/*read character by character till null*/
		for(i = 0; strcmp(element, "\0"); i++){
			fread(element, sizeof(char), 1, fp);
			element[1] = '\0';
			strcat(data, element);
			data = realloc( data, sizeof(char) * (i + 3));
		}


		/*info = malloc(sizeof(char)* strlen(data) + 1);*/
		strcpy(info, data);
		free(data);
		free(element);
		/*printf("%s\n", info);*/
	}

	/*return info;*/
}
