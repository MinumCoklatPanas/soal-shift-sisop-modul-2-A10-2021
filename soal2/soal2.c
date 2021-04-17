#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h>
#include <wait.h>

void run(char command[], char *arg[]){
	pid_t child_id;
  int status;
	child_id = fork();

	if(child_id == 0){
		execv(command, arg);
	}
	else{
		((wait(&status))>0);
	}
}

void buat(){
  char *argv0[] = {"mkdir", "-p", "/home/arsyad/modul2/petshop", NULL};
  run("/bin/mkdir", argv0);

  char *argv1[] = {"unzip", "/home/arsyad/modul2/pets.zip", "-d","/home/arsyad/modul2/petshop", "*.jpg",NULL};
  run("/bin/unzip", argv1);
}

void soal2b(char *basePath)
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
          	strtok(newname, ";");
            char sourcefile[100] = "/home/arsyad/modul2/petshop/";
            strcat(sourcefile, newname);
            char dirmv[100] = "/home/arsyad/modul2/petshop/";
            strcat(dirmv, dp->d_name);
            char namafile[100] = "";
            strcpy(namafile, dp->d_name);
            
            char *argv[] = {"mkdir","-p", sourcefile, NULL};
          	run("/bin/mkdir", argv);

            if (!(strstr(dp->d_name, "_"))){
              char *argv[] = {"mv","-f", dirmv, sourcefile ,NULL};
          	  run("/bin/mv", argv);
            }
        }
    }
    closedir(dir);
}

int main() {
  char loc[] = "/home/arsyad/modul2/petshop";
  buat();
  soal2b(loc);
}






