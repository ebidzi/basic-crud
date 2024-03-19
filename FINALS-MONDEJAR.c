#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Define the maximum number of files that can be stored
#define MAX_FILES 100

// Structure for storing book information
typedef struct {
    char title[50];
    char author[50];
    int year;
    float price;
    char filename[100];
    int isRenamed;
} Book;

// Declare global variables
Book books[MAX_FILES];
int bookCount = 0;

// Declaration for functions
void writeFilenamesToFile();
void readFilenamesFromFile();
void createFile();
void updateFile();
void readFile();
void removeFile();
void renameFile();
void displayFiles();

// Function to write the masterlist document to "masterlist.txt"
void writeFilenamesToFile() {
    // Open the file in write mode
    FILE* file = fopen("masterlist.txt", "w");
    if (file == NULL) {
        printf("Error opening file: masterlist.txt\n");
        return;
    }
   

    // Write book information to the file
    /* This function puts the book information to the masterlist with this format:
    * Title | Author | Filename | Rename indicator
    *
    * the Rename indicator indicates if the file was renamed or not
    * if the file was renamed it will indicate 1, if not, it will indicate 0
    *
    */
    for (int loop = 0; loop < bookCount; loop++) {
        fprintf(file, "%s|%s|%s|%d\n", books[loop].title, books[loop].author, books[loop].filename, books[loop].isRenamed);
    }

    // Close the file
    fclose(file);
}

// Function to read the masterlist document from "masterlist.txt"
void readFilenamesFromFile() {
    // Open the file in read mode
    FILE* file = fopen("masterlist.txt", "r");
    if (file == NULL) {
        // If the file does not exist, return without doing anything
        return;
    }

    // Read book information from the file
    char line[200];
    while (fgets(line, sizeof(line), file) != NULL) {
        line[strcspn(line, "\n")] = '\0';

        char* title = strtok(line, "|");
        char* author = strtok(NULL, "|");
        char* filename = strtok(NULL, "|");
        int isRenamed = atoi(strtok(NULL, "|"));

        // Store the information in the books array
        strcpy(books[bookCount].title, title);
        strcpy(books[bookCount].author, author);
        strcpy(books[bookCount].filename, filename);
        books[bookCount].isRenamed = isRenamed;

        // Increment the book count
        bookCount++;
    }

    // Close the file
    fclose(file);
}


