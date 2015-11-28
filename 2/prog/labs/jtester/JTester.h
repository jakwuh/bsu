#pragma once

#include <string>
#include <msclr\marshal_cppstd.h>
#include <stdexcept>
#include <ctime>
#include <map>
#include <Windows.h>
#include <ShlObj.h>
#include "math\definitions.h"
#include "math\linear_regression.h"
#include "math\logarithmic_regression.h"
#include "math\power_regression.h"
#include "math\quasilog_regression.h"

#pragma comment(lib, "shell32.lib")

namespace jtester {

	using namespace System;
	using namespace System::IO;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Collections::Generic;

	/// <summary>
	/// —водка дл€ JTester
	/// </summary>
	public ref class JTester : public System::Windows::Forms::Form
	{
	public:
		JTester(void)
		{
			InitializeComponent();
			//
			//TODO: добавьте код конструктора
			//
		}

	protected:
		/// <summary>
		/// ќсвободить все используемые ресурсы.
		/// </summary>
		~JTester()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::MenuStrip^  MenuBar;
	private: System::Windows::Forms::StatusStrip^  StatusBar;
	private: System::Windows::Forms::ToolStripStatusLabel^  StatusLabel;

	private: System::Windows::Forms::ToolStripMenuItem^  MenuToolStripMenuItem;
	private: System::Windows::Forms::ToolStripSeparator^  toolStripMenuItem1;
	private: System::Windows::Forms::ToolStripMenuItem^  exitToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  helpToolStripMenuItem;
	private: System::Windows::Forms::ToolStripSeparator^  toolStripMenuItem2;
	private: System::Windows::Forms::ToolStripMenuItem^  aboutToolStripMenuItem;
	private: System::Windows::Forms::TableLayoutPanel^  BodyLayout;
	private: System::Windows::Forms::RichTextBox^  StatsRichTextBox;



	private: System::Windows::Forms::OpenFileDialog^  OpenFileDialog;
	private: System::Windows::Forms::TableLayoutPanel^  FilechooseLayout;



	private: System::Windows::Forms::TextBox^  InfoTextbox;
	private: System::Windows::Forms::Button^  TestButton;

	private: System::Windows::Forms::ToolStripMenuItem^  aboutAuthorToolStripMenuItem;
	private: System::Windows::Forms::TableLayoutPanel^  tableLayoutPanel1;
	private: System::Windows::Forms::RichTextBox^  InputRichTextBox;

	private: System::Windows::Forms::RichTextBox^  NRichTextBox;
	private: System::Windows::Forms::Button^  FileBtn;
	private: System::Windows::Forms::TableLayoutPanel^  tableLayoutPanel2;
	private: System::Windows::Forms::DataVisualization::Charting::Chart^  DataChart;
	private: System::Windows::Forms::TableLayoutPanel^  tableLayoutPanel3;
	private: System::Windows::Forms::CheckedListBox^  FilesListBox;
	private: System::Windows::Forms::Button^  ClearFilesButton;
	private: System::Windows::Forms::Button^  FullscreenButton;
	private: System::Windows::Forms::ToolStripMenuItem^  toolStripMenuItem3;
	private: System::Windows::Forms::ToolStripProgressBar^  ProgressBar;
	private: System::Windows::Forms::OpenFileDialog^  OpenInputDialog;


	private:
		/// <summary>
		/// “ребуетс€ переменна€ конструктора.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// ќб€зательный метод дл€ поддержки конструктора - не измен€йте
		/// содержимое данного метода при помощи редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			System::Windows::Forms::DataVisualization::Charting::ChartArea^  chartArea4 = (gcnew System::Windows::Forms::DataVisualization::Charting::ChartArea());
			System::Windows::Forms::DataVisualization::Charting::Series^  series4 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			this->MenuBar = (gcnew System::Windows::Forms::MenuStrip());
			this->MenuToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolStripMenuItem3 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolStripMenuItem1 = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->exitToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->helpToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolStripMenuItem2 = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->aboutToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->aboutAuthorToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->StatusBar = (gcnew System::Windows::Forms::StatusStrip());
			this->StatusLabel = (gcnew System::Windows::Forms::ToolStripStatusLabel());
			this->ProgressBar = (gcnew System::Windows::Forms::ToolStripProgressBar());
			this->BodyLayout = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->StatsRichTextBox = (gcnew System::Windows::Forms::RichTextBox());
			this->FilechooseLayout = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->InfoTextbox = (gcnew System::Windows::Forms::TextBox());
			this->TestButton = (gcnew System::Windows::Forms::Button());
			this->FileBtn = (gcnew System::Windows::Forms::Button());
			this->tableLayoutPanel1 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->InputRichTextBox = (gcnew System::Windows::Forms::RichTextBox());
			this->NRichTextBox = (gcnew System::Windows::Forms::RichTextBox());
			this->tableLayoutPanel2 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->DataChart = (gcnew System::Windows::Forms::DataVisualization::Charting::Chart());
			this->tableLayoutPanel3 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->FilesListBox = (gcnew System::Windows::Forms::CheckedListBox());
			this->ClearFilesButton = (gcnew System::Windows::Forms::Button());
			this->FullscreenButton = (gcnew System::Windows::Forms::Button());
			this->OpenFileDialog = (gcnew System::Windows::Forms::OpenFileDialog());
			this->OpenInputDialog = (gcnew System::Windows::Forms::OpenFileDialog());
			this->MenuBar->SuspendLayout();
			this->StatusBar->SuspendLayout();
			this->BodyLayout->SuspendLayout();
			this->FilechooseLayout->SuspendLayout();
			this->tableLayoutPanel1->SuspendLayout();
			this->tableLayoutPanel2->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->DataChart))->BeginInit();
			this->tableLayoutPanel3->SuspendLayout();
			this->SuspendLayout();
			// 
			// MenuBar
			// 
			this->MenuBar->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->MenuToolStripMenuItem,
					this->helpToolStripMenuItem
			});
			this->MenuBar->Location = System::Drawing::Point(0, 0);
			this->MenuBar->Name = L"MenuBar";
			this->MenuBar->Size = System::Drawing::Size(584, 24);
			this->MenuBar->TabIndex = 0;
			this->MenuBar->Text = L"menuStrip1";
			// 
			// MenuToolStripMenuItem
			// 
			this->MenuToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {
				this->toolStripMenuItem3,
					this->toolStripMenuItem1, this->exitToolStripMenuItem
			});
			this->MenuToolStripMenuItem->Name = L"MenuToolStripMenuItem";
			this->MenuToolStripMenuItem->Size = System::Drawing::Size(50, 20);
			this->MenuToolStripMenuItem->Text = L"Menu";
			// 
			// toolStripMenuItem3
			// 
			this->toolStripMenuItem3->Name = L"toolStripMenuItem3";
			this->toolStripMenuItem3->Size = System::Drawing::Size(165, 22);
			this->toolStripMenuItem3->Text = L"Change input file";
			this->toolStripMenuItem3->Click += gcnew System::EventHandler(this, &JTester::toolStripMenuItem3_Click);
			// 
			// toolStripMenuItem1
			// 
			this->toolStripMenuItem1->Name = L"toolStripMenuItem1";
			this->toolStripMenuItem1->Size = System::Drawing::Size(162, 6);
			// 
			// exitToolStripMenuItem
			// 
			this->exitToolStripMenuItem->Name = L"exitToolStripMenuItem";
			this->exitToolStripMenuItem->Size = System::Drawing::Size(165, 22);
			this->exitToolStripMenuItem->Text = L"Exit";
			this->exitToolStripMenuItem->Click += gcnew System::EventHandler(this, &JTester::exitToolStripMenuItem_Click);
			// 
			// helpToolStripMenuItem
			// 
			this->helpToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {
				this->toolStripMenuItem2,
					this->aboutToolStripMenuItem, this->aboutAuthorToolStripMenuItem
			});
			this->helpToolStripMenuItem->Name = L"helpToolStripMenuItem";
			this->helpToolStripMenuItem->Size = System::Drawing::Size(44, 20);
			this->helpToolStripMenuItem->Text = L"Help";
			// 
			// toolStripMenuItem2
			// 
			this->toolStripMenuItem2->Name = L"toolStripMenuItem2";
			this->toolStripMenuItem2->Size = System::Drawing::Size(153, 6);
			// 
			// aboutToolStripMenuItem
			// 
			this->aboutToolStripMenuItem->Name = L"aboutToolStripMenuItem";
			this->aboutToolStripMenuItem->Size = System::Drawing::Size(156, 22);
			this->aboutToolStripMenuItem->Text = L"About Program";
			this->aboutToolStripMenuItem->Click += gcnew System::EventHandler(this, &JTester::aboutToolStripMenuItem_Click);
			// 
			// aboutAuthorToolStripMenuItem
			// 
			this->aboutAuthorToolStripMenuItem->Name = L"aboutAuthorToolStripMenuItem";
			this->aboutAuthorToolStripMenuItem->Size = System::Drawing::Size(156, 22);
			this->aboutAuthorToolStripMenuItem->Text = L"About Author";
			this->aboutAuthorToolStripMenuItem->Click += gcnew System::EventHandler(this, &JTester::aboutAuthorToolStripMenuItem_Click);
			// 
			// StatusBar
			// 
			this->StatusBar->AutoSize = false;
			this->StatusBar->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) { this->StatusLabel, this->ProgressBar });
			this->StatusBar->LayoutStyle = System::Windows::Forms::ToolStripLayoutStyle::HorizontalStackWithOverflow;
			this->StatusBar->Location = System::Drawing::Point(0, 339);
			this->StatusBar->Margin = System::Windows::Forms::Padding(3, 0, 3, 0);
			this->StatusBar->Name = L"StatusBar";
			this->StatusBar->Size = System::Drawing::Size(584, 22);
			this->StatusBar->TabIndex = 1;
			this->StatusBar->Text = L"statusStrip1";
			// 
			// StatusLabel
			// 
			this->StatusLabel->Name = L"StatusLabel";
			this->StatusLabel->Size = System::Drawing::Size(43, 17);
			this->StatusLabel->Text = L"JTester";
			// 
			// ProgressBar
			// 
			this->ProgressBar->Alignment = System::Windows::Forms::ToolStripItemAlignment::Right;
			this->ProgressBar->Name = L"ProgressBar";
			this->ProgressBar->Size = System::Drawing::Size(100, 16);
			this->ProgressBar->Step = 1;
			this->ProgressBar->Style = System::Windows::Forms::ProgressBarStyle::Continuous;
			this->ProgressBar->Visible = false;
			// 
			// BodyLayout
			// 
			this->BodyLayout->ColumnCount = 2;
			this->BodyLayout->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent, 50)));
			this->BodyLayout->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent, 50)));
			this->BodyLayout->Controls->Add(this->StatsRichTextBox, 0, 1);
			this->BodyLayout->Controls->Add(this->FilechooseLayout, 0, 0);
			this->BodyLayout->Controls->Add(this->tableLayoutPanel1, 1, 0);
			this->BodyLayout->Controls->Add(this->tableLayoutPanel2, 1, 1);
			this->BodyLayout->Dock = System::Windows::Forms::DockStyle::Fill;
			this->BodyLayout->Location = System::Drawing::Point(0, 24);
			this->BodyLayout->Name = L"BodyLayout";
			this->BodyLayout->RowCount = 2;
			this->BodyLayout->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 50)));
			this->BodyLayout->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 50)));
			this->BodyLayout->Size = System::Drawing::Size(584, 315);
			this->BodyLayout->TabIndex = 2;
			// 
			// StatsRichTextBox
			// 
			this->StatsRichTextBox->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->StatsRichTextBox->Dock = System::Windows::Forms::DockStyle::Fill;
			this->StatsRichTextBox->Location = System::Drawing::Point(3, 160);
			this->StatsRichTextBox->Name = L"StatsRichTextBox";
			this->StatsRichTextBox->ReadOnly = true;
			this->StatsRichTextBox->Size = System::Drawing::Size(286, 152);
			this->StatsRichTextBox->TabIndex = 0;
			this->StatsRichTextBox->TabStop = false;
			this->StatsRichTextBox->Text = L"";
			// 
			// FilechooseLayout
			// 
			this->FilechooseLayout->ColumnCount = 1;
			this->FilechooseLayout->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				100)));
			this->FilechooseLayout->Controls->Add(this->InfoTextbox, 0, 1);
			this->FilechooseLayout->Controls->Add(this->TestButton, 0, 2);
			this->FilechooseLayout->Controls->Add(this->FileBtn, 0, 0);
			this->FilechooseLayout->Dock = System::Windows::Forms::DockStyle::Fill;
			this->FilechooseLayout->Location = System::Drawing::Point(3, 3);
			this->FilechooseLayout->Name = L"FilechooseLayout";
			this->FilechooseLayout->RowCount = 3;
			this->FilechooseLayout->RowStyles->Add((gcnew System::Windows::Forms::RowStyle()));
			this->FilechooseLayout->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 100)));
			this->FilechooseLayout->RowStyles->Add((gcnew System::Windows::Forms::RowStyle()));
			this->FilechooseLayout->Size = System::Drawing::Size(286, 151);
			this->FilechooseLayout->TabIndex = 4;
			// 
			// InfoTextbox
			// 
			this->InfoTextbox->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->InfoTextbox->Dock = System::Windows::Forms::DockStyle::Fill;
			this->InfoTextbox->Location = System::Drawing::Point(3, 37);
			this->InfoTextbox->Multiline = true;
			this->InfoTextbox->Name = L"InfoTextbox";
			this->InfoTextbox->ReadOnly = true;
			this->InfoTextbox->Size = System::Drawing::Size(280, 77);
			this->InfoTextbox->TabIndex = 1;
			this->InfoTextbox->TabStop = false;
			this->InfoTextbox->Text = L"Enter input data in the right textbox\r\nEach new line - separate call of executabl"
				L"e file";
			// 
			// TestButton
			// 
			this->TestButton->Dock = System::Windows::Forms::DockStyle::Fill;
			this->TestButton->Location = System::Drawing::Point(3, 120);
			this->TestButton->Name = L"TestButton";
			this->TestButton->Size = System::Drawing::Size(280, 28);
			this->TestButton->TabIndex = 3;
			this->TestButton->Text = L"Test!";
			this->TestButton->UseVisualStyleBackColor = true;
			this->TestButton->Click += gcnew System::EventHandler(this, &JTester::TestButton_Click);
			// 
			// FileBtn
			// 
			this->FileBtn->AutoSize = true;
			this->FileBtn->Dock = System::Windows::Forms::DockStyle::Fill;
			this->FileBtn->Location = System::Drawing::Point(3, 3);
			this->FileBtn->Name = L"FileBtn";
			this->FileBtn->Size = System::Drawing::Size(280, 28);
			this->FileBtn->TabIndex = 0;
			this->FileBtn->Text = L"Click to choose executable";
			this->FileBtn->UseVisualStyleBackColor = true;
			this->FileBtn->Click += gcnew System::EventHandler(this, &JTester::FileBtn_Click);
			// 
			// tableLayoutPanel1
			// 
			this->tableLayoutPanel1->ColumnCount = 2;
			this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				30)));
			this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				70)));
			this->tableLayoutPanel1->Controls->Add(this->InputRichTextBox, 1, 0);
			this->tableLayoutPanel1->Controls->Add(this->NRichTextBox, 0, 0);
			this->tableLayoutPanel1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->tableLayoutPanel1->Location = System::Drawing::Point(295, 3);
			this->tableLayoutPanel1->Name = L"tableLayoutPanel1";
			this->tableLayoutPanel1->RowCount = 1;
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 100)));
			this->tableLayoutPanel1->Size = System::Drawing::Size(286, 151);
			this->tableLayoutPanel1->TabIndex = 5;
			// 
			// InputRichTextBox
			// 
			this->InputRichTextBox->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->InputRichTextBox->Dock = System::Windows::Forms::DockStyle::Fill;
			this->InputRichTextBox->Location = System::Drawing::Point(88, 3);
			this->InputRichTextBox->Name = L"InputRichTextBox";
			this->InputRichTextBox->Size = System::Drawing::Size(195, 145);
			this->InputRichTextBox->TabIndex = 2;
			this->InputRichTextBox->Text = L"[ Enter input ]";
			this->InputRichTextBox->WordWrap = false;
			// 
			// NRichTextBox
			// 
			this->NRichTextBox->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->NRichTextBox->Dock = System::Windows::Forms::DockStyle::Fill;
			this->NRichTextBox->Location = System::Drawing::Point(3, 3);
			this->NRichTextBox->Name = L"NRichTextBox";
			this->NRichTextBox->Size = System::Drawing::Size(79, 145);
			this->NRichTextBox->TabIndex = 1;
			this->NRichTextBox->Text = L"[ Enter N ]";
			// 
			// tableLayoutPanel2
			// 
			this->tableLayoutPanel2->ColumnCount = 2;
			this->tableLayoutPanel2->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				30)));
			this->tableLayoutPanel2->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				70)));
			this->tableLayoutPanel2->Controls->Add(this->DataChart, 1, 0);
			this->tableLayoutPanel2->Controls->Add(this->tableLayoutPanel3, 0, 0);
			this->tableLayoutPanel2->Dock = System::Windows::Forms::DockStyle::Fill;
			this->tableLayoutPanel2->Location = System::Drawing::Point(295, 160);
			this->tableLayoutPanel2->Name = L"tableLayoutPanel2";
			this->tableLayoutPanel2->RowCount = 1;
			this->tableLayoutPanel2->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 100)));
			this->tableLayoutPanel2->Size = System::Drawing::Size(286, 152);
			this->tableLayoutPanel2->TabIndex = 6;
			// 
			// DataChart
			// 
			chartArea4->Name = L"ChartArea1";
			this->DataChart->ChartAreas->Add(chartArea4);
			this->DataChart->Dock = System::Windows::Forms::DockStyle::Fill;
			this->DataChart->Location = System::Drawing::Point(88, 3);
			this->DataChart->Name = L"DataChart";
			series4->ChartArea = L"ChartArea1";
			series4->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Spline;
			series4->MarkerColor = System::Drawing::Color::Black;
			series4->Name = L"Default";
			this->DataChart->Series->Add(series4);
			this->DataChart->Size = System::Drawing::Size(195, 146);
			this->DataChart->TabIndex = 4;
			this->DataChart->TabStop = false;
			this->DataChart->Text = L"chart1";
			// 
			// tableLayoutPanel3
			// 
			this->tableLayoutPanel3->ColumnCount = 1;
			this->tableLayoutPanel3->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				100)));
			this->tableLayoutPanel3->Controls->Add(this->FilesListBox, 0, 0);
			this->tableLayoutPanel3->Controls->Add(this->ClearFilesButton, 0, 2);
			this->tableLayoutPanel3->Controls->Add(this->FullscreenButton, 0, 1);
			this->tableLayoutPanel3->Dock = System::Windows::Forms::DockStyle::Fill;
			this->tableLayoutPanel3->Location = System::Drawing::Point(0, 0);
			this->tableLayoutPanel3->Margin = System::Windows::Forms::Padding(0);
			this->tableLayoutPanel3->Name = L"tableLayoutPanel3";
			this->tableLayoutPanel3->RowCount = 3;
			this->tableLayoutPanel3->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 100)));
			this->tableLayoutPanel3->RowStyles->Add((gcnew System::Windows::Forms::RowStyle()));
			this->tableLayoutPanel3->RowStyles->Add((gcnew System::Windows::Forms::RowStyle()));
			this->tableLayoutPanel3->Size = System::Drawing::Size(85, 152);
			this->tableLayoutPanel3->TabIndex = 5;
			// 
			// FilesListBox
			// 
			this->FilesListBox->CheckOnClick = true;
			this->FilesListBox->Dock = System::Windows::Forms::DockStyle::Fill;
			this->FilesListBox->FormattingEnabled = true;
			this->FilesListBox->Location = System::Drawing::Point(3, 3);
			this->FilesListBox->Name = L"FilesListBox";
			this->FilesListBox->RightToLeft = System::Windows::Forms::RightToLeft::Yes;
			this->FilesListBox->Size = System::Drawing::Size(79, 78);
			this->FilesListBox->TabIndex = 6;
			this->FilesListBox->TabStop = false;
			this->FilesListBox->ItemCheck += gcnew System::Windows::Forms::ItemCheckEventHandler(this, &JTester::FilesListBox_ItemCheck);
			// 
			// ClearFilesButton
			// 
			this->ClearFilesButton->Dock = System::Windows::Forms::DockStyle::Fill;
			this->ClearFilesButton->Location = System::Drawing::Point(3, 121);
			this->ClearFilesButton->Name = L"ClearFilesButton";
			this->ClearFilesButton->Size = System::Drawing::Size(79, 28);
			this->ClearFilesButton->TabIndex = 5;
			this->ClearFilesButton->Text = L"Clear all";
			this->ClearFilesButton->UseVisualStyleBackColor = true;
			this->ClearFilesButton->Click += gcnew System::EventHandler(this, &JTester::ClearFilesButton_Click);
			// 
			// FullscreenButton
			// 
			this->FullscreenButton->Dock = System::Windows::Forms::DockStyle::Fill;
			this->FullscreenButton->Location = System::Drawing::Point(3, 87);
			this->FullscreenButton->Name = L"FullscreenButton";
			this->FullscreenButton->Size = System::Drawing::Size(79, 28);
			this->FullscreenButton->TabIndex = 4;
			this->FullscreenButton->Text = L"Fullscreen";
			this->FullscreenButton->UseVisualStyleBackColor = true;
			this->FullscreenButton->Click += gcnew System::EventHandler(this, &JTester::FullscreenButton_Click);
			// 
			// OpenFileDialog
			// 
			this->OpenFileDialog->DefaultExt = L"exe";
			this->OpenFileDialog->Filter = L"Executable file|*.exe";
			this->OpenFileDialog->Multiselect = true;
			// 
			// OpenInputDialog
			// 
			this->OpenInputDialog->FileName = L"input.txt";
			// 
			// JTester
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(584, 361);
			this->Controls->Add(this->BodyLayout);
			this->Controls->Add(this->StatusBar);
			this->Controls->Add(this->MenuBar);
			this->MainMenuStrip = this->MenuBar;
			this->MinimumSize = System::Drawing::Size(600, 400);
			this->Name = L"JTester";
			this->Text = L"JTester";
			this->Load += gcnew System::EventHandler(this, &JTester::JTester_Load);
			this->MenuBar->ResumeLayout(false);
			this->MenuBar->PerformLayout();
			this->StatusBar->ResumeLayout(false);
			this->StatusBar->PerformLayout();
			this->BodyLayout->ResumeLayout(false);
			this->FilechooseLayout->ResumeLayout(false);
			this->FilechooseLayout->PerformLayout();
			this->tableLayoutPanel1->ResumeLayout(false);
			this->tableLayoutPanel2->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->DataChart))->EndInit();
			this->tableLayoutPanel3->ResumeLayout(false);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

