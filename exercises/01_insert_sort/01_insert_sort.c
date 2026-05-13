#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char name[20];
    int score;
} Student;

void print_all_students(Student students[],int n)
{
    for (int i = 0; i < n; i++) {
        printf("%s %d\n", students[i].name, students[i].score);
    }
    printf("\n");
}
void insertion_sort(Student students[], int n) {
    // TODO: 在这里添加你的代码
    const int max_size = 50;
    print_all_students(students, n);
    for (int i = 0; i < n; i++)
    {
        Student keyStudent = students[i];
        int j = i -1;
        for (j = i-1; j >= 0; j--)
        {
            if (students[j].score < keyStudent.score)
            {
                //move all items from i to j
                students[j+1] = students[j];
            }
            else
            {
                break;
            }
        }
        students[j+1]  = keyStudent;
        print_all_students(students, n);
    }
}

int main(void) {
    FILE *file;
    Student students[50];
    int n = 0;
    
    // 打开文件（从命令行参数获取文件名）
    file = fopen("01_students.txt", "r");
    if (!file) {
        printf("错误：无法打开文件 01_students.txt\n");
        return 1;
    }
    
    // 从文件读取学生信息
    while (n < 50 && fscanf(file, "%s %d", students[n].name, &students[n].score) == 2) {
        n++;
    }
    fclose(file);
    
    if (n == 0) {
        printf("文件中没有学生信息\n");
        return 1;
    }
    
    insertion_sort(students, n);
    
    printf("\n按成绩从高到低排序后的学生信息:\n");
    for (int i = 0; i < n; i++) {
        printf("%s %d\n", students[i].name, students[i].score);
    }
    
    return 0;
}

