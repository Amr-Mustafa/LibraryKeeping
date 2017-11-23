#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "books.h"

void open_main_menu(void);
void open_book_menu(void);
char get_main_label(void);
void do_main_label(char);
char get_book_label (void);
void do_book_label(char);

int main() {

    // open main menu
    open_main_menu();

    return 0;
}

void open_main_menu() {

    while(1) {
        // clear the screen
        system("clear");

        // show main menu
        printf("To choose an option, enter its letter label:\n\
        a) Book Management\n\
        b) Member Management\n\
        c) Borrow Management\n\
        d) Administrative Actions\n\
        e) Save Changes\n\
        f) Save and Exit\n\
        g) Exit without Saving\n");

        // wait for user input
        char label = get_main_label();

        // respond accordingly
        do_main_label(label);
    }

}

void open_book_menu() {

    while(1) {
        // clear the screen
        system("clear");

        // show book menu
        printf("To choose an option, enter its letter label:\n\
        a) Insert a new book\n\
        b) Search for a book\n\
        c) Add new copies\n\
        d) Delete a book\n\
        e) Edit a book\n\
        f) <-- back\n");

        // wait for user input
        char label = get_book_label();

        // respond accordingly
        do_book_label(label);
    }
}

/*
 * Function:  get_main_label
 * -------------------------
 * Reads in the label from the user and validate it.
 *
 *  returns: a copy of the label read.
 */
char get_main_label (void) {

    // Store label input.
    char label;

    // Skip whitespaces and read the label.
    while(!isalpha((label = getchar())));

    // Validate input.
    if (label < 'a' || label > 'g') {
        fprintf(stderr, "ERROR: Invalid input.\n");
        exit(EXIT_FAILURE);
    }

    // Return the label.
    return label;
}

/*
 * Function:  get_book_label
 * -------------------------
 * Reads in the label from the user and validate it.
 *
 *  returns: a copy of the label read.
 */
char get_book_label (void) {

    // Store label input.
    char label;

    // Skip whitespaces and read the label.
    while(!isalpha((label = getchar())));

    // Validate input.
    if (label < 'a' || label > 'f') {
        fprintf(stderr, "ERROR: Invalid input.\n");
        exit(EXIT_FAILURE);
    }

    // Return the label.
    return label;
}

/*
 * Function:  do_main_label
 * -------------------------
 * Reads in the label from the user and validate it.
 *
 *  returns: a copy of the label read.
 */
void do_main_label(char label) {

    switch (label) {
        case 'a':
            open_book_menu();
            break;

        case 'b':
            break;

        case 'c':
            break;

        case 'd':
            break;

        case 'e':
            break;
    }
}

/*
 * Function:  do_book_label
 * -------------------------
 * Reads in the label from the user and validate it.
 *
 *  returns: a copy of the label read.
 */
void do_book_label(char label) {

    switch (label) {
        case 'a':
            insert_book();
            break;

        case 'b':
            break;

        case 'c':
            break;

        case 'd':
            break;

        case 'e':
            break;

        case 'f':
            open_main_menu();
            break;
    }
}