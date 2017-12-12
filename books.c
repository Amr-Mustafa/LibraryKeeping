#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>
#include "books.h"

/*
 * Function:  get_string
 * --------------------
 * reads a string of characters from the specified file stream untill \n is encountered.
 *
 *  returns: a pointer to a null terminated string on success
 *           NULL on failure
 */

char* get_string (FILE* stream) {

    // point to the string allocated for the user input
    char* str = NULL;

    // store character input
    char c;

    // indices
    int i = 1, j = 0;

    //skip whitespaces before user input
    while(!isalpha((c = getc(stream))) && !isdigit((c)));

    // the last digit read is a non-whitespace character so we need to push it again into the stdin
    ungetc(c, stream);

    // read character and allocate memory for it until \n is encountered
    while(((c = getc(stream)) != '\n')) {

        // allocate memory for the read character
        str = realloc(str, i++ * sizeof(char));

        // add the read character to the string and increment the index
        str[j++] = c;
    }

    // add the null terminating character to the string
    str[j] = '\0';

    // return a pointer to the read string or NULL
    return str;
}

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
 *  returns: 0 on success
 *           1, 2, 3, 4, 5, 6, 7 on failure
 *
 *           # - Error codes
 *           ----------------------------------------------
 *           1 = Error opening/closing a database file
 *           2 = Error reading the book information string
 *           3 = User abort
 *           4 = Error allocating memory
 *           5 = Invalid book information (duplicated ISBN)
 *           6 = Error updating database file
 *           7 = Error processing book info string
 */

int insert_book (void) {

    /********************************/
    /** 1. Open the database file. **/
    /********************************/

    /* open database file in read/write mode */
    FILE* books_database = fopen("books.txt", "r+");

    /* make sure database file opened successfully */
    if (!books_database) {
        fprintf(stderr, "ERROR: Couldn't open the database file.\n");
        puts("Enter any character to continue...");
        getchar();
        return 1;
    }

    /***********************************/
    /** 2. Prompt the user for input. **/
    /***********************************/

    /* prompt the user for input */
    system("clear");
    puts("To insert a new book, please enter the book's information as shown in the example below:\n\
(ex. C How to Program, Paul Deitel, Pearson Education. Inc, 0-13-612356-2, 29/10/2009, 5, 3, Programming)\n\
Note: To cancel this action type \"exit\" without the double quotes.");

    /******************************************/
    /** 3. Read the book information string. **/
    /******************************************/

    /* read user input */
    char* book_info = get_string(stdin);

    /* make sure the get_string function returned a valid pointer value */
    if (!book_info) {
        fprintf(stderr, "ERROR: Couldn't read the book info.\n");
        puts("Enter any character to continue...");
        getchar();
        return 2;
    }

    /* exit */
    if (strcmp(book_info, "exit") == 0) return 3;



    /******************************************/
    /** 4. Validate book information string. **/
    /******************************************/

    /* create a book structure to store the book info for further manipulation and validation */
    Book* book = (Book*) malloc(sizeof(Book));

    /* make sure the allocation was performed successfully */
    if (!book) {
        fprintf(stderr, "ERROR: Not enough memory.\n");
        puts("Enter any character to continue...");
        getchar();
        return 4;
    }

    /* fill the book structure with book info read */

    char tk_book_info[150];          // created a copy of book_info to protect it from the "strtok" function
    strcpy(tk_book_info, book_info); // in "initialize_book" function

    if (initialize_book(book, tk_book_info)) {
        // couldn't process book info string
        puts("Enter any character to continue...");
        getchar();
        return 7;
    }

    /* validate the read book */
    int res = validate_book(book, books_database);
    if (res == 1) {
        fprintf(stderr, "ERROR: A book with the exact ISBN already exists.\n");
        puts("Enter any character to continue...");
        getchar();
        return 5;
    } else if (res == 2) {
        fprintf(stderr, "ERROR: Invalid author name.\n");
        puts("Enter any character to continue...");
        getchar();
        return 5;
    } else if (res == 3) {
        fprintf(stderr, "ERROR: Invalid number of [available] copies.\n");
        puts("Enter any character to continue...");
        getchar();
        return 5;
    } else if (res == 4) {
        fprintf(stderr, "ERROR: Invalid book category.\n");
        puts("Enter any character to continue...");
        getchar();
        return 5;
    } else if (res == 5) {
        fprintf(stderr, "ERROR: Invalid date of publication.\n");
        puts("Enter any character to continue...");
        getchar();
        return 5;
    } else if (res == 6) {
        fprintf(stderr, "ERROR: Invalid ISBN.\n");
        puts("Enter any character to continue...");
        getchar();
        return 5;
    }

    /****************************************************************/
    /** 5. Store the book information string in the database file. **/
    /****************************************************************/

    /* store book in database */
    if(!fputs(book_info, books_database)) {
        fprintf(stderr, "ERROR: Couldn't add the book.\n");
        puts("Enter any character to continue...");
        getchar();
        return 6;
    }

    /* add a newline to the database */
    fprintf(books_database, "\n");

    printf("Book added successfully.\n");

    /*********************************/
    /** 6. Close the database file. **/
    /*********************************/

    /* close the database file and free any allocated memory*/
    if (fclose(books_database) == EOF) {
        fprintf(stderr, "ERROR: Couldn't close the database.\n");
        puts("Enter any character to continue...");
        getchar();
        return 1;
    }

    free(book);

    puts("Press any key to continue...");
    getchar();
    return 0;
}

