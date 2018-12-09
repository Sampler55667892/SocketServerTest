#include "socketServer.h" // Windows.h より先にインクルードする (WinSock2.h を Windows.h より先にインクルードするため (そうしないとコンパイルエラー))
#include "mainWindow.h"
#include "testConstants.h"
#include "resource.h"
#include "instancesMap.h"
#include "windowUtility.h"
#include "socketUtility.h"
#include <string>

namespace test
{
	using namespace ws_server;

	MainWindow::MainWindow(WindowInitSetting& initSetting, int templateId) : ModelessDialogBase::ModelessDialogBase(initSetting, templateId)
	{
		init();
	}

	MainWindow::~MainWindow()
	{
		ModelessDialogBase::~ModelessDialogBase();
	}

	void MainWindow::addTextToConsole(const char * text)
	{
		HWND console = ::GetDlgItem(ModelessDialogBase::getDialogHandle(), IDC_CONSOLE);
		if (console != nullptr) {
			consoleTexts.push_back(::_strdup(text));
			auto size = (int)consoleTexts.size();
			string text;
			for (auto i = size - 1; i >= 0; --i) {
				text += consoleTexts[i];
				text += "\r\n";
			}
			::SendMessageA(console, WM_SETTEXT, (WPARAM)NULL, (LPARAM)text.c_str());
		}
	}

	void MainWindow::addTextToConsole(const char * text, const char * header)
	{
		addTextToConsole(text);
		addTextToConsole(header);
	}

	void MainWindow::clearConsole()
	{
		auto size = (int)consoleTexts.size();
		for (auto i = 0; i < size; ++i)
			delete consoleTexts[i];
		consoleTexts.clear();
	}

	void MainWindow::init()
	{
		InstancesMap::set(INSTANCE_KEY_MAIN_WINDOW, this);

		ModelessDialogBase::init();
	}

	void MainWindow::create()
	{
		ModelessDialogBase::create();
	}

	void MainWindow::show()
	{
		ModelessDialogBase::show();
	}

	int MainWindow::getWindowKey()
	{
		return WINDOW_KEY_MAIN;
	}

	void MainWindow::onInitialize(HWND dialogHandle)
	{
	}

	void MainWindow::onCommand(HWND dialogHandle, int commandId)
	{
		if (commandId == IDC_SEND_TEST_BUTTON) {
			const char * message = "test send";
			addTextToConsole(message, "send:");

			auto server = (SocketServer *)InstancesMap::get(INSTANCE_KEY_SOCKET_SERVER);
			if (!server->send((char *)message))
				WindowUtility::showErrorMessage(ModelessDialogBase::getDialogHandle(), SocketUtility::convertToErrorText(server->getLastError()), "SOCKET ERROR (send)");
		}
	}
}
