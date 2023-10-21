// Inter process communication in Linux using FIFO	

// Writer :-
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
    int fd;
    char *myfifo = "/tmp/myfifo";

    // Create the named pipe (FIFO)
    mkfifo(myfifo, 0666);

    char sentence[80];

    while (1)
    {
        // Open FIFO for writing
        fd = open(myfifo, O_WRONLY);

        // Take input sentence from the user
        printf("Enter a sentence: ");
        fgets(sentence, 80, stdin);

        // Write the sentence to the FIFO
        write(fd, sentence, strlen(sentence) + 1);
        close(fd);

        // Open FIFO for reading
        fd = open(myfifo, O_RDONLY);

        // Read and print the processed data
        char processed_data[256];
        read(fd, processed_data, sizeof(processed_data));
        printf("Processed data: %s\n", processed_data);
        close(fd);
    }

    return 0;
}

// Reader :- 
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
    int fd;
    char *myfifo = "/tmp/myfifo";

    // Create the named pipe (FIFO)
    mkfifo(myfifo, 0666);

    while (1)
    {
        // Open FIFO for reading
        fd = open(myfifo, O_RDONLY);

        // Read the sentence from the FIFO
        char sentence[80];
        read(fd, sentence, sizeof(sentence));
        
        read(fd, sentence, 80);
        // Print the read string and close
        printf("User1: %s\n", sentence);
        close(fd);

        // Process the data (count characters, words, and lines)
        int char_count = 0, word_count = 0, line_count = 0;
        for (int i = 0; sentence[i] != '\0'; i++)
        {
            if(sentence[i] == '\n')
            {
                line_count++;
            }
            else if(sentence[i] == ' ')
            {
                word_count++;
            }
            else
            {
            	char_count++;
            }
            	
        }
        word_count++; // Count the last word

        // Create a string with the counting results
        char counting_result[256];
        snprintf(counting_result, sizeof(counting_result), "Characters: %d, Words: %d, Lines: %d", char_count, word_count, line_count);

        // Write the counting results to a file
        FILE *output_file = fopen("output.txt", "w");
        if (output_file)
        {
            fprintf(output_file, "%s\n", counting_result);
            fclose(output_file);
        }

        // Open FIFO for writing
        fd = open(myfifo, O_WRONLY);

        // Send the counting results back to Process 1
        write(fd, counting_result, strlen(counting_result) + 1);
        close(fd);
    }

    return 0;
}


// OUTPUT >>

// Terminal 1
// pranav@pranav:~/OS/7A$ gcc u1.c
// pranav@pranav:~/OS/7A$ ./a.out
// Enter a sentence: hello world
// Processed data: Characters: 10, Words: 2, Lines: 1
// Enter a sentence: see ya \n lets watch movie
// Processed data: Characters: 21, Words: 6, Lines: 2
// Enter a sentence: 


// Terminal 2
// pranav@pranav:~/OS/7A$ gcc u2.c
// pranav@pranav:~/OS/7A$ ./a.out
// User1: hello world

// User1: see ya \n lets watch movie