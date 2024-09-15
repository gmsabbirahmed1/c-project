#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// store book information
struct Book
{
    int id;
    char title[50];
    char author[50];
    int available;
};

//Store user information
struct User
{
    int id;
    char name[50];
    char userType[10];
};

// store books and users
struct Book books[100];
struct User users[100];

// keep track of the number of books and users
int bookCount = 0;
int userCount = 0;

// add a book to the library
void addBook()
{
    struct Book newBook;
    printf("\nEnter book ID: ");
    scanf("%d", &newBook.id);
    printf("Enter book title: ");
    getchar();
    fgets(newBook.title, 50, stdin);
    printf("Enter book author: ");
    fgets(newBook.author, 50, stdin);
    newBook.available = 1;
    books[bookCount++] = newBook;
    printf("Book added successfully!\n");
}

//add a user to the system
void addUser()
{
    struct User newUser;
    printf("\nEnter user ID: ");
    scanf("%d", &newUser.id);
    printf("Enter user name: ");
    getchar();
    fgets(newUser.name, 50, stdin);
    printf("Enter user type (Student/Faculty): ");
    fgets(newUser.userType, 10, stdin);
    users[userCount++] = newUser;
    printf("User added successfully!\n");
}

//search for a book by ID
void searchBook()
{
    int id;
    printf("\nEnter book ID to search: ");
    scanf("%d", &id);

    for (int i = 0; i < bookCount; i++)
    {
        if (books[i].id == id)
        {
            printf("Book found: \n");
            printf("ID: %d\n", books[i].id);
            printf("Title: %s", books[i].title);
            printf("Author: %s", books[i].author);
            printf("Availability: %s\n", books[i].available ? "Available" : "Issued");
            return;
        }
    }
    printf("Book not found!\n");
}

// Function to issue a book
void issueBook()
{
    int bookId, userId;
    printf("\nEnter book ID to issue: ");
    scanf("%d", &bookId);
    printf("Enter user ID: ");
    scanf("%d", &userId);

    for (int i = 0; i < bookCount; i++)
    {
        if (books[i].id == bookId && books[i].available)
        {
            books[i].available = 0;
            printf("Book issued successfully!\n");
            return;
        }
    }
    printf("Book not available for issuing!\n");
}

// Function to return a book
void returnBook()
{
    int bookId;
    printf("\nEnter book ID to return: ");
    scanf("%d", &bookId);

    for (int i = 0; i < bookCount; i++)
    {
        if (books[i].id == bookId && !books[i].available)
        {
            books[i].available = 1;
            printf("Book returned successfully!\n");
            return;
        }
    }
    printf("Book not found or already available!\n");
}

//display all books
void displayBooks()
{
    printf("\nLibrary Books:\n");
    for (int i = 0; i < bookCount; i++)
    {
        printf("ID: %d\n", books[i].id);
        printf("Title: %s", books[i].title);
        printf("Author: %s", books[i].author);
        printf("Availability: %s\n", books[i].available ? "Available" : "Issued");
        printf("--------------------------\n");
    }
}


int main()
{
    int choice;

    while (1)
    {
        printf("\n welcome to DIU LIBERY \n");
        printf("1. Add Book\n");
        printf("2. Add User\n");
        printf("3. Search Book\n");
        printf("4. Issue Book\n");
        printf("5. Return Book\n");
        printf("6. Display All Books\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            addBook();
            break;
        case 2:
            addUser();
            break;
        case 3:
            searchBook();
            break;
        case 4:
            issueBook();
            break;
        case 5:
            returnBook();
            break;
        case 6:
            displayBooks();
            break;
        case 7:
            exit(0);
        default:
            printf("Invalid choice!\n");
        }
    }

    return 0;
}
