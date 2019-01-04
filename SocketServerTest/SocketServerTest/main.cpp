#include <thread>
#include "socketServer.h" // Windows.h より先にインクルードする (WinSock2.h を Windows.h より先にインクルードするため (そうしないとコンパイルエラー))
#include "mainWindow.h"
#include "windowUtility.h"
#include "socketUtility.h"
#include "testConstants.h"
#include "resource.h"
#include "instancesMap.h"

#define LISTENING_PORT	8080

using namespace std;
using namespace test;
using namespace frame;
using namespace ws_server;

void windowThread(HINSTANCE exeInstance, int commandShow)
{
	RECT windowRect;
	windowRect.left = 0;
	windowRect.top = 0;
	windowRect.right = windowRect.left + 800;
	windowRect.bottom = windowRect.top + 600;
	//DWORD windowStyle = WS_OVERLAPPEDWINDOW;
	DWORD windowStyle = WS_CHILD;
	WindowInitSetting initSetting(exeInstance, commandShow, IDS_MAIN_WINDOW_TITLE, IDS_MAIN_WINDOW_CLASS, windowStyle, windowRect, nullptr);
	MainWindow * mainWindow = new MainWindow(initSetting, IDD_MAIN_WINDOW);
}

void receiveThread(int port)
{
	SocketServer server;
	if (server.getLastError() != NO_ERROR) {
		WindowUtility::showErrorMessage(nullptr, SocketUtility::convertToErrorText(server.getLastError()), "SOCKET ERROR (ctor)");
		return;
	}
	InstancesMap::set(INSTANCE_KEY_SOCKET_SERVER, &server);

	SocketInitProcState procState;
	if (!server.init(port, procState)) {
		WindowUtility::showErrorMessage(nullptr, SocketUtility::convertToErrorText(server.getLastError()), "SOCKET ERROR (init)");
		return;
	}

	const int sleepTimeMillisec = 100;
	for (;;) {
		char * text = nullptr;
		bool bufferOverflow = false;
		bool disconnected = false;
		if (!server.receive(&text, bufferOverflow, disconnected)) {
			if (disconnected) {
				if (!server.reset(port))
					break;
				continue;
			}
			if (bufferOverflow)
				WindowUtility::showErrorMessage(nullptr, "Buffer overflow happened.", "SOCKET ERROR (receive)");
			else
				WindowUtility::showErrorMessage(nullptr, SocketUtility::convertToErrorText(server.getLastError()), "SOCKET ERROR (receive)");
			break;
		}
		if (text == nullptr) {
			WindowUtility::showErrorMessage(nullptr, "Received text is empty.", "SOCKET ERROR (receive)");
			break;
		}

		auto mainWindow = (MainWindow *)InstancesMap::get(INSTANCE_KEY_MAIN_WINDOW);
		mainWindow->addTextToConsole(text, "receive:");

		if (text != nullptr)
			delete text;

		this_thread::sleep_for(chrono::milliseconds(sleepTimeMillisec));
	}

	WindowUtility::showErrorMessage(nullptr, "Exit receiveThread.", "SOCKET ERROR (receive)");
}

int __stdcall WinMain(HINSTANCE exeInstance, HINSTANCE prevInstance, LPSTR commandLine, int commandShow)
{
	thread winThread(windowThread, exeInstance, commandShow);
	thread recvThread(receiveThread, LISTENING_PORT);

	recvThread.detach(); // winThread の停止でプログラムを終了させる
	winThread.join();

	return 0;
}
