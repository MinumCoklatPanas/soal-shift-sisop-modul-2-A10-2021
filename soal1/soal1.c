#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <time.h>

char *music[] = {"https://drive.google.com/uc?id=1ZG8nRBRPquhYXq_sISdsVcXx5VdEgi-J&export=download","Musik_for_Stevany.zip","Musyik","MUSIK"};
char *film[] = {"https://drive.google.com/uc?id=1ktjGgDkL0nNpY-vT7rT7O6ZI47Ke9xcp&export=download","Film_for_Stevany.zip"," Fylm","FILM"};
char *fotoo [] = {"https://drive.google.com/uc?id=1FsrAzb9B5ixooGUs0dGiBr-rC7TS9wTD&export=download","Foto_for_Stefany.zip","Pyoto","FOTO"};
    
const char * getSystemTime()
{
    struct timeval tp;
    struct tm *t;
    char *current_time;
    time_t curtime;    
    
    //gettimeofday(&tp, 0); //Pass tp to library function gettimeofday()
    curtime = tp.tv_sec;
    t = localtime(&curtime);
    
    current_time = (char *) malloc(sizeof(char) * 18);
    sprintf(current_time,"%02d:%02d:%02d:%04ld", 
                         t->tm_hour, t->tm_min, t->tm_sec, tp.tv_usec/1000);
    return current_time;
}

void pre_ultah(){
    pid_t start = fork();
    int statusstart;
    
    if(start<0) exit(EXIT_FAILURE);
    
        if(start==0){
            pid_t awal = fork();
            int statusawal;
         
            if(awal<0) exit(EXIT_FAILURE);
         
            if(awal==0){
                char *argv[]={"mkdir","-p",music[2], film[2], fotoo[2], NULL};
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
                                char *argv[] = {"wget","-q","--no-check-certificate",music[0],"-O",music[1], NULL};
                                execv("/usr/bin/wget",argv);
                            }
                            else{
                                while((wait(&status4)) > 0);
                                char *argv[] = {"unzip", music[1], NULL};
                                execv("/usr/bin/unzip", argv);
                            }
                        }
                        else{// film
                            while((wait(&status3)) > 0);
                            pid_t child5 = fork();
                            int status5;
                         
                            if(child5<0) exit(EXIT_FAILURE);
                         
                            if(child5 == 0){
                                char *argv[] = {"wget","-q","--no-check-certificate",film[0],"-O",film[1], NULL};
                                execv("/usr/bin/wget", argv);
                            }
                            else{
                                while((wait(&status5)) > 0);
                                char *argv[] = {"unzip", film[1], NULL};
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
                            char *argv[] = {"wget","-q","--no-check-certificate",fotoo[0],"-O",fotoo[1], NULL};
                            execv("/usr/bin/wget", argv);
                        }
                        else{
                            while((wait(&status6)) > 0);
                            char *argv[] = {"unzip", fotoo[1], NULL};
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
                         
                        if(child8==0){//move musik
                            char *argv[] = {"find", "/home/velli/modul2/MUSIK", "-type","f","-exec","mv","{}","/home/velli/modul2/Musyik",";", NULL};
                            execv("/usr/bin/find", argv);
                        }
                        else{//move film
                            while((wait(&status8)) > 0);
                            char *argv[] = {"find", "/home/velli/modul2/FILM", "-type","f","-exec","mv","{}","/home/velli/modul2/Fylm",";", NULL};
                            execv("/usr/bin/find", argv);
                        }
                    }
                    else{//move foto
                        while((wait(&status7)) > 0);
                        char *argv[] = {"find","/home/velli/modul2/FOTO","-type","f","-exec","mv","{}","/home/velli/modul2/Pyoto",";", NULL};
                        execv("/usr/bin/find", argv);
                    }
                }
            }
        }
        else{
            while((wait(&statusstart)) > 0);
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
                char *argv[]={"zip","-mr","/home/velli/modul2/Lopyu_Stevany",music[2], film[2], fotoo[2], NULL};
                execv("/usr/bin/zip",argv);
            }
            else{// delete empty folder
                while((wait(&status9)) > 0);
                char *argv[]={"rm","-r",music[3], film[3], fotoo[3], NULL};
                execv("/usr/bin/rm",argv);
            }   
    }
    else{
        while((wait(&statuslili)) > 0);
        return;
    }
}

int main() {
    pid_t pid, sid;   // Variabel untuk menyimpan PID
    pid = fork();   // Menyimpan PID dari Child Process
    
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
    
    while(1){
        time_t waktu;
        struct tm* tm_now;

        waktu = time(NULL);
        tm_now = localtime(&waktu);
         
        if(tm_now->tm_mon==3 && tm_now->tm_mday==9 && tm_now->tm_hour==16 && tm_now->tm_min==22 && tm_now->tm_sec==0){
            pre_ultah();
        }
        else if(tm_now->tm_mon==3 && tm_now->tm_mday==9 && tm_now->tm_hour==22 && tm_now->tm_min==22 && tm_now->tm_sec==0){
            ultah();           
        }
    }sleep(1);
}
