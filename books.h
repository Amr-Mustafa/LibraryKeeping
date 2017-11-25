#include <stdio.h>

#define MAX_STR_LEN 30
#define MAX_ADDRESS_LEN 60
#define ISBN_LEN 13
#define MAX_DATE_LEN 11

/*
 * Defined a new type "Book" which is a struct that holds all relevant information regarding a book.
 */
typedef struct {

    char title[MAX_STR_LEN];
    char author[MAX_STR_LEN];
    char publisher[MAX_STR_LEN];
    char ISBN[ISBN_LEN + 1];
    char date_of_publication[MAX_DATE_LEN + 1];
    char category[MAX_STR_LEN];
    unsigned int number_of_copies;
    unsigned int number_of_available_copies;

}Book;

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
    unsigned int ID;
    unsigned int phone_number;
    unsigned short age;

}Member;


/*
 * Function prototypes.
 */
char* get_book_info(void);
int insert_book(void);
int initialize_book(Book*, char*);
int validate_book(Book*, FILE*);

void search_book();
int add_new_copy();