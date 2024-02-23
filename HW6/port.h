#include "string.h"
#include "generic-field.h"



class Port:public GenericField{
public:
	String port;
	int min = 0;
	int max = 0;
//public:
/**
	* @brief Initiates a port from a string.
*/  
	Port(const String str);
	~Port();
/**
	* @brief checks if val is a valid.
	*  returns false if not valid.
*/  
	bool set_value(String val);
/**
	* @brief matches a port string from packet to a rule set by set_value.
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
