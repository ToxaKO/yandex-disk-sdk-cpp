# include <iostream>
#include <stdio.h>
#include <curl/curl.h>
#include <sys/stat.h>
#include <fcntl.h>
using namespace std;

class Client {
public:
  void UploadA()
  {
    CURL *curl;
  CURLcode res;
  struct stat file_info;
  double speed_upload, total_time;
  FILE *fd;
 
  fd = fopen("file.txt", "w");  //открытие файла для загрузки
  if(!fd)
    return 1; 
 
   // получаем размер файла
  if(fstat(fileno(fd), &file_info) != 0)
    return 1; /* can't continue */ 
 
  curl = curl_easy_init();
  if(curl) {
     //выбор места для загрузки
    curl_easy_setopt(curl, CURLOPT_URL,url.c_str());
                     
 
     //загрузка по URL
    curl_easy_setopt(curl, CURLOPT_UPLOAD, 1L);
 
     //чтения файла 
    curl_easy_setopt(curl, CURLOPT_READDATA, fd);
 
    //устанавливаем размер файла для отправки
    curl_easy_setopt(curl, CURLOPT_INFILESIZE_LARGE,
                     (curl_off_t)file_info.st_size);
 
     //для облегчения трассировки 
    curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
 
    res = curl_easy_perform(curl);
     //проверка на ошибки
    if(res != CURLE_OK) {
      fprintf(stderr, "curl_easy_perform() failed: %s\n",
              curl_easy_strerror(res));
 
    }
   
    //очистка
    curl_easy_cleanup(curl);
  }
  fclose(fd);
  return 0;
  }
    
};
