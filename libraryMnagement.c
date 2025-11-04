#include <stdio.h>
#include<stdlib.h>
#include <string.h>

void addBook();
void searchBook(); void viewBooks(); void removeBook(); void issueBook(); void viewIssue(); void studentInfo(); void returnBook();
void toUpperCase(char str[]);

struct book {
    int id;
    char book_name[100];     char author_name[100];     char date[12];
} b;

struct student {
    int id;
    char sName[100];     char sClass[100];     int sld;     char date[12];     char book_name[100];
} s;
FILE *file; FILE *ftemp; int main() {     int n;     while (1) {         printf("\n\n");
        printf(" *******Welcome to IIUC Library******\n");         printf("1. Add book.\n");         printf("2. Search book.\n");         printf("3. View books list.\n");         printf("4. Remove book.\n");         printf("5. Issue book.\n");         printf("6. View issued book list.\n");         printf("7. Student Information.\n");         printf("8. Return book.\n");         printf("0. Exit.\n");         printf("-------------------\n");         printf("Enter your choice: ");         scanf("%d", &n);         getchar();

        switch (n) {             case 0:                 exit(0);             case 1:                 addBook();                 break;             case 2:                 searchBook();                 break;             case 3:                 viewBooks();                 break;             case 4:
                removeBook();                 break;             case 5:                 issueBook();                 break;             case 6:                 viewIssue();                 break;             case 7:                 studentInfo();                 break;             case 8:
                returnBook();                 break;             default:
                printf("Enter a valid number (1-10).\n");
        }
        printf("Press Enter to continue...");         getchar();
    }
    return 0;
}

void addBook() {     char myDate[12];
    printf("Enter today's date (DD/MM/YYYY): ");     fgets(myDate, sizeof(myDate), stdin);     myDate[strcspn(myDate, "\n")] = '\0';     strcpy(b.date, myDate);

    file = fopen("books.txt", "ab");     if (file == NULL) {
        printf("Error: Unable to open books file!\n");         return;
    }

    printf("Enter book id: ");     scanf("%d", &b.id);     getchar();
    printf("Enter book name: ");
    fgets(b.book_name, sizeof(b.book_name), stdin);
    b.book_name[strcspn(b.book_name, "\n")] = '\0';     toUpperCase(b.book_name);

    printf("Enter author name: ");
    fgets(b.author_name, sizeof(b.author_name), stdin);
    b.author_name[strcspn(b.author_name, "\n")] = '\0';     toUpperCase(b.author_name);     fwrite(&b, sizeof(b), 1, file);     fclose(file);
    printf("Book added successfully.\n");
}

void searchBook() {     char bookName[100];     int found = 0;
    printf("\n<== Search Book ==>\n ");
printf("\nEnter book name to search: ");
    fgets(bookName, sizeof(bookName), stdin);     bookName[strcspn(bookName, "\n")] = '\0';     toUpperCase(bookName);

    file = fopen("books.txt", "rb");     if (file == NULL) {
        printf("Error: Unable to open books file!\n");         return;
    }
    printf("\n%-10s %-30s %-20s %s\n", "Book Id", "Book Name",
"Author Name", "Date");
    while (fread(&b, sizeof(b), 1, file) == 1) {         if (strcmp(bookName, b.book_name) == 0) {             found = 1;
            printf("%-10d %-30s %-20s %s\n", b.id, b.book_name,
b.author_name, b.date);
        }
    }
    fclose(file);

    if (!found) {
        printf("No record found.\n");
    }
}

void viewBooks() {
    printf("\n<== Available Books ==>\n");
    printf("\n%-10s %-30s %-20s %s\n", "Book Id", "Book Name",
"Author Name", "Date");     file = fopen("books.txt", "rb");     if (file == NULL) {
        printf("Error: Unable to open books file!\n");         return;
    }
    while (fread(&b, sizeof(b), 1, file) == 1) {
        printf("%-10d %-30s %-20s %s\n", b.id, b.book_name,
b.author_name, b.date);
    }

    fclose(file);
}

void removeBook() {
int id, found = 0;
     printf("\n<== Remove Books ==>\n");     printf("Enter book id to remove: ");     scanf("%d", &id);     getchar();
    file = fopen("books.txt", "rb");     if (file == NULL) {
        printf("Error: Unable to open books file!\n");         return;
    }
    ftemp = fopen("temp.txt", "wb");     if (ftemp == NULL) {
        printf("Error: Unable to create temporary file!\n");         fclose(file);         return;
    }
    while (fread(&b, sizeof(b), 1, file) == 1) {         if (b.id == id) {             found = 1;
        } else {
            fwrite(&b, sizeof(b), 1, ftemp);
        }
} fclose(file); fclose(ftemp);

    if (found) {         remove("books.txt");         rename("temp.txt", "books.txt");         printf("Book removed successfully.\n");
    } else {
        remove("temp.txt");
        printf("No record found with the given book id.\n");
    }
}

