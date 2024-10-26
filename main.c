#include <stdio.h>

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


int main() {
    displayMenu();
    addBook();
    viewBook();






    return 0;
}

void displayMenu() {
    printf("library management system\n");
    printf("1: Add a book\n");
    printf("2: view book\n");
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
    scanf("%s", newBook.title);
    printf("Enter book author: ");
    scanf("%s", newBook.author);
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
    printf("ID\tTitle\t\tAuthor\t\tQuantity\n");
    printf("-----------------------------------------------\n");

    while(fread(&book, sizeof(struct Book),1,file)){
        printf("%d\t%s\t\t%s\t\t%d\n", book.id, book.title, book.author, book.quantity);
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
        if(book.id == id) {}
    }
}
