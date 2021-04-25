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