/* This function allows the user to create file by this format:
*  Title:
*  Author:
*  Publication Year:
*  Price:
*/
void createFile() {
    // Clear the console
    system("cls");

   printf("\n|=========================================================================|\n");
    printf("|                               Create a New File                         |\n");
    printf("|=========================================================================|\n");
    puts("");
   
    printf("Enter the title of the book: ");
    scanf(" %[^\n]", books[bookCount].title);
    printf("Enter the author of the book: ");
    scanf(" %[^\n]", books[bookCount].author);
   
   

    // Check if the book already exists in the masterlist (case-insensitive search)
    for (int loop = 0; loop < bookCount; loop++) {
        if (strcasecmp(books[loop].title, books[bookCount].title) == 0 && strcasecmp(books[loop].author, books[bookCount].author) == 0) {
            printf("\nA book with the same title and author already exists in the library.\n");
            printf("Please enter a unique title and author combination.\n");
            return;
        }
    }

    // Read additional book information
    printf("Enter year published: ");
    scanf(" %d", &books[bookCount].year);
    printf("Enter price: ");
    scanf(" %f", &books[bookCount].price);

    // Generate the filename for the book
    sprintf(books[bookCount].filename, "%s-%s.txt", books[bookCount].title, books[bookCount].author);
    books[bookCount].isRenamed = 0;

    // Create the file and write book information to it
    FILE* file = fopen(books[bookCount].filename, "w");
    if (file == NULL) {
        printf("Unable to create the file.\n");
        return;
    }

    // Increment the book count
    bookCount++;

    // Write book information to the file
    fprintf(file, "Title: %s\n", books[bookCount - 1].title);
    fprintf(file, "Author: %s\n", books[bookCount - 1].author);
    fprintf(file, "Year Published: %d\n", books[bookCount - 1].year);
    fprintf(file, "Price: %.2f\n", books[bookCount - 1].price);
    printf("\nFile created successfully.\n");
    fclose(file);

    // Update the masterlist file
    writeFilenamesToFile();
}

 
/* Function to Update file
*
*  Update Title || Author || Publication Year || Price
*
* With this function, it allows user to select which of these mentioned above he/she wants to update
*/
void updateFile() {
    // Clear the console
    system("cls");
    back:
    // Display the list of available files
    displayFiles();

    if (bookCount == 0) {
        printf("\nNo files available for updating.\n");
        return;
    }

   printf("\n|=========================================================================|\n");
    printf("|                                Update File                              |\n");
    printf("|=========================================================================|\n");
    puts("");
   
    printf("Enter the title of the book you want to update: ");
    char updateTitle[50];
    scanf(" %[^\n]", updateTitle);

    printf("Enter the author of the book you want to update: ");
    char updateAuthor[50];
    scanf(" %[^\n]", updateAuthor);
   
    system("cls");
   
   
    printf("\n|=========================================================================|\n");
    printf("|                                Update File                              |\n");
    printf("|=========================================================================|\n");
    puts("");

    int bookIndex = -1;

    // Search for the book index based on the title and author provided by the user (case-insensitive)
    for (int loop = 0; loop < bookCount; loop++) {
        if (strcasecmp(books[loop].title, updateTitle) == 0 && strcasecmp(books[loop].author, updateAuthor) == 0) {
            bookIndex = loop;
            break;
        }
    }

    if (bookIndex == -1) {
        printf("Book not found in the library.\n");
        return;
    }

    printf("\nFile contents:\n");

    FILE* file = fopen(books[bookIndex].filename, "r");
    if (file == NULL) {
        printf("Unable to open the file.\n");
        return;
    }

    int c;
    while ((c = fgetc(file)) != EOF) {
        printf("%c", c);
    }

    fclose(file);

    printf("\n-------------------------------------\n");
    printf("| Option |      Description          |\n");
    printf("--------------------------------------\n");
    printf("|   1    |   Update title            |\n");
    printf("|   2    |   Update author           |\n");
    printf("|   3    |   Update publication year |\n");
    printf("|   4    |   Update price            |\n");
    printf("--------------------------------------\n");
    printf("|---------PRESS 0 TO GO BACK---------|\n");
    puts("");

    int kimvej;
    printf("Enter the number you want to update: ");
    scanf("%d", &kimvej);
   
    // Clear the console
    system("cls");

    // Update the selected option
    switch (kimvej) {
    case 0:
    goto back;
        case 1:
            printf("\nEnter new title: ");
            scanf(" %[^\n]", books[bookIndex].title);
            break;
        case 2:
            printf("\nEnter new author: ");
            scanf(" %[^\n]", books[bookIndex].author);
            break;
        case 3:
            printf("\nEnter new year published: ");
            scanf(" %d", &books[bookIndex].year);
            break;
        case 4:
            printf("\nEnter new price: ");
            scanf(" %f", &books[bookIndex].price);
            break;
        default:
            printf("\nInvalid option.\n");
            return;
    }

    // Generate the new filename
    char newFilename[100];
    sprintf(newFilename, "%s-%s.txt", books[bookIndex].title, books[bookIndex].author);
    books[bookIndex].isRenamed = 1;

    // Create a temporary file with updated book information
    FILE* tempFile = fopen("tempfile.txt", "w");
    if (tempFile == NULL) {
        printf("Unable to open the temporary file.\n");
        return;
    }

    // Write updated book information to the temporary file
    fprintf(tempFile, "Title: %s\n", books[bookIndex].title);
    fprintf(tempFile, "Author: %s\n", books[bookIndex].author);
    fprintf(tempFile, "Year Published: %d\n", books[bookIndex].year);
    fprintf(tempFile, "Price: %.2f\n", books[bookIndex].price);
    fclose(tempFile);

    // Remove the old file and rename the temporary file to the new filename
    if (remove(books[bookIndex].filename) != 0) {
        printf("Error removing the old file.\n");
        return;
    }

    if (rename("tempfile.txt", newFilename) != 0) {
        printf("Error renaming the temporary file.\n");
        return;
    }

    // Update the book's filename
    strcpy(books[bookIndex].filename, newFilename);
    printf("\nFile updated successfully.\n");

    // Update the masterlist file
    writeFilenamesToFile();
}

