#include "MyForm.h"

using namespace System;
using namespace System::Windows::Forms;
using namespace DeltaPatcher;

[STAThreadAttribute]
int main()
{
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	MyForm form;
	Application::Run(% form);
	return 0;
}