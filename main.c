#include <stdio.h>
struct book {
    int id;
    char title[50];
    char author[50];
    int quantity;
};

void displayMenu();
void addBook();




int main(){
    int option;

    while (1)
    {
        displayMenu();

        printf("Enter your choice: ");
        scanf("%d", &option);

        switch (option){
        case 1:
            addBook();
            break;
        default:
            printf("Invalid choice. Please try again.\n");

        }
        
    }
    


    return 0;
}
 
void displayMenu(){
    printf("Library Management\n");
    printf("1.Add Book\n");
    printf("2.View Book\n");
    printf("3.Borrow Book\n");
    printf("4.Return Book\n");
    printf("5.Search Book\n");
    printf("6.Delete Book\n");
    printf("7.Exit system\n");
}

void addBook(){
    FILE *file = fopen ("Library.dat","ab");
    struct book newBook;

    printf("Enter book id: ");
    scanf("%d",&newBook.id);
    printf("Enter book title: ");
    scanf("%s",newBook.title);
    printf("Enter book author: ");
    scanf("%s",newBook.author);
    printf("Enter book quantity: ");
    scanf("%d",&newBook.quantity);

    fwrite(&newBook, sizeof(struct book), 1, file);

    fclose(file);

    printf("Book added successfully!\n");
}