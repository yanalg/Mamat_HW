
#!/bin/bash

packet_list=$(cat /dev/stdin | sed -e 's/#.*//' | tr -d ' ')
	while read rule; do
		rule_trimmed=$(echo "$rule" | tr -d ' ' | tr -d ' ,' | \
			 sed -e 's/#.*//' | tr [:upper:] [:lower:] | \
		     sed -e 's/dst/,dst/g' | sed -e 's/src-port/,src-port/g' )
		if [[ "$rule_trimmed" != "" ]]; then
			src_ip_rule=$(echo $rule_trimmed | awk -F, '{print $1}')
			dst_ip_rule=$(echo $rule_trimmed | awk -F, '{print $2}')
			src_port_rule=$(echo $rule_trimmed | awk -F, '{print $3}')
			dst_port_rule=$(echo $rule_trimmed | awk -F, '{print $4}')
				print+=$(echo "$packet_list" | \
				./firewall.exe "$src_ip_rule" | \
			    ./firewall.exe "$dst_ip_rule" | \
				./firewall.exe "$src_port_rule" | \
			    ./firewall.exe "$dst_port_rule" )

			print+="\n"
		fi
	done < "$1"
echo -e "$print" | sed "s/src-ip/\n&/g" | sed '/^$/d' | sort