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



#ifndef CODINGS_H_
#define CODINGS_H_
#include <string>
int UrlDecode(const char *source, char *dest);
int UrlEncode(const char *source, char *dest, unsigned max);
std::string UrlDecodeString(const std::string & encoded);
std::string UrlEncodeString(const std::string & decoded);

std::string urlencode(const std::string &c);
std::string char2hex( char dec );


#endif
