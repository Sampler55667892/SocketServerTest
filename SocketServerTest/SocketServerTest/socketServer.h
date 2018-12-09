#ifndef _socketServer_h_
#define _socketServer_h_

#pragma comment(lib, "ws2_32.lib")

#include <WinSock2.h> // Windows.h ����� Include ���Ȃ��ƃR���p�C���G���[
#include "socketInitProcState.h"

namespace ws_server
{
	// [�O��] �|�[�g���ɃC���X�^���X���قȂ�
	class SocketServer
	{
		public:
			SocketServer();
			virtual ~SocketServer();
			bool init(unsigned short port, SocketInitProcState& procState);
			bool receive(char ** text, bool& bufferOverflow); // �X���b�h�u���b�N���|����
			bool send(char * text);
			bool close();
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
