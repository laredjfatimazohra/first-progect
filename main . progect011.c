#include <stdio.h>
#include <stdlib.h>

 int main()

typedef struct
    float td;
    float tp;
    float quiz;
    float exam;
Course;


void inputMarks(Course *course) {
    printf("Enter marks for TD, TP, Quiz, and Exam: ");
    scanf("%f %f %f %f", &course->td, &course->tp, &course->quiz, &course->exam);
}



float calculateCourseMark(float td, float tp, float quiz, float exam) {
    return 0.2 * ((td + tp + quiz) / 3) + 0.8 * (exam * 0.2);
}

float calculateCourseMarkWithoutTD(float tp, float quiz, float exam) {
    return 0.5 * ((tp + quiz) / 2) + 0.5 * (exam * 0.2);
}

float calculateCourseMarkWithoutTP(float td, float quiz, float exam) {
    return 0.5 * ((td + quiz) / 2) + 0.5 * (exam * 0.2);
}

float calculateCourseMarkWithOnlyExam(float exam) {
    return exam * 0.2;
}

float calculateSemesterAverage(Course modules[], int numModules) {
    float total_marks = 0;
    for (int i = 0; i < numModules; i++) {
        if (modules[i].td == -1 && modules[i].tp == -1) {
            total_marks += calculateCourseMarkWithOnlyExam(modules[i].exam);
        } else if (modules[i].td == -1) {
            total_marks += calculateCourseMarkWithoutTD(modules[i].tp, modules[i].quiz, modules[i].exam);
        } else if (modules[i].tp == -1) {
            total_marks += calculateCourseMarkWithoutTP(modules[i].td, modules[i].quiz, modules[i].exam);
        } else {
            total_marks += calculateCourseMark(modules[i].td, modules[i].tp, modules[i].quiz, modules[i].exam);
        }
    }
    return total_marks / numModules;
}

void checkRemediation(Course modules[], int numModules) {
    for (int i = 0; i < numModules; i++) {
        float course_mark;
        if (modules[i].td == -1 && modules[i].tp == -1) {
            course_mark = calculateCourseMarkWithOnlyExam(modules[i].exam);
        } else if (modules[i].td == -1) {
            course_mark = calculateCourseMarkWithoutTD(modules[i].tp, modules[i].quiz, modules[i].exam);
        } else if (modules[i].tp == -1) {
            course_mark = calculateCourseMarkWithoutTP(modules[i].td, modules[i].quiz, modules[i].exam);
        } else {
            course_mark = calculateCourseMark(modules[i].td, modules[i].tp, modules[i].quiz, modules[i].exam);
        }
        if (course_mark < 2) {
            printf("Student needs remediation exam in Course %d.\n", i + 1);
        }
    }
}

void checkRetake(Course modules[], int numModules) {
    for (int i = 0; i < numModules; i++) {
        float course_mark;
        if (modules[i].td == -1 && modules[i].tp == -1) {
            course_mark = calculateCourseMarkWithOnlyExam(modules[i].exam);
        } else if (modules[i].td == -1) {
            course_mark = calculateCourseMarkWithoutTD(modules[i].tp, modules[i].quiz, modules[i].exam);
        } else if (modules[i].tp == -1) {
            course_mark = calculateCourseMarkWithoutTP(modules[i].td, modules[i].quiz, modules[i].exam);
        } else {
            course_mark = calculateCourseMark(modules[i].td, modules[i].tp, modules[i].quiz, modules[i].exam);
        }
        if (course_mark < 2) {
            printf("Student needs to retake Course %d.\n", i + 1);
        }
    }
}


int main() {

    printf("Welcome to your first year!\n");


    Course modules[7];


    for (int i = 0; i < 7; i++) {
        printf("\nFor Course %d:\n", i + 1);
        inputMarks(&modules[i]);
    }


    float semester_average = calculateSemesterAverage(modules, 7);
    printf("\nYour Semester Average: %.2f out of 20.00\n", semester_average * 10);

    if (semester_average < 10) {
        printf("Student needs remediation exams.\n");
        checkRemediation(modules, 7);
    } else {
        printf("Student passed the semester.\n");
    }
    checkRetake(modules, 7);


 return 0;
}


