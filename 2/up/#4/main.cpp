#include "MyForm.h"

using namespace System;
using namespace System::Windows::Forms;

[STAThread]

int main(array<String^>^args)
{
	try{
		Application::EnableVisualStyles();
		Application::SetCompatibleTextRenderingDefault(false);
		up::MyForm form;
		Application::Run(%form);
	}
	catch (System::Exception^ e) {
		MessageBox::Show(e->Message);
	}
	return 0;
}