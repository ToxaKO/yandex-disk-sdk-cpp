
    auto Client::upload(url::path to, fs::path from, bool overwrite, std::list<string> fields) -> json {
   	 CURL *curl;
  	
  	struct stat file_info;
  
  	FILE *fd;
 	url::params_t url_params;
	struct curl_slist *header_list = nullptr;
	std::string auth_header;
	    
 	fs::path p(fs::current_path());
	url_params["path"] = quote(to.string(), curl);
	url_params["overwrite"] = overwrite;
	url_params["fields"] = boost::algorithm::join(fields, ",");
	std::string url = api_url + "/upload?" + url_params.string();
	    
	struct curl_slist *head_list = nullptr;
  	auth_head = "Authorization: OAuth " + token;
	head_list = curl_slist_append(head_list, auth_head.c_str());
  
  	fd = fopen("C:\\file.txt", "w");  //открытие файла для загрузки
 	if(!fd)
    	return 1; //не может продолжить 
   	// получаем размер файла
  	if(fstat(fileno(fd), &file_info)!=0;
    	return 1; /* can't continue */ 
 
  	curl = curl_easy_init();
	//  if(curl) {
     	//выбор места для загрузки
    	curl_easy_setopt(curl, CURLOPT_URL,url.c_str());
    	curl_easy_setopt(curl, CURLOPT_READDATA, &response);              
    	curl_easy_setopt(curl, CURLOPT_READFUNCTION, write<stringstream>);
	curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0);
	curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0);
	curl_easy_setopt(curl, CURLOPT_HTTPHEADER, head_list);
    	auto res = curl_easy_perform(curl);
     	curl_easy_cleanup(curl);
     	return http_response_code == 200;
	return ans;
    	 //загрузка по URL
    	curl_easy_setopt(curl, CURLOPT_UPLOAD, 1L);
 	curl_easy_setopt(curl, CURLOPT_PUT, 1L);
     	//чтения файла 
    	curl_easy_setopt(curl, CURLOPT_READDATA, fd);
    	//устанавливаем размер файла для отправки
    	curl_easy_setopt(curl, CURLOPT_INFILESIZE_LARGE,(curl_off_t)file_info.st_size);
     	//для облегчения трассировки 
    	curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
    	auto response_code = curl_easy_perform(curl);
	curl_slist_free_all(head_list);
	curl_easy_cleanup(curl);
	if (response_code != CURLE_OK) return json();
	return http_response_code == 201;
     	return 0;    
}

