
#ifndef __SOCKET_H
#define __SOCKET_H

#include <string>
#include <vector>

class Socket {
private:
	struct Core;
	Core *core;
	void assign(Core *p);
public:
	Socket();

	Socket(Socket const &r)
		: core(0)
	{
		assign(r.core);
	}

	~Socket()
	{
		assign(0);
	}

	void operator = (Socket const &r)
	{
		assign(r.core);
	}
private:
	void parse_http_result(unsigned char const *begin, unsigned char const *end, std::vector<std::string> *resheader, std::vector<unsigned char> *resdata);
public:
	void socket(int af, int type, int protocol);
	void connect(char const *name, int port);
	void http_get(char const *uri, std::vector<std::string> const *header, std::vector<std::string> *resheader, std::vector<unsigned char> *resdata, bool keepalive);
	void http_post(char const *uri, char const *content, size_t contentlen, std::vector<std::string> const *header, std::vector<std::string> *resheader, std::vector<unsigned char> *resdata, bool keepalive);
	void close();
	void clear();

	int recv(void *buf, size_t len);
	int send(const void *buf, size_t len);

	void read(std::vector<unsigned char> *buffer);
	void write(char const *data, int datalen);
	void write(char const *data);

	static void initialize();
};

#endif
