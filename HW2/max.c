#include <stdio.h>
#include <stdlib.h>  
#include <string.h>

#define ARRAY_SIZE 101
 
//static FILE *f; 


void operate(int hist_arr[], FILE *f);
	////////////////////////////////////check if need to add mpre functions declerations here. 
/*void parse_arg(int argc, char **argv) { 
	f = stdin; 
	for (int i=1; i<argc; i++){
		if (!strcmp(argv[i], "-")) {
			f = stdin; 
		} else if (!strcmp(argv[i], "-n_bins")) {
			nbins = i<argc-1 ? atoi(argv[i+1]) : 10;
			i++; 
		} else {
			f = fopen(argv[i], "r"); ///////////////////////////////////////////////////////////////////////////////add also f close(page 6 on ipad )
		}
	}
}*/

int main(int argc, char **argv)
{ 

	FILE *f;

	if  (argc == 1 || !strcmp("-", argv[1])) {
		f = stdin; 
	} else {
		f = fopen(argv[1], "r"); /*check wither to do fclose or not */////////////////////////////////////////////////////////////////////////////////////////////////////
	} 
	/* Must check for errors...*/ 
	if (!f) { 
		fprintf(stderr, "File not found: \"%s\"\n", argv[1]); 
		return 1; 
	}
	/* Initiate array */ 
	int hist_arr[ARRAY_SIZE] = { 0 }; 
	operate(hist_arr,f);
	fclose(f); 
 }

void operate(int hist_arr[], FILE *f) 
{ 
	int grade; 
	int retval;  
	int max_grade=0;
	int line_n =0;
 
	 

	while (1) {
		retval = fscanf(f, "%d", &grade); //getting the grade from the file
		if (retval == EOF) { 
			break; /*Finished */
			} else if (retval != 1) { 
				/* Error */
				fprintf(stderr, "Error: not a number\n"); 
				exit(1); 
			}
		if (0 > grade || grade > 100) {
			fprintf(stderr, "Error: grade not in range, line: %d\n", line_n+1);
			exit(1);
		}
		// fills the array with the number of students that got each grade 
		for ( int i = 0; i < ARRAY_SIZE; i++)
		{
			if(grade == i)
			{
				hist_arr[i]++; 
			}
			 
		}
		line_n++; // calculating the total num of students
	} 
	for (int j = 0; j < ARRAY_SIZE-1 ; j++)
	{
		//checking if any student got that grade
		if (hist_arr[j] > 0)
		{
			//fprintf(stderr, "%d\n",max_grade );
			//checkung if the current grade is the max grade
			if (max_grade  < j)
			{
				
				max_grade = j; 
			}
		} 
	}
	if( hist_arr[100] > 0){
		max_grade = 100;
	}
	printf("%d\t", max_grade);
}