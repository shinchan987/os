// 3.Writeaprogram to:
// a.Createafileb.Readcontentsof afilec.
// Writeto a filed.Linkandunlinka filee.
// Copyfilef.
// Readcontentsof afileina reverseorder


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

// Function to create a file and write data to it
void createAndWriteFile() {
    int file_descriptor = open("example.txt", O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if (file_descriptor == -1) {
        perror("Failed to create file");
        exit(1);
    }

    const char* data = "This is a sample text.\n";
    write(file_descriptor, data, strlen(data));

    close(file_descriptor);
}

// Function to read the contents of a file
void readFile() {
    int file_descriptor = open("example.txt", O_RDONLY);
    if (file_descriptor == -1) {
        perror("Failed to open file for reading");
        exit(1);
    }

    char buffer[100];
    ssize_t bytes_read = read(file_descriptor, buffer, sizeof(buffer));

    printf("File Contents:\n");
    write(STDOUT_FILENO, buffer, bytes_read);

    close(file_descriptor);
}

// Function to link and unlink a file
void linkAndUnlinkFile() {
    if (link("example.txt", "linked_file.txt") == -1) {
        perror("Failed to create a hard link");
        exit(1);
    }

    printf("Hard link created successfully.\n");

    if (unlink("linked_file.txt") == -1) {
        perror("Failed to unlink the file");
        exit(1);
    }

    printf("Hard link unlinked successfully.\n");
}

// Function to copy a file
void copyFile() {
    int source_fd = open("example.txt", O_RDONLY);
    if (source_fd == -1) {
        perror("Failed to open source file");
        exit(1);
    }

    int destination_fd = open("copy.txt", O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if (destination_fd == -1) {
        perror("Failed to create/overwrite destination file");
        exit(1);
    }

    char buffer[1024];
    ssize_t bytes_read;

    while ((bytes_read = read(source_fd, buffer, sizeof(buffer))) > 0) {
        write(destination_fd, buffer, bytes_read);
    }

    close(source_fd);
    close(destination_fd);

    printf("File copied successfully.\n");
}

// Function to read the contents of a file in reverse order
void readInReverse() {
    int file_descriptor = open("example.txt", O_RDONLY);
    if (file_descriptor == -1) {
        perror("Failed to open file for reading");
        exit(1);
    }

    char buffer[100];
    off_t file_size = lseek(file_descriptor, 0, SEEK_END);

    while (file_size > 0) {
        lseek(file_descriptor, --file_size, SEEK_SET);
        ssize_t bytes_read = read(file_descriptor, buffer, 1);
        write(STDOUT_FILENO, buffer, bytes_read);
    }

    close(file_descriptor);
}

int main() {
    createAndWriteFile();
    readFile();
    linkAndUnlinkFile();
    copyFile();
    readInReverse();

    return 0;
}
