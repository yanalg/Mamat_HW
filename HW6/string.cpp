#include "string.h"
#include <string.h>
#include <vector>
#include <iostream>

#define SPACE " "


int count_substring (const char *delimiters, char *str);





String::String(){
	this->data = NULL;
}
	

String::String(const String &str){
	this->length = str.length;
	this->data = new char[(this->length) + 1];
	strcpy(this->data,str.data);
}

String::String(const char *str){
	this->length = strlen(str)+1;
	this->data = new char[(this->length) + 1];
	strcpy(this->data,str);
}


String::~String(){
	delete[] this->data;
}

String& String::operator=(const String &rhs){ 
	if(this == &rhs){
		return *this;
	}
	
	this->length = rhs.length;
	delete[] this->data;
	this->data = new char[(this->length)+1];
	strcpy(this->data,rhs.data);
	return *this;
}



String& String::operator=(const char *str){ 
	if (this->data == str){
		return *this;
	}
	this->length = strlen(str);
	delete[] this->data;
	this->data = new char[(this->length)+1];	
	strcpy(this->data,str);
	return *this;
}


bool String::equals(const char *rhs) const{
	return (!strcmp(this->data,rhs));
}


bool String::equals(const String &rhs) const{
		return (!strcmp(this->data,rhs.data));
}




void String::split(const char *delimiters, String **output,size_t *size) const {
	 
	char *dup= new char [(this->length)+1]; 
	char *spare= new char [(this->length)+1]; 
	strcpy(spare,this->data);
	strcpy(dup,this->data);
	int k = count_substring(delimiters,dup); 
	*size = (size_t)k;
	if(output == NULL){ 
		return;
	}
	*output = new String[k]; 
	char *token = strtok(spare,delimiters);  
	int i=0;
	while(token != NULL) {
		(*output)[i] = String(token);
		i++;
		token = strtok(NULL, delimiters);
	}
	delete[] dup;
	delete[] spare;
}



/**
	* @brief seprates string into sub-strings by delimiters.
	*  returns the number of sub-strings.
*/  
int count_substring (const char *delimiters, char *str){ 
	if (str == NULL){
		return 0;
	}
	char *token;
	token = strtok(str,delimiters);
	int count = 0;
	while (token != NULL){
		token = strtok(NULL,delimiters);
		count++;
	}
return count;
}



int String::to_integer() const{
	int integer = atoi(this->data);
	return (integer);
}


String String::trim() const{
	char* space_free = new char[(this->length)+1];
	int i = 0, j = this->length-1;
	strcpy(space_free,this->data);
	while(space_free[i] == *SPACE && i<(int)(this->length)){
		i++;
	}
	while(space_free[j] == *SPACE && j>0){
		j--;
	}
	char* trimmed = new char[j-i+1];
	int k=0;
	while (!(i>j)){
		trimmed[k] = space_free[i];
		k++;
		i++;	
	}
	trimmed[k] = '\0';
	String str_trimmed = String(trimmed);
	delete[] trimmed;
	delete[] space_free;
	return str_trimmed;
}













































