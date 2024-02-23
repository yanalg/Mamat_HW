#include <stdio.h> 
#include <stdlib.h>  
#include <string.h>  

void operate(FILE *f); 


int main(int argc, char **argv) {
	FILE *f;

	if  (argc == 1 || !strcmp("-", argv[1])) {
		f = stdin; 
	} else {
		f = fopen(argv[1], "r"); 
	}
	/* Must check for errors...*/ 
	if (!f){
		fprintf(stderr, "File not found: \"%s\"\n", argv[1]); 
		return 1; 
	}

	operate(f);
	fclose(f); 	
}
//getting grades and calculatiing average  
void operate(FILE *f) {
	int grade; 
	int retval; 
	double avg; 
	int line_n; 

	avg = 0; 
	line_n  = 0; 
	while (1) { 
		retval = fscanf(f, "%d" ,&grade); 
		if (retval == EOF){
			break;
		}
		else if (retval !=1 ){
			/* Error */ 
			fprintf(stderr, "Error: not a number\n"); 
			exit(1); 
		}
		if (0 > grade || grade > 100) {
			fprintf(stderr, "Error: grade not in range, line: %d\n", line_n+1);
			exit(1); 
		}
		avg += grade; 
		line_n++;
	}
	printf("%.2lf\t", avg/ line_n);
}