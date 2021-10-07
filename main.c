#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct string{
	char value[50];
	int length;
}String;
void newStrcpy(String *s,char* value){
	int i=0;
	while(value[i]){
		s->value[i]=value[i];
		i++;
	}
	s->length=i;
	s->value[i]=0;
}
int charAt(String *s,int index){
	if(index>=s->length||index<0)return -1;
	return s->value[index];
}
String *concat(String *s1,String *s2){
	String* temp = (String*)malloc(sizeof(String));
	int newLen=s1->length+s2->length;
	if(newLen+1>=50)return NULL; //Length must be smaller than 50 
	temp->length=newLen+1;
	int i,j=0,k=0;
	for(i=0;i<newLen;i++){
		if(j<s1->length){
			temp->value[i]=s1->value[j];
			j++;
		}
		else{
			if(j==s1->length){
				//Add space between to strings
				temp->value[i]=' ';
				j++;
			}
			else{
				temp->value[i]=s2->value[k];
				k++;
			}
			
		}
	}
	temp->value[i]=0;
	return temp;
}
unsigned int strSearch(String *s1,String *s2){
	String* temp = (String*)malloc(sizeof(String));
	int i=0,j=0,k=0, total=0;
	while(i<s1->length){
		if(s1->value[i]==s2->value[0]){
			k=0;
			while(s1->value[i+k]==s2->value[k]&&k+i<s1->length){
				k++;
			}
			if(k==s2->length){
				while(s1->value[i+k]!=' '&&s1->value[i+k]!=0){
					k++;
				}
				return k;
			}
		}
		i++;
	}
	return total;
}
char toUpper(char ch){
	if(ch>='a'&&ch<='z'){
		return ch-32;
	}
}
unsigned int findScore(String *s1){
	char table[7][10]={"AEIOULNRST","DG","BCMP","FHVWY","K","JX","QZ"
	};
	int points[7]={1,2,3,4,5,8,10};
	int score=0,i,j,k;
	for(i=0;i<s1->length;i++){
		for(j=0;j<7;j++){
			for(k=0;k<10;k++){
				if(table[j][k]){
					if(table[j][k]==toUpper(s1->value[i])){
						score+=points[j];
						break;
					}
				}
			}
		}
	}
	return score;
}

void printStats(String *s1){
	int i,cnt=0,words=1;
	for(i=0;i<s1->length;i++){
		char ch =toUpper(s1->value[i]);
		if(ch>='A'&&ch<='Z'){
			cnt++;
		}
		else if(ch==' ')words++;
	}
	printf("The number of words: %d\nThe number of alphabetic letters: %d\n",words,cnt);
}
int noOfWords(String* s1){
	int i,cnt=1;
	for(i=0;i<s1->length;i++){
		if(s1->value[i]==' ')cnt++;
	}
	return cnt;
}
int noOfLetters(String* s1){
	int i,cnt=1;
	for(i=0;i<s1->length;i++){
		if(toUpper(s1->value[i])>='A'||toUpper(s1->value[i])<='Z')cnt++;
	}
	return cnt;
}
int main(int argc, char *argv[]) {
	if(argc==3){
		String *input=(String*)malloc(sizeof(String));
		String *temp = (String*)malloc(sizeof(String));
		FILE* inpf= fopen(argv[1],"r");
		FILE* outf = fopen(argv[2],"w");
		int wordCount=0;
		int letterCount=0;
		while(!feof(inpf)){
			fscanf(inpf,"%[^:]:",input->value);
			input->length=strlen(input->value);
			printf("%s,%d\n",input->value,input->length);
			if(strstr(input->value,"stat")>0){
				fprintf(outf,"The number of words: %d\nThe number of alphabetic letters: %d\n",wordCount,letterCount);
			}
			else{
				letterCount+=noOfLetters(input);
				if(strstr(input->value,"quit")>0||strstr(input->value,"exit")>0){
					fprintf(outf,"Program ends. Bye\n");
					break;
				}
				else{
					int process,tempint;
					fscanf(inpf,"%d,",&process);
					if(process==2||process==3){
						fscanf(inpf,"%s\n",temp->value);
						temp->length=strlen(temp->value);
						wordCount+=noOfWords(temp);
					}
					if(process==1){
						fscanf(inpf,"%d\n",&tempint);
						fprintf(outf,"%c\n",toUpper(charAt(input,tempint)));
					}else if(process==2){
						String* concat_str=concat(input,temp);
						fprintf(outf,"%s\n",concat_str->value);
						wordCount+=noOfWords(concat_str);
					}else if(process==3){
						fprintf(outf,"%d\n",strSearch(input,temp));
						wordCount+=noOfWords(temp);
						wordCount+=noOfWords(input);
					}else if(process==4){
						fscanf(inpf,"\n");
						fprintf(outf,"%d\n",findScore(input));
						wordCount+=noOfWords(input);
					}else printf("Invalid process\n");
				}
			}
		}
		fclose(inpf);
		fclose(outf);
	}
	else printf("Invalid arguments.");
	return 0;
}
