// Write  a  program  to  change  current  working  directory 
//  and  display  the  inode  details  for  each  file  in 
//  the newdirectoryusingthesystem calls: 
//  opendir(), readdir(),closedir(),getcwd(),chdir( ).


#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int main() {
    const char* new_directory = "/path/to/your/new/directory"; // Change this to the desired directory path

    // Change the current working directory
    if (chdir(new_directory) == -1) {
        perror("chdir() failed");
        exit(1);
    }

    // Get the current working directory
    char current_directory[1024];
    if (getcwd(current_directory, sizeof(current_directory) - 1) == NULL) {
        perror("getcwd() failed");
        exit(1);
    }

    printf("Current working directory: %s\n\n", current_directory);

    // Open the current directory
    DIR* dir = opendir(current_directory);
    if (dir == NULL) {
        perror("opendir() failed");
        exit(1);
    }

    // Read and display the inode details for each file in the directory
    struct dirent* entry;
    struct stat file_stat;

    while ((entry = readdir(dir)) != NULL) {
        if (stat(entry->d_name, &file_stat) == 0) {
            printf("File: %s\n", entry->d_name);
            printf("Inode: %lu\n", (unsigned long)file_stat.st_ino);
            printf("File Size: %ld bytes\n\n", (long)file_stat.st_size);
        }
    }

    // Close the directory
    closedir(dir);

    return 0;
}
