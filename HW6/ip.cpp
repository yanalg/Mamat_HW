#include "ip.h"
#include "string.h"
#include "generic-field.h"

#define MIN 0
#define MAX 255
#define VALID_SIZE 2
#define IP_SIZE 4
#define BYTE 8
#define WORD 32
#define SLASH "/"
#define DOT "."
#define ERROR -1
#define EQUAL "="
#define OUR_DELIM ","



 
unsigned int dots_no_more(String val, bool *flag);



Ip::Ip(String str){
	this->ip = str;

}

Ip::~Ip(){
}



bool Ip::set_value(String val) {
	String *out;
	size_t size=0;
	val.split(SLASH , &out, &size);
	if(size != VALID_SIZE){
		if(size!=0){
			//delete[] out;  ///check we may need to delete if 
		}
		return false;
	}
	this->mask =WORD-(out[1].trim().to_integer());
	bool flag;
	if(this->mask <0 || this->mask>32){
		return ERROR;
	}
	this->int_ip = dots_no_more(out[0],&flag); 
	this->flag = flag;
	return(this->flag);
}


bool Ip::match(String packet){
	if(match_aux(packet)){ 
		bool flag = false;
		unsigned int num = dots_no_more(packet, &flag);
		if (this->mask == WORD){
			return true;
		}
		return(((this->int_ip >> this->mask) == (num >> this->mask)) && flag);
	}
	
	return false;	
}



/**
	* @brief removes dots from Ip address.
	*  returns unsingned int value of address.
*/ 
unsigned int dots_no_more(String val, bool *flag){
	String *out;
	size_t size = 0;
	*flag = true;
	unsigned int address[IP_SIZE]={0};
	val.split(DOT, &out , &size);	
	if(size != IP_SIZE){
		if(size!=0){
			//delete[] out;  //check again!!!!!!!!
		}
		*flag = false;
		return ERROR;
	}
	for(int i=0;i<IP_SIZE;i++){
		address[i] = (out[i]).trim().to_integer();
		if (address[i]<MIN || address[i]>MAX){
			*flag = false;
			return ERROR;
		}
		address [i] = address[i]<<BYTE*(IP_SIZE-i-1);
	}
	return ((unsigned int)(address[3] | address[2] | address[1] | address[0]));
}




bool Ip::match_aux(String& packet){
        bool flag = false;
        String *sub_packets;
        size_t size = 0;
        packet.split(OUR_DELIM , &sub_packets,&size);
        for (int i=0 ; i<(int)size ; i++){
                String *values;
                size_t num = 0;
                (sub_packets[i]).split(EQUAL , &values,&num);
                (values[0])=(values[0]).trim();
                if ((this->ip).equals(values[0])){
                        flag = true;
                        packet = values[1].trim();
                }
                delete[] values;
        }
        delete[] sub_packets;
        return flag;
}





