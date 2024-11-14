#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BOOKS 100
#define MAX_USERS 50

typedef struct {
    int id;
    char title[50];
    char author[50];
    int year;
    int quantity;
} Book;

typedef struct {
    char studentId[17]; // 16-digit student ID + '\0'
} User;

Book library[MAX_BOOKS];
User users[MAX_USERS];
int bookCount = 0, userCount = 0;

void saveBooksToFile() {
    FILE *fp = fopen("books.txt", "w");
    if (fp == NULL) {
        printf("Error saving books to file.\n");
        return;
    }
    for (int i = 0; i < bookCount; i++) {
        fprintf(fp, "%d\n%s\n%s\n%d\n%d\n", library[i].id, library[i].title, library[i].author, library[i].year, library[i].quantity);
    }
    fclose(fp);
}

void loadBooksFromFile() {
    FILE *fp = fopen("books.txt", "r");
    if (fp == NULL) {
        printf("No books found, starting fresh.\n");
        return;
    }
    while (fscanf(fp, "%d\n", &library[bookCount].id) != EOF) {
        fgets(library[bookCount].title, 50, fp);
        fgets(library[bookCount].author, 50, fp);
        fscanf(fp, "%d\n%d\n", &library[bookCount].year, &library[bookCount].quantity);
        library[bookCount].title[strcspn(library[bookCount].title, "\n")] = 0;
        library[bookCount].author[strcspn(library[bookCount].author, "\n")] = 0;
        bookCount++;
    }
    fclose(fp);
}

void saveUsersToFile() {
    FILE *fp = fopen("users.txt", "w");
    if (fp == NULL) {
        printf("Error saving users to file.\n");
        return;
    }
    for (int i = 0; i < userCount; i++) {
        fprintf(fp, "%s\n", users[i].studentId);
    }
    fclose(fp);
}

void loadUsersFromFile() {
    FILE *fp = fopen("users.txt", "r");
    if (fp == NULL) {
        printf("No users found, starting fresh.\n");
        return;
    }
    while (fgets(users[userCount].studentId, 17, fp) != NULL) {
        users[userCount].studentId[strcspn(users[userCount].studentId, "\n")] = 0;
        userCount++;
    }
    fclose(fp);
}

int adminLogin() {
    char password[10];
    printf("Enter Admin Password: ");
    scanf("%s", password);
    if (strcmp(password, "DIU321") == 0) {
        return 1; // Success
    } else {
        printf("Incorrect password!\n");
        return 0;
    }
}

int userSignup() {
    if (userCount >= MAX_USERS) {
        printf("User registration limit reached.\n");
        return 0;
    }
    User newUser;
    printf("Enter 16-digit Student ID: ");
    scanf("%s", newUser.studentId);

    if (strlen(newUser.studentId) != 16) {
        printf("Invalid ID! Must be 16 digits.\n");
        return 0;
    }

    for (int i = 0; i < userCount; i++) {
        if (strcmp(users[i].studentId, newUser.studentId) == 0) {
            printf("User already exists!\n");
            return 0;
        }
    }

    users[userCount++] = newUser;
    saveUsersToFile();
    printf("User registered successfully!\n");
    return 1;
}

int userLogin() {
    char id[17];
    printf("Enter 16-digit Student ID: ");
    scanf("%s", id);

    for (int i = 0; i < userCount; i++) {
        if (strcmp(users[i].studentId, id) == 0) {
            return 1; // Success
        }
    }
    printf("User not found!\n");
    return 0;
}

void addBook() {
    if (bookCount >= MAX_BOOKS) {
        printf("Library is full. Cannot add more books.\n");
        return;
    }

    Book newBook;
    printf("Enter Book ID: ");
    scanf("%d", &newBook.id);
    printf("Enter title: ");
    scanf(" %[^\n]", newBook.title);
    printf("Enter author: ");
    scanf(" %[^\n]", newBook.author);
    printf("Enter publication year: ");
    scanf("%d", &newBook.year);
    printf("Enter quantity: ");
    scanf("%d", &newBook.quantity);

    library[bookCount++] = newBook;
    printf("Book added successfully!\n");
    saveBooksToFile();
}

