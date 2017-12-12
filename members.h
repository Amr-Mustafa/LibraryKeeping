#include <stdio.h>

/*
 * Defined a new type "Borrowed_book" which is a struct that holds all relevant information regarding a library member
 * and a single book he borrowed.
 */
typedef struct {

    char ISBN[ISBN_LEN + 1];
    unsigned int ID;
    char date_borrowed[MAX_DATE_LEN + 1];
    char date_due_return[MAX_DATE_LEN + 1];
    char date_returned[MAX_DATE_LEN + 1];

}Borrowed_book;


/*
 * Defined a new type "Member" which is a struct that holds all relevant information regarding a library member.
 */
typedef struct {

    char first_name[MAX_STR_LEN];
    char last_name[MAX_STR_LEN];
    char email[MAX_STR_LEN];
    char address[MAX_ADDRESS_LEN];
    int ID;
    char phone_number[MAX_STR_LEN];
    int age;

}Member;

int register_member(void);
int borrow_book(void);