#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "library.h"

/*
 * Function:  insert_book
 * --------------------
 * adds a new book to the library database file.
 *
 *  returns: EXIT_SUCCESS for success
 *           EXIT_FAILURE for failure
 *
 */

int insert_book (void) {

    /* open the database file */
    FILE* books_database = fopen("books.txt", "a");

    /* make sure database file is opened successfully */
    if (!books_database) {
        fprintf(stderr, "ERROR: Couldn't open the database file.\n");
        exit(EXIT_FAILURE);
    }

    /* prompt the user for input */
    system("clear");
    puts("To insert a new book, please enter the book's information as shown in the example below:\n\
(ex. C How to Program, Paul Deitel, Pearson Education. Inc, 0-13-612356-2, 29/10/2009, 5, 3, Programming)");

    /* read user input */
    char* book_info = get_book_info();

    /* make sure the get_book_info function returned a valid pointer value */
    if (!book_info) {
        fprintf(stderr, "ERROR: Couldn't read the book info.\n");
        exit(EXIT_FAILURE);
    }

    /* create a book structure to store the book info for further manipulation and validation */
    Book* book = (Book*) malloc(sizeof(Book));

    /* make sure the allocation was performed successfully */
    if (!book) {
        fprintf(stderr, "ERROR: Not enough memory.\n");
        exit(EXIT_FAILURE);
    }

    /* fill the book structure with book info read */

    char tk_book_info[150];          // created a copy of book_info to protect it from the "strtok" function
    strcpy(tk_book_info, book_info); // in "initialize_book" function

    initialize_book(book, tk_book_info);

    /* validate the read book */
    validate_book(book);

    /* store book in database */
    if(!fputs(book_info, books_database)) {
        fprintf(stderr, "ERROR: Couldn't add the book.\n");
        exit(EXIT_FAILURE);
    }

    return EXIT_SUCCESS;
}

/*
 * Function:  get_book_info
 * --------------------
 * reads in a string of book information from the user.
 *
 *  returns: a pointer to the read string.
 *
 */

char* get_book_info (void) {

    // allocate enough memory to store the book info string
    char* book_info = (char*) malloc(sizeof(char) * 150);

    // read user input
    fgets(book_info, 150, stdin);

    // return a pointer to the book info string
    return book_info;

}

/*
 * Function:  initialize_book
 * --------------------
 * fills a given Book struct with the appropriate values for each member from a given book info string.
 *
 *  returns: EXIT_SUCCESS on success
 *           EXIT_FAILURE on failure
 *
 */

int initialize_book (Book* book, char* book_info) {

    // We need a pointer to handle the token.
    char* token = NULL;

    if (token = strtok(book_info, ","))
        strcpy(book->title, token);
    else {
        fprintf(stderr, "ERROR: Couldn't process the book info.\n");
        exit(EXIT_FAILURE);
    }

    if (token = strtok(NULL, ","))
        strcpy(book->author, token);
    else {
        fprintf(stderr, "ERROR: Couldn't process the book info.\n");
        exit(EXIT_FAILURE);
    }

    if (token = strtok(NULL, ","))
        strcpy(book->publisher, token);
    else {
        fprintf(stderr, "ERROR: Couldn't process the book info.\n");
        exit(EXIT_FAILURE);
    }

    if (token = strtok(NULL, ","))
        strcpy(book->ISBN, token);
    else {
        fprintf(stderr, "ERROR: Couldn't process the book info.\n");
        exit(EXIT_FAILURE);
    }

    if (token = strtok(NULL, ","))
        strcpy(book->date_of_publication, token);
    else {
        fprintf(stderr, "ERROR: Couldn't process the book info.\n");
        exit(EXIT_FAILURE);
    }

    if (token = strtok(NULL, ","))
        book->number_of_copies = (unsigned int) atoi(token);
    else {
        fprintf(stderr, "ERROR: Couldn't process the book info.\n");
        exit(EXIT_FAILURE);
    }

    if (token = strtok(NULL, ","))
        book->number_of_available_copies = (unsigned int) atoi(token);
    else {
        fprintf(stderr, "ERROR: Couldn't process the book info.\n");
        exit(EXIT_FAILURE);
    }

    if (token = strtok(NULL, ","))
        strcpy(book->category, token);
    else {
        fprintf(stderr, "ERROR: Couldn't process the book info.\n");
        exit(EXIT_FAILURE);
    }

    return EXIT_SUCCESS;
}
