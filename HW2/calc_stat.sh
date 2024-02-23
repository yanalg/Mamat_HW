#!/bin/bash

number_of_arg=1
course_num=$1


if [[ $# -ne number_of_arg ]]; then
	echo "Wrong number of arguments" >&2
	exit 1

	else if [[ ! -e $course_num.txt ]]; then
    	echo "Course not found" >&2
    	exit 1
	fi
fi

if [[ -d "$course_num"_stat ]]; then
	 rm -r "$course_num"_stat
fi

mkdir "$course_num"_stat

#creating histogram of 10 bins.
data=$(cat $1.txt)

hist=$(echo "$data" | ./hist.exe)
echo "$hist" >> $1_stat/histogram.txt

#calculating average
avg=$(echo "$data" | ./mean.exe)
echo -n  "$avg" >> $1_stat/statistics.txt

#calculating median
median=$(echo "$data" | ./median.exe)
echo -n  "$median" >> $1_stat/statistics.txt

#calculating min grade
min=$(echo "$data" | ./min.exe)
echo -n  "$min" >> $1_stat/statistics.txt

#calculating max grade
max=$(echo "$data" | ./max.exe)
echo "$max" >> $1_stat/statistics.txt

#calculating percentage of the students who passed
student_num=$( echo "$data" | wc -l)

hist=$(echo "$data" | ./hist.exe -n_bins 100)


#go over all lines in "hist", count sum of students who passed the exam
sum=0
while read line; do 
	arr=($line)
	if (( `echo ${arr[0]} | cut -d"-" -f1` >= 55 )); then
	
		(( sum=$sum+${arr[1]} ))	
	fi 
done < <(echo "$hist")
sum=$sum*100
(( percentage=sum/student_num ))
echo $percentage >> $1_stat/statistics.txt 



