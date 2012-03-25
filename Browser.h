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


#ifndef _CXXRUL_H_
#define _CXXRUL_H_

#include <string>
#include <map>
#include <curl/curl.h>

class Browser
{
private:
	static bool first_initialize;
	static int counter;
	std::string url;
	std::string user_agent;
	bool ignore_ssl_cert;
	CURLSH* share;
public:
	Browser();
	virtual ~Browser();
	CURLcode get(const std::string& url, std::ostream& os);
	CURLcode get(const std::string& url, std::string& str);

	CURLcode post(const std::string& url, std::map<std::string, std::string> data_list, std::ostream& os);
	CURLcode post(const std::string& url, std::map<std::string, std::string> data_list, std::string& str);

	CURLcode post(const std::string& url, std::string data, std::ostream& os);
	CURLcode post(const std::string& url, std::string data, std::string& str);

};

#endif