/* Function to read and display the contents of a file
The format should be;
Title:
Author:
Publication Year:
Price:
*/
void readFile() {
    // Clear the console
    system("cls");
    if (bookCount == 0) {
        printf("\nNo files available for reading.\n");
        return;
    }
    // Display the list of available files
    displayFiles();

    printf("\n|=========================================================================|\n");
    printf("|                                Read File                                |\n");
    printf("|=========================================================================|\n");
    puts("");
    printf("Enter the title of the book you want to read: ");
    char readTitle[50];
    scanf(" %[^\n]", readTitle);

    printf("Enter the author of the book you want to read: ");
    char readAuthor[50];
    scanf(" %[^\n]", readAuthor);
   
    system("cls");
printf("\n|=========================================================================|\n");
    printf("|                                Read File                                |\n");
    printf("|=========================================================================|\n");
    puts("");
    int bookIndex = -1;

    // Search for the book index based on the title and author provided by the user (case-insensitive)
    for (int loop = 0; loop < bookCount; loop++) {
        if (strcasecmp(books[loop].title, readTitle) == 0 && strcasecmp(books[loop].author, readAuthor) == 0) {
            bookIndex = loop;
            break;
        }
    }

    if (bookIndex == -1) {
        printf("Book not found in the library.\n");
        return;
    }

    // Open the file in read mode and display its contents
    FILE* file = fopen(books[bookIndex].filename, "r");
    if (file == NULL) {
        printf("Unable to open the file.\n");
        return;
    }

    char line[200];
    while (fgets(line, sizeof(line), file) != NULL) {
        line[strcspn(line, "\n")] = '\0';
        printf("%s\n", line);
    }

    fclose(file);
}


/* Function to remove a file
it will just ask the user for the title and author of the file he/she want to remove
*/
void removeFile() {
    // Clear the console
    system("cls");
    // Display the list of available files
    displayFiles();
   
    if (bookCount == 0) {
        printf("\nNo files available for removal.\n");
        return;
    }

    printf("\n|=========================================================================|\n");
    printf("|                                Remove File                              |\n");
    printf("|=========================================================================|\n");
    puts("");
    printf("Enter the title of the book you want to remove: ");
    char removeTitle[50];
    scanf(" %[^\n]", removeTitle);

    printf("Enter the author of the book you want to remove: ");
    char removeAuthor[50];
    scanf(" %[^\n]", removeAuthor);

    int bookIndex = -1;

    // Search for the book index based on the title and author provided by the user (case-insensitive)
    for (int loop = 0; loop < bookCount; loop++) {
        if (strcasecmp(books[loop].title, removeTitle) == 0 && strcasecmp(books[loop].author, removeAuthor) == 0) {
            bookIndex = loop;
            break;
        }
    }

    if (bookIndex == -1) {
        printf("Book not found in the library.\n");
        return;
    }

    // Ask for confirmation before removing the file
    printf("Are you sure you want to remove this file? (Y/N): ");
    char confirmation;
    scanf(" %c", &confirmation);
    if (confirmation == 'Y' || confirmation == 'y') {
        // Remove the file and update the book list
        if (remove(books[bookIndex].filename) != 0) {
            printf("Error removing the file.\n");
            return;
        }

        for (int loop = bookIndex; loop < bookCount - 1; loop++) {
            books[loop] = books[loop + 1];
        }

        bookCount--;
        printf("\nFile removed successfully.\n");

        // Update the masterlist file
        writeFilenamesToFile();
    } else {
        printf("File removal canceled.\n");
    }

}


