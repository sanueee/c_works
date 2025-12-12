#include <stdio.h>
#include <dirent.h>

int main(int argc, char **argv) {
    const char* path_dir = &argv[0][1];
    int count = 0;

}

void count_files(const char *path_dir, int *count) {
    DIR* dir = opendir(path_dir);
    if (dir == NULL) {
        printf("не директория");
        return;
    }

    struct dirent* entry;
    while ((entry = readdir()) != NULL) {

        char fullPath[1024];
        snprintf(fullPath, sizeof(fullPath), "%s/%s", path_dir, entry->d_name);

        if (entry->d_type == DT_DIR) {
            count_files(fullPath, &count);
        }
    }
}