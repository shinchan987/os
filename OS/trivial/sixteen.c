#include <stdio.h>
#include <dirent.h>


// ls
int main() {
    DIR *dir;
    struct dirent *entry;

    dir = opendir("."); // Open the current directory
    if (dir == NULL) {
        perror("opendir");
        return 1;
    }

    while ((entry = readdir(dir)) != NULL) {
        printf("%s\n", entry->d_name);
    }

    closedir(dir);
    return 0;
}


#include <stdio.h>
#include <string.h>


// grep
int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s <pattern> <file>\n", argv[0]);
        return 1;
    }

    const char *pattern = argv[1];
    const char *file_path = argv[2];

    FILE *file = fopen(file_path, "r");
    if (file == NULL) {
        perror("fopen");
        return 1;
    }

    char line[1024];
    while (fgets(line, sizeof(line), file)) {
        if (strstr(line, pattern)) {
            printf("%s", line);
        }
    }

    fclose(file);
    return 0;
}
