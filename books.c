#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>
#include "books.h"

/*
 * Function:  insert_book
 * --------------------
 * adds a new book to the library database file.
 *
 * Steps for inserting a new book:
 *  1. Open the database file.
 *  2. Prompt the user for input.
 *  3. Read the book information string.
 *  4. Validate the book information.
 *      4.1. Unique ISBN.
 *  5. Store the book information string in the database file.
 *  6. Close the database file.
 *
 *  returns: EXIT_SUCCESS for success
 *           EXIT_FAILURE for failure
 *
 */

int insert_book (void) {

    /********************************/
    /** 1. Open the database file. **/
    /********************************/

    /* open the database file in read/write mode */
    FILE* books_database = fopen("books.txt", "r+");

    /* make sure database file is opened successfully */
    if (!books_database) {
        fprintf(stderr, "ERROR: Couldn't open the database file.\n");
        exit(EXIT_FAILURE);
    }

    /***********************************/
    /** 2. Prompt the user for input. **/
    /***********************************/

    /* prompt the user for input */
    system("clear");
    puts("To insert a new book, please enter the book's information as shown in the example below:\n\
(ex. C How to Program, Paul Deitel, Pearson Education. Inc, 0-13-612356-2, 29/10/2009, 5, 3, Programming)");

    /******************************************/
    /** 3. Read the book information string. **/
    /******************************************/

    /* read user input */
    char* book_info = get_book_info();

    /* make sure the get_book_info function returned a valid pointer value */
    if (!book_info) {
        fprintf(stderr, "ERROR: Couldn't read the book info.\n");
        exit(EXIT_FAILURE);
    }

    /******************************************/
    /** 4. Validate book information string. **/
    /******************************************/

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
    if (validate_book(book, books_database) == 1) {
        fprintf(stderr, "ERROR: A book with the exact ISBN already exists.\n");
        printf("You will be redirected in 3 seconds...\n");
        sleep(3);
        exit(EXIT_FAILURE);
    }

    /****************************************************************/
    /** 5. Store the book information string in the database file. **/
    /****************************************************************/

    /* store book in database */
    if(!fputs(book_info, books_database)) {
        fprintf(stderr, "ERROR: Couldn't add the book.\n");
        exit(EXIT_FAILURE);
    }

    printf("Book added successfully.\n");
    printf("You will be redirected in 3 seconds...\n");
    sleep(3);

    /*********************************/
    /** 6. Close the database file. **/
    /*********************************/

    /* close the database file */
    if (fclose(books_database) == EOF) {
        fprintf(stderr, "ERROR: Couldn't close the database.\n");
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

    // skip whitespaces and read the label
    char c;
    while(!isalpha(c = getchar()));
    ungetc(c, stdin);

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

    if (token = strtok(book_info, ",")) {
        //printf("title: %s\n", token);
        strcpy(book->title, token);
    }
    else {
        fprintf(stderr, "ERROR: Couldn't process the book info.\n");
        exit(EXIT_FAILURE);
    }

    if (token = strtok(NULL, ",")) {
        //printf("author: %s\n", token);
        strcpy(book->author, token);
    }
    else {
        fprintf(stderr, "ERROR: Couldn't process the book info.\n");
        exit(EXIT_FAILURE);
    }

    if (token = strtok(NULL, ",")) {
        //printf("publisher: %s\n", token);
        strcpy(book->publisher, token);
    }
    else {
        fprintf(stderr, "ERROR: Couldn't process the book info.\n");
        exit(EXIT_FAILURE);
    }

    if (token = strtok(NULL, ",")) {
        strcpy(book->ISBN, token);
    }
    else {
        fprintf(stderr, "ERROR: Couldn't process the book info.\n");
        exit(EXIT_FAILURE);
    }

    if (token = strtok(NULL, ",")) {
        //printf("date_of_publication: %s\n", token);
        strcpy(book->date_of_publication, token);
    }
    else {
        fprintf(stderr, "ERROR: Couldn't process the book info.\n");
        exit(EXIT_FAILURE);
    }

    if (token = strtok(NULL, ",")) {
        //printf("number_of_copies: %s\n", token);
        book->number_of_copies = (unsigned int) atoi(token);
    }
    else {
        fprintf(stderr, "ERROR: Couldn't process the book info.\n");
        exit(EXIT_FAILURE);
    }

    if (token = strtok(NULL, ",")) {
        //printf("number_of_available_copies: %s\n", token);
        book->number_of_available_copies = (unsigned int) atoi(token);
    }
    else {
        fprintf(stderr, "ERROR: Couldn't process the book info.\n");
        exit(EXIT_FAILURE);
    }

    if (token = strtok(NULL, ",")) {
        //printf("Category: %s\n", token);
        token[strlen(token) - 1] = '\0';
        strcpy(book->category, token);
    }
    else {
        fprintf(stderr, "ERROR: Couldn't process the book info.\n");
        exit(EXIT_FAILURE);
    }

    return EXIT_SUCCESS;
}

/*
 * Function:  validate_book
 * --------------------
 * validates a given book.
 *
 *  returns: 0 on success
 *           1 on failure
 *
 */

int validate_book (Book* book, FILE* books_database) {

    // check for correct use
    if (book == NULL || books_database == NULL) {
        fprintf(stderr, "ERROR: Invalid arguments to function \"validate_book\"\n");
        return 1;
    }

    char book_info[150];

    Book book_d;

    // get all books stored in the database
    while (fgets(book_info, 150, books_database)) {

        // initialize the current book in the current iteration with the read book info string
        initialize_book(&book_d, book_info);

        //printf("%s\n", book->ISBN);
        //sleep(30);

        // make sure the ISBN of the book to be validated in unique
        if (strcmp(book_d.ISBN, book->ISBN) == 0) {

            // return 1 for failure
            return 1;
        }
    }

    // return 0 for success
    return 0;

}