void issueBook() {     char issueDate[12];
    printf("Enter today's date (DD/MM/YYYY): ");     fgets(issueDate, sizeof(issueDate), stdin);     issueDate[strcspn(issueDate, "\n")] = '\0';     strcpy(s.date, issueDate);

    int found = 0;
printf("\n<== Issue Book ==>\n");
    printf("Enter Book ID to issue: ");     scanf("%d", &s.id);     getchar();

    file = fopen("books.txt", "rb");     if (file == NULL) {
        printf("Error: Unable to open books file!\n");         return;
    }
    while (fread(&b, sizeof(b), 1, file) == 1) {         if (b.id == s.id) {             found = 1;
            strcpy(s.book_name, b.book_name);             break;
        }
    }
    fclose(file);

    if (!found) {
        printf("No book found with this ID. Please try again.\n");         return;
}
file = fopen("issue.txt", "ab"); if (file == NULL) {
        printf("Error: Unable to open issue file!\n");         return;
    }

    printf("Enter student name: ");     fgets(s.sName, sizeof(s.sName), stdin);
    s.sName[strcspn(s.sName, "\n")] = '\0';     toUpperCase(s.sName);

    printf("Enter student class: ");     fgets(s.sClass, sizeof(s.sClass), stdin);
    s.sClass[strcspn(s.sClass, "\n")] = '\0';     toUpperCase(s.sClass);     printf("Enter student roll number: ");     scanf("%d", &s.sld);     getchar();
    fwrite(&s, sizeof(s), 1, file);     fclose(file);
    printf("Book issued successfully!\n");
}
void viewIssue() {
    printf("\n<== Issue Book List ==>\n");
    printf("%-10s %-30s %-20s %-10s %-30s %s\n\n", "BOOK id",
"Name", "Class", "Roll", "Book Name", "Issue Date");     file = fopen("issue.txt", "rb");     if (file== NULL){     printf("File not found.\n");
    }
    while (fread(&s, sizeof(s), 1, file) == 1){
    printf("%-10d %-30s %-20s %-10d %-30s %s\n", s.id, s.sName,
s.sClass, s.id, s.book_name,s.date);
    }
    fclose(file);
}
void studentInfo() {
    int roll;     char class[100];     int found = 0;

    printf("\n<== Student Information ==>\n");     printf("Enter student class: ");
fgets(class, sizeof(class), stdin); class[strcspn(class, "\n")] = '\0'; toUpperCase(class);

    printf("Enter student roll number: ");     scanf("%d", &roll);     getchar();

    file = fopen("issue.txt", "rb");     if (file == NULL) {
        printf("Error: Unable to open issue file!\n");         return;
    }
    printf("\n%-10s %-30s %-20s %-10s %-30s %s\n", "Book ID",
"Name", "Class", "Roll", "Book Name", "Issue Date");     while (fread(&s, sizeof(s), 1, file) == 1) {         if (s.sld == roll && strcmp(s.sClass, class) == 0) {             found = 1;
            printf("%-10d %-30s %-20s %-10d %-30s %s\n", s.id, s.sName,
s.sClass, s.sld, s.book_name, s.date);
        }
    }
fclose(file);

if (!found) {
        printf("No records found for the given student.\n");
    }
}

void returnBook() {
    int id, roll;     char class[100];     int found = 0;

    printf("\n<== Return Book ==>\n");     printf("Enter Book ID to return: ");     scanf("%d", &id);     getchar();
    printf("Enter student class: ");     fgets(class, sizeof(class), stdin);     class[strcspn(class, "\n")] = '\0';     toUpperCase(class);
    printf("Enter student roll number: ");     scanf("%d", &roll);
getchar();
file = fopen("issue.txt", "rb"); if (file == NULL) {
        printf("Error: Unable to open issue file!\n");         return;
    }
    ftemp = fopen("temp.txt", "wb");     if (ftemp == NULL) {
        printf("Error: Unable to create temporary file!\n");         fclose(file);         return;
    }
    while (fread(&s, sizeof(s), 1, file) == 1) {
        if (s.id == id && s.sld == roll && strcmp(s.sClass, class) == 0) {             found = 1;         } else {
            fwrite(&s, sizeof(s), 1, ftemp);
        }
    }
    fclose(file);     fclose(ftemp); if (found) {
        remove("issue.txt");         rename("temp.txt", "issue.txt");         printf("Book returned successfully.\n");
    } else {
        remove("temp.txt");
        printf("No record found for the given details.\n");
    }
}
void toUpperCase(char str[]) {
    for (int i = 0; str[i] != '\0'; i++) {         if (str[i] >= 'a' && str[i] <= 'z') {             str[i] -= 32;
        }
    }
}