private:
	ref struct Execution
	{
		Execution(String^ File_, String^ InputFile_, String^ Input_, String^ ChartName_, Double N_) 
		: File(File_), InputFile(InputFile_), Input(Input_), ChartName(ChartName_), N(N_) {};
		String^ File;
		String^ InputFile;
		String^ Input;
		String^ ChartName;
		Double N;
	};

private: Generic::Queue< Generic::Queue< Execution^ >^ > Series;
private: IO::StreamWriter^ log;
private: System::String^ InputFile;

private: System::Void exitToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) { Application::Exit(); }
private: System::Void TestButton_Click(System::Object^  sender, System::EventArgs^  e) { Test(); }
private: System::Void aboutAuthorToolStripMenuItem_Click(System::Object^, System::EventArgs^);
private: System::Void aboutToolStripMenuItem_Click(System::Object^, System::EventArgs^);
private: System::Void FileBtn_Click(System::Object^, System::EventArgs^);
private: System::Void FilesListBox_ItemCheck(System::Object^  sender, System::Windows::Forms::ItemCheckEventArgs^  e);
private: System::Void FullscreenButton_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void toolStripMenuItem3_Click(System::Object^  sender, System::EventArgs^  e);

private: System::Void Test();
private: System::Void Execute();
private: System::Void Log(System::String^);
private: System::Void Status(System::String^);
private: System::Void Regress(::Math::Regression*, ::Math::Regression*&);
private: System::String^ GetChartName(System::String^, System::Int32);
private: std::string toSTD(System::String^);

private: System::Void ClearFilesButton_Click(System::Object^  sender, System::EventArgs^  e) {
	FilesListBox->Items->Clear();
}

private: System::Void JTester_Load(System::Object^  sender, System::EventArgs^  e) {
	InputFile = "input.txt";
	setlocale(LC_ALL, "en");
}
};
}
