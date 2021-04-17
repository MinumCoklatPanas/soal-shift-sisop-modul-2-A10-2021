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
#include <dirent.h>

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

void execute(char *arg[],char path[])
{
    pid_t pid;
    int status;
    pid = fork();
    if (pid == 0)
    {
        execv(path,arg);
    }
    while (wait(&status) > 0);
    return;
}

void makeFolder(char name[])
{
    char* argv[] = {"mkdir",name,NULL};
    char path[] = "/bin/mkdir";
    execute(argv,path);
}

void unzip()
{
    char* argv[] = {"unzip","/home/pan/sisop/soal-shift-sisop-modul-2-A10-2021/tmp.zip",NULL};
    char path[] = "/usr/bin/unzip";
    execute(argv,path);
}
void download(char url[])
{
    char* argv[] = {"wget","--no-check-certificate",url,"-O","tmp.zip",NULL};
    char path[] = "/usr/bin/wget";
    execute(argv,path);
    // unzip();
    // execl("/usr/bin/wget","wget",url,NULL);
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

void moveFile(char sourcePath[],char destPath[])
{
    char* argv[] = {"mv",sourcePath,destPath,NULL};
    char path[] = "/bin/mv";
    execute(argv,path);
}

void listFilesRecursively(char *basePath,char nama[])
{
    char path[1010];
    struct dirent *dp;
    DIR *dir = opendir(basePath);

    if (!dir)
        return;

    while ((dp = readdir(dir)) != NULL)
    {
        if (strcmp(dp->d_name, ".") != 0 && strcmp(dp->d_name, "..") != 0)
        {
            // printf("%s\n", dp->d_name);


            // Construct new path from our base path
            strcpy(path, basePath);
            strcat(path, "/");
            strcat(path, dp->d_name);

            char destPath[1010];
            strcpy(destPath,"/home/pan/sisop/soal-shift-sisop-modul-2-A10-2021/");
            strcat(destPath,nama);

            moveFile(path,destPath);

            listFilesRecursively(path,nama);
        }
    }

    closedir(dir);
}


void deleteZip()
{
    char* argv[] = {"rm","tmp.zip",NULL};
    char path[] = "/bin/rm";
    execute(argv,path);
}

void deleteFolder(char nama[])
{
    char* argv[] = {"rm","-r",nama,NULL};
    char path[] = "/bin/rm";
    execute(argv,path);
}

void downloadAndExtract(char url[],char dirName[],char namaBawaan[])
{
    makeFolder(dirName);
    download(url);
    unzip();
    deleteZip();
    char initPath[1010];
    strcpy(initPath,"/home/pan/sisop/soal-shift-sisop-modul-2-A10-2021/");
    strcat(initPath,namaBawaan);
    listFilesRecursively(initPath,dirName);
    deleteFolder(namaBawaan);
}

int main()
{
    // initDaemon();
    
    while (1)
    {
        time_t timer;
        char buffer[35];
        struct tm* tm_info;

        timer = time(NULL);
        tm_info = localtime(&timer);
        strftime(buffer,35,"%m-%d_%H:%M",tm_info);
        printf("%s\n",buffer);
        if (strcmp(buffer,"04-09_16:22") == 0)
        {
            downloadAndExtract("https://drive.google.com/uc?id=1ZG8nRBRPquhYXq_sISdsVcXx5VdEgi-J&export=download","Musyik","MUSIK");
            downloadAndExtract("https://drive.google.com/uc?id=1FsrAzb9B5ixooGUs0dGiBr-rC7TS9wTD&export=download","Fyoto","FOTO");
            downloadAndExtract("https://drive.google.com/uc?id=1ktjGgDkL0nNpY-vT7rT7O6ZI47Ke9xcp&export=download","Fylm","FILM");
        }
        if (strcmp(buffer,"04-09_22:22") == 0)
        {
            char* arg[] = {"zip","-r","Lopyu_Stevany.zip","Musyik","Fyoto","Fylm",NULL};
            char path[] = "/usr/bin/zip";
            execute(arg,path);
        }
        sleep(1000);
        // break;
    }
}