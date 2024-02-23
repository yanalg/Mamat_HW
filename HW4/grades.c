#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include "grades.h"
#include "linked-list.h"

#define MIN_GRADE 0
#define MAX_GRADE 100

typedef struct course *Course;
typedef struct student *Student;
typedef struct grades *Grades;

int add_student(Grades *grades, const char *name, int id);
Course course_init(const char *name, int grade);
Student student_init(const char *name, int id);
void print_courses (Student student);
void list_clone(struct list *list, struct list *out);

/--------Course Struct--------/

struct course{
	char *name;
	int grade;
};



int course_clone(void *elem, void **out){
	Course course = (Course) elem;
	if (course == NULL || out == NULL){
		return -1;
	}
	Course new = course_init(course->name,course->grade);
	*out = new;
	free (course->name);
	free (course);
	return 0;
}







void course_destroy (void *elem){
	Course course = (Course) elem;
	if (course->name != NULL){
		free (course->name);
	}
	if (course != NULL){
		free (course);
	}
}




Course course_init(const char *name, int grade){
	Course new = (Course)malloc(sizeof(*new));
	if (new == NULL){
		return NULL;
	}
	new->name = (char*)malloc(sizeof(char)*(strlen(name) +1));
	if (new->name == NULL){
		free (new);
		return NULL;
	}
	strcpy(new->name , name);
	new->grade = grade;
	return new;
}





/--------Student Struct--------/

struct student{
	char *name;
	int id;
	struct list *courses;
};

void student_destroy(void *elem){
	if (elem == NULL) return;
	Student student = (Student) elem;
	if (!student){
		return;
	}
	if (!(student->courses)){
		list_destroy(student->courses);
	}
	if (!(student->name)){
		free (student->name);
	}
	free(student);
}



int student_clone(void *elem, void **out){ // CHECK AGAIN
	Student student = (Student) elem;
	if (student == NULL|| out==NULL){
		return -1;
	}
	Student new = student_init(student->name,student->id);
	if (new==NULL){
		return -1;
	}	
	list_clone(student->courses, new->courses);
	if (new->courses==NULL){
		student_destroy(new);
		return -1;
	}
	*out = new;
	free(student->name);
	free (student);
	return 0;
}


Student student_init(const char *name, int id){ 
	Student student = (Student)malloc(sizeof(*student));
	if (student == NULL){
		return NULL;
	}
	
	student->name = (char*)malloc(sizeof(char)*(strlen(name)+1));
	if (student->name == NULL){
		free(student->name);
		free(student);
		return NULL;
	}
	strcpy(student->name,name);
	student->id = id;
	student->courses = list_init(student_clone, student_destroy);
	if(student->courses == NULL){//check correctness
		free(student->name);
		free(student);
		return NULL;
	}
	return student;
}






/--------Grade Struct--------/

struct grades{
	struct list *students_list;
};


void grades_destroy(Grades grades){
	if (grades == NULL){
		return;
	}
	if(grades->students_list!=NULL) {
		list_destroy(grades->students_list);
	}
	free (grades);
}



struct grades* grades_init(){
	Grades students_grades = (Grades)malloc(sizeof(struct grades));
	if (students_grades == NULL){
		return NULL;
	}
	students_grades->students_list = list_init(student_clone, student_destroy);
	if((students_grades->students_list) == NULL){
		free(students_grades);
		return NULL;
	}
	return students_grades;
}




/--------Library Commands--------/

int grades_add_grade(Grades grades,
                     const char *name,
                     int id,
                     int grade){
	if (grade < MIN_GRADE || grade > MAX_GRADE || !grades || 
		!(grades->students_list)){
		return -1;
	}
	struct iterator *it;
	for (it= list_begin(grades->students_list); 
	it != NULL; 
	it = list_next(it)){
		Student curr_student = (Student)list_get(it);
		if (curr_student == NULL){
			return -1;
		}
		if (id == curr_student->id){
			struct iterator *jt;
			for (jt = list_begin(curr_student->courses); 
			jt != NULL; 
			jt = list_next(jt)){
				Course curr_course = (Course)list_get(jt);
				if (strcmp(curr_course->name,name) == 0){
					//The course already exists for student
					return -1;
				}
			}
			Course course = course_init(name,grade);
			if (course == NULL){
				course_destroy(course);
				return -1;
			}
			if(list_push_back(curr_student->courses,course)){
				course_destroy(course);
				return -1;
			}
			return 0;
		}
	}
	return -1;
}







