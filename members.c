#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>
#include "books.h"
#include "members.h"
#include <time.h>

int validate_name (char* name) {

    if (strcmp(name, "exit") == 0) return 0;

    char* chk = name;
    while(*chk != '\0') {
        if (isalpha(*chk) || *chk == ' ' || *chk == '\n') chk++;
        else return 1;
    }

    return 0;
}

int validate_number (char* number, char* config) {

    if (strcmp(number, "exit") == 0) return 0;

    if (strcmp(config, "phone") == 0) {
        char* chk = number;
        while(*chk != '\0') {
            if (strlen(number) != 11 || *number != '0' || *(number + 1) != '1' || isalpha(*chk)) return 1;
            else chk++;
        }
    } else if (strcmp(config, "building") == 0) {
        char* chk = number;
        while(*chk != '\0') {
            if (!isalpha(*chk) || *chk == '\n') chk++;
            else return 1;
        }
    }

    return 0;
}

int validate_email (char* email) {

    if (strcmp(email, "exit") == 0) return 0;

    if (strlen(email) < 4) return 1;

    int at_count = 0, dot_count = 0, before_count = 0, after_count = 0, final_count = 0;
    char* chk = email;

    for (int i = 0, n = strlen(email); i < n; i++) {
        if (isalpha(email[i]) && at_count == 0) before_count++;
        else if (email[i] == '@') at_count++;
        else if (isalpha(email[i]) && at_count == 1 && dot_count == 0) after_count++;
        else if (email[i] == '.') dot_count++;
        else if (isalpha(email[i]) && dot_count == 1) final_count++;
    }

    if (at_count != 1 || dot_count != 1 || before_count < 1 || after_count < 1 || final_count < 1) return 1;
    else return 0;
}


/*
 * Function:  register_member
 * --------------------
 * registers a new member to the library database file.
 *
 * Steps for inserting a new book:
 *  1. Open the database file.
 *  2. Prompt the user for input.
 *  3. Read and validate the member information.
 *  4. Store the member information string in the database file.
 *  5. Close the database file.
 *
 *  returns: 0 on success
 *           1, 2, 3 on failure
 *
 *           # - Error codes
 *           ----------------------------------------------
 *           1 = Error opening/closing a database file
 *           2 = Error allocating memory
 *           3 = User abort
 *           4 = Error updating database file
 */

