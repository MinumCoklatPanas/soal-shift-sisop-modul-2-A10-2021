#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h>

void buat(int child_id){
  child_id = fork();

  if (child_id < 0) {
    exit(EXIT_FAILURE); 
  }

  if (child_id == 0) {

    char *argv[] = {"mkdir", "-p", "/home/arsyad/modul2/petshop", NULL};
    execv("/bin/mkdir", argv);

  } else {
    char *argv[] = {"unzip", "/home/arsyad/modul2/pets.zip", "-d","/home/arsyad/modul2/petshop", "*.jpg",NULL};
    execv("/bin/unzip", argv);
  }
}

void listFilesRecursively(char *basePath)
{
    char path[1000];
    struct dirent *dp;
    DIR *dir = opendir(basePath);

    if (!dir)
        return;

    while ((dp = readdir(dir)) != NULL)
    {
        if (strcmp(dp->d_name, ".") != 0 && strcmp(dp->d_name, "..") != 0)
        {
            char newname[100] = "";
            strcpy(newname, dp->d_name);
            char filebaru[100] = "/home/arsyad/modul2/petshop/";
          	strtok(newname, ";");
          	strcat(filebaru, newname);
          	char *argv[] = {"mkdir","-p", "/home/arsyad/modul2/petshop/", NULL};
          	execv("/bin/mkdir", argv);
          
            strcpy(path, basePath);
            strcat(path, "/");
            strcat(path, dp->d_name);

            listFilesRecursively(path);
        }
    }

    closedir(dir);
}

int main() {
  pid_t child_id;
  char loc[] = "/home/zoniacer/modul2/petshop";

  buat(child_id);
  listFilesRecursively(loc);
}






