#ifndef _STUDENT_H_
#define _STUDENT_H_

typedef struct _student_ Student;

Student *stuCreate(char name[30], int registry, float grade);

int cmpName(void *a, void *b);

int cmpRegistry(void *a, void *b);

int cmpGrade(void *a, void *b);

char *getName(Student *stu);

int getRegistry(Student *stu);

float getGrade(Student *stu);

int stuFree(void *a);

#endif
