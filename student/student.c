#ifndef _STUDENT_C_
#define _STUDENT_C_

#include <stdlib.h>
#include <string.h>
#include "student.h"

#define FALSE 0
#define TRUE 1

typedef struct _student_ {
    char name[30];
    int registry;
    float grade;
} Student;

Student *stuCreate(char name[30], int registry, float grade) {
    Student *student;
    if (registry > 0 && grade >= 0) {
        student = (Student*)malloc(sizeof(Student));
        if (student != NULL) {
            strcpy(student->name, name);
            student->registry = registry;
            student->grade = grade;
            return student;
        }
    }
    return NULL;
}

int cmpName(void *a, void *b) {
    char *name = (char *)a;
    Student *student = (Student *)b;
    if (strcmp(student->name, name) == 0) {
        return TRUE;
    }
    return FALSE;
}

int cmpRegistry(void *a, void *b) {
    int *mat = (int *)a;
    Student *student = (Student *)b;
    if (student->registry == *mat) {
        return TRUE;
    }
    return FALSE;
}

int cmpGrade(void *a, void *b) {
    float *grade = (float *)a;
    Student *student = (Student *)b;
    if (student->grade == *grade) {
        return TRUE;
    }
    return FALSE;
}

char *getName(Student *stu) {
    return stu->name;
}

int getRegistry(Student *stu) {
    return stu->registry;
}

float getGrade(Student *stu) {
    return stu->grade;
}

int stdFree(void *a) {
    Student *student = (Student *)a;
    free(student);
    return TRUE;
}

#endif
