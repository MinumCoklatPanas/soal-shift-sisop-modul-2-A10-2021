#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>
#include <time.h>

void pre_ultah(){
  pid_t jeda = fork();
  int statusjeda;
    
  if(jeda<0) exit(EXIT_FAILURE);
    
      if(jeda==0){
          pid_t awal = fork();
          int statusawal;
         
          if(awal<0) exit(EXIT_FAILURE);
         
          if(awal==0){
              char *argv[]={"mkdir","-p",”Musyik”, “Fylm”, “Pyoto”, NULL};
              execv("/usr/bin/mkdir",argv);
          }
          else{
              while((wait(&statusawal)) > 0);
              pid_t child1 = fork();
              int status1;
             
              if(child1<0) exit(EXIT_FAILURE);
             
              if(child1==0){
                  pid_t child2 = fork();
                  int status2;
                 
                  if(child2<0) exit(EXIT_FAILURE);
                 
                  if(child2==0){
                      pid_t child3 = fork();
                      int status3;
                     
                      if(child3<0) exit(EXIT_FAILURE);
                     
                      if(child3==0){// musik
                          pid_t child4 = fork();
                          int status4;
                         
                          if(child4<0) exit(EXIT_FAILURE);
                         
                          if(child4==0){
                                char *argv[] = {"wget","-q","--no-check-certificate",drive[0],"-O",”Musik_for_Stevany.zip”, NULL};
                              execv("/usr/bin/wget",argv);
                          }
                          else{
                              while((wait(&status4)) > 0);
                              char *argv[] = {"unzip", “Musik_for_Stevany.zip”, NULL};
                              execv("/usr/bin/unzip", argv);
                          }
                      }
                      else{// film
                          while((wait(&status3)) > 0);
                          pid_t child5 = fork();
                          int status5;
                         
                          if(child5<0) exit(EXIT_FAILURE);
                         
                          if(child5 == 0){
                              char *argv[] = {"wget","-q","--no-check-certificate",drive[1],"-O",”Film_for_Stevany.zip”, NULL};
                              execv("/usr/bin/wget", argv);
                          }
                          else{
                              while((wait(&status5)) > 0);
                              char *argv[] = {"unzip", “Film_for_Stevany.zip”, NULL};
                              execv("/usr/bin/unzip", argv);
                          }
                      }
                  }
                  else{// foto
                      while((wait(&status2)) > 0);
                      pid_t child6 = fork();
                      int status6;
                     
                      if(child6<0) exit(EXIT_FAILURE);
                     
                      if(child6 == 0){
                          char *argv[] = {"wget","-q","--no-check-certificate",drive[2],"-O",”Foto_for_Stevany.zip”, NULL};
                            execv("/usr/bin/wget", argv);
                      }
                      else{
                          while((wait(&status6)) > 0);
                          char *argv[] = {"unzip", “Foto_for_Stevany.zip”, NULL};
                          execv("/usr/bin/unzip", argv);
                      }
                  }
                }
                else{
                    while((wait(&status1)) > 0);
                    pid_t child7 = fork();
                    int status7;
                     
                    if(child7<0) exit(EXIT_FAILURE);
                     
                    if(child7==0){
                        pid_t child8 = fork();
                        int status8;
                         
                        if(child8<0) exit(EXIT_FAILURE);
                         
                      if(child8==0){//mindah musik
                          char *argv[] = {"find", "/home/velli/modul2/MUSIK", "-type","f","-exec","mv","{}","/home/velli/modul2/Musyik",";", NULL};
                          execv("/usr/bin/find", argv);
                      }
                      else{//mindah film
                          while((wait(&status8)) > 0);
                          char *argv[] = {"find", "/home/velli/modul2/FILM", "-type","f","-exec","mv","{}","/home/velli/modul2/Fylm",";", NULL};
                          execv("/usr/bin/find", argv);
                      }
                  }
                  else{//mindah foto
                      while((wait(&status7)) > 0);
                      char *argv[] = {"find","/home/velli/modul2/FOTO","-type","f","-exec","mv","{}","/home/velli/modul2/Pyoto",";", NULL};
                      execv("/usr/bin/find", argv);
                  }
              }
          }//punyaelseawal
      }//punyajeda
      else{
          while((wait(&statusjeda)) > 0);
          return;
      }
}

void ultah(){
  pid_t lili = fork();
  int statuslili;
    
  if(lili<0) exit(EXIT_FAILURE);
    
  if(lili==0){
      pid_t child9 = fork();
          int status9;
         
          if(child9<0) exit(EXIT_FAILURE);

          if(child9==0){//ngezip
              char *argv[]={"zip","-mr","/home/velli/modul2/Lopyu_Stevany",”Musyik”, “Fylm”, “Pyoto”, NULL};
                execv("/usr/bin/zip",argv);
          }
          else{//buang folder kosong
              while((wait(&status9)) > 0);
              char *argv[]={"rm","-r",”MUSIK”, “FILM”, “FOTO”, NULL};
              execv("/usr/bin/rm",argv);
          }   
  }
  else{
      while((wait(&statuslili)) > 0);
      return;
  }
}

int main() {
  pid_t pid, sid;        // Variabel untuk menyimpan PID

  pid = fork();     // Menyimpan PID dari Child Process

  /* Keluar saat fork gagal
  * (nilai variabel pid < 0) */
  if (pid < 0) {
    exit(EXIT_FAILURE);
  }

  /* Keluar saat fork berhasil
  * (nilai variabel pid adalah PID dari child process) */
  if (pid > 0) {
    exit(EXIT_SUCCESS);
  }

  umask(0);

  sid = setsid();
  if (sid < 0) {
    exit(EXIT_FAILURE);
  }

  if ((chdir("/")) < 0) {
    exit(EXIT_FAILURE);
  }

  close(STDIN_FILENO);
  close(STDOUT_FILENO);
  close(STDERR_FILENO);

  while (1) {
    //  program akan ditulis disini 

      time_t waktu;
        struct tm* tm_skrg;

        waktu = time(NULL);
        tm_skrg = localtime(&waktu);
       
        if(tm_skrg->tm_mon==3 && tm_skrg->tm_mday==9 && tm_skrg->tm_hour==16 && tm_skrg->tm_min==22 && tm_skrg->tm_sec==0){
          pre_ultah();
      }
      else if(tm_skrg->tm_mon==3 && tm_skrg->tm_mday==9 && tm_skrg->tm_hour==22 && tm_skrg->tm_min==22 && tm_skrg->tm_sec==0){
          ultah();           
      }
  }sleep(1);
}
