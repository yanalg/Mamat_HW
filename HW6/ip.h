#include "string.h"
#include "generic-field.h"




class Ip : public GenericField{
public:
	String ip;
	
private:
	int mask=0;
	unsigned int int_ip=0;
	bool flag = true;
public:
/**
	* @brief Initiates an Ip from a string.
*/  
	Ip(String str);
	~Ip();
/**
	* @brief checks if Ip value is valid.
	* returns 0 if not valid.
*/  	
	bool set_value(String val);
/**
	* @brief checks if Ip value matches rule set by set_value.
	*  returns true if matches.
*/  	
	bool match(String packet);

/**
	* @brief performs spilts on packet recieved from match.
	*  returns true if found a match between packet and rule.
	*  updates the value of packets.
*/

	bool match_aux(String& packet);
};
