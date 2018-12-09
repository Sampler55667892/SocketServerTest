#ifndef _socketUtility_h_
#define _socketUtility_h_

#include <WinSock2.h>

namespace ws_server
{
	class SocketUtility
	{
		public:
			static const char * convertToErrorText(unsigned int errorCode);
	};
}

#endif // _socketUtility_h_
