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
		if (console == nullptr)
			return;

		consoleTexts.push_front(::_strdup(text)); // ヒープを積む

		string outputText;
		int countLines = 0;
		list<const char *> deleteTargets;
		for (list<const char *>::iterator itr = consoleTexts.begin(); itr != consoleTexts.end(); ++itr) {
			outputText += *itr;
			outputText += "\r\n";
			if (countLines++ > MaxCountLinesOnConsole) {
				// コレクションのループ中にコレクション自体を変更するとエラーになる
				deleteTargets.push_back(*itr);
			}
		}
		if ((int)deleteTargets.size() > 0) {
			for (list<const char *>::iterator itr = deleteTargets.begin(); itr != deleteTargets.end(); ++itr) {
				delete[] *itr; // ヒープ以外が積まれるとエラーになる
				consoleTexts.pop_back();
			}
		}

		::SendMessageA(console, WM_SETTEXT, (WPARAM)NULL, (LPARAM)outputText.c_str());
	}

	void MainWindow::addTextToConsole(const char * text, const char * header)
	{
		addTextToConsole(text);
		addTextToConsole(header);
	}

	void MainWindow::clearConsole()
	{
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

	void MainWindow::onClose(HWND dialogHandle)
	{
	}

	const int MainWindow::MaxCountLinesOnConsole = 256;
}
