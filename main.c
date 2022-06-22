#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <ctype.h>

// Structure for student record
struct student
{
    char Name[100];
    int roll_no;
    char course[100];
    float percentage;
} info;

char fileName[20] = "records.txt";
// prototypes
void addStudent();    // add student
void displayRecord(); // display student record
void searchStudent(); // search student by roll no
void deleteRecord();  // delete a student record

void main()
{
    printf("\nMade by:\n\tSOHAM DATTA RA2111031010089\n\tB.Tech CSE(IT) P2\n");
    int choice;
    while (choice != 5)
    {
        printf("\n-------STUDENT RECORD MANAGEMENT-------\n");
        printf("\n1. Add Student");
        printf("\n2. Display Student Record");
        printf("\n3. Search by roll number");
        printf("\n4. Delete Student Record");
        printf("\n5. Exit the program\n");
        printf("\nEnter choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            addStudent();
            break;
        case 2:
            displayRecord();
            break;
        case 3:
            searchStudent();
            break;
        case 4:
            deleteRecord();
            break;
        case 5:
            printf("\nexiting the program...\n");
            break;
        default:
            printf("\nEnter a valid choice(1-5)");
            break;
        }
    }
}
// add a student record
void addStudent()
{
    char more;
    FILE *fp;
    do
    {
        printf("\nAdd a student record by giving the below details:\n");
        fp = fopen(fileName, "a");
        printf("\nEnter name: ");
        scanf("%s", &info.Name);
        printf("Enter roll no.: ");
        scanf("%d", &info.roll_no);
        printf("Enter course: ");
        scanf("%s", &info.course);
        printf("Enter percentage: ");
        scanf("%f", &info.percentage);
        if (fp == NULL)
        {
            printf("Error, couldn't open file\n");
        }
        else
        {
            printf("Student added to record.\n\n");
        }

        // write data to file
        fprintf(fp, "%s %d %s %f\n", info.Name, info.roll_no, info.course, info.percentage);
        fclose(fp);
        printf("Do you want to add another student? (y/n): ");
        scanf("%s", &more);
    } while (tolower(more) == 'y');
}

// display current records
void displayRecord()
{
    FILE *fp;
    fp = fopen(fileName, "r");
    if (fp == NULL)
    {
        fprintf(stderr, "can't open file\n");
        exit(0);
    }
    else
    {
        printf("\nCurrent Records\n");
        printf("-------------------------\n");
    }
    // read data from file
    while (fscanf(fp, "%s %d %s %f\n", &info.Name, &info.roll_no, &info.course, &info.percentage) != EOF)
    {
        printf("\nStudent Name: %s\n", info.Name);
        printf("Roll no.: %d\n", info.roll_no);
        printf("Course: %s\n", info.course);
        printf("Percentage: %.2f %% \n", info.percentage);
        printf("--------------------\n");
    }
    printf("-------------------------\n");
    fclose(fp);
}
// search a student by roll no
void searchStudent()
{

    FILE *fp;
    int roll_no, found = 0;
    fp = fopen(fileName, "r");
    printf("Enter the roll no : ");
    scanf("%d", &roll_no);
    while (fscanf(fp, "%s %d %s %f\n", &info.Name, &info.roll_no, &info.course, &info.percentage) != EOF)
    {
        if (info.roll_no == roll_no)
        {
            printf("\nStudent name: %s\n", info.Name);
            printf("Roll no.: %d\n", info.roll_no);
            printf("Course: %s\n", info.course);
            printf("Percentage: %.2f %% \n\n", info.percentage);
            found = 1;
        }
    }

    if (!found)
    {
        printf("\nRoll number not found\n");
    }
    fclose(fp);
}
// delete a student record
void deleteRecord()
{
    FILE *fp, *fp_temp;
    int roll_no, found = 0;
    fp = fopen(fileName, "r");
    fp_temp = fopen("temp.txt", "w");
    printf("Enter the roll no : ");
    scanf("%d", &roll_no);
    while (fscanf(fp, "%s %d %s %f\n", &info.Name, &info.roll_no, &info.course, &info.percentage) != EOF)
    {
        if (info.roll_no != roll_no)
        {
            fprintf(fp_temp, "%s %d %s %f\n", info.Name, info.roll_no, info.course, info.percentage);
        }
        else
        {
            found = 1;
        }
    }
    if (!found)
    {
        printf("\nRoll number not found\n");
    }
    else
    {
        printf("\n%d deleted.\n", roll_no);
    }
    fclose(fp);
    fclose(fp_temp);
    remove(fileName);
    rename("temp.txt", fileName);
}