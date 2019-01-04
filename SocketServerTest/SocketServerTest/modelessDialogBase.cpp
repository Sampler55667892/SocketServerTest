#include "modelessDialogBase.h"

namespace frame
{
	ModelessDialogBase::ModelessDialogBase(WindowInitSetting& initSetting, int templateId) :
		WindowBase::WindowBase(initSetting), templateId(templateId)
	{
		// init() は派生先で呼ぶ
	}

	ModelessDialogBase::~ModelessDialogBase()
	{
		WindowBase::~WindowBase();
	}

	HWND ModelessDialogBase::getDialogHandle()
	{
		return dialogHandle;
	}

	void ModelessDialogBase::init()
	{
		registerEventHandlers();

		WindowBase::init();
	}

	void ModelessDialogBase::create()
	{
		WindowBase::create();

		this->dialogHandle =
			::CreateDialog(WindowBase::getExeInstance(), MAKEINTRESOURCE(this->templateId), WindowBase::getWindowHandle(), dialogProc);
		// case modal:
		//::DialogBox(WindowBase::getExeInstance(), MAKEINTRESOURCE(this->templateId), WindowBase::getWindowHandle(), dialogHandle);
	}

	void ModelessDialogBase::show()
	{
		WindowBase::show();

		::ShowWindow(this->dialogHandle, SW_SHOW);
		::UpdateWindow(this->dialogHandle);
	}

	void ModelessDialogBase::onInitialize(HWND dialogHandle)
	{
	}

	void ModelessDialogBase::onCommand(HWND dialogHandle, int commandId)
	{
		//::EndDialog(dialogHandle, (INT_PTR)TRUE);
	}

	void ModelessDialogBase::onClose(HWND dialogHandle)
	{
	}

	void ModelessDialogBase::registerEventHandlers()
	{
		initDialogHandlers.push_back(pair<ModelessDialogBase *, ModelessDialogBase::InitDialogMessageHandler>(this, (InitDialogMessageHandler)&ModelessDialogBase::onInitialize));
		commandHandlers.push_back(pair<ModelessDialogBase *, ModelessDialogBase::CommandMessageHandler>(this, (CommandMessageHandler)&ModelessDialogBase::onCommand));
		closeHandlers.push_back(pair<ModelessDialogBase *, ModelessDialogBase::CloseMessageHandler>(this, (CloseMessageHandler)&ModelessDialogBase::onClose));
	}

	INT_PTR CALLBACK ModelessDialogBase::dialogProc(HWND dialogHandle, unsigned int message, WPARAM wParameter, LPARAM lParameter)
	{
		switch (message) {
			case WM_INITDIALOG: {
				for (list<pair<ModelessDialogBase *, ModelessDialogBase::InitDialogMessageHandler>>::iterator itr = initDialogHandlers.begin(); itr != initDialogHandlers.end(); ++itr) {
					auto pair = *itr;
					(pair.first->*pair.second)(dialogHandle);
				}
				break;
			}
			case WM_COMMAND: {
				int commandId = LOWORD(wParameter);
				for (list<pair<ModelessDialogBase *, ModelessDialogBase::CommandMessageHandler>>::iterator itr = commandHandlers.begin(); itr != commandHandlers.end(); ++itr) {
					auto pair = *itr;
					(pair.first->*pair.second)(dialogHandle, commandId);
				}
				break;
			}
			case WM_CLOSE: {
				for (list<pair<ModelessDialogBase *, ModelessDialogBase::CloseMessageHandler>>::iterator itr = closeHandlers.begin(); itr != closeHandlers.end(); ++itr) {
					auto pair = *itr;
					(pair.first->*pair.second)(dialogHandle);
				}
				::PostQuitMessage(0);
				break;
			}
		}
		return (INT_PTR)FALSE;
	}

	list<pair<ModelessDialogBase *, ModelessDialogBase::InitDialogMessageHandler>> ModelessDialogBase::initDialogHandlers;
	list<pair<ModelessDialogBase *, ModelessDialogBase::CommandMessageHandler>> ModelessDialogBase::commandHandlers;
	list<pair<ModelessDialogBase *, ModelessDialogBase::CloseMessageHandler>> ModelessDialogBase::closeHandlers;
}
