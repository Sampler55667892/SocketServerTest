#ifndef _socketInitProcState_h_
#define _socketInitProcState_h_

namespace ws_server
{
	struct SocketInitProcState
	{
		public:
			bool passed_socket;
			bool passed_bind;
			bool passed_listen;
			bool passed_accept;

			SocketInitProcState() :
				passed_socket(false),
				passed_bind(false),
				passed_listen(false),
				passed_accept(false)
			{
			}
	};
}

#endif // _socketInitProcState_h_
