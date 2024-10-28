#include <stdio.h>
#include <string.h>

struct Book
{
    int id;
    char title[50];
    char author[50];
    int quantity;
};

void displayMenu();
void addBook();
void viewBook();
void borrowBook();
void returnBook();
void searchBook();
void deleteBook();


int main() {

    while (1)
    {
        int choice;
        displayMenu();
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            addBook();
            break;
        case 2:
            viewBook();
            break;
        case 3:
            borrowBook();
            break;
        case 4:
            returnBook();
            break;
        case 5:
            searchBook();
            break;
        case 6:
            deleteBook();
            break;
        case 7:
            printf("Exiting program...\n");
            return 0;
        default:
            printf("Invalid choice!\n");
            break;
        }
    }

    return 0;
}

void displayMenu() {
    printf("library management system\n");
    printf("1: Add a book\n");
    printf("2: view books\n");
    printf("3: Borrow book\n");
    printf("4: Return book\n");
    printf("5: search book\n");
    printf("6: Delete book\n");
    printf("7: Eixt\n");
}


void addBook() {

    FILE *file = fopen("library.dat", "ab");
    struct Book newBook;
    printf("Enter book id: ");
    scanf("%d", &newBook.id);
    printf("Enter book title: ");
    scanf("%49s", newBook.title);
    printf("Enter book author: ");
    scanf("%49s", newBook.author);
    printf("Enter book quantity: ");
    scanf("%d", &newBook.quantity);
    fwrite(&newBook, sizeof(struct Book), 1, file);
    fclose(file);

    printf("Book added successfully!\n");

}


void viewBook() {

    FILE *file = fopen("library.dat", "rb");
    struct Book book;

    printf("Available Books:\n");
    printf("ID\tTitle\t\t\tAuthor\t\t\tQuantity\n");
    printf("---------------------------------------------------------------------------\n");

    while(fread(&book, sizeof(struct Book),1,file)){
        printf("%d\t%s\t\t%s\t\t\t%d\n", book.id, book.title, book.author, book.quantity);
    }
    fclose(file);        
}

void borrowBook() {

    FILE *file = fopen("library.dat", "rb+");
    struct Book book;
    int id, found = 0;

    printf("Enter book id: ");
    scanf("%d", &id);

    while(fread(&book, sizeof(struct Book), 1, file)){
        if(book.id == id && book.quantity > 0){
            book.quantity--;
            fseek(file, -sizeof(struct Book), SEEK_CUR);
            fwrite(&book, sizeof(struct Book), 1, file);

            printf("You have successfully borrowed a book: %s\n", book.title);
            found = 1;
            break;
        }
    }

    if(!found){
        printf("Book not found\n");
    }

    fclose(file);

}


void returnBook() {
    FILE *file = fopen("library.dat", "rb+");
    struct Book book;
    int id, found = 0;

    printf("Enter book id: ");
    scanf("%d", &id);

    while(fread(&book, sizeof(struct Book), 1, file)){
        if(book.id == id){
            book.quantity++;
            fseek(file, -sizeof(struct Book), SEEK_CUR);
            fwrite(&book, sizeof(struct Book), 1, file);

            printf("You have successfully returned a book: %s\n", book.title);
            found = 1;
            break;
        }
    }

    if(!found){
        printf("Book not found\n");
    }

    fclose(file);
}

//remaining functions >> delete, search, exit
void searchBook(){
    FILE *file = fopen("library.dat", "rd");
    struct Book book;
    char query[50];
    int found = 0;

    printf("Enter book title or author: ");
    scanf("%s", query);

    while(fread(&book, sizeof(struct Book), 1, file)){
        if(strstr(book.title, query) || strstr(book.author, query)){
            printf("Book Found:\n ID: %d\n Title: %s\n Author: %s\n Quantity: %d\n", book.id, book.title, book.author, book.quantity);
            found = 1;
        }
    }

    if (!found){
        //!found=!0=!false=true
        //!found=!1=!true=false
        printf("No matching books found\n");
    }

    // not true > false
    // not false > true

    fclose(file);
    
}

void deleteBook(){
    FILE *file = fopen("library.dat", "rb+");
    FILE *temp = fopen("temp.dat", "wb");

    struct Book book;
    int id, found = 0;

    printf("Enter book id to be deleted: ");
    scanf("%d", &id);

    while(fread(&book, sizeof(struct Book), 1, file)){
        if (book.id != id){
            fwrite(&book, sizeof(struct Book), 1, temp);
        }else{
            found = 1;
            printf("Book with ID %d has been deleted successfully\n", id);
        }
    }

    fclose(file);
    fclose(temp);

    // library.dat and temp.dat

    remove("library.dat");
    // delete library.dat remain with temp.dat

    rename("temp.dat", "library.dat");
    //temp.dat >>> library.dat
    


    if(!found){
        printf("Book not found\n");
    }
}