/*
 * Function:  initialize_book
 * --------------------
 * fills a given Book struct with the appropriate values for each member from a given book info string.
 *
 *  returns: 0 on success
 *           1 on failure
 *
 */

int initialize_book (Book* book, char* book_info) {

    // we need a pointer to handle the token
    char* token = NULL;

    if (token = strtok(book_info, ",")) {
        strcpy(book->title, token);
    }
    else {
        fprintf(stderr, "ERROR: Couldn't process the book info.\n");
        return 1;
    }

    if (token = strtok(NULL, ",")) {
        strcpy(book->author, token + 1);
    }
    else {
        fprintf(stderr, "ERROR: Couldn't process the book info.\n");
        return 1;
    }

    if (token = strtok(NULL, ",")) {
        strcpy(book->publisher, token + 1);
    }
    else {
        fprintf(stderr, "ERROR: Couldn't process the book info.\n");
        return 1;
    }

    if (token = strtok(NULL, ",")) {
        strcpy(book->ISBN, token + 1);
    }
    else {
        fprintf(stderr, "ERROR: Couldn't process the book info.\n");
        return 1;
    }

    if (token = strtok(NULL, ",")) {
        char* date_token = token + 1;
        char* save_ptr = date_token;

        date_token = strtok_r(date_token, "/", &save_ptr);
        book->date_of_publication.day = atoi(date_token);

        date_token = strtok_r(NULL, "/", &save_ptr);
        book->date_of_publication.month = atoi(date_token);

        date_token = strtok_r(NULL, "/", &save_ptr);
        book->date_of_publication.year = atoi(date_token);
    }
    else {
        fprintf(stderr, "ERROR: Couldn't process the book info.\n");
        return 1;
    }

    if (token = strtok(NULL, ",")) {
        book->number_of_copies = (unsigned int) atoi(token);
    }
    else {
        fprintf(stderr, "ERROR: Couldn't process the book info.\n");
        return 1;
    }

    if (token = strtok(NULL, ",")) {
        book->number_of_available_copies = (unsigned int) atoi(token);
    }
    else {
        fprintf(stderr, "ERROR: Couldn't process the book info.\n");
        return 1;
    }

    if (token = strtok(NULL, ",")) {
        //token[strlen(token) - 1] = '\0'; commented unless otherwise
        strcpy(book->category, token + 1);
    }
    else {
        fprintf(stderr, "ERROR: Couldn't process the book info.\n");
        return 1;
    }

    return 0;
}

