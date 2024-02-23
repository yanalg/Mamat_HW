#include "string.h"
#include "generic-field.h"
#include "ip.h"
#include "port.h"
#include "input.h" 
#include <string.h>


#define ERROR -1
#define EQUAL "="



int main(int argc, char *argv[]){

	if(check_args(argc,argv)){
		return ERROR;
	}
	String rule = argv[1];
	String *out;
	size_t size=0;
	String original = String(rule);     
	rule.split(EQUAL,&out,&size);
	String name = ((out)[0]).trim();
	String value = ((out)[1]).trim();

	if ((name.equals("dst-port"))||(name.equals("src-port"))){
		Port port_rule = Port(name);
		if(port_rule.set_value(value)){
			parse_input(port_rule);
			return 0;
		}	
	}
	if ((name.equals("dst-ip"))||(name.equals("src-ip"))){
		Ip ip_rule = Ip(name);
		if(ip_rule.set_value(value)){
			parse_input(ip_rule); 
			return 0;
		}	
	}
	return ERROR;	
}



