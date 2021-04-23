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

void soal2bcde()
{
    char basePath[] = "/home/arsyad/modul2/petshop/";
    
    struct dirent *dp;
    DIR *dir = opendir(basePath);

    if (!dir)
        return;

    while ((dp = readdir(dir)) != NULL)
    {
        if (strcmp(dp->d_name, ".") != 0 && strcmp(dp->d_name, "..") != 0)
        {
            char loc[] = "/home/arsyad/modul2/petshop/";
            char newname[100] = "";
            strcpy(newname, dp->d_name);
            char pettype[50], petname[50], petage[50];
            char *sign1 = strtok(newname,"_;");
            int word = 0;
            while(sign1 != NULL) {
                  if(word==0){ 
                    strcpy(pettype, sign1);
                    char temp[100]="";
                    strcpy(temp, loc);
                    strcat(temp, pettype);
                    char *argv[] = {"mkdir", "-p", temp, NULL};
                    run("/bin/mkdir", argv);
                  }
                  if(word==1){ 
                    strcpy(petname, sign1); 
                    
                    char dirmv[100] = "";
                    strcpy(dirmv,loc);
                    strcat(dirmv,dp->d_name);

                    char source[100] = "";
                    strcpy(source,loc);
                    strcat(source,pettype);
                    strcat(source,"/");
                    strcat(source,petname);
                    strcat(source,".jpg");

                    char *argv1[] = {"mv", dirmv, source, NULL};
                    run("/bin/mv", argv1);
                  }
                  if(word==2){ 
                    strcpy(petage, sign1); 
                    char sourcefile[100] = "";
                    strcat(sourcefile, loc);
                    strcat(sourcefile, pettype);
                    strcat(sourcefile, "/keterangan.txt");

                    FILE *fp;
                    fp = fopen (sourcefile, "a");
                    fprintf(fp, "nama: %s\numur: %s tahun\n\n", petname, petage);
                    fclose(fp);
                  }
              sign1 = strtok(NULL, "_;");
              word++;
              }
            
        }
    }
    closedir(dir);
}

int main() {
  char loc[] = "/home/arsyad/modul2/petshop";
  buat();
  soal2bcde();
  return 0;
}
