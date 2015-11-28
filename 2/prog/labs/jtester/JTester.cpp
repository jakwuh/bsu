#include "JTester.h"

using namespace jtester;

System::Void JTester::Test()
{
	TestButton->Enabled = false;
	try {
		delete log;
		log = gcnew StreamWriter("report.log");
		DataChart->Series->Clear();
		StatsRichTextBox->Clear();
		Series.Clear();
		List< String^ >^ Complexity = gcnew List< String^ >;
		List< String^ >^ Data = gcnew List< String^ >;
		List< String^ >^ Files = gcnew List< String^ >;

		for each (System::String^ Line in NRichTextBox->Lines) {
			if (Line->Length == 0) continue;
			Complexity->Add(Line);
		}
		for each (System::String^ Line in InputRichTextBox->Lines) {
			if (Line->Length == 0) continue;
			Data->Add(Line);
		}
		for each (System::String^ Line in FilesListBox->Items) {
			Files->Add(Line);
		}

		if (Files->Count == 0) {
			throw gcnew ::Exception::InputException("Please, provide at least one executable file.");
		}
		if (Complexity->Count == 0) {
			throw gcnew ::Exception::InputException("Please, provide any data for testing.");
		}
		if (Complexity->Count != Data->Count) {
			throw gcnew ::Exception::InputException("Input textboxes contain different number of lines.");
		}

		Log("Start testing...");
		Log("-");
		Status("Running");

		for(int i = 0; i < Files->Count; ++i) {
			String^ File = Files[i];
			String^ ChartName = GetChartName(File, i);
			DataChart->Series->Add(ChartName);
			DataChart->Series[ChartName]->ChartType = DataVisualization::Charting::SeriesChartType::Spline;
			Generic::Queue< Execution^ >^ Executions = gcnew Generic::Queue< Execution^ >;
			for (int i = 0; i < Complexity->Count; i++) {
				Executions->Enqueue(gcnew Execution( File, InputFile, Data[i], ChartName, Convert::ToDouble(Complexity[i])));
			}
			Series.Enqueue(Executions);
		}

		Execute();
		log->Close();
	}
	catch (::Exception::Exception^ e) {
		MessageBox::Show(e->Message);
	}
	catch (::System::Exception^ e) {
		MessageBox::Show(e->Message);
	}
	TestButton->Enabled = true;
}

System::Void JTester::Execute()
{
	ProgressBar->Value = 0;
	ProgressBar->Visible = true;
	clock_t start, end;
	std::map< double, double > points;
	System::Int32 TotalN = Series.Count * Series.Peek()->Count, ExecutedN = 0;
	while (Series.Count > 0) {
		Generic::Queue< Execution^ >^ Executions = Series.Dequeue(); 
		String^ File = Executions->Peek()->File;
		points.clear();
		Log("-");
		Log("\nStart testing file \"" + File + "\"\n");
		System::Int32 Count = Executions->Count;
		while (Executions->Count > 0) {
			Status("Executing \"" + File + "\" " + Convert::ToString(Count - Executions->Count) + "\\" + Convert::ToString(Count));
			Execution^ Exec = Executions->Dequeue();

		   	StreamWriter^ SW = gcnew StreamWriter(Exec->InputFile);
		   	SW->Write(Exec->Input);
		   	SW->Close();

			start = clock();

			char name[500];
			strcpy_s(name, 500, toSTD(Exec->File).c_str());
			wchar_t wname[500];
			mbstowcs(wname, name, 500);

			SHELLEXECUTEINFO ShExecInfo;
			HANDLE hProcess = NULL;
			ShExecInfo.cbSize = sizeof(SHELLEXECUTEINFO);
			ShExecInfo.fMask = SEE_MASK_NOCLOSEPROCESS;
			ShExecInfo.hwnd = NULL;
			ShExecInfo.lpVerb = NULL;
			ShExecInfo.lpFile = wname;
			ShExecInfo.lpParameters = NULL;
			ShExecInfo.lpDirectory = NULL;
			ShExecInfo.nShow = SW_HIDE;
			ShExecInfo.hInstApp = NULL;
			ShExecInfo.hProcess = hProcess;
			ShellExecuteEx(&ShExecInfo);
			WaitForSingleObject(ShExecInfo.hProcess, INFINITE);

			end = clock();

			points[Convert::ToDouble(Exec->N)] = (end - start);
			DataChart->Series[Exec->ChartName]->Points->AddXY(Exec->N, end - start);
			Log("\nExecution for N = " + Convert::ToString(Exec->N) + " | time = " + Convert::ToString(end - start));
			++ExecutedN;
			ProgressBar->Value = (int)(100 * (ExecutedN * 1. / TotalN));
			Refresh();
		}
		Status("Analyzing approximaitons");
		Log("\n\nStart analyzing approximations");

		::Math::Regression *bestR = nullptr;

		Regress(new ::Math::LinearRegression(points), bestR);
		Regress(new ::Math::LogarithmicRegression(points), bestR);
		Regress(new ::Math::PowerRegression(points), bestR);
		Regress(new ::Math::QuasilogRegression(points), bestR);

		Log("\n\nEnd analyzing approximations");
		Log("\nBest approximation is:");

		Log("\n\n");
		Log(gcnew String(bestR->toString().c_str()));

		Log("\n\nEnd testing file \"" + File + "\"");
		Log("-");
	}
	
	Log("-");
	Log("\nEnd testing...");
	Status("");
	ProgressBar->Visible = false;
}

