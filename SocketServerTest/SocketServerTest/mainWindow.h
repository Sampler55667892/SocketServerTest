#ifndef _mainWindow_h_
#define _mainWindow_h_

#include <vector>
#include "modelessDialogBase.h"

namespace test
{
	using namespace frame;
	using namespace std;

	class MainWindow : public ModelessDialogBase
	{
		public:
			MainWindow(WindowInitSetting& initSetting, int templateId);
			virtual ~MainWindow();
			void addTextToConsole(const char * text);
			void addTextToConsole(const char * text, const char * header);
			void clearConsole();
		protected:
			virtual void init();
			virtual void create();
			virtual void show();
			virtual int getWindowKey();
			// Handlers
			virtual void onInitialize(HWND dialogHandle);
			virtual void onCommand(HWND dialogHandle, int commandId);
		private:
			vector<char *> consoleTexts;
	};
}

#endif // _mainWindow_h_
