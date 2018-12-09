#ifndef _modelessDialogBase_h_
#define _modelessDialogBase_h_

#include "windowBase.h"
#include <list>

namespace frame
{
	using namespace std;

	// {abstract}
	class ModelessDialogBase : public WindowBase
	{
		public:
			ModelessDialogBase(WindowInitSetting& initSetting, int templateId);
			virtual ~ModelessDialogBase();
			HWND getDialogHandle();
		protected:
			virtual void init();
			virtual void create();
			virtual void show();
			virtual void onInitialize(HWND dialogHandle);
			virtual void onCommand(HWND dialogHandle, int commandId);
		private:
			void registerEventHandlers();
			static INT_PTR CALLBACK dialogProc(HWND dialogHandle, unsigned int message, WPARAM wParameter, LPARAM lParameter);

			typedef void(ModelessDialogBase::*InitDialogMessageHandler)(HWND);
			typedef void(ModelessDialogBase::*CommandMessageHandler)(HWND, int);

			HWND dialogHandle;
			int templateId;
			static list<pair<ModelessDialogBase *, ModelessDialogBase::InitDialogMessageHandler>> initDialogHandlers;
			static list<pair<ModelessDialogBase *, ModelessDialogBase::CommandMessageHandler>> commandHandlers;
	};
}

#endif // _modelessDialogBase_h_
