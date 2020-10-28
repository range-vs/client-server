#include "../shared/TransportData.h"
#include "Net.h"
#include "Window.h"

#include <string>
#include <iostream>

using namespace std;

[System::STAThread]
int WinMain(HINSTANCE hInst, HINSTANCE prewHInst, LPSTR lpCmdLine, int nShowCmd)
{
	/*AllocConsole();
	freopen("CONIN$", "r", stdin);*/

	WpfWindow::Application^ app = gcnew WpfWindow::Application();

	app->MainWindow = gcnew WpfWindow::MainWindow();
	app->MainWindow->ShowDialog();

	return 0;
}

// написать краткую инструкцию
// залить на гит
