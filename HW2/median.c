#include <stdio.h>
#include <stdlib.h>  
#include <string.h>

#define ARRAY_SIZE 101
#define EVEN_NUM 2 
  


void operate(int hist_arr[], FILE *f );

int main(int argc, char **argv)
{ 
	FILE *f;

	if  (argc == 1 || !strcmp("-", argv[1])) {
		f = stdin; 
	} else {
		f = fopen(argv[1], "r"); 
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
	int students_num = 0;
	int median; 
	 

	while (1) {
		retval = fscanf(f, "%d", &grade); //geting the grade from the file
		if (retval == EOF) { 
			break; /*Finished */
			} else if (retval != 1) { 
				/* Error */
				fprintf(stderr, "Error: not a number\n"); 
				exit(1); 
			}
		if (0 > grade || grade > 100) {
			fprintf(stderr, "Error: grade not in range, line: %d\n", 
					students_num+1);
			exit(1); 
		}
		students_num++;	// calculating the total num of students
		// fills the array with the number of students that got each grade 
		for ( int i = 0; i < ARRAY_SIZE; i++)
		{
			
			if(grade == i)
			{
				hist_arr[i]++; 
			}
			
		}
	}
	//calculating the median
	int sum =0;
	median = (students_num + 1)/EVEN_NUM; 
	for (int j = 0; j < ARRAY_SIZE ; j++)
	{

		sum = sum + hist_arr[j]; 
		if(sum >= median)
			{
				//fprintf(stderr, "%d\n", j);
				printf("%d\t", j);
				break; 
			}
	}
}