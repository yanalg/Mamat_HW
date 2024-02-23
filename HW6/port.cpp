#include "port.h"


#define MAX 65535
#define MIN 0
#define STR_SIZE 2
#define DASH "-"
#define EQUAL "="
#define OUR_DELIM ","



Port::Port(String str){
	this->min = 0;
	this->max = 0;       
	this->port = str;       
}   

Port::~Port(){
}

bool Port::set_value(String value){
	String *sub_val;
	size_t size = 0;
	value.split(DASH,&sub_val,&size);
	if (size != STR_SIZE){
		return false;
	}
	this->min = sub_val[0].trim().to_integer();
	this->max = sub_val[1].trim().to_integer();
	if (this->min < MIN || this->max > MAX || this->min > this->max){
		return false;
	}
	return true;
}


bool Port::match(String packet){
	if(match_aux(packet)){
		int val = packet.trim().to_integer();
	    if (val < this->min || val > this->max){
		    return false;
	    } 
		return true;
	}

	return false;

}

	




bool Port::match_aux(String& packet){
        bool flag = false;
        String *sub_packets;
        size_t size = 0;
        packet.split(OUR_DELIM , &sub_packets,&size);
        for (int i=0 ; i<(int)size ; i++){
                String *values;
                size_t num = 0;
                (sub_packets[i]).split(EQUAL , &values,&num);
                (values[0])=(values[0]).trim();
                if ((this->port).equals(values[0])){
                        flag = true;
                        packet = values[1].trim();
                }
                delete[] values;
        }
        delete[] sub_packets;
        return flag;
}

