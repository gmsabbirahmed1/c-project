#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_BOOKS 100
#define MAX_USERS 50
#define MAX_BORROWED 100

typedef struct
{
    int id;
    char title[50];
    char author[50];
    int year;
    int quantity;
} Book;

typedef struct
{
    char studentId[17];
} User;

typedef struct
{
    char studentId[17];
    int bookId;
    char borrowDate[11];
    int days;
} BorrowedBook;

Book library[MAX_BOOKS];
User users[MAX_USERS];
BorrowedBook borrowedBooks[MAX_BORROWED];
int bookCount = 0, userCount = 0, borrowedCount = 0;

void saveBooksToFile();
void loadBooksFromFile();
void saveUsersToFile();
void loadUsersFromFile();
void saveBorrowedBooksToFile();
void loadBorrowedBooksFromFile();
void getCurrentDate(char *buffer);
int adminLogin();
int userSignup();
int userLogin();
void addBook();
void deleteBook();
void updateBook();
void displayBooks();
void searchBook();
void borrowBook();
void viewBorrowedBooks();
void adminMenu();
void userMenu();
void returnBook();
void deleteUser();
void viewBorrowedBooksByUser();
void aboutUs();


int main()
{
    int choice;

    loadBooksFromFile();
    loadUsersFromFile();
    loadBorrowedBooksFromFile();

    printf(" --------------Welcome to \"Libro_GO\" -------------------------\n ----------(a Library Management System)------------------\n");

    while (1)
    {
        printf("\n1. Admin Login\n2. User Login\n3. Exit\n4. About Us\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            if (adminLogin())
            {
                adminMenu();
            }
            break;
        case 2:
            if (userLogin())
            {
                userMenu();
            }
            break;
        case 3:
            saveBooksToFile();
            saveUsersToFile();
            saveBorrowedBooksToFile();
            exit(0);
        case 4:
            aboutUs();
            break;
        default:
            printf("Invalid choice.\n");
        }
    }

    return 0;
}

void saveBooksToFile()
{
    FILE *fp = fopen("books.txt", "w");
    if (fp == NULL)
    {
        printf("Error saving books to file.\n");
        return;
    }
    for (int i = 0; i < bookCount; i++)
    {
        fprintf(fp, "%d\n%s\n%s\n%d\n%d\n", library[i].id, library[i].title, library[i].author, library[i].year, library[i].quantity);
    }
    fclose(fp);

}

void loadBooksFromFile()
{
    FILE *fp = fopen("books.txt", "r");
    if (fp == NULL)
    {
        printf("No books found, starting fresh.\n");
        return;
    }
    while (fscanf(fp, "%d\n", &library[bookCount].id) != EOF)
    {
        fgets(library[bookCount].title, 50, fp);
        fgets(library[bookCount].author, 50, fp);
        fscanf(fp, "%d\n%d\n", &library[bookCount].year, &library[bookCount].quantity);
        library[bookCount].title[strcspn(library[bookCount].title, "\n")] = 0;
        library[bookCount].author[strcspn(library[bookCount].author, "\n")] = 0;
        bookCount++;
    }
    fclose(fp);
}

void saveUsersToFile()
{
    FILE *fp = fopen("users.txt", "w");
    if (fp == NULL)
    {
        printf("Error saving users to file.\n");
        return;
    }
    for (int i = 0; i < userCount; i++)
    {
        fprintf(fp, "%s\n", users[i].studentId);
    }
    fclose(fp);
}

void loadUsersFromFile()
{
    FILE *fp = fopen("users.txt", "r");
    if (fp == NULL)
    {
        printf("No users found, starting fresh.\n");
        return;
    }
    while (fgets(users[userCount].studentId, 17, fp) != NULL)
    {
        users[userCount].studentId[strcspn(users[userCount].studentId, "\n")] = 0;
        userCount++;
    }
    fclose(fp);
}

void saveBorrowedBooksToFile()
{
    FILE *fp = fopen("borrowed_books.txt", "w");
    if (fp == NULL)
    {
        printf("Error saving borrowed books to file.\n");
        return;
    }
    for (int i = 0; i < borrowedCount; i++)
    {
        fprintf(fp, "%s\n%d\n%s\n%d\n", borrowedBooks[i].studentId, borrowedBooks[i].bookId, borrowedBooks[i].borrowDate, borrowedBooks[i].days);
    }
    fclose(fp);
}

