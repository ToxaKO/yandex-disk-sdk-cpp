# include <iostream>
#include <stdio.h>
#include <curl/curl.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <curl/curl.h>

#include <url/params.hpp>
#include <yadisk/client.hpp>
#include <boost/algorithm/string/join.hpp>

#include <sstream>
using std::stringstream;

#include "callbacks.hpp"
#include "quote.hpp"
using namespace std;

Client::Client(string token_) : token{token_} {}

auto upload(url::path to, fs::path from, bool overwrite, list<string> fields) -> json {
    CURL *curl;
  CURLcode res;
  struct stat file_info;
  double speed_upload, total_time;
  FILE *fd;
  url::params_t url_params;
		struct curl_slist *header_list = nullptr;
		std::string auth_header;
 
		url_params["path"] = quote(to.string(), curl);
		url_params["overwrite"] = overwrite;
		url_params["fields"] = boost::algorithm::join(fields, ",");
		std::string url = api_url + "/copy?" + url_params.string();
  auth_header = "Authorization: OAuth " + token;
		header_list = curl_slist_append(header_list, auth_header.c_str());
  
  fd = fopen("debugit", "rb");  //открытие файла для загрузки
 /* if(!fd)
    return 1; */
   // получаем размер файла
  if(fstat(fileno(fd), &file_info) != 0)
  //  return 1; /* can't continue */ 
 
  curl = curl_easy_init();
//  if(curl) {
     //выбор места для загрузки
    curl_easy_setopt(curl, CURLOPT_URL,url.c_str());
    curl_easy_setopt(curl, CURLOPT_READDATA, &response);              
    curl_easy_setopt(curl, CURLOPT_READFUNCTION, write<stringstream>);
		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0);
		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0);
		curl_easy_setopt(curl, CURLOPT_HTTPHEADER, header_list);
     //загрузка по URL
    curl_easy_setopt(curl, CURLOPT_UPLOAD, 1L);
 
     //чтения файла 
    curl_easy_setopt(curl, CURLOPT_READDATA, fd);
 
    //устанавливаем размер файла для отправки
    curl_easy_setopt(curl, CURLOPT_INFILESIZE_LARGE,
                     (curl_off_t)file_info.st_size);
 
     //для облегчения трассировки 
    curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
 
    auto response_code = curl_easy_perform(curl);

		curl_slist_free_all(header_list);
		curl_easy_cleanup(curl);

		if (response_code != CURLE_OK) return json();

		auto answer = json::parse(response);
		return answer;
    
};