System::Void JTester::Regress(::Math::Regression* R, ::Math::Regression*& bestR)
{
	R->calculate();
	Log("\n\n");
	Log(gcnew String(R->toString().c_str()));
	if (!bestR || ::std::abs(bestR->correlation) < std::abs(R->correlation)) std::swap(bestR, R);
	delete R;
}

System::Void JTester::Log(System::String^ text)
{
	if (text->CompareTo("-") == 0) text = "\n----------------------------------------";
	StatsRichTextBox->Text += text;
	log->Write(text);
}

System::Void JTester::Status(System::String^ text)
{
	if (text->Length == 0) text = "JTester";
	else text = "JTester - " + text;
	StatusLabel->Text = text;
}

System::String^ JTester::GetChartName(System::String^ File, System::Int32 Index)
{
	return File + Convert::ToString(Index);
}

System::Void JTester::aboutAuthorToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
	char text[] = "Developer: James Akwuh, 2015 (C) \nTo contact mail on akwuh@mail.ru \nOnly for non-commercial use. \nEnjoy the soft!";
	System::String^ buf = gcnew System::String(text);
	MessageBox::Show(this, buf, "About Author");
}

System::Void JTester::aboutToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
	char text[] = "JTester build 01 \nThe program checks the execution time of \ncustom executable files and calculates complexity for them\nEnjoy the soft!";
	System::String^ buf = gcnew System::String(text);
	MessageBox::Show(this, buf, "About Program");
}

System::Void JTester::FileBtn_Click(System::Object^  sender, System::EventArgs^  e) {
	if (OpenFileDialog->ShowDialog() == System::Windows::Forms::DialogResult::OK)
	{
		for each (String^ FileName in OpenFileDialog->FileNames) {
			FilesListBox->Items->Add(FileName, true);
		}
	}
}

System::Void JTester::FilesListBox_ItemCheck(System::Object^  sender, System::Windows::Forms::ItemCheckEventArgs^  e)
{
	System::Int32 i = FilesListBox->SelectedIndex;
	if (i < 0) return;
	System::String^ ChartName = GetChartName(FilesListBox->Items[i]->ToString(), i);
	if (DataChart->Series->FindByName(ChartName)) {
		DataChart->Series[ChartName]->Enabled = !FilesListBox->GetItemChecked(i);
	}
}

System::Void JTester::FullscreenButton_Click(System::Object^  sender, System::EventArgs^  e)
{
	using namespace System::Windows::Forms;
	if (FullscreenButton->Text == "Fullscreen") {
		FullscreenButton->Text = "Exit fullscreen";
		BodyLayout->ColumnStyles[0]->Width = 0;
		BodyLayout->RowStyles[0]->Height = 0;
	}
	else {
		FullscreenButton->Text = "Fullscreen";
		BodyLayout->ColumnStyles[0]->Width = 50;
		BodyLayout->RowStyles[0]->Height = 50;
	}
}

::std::string JTester::toSTD(System::String^ s)
{
	return msclr::interop::marshal_as<std::string>(s);
}

System::Void JTester::toolStripMenuItem3_Click(System::Object^  sender, System::EventArgs^  e)
{
	if (OpenInputDialog->ShowDialog() == System::Windows::Forms::DialogResult::OK)
	{
		InputFile = OpenInputDialog->FileName;
	}
}