int register_member (void) {
    /********************************/
    /** 1. Open the database file. **/
    /********************************/

    /* open database file in read/write mode */
    FILE* members_database = fopen("members.txt", "a+");

    /* make sure database file opened successfully */
    if (!members_database) {
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
    puts("To register a new member, please enter the members's information as prompted:\n\
Note: To cancel this action type \"exit\" without the double quotes.");

    /**************************************************/
    /** 3. Read and validate the member information. **/
    /**************************************************/
    Member* member = (Member*) malloc(sizeof(Member));

    /* make sure the allocation was performed successfully */
    if (!member) {
        fprintf(stderr, "ERROR: Not enough memory.\n");
        puts("Enter any character to continue...");
        getchar();
        return 2;
    }

    /* read and validate the first name */
    char* first_name = NULL;

    do {

        printf("First Name: ");
        first_name = get_string(stdin);

    } while (validate_name(first_name));

    /* exit */
    if (strcmp(first_name, "exit") == 0) return 3;

    strcpy(member->first_name, first_name);

    /* read and validate the last name */
    char* last_name = NULL;

    do {

        printf("Last Name: ");
        last_name = get_string(stdin);

    } while (validate_name(last_name));

    /* exit */
    if (strcmp(last_name, "exit") == 0) return 3;

    strcpy(member->last_name, last_name);

    /* read and validate the phone number */
    char* phone_number = NULL;

    do {

        printf("Phone Number: ");
        phone_number = get_string(stdin);

    } while (validate_number(phone_number, "phone"));

    /* exit */
    if (strcmp(phone_number, "exit") == 0) return 3;

    strcpy(member->phone_number, phone_number);

    /* read and validate the address */
    char* building_no;

    do {

        printf("Building Number: ");
        building_no = get_string(stdin);

    } while (validate_number(building_no, "building"));

    /* exit */
    if (strcmp(building_no, "exit") == 0) return 3;

    char* street;

    do {

        printf("Street: ");
        street = get_string(stdin);

    } while (validate_name(street));

    /* exit */
    if (strcmp(street, "exit") == 0) return 3;

    char* city;

    do {

        printf("City: ");
        city = get_string(stdin);

    } while (validate_name(city));

    /* exit */
    if (strcmp(city, "exit") == 0) return 3;

    char address[MAX_ADDRESS_LEN];
    snprintf(address, MAX_ADDRESS_LEN, "%s, %s, %s", building_no, street, city);

    strcpy(member->address, address);

    /* read and validate the email */
    char* email;

    do {

        printf("Email: ");
        email = get_string(stdin);

    } while (validate_email(email));

    /* exit */
    if (strcmp(email, "exit") == 0) return 3;

    strcpy(member->email, email);

    /* read and validate the age */
    int age;

    do {

        printf("Age: ");
        scanf("%d", &age);

    } while (age < 1);

    member->age = age;

    /****************************************************************/
    /** 4. Store the book information string in the database file. **/
    /****************************************************************/

    char final[MAX_STR_LEN];
    sprintf(final, "%s, %s, %d, %s, %s, %d, %s", member->last_name, member->first_name, 95314, member->address, member->phone_number, member->age, member->email);

    /* store book in database */
    if(!fputs(final, members_database)) {
        fprintf(stderr, "ERROR: Couldn't register the member.\n");
        puts("Enter any character to continue...");
        getchar();
        return 6;
    }

    /* add a newline to the database */
    fprintf(members_database, "\n");

    /************************/
    /** 5. Close databases **/
    /************************/

    /* close the database file and free any allocated memory*/

    if (fclose(members_database) == EOF) {
        fprintf(stderr, "ERROR: Couldn't close the database.\n");
        puts("Enter any character to continue...");
        getchar();
        return 1;
    }

    free(member);

    /*************/
    /** 6. Exit **/
    /*************/

    getchar();
    puts("Member registered successfully.");
    puts("Press any key to continue...");
    getchar();
    return 0;
}

/*
 * Function:  borrow_book
 * --------------------
 * borrows a book to a member given the book's ISBN and the members ID.
 *
 *  returns: 0 on success
 */
int borrow_book(void) {

    /********************************/
    /** 1. Open the database file. **/
    /********************************/

    /* open database files in appropriate mode */
    FILE* members_database = fopen("members.txt", "r");
    FILE* books_database   = fopen("books.txt", "r");
    FILE* borrows_database = fopen("borrows.txt", "r+");
    FILE* temp_database    = fopen("temp.txt", "w");

    /* make sure database file opened successfully */
    if (!members_database || !borrows_database) {
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
    puts("To borrow a book, please enter the members's ID followed by the ISBN of the book:\n\
Note: To cancel this action type \"exit\" without the double quotes.");

    /********************************/
    /** 3. Read and validate data. **/
    /********************************/

    char* input = get_string(stdin);

    if (!input) {

        fprintf(stderr, "ERROR: Couldn't read user input.\n");
        puts("Enter any character to continue...");
        getchar();
        return 2;

    } else if (strcmp(input, "exit") == 0) {

        return 3;

    }

    char* ID_s = strtok(input, " ");
    char* ISBN = strtok(NULL, " ");

    // validate the given ISBN
    if (strlen(ISBN) != 13) return 4;

    // validate the given ID
    int ID = atoi(ID_s);
    if (ID < 1) return 4;

    /**************************************/
    /** 4. Make sure the given ID exists **/
    /**************************************/

    char member[MAX_STR_LEN];
    int found = 1;

    while (fgets(member, MAX_STR_LEN, members_database)) {

        if (!strstr(member, ID_s)) {
            found = 0;
        }
    }

    if (found = 0) {

        fprintf(stderr, "ERROR: No member with the given ID was found.\n");
        puts("Enter any character to continue...");
        getchar();
        return 5;

    }

    /*************************************/
    /** 5. Count the number of borrows. **/
    /*************************************/

    char borrow[MAX_STR_LEN];
    int borrow_count = 0;

    while (fgets(borrow, MAX_STR_LEN, borrows_database)) {

        strstr(borrow, ID_s) ? borrow_count++ : borrow_count;

    }

    // a member can not borrow more than 3 books at the same time
    if (borrow_count >= 3) {

        fprintf(stderr, "ERROR: A member can not borrow more than 3 books at the same time.\n");
        puts("Enter any character to continue...");
        getchar();
        return 6;

    }

    /*****************************************/
    /** 6. Make sure the given book exists. **/
    /*****************************************/

    char book[MAX_STR_LEN];
    found = 0;
    Book req_book;


    // search for the required book
    while (fgets(book, MAX_STR_LEN, books_database)) {

        if (strstr(book, ISBN)) {

            initialize_book(&req_book, book);
            found = 1;
            break;

        }

    }

    // exit if not found
    if (found == 0) {

        fprintf(stderr, "ERROR: No book with the given ISBN was found.\n");
        puts("Enter any character to continue...");
        getchar();
        return 7;

    }

    // check number of available copies
    if (req_book.number_of_available_copies < 1) {

        fprintf(stderr, "ERROR: Insufficient number of available book copies.\n");
        puts("Enter any character to continue...");
        getchar();
        return 8;

    }

    /**************************************************/
    /** 7. Decrement the number of available copies. **/
    /**************************************************/

    req_book.number_of_available_copies--;

    char line[MAX_STR_LEN];

    rewind(books_database);
    while (fgets(line, MAX_STR_LEN, books_database)) {

        if (!strstr(line, ISBN)) {

            fputs(line, temp_database);

        }

    }

    snprintf(line, MAX_STR_LEN, "%s, %s, %s, %s, %d/%d/%d, %d, %d, %s", req_book.title, req_book.author, req_book.publisher, req_book.ISBN, req_book.date_of_publication.day, req_book.date_of_publication.month, req_book.date_of_publication.year, req_book.number_of_copies, req_book.number_of_available_copies, req_book.category);
    fputs(line, temp_database);

    // delete the contents of the book database
    fclose(books_database);
    books_database = fopen("books.txt", "w");

    fclose(temp_database);
    temp_database = fopen("temp.txt", "r");

    // get all books stored in the temp database
    while (fgets(line, MAX_STR_LEN, temp_database)) {

        // write them to the empty main database
        fputs(line, books_database);

    }

    /*******************************/
    /** 8. Update borrow database **/
    /*******************************/

    time_t current_time;
    time(&current_time);

    struct tm* local_time = localtime(&current_time);

    char date_issued[MAX_STR_LEN];
    snprintf(date_issued, MAX_STR_LEN, "%d/%d/%d", local_time->tm_mday, local_time->tm_mon + 1, local_time->tm_year + 1900);

    int grace;
    do {

        printf("Enter grace period (in days): ");
        scanf("%d", &grace);

    } while (grace < 0);


    current_time += (grace * 24 * 60 * 60);
    struct tm* futr_time = localtime(&current_time);

    char due_date[MAX_STR_LEN];
    snprintf(due_date, MAX_STR_LEN, "%d/%d/%d", futr_time->tm_mday, futr_time->tm_mon + 1, futr_time->tm_year + 1900);

    fprintf(borrows_database, "%s, %s, %s, %s, 0/0/0\n", ISBN, ID_s, date_issued, due_date);

    /************************************/
    /** 9. Close databases and return. **/
    /************************************/

    fclose(books_database);
    fclose(members_database);
    fclose(borrows_database);
    remove("temp.txt");

    puts("Press any key to continue...");
    getchar();
    return 0;

}