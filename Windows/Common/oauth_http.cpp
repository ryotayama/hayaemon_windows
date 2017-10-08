/*
 * OAuth http functions in POSIX-C.
 *
 * Copyright 2007, 2008, 2009, 2010 Robin Gareus <robin@gareus.org>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 */
#if HAVE_CONFIG_H
# include <config.h>
#endif

#include <windows.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

#ifdef WIN32
#  define snprintf _snprintf
#pragma warning(disable:4996)
#endif

#include "oauth.h"

#define OAUTH_USER_AGENT "liboauth-agent/" LIBOAUTH_VERSION

#include <sys/stat.h>

#include "socket.h"

/* wrapper functions */

/**
 * do a HTTP GET request, wait for it to finish 
 * and return the content of the reply.
 * (requires libcurl or a command-line HTTP client)
 * 
 * more documentation in oauth.h
 *
 * @param u base url to get
 * @param q query string to send along with the HTTP request or NULL.
 * @return  In case of an error NULL is returned; otherwise a pointer to the
 * replied content from HTTP server. latter needs to be freed by caller.
 */
std::string oauth_http_get(const char *u, const char *q)
{
	Socket sock;
	std::vector<std::string> header;
	std::vector<std::string> resheader;
	std::vector<unsigned char> resdata;
	sock.http_get(u, &header, &resheader, &resdata, false);
	if (resheader.size() > 0) {
		int a, b, c;
		sscanf(resheader[0].c_str(), "HTTP/%u.%u %u", &a, &b, &c);
		if (c == 200 && !resdata.empty()) {
			char const *p = (char const *)&resdata[0];
			return std::string(p, p + resdata.size());
		}
	}
	return std::string();
}

/**
 * do a HTTP POST request, wait for it to finish 
 * and return the content of the reply.
 * (requires libcurl or a command-line HTTP client)
 *
 * more documentation in oauth.h
 *
 * @param u url to query
 * @param p postargs to send along with the HTTP request.
 * @return  In case of an error NULL is returned; otherwise a pointer to the
 * replied content from HTTP server. latter needs to be freed by caller.
 */
std::string oauth_http_post(const char *u, const char *p, bool keepalive)
{
	Socket sock;
	std::vector<std::string> header;
	std::vector<std::string> resheader;
	std::vector<unsigned char> resdata;
	sock.http_post(u, p, strlen(p), &header, &resheader, &resdata, keepalive);
	if (resheader.size() > 0) {
		int a, b, c;
		sscanf(resheader[0].c_str(), "HTTP/%u.%u %u", &a, &b, &c);
		if (c == 200 && !resdata.empty()) {
			char const *p = (char const *)&resdata[0];
			return std::string(p, p + resdata.size());
		}
	}
	return std::string();
}