void deleteBook() {
    int id;
    printf("Enter book ID to delete: ");
    scanf("%d", &id);

    for (int i = 0; i < bookCount; i++) {
        if (library[i].id == id) {
            for (int j = i; j < bookCount - 1; j++) {
                library[j] = library[j + 1];
            }
            bookCount--;
            printf("Book deleted successfully!\n");
            saveBooksToFile();
            return;
        }
    }
    printf("Book not found.\n");
}

void updateBook() {
    int id;
    printf("Enter book ID to update: ");
    scanf("%d", &id);

    for (int i = 0; i < bookCount; i++) {
        if (library[i].id == id) {
            printf("Enter new title: ");
            scanf(" %[^\n]", library[i].title);
            printf("Enter new author: ");
            scanf(" %[^\n]", library[i].author);
            printf("Enter new publication year: ");
            scanf("%d", &library[i].year);
            printf("Enter new quantity: ");
            scanf("%d", &library[i].quantity);
            saveBooksToFile();
            printf("Book updated successfully!\n");
            return;
        }
    }
    printf("Book not found.\n");
}

void displayBooks() {
    for (int i = 0; i < bookCount; i++) {
        printf("Book ID: %d\nTitle: %s\nAuthor: %s\nYear: %d\nQuantity: %d\n\n",
               library[i].id, library[i].title, library[i].author, library[i].year, library[i].quantity);
    }
}

void searchBook() {
    int id;
    printf("Enter book ID to search: ");
    scanf("%d", &id);

    for (int i = 0; i < bookCount; i++) {
        if (library[i].id == id) {
            printf("Book ID: %d\nTitle: %s\nAuthor: %s\nYear: %d\nQuantity: %d\n",
                   library[i].id, library[i].title, library[i].author, library[i].year, library[i].quantity);
            return;
        }
    }
    printf("Book not found.\n");
}

void borrowBook() {
    int id, days;
    printf("Enter book ID to borrow: ");
    scanf("%d", &id);

    for (int i = 0; i < bookCount; i++) {
        if (library[i].id == id) {
            if (library[i].quantity > 0) {
                printf("Enter number of days to borrow: ");
                scanf("%d", &days);
                library[i].quantity--;
                printf("Book borrowed for %d days.\n", days);
                saveBooksToFile();
            } else {
                printf("Book is out of stock.\n");
            }
            return;
        }
    }
    printf("Book not found.\n");
}

void adminMenu() {
    int choice;
    while (1) {
        printf("\nAdmin Menu:\n1. Add Book\n2. Delete Book\n3. Update Book\n4. Display Books\n5. Search Book\n6. Sign-up Student\n7. Go Back\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addBook(); break;
            case 2: deleteBook(); break;
            case 3: updateBook(); break;
            case 4: displayBooks(); break;
            case 5: searchBook(); break;
            case 6: userSignup(); break;
            case 7: return;
            default: printf("Invalid choice.\n");
        }
    }
}

void userMenu() {
    int choice;
    while (1) {
        printf("\nUser Menu:\n1. Display All Books\n2. Search Book\n3. Borrow Book\n4. Log Out\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: displayBooks(); break;
            case 2: searchBook(); break;
            case 3: borrowBook(); break;
            case 4: return;
            default: printf("Invalid choice.\n");
        }
    }
}

int main() {
    int choice;

    loadBooksFromFile();
    loadUsersFromFile();

    printf("Library Management System\n");

    while (1) {
        printf("\n1. Admin Login\n2. User Login\n3. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                if (adminLogin()) {
                    adminMenu();
                }
                break;
            case 2:
                if (userLogin()) {
                    userMenu();
                }
                break;
            case 3:
                saveBooksToFile();
                saveUsersToFile();
                exit(0);
            default:
                printf("Invalid choice.\n");
        }
    }

    return 0;
}

