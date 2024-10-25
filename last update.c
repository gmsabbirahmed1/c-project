#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_BOOKS 100
#define MAX_TITLE 50
#define MAX_AUTHOR 50
#define MAX_USERS 100
#define MAX_STUDENT_ID 17 // 16 digits + null terminator
#define MAX_NAME 50

// Structure definition for Book
typedef struct {
    int id;
    char title[MAX_TITLE];
    char author[MAX_AUTHOR];
    int year;
    int quantity;
} Book;

// Structure definition for User
typedef struct {
    char studentID[MAX_STUDENT_ID];
    char name[MAX_NAME];
} User;

// Global variables
Book books[MAX_BOOKS];     // Array to hold the books
User users[MAX_USERS];     // Array to hold user accounts
int bookCount = 0;         // Current number of books
int userCount = 0;         // Current number of users

// Function declarations
void addBook();
void updateBook();
void deleteBook();
void searchBook();
void displayBooks();
void borrowBook();
void saveBooks();
void loadBooks();
void adminInterface();
void userPortal();
void signup();
int login();
int isValidStudentID(const char *studentID);

// Security key
const char *SECURITY_KEY = "diu123456789";

int main() {
    loadBooks();
    int choice;

    do {
        printf("Welcome to the Library Management System\n");
        printf("1. Administrator Interface\n");
        printf("2. User Portal\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: adminInterface(); break;
            case 2: userPortal(); break;
            case 3: printf("Exiting...\n"); break;
            default: printf("Invalid choice! Please try again.\n");
        }
    } while (choice != 3);

    saveBooks();
    return 0;
}

// Function to load books from a file
void loadBooks() {
    FILE *file = fopen("books.dat", "rb");
    if (file == NULL) {
        printf("No existing data found. Starting fresh.\n");
        return;
    }
    bookCount = fread(books, sizeof(Book), MAX_BOOKS, file);
    fclose(file);
}

// Function to save books to a file
void saveBooks() {
    FILE *file = fopen("books.dat", "wb");
    if (file == NULL) {
        printf("Error saving books.\n");
        return;
    }
    fwrite(books, sizeof(Book), bookCount, file);
    fclose(file);
}

// Function to validate student ID
int isValidStudentID(const char *studentID) {
    if (strlen(studentID) != 16) {
        return 0; // Invalid length
    }
    for (int i = 0; i < 16; i++) {
        if (!isdigit(studentID[i])) {
            return 0; // Invalid character
        }
    }
    return 1; // Valid student ID
}

// Administrator Interface
void adminInterface() {
    char inputKey[20]; // Buffer for the security key
    printf("Enter Security Key: ");
    getchar(); // Consume newline character
    fgets(inputKey, sizeof(inputKey), stdin);
    inputKey[strcspn(inputKey, "\n")] = 0; // Remove newline

    // Check if the input key is correct
    if (strcmp(inputKey, SECURITY_KEY) != 0) {
        printf("Invalid Security Key! Access Denied.\n");
        return;
    }

    int choice;
    do {
        printf("\nAdministrator Interface\n");
        printf("1. Add Book\n");
        printf("2. Update Book\n");
        printf("3. Delete Book\n");
        printf("4. Search Book\n");
        printf("5. Display Books\n");
        printf("6. Exit to Main Menu\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addBook(); break;
            case 2: updateBook(); break;
            case 3: deleteBook(); break;
            case 4: searchBook(); break;
            case 5: displayBooks(); break;
            case 6: printf("Exiting to Main Menu...\n\n"); break;
            default: printf("Invalid choice! Please try again.\n");
        }
    } while (choice != 6);
}

// Function to add a new book
void addBook() {
    if (bookCount >= MAX_BOOKS) {
        printf("Library is full! Cannot add more books.\n");
        return;
    }
    Book newBook;
    printf("Enter Book ID: ");
    scanf("%d", &newBook.id);
    printf("Enter Book Title: ");
    getchar();  // to consume the newline character
    fgets(newBook.title, MAX_TITLE, stdin);
    newBook.title[strcspn(newBook.title, "\n")] = 0;  // remove newline
    printf("Enter Author Name: ");
    fgets(newBook.author, MAX_AUTHOR, stdin);
    newBook.author[strcspn(newBook.author, "\n")] = 0;  // remove newline
    printf("Enter Publication Year: ");
    scanf("%d", &newBook.year);
    printf("Enter Quantity: ");
    scanf("%d", &newBook.quantity);

    books[bookCount++] = newBook;
    printf("Book added successfully!\n");
}

// Function to update an existing book
void updateBook() {
    int id;
    printf("Enter Book ID to update: ");
    scanf("%d", &id);
    for (int i = 0; i < bookCount; i++) {
        if (books[i].id == id) {
            printf("Updating Book: %s\n", books[i].title);
            printf("Enter New Title: ");
            getchar(); // consume newline
            fgets(books[i].title, MAX_TITLE, stdin);
            books[i].title[strcspn(books[i].title, "\n")] = 0;  // remove newline
            printf("Enter New Author: ");
            fgets(books[i].author, MAX_AUTHOR, stdin);
            books[i].author[strcspn(books[i].author, "\n")] = 0;  // remove newline
            printf("Enter New Publication Year: ");
            scanf("%d", &books[i].year);
            printf("Enter New Quantity: ");
            scanf("%d", &books[i].quantity);
            printf("Book updated successfully!\n");
            return;
        }
    }
    printf("Book not found!\n");
}

