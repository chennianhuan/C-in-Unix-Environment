#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

/* a C program to count the total number of commented characters and words in 
*  a C file taking both types of C file comments (single line and block) into account
*/

char *getfileall(char *fname) {

	FILE *fp;
	char *str;
	char txt[1000];
	int filesize;

	if ((fp = fopen(fname, "r")) == NULL){
	printf("cannot open file %s\n", fname);
	return NULL;
	}

	fseek(fp, 0, SEEK_END); 
	filesize = ftell(fp);
	str = (char *)malloc(filesize);
	str[0] = 0;

	rewind(fp);

	while((fgets(txt, 1000, fp)) != NULL){
	strcat(str, txt);
	}

	fclose(fp);

	return str;
}

/* 

 * match

 * */

void matchComments(char *str, char *pattern) {
	regmatch_t regmatch[10];
	regex_t re;
	int cflags = REG_EXTENDED + REG_NEWLINE;
	
	regcomp(&re, pattern, cflags);
	int count = 0;
 
	while (str && regexec(&re, str, 10, regmatch, REG_NOTEOL) != REG_NOMATCH) {
	int len = regmatch[0].rm_eo - regmatch[0].rm_so;
	printf("match_str: \"%.*s\"\n", len, str + regmatch[0].rm_so);
	str = &str[regmatch[0].rm_eo + 1];
	count += len;
	}
	
	printf("total length: %d\n", count);
	regfree(&re);

}

int main(int argc, char *argv[]) {

	char *p;

	char fname[50];

	// Prompt the user to enter a c program filename
	printf("Enter a C program filename: ");
	scanf("%s", fname);

	p = getfileall(fname);

	if (p != NULL) {

	matchComments(p, "(/\\*([^*]|[\\r\\n]|(\\*+([^*/]|[\\r\\n])))*\\*+/)|(//.*)");
	};

	return 0;
}