/*
 * Function:  validate_book
 * --------------------
 * given a book and a database file, it checks whether the book's ISBN is unique or not.
 *
 *  returns: 0 on success
 *           1,2 on failure
 *
 *           # - Error codes
 *           ----------------------------------------------
 *           1 = Duplicated ISBN
 *           2 = Invalid author
 *           3 = Invalid number of copies/available copies
 *           4 = Invalid category
 *           5 = Invalid date
 *           6 = Invalid ISBN
 */

int validate_book (Book* book, FILE* books_database) {

    // check for correct use
    if (book == NULL || books_database == NULL) {
        fprintf(stderr, "ERROR: Invalid arguments to function \"validate_book\"\n");
        return 1;
    }

    char book_info[150];

    Book book_d;


    // check author name
    char* chk = book->author;
    while(*chk != '\0') {
        if (isalpha(*chk) || *chk == ' ' || *chk == '\n' || *chk == '&') chk++;
        else return 2;
    }

    // check number of copies & number of available copies
    if (book->number_of_copies < 1 || book->number_of_available_copies < 1) {
        return 3;
    }

    // check category
    chk = book->category;
    while(*chk != '\0') {
        if (isalpha(*chk) || *chk == ' ' || *chk == '\n') chk++;
        else return 4;
    }

    // check date
    if (book->date_of_publication.day < 1 || book->date_of_publication.day > 31) return 5;
    if (book->date_of_publication.month < 1 || book->date_of_publication.month > 12) return 5;
    if (book->date_of_publication.year < 1 || book->date_of_publication.year > 2017) return 5;

    // check ISBN
    if (strlen(book->ISBN) != 13) return 6;

    // check ISBN uniqueness
    // get all books stored in the database
    while (fgets(book_info, 150, books_database)) {

        // initialize the current book in the current iteration with the read book info string
        initialize_book(&book_d, book_info);

        // make sure the ISBN of the book to be validated in unique
        if (strcmp(book_d.ISBN, book->ISBN) == 0) {

            // return 1 for failure
            return 1;
        }
    }

    // return 0 for success
    return 0;

}

/*
 * Function:  search_book
 * --------------------
 * searches for a book in the database file given a part of the book title, author, ISBN, or category.
 *
 * Steps for inserting a new book:
 *  1. Open the database file.
 *  2. Prompt the user for input.
 *  3. Read the lead.
 *  4. Iterate over all books in the database searching for the lead.
 *  5. Close the database file.
 *
 *  returns:
 *
 *
 */
