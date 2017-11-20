#include <stdio.h>
#include <stdlib.h>
#include "library.h"

/*
 * Function:  insert_book
 * --------------------
 * adds a new book to the library database file.
 *
 *  n: number of terms in the series to sum
 *
 *  returns: 1 for success
 *           0 for failure
 *
 */

int insert_book (void) {

    // Open the database file.
    FILE* books_database = fopen("books.txt", "a");

    // Make sure database file is opened successfully.
    if (!books_database) {
        fprintf(stderr, "ERROR: Couldn't open the database file.\n");
        exit(EXIT_FAILURE);
    }

    // Prompt the user for input.
    system("clear");
    puts("To insert a new book, please enter the book's information as shown in the example below:\n\
(ex. C How to Program, Paul Deitel, Pearson Education. Inc, 0-13-612356-2, 29/10/2009, 5, 3, Programming)");

    // Read user input.
    char* book_info = get_book_info();

    // Make sure the get_book_info function returned a valid pointer value.
    if (!book_info) {
        fprintf(stderr, "ERROR: Couldn't read the book info.\n");
        exit(EXIT_FAILURE);
    }

    

    // Store book in database.
    fputs(book_info, books_database);



}