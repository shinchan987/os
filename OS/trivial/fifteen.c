// Determine  the  size  of  a  file  using  the  lseekcommand.  
// Once  you  found  out  the  size,  calculate  thenumber of blocks assigned for the file.
// Compare these results with the similar results obtained when using the function stat.


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <file_path>\n", argv[0]);
        exit(1);
    }

    const char *file_path = argv[1];

    // Using lseek to determine the file size
    int fd = open(file_path, O_RDONLY);
    if (fd == -1) {
        perror("open");
        exit(1);
    }

    off_t file_size = lseek(fd, 0, SEEK_END);
    if (file_size == -1) {
        perror("lseek");
        close(fd);
        exit(1);
    }

    close(fd);

    printf("Using lseek:\n");
    printf("File size: %ld bytes\n", (long)file_size);
    printf("Number of blocks: %ld\n", (long)(file_size / 512));  // Assuming a block size of 512 bytes

    // Using stat to get file size
    struct stat file_stat;
    if (stat(file_path, &file_stat) == -1) {
        perror("stat");
        exit(1);
    }

    printf("\nUsing stat:\n");
    printf("File size: %ld bytes\n", (long)file_stat.st_size);
    printf("Number of blocks: %ld\n", (long)(file_stat.st_blocks));

    return 0;
}
