# soal-shift-sisop-modul-2-A10-2021

## Soal 2

Loba bekerja di sebuah petshop terkenal, suatu hari dia mendapatkan zip yang berisi banyak foto peliharaan dan ia diperintahkan untuk mengkategorikan foto-foto peliharaan tersebut. Loba merasa kesusahan melakukan pekerjaanna secara manual, apalagi ada kemungkinan ia akan diperintahkan untuk melakukan hal yang sama. Kamu adalah teman baik Loba dan ia meminta bantuanmu untuk membantu pekerjaannya.

#### Solusi

Perintah fork dan execv dijadikan dalam satu fungsi bernama "Run" sehingga lebih memudahkan dalam penulisan code

```c
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
```

##### A. Mengextract zip ke dalam folder "/home/[user]/modul2/petshop". Program harus bisa membedakan file dan folder sehingga dapat memproses file yang dibutuhkan dan menghapus folder yang tidak dibutuhkan.
- Membuat folder baru dalam direktori "/home/[user]/modul2/" yang diberi nama "petshop" menggunakan perintah ```mkdir```.
- Filtering file dan folder menggunakan perintah ```unzip```. Apabila file berekstensi .jpg di extract dan selain itu tidak.

```c
void buat(){
  char *argv0[] = {"mkdir", "-p", "/home/arsyad/modul2/petshop", NULL};
  run("/bin/mkdir", argv0);

  char *argv1[] = {"unzip", "/home/arsyad/modul2/pets.zip", "-d","/home/arsyad/modul2/petshop", "*.jpg",NULL};
  run("/bin/unzip", argv1);
}
```

Output:

![Output1](https://user-images.githubusercontent.com/73766214/115992978-9e3ae900-a5fa-11eb-9d76-d5a5a7fa5464.png)

##### B. Mengkategorikan foto peliharaan sesuai jenis peliharaan dengan membuat folder untuk setiap jenis peliharaan.
- Menggunakan operasi-operasi dasar dari string untuk memproses nama file.
- Memisahkan kata setiap kata pada nama file yang dibatasi oleh karakter ```;```.
- Kata pertama pada nama file adalah jenis peliharaan, lalu melakukan looping hingga file terakhir dan membuat folder baru sesuai jenis peliharaan tersebut menggunakan perintah ```mkdir```.

```c
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
      sign1 = strtok(NULL, "_;");
      word++;
}
```

Output:

![Hasil1](https://user-images.githubusercontent.com/73766214/115993002-d17d7800-a5fa-11eb-808c-eca2a3d40c1c.png)

##### C. Memindahkan foto ke folder dengan kategori sesuai dan di rename dengan nama peliharaan.
- Menggunakan operasi-operasi dasar dari string untuk memproses nama file.
- Memisahkan kata setiap kata pada nama file yang dibatasi oleh karakter ```;```.
- Kata kedua pada nama file adalah nama peliharaan dan disimpan pada variabel petname, lalu memproses path direktori dengan menambahkan "/[petname].jpg" dari direktori asli menggunakan perintah ```strcat```.
- Memindahkan file ke folder sesuai dengan jenis pelihaaran menggunakan peintah ```mv```.

```c
char loc[] = "/home/arsyad/modul2/petshop/";
char newname[100] = "";
strcpy(newname, dp->d_name);
char pettype[50], petname[50], petage[50];
char *sign1 = strtok(newname,"_;");
int word = 0;
while(sign1 != NULL) {
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
      sign1 = strtok(NULL, "_;");
      word++;
}
```

Output:

![Hasil2](https://user-images.githubusercontent.com/73766214/115993019-e3f7b180-a5fa-11eb-98f6-66ac5582dd25.png)

##### D. Dalam satu foto bisa terdapat lebih dari satu peliharaan maka foto harus dipindah ke masing-masing kategori yang sesuai.
- Menggunakan operasi-operasi dasar dari string untuk memproses nama file.
- Memisahkan antara satu peliharaan dan peliharaan yang lain yang dibatasi oleh ```_```.
- Memisahkan kata setiap kata pada nama file yang dibatasi oleh karakter ```;```.
- Memindahkan foto sesuai dengan jenis peliharaan dan nama file direname menjadi nama peliharaan tersebut.

Output:

![Hasil2](https://user-images.githubusercontent.com/73766214/115993027-f2de6400-a5fa-11eb-8434-a2df36be966e.png)
![Output2](https://user-images.githubusercontent.com/73766214/115993047-0e496f00-a5fb-11eb-883f-ec39a546d02c.png)

##### E. Membuat file "keterangan.txt" di setiap folder yang berisi nama dan umur semua peliharaan dalam folder tersebut. 
- Menggunakan operasi-operasi dasar dari string untuk memproses nama file.
- Memisahkan kata setiap kata pada nama file yang dibatasi oleh karakter ```;```.
- Kata ketiga adalah umur peliharaan dan disimpan pada variabel petage.
- Membuat file dengan menambah "/keterangan.txt" pada direktori asli.
- Mengakses file dan memasukkan data nama dan umur melalui variabel petname dan petage.

```c
char loc[] = "/home/arsyad/modul2/petshop/";
char newname[100] = "";
strcpy(newname, dp->d_name);
char pettype[50], petname[50], petage[50];
char *sign1 = strtok(newname,"_;");
int word = 0;
while(sign1 != NULL) {
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
```
Output:

![Hasil2](https://user-images.githubusercontent.com/73766214/115993061-27522000-a5fb-11eb-8039-1eaa41f68e0b.png)
![Hasil3](https://user-images.githubusercontent.com/73766214/115993066-3a64f000-a5fb-11eb-941a-b36db1c2a22e.png)

#### Kendala
- Susah untuk memproses string yang ada pada file keterangan.txt


## Soal 3

Ranora adalah mahasiswa Teknik Informatika yang saat ini sedang menjalani magang di perusahan ternama yang bernama “FakeKos Corp.”, perusahaan yang bergerak dibidang keamanan data. Karena Ranora masih magang, maka beban tugasnya tidak sebesar beban tugas pekerja tetap perusahaan. Di hari pertama Ranora bekerja, pembimbing magang Ranora memberi tugas pertamanya untuk membuat sebuah program.hkan

#### Solusi


##### A. Ranora harus membuat sebuah program C yang dimana setiap 40 detik membuat sebuah direktori dengan nama sesuai timestamp [YYYY-mm-dd_HH:ii:ss].
- Menggunakan operasi-operasi dasar dari string untuk memproses direktori file.
- Menambah library ```#include <time.h>``` agar bisa mengakses waktu hari ini.
- Set waktu 40 detik untuk membuat sebuah direktori

```c
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
```

Output:



##### B. Setiap direktori yang sudah dibuat diisi dengan 10 gambar yang didownload dari https://picsum.photos/, dimana setiap gambar akan didownload setiap 5 detik. Setiap gambar yang didownload akan diberi nama dengan format timestamp [YYYY-mm-dd_HH:ii:ss] dan gambar tersebut berbentuk persegi dengan ukuran (n%1000) + 50 pixel dimana n adalah detik Epoch Unix.
- Mengunduh gambar menggunakan perintah ```wget```
- Mengatur ukuran gambar dengan memproses url gambar

```c
for (i = 1 ; i <= 10 ; i++){
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
    sleep(5);
}
```

Output:



##### C. Setelah direktori telah terisi dengan 10 gambar, program tersebut akan membuat sebuah file “status.txt”, dimana didalamnya berisi pesan “Download Success” yang terenkripsi dengan teknik Caesar Cipher dan dengan shift 5. Caesar Cipher adalah Teknik enkripsi sederhana yang dimana dapat melakukan enkripsi string sesuai dengan shift/key yang kita tentukan. Misal huruf “A” akan dienkripsi dengan shift 4 maka akan menjadi “E”. Karena Ranora orangnya perfeksionis dan rapi, dia ingin setelah file tersebut dibuat, direktori akan di zip dan direktori akan didelete, sehingga menyisakan hanya file zip saja.
- Membuat file "status.txt" menggunakan perintah ```touch```
- Write file status.txt dengan status yang telah dienkripsi dengan caesar cipher

```c
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
```

Output:



##### D. Untuk mempermudah pengendalian program, pembimbing magang Ranora ingin program tersebut akan men-generate sebuah program “Killer” yang executable, dimana program tersebut akan menterminasi semua proses program yang sedang berjalan dan akan menghapus dirinya sendiri setelah program dijalankan. Karena Ranora menyukai sesuatu hal yang baru, maka Ranora memiliki ide untuk program “Killer” yang dibuat nantinya harus merupakan program bash.
- Mengakses file killer.sh yang telah dibuat
- Membuat program killer meng-kill proses dengan perintah ```getpid()```

```c
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
```

Output:



##### E. Pembimbing magang Ranora juga ingin nantinya program utama yang dibuat Ranora dapat dijalankan di dalam dua mode. Untuk mengaktifkan mode pertama, program harus dijalankan dsdengan argumen -z, dan Ketika dijalankan dalam mode pertama, program utama akan langsung menghentikan semua operasinya Ketika program Killer dijalankan. Sedangkan untuk mengaktifkan mode kedua, program harus dijalankan dengan argumen -x, dan Ketika dijalankan dalam mode kedua, program utama akan berhenti namun membiarkan proses di setiap direktori yang masih berjalan hingga selesai (Direktori yang sudah dibuat akan mendownload gambar sampai selesai dan membuat file txt, lalu zip dan delete direktori).
- Membuat program daemon sehingga Program utama dapat dijalankan dalam dua mode.

```c
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

  if ((chdir("/home/arsyad/modul2/")) < 0) {
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
```

Output:



#### Kendala
