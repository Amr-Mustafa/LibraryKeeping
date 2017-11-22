#include <stdio.h>
#include "books.h"

int main() {

    while (1) {

        // Show menu.
        show_menu();

        // Read user input.
        char label = get_label();

        // Respond accordingly.
        do_label(label, plane, 12);

    }

    return 0;
}