float grades_calc_avg(Grades grades, int id, char **out){
	if(grades==NULL){
		*out = NULL;
		return -1;
	}
	*out = NULL;
	struct iterator *it;
	int grades_sum=0;
	int size =0;
	for (it = list_begin(grades->students_list);
	it != NULL;
	it = list_next(it)){
			Student curr_student = list_get(it);
			if (curr_student->id == id){
				out =(char)malloc(strlen(curr_student->name)+1);
				if (!*out){
					return -1;
				}
				strcpy(*out,curr_student->name);
				size = list_size(curr_student->courses);
				if (size == 0){
					return 0;
				}
				struct iterator *jt;
				for(jt = list_begin(curr_student-> courses);
				jt != NULL;
				jt=list_next(jt)){
					Course curr_course = (Course)list_get(jt);
					grades_sum = grades_sum + (curr_course->grade);
				}
			}		
		}
		float average = (float)((float)grades_sum/(float)size);
		if (*out == NULL){
		return -1;
	}
	return average;
}

	





int grades_print_student(Grades grades, int id){
	if (grades == NULL){
		return -1;
	}int curr_id = 0;
	char *curr_name;
	struct iterator *it;
	for(it = list_begin(grades->students_list) ; it!=NULL ; it=list_next(it)){
		Student curr = (Student)list_get(it);
		curr_id = (curr->id);
		if(curr_id == id ){
			//student with "id" is found.
			curr_name = (curr->name);
			break;
		}
	}
	
	if (!(Student)list_get(it)){
		return -1;
	}
	printf("%s",curr_name);
	printf(" %d:",curr_id);
	print_courses (list_get(it));
	printf("\n");
	return 0;
}







/**
 *@brief Prints' courses of "student" in the following manner:
 * COURSE-1-NAME COURSE-1-GRADE, [...]
 */
void print_courses (Student student){
	struct iterator *it = list_begin(student->courses);
	Course curr_course = (Course)list_get(it);
	if(curr_course == NULL){
		//no courses exist for student
		return;
	}
	printf(" %s %d",curr_course->name, curr_course->grade);
	
	for(it = list_next(it) ; it != NULL ; it = list_next(it)){
		curr_course = (Course)list_get(it);
		if(curr_course == NULL){
			return;
		}
		printf(", %s %d",curr_course->name, curr_course->grade);
	}
	return;
}







int grades_print_all(Grades grades){
	struct iterator *it ;
	for(it = list_begin(grades->students_list);it!=NULL;it=list_next(it)){
		Student curr = list_get(it);
		int true = grades_print_student(grades,curr->id);
		 if(true){
		 	//grades_print_student failed
		 	return -1;
		 }
	}
	return 0;
}











/**
 *@brief casing for add_student func
 */
int grades_add_student(Grades grades, const char *name, int id){
	
	return (add_student(&grades,name,id));
}



void list_clone(struct list *list, struct list *out){
	Course course;
	struct iterator *it;
	for (it = list_begin(list);
	it != NULL;
	it = list_next(it)){
		course = list_get(it);
		if(list_push_back(out,course)){
			list_destroy(out);
		}
	}
}


int add_student(Grades *grades, const char *name, int id){
	if (!(*grades)){
		return -1;
	}
	Student student_id;
	struct iterator *it;
	for (it = list_begin((*grades)->students_list);
	it != NULL;
	it = list_next(it)){
		student_id =(Student) list_get(it);
		if (id == (student_id->id)){ 
			//student with "id" already exists
			return -1;
		}
	}
	Student new = student_init(name, id);
	if (list_push_back((*grades)->students_list, new)){
		student_destroy(new);
		return -1;
	}
	return 0;
}