// Function to delete a book
void deleteBook() {
    int id;
    printf("Enter Book ID to delete: ");
    scanf("%d", &id);
    for (int i = 0; i < bookCount; i++) {
        if (books[i].id == id) {
            for (int j = i; j < bookCount - 1; j++) {
                books[j] = books[j + 1];
            }
            bookCount--;
            printf("Book deleted successfully!\n");
            return;
        }
    }
    printf("Book not found!\n");
}

// Function to search for a book
void searchBook() {
    char title[MAX_TITLE];
    printf("Enter Book Title to search: ");
    getchar(); // consume newline
    fgets(title, MAX_TITLE, stdin);
    title[strcspn(title, "\n")] = 0;  // remove newline
    for (int i = 0; i < bookCount; i++) {
        if (strcasecmp(books[i].title, title) == 0) {
            printf("Book Found: ID: %d, Title: %s, Author: %s, Year: %d, Quantity: %d\n",
                   books[i].id, books[i].title, books[i].author, books[i].year, books[i].quantity);
            return;
        }
    }
    printf("Book not found!\n");
}

// Function to display all books
void displayBooks() {
    if (bookCount == 0) {
        printf("No books available in the library.\n");
        return;
    }
    printf("\nList of Books:\n");
    for (int i = 0; i < bookCount; i++) {
        printf("ID: %d, Title: %s, Author: %s, Year: %d, Quantity: %d\n",
               books[i].id, books[i].title, books[i].author, books[i].year, books[i].quantity);
    }
}

// User Portal
void userPortal() {
    int choice;
    do {
        printf("\nUser Portal\n");
        printf("1. Sign Up\n");
        printf("2. Log In\n");
        printf("3. Exit to Main Menu\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: signup(); break;
            case 2:
                if (login()) {
                    printf("Login successful!\n");
                    int userChoice;
                    do {
                        printf("\nUser Actions\n");
                        printf("1. Display Books\n");
                        printf("2. Borrow Book\n");
                        printf("3. Exit to User Portal Menu\n");
                        printf("Enter your choice: ");
                        scanf("%d", &userChoice);

                        switch (userChoice) {
                            case 1: displayBooks(); break;
                            case 2: borrowBook(); break;
                            case 3: printf("Exiting to User Portal Menu...\n\n"); break;
                            default: printf("Invalid choice! Please try again.\n");
                        }
                    } while (userChoice != 3);
                } else {
                    printf("Login failed!\n");
                }
                break;
            case 3: printf("Exiting to Main Menu...\n"); break;
            default: printf("Invalid choice! Please try again.\n");
        }
    } while (choice != 3);
}

// Function to sign up a new user
void signup() {
    if (userCount >= MAX_USERS) {
        printf("Maximum users reached! Cannot sign up more users.\n");
        return;
    }

    User newUser;
    printf("Enter Student ID (16 digits): ");
    getchar();  // to consume the newline character
    fgets(newUser.studentID, MAX_STUDENT_ID, stdin);
    newUser.studentID[strcspn(newUser.studentID, "\n")] = 0;  // remove newline

    // Validate student ID
    if (!isValidStudentID(newUser.studentID)) {
        printf("Invalid Student ID! It must be 16 digits long.\n");
        return;
    }

    printf("Enter Name: ");
    fgets(newUser.name, MAX_NAME, stdin);
    newUser.name[strcspn(newUser.name, "\n")] = 0;  // remove newline

    // Check for duplicate student ID
    for (int i = 0; i < userCount; i++) {
        if (strcasecmp(users[i].studentID, newUser.studentID) == 0) {
            printf("Student ID already exists! Please choose a different one.\n");
            return;
        }
    }

    users[userCount++] = newUser;
    printf("Sign up successful! You can now log in.\n");
}

// Function to log in a user
int login() {
    char studentID[MAX_STUDENT_ID];
    char name[MAX_NAME];

    printf("Enter Student ID (16 digits): ");
    getchar();  // to consume the newline character
    fgets(studentID, MAX_STUDENT_ID, stdin);
    studentID[strcspn(studentID, "\n")] = 0;  // remove newline

    // Validate student ID
    if (!isValidStudentID(studentID)) {
        printf("Invalid Student ID! It must be 16 digits long.\n");
        return 0; // Login failed
    }

    printf("Enter Name: ");
    fgets(name, MAX_NAME, stdin);
    name[strcspn(name, "\n")] = 0;  // remove newline

    // Check for valid student ID and name
    for (int i = 0; i < userCount; i++) {
        if (strcasecmp(users[i].studentID, studentID) == 0 &&
            strcasecmp(users[i].name, name) == 0) {
            return 1; // Login successful
        }
    }
    return 0; // Login failed
}

// Function to borrow a book
void borrowBook() {
    int id;
    printf("Enter Book ID to borrow: ");
    scanf("%d", &id);
    for (int i = 0; i < bookCount; i++) {
        if (books[i].id == id) {
            if (books[i].quantity > 0) {
                books[i].quantity--;
                printf("You have borrowed the book: %s\n", books[i].title);
            } else {
                printf("Sorry, this book is currently not available.\n");
            }
            return;
        }
    }
    printf("Book not found!\n");
}
