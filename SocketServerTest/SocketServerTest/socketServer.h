#ifndef _socketServer_h_
#define _socketServer_h_

#pragma comment(lib, "ws2_32.lib")

#include <WinSock2.h> // Windows.h より先に Include しないとコンパイルエラー
#include "socketInitProcState.h"

namespace ws_server
{
	// [前提] ポート毎にインスタンスが異なる
	class SocketServer
	{
		public:
			SocketServer();
			virtual ~SocketServer();
			bool init(unsigned short port, SocketInitProcState& procState);
			bool receive(char ** text, bool& bufferOverflow, bool& disconnected); // スレッドブロックを掛ける
			bool send(char * text);
			bool close();
			bool reset(int port);
			int getLastError();

		private:
			bool startup(int * errorCode);
			bool cleanup(int * errorCode);

			// init
			bool initPort(unsigned short port, SocketInitProcState& procState);
			bool startListen(SocketInitProcState& procState);

			static const int SizeOfReceiveBuffer = 4096;
			static const int InvalidSocketValue = 0;
			SOCKET serverSocket;
			SOCKET clientSocket;
			int lastError;
			char receivedString[SizeOfReceiveBuffer];
	};
}

#endif // _socketServer_h_
