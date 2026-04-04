#include "user.h"


void read_input(void) {

}


void main(void) {
    char hist[10][128];
    int cmd_idx = 0;
    while (1) {
prompt:
        printf("> ");
        char cmdline[128];
        int char_idx = 0;
        int curr_size = 0;
        while (1) {
            char ch = getchar();

            // Checking initial character input
            if (ch == '\r' || ch == '\n') {
                printf("\n");
                cmdline[curr_size] = '\0';
                break;
            }

            // Arrow key
            else if (ch == 0x1b) {
                char temp_ctl = getchar();
                if (temp_ctl == 0x5b) {
                    char temp_dir = getchar();
                    if (temp_dir == 'D') {
                        if (char_idx > 0) {
                            char_idx -= 1;
                            putchar('\b');
                        }
                    }
                    else if (temp_dir == 'C') {
                        if (char_idx < curr_size) {
                            putchar(cmdline[char_idx]);
                            char_idx += 1;
                        }
                    }
                    continue;
                }
            }

            // Backspace / delete
            else if (ch == 0x7f || ch == '\b') {
                if (char_idx > 0) {
                    // Shift buffer left
                    for (int i = char_idx - 1; i < curr_size - 1; i++) {
                        cmdline[i] = cmdline[i + 1];
                    }
                    curr_size--;
                    char_idx--;

                    // Visually update terminal
                    putchar('\b'); // Move cursor back
                    for (int i = char_idx; i < curr_size; i++) {
                        putchar(cmdline[i]); // Print shifted characters
                    }
                    putchar(' '); // Clear the leftover character at the end

                    // Move cursor back to correct position
                    for (int i = curr_size + 1; i > char_idx; i--) {
                        putchar('\b');
                    }
                }
                continue;
            }

            // 4. Handle Standard Character Input
            if (curr_size >= sizeof(cmdline) - 1) {
                printf("\ncommand line too long\n");
                goto prompt;
            }

            if (char_idx == curr_size) {
                // Append mode
                cmdline[char_idx++] = ch;
                curr_size++;
                putchar(ch);
            } 
            else {
                // Shift buffer right
                for (int i = curr_size; i > char_idx; i--) {
                    cmdline[i] = cmdline[i - 1];
                }
                cmdline[char_idx] = ch;
                curr_size++;

                // Visually update terminal
                for (int i = char_idx; i < curr_size; i++) {
                    putchar(cmdline[i]);
                }

                // Move cursor back to correct position
                for (int i = curr_size; i > char_idx + 1; i--) {
                    putchar('\b');
                }
                char_idx++;
            }
        }

        // Debug output to verify command parsing
        printf("\n>>>>%s<<<<\n", cmdline);

        // Command Execution
        if (strcmp(cmdline, "hello") == 0) {
            printf("Hello world from shell!\n");
        }
        else if (strcmp(cmdline, "exit") == 0) {
            exit();
        }
        else if (strcmp(cmdline, "readfile") == 0) {
            char buf[128];
            int len = readfile("hello.txt", buf, sizeof(buf));
            buf[len] = '\0';
            printf("%s\n", buf);
        }
        else if (strcmp(cmdline, "writefile") == 0) {
            writefile("hello.txt", "Hello from shell!\n", 19);
        }
        else if (curr_size > 0) {
            printf("unknown command: >>>>%s<<<<%d>>>>>>\n", cmdline, curr_size);
        }
    }
}



char ** readline(void) {

}