void loadBorrowedBooksFromFile()
{
    FILE *fp = fopen("borrowed_books.txt", "r");
    if (fp == NULL)
    {
        printf("No borrowed books found, starting fresh.\n");
        return;
    }
    while (fscanf(fp, "%s\n%d\n%s\n%d\n", borrowedBooks[borrowedCount].studentId, &borrowedBooks[borrowedCount].bookId, borrowedBooks[borrowedCount].borrowDate, &borrowedBooks[borrowedCount].days) != EOF)
    {
        borrowedCount++;
    }
    fclose(fp);
}

void getCurrentDate(char *buffer)
{
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    sprintf(buffer, "%04d-%02d-%02d", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday);
}

int adminLogin()
{
    char password[10];
    printf("Enter Admin Password: ");
    scanf("%s", password);
    if (strcmp(password, "DIU321") == 0)
    {
        return 1;
    }
    else
    {
        printf("Incorrect password!\n");
        return 0;
    }
}

int userSignup()
{
    if (userCount >= MAX_USERS)
    {
        printf("User registration limit reached.\n");
        return 0;
    }
    User newUser;
    printf("Enter 16-digit Student ID: ");
    scanf("%s", newUser.studentId);

    if (strlen(newUser.studentId) != 16)
    {
        printf("Invalid ID! Must be 16 digits.\n");
        return 0;
    }

    for (int i = 0; i < userCount; i++)
    {
        if (strcmp(users[i].studentId, newUser.studentId) == 0)
        {
            printf("User already exists!\n");
            return 0;
        }
    }

    users[userCount++] = newUser;
    saveUsersToFile();
    printf("User registered successfully!\n");
    return 1;
}

int userLogin()
{
    char id[17];
    printf("Enter 16-digit Student ID: ");
    scanf("%s", id);

    for (int i = 0; i < userCount; i++)
    {
        if (strcmp(users[i].studentId, id) == 0)
        {
            return 1;
        }
    }
    printf("User not found!\n");
    return 0;
}

void addBook()
{
    Book newBook;
    printf("Enter Book ID: ");
    scanf("%d", &newBook.id);

    for (int i = 0; i < bookCount; i++) {
        if (library[i].id == newBook.id) {
            printf("Error: Book ID %d already exists. Please enter a unique Book ID.\n", newBook.id);
            return;
        }
    }

    printf("Enter Book Title: ");
    getchar();  // Consume the newline character left by the previous scanf
    fgets(newBook.title, sizeof(newBook.title), stdin);

    printf("Enter Book Author: ");
    fgets(newBook.author, sizeof(newBook.author), stdin);

    printf("Enter Book Quantity: ");
    scanf("%d", &newBook.quantity);

    library[bookCount] = newBook;
    bookCount++;

    // Save new book data to the file
    FILE *file = fopen("books.txt", "a");
    if (file != NULL) {
        fprintf(file, "%d\n%s\n%s\n%d\n%d\n", newBook.id, newBook.title, newBook.author, newBook.year, newBook.quantity);
        fclose(file);
    } else {
        printf("Error saving book data.\n");
    }
    printf("Book added successfully.\n");
}


