#include <stdio.h>

#define MAX_STR_LEN 30
#define MAX_ADDRESS_LEN 200
#define ISBN_LEN 20
#define MAX_DATE_LEN 20

/*
 * Defined a new type "Date" which is a struct that holds all relevant information regarding a date.
 */
typedef struct {

    int day;
    int month;
    int year;

}Date;

/*
 * Defined a new type "Book" which is a struct that holds all relevant information regarding a book.
 */
typedef struct {

    char title[MAX_STR_LEN];
    char author[MAX_STR_LEN];
    char publisher[MAX_STR_LEN];
    char ISBN[ISBN_LEN];
    Date date_of_publication;
    char category[MAX_STR_LEN];
    int number_of_copies;
    int number_of_available_copies;

}Book;


/*
 * Function prototypes.
 */
char* get_string (FILE*);
int insert_book(void);
int initialize_book(Book*, char*);
int validate_book(Book*, FILE*);
int search_book(void);

int add_new_copies(void);
int delete_book(void);