int search_book (void) {

    /********************************/
    /** 1. Open the database file. **/
    /********************************/

    /* open the database file in read mode */
    FILE* books_database = fopen("books.txt", "r");

    /* make sure database file is opened successfully */
    if (!books_database) {
        fprintf(stderr, "ERROR: Couldn't open the database file.\n");
        return 1;
    }

    /***********************************/
    /** 2. Prompt the user for input. **/
    /***********************************/

    /* prompt the user for input */
    system("clear");
    puts("To search for a book, please enter below the book title, author, ISBN, or category.\n\
Note: To cancel this action type \"exit\" without the double quotes.");

    /***********************/
    /** 3. Read the lead. **/
    /***********************/
    char* lead = get_string(stdin);

    /* check for exit */
    if (strcmp(lead, "exit") == 0) return 2;

    /*****************************/
    /** 4. Search for the lead. **/
    /*****************************/

    /* declare book_info array to hold the current book's info string */
    char book_info[150];

    Book book_d;

    printf("Search Results:\n================\n");

    // get all books stored in the database
    while (fgets(book_info, 150, books_database)) {

        char tk_book_info[150];          // created a copy of book_info to protect it from the "strtok" function
        strcpy(tk_book_info, book_info); // in "initialize_book" function

        // initialize the current book in the current iteration with the read book info string
        initialize_book(&book_d, tk_book_info);

        /* search with the ISBN */
        if (strcmp(lead, book_d.ISBN) == 0) printf("%s", book_info);

        /* tokenize the lead if it contains more than one word */
        char tk_lead[50]; // created a copy of lead to protect it from the "strtok" function
        strcpy(tk_lead, lead);
        char* token;
        char* save_tk_lead = tk_lead;
        token = strtok_r(tk_lead, " ", &save_tk_lead);

        /* tokenize the category */
        char tk_book_cat[50];
        strcpy(tk_book_cat, book_d.category);
        char* category_token;
        char* save_cat = tk_book_cat;
        category_token = strtok_r(tk_book_cat, " ", &save_cat);
        category_token = strtok(category_token, "\n");


        /* tokenize the book title if it contains more than one word */
        char tk_book_title[150];
        strcpy(tk_book_title, book_d.title);
        char* title_token;
        char* save_title = tk_book_title;
        title_token = strtok_r(tk_book_title, " ", &save_title);

        /* tokenize the book author if it contains more than one word */
        char tk_book_author[150];
        strcpy(tk_book_author, book_d.author);
        char* author_token;
        char* save_author = tk_book_author;
        author_token = strtok_r(tk_book_author, " ", &save_author);

        // check whether the lead is one word or more
        token = strtok_r(NULL, " ", &save_tk_lead);
        token == NULL ? token = lead : NULL;

        while (token) {

            while (title_token || author_token || category_token) {
                // check for a match
                if ((title_token != NULL ? (strcmp(token, title_token) == 0) : 0) || (category_token != NULL ? (strcmp(token, category_token) == 0) : 0) || (author_token != NULL ? (strcmp(token, author_token) == 0) : 0)) {
                    printf("%s", book_info);
                }

                // get the next token
                title_token = strtok_r(NULL, " ", &save_title);
                author_token = strtok_r(NULL, " ", &save_author);
                category_token = strtok_r(NULL, " ", &save_cat);
                category_token = strtok(category_token, "\n");
            }

            strcmp(token, lead) == 0 ? (token = NULL) : (token = strtok_r(NULL, " ", &save_tk_lead));
        }

    }

    /*********************************/
    /** 5. Close the database file. **/
    /*********************************/

    /* close the database file */
    if (fclose(books_database) == EOF) {
        fprintf(stderr, "ERROR: Couldn't close the database.\n");
        exit(EXIT_FAILURE);
    }

    puts("Press any key to continue...");
    getchar();
    return 0;

}

/*
 * Function:  add_new_copies
 * --------------------
 * prompts the user for an ISBN and the number of copies to be added and updates the records.
 *
 * Steps for inserting a new book:
 *  1. Open the temporary database file.
 *  2. Prompt the user for input.
 *  3. Read the ISBN and number of copies.
 *  4. Iterate over all books in the database searching for the ISBN.
 *  5. Update the temporary database file.
 *  5. Close the temporary database file.
 *
 *  returns: 0 on success and 1 on failure and -1 on user exit.
 *
 */