void deleteBook()
{
    int id;
    printf("Enter book ID to delete: ");
    scanf("%d", &id);

    for (int i = 0; i < bookCount; i++)
    {
        if (library[i].id == id)
        {
            for (int j = i; j < bookCount - 1; j++)
            {
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
    int id, choice;
    printf("Enter book ID to update: ");
    scanf("%d", &id);

    for (int i = 0; i < bookCount; i++) {
        if (library[i].id == id) {
            while (1) {
                printf("\nEditing Book ID: %d\n", id);
                printf("1. Update Title\n");
                printf("2. Update Author\n");
                printf("3. Update Publication Year\n");
                printf("4. Update Quantity\n");
                printf("5. Go Back\n");
                printf("Enter your choice: ");
                scanf("%d", &choice);

                switch (choice) {
                    case 1:
                        printf("Enter new title: ");
                        scanf(" %[^\n]", library[i].title);
                        printf("Title updated successfully!\n");
                        break;
                    case 2:
                        printf("Enter new author: ");
                        scanf(" %[^\n]", library[i].author);
                        printf("Author updated successfully!\n");
                        break;
                    case 3:
                        printf("Enter new publication year: ");
                        scanf("%d", &library[i].year);
                        printf("Publication year updated successfully!\n");
                        break;
                    case 4:
                        printf("Enter new quantity: ");
                        scanf("%d", &library[i].quantity);
                        printf("Quantity updated successfully!\n");
                        break;
                    case 5:
                        saveBooksToFile();
                        printf("Changes saved. Returning to Admin Menu.\n");
                        return;
                    default:
                        printf("Invalid choice! Please try again.\n");
                }
            }
        }
    }
    printf("Book not found.\n");
}
void displayBooks()
{
    for (int i = 0; i < bookCount; i++)
    {
        printf("ID: %d\nTitle: %s\nAuthor: %s\nYear: %d\nQuantity: %d\n\n",
               library[i].id, library[i].title, library[i].author, library[i].year, library[i].quantity);
    }
}

void searchBook()
{
    int choice;
    char searchQuery[100];
    int found = 0;

    // Prompt the user to choose search criteria
    printf("Select search criteria:\n");
    printf("1. Search by Book ID\n");
    printf("2. Search by Title\n");
    printf("3. Search by Author\n");
    printf("Enter your choice (1-3): ");
    scanf("%d", &choice);

    // Handle invalid input
    if (choice < 1 || choice > 3) {
        printf("Invalid choice. Please select a valid option (1-3).\n");
        return;
    }


    switch (choice) {
        case 1:
            printf("Enter the Book ID to search: ");
            scanf("%d", &choice);
            for (int i = 0; i < bookCount; i++) {
                if (library[i].id == choice) {
                    printf("\nBook Found: \n");
                    printf("ID: %d\n", library[i].id);
                    printf("Title: %s", library[i].title);
                    printf("Author: %s", library[i].author);
                    printf("Quantity: %d\n", library[i].quantity);
                    found = 1;
                    break;
                }
            }
            break;

        case 2:
            getchar();
            printf("Enter the Book Title to search: ");
            fgets(searchQuery, sizeof(searchQuery), stdin);
            searchQuery[strcspn(searchQuery, "\n")] = 0;
            for (int i = 0; i < bookCount; i++) {
                if (strstr(library[i].title, searchQuery) != NULL) {
                    printf("\nBook Found: \n");
                    printf("ID: %d\n", library[i].id);
                    printf("Title: %s", library[i].title);
                    printf("Author: %s", library[i].author);
                    printf("Quantity: %d\n", library[i].quantity);
                    found = 1;
                }
            }
            break;

        case 3:
            getchar();
            printf("Enter the Author Name to search: ");
            fgets(searchQuery, sizeof(searchQuery), stdin);
            searchQuery[strcspn(searchQuery, "\n")] = 0;
            for (int i = 0; i < bookCount; i++) {
                if (strstr(library[i].author, searchQuery) != NULL) {
                    printf("\nBook Found: \n");
                    printf("ID: %d\n", library[i].id);
                    printf("Title: %s", library[i].title);
                    printf("Author: %s", library[i].author);
                    printf("Quantity: %d\n", library[i].quantity);
                    found = 1;
                }
            }
            break;
    }


    if (!found) {
        printf("\nNo book matches your search criteria.\n");
    }
}



void borrowBook()
{
    int id, days;
    char studentId[17];

    printf("Enter your Student ID: ");
    scanf("%s", studentId);

    int validUser = 0;
    for (int i = 0; i < userCount; i++)
    {
        if (strcmp(users[i].studentId, studentId) == 0)
        {
            validUser = 1;
            break;
        }
    }

    if (!validUser)
    {
        printf("Invalid Student ID.\n");
        return;
    }

    printf("Enter book ID to borrow: ");
    scanf("%d", &id);

    for (int i = 0; i < bookCount; i++)
    {
        if (library[i].id == id)
        {
            if (library[i].quantity > 0)
            {
                printf("Enter number of days to borrow: ");
                scanf("%d", &days);
                library[i].quantity--;

                BorrowedBook b;
                strcpy(b.studentId, studentId);
                b.bookId = id;
                b.days = days;
                getCurrentDate(b.borrowDate);
                borrowedBooks[borrowedCount++] = b;

                printf("Book borrowed successfully for %d days starting from %s.\n", days, b.borrowDate);
                saveBooksToFile();
                saveBorrowedBooksToFile();
            }
            else
            {
                printf("Book is out of stock.\n");
            }
            return;
        }
    }
    printf("Book not found.\n");
}

void viewBorrowedBooks()
{
    if (borrowedCount == 0)
    {
        printf("No books are currently borrowed.\n");
        return;
    }
    for (int i = 0; i < borrowedCount; i++)
    {
        printf("Student ID: %s\nBook ID: %d\nBorrowed for: %d days\nBorrowed Date: %s\n\n",
               borrowedBooks[i].studentId,
               borrowedBooks[i].bookId,
               borrowedBooks[i].days,
               borrowedBooks[i].borrowDate);
    }
}
void returnBook()
{
    char studentId[17];
    int bookId;
    int found = 0;

    printf("Enter your Student ID: ");
    scanf("%s", studentId);

    printf("Enter book ID to return: ");
    scanf("%d", &bookId);

    for (int i = 0; i < borrowedCount; i++)
    {
        if (strcmp(borrowedBooks[i].studentId, studentId) == 0 && borrowedBooks[i].bookId == bookId)
        {

            for (int j = 0; j < bookCount; j++)
            {
                if (library[j].id == bookId)
                {
                    library[j].quantity++;
                    break;
                }
            }


            for (int j = i; j < borrowedCount - 1; j++)
            {
                borrowedBooks[j] = borrowedBooks[j + 1];
            }
            borrowedCount--;
            found = 1;
            printf("Book returned successfully!\n");
            saveBooksToFile();
            saveBorrowedBooksToFile();
            break;
        }
    }

    if (!found)
    {
        printf("No record of this book being borrowed under this Student ID.\n");
    }
}

void adminMenu()
{
    int choice;
    while (1)
    {
        printf("\nAdmin Menu:\n1. Add Book\n2. Delete Book\n3. Update Book\n4. Display Books\n5. Search Book\n6. Sign-up Student\n7. View Borrowed Books\n8. Delete User\n9. Go Back\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            addBook();
            break;
        case 2:
            deleteBook();
            break;
        case 3:
            updateBook();
            break;
        case 4:
            displayBooks();
            break;
        case 5:
            searchBook();
            break;
        case 6:
            userSignup();
            break;
        case 7:
            viewBorrowedBooks();
            break;
        case 8:
            deleteUser();
            break;
        case 9:
            return;
        default:
            printf("Invalid choice.\n");
        }
    }
}

void userMenu()
{
    int choice;
    while (1)
    {
        printf("\nUser Menu:\n1. Borrow Book\n2. Return Book\n3. View Books\n4. Search Book\n5. View Borrowed Books\n6. Go Back\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            borrowBook();
            break;
        case 2:
            returnBook();
            break;
        case 3:
            displayBooks();
            break;
        case 4:
            searchBook();
            break;
        case 5:
            viewBorrowedBooksByUser();
            break;
        case 6:
            return;
        default:
            printf("Invalid choice.\n");
        }
    }
}

void aboutUs()
{
    printf("\n--------------- About Us ---------------\n");
    printf("      Welcome to \"Libro_GO\" -\n A Library Management Capstone Project\n");
    printf("Bevelop by\n");
    printf("G.M Sabbir Ahmed        Id: 232-35-359\n");
    printf("Refat Anwar.            Id: 232-35-423\n");
    printf("Sabikun Nahar Sinthia   id: 232-35-475\n");
    printf("-----------------------------------------\n");
}

void deleteUser()
{
    char studentId[17];
    printf("Enter Student ID to delete: ");
    scanf("%s", studentId);

    for (int i = 0; i < userCount; i++)
    {
        if (strcmp(users[i].studentId, studentId) == 0)
        {
            for (int j = i; j < userCount - 1; j++)
            {
                users[j] = users[j + 1];
            }
            userCount--;
            printf("User deleted successfully!\n");
            saveUsersToFile();
            return;
        }
    }
    printf("User not found.\n");
}

void viewBorrowedBooksByUser()
{
    char studentId[17];
    int found = 0;

    printf("Enter your Student ID: ");
    scanf("%s", studentId);

    for (int i = 0; i < borrowedCount; i++)
    {
        if (strcmp(borrowedBooks[i].studentId, studentId) == 0)
        {
            printf("Book ID: %d\nBorrowed for: %d days\nBorrowed Date: %s\n\n",
                   borrowedBooks[i].bookId,
                   borrowedBooks[i].days,
                   borrowedBooks[i].borrowDate);
            found = 1;
        }
    }

    if (!found)
    {
        printf("No borrowed books found for this Student ID.\n");
    }
}
