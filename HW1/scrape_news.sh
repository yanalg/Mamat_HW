	#!/bin/bash 

	#enters the link that includes the news
	site="https://www.ynetnews.com/category/3082" 
	data=$(wget --no-check-certificate -O - $site 2>/dev/null)  
	#search for articles
	articles=$(echo "$data"  |
						grep -oP "https://(www.)?ynetnews.com/article/[0-9a-zA-Z]+" )
	#counts how many articles are on the site
	new_articles=$(echo "$articles" | sort | uniq)
	echo "$(echo "$new_articles" | wc -l)" >> results.csv
	#counts the appearance of the given words 
	for links in $new_articles; do
		current_site=$(wget -q -O - "$links" 2>/dev/null)
		num_N=$(echo "$current_site" | grep -o "Netanyahu" | wc -l)
		num_G=$(echo "$current_site" | grep -o "Gantz" | wc -l)
		num_L=$(echo "$current_site" | grep -o "Lapid" | wc -l)
		num_B=$(echo "$current_site" | grep -o "Ben-Gvir" | wc -l)
		#zero appearance of the given words case 
		if [[($num_N -eq 0) && ($num_G -eq 0) && ($num_L -eq 0) && ($num_B -eq 0) ]]; then 
			echo "$links, -" >> results.csv  
			continue
		fi
		#prints the results to the results.csv file
		echo "$links,Netanyahu,$num_N,Gantz,$num_G,Lapid,$num_L,Ben-Gvir,$num_B" >> results.csv

	done 

