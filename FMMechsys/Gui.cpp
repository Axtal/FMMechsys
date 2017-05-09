#include "Gui.h"

using namespace System;
using namespace System::Windows::Forms;


[STAThread]
void Main()
{
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);

	FMMechsys::Gui form;
	Application::Run(%form);
}

void main()
{
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);

	FMMechsys::Gui form;
	Application::Run(%form);
}

