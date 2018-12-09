#include "socketServer.h"

namespace ws_server
{
	SocketServer::SocketServer() : serverSocket(InvalidSocketValue), clientSocket(InvalidSocketValue), lastError(NO_ERROR)
	{
		int errorCode;
		if (!startup(&errorCode))
			lastError = errorCode;
	}

	SocketServer::~SocketServer()
	{
		int dummy;
		cleanup(&dummy);
	}

	bool SocketServer::startup(int * errorCode)
	{
		WSADATA wsaData;
		*errorCode = ::WSAStartup(MAKEWORD(2, 0), &wsaData);
		return *errorCode != NO_ERROR;
	}

	bool SocketServer::cleanup(int * errorCode)
	{
		*errorCode = NO_ERROR;

		if (::WSACleanup() == INVALID_SOCKET) {
			*errorCode = ::WSAGetLastError();
			return false;
		}
		return true;
	}

#pragma region init

	bool SocketServer::init(unsigned short port, SocketInitProcState& procState)
	{
		if (!initPort(port, procState))
			return false;
		if (!startListen(procState))
			return false;
		return true;
	}

	bool SocketServer::initPort(unsigned short port, SocketInitProcState& procState)
	{
		this->serverSocket = ::socket(PF_INET, SOCK_STREAM, 0);
		if (serverSocket == INVALID_SOCKET) {
			lastError = ::WSAGetLastError();
			return false;
		}
		procState.passed_socket = true;
		sockaddr_in serverAddress;
		serverAddress.sin_family = PF_INET;
		serverAddress.sin_port = ::htons(port);
		serverAddress.sin_addr.S_un.S_addr = INADDR_ANY;
		if (::bind(serverSocket, (sockaddr *)&serverAddress, sizeof(serverAddress)) == INVALID_SOCKET) {
			lastError = ::WSAGetLastError();
			return false;
		}
		procState.passed_bind = true;

		return true;
	}

	bool SocketServer::startListen(SocketInitProcState& procState)
	{
		int backLog = SOMAXCONN; // Maximum (receive) queue length
		if (::listen(serverSocket, backLog) == INVALID_SOCKET) {
			lastError = ::WSAGetLastError();
			return false;
		}
		procState.passed_listen = true;

		sockaddr_in clientAddress;
		int addressLength = sizeof(clientAddress);
		// accept() (接続施行の許可) でスレッドブロックが掛かる
		// クライアントからの connect() でスレッドブロックが外れる
		this->clientSocket = ::accept(serverSocket, (sockaddr *)&clientAddress, &addressLength);
		if (clientSocket == INVALID_SOCKET) {
			lastError = ::WSAGetLastError();
			return false;
		}
		procState.passed_accept = true;

		return true;
	}

#pragma endregion // init

#pragma region communicate

	bool SocketServer::receive(char ** text, bool& bufferOverflow)
	{
		*text = nullptr;
		bufferOverflow = false;

		::memset(receivedString, sizeof(receivedString), 0);
		int flags = 0;
		// recv() によりサーバ側でスレッドブロックが掛かる
		// クライアントからの send() を受けてスレッドブロックが外れる
		int receivedDataBytes = ::recv(clientSocket, receivedString, sizeof(receivedString), flags);
		if (receivedDataBytes == SOCKET_ERROR) {
			lastError = ::WSAGetLastError();
			return false;
		}
		if (SizeOfReceiveBuffer <= receivedDataBytes) {
			bufferOverflow = true;
			return false;
		}
		receivedString[receivedDataBytes] = '\0';

		// ヒープメモリー確保 (呼出し元で解放されること想定)
		*text = ::_strdup(receivedString);

		return true;
	}

	bool SocketServer::send(char * text)
	{
		int flags = 0;
		if (::send(clientSocket, text, ::strlen(text), flags) == SOCKET_ERROR) {
			lastError = ::WSAGetLastError();
			return false;
		}
		return true;
	}

#pragma endregion // communicate

	int SocketServer::getLastError()
	{
		return lastError;
	}

	bool SocketServer::close()
	{
		if (::closesocket(this->serverSocket) == INVALID_SOCKET) {
			lastError = ::WSAGetLastError();
			return false;
		}
		this->serverSocket = 0;
		if (::closesocket(this->clientSocket) == INVALID_SOCKET) {
			lastError = ::WSAGetLastError();
			return false;
		}
		return true;
	}

	const int SocketServer::SizeOfReceiveBuffer;
	const int SocketServer::InvalidSocketValue;
}
