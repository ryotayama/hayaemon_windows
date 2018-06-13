
#ifdef WIN32
#include <winsock.h>
#include <windows.h>
#else
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <net/if.h>
#include <netdb.h>
#endif

#include "socket.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#ifdef WIN32
typedef SOCKET socket_t;
#pragma warning(disable:4996)
#else
typedef int socket_t;
#define INVALID_SOCKET (-1)
#define closesocket(FD) close(FD)
#endif

#define USER_AGENT "soramimi.jp"

void Socket::initialize()
{
#ifdef WIN32
	WSADATA wsaData;
	WORD wVersionRequested;
	wVersionRequested = MAKEWORD(1,1);
	WSAStartup(wVersionRequested, &wsaData);
	atexit((void (*)(void))(WSACleanup));
#endif
}



struct Socket::Core {
	unsigned int ref;
	socket_t sock;
	Core()
		: ref(0)
		, sock(INVALID_SOCKET)
	{
	}
};

Socket::Socket()
	: core(0)
{
	assign(new Core());
}

void Socket::assign(Core *p)
{
	if (p) {
		p->ref++;
	}
	if (core) {
		if (core->ref > 1) {
			core->ref--;
		} else {
			delete core;
		}
	}
	core = p;
}

void Socket::socket(int af, int type, int protocol)
{
	assign(new Core());
	core->sock = ::socket(af, type, protocol);
}

struct http_request_t {
	std::string name;
	int port;
	std::string query;
	http_request_t()
	{
		port = 0;
	}
};

static http_request_t parse_http(char const *uri)
{
	if (strncmp(uri, "http://", 7) != 0) {
		return http_request_t();
	}

	http_request_t x;

	char const *p;
	p = strchr(uri + 7, '/');
	if (p) {
		x.query = p;
	} else {
		p = uri + strlen(uri);
		x.query = "/";
	}
	x.name = std::string(uri + 7, p);
	x.port = 80;
	p = strchr(x.name.c_str(), ':');
	if (p) {
		x.port = atoi(p + 1);
		x.name = std::string(x.name.c_str(), p);
	}

	return x;
}

void Socket::connect(char const *name, int port)
{
	struct hostent *host;
	struct sockaddr_in addr;
	host = gethostbyname(name);
	memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	memcpy(&addr.sin_addr, host->h_addr, host->h_length);
	addr.sin_port = htons(port);
	::connect(core->sock, (struct sockaddr *)&addr, sizeof(sockaddr_in));
}

void Socket::parse_http_result(unsigned char const *begin, unsigned char const *end, std::vector<std::string> *resheader, std::vector<unsigned char> *resdata)
{
	if (begin < end) {
		unsigned char const *left = begin;
		unsigned char const *right = left;
		while (1) {
			if (right >= end) {
				break;
			}
			if (*right == '\r' || *right == '\n') {
				if (left < right) {
					resheader->push_back(std::string(left, right));
				}
				if (right + 1 < end && *right == '\r' && right[1] == '\n') {
					right++;
				}
				right++;
				if (*right == '\r' || *right == '\n') {
					if (right + 1 < end && *right == '\r' && right[1] == '\n') {
						right++;
					}
					right++;
					left = right;
					break;
				}
				left = right;
			} else {
				right++;
			}
		}
		if (left < end) {
			resdata->assign(left, end);
		}
	}
}

void Socket::http_get(char const *uri, std::vector<std::string> const *header, std::vector<std::string> *resheader, std::vector<unsigned char> *resdata, bool keepalive)
{
	resheader->clear();
	resdata->clear();

	if (strncmp(uri, "http://", 7) != 0) {
		return;
	}

	http_request_t http = parse_http(uri);

	socket(AF_INET, SOCK_STREAM, 0);
	connect(http.name.c_str(), http.port);

	std::string req;
	req = "GET ";
	req += http.query;
	req += " HTTP/1.1\r\n";

	std::vector<std::string> preheader;
	preheader.push_back(std::string("User-Agent: ") + USER_AGENT);
	preheader.push_back("Host: " + http.name);
	preheader.push_back("Accept: */*");
	if (!keepalive) {
		preheader.push_back("Connection: close");
	}

	for (std::vector<std::string>::const_iterator it = preheader.begin(); it != preheader.end(); it++) {
		req += *it;
		req += "\r\n";
	}

	if (header) {
		for (std::vector<std::string>::const_iterator it = header->begin(); it != header->end(); it++) {
			req += *it;
			req += "\r\n";
		}
	}
	req += "\r\n";

	write(req.c_str(), req.size());

	//

	std::vector<unsigned char> data;
	read(&data);

	if (!data.empty()) {
		unsigned char const *begin = &data[0];
		unsigned char const *end = begin + data.size();
		parse_http_result(begin, end, resheader, resdata);
	}

}

static inline std::string to_s(size_t n)
{
	char tmp[100];
	sprintf(tmp, "%u", n);
	return tmp;
}

void Socket::http_post(char const *uri, char const *content, size_t contentlen, std::vector<std::string> const *header, std::vector<std::string> *resheader, std::vector<unsigned char> *resdata, bool keepalive)
{
	resheader->clear();
	resdata->clear();

	if (strncmp(uri, "http://", 7) != 0) {
		return;
	}

	http_request_t http = parse_http(uri);

	socket(AF_INET, SOCK_STREAM, 0);
	connect(http.name.c_str(), http.port);

	std::string req;
	req = "POST ";
	req += http.query;
	req += " HTTP/1.1\r\n";

	std::vector<std::string> preheader;
	preheader.push_back(std::string("User-Agent: ") + USER_AGENT);
	preheader.push_back("Host: " + http.name);
	preheader.push_back("Accept: */*");
	preheader.push_back("Content-Length: " + to_s(contentlen));	
	preheader.push_back("Content-Type: application/x-www-form-urlencoded");
	if (!keepalive) {
		preheader.push_back("Connection: close");
	}

	for (std::vector<std::string>::const_iterator it = preheader.begin(); it != preheader.end(); it++) {
		req += *it;
		req += "\r\n";
	}

	if (header) {
		for (std::vector<std::string>::const_iterator it = header->begin(); it != header->end(); it++) {
			req += *it;
			req += "\r\n";
		}
	}
	req += "\r\n";

	write(req.c_str(), req.size());
	write(content, contentlen);

	//

	std::vector<unsigned char> data;
	read(&data);

	if (!data.empty()) {
		unsigned char const *begin = &data[0];
		unsigned char const *end = begin + data.size();
		parse_http_result(begin, end, resheader, resdata);
	}
}

void Socket::close()
{
	::closesocket(core->sock);
}

void Socket::clear()
{
	core->sock = INVALID_SOCKET;
}

int Socket::recv(void *buf, size_t len)
{
	return ::recv(core->sock, (char *)buf, len, 0);
}

int Socket::send(const void *buf, size_t len)
{
	return ::send(core->sock, (char const *)buf, len, 0);
}

void Socket::read(std::vector<unsigned char> *buffer)
{
	buffer->clear();

	char tmp[4096];
	while (1) {
		int n = recv(tmp, sizeof(tmp));
		if (n < 1) {
			break;
		}
		buffer->insert(buffer->end(), tmp, tmp + n);
	}
}

void Socket::write(char const *data, int datalen)
{
	while (datalen > 0) {
		int n = send(data, datalen);
		if (n < 1 || n > datalen) {
			break;
		}
		datalen -= n;
		data += n;
	}
}

void Socket::write(char const *data)
{
	write(data, strlen(data));
}
