#include <stdio.h>
#include <stdbool.h>

int stringLength(char a[9])
{
    int i = 0;
    while(a[i] != '\0')
    {
        i++;
    }
    return i;
}

bool stringsEqual(char a[9], char b[9])
{
    if(stringLength(a) != stringLength(b))
        return false;
    int len = stringLength(a);

    for(int i = 0; i < len; ++i)
    {
        if(a[i] != b[i])
            return false;
    }

    return true;
}

int findStudentIdx(char itemArray[11][9], char *item)
{
    for(int i = 0; i < 11; ++i)
    {
        if(stringsEqual(itemArray[i], item))
            return i;
    }
    return -1;
}

int findClassIdx(char itemArray[5][9], char *item)
{
    for(int i = 0; i < 5; ++i)
    {
        if(stringsEqual(itemArray[i], item))
            return i;
    }
    return -1;
}

void changeStudentGrade(char students[11][9], char classes[10][5][7], int grades[10][5])
{
    char student[9];
    char class[7];
    int newGrade = 0;
    printf("Student: ");
    scanf("%s", student);
    printf("Class: ");
    scanf("%s", class);
    printf("New Grade: ");
    scanf("%d", newGrade);
    int studentIdx = findStudentIdx(students, student);
    int gradeIdx = findStudentIdx(classes[studentIdx], class);
    if(studentIdx == -1)
    {
        printf("Student not found\n");
        return;
    }
    if(gradeIdx == -1)
    {
        printf("Class not found\n");
        return;
    }
    grades[studentIdx][gradeIdx] = newGrade;
}

void printStudentGradeForClass(char students[11][9], char classes[10][5][7], int grades[10][5], char username[])
{
    char student[9];
    char class[7];
    printf("Student: ");
    scanf("%s", student);
    if(!(stringsEqual(username, student) || stringsEqual(username, "admin")))
    {
        printf("Must be admin to view grades\n");
        return;
    }
    printf("Class: ");
    scanf("%s", class);
    int studentIdx = findStudentIdx(students, student);
    int classIdx = findStudentIdx(classes[studentIdx], class);

    if(studentIdx == -1)
    {
        printf("Student not found\n");
        return;
    }
    if(classIdx == -1)
    {
        printf("Class not found\n");
        return;
    }

    printf("%s\n %s: %d\n", student, class, grades[studentIdx][classIdx]);
}

void printStudentClasses(char students[11][9], char classes[10][5][7])
{
    char student[9];
    printf("Student: ");
    scanf("%s", student);
    int studentIdx = findStudentIdx(students, student);
    if(studentIdx == -1)
    {
        printf("Student not found\n");
        return;
    }
    printf("%s:\n", student);
    for(int i = 0; i < 5; ++i)
    {
         printf("%s\n", classes[studentIdx][i]);
    }
}

void printStudentGrades(char students[11][9], char classes[10][5][7], int grades[10][5], char username[])
{
    char student[9];
    printf("Student: ");
    scanf("%s", student);
    if(!(stringsEqual(username, student) || stringsEqual(username, "admin")))
    {
        printf("Must be admin to change grades\n");
        return;
    }
    int studentIdx = findStudentIdx(students, student);
    printf("%s:\n", student);
    for(int i = 0; i < 5; ++i)
    {
        printf("%s: ", classes[studentIdx][i]);
        printf("%d\n", grades[studentIdx][i]);
    }
}

void addExtraCredit(char students[11][9], char classes[10][5][7], int grades[10][5], char username[])
{
    char student[9];
    char class[6];
    int points;
    printf("Student: ");
    scanf("%s", student);
    if(!(stringsEqual(username, student) || stringsEqual(username, "admin")))
    {
        printf("Must be admin to change grades\n");
        return;
    }
    printf("Class: ");
    scanf("%s", class);
    printf("Points:");
    scanf("%d", &points);
    int studentIdx = findStudentIdx(students, student);
    int gradeIdx = findClassIdx(classes[studentIdx], class);
    if(studentIdx == -1)
    {
        printf("Student not found\n");
        return;
    }
    if(gradeIdx == -1)
    {
        printf("Class not found\n");
        return;
    }
    if((grades[studentIdx][gradeIdx] + points) <= 100)
    {
        grades[studentIdx][gradeIdx] += points;
    }
    else
    {
        printf("Invalid input: grade must be less than or equal to 100\n");
    }
}


int main() {
    char students[11][9] = {"jsmith", "jdoe", "bwithers", "narmstro", "bobama",
                            "phaines", "jdilling", "xjinpin", "avespucc", "kwest", "admin"};
    char passwords[11][10] = {"1234567", "password", "bwithers", "abcdefg", "abc123",
                             "0987654", "qwerty", "a;sldkf", "incorrect", "password", "admin"};
    char classes[10][5][7] = {{"COS265", "SYS101", "BIB210", "MAT310", "IAS100"},
                              {"BIB110", "HUM250", "COS265", "SYS101", "IAS100"},
                              {"BIO100", "IAS100", "KIN100", "COS265", "SYS101"},
                              {"BIB110", "HUM250", "COS265", "SYS101", "IAS100"},
                              {"KIN100", "COS265", "SYS101", "MAT310", "IAS100"},
                              {"CHE120", "COS265", "SYS101", "MAT310", "BIB110"},
                              {"BIB110", "HUM250", "COS265", "SYS101", "IAS100"},
                              {"BIO100", "IAS100", "KIN100", "COS265", "SYS101"},
                              {"KIN100", "COS265", "SYS101", "MAT310", "IAS100"},
                              {"CHE100", "COS265", "SYS101", "MAT310", "BIB110"}};
    int grades[10][5] = {{78,  97, 95,  74, 90},
                         {98,  89, 87,  90, 85},
                         {100, 87, 92,  73, 89},
                         {94,  92, 89,  97, 100},
                         {98,  89, 87,  92, 94},
                         {87,  92, 73,  85, 93},
                         {94,  92, 100, 87, 97},
                         {92,  73, 89,  84, 86},
                         {98,  89, 87,  92, 94},
                         {98,  89, 87,  90, 85}};

    char username[9];
    char password[10];

    printf("Please enter your username:");
    scanf("%s", username);
    printf("Please enter your password:");
    scanf("%s", password);


    char *menu = "0: Exit\n1: List student grades\n2: Print a student's grade in a class\n3: Add extra credit to student's class\n4: List a student's classes\n5: Change a student's grade\nEnter your choice: ";
    int functionNum = 5;

    while(functionNum > 4)
    {
        printf("%s", &menu[0]);
        scanf("%d", &functionNum);
    }


    while(functionNum != 0)
    {
        switch(functionNum)
        {
            case 1: // list grades
                    printStudentGrades(students, classes, grades, username);
                break;
            case 2: // print grade in class
                    printStudentGradeForClass(students, classes, grades, username);
                break;
            case 3: // add extra credit to a class
                if(stringsEqual(username, "admin"))
                {
                    addExtraCredit(students, classes, grades, username);
                }
                else
                {
                    printf("Must be user or admin to view grades");
                }
                break;
            case 4: // print classes
                printStudentClasses(students, classes);
                break;
            case 5:
                changeStudentGrade(students, classes, grades);
        }

        printf("%s", menu);
        scanf("%d", &functionNum);
    }

}
