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


char detail[100]="";
void listFilesRecursively(char *basePath)
{
    char path[1000];
    struct dirent *dp;
    DIR *dir = opendir(basePath);
    FILE *file;

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
              
              
              //strcpy(detail,newname);
        	  	//strcat(detail,"/keterangan.txt");
        	  	//file = fopen(detail,"a");
              char changename[100] = "";
              char usedname[100] = "";
        	  	strcpy(changename,newname);
        	  	strcat(changename,"/");

              int cnt = 0;
              char sign1[1] = ";";
              char sign2[2] = ".j";
        	  	for(int x=0; x<35; x++){
        	  		if(cnt == 0){
        	  			if(namafile[x] == sign1[0]){
        	  				cnt++;
                    //fprintf(file,"nama : ");
                    //fprintf(file,"\n");
        	  			}
        	  			continue;
        	  		}
        	  		if(cnt == 1){
        	  			if(namafile[x]== sign1[0]){
        	  				cnt++;
                    //fprintf(file,"umur : ");
                    //fprintf(file,"\n");
        	  			}
                  //fprintf(file,"%c", namafile[x]);
        	  			strncat(usedname,&namafile[x],1);
        	  			//continue;
                  break;
        	  		}
                //if(namafile[x]==sign2[0] && namafile[x+1]==sign2[1]){
        	  			//fprintf(file, " tahun ");
                  //fprintf(file,"\n\n");
        	  			//break;	
        	  		//}
        	  	//	fprintf(file, "%c", namafile[x]);
              }
              strcat(changename,usedname);
        	  	strcat(changename,".jpg");
        	  	strcat(newname,"/");
        	  	strcat(newname, dp->d_name);
        	  	char *argv10[] = {"mv",newname,changename,NULL};
        	  	run("/bin/mv", argv10); 
            
            }
      strcpy(path, basePath);
      strcat(path, "/");
      strcat(path, dp->d_name);

      listFilesRecursively(path);
    }
  }
  closedir(dir);
}

int main() {
  char loc[] = "/home/arsyad/modul2/petshop";

  buat();
  listFilesRecursively(loc);
}