int add_new_copies (void) {
    /************************/
    /** 1. Open databasse. **/
    /************************/

    /* open the temporary database file in read mode */
    FILE* books_database = fopen("books.txt", "r");

    /* make sure database file is opened successfully */
    if (!books_database) {
        fprintf(stderr, "ERROR: Couldn't open the database file.\n");
        return 1;
    }

    /* open the intermediate database file in read/write mode */
    FILE* intermediate_database = fopen("intermediate.txt", "w");

    /* make sure database file is opened successfully */
    if (!intermediate_database) {
        fprintf(stderr, "ERROR: Couldn't open the database file.\n");
        return 1;
    }

    /***********************************/
    /** 2. Prompt the user for input. **/
    /***********************************/

    /* prompt the user for input */
    system("clear");
    puts("To add new copies for an existing book, please enter below the ISBN.\nNote: To cancel this action type \"exit\" without the double quotes.");

    /********************************************/
    /** 3. Read the ISBN and number of copies. **/
    /********************************************/

    /* read the ISBN */
    char* ISBN = get_string(stdin);

    /* check for exit */
    if (strcmp(ISBN, "exit") == 0) return -1;

    /* read the number of copies */
    int num_copies;
    do {
        puts("Enter below the number of copies to be added.");
        scanf("%d", &num_copies);
    } while (num_copies < 1);

    /************************************************************************************************/
    /** 4. Search for a book with the read ISBN and copy all others into the intermediate database **/
    /************************************************************************************************/

    char book_info[150];
    char book_t[150];
    char tk_book_info_2[150];
    char tk_book_info_3[150];
    Book book_d;
    int found = 0;

    // make sure there exits a book with the given ISBN
    while (fgets(book_info, 150, books_database)) {

        strcpy(tk_book_info_3, book_info);

        // initialize the current book in the current iteration with the read book info string
        initialize_book(&book_d, tk_book_info_3);

        // compare the read ISBN with the current book's ISBN
        if (strcmp(ISBN, book_d.ISBN) == 0) {
            found = 1;
            break; // found
        }
    }

    if (found == 0) {
        // delete the intermediate file
        remove("intermediate.txt");
        fprintf(stderr, "ERROR: No book with the given ISBN could be found.\n");
        getchar();
        puts("Press any key to continue...");
        getchar();
        return 2;
    }

    rewind(books_database);

    // get all books stored in the database
    while (fgets(book_info, 150, books_database)) {

        strcpy(tk_book_info_2, book_info);

        // initialize the current book in the current iteration with the read book info string
        initialize_book(&book_d, tk_book_info_2);

        // compare the read ISBN with the current book's ISBN
        if (strcmp(ISBN, book_d.ISBN) != 0) {
            // if not equal then copy this book to the intermediate database file
            fputs(book_info, intermediate_database);
        } else {
            strcpy(book_t, book_info);
        }
    }

    /******************************************************/
    /** 5. Delete the contents of the temporary database **/
    /******************************************************/

    // close the temporary database
    fclose(books_database);
    fclose(intermediate_database);

    //re-open it in write mode to delete its contents
    FILE* books_database_N = fopen("books.txt", "w");
    FILE* intermediate_database_N = fopen("intermediate.txt", "r");

    /* make sure database file is opened successfully */
    if (!books_database_N) {
        fprintf(stderr, "ERROR: Couldn't open the database file.\n");
        return 1;
    }

    /* make sure database file is opened successfully */
    if (!intermediate_database_N) {
        fprintf(stderr, "ERROR: Couldn't open the database file.\n");
        return 1;
    }

    /************************************************************************************/
    /** 6. Write the contents of the intermediate database into the temporary database **/
    /************************************************************************************/

    // get all books stored in the database
    while (fgets(book_info, 150, intermediate_database_N)) {

        // write them to the empty temporary database
        fputs(book_info, books_database_N);
    }

    /************************************************************/
    /** 7. Write the updated book into the temporary database **/
    /************************************************************/

    char* ptr = book_t;
    char final[150];

    /* fill the book structure with book info */
    char tk_book_info[150];      // created a copy of book_t to protect it from the "strtok" function
    strcpy(tk_book_info, book_t); // in "initialize_book" function

    initialize_book(&book_d, tk_book_info);

    book_d.number_of_copies += num_copies;

    snprintf(final, 150, "%s, %s, %s, %s, %d/%d/%d, %d, %d, %s", book_d.title, book_d.author, book_d.publisher, book_d.ISBN, book_d.date_of_publication.day, book_d.date_of_publication.month, book_d.date_of_publication.year, book_d.number_of_copies, book_d.number_of_available_copies, book_d.category);

    fputs(final, books_database_N);

    /****************************/
    /** 8. Close all databases **/
    /****************************/
    fclose(books_database_N);

    // delete the intermediate file
    remove("intermediate.txt");

    getchar();
    puts("Book updated successfully.");
    puts("Press any key to continue...");
    getchar();
    return 0;

}

