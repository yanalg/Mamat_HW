#include <string.h>
#include <stdio.h> 
#include <stdlib.h>

static FILE *f; 
static int nbins = 10; 

void operate(int *bins); 

//function 
void parse_arg(int argc, char **argv) { 
	f = stdin; 
	for (int i=1; i<argc; ++i){
		if (!strcmp(argv[i], "-")) {
			f = stdin; 
		} else if (!strcmp(argv[i], "-n_bins")) {
			nbins = i<argc-1 ? atoi(argv[i+1]) : 10; //determining the parameter nbins value 
			i++; 
		} else {
			f = fopen(argv[i], "r"); 
		}
	}
}

int main(int argc, char **argv) { 

	parse_arg(argc, argv); 
	/* Must check for errors...*/ 
	if (!f) { 
		fprintf(stderr, "File not found: \"%s\"\n", argv[1]); 
		return 1; 
	}
	/* Initiate array */ 
	int *bins = (int*)malloc(sizeof(int)*nbins);
	//setting the array to zero  
	for (int i=0; i<nbins; ++i) { 
		bins[i] = 0; 
	}
	operate(bins); 
	free(bins);
	fclose(f); 
 }

//the function calculates the number of students in every bin                                                                           
void operate(int *bins) { 
	int grade; 
	int retval; 
	int pace; 
	double first_num_bin; 
	double last_num_bin; 

	while (1) {
		//receiving the grades from the file 
		retval = fscanf(f, "%d", &grade); 
		if (retval == EOF) { 
			break; /*Finished */
		}	
		else if (retval != 1) { 
				/* Error */
			
			fprintf(stderr, "Error: not a number\n"); 
			exit(1); 
		}
			/*Find bin */
		int n = grade / (100 / nbins); //calculating how many grades are in each bin 
		if (n < nbins) {
			bins[n]++; 
		}	 
		else if (n == nbins) { 
			bins[n-1]++;
		}
	}
	/*print bins  */
	pace = 100.0 /nbins;
	for (int i=0; i<nbins; ++i)
	{
		first_num_bin = i*pace;
		if ( first_num_bin == 0)
		{
			last_num_bin = pace-1; 
			printf("%.0lf-%.0lf\t%d\n", first_num_bin, last_num_bin, bins[0]);  
		} 
		else 
		{

			last_num_bin = (i+1)*(pace);  
			printf("%.0lf-%.0lf\t%d\n", first_num_bin, last_num_bin, bins[i]);
		}
	}
} 