/* Function to rename a file
 only the file name will be renamed in this function
 not the contents
*/
void renameFile() {
    // Clear the console
    system("cls");
    // Display the list of available files
    displayFiles();

    if (bookCount == 0) {
        printf("\nNo files available for renaming.\n");
        return;
    }

    printf("\n|=========================================================================|\n");
    printf("|                                Rename File                             |\n");
    printf("|=========================================================================|\n");
    puts("");
    printf("Enter the title of the book you want to rename: ");
    char renameTitle[50];
    scanf(" %[^\n]", renameTitle);

    printf("Enter the author of the book you want to rename: ");
    char renameAuthor[50];
    scanf(" %[^\n]", renameAuthor);

    int bookIndex = -1;

    // Search for the book index based on the title and author provided by the user (case-insensitive)
    for (int loop = 0; loop < bookCount; loop++) {
        if (strcasecmp(books[loop].title, renameTitle) == 0 && strcasecmp(books[loop].author, renameAuthor) == 0) {
            bookIndex = loop;
            break;
        }
    }

    if (bookIndex == -1) {
        printf("Book not found in the library.\n");
        return;
    }

    // Ask for the new filename
    printf("Enter the new filename: ");
    char newFilename[100];
    scanf(" %[^\n]", newFilename);

    // Check if the new filename already exists (case-insensitive)
    for (int loop = 0; loop < bookCount; loop++) {
        if (loop != bookIndex && strcasecmp(books[loop].filename, newFilename) == 0) {
            printf("A file with the new filename already exists. Please choose a different filename.\n");
            return;
        }
    }

    // Get the file extension from the old filename and append it to the new filename
    char originalExtension[10];
    sscanf(books[bookIndex].filename, "%*[^.].%s", originalExtension);
    sprintf(newFilename, "%s.%s", newFilename, originalExtension);

    books[bookIndex].isRenamed = 1;

    // Rename the file
    if (rename(books[bookIndex].filename, newFilename) != 0) {
        printf("Error renaming the file.\n");
        return;
    }

    // Update the book's filename
    strcpy(books[bookIndex].filename, newFilename);
    printf("\nFile renamed successfully.\n");

    // Update the masterlist file
    writeFilenamesToFile();
}

/* Function to display the list of files
This funtion will only display the files that created on this program
*/
void displayFiles() {
    // Clear the console
    system("cls");
    printf("\n|=========================================================================|\n");
    printf("|                                List of Files                            |\n");
    printf("|=========================================================================|\n");
    puts("");

    int numBullets = 0;
   
    printf("------------------------------\n");
    for (int loop = 0; loop < bookCount; loop++) {
        // Check if the file exists and display the book information
        FILE* file = fopen(books[loop].filename, "r");
        if (file != NULL) {
            fclose(file);
           
            printf("%d. %s by %s\n", numBullets + 1, books[loop].title, books[loop].author);
            numBullets++;
           
        }
    }
printf("------------------------------\n");
    if (numBullets == 0) {
        printf("\nNO FILES.\n");
        puts("");
    }
}

// Main function
int main() {
    // Read existing filenames from the masterlist file
    readFilenamesFromFile();

    int choice;
    while (1) {
        // Clear the console
        system("cls");
       
        // Display the menu options
        printf("\n |==========================================|");
        printf("\n |        File Handling Menu:               |");
        printf("\n |==========================================|");
        printf("\n | 1. Create File                           |");
        printf("\n |==========================================|");
        printf("\n | 2. Update File                           |");
        printf("\n |==========================================|");
        printf("\n | 3. Read File                             |");
        printf("\n |==========================================|");
        printf("\n | 4. Remove File                           |");
        printf("\n |==========================================|");
        printf("\n | 5. Rename File                           |");
        printf("\n |==========================================|");
        printf("\n | 6. Display Files                         |");
        printf("\n |==========================================|");
        printf("\n | 7. Exit                                  |");
        printf("\n |==========================================|");
        puts("");
        printf("\n Enter your choice: ");

        // Check if the user's input is a valid integer
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Please enter a valid number.\n");
            // Clear the input buffer to handle invalid inputs
            while (getchar() != '\n');
            continue; // Use 'continue' instead of 'return'
        }

        // Process the user's choice
        switch (choice) {
            case 1:
                createFile();
                break;
            case 2:
                updateFile();
                break;
            case 3:
                readFile();
                break;
            case 4:
                removeFile();
                break;
            case 5:
                renameFile();
                break;
            case 6:
                displayFiles();
                break;
            case 7:
                writeFilenamesToFile();
                printf("\nExiting program...\n");
                system("pause"); // Add system("pause") here to wait for user input before exiting
                exit(0);
            default:
                printf("\nInvalid choice. Please enter the number corresponding to your desired action.\n");
        }

        system("pause"); // Add system("pause") here to wait for user input before showing the menu again
    }

    return 0;
}