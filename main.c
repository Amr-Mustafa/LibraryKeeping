#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "books.h"
#include "members.h"
#include <unistd.h>

void open_main_menu(void);
void open_book_menu(void);
void open_members_menu(void);

char get_main_label(void);
char get_book_label(void);
char get_members_label(void);

void do_main_label(char);
void do_book_label(char);
void do_members_label(char);

int main() {

    // open main menu
    open_main_menu();

    return 0;
}

void open_main_menu() {

    while(1) {
        // clc the screen
        system("clc||clear");

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
        // clc the screen
        system("clc");

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

void open_members_menu() {

    while(1) {
        // clc the screen
        system("clc");

        // show book menu
        printf("To choose an option, enter its letter label:\n\
        a) Register member\n\
        b) Remove member\n\
        c) <-- back\n");

        // wait for user input
        char label = get_members_label();

        // respond accordingly
        do_members_label(label);
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

    do {

        // Skip whitespaces and read the label.
        while(!isalpha((label = getchar())));

    } while (label < 'a' || label > 'g');

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

    do {

        // Skip whitespaces and read the label.
        while(!isalpha((label = getchar())));

    } while (label < 'a' || label > 'f');

    // Return the label.
    return label;

    // Return the label.
    return label;
}

/*
 * Function:  do_main_label
 * -------------------------
 * Call a specific function based on the passed label.
 */
void do_main_label(char label) {

    switch (label) {
        case 'a':
            open_book_menu();
            break;

        case 'b':
            open_members_menu();
            break;

        case 'c':
            break;

        case 'd':
            break;

        case 'e':
            break;

        default:
            fprintf(stderr, "ERROR: Invalid argument to function do_main_label.");
    }
}

/*
 * Function:  do_book_label
 * -------------------------
 * Call a specific function based on the passed label.
 */
void do_book_label(char label) {

    switch (label) {
        case 'a':
            insert_book();
            break;

        case 'b':
            search_book();
            break;

        case 'c':
            add_new_copies();
            break;

        case 'd':
            delete_book();
            break;

        case 'e':
            break;

        case 'f':
            open_main_menu();
            break;

        default:
            fprintf(stderr, "ERROR: Invalid argument to function do_book_label.");
    }
}

/*
 * Function:  get_members_label
 * -------------------------
 * Reads in the label from the user and validate it.
 *
 *  returns: a copy of the label read.
 */
char get_members_label (void) {

    // Store label input.
    char label;

    do {

        // Skip whitespaces and read the label.
        while(!isalpha((label = getchar())));

    } while (label < 'a' || label > 'c');

    // Return the label.
    return label;

    // Return the label.
    return label;
}

/*
 * Function:  do_members_label
 * -------------------------
 * Call a specific function based on the passed label.
 */
void do_members_label(char label) {

    switch (label) {
        case 'a':
            register_member();
            break;

        case 'b':
            //remove_member();
            break;

        case 'c':
            open_main_menu();
            break;

        default:
            fprintf(stderr, "ERROR: Invalid argument to function do_members_label.");
    }
}