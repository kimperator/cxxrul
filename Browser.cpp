/*
Copyright (C) 2012 cxxrul authors,

This file is part of cxxrul.

cxxrul is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

cxxrul is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/


#include "Browser.h"
#include "Codings.h"
#include <iostream>
#include <sstream>
using namespace std;

bool Browser::first_initialize = true;
int Browser::counter = 0;

// callback function writes data to a std::ostream
static size_t data_write(void* buf, size_t size, size_t nmemb, void* userp)
{
	if(userp)
	{
		std::ostream& os = *static_cast<std::ostream*>(userp);
		std::streamsize len = size * nmemb;
		if(os.write((char*)buf, len))
			return len;
	}
	return 0;
}

Browser::Browser()
{
	if(first_initialize)
	{
		curl_global_init(CURL_GLOBAL_ALL);
		first_initialize = false;
	}
	counter++;
	user_agent = string("Mozilla/4.0 (compatible; MSIE 7.0b; Windows NT 6.0)");
	ignore_ssl_cert = true;
	share = curl_share_init();
	curl_share_setopt(share, CURLSHOPT_SHARE, CURL_LOCK_DATA_COOKIE);
}


Browser::~Browser()
{
	curl_share_cleanup(share);
	counter--;
	if(counter==0)
	{
		curl_global_cleanup();
	}
}

CURLcode Browser::get(const std::string& url, std::string& str)
{
	CURLcode ret;	
	stringstream ss;
	ret = get(url, ss);
	str = ss.str();
	return ret;
}

CURLcode Browser::get(const std::string& url, std::ostream& os)
{
	CURLcode code(CURLE_FAILED_INIT);
	CURL* curl = curl_easy_init();

	if(curl)
	{
		curl_easy_setopt(curl, CURLOPT_SHARE, share);
		curl_easy_setopt(curl, CURLOPT_USERAGENT, user_agent.c_str());
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, data_write);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &os);
		curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 1L);
		curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
		//curl_easy_setopt(curl, CURLOPT_FILE, &os);
		//curl_easy_setopt(curl, CURLOPT_TIMEOUT, timeout);
		curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
		{
			code = curl_easy_perform(curl);
		}
		curl_easy_cleanup(curl);
	}
	return code;
}

CURLcode Browser::post(const std::string& url, std::map<std::string, std::string> data_list, std::string& str)
{
	CURLcode ret;
	stringstream ss;
	ret = post(url, data_list, ss);
	str = ss.str();
	return ret;
}

CURLcode Browser::post(const std::string& url, std::map<std::string, std::string> data_list, std::ostream& os)
{
	std::string data;

	std::map<std::string, std::string>::const_iterator itr = data_list.begin();
	for(itr = data_list.begin(); itr != data_list.end(); ++itr){
		if(!data.empty())
		{
			data += "&";
		}
		data += (*itr).first + "=" + urlencode((*itr).second);
	}
	cout << "Browser::post> data(" << data.size() << ") = " << data << endl;
	return post(url, data, os);
}

CURLcode Browser::post(const std::string& url, std::string data, std::string& str)
{
	CURLcode ret;
	stringstream ss;
	ret = post(url, data, ss);
	str = ss.str();
	return ret;
}

CURLcode Browser::post(const std::string& url, std::string data, std::ostream& os)
{
	CURLcode code(CURLE_FAILED_INIT);
	CURL* curl = curl_easy_init();

	if(curl)
	{
		curl_easy_setopt(curl, CURLOPT_SHARE, share);
		curl_easy_setopt(curl, CURLOPT_USERAGENT, user_agent.c_str());
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &data_write);
		curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 1L);
		curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
		curl_easy_setopt(curl, CURLOPT_FILE, &os);
		//curl_easy_setopt(curl, CURLOPT_TIMEOUT, timeout);
		curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
		curl_easy_setopt(curl, CURLOPT_POST, 1);
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data.c_str());
		//curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE_LARGE, data.size()); 
		{
			code = curl_easy_perform(curl);
		}
		curl_easy_cleanup(curl);
	}
	return code;
}


