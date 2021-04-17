#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <wait.h>

void initDaemon()
{
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

  if ((chdir("/home/pan/sisop/soal-shift-sisop-modul-2-A10-2021")) < 0) {
    exit(EXIT_FAILURE);
  }

  close(STDIN_FILENO);
  close(STDOUT_FILENO);
  close(STDERR_FILENO);

  // while (1) {
  //   // Tulis program kalian di sini
  //   int a = system("mkdir `date`");
  //   sleep(10);
  // }
}

char dirName[35];

void makeFolder()
{
    time_t timer;
    char buffer[35];
    struct tm* tm_info;

    timer = time(NULL);
    tm_info = localtime(&timer);
    strftime(buffer,35,"%Y-%m-%d_%H:%M:S",tm_info);

    printf("%s",buffer);

    pid_t pid;
    int status;
    pid = fork();

    if (pid == 0)
    {
        char *mkdir[] = {"mkdir",buffer,NULL};
        execv("/bin/mkdir",mkdir);
    }
    while (wait(&status) > 0);
    chdir(buffer);
    strcpy(dirName,buffer);
}

void downloadPics()
{
    time_t timer;
    char buffer[35];
    struct tm* tm_info;

    timer = time(NULL);
    tm_info = localtime(&timer);
    strftime(buffer,35,"%Y-%m-%d_%H:%M:%S",tm_info);
    // printf("%s",buffer);
    // puts("yo");
    // return;
    int sz = (timer % 1000) + 50;
    char url[] = "https://picsum.photos/";
    char tmp[55];
    sprintf(tmp,"%d",sz);
    strcat(url,tmp);
    printf("%s\n",url);
    pid_t pid;
    int status;
    pid = fork();
    if (pid == 0)
    {
        char *arg[] = {"wget",url,"-O",buffer,NULL};
        execv("/usr/bin/wget",arg);
    }
    while (wait(&status) > 0);
    return;
}

void normalize(int* x)
{
    // int &a = *x;
    *x += 5;
    if (*x >= 26) *x %= 26;
}

void writeStatus()
{
    // FILE* f;
    char status[] = "Download Success";
    for (int i = 0 ; i < 16 ; i++)
    {
        if (status[i] == ' ') continue;
        char pivot = ('A' <= status[i] && status[i] <= 'Z' ? 'A' : 'a');
        int ix = status[i] - pivot;
        normalize(&ix);
        status[i] = pivot + ix;
    }
    int sts;
    pid_t pid;
    pid = fork();
    if (pid == 0)
    {
        char* arg[] = {"touch","status.txt",NULL};
        execv("/bin/touch",arg);
    }
    else
    {
        while ((wait(&sts)) > 0);
        char* arg2[] = {"printf",status,">>","status.txt",NULL};
        execvp(arg2[0],arg2);
    }
    // fopen("status.txt","w");
    // fprintf(f,"%s",status);
    // fclose(f);
}

void zipFile()
{
    pid_t pid;
    int status;
    pid = fork();
    if (pid == 0)
    {
        char* arg[] = {"zip","-r","z.zip",dirName,NULL};
        execv("/usr/bin/zip",arg);
    }
    while (wait(&status) > 0);
    return;
}

int main(int argc, char* argv[]) 
{
    // bool KILL_MODE = (argv[1][1] == 'x');
    int status;

    FILE * f;
    f = fopen("killer.sh","w");
    // perror("fopen");
    // fflush(f);
    fprintf(f,"kill %d\nrm \"$0\"",getpid());
    // fprintf(f,"\n");
    // fflush(f);
    fclose(f);
    fflush(0);

    pid_t child_id;
    child_id = fork();
    if (child_id == 0)
    {
      char *ag[] = {"chmod", "u+x", "killer.sh", NULL};
      execv("/bin/chmod", ag);
    }
    while ((wait(&status)) > 0);

    initDaemon();

    if (argv[1][1] == 'z') return 0;

    while (1)
    {
        makeFolder();

        int i,status2;
        for (i = 1 ; i <= 10 ; i++)
        {
            downloadPics();
            sleep(5);
        }
        // while (wait(&status2) > 0);
        chdir("..");
        zipFile();
        sleep(40);
    }
    
}