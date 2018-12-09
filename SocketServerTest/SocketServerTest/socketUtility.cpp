#include "socketUtility.h"

namespace ws_server
{
	// (cf.) WSAStartup (http://chokuto.ifdef.jp/advanced/function/WSAStartup.html)
	// (cf.) WSACleanup (http://chokuto.ifdef.jp/advanced/function/WSACleanup.html)
	// (cf.) socket (http://chokuto.ifdef.jp/advanced/function/socket.html)
	// (cf.) closesocket (http://chokuto.ifdef.jp/advanced/function/closesocket.html)
	// (cf.) bind (http://chokuto.ifdef.jp/advanced/function/bind.html)
	// (cf.) listen (http://chokuto.ifdef.jp/advanced/function/listen.html)
	// (cf.) accept (http://chokuto.ifdef.jp/advanced/function/accept.html)
	// (cf.) Windowsソケットのエラーコード、値、および意味 (https://support.microsoft.com/ja-jp/help/819124/windows-sockets-error-codes-values-and-meanings)
	// (cf.) winerror.h
	const char * SocketUtility::convertToErrorText(unsigned int errorCode)
	{
		// 10004
		if (errorCode == WSAEINTR) return "A blocking operation was interrupted by a call to WSACancelBlockingCall.";
		// 10013
		else if (errorCode == WSAEACCES) return "An attempt was made to access a socket in a way forbidden by its access permissions.";
		// 10014
		else if (errorCode == WSAEFAULT) return "The system detected an invalid pointer address in attempting to use a pointer argument in a call.";
		// 10022
		else if (errorCode == WSAEINVAL) return "An invalid argument was supplied.";
		// 10024
		else if (errorCode == WSAEMFILE) return "Too many open sockets.";
		// 10035
		else if (errorCode == WSAEWOULDBLOCK) return "A non-blocking socket operation could not be completed immediately.";
		// 10036
		else if (errorCode == WSAEINPROGRESS) return "A blocking operation is currently executing.";
		// 10038
		else if (errorCode == WSAENOTSOCK) return "An operation was attempted on something that is not a socket.";
		// 10040
		else if (errorCode == WSAEMSGSIZE) return "A message sent on a datagram socket was larger than the internal message buffer or some other network limit, or the buffer used to receive a datagram into was smaller than the datagram itself.";
		// 10041
		else if (errorCode == WSAEPROTOTYPE) return "A protocol was specified in the socket function call that does not support the semantics of the socket type requested.";
		// 10043
		else if (errorCode == WSAEPROTONOSUPPORT) return "The requested protocol has not been configured into the system, or no implementation for it exists.";
		// 10044
		else if (errorCode == WSAESOCKTNOSUPPORT) return "The support for the specified socket type does not exist in this address family.";
		// 10045
		else if (errorCode == WSAEOPNOTSUPP) return "The attempted operation is not supported for the type of object referenced.";
		// 10047
		else if (errorCode == WSAEAFNOSUPPORT) return "An address incompatible with the requested protocol was used.";
		// 10048
		else if (errorCode == WSAEADDRINUSE) return "Only one usage of each socket address (protocol/network address/port) is normally permitted.";
		// 10049
		else if (errorCode == WSAEADDRNOTAVAIL) return "The requested address is not valid in its context.";
		// 10050
		else if (errorCode == WSAENETDOWN) return "A socket operation encountered a dead network.";
		// 10052
		else if (errorCode == WSAENETRESET) return "The connection has been broken due to keep-alive activity detecting a failure while the operation was in progress.";
		// 10053
		else if (errorCode == WSAECONNABORTED) return "An established connection was aborted by the software in your host machine.";
		// 10054
		else if (errorCode == WSAECONNRESET) return "An existing connection was forcibly closed by the remote host.";
		// 10055
		else if (errorCode == WSAENOBUFS) return "An operation on a socket could not be performed because the system lacked sufficient buffer space or because a queue was full.";
		// 10056
		else if (errorCode == WSAEISCONN) return "A connect request was made on an already connected socket.";
		// 10057
		else if (errorCode == WSAENOTCONN) return "A request to send or receive data was disallowed because the socket is not connected and (when sending on a datagram socket using a sendto call) no address was supplied.";
		// 10058
		else if (errorCode == WSAESHUTDOWN) return "A request to send or receive data was disallowed because the socket had already been shut down in that direction with a previous shutdown call.";
		// 10060
		else if (errorCode == WSAETIMEDOUT) return "A connection attempt failed because the connected party did not properly respond after a period of time, or established connection failed because connected host has failed to respond.";
		// 10065
		else if (errorCode == WSAEHOSTUNREACH) return "A socket operation was attempted to an unreachable host.";
		// 10067
		else if (errorCode == WSAEPROCLIM) return "A Windows Sockets implementation may have a limit on the number of applications that may use it simultaneously.";
		// 10091
		else if (errorCode == WSASYSNOTREADY) return "WSAStartup cannot function at this time because the underlying system it uses to provide network services is currently unavailable.";
		// 10092
		else if (errorCode == WSAVERNOTSUPPORTED) return "The Windows Sockets version requested is not supported.";
		// 10093
		else if (errorCode == WSANOTINITIALISED) return "Either the application has not called WSAStartup, or WSAStartup failed.";
		// 10104
		else if (errorCode == WSAEINVAL) return "The procedure call table is invalid.";

		return nullptr;
	}
}
