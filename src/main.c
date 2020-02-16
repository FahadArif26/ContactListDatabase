#include "contacts.h"

int main(){

	FILE *fp;

	char decision[3];/*0 = save new contact, 1 = retrieve contact, 2 = exit whole program*/
	decision[0] = '\0';
	int i=0;
	int fileSize =0;
	char *buffer =  malloc(sizeof(char) *1000);
	int arrayLen = 0;
	int selectContactNum = 10;

	struct contact *member = malloc(sizeof(struct contact) * 1);/*Struct for positions*/
	struct contactInfo *memberInfo = malloc(sizeof(struct contactInfo) * 1);/*struct array for contact names and etc.*/

	/*Open/create file*/
	fp = fopen("bin/myContactList.db", "ab+");
	if (fp == NULL){
		printf("File cannot be opened or does not exist\n");
		return(-1);
	}

	/*Read in any exitsing contacts in myContactList*/
	fseek(fp, 0, SEEK_END);
	fileSize =  ftell(fp);
	rewind(fp);
	/*LOOP till end of file */
	for (i = 0; ftell(fp) != fileSize; i++){
		fread(member, sizeof(struct contact), 1, fp);

		/*call function to retirve string for first name save to buffer, then to contact in array*/
		getContactString(fp, member->first_name_posn, buffer);
		memberInfo[i].first_name = malloc(sizeof(char)*strlen(buffer)+1);
		strcpy(memberInfo[i].first_name,buffer);

		getContactString(fp, member->last_name_posn,buffer);
		memberInfo[i].last_name = malloc(sizeof(char)*strlen(buffer)+1);
		strcpy(memberInfo[i].last_name,buffer);

		getContactString(fp, member->company_name_posn, buffer);
		memberInfo[i].company_name = malloc(sizeof(char)*strlen(buffer)+1);
		strcpy(memberInfo[i].company_name,buffer);

		getContactString(fp, member->email_posn, buffer);
		memberInfo[i].email = malloc(sizeof(char)*strlen(buffer)+1);
		strcpy(memberInfo[i].email,buffer);

		memberInfo[i].phone_num = member->phone_number;

		memberInfo[i].deleteMe = 0;

		memberInfo = realloc(memberInfo, sizeof (struct contactInfo) * (i + 2));

		fseek(fp, member->next,SEEK_SET);
		arrayLen++;
	}

	fclose(fp);

	/*print out how many contacts there are and the sorted list*/
	printf("Number of Contacts  = %d\n", arrayLen);
	listAllContacts(memberInfo, arrayLen);

	while(decision[0] != 'X'){

		printf("Action:");
		fgets(decision,3,stdin);

		if(decision[0] == 'A'){
			/*Save New Contact*/
			/*printf("arrayLen %d\n", arrayLen);*/
			/*realloc struct array to have space for new contact*/
			memberInfo = realloc(memberInfo, sizeof(struct contactInfo) * (arrayLen + 2));
			arrayLen = addNewContact(&memberInfo[arrayLen], arrayLen);
			/*printf("arrayLen %d\n", arrayLen);*/

			printf("Number of Contacts  = %d\n", arrayLen);
			listAllContacts(memberInfo, arrayLen);
		}

		if(isdigit(decision[0]) != 0){
			/*convert string of what contact number into an int*/
			sscanf(decision, "%d", &selectContactNum);
			/*printf("%d,\n", selectContactNum);*/
			selectContactNum -= 1;
			/*printf(" before delte arrayLen %d\n", arrayLen);*/

			/*error catch for if they typed in an inccorrect nuumber*/
			if (selectContactNum < arrayLen ) {
				arrayLen = printOutContactInfo(memberInfo, selectContactNum, arrayLen);
				/*printf(" back from delte arrayLen %d\n", arrayLen);*/
				memberInfo = realloc(memberInfo, sizeof(struct contactInfo) * (arrayLen + 1));
				/*printf("Number of Contacts  = %d\n", arrayLen);*/
				listAllContacts(memberInfo, arrayLen);
			}

		}

	}

	/*open file to write new contact list*/
	fp = fopen("bin/myContactList.db", "wb+");
	if (fp == NULL){
		printf("File cannot be opened or does not exist\n");
		return(-1);
	}

	/*write to the fille each contact from array*/
	for(i = 0; i < arrayLen; i++){
		saveContactToFIle(fp, &memberInfo[i]);
	}
	fclose(fp);

	/*FREE EVERYTHING!*/
	free(buffer);
	free(member);

	/*free each element for the struct*/
	for(i = 0; i < arrayLen; i++){
		free(memberInfo[i].first_name);
		free(memberInfo[i].last_name);
		free(memberInfo[i].company_name);
		free(memberInfo[i].email);
	}
	free(memberInfo);

	return 0;
}
