#include "JTester.h"

using namespace System;
using namespace System::Windows::Forms;
[STAThread]

int main()
{
	jtester::JTester main;
	Application::Run(%main);
}