int delete_book (void) {
    /************************/
    /** 1. Open databasse. **/
    /************************/

    /* open the temporary database file in read mode */
    FILE* books_database = fopen("books.txt", "r");

    /* make sure database file is opened successfully */
    if (!books_database) {
        fprintf(stderr, "ERROR: Couldn't open the database file.\n");
        return 1;
    }

    /* open the intermediate database file in read/write mode */
    FILE* intermediate_database = fopen("intermediate.txt", "w");

    /* make sure intermediate database file is opened successfully */
    if (!intermediate_database) {
        fprintf(stderr, "ERROR: Couldn't open the database file.\n");
        return 1;
    }

    /***********************************/
    /** 2. Prompt the user for input. **/
    /***********************************/

    /* prompt the user for input */
    system("clear");
    puts("To delete an existing book, please enter below the ISBN.\nNote: To cancel this action type \"exit\" without the double quotes.");

    /********************************************/
    /** 3. Read the ISBN and number of copies. **/
    /********************************************/

    /* read the ISBN */
    char* ISBN = get_string(stdin);

    /* check for exit */
    if (strcmp(ISBN, "exit") == 0) return -1;

    /************************************************************************************************/
    /** 4. Search for a book with the read ISBN and copy all others into the intermediate database **/
    /************************************************************************************************/

    char book_info[150];
    char book_t[150];
    char tk_book_info_2[150];
    char tk_book_info_3[150];
    Book book_d;
    int found = 0;

    // make sure there exits a book with the given ISBN
    while (fgets(book_info, 150, books_database)) {

        strcpy(tk_book_info_3, book_info);

        // initialize the current book in the current iteration with the read book info string
        initialize_book(&book_d, tk_book_info_3);

        // compare the read ISBN with the current book's ISBN
        if (strcmp(ISBN, book_d.ISBN) == 0) {
            found = 1;
            break; // found
        }
    }

    if (found == 0) {
        // delete the intermediate file
        remove("intermediate.txt");

        fprintf(stderr, "ERROR: No book with the given ISBN could be found.\n");
        puts("Press any key to continue...");
        getchar();
        return 2;
    }

    rewind(books_database);

    // get all books stored in the database
    while (fgets(book_info, 150, books_database)) {

        strcpy(tk_book_info_2, book_info);

        // initialize the current book in the current iteration with the read book info string
        initialize_book(&book_d, tk_book_info_2);

        // compare the read ISBN with the current book's ISBN
        if (strcmp(ISBN, book_d.ISBN) != 0) {
            // if not equal then copy this book to the intermediate database file
            fputs(book_info, intermediate_database);
        } else {
            strcpy(book_t, book_info);
        }
    }

    /******************************************************/
    /** 5. Delete the contents of the temporary database **/
    /******************************************************/

    // close the temporary database
    fclose(books_database);
    fclose(intermediate_database);

    //re-open it in write mode to delete its contents
    FILE* books_database_N = fopen("books.txt", "w");
    FILE* intermediate_database_N = fopen("intermediate.txt", "r");

    /* make sure database file is opened successfully */
    if (!books_database_N) {
        fprintf(stderr, "ERROR: Couldn't open the database file.\n");
        return 1;
    }

    /* make sure database file is opened successfully */
    if (!intermediate_database_N) {
        fprintf(stderr, "ERROR: Couldn't open the database file.\n");
        return 1;
    }

    /************************************************************************************/
    /** 6. Write the contents of the intermediate database into the temporary database **/
    /************************************************************************************/

    // get all books stored in the database
    while (fgets(book_info, 150, intermediate_database_N)) {

        // write them to the empty temporary database
        fputs(book_info, books_database_N);
    }

    /****************************/
    /** 8. Close all databases **/
    /****************************/
    fclose(books_database_N);

    // delete the intermediate file
    remove("intermediate.txt");

    puts("Book deleted successfully.");
    puts("Press any key to continue...");
    getchar();
    return 0;
}
