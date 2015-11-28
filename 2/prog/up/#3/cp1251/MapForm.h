#pragma once

#include <string>
#include <map>
#include <algorithm>
#include <msclr\marshal_cppstd.h>

namespace up {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	typedef std::pair<std::string, int> mappair;

	struct MapCmp {
		bool operator ()(std::string a, std::string b) {
			return b < a;
		}
	} mapcmp;

	std::multimap<std::string, int, MapCmp> map1, map2;

	/// <summary>
	/// Сводка для MapForm
	/// </summary>
	public ref class MapForm : public System::Windows::Forms::Form
	{
	public:
		MapForm(void)
		{
			InitializeComponent();
			//
			//TODO: добавьте код конструктора
			//
		}

	protected:
		/// <summary>
		/// Освободить все используемые ресурсы.
		/// </summary>
		~MapForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::StatusStrip^  statusStrip1;
	protected:
	private: System::Windows::Forms::ToolStripStatusLabel^  toolStripStatusLabel1;
	private: System::Windows::Forms::TableLayoutPanel^  tableLayoutPanel1;
	private: System::Windows::Forms::FlowLayoutPanel^  flowLayoutPanel1;
	private: System::Windows::Forms::FlowLayoutPanel^  flowLayoutPanel2;
	private: System::Windows::Forms::FlowLayoutPanel^  flowLayoutPanel3;
	private: System::Windows::Forms::Button^  button1;
	private: System::Windows::Forms::Button^  button2;
	private: System::Windows::Forms::FlowLayoutPanel^  flowLayoutPanel4;
	private: System::Windows::Forms::Button^  button8;
	private: System::Windows::Forms::Button^  button9;

	private: System::Windows::Forms::TableLayoutPanel^  tableLayoutPanel3;
	private: System::Windows::Forms::TextBox^  textBox4;
	private: System::Windows::Forms::Button^  button4;
	private: System::Windows::Forms::TextBox^  textBox5;
	private: System::Windows::Forms::Button^  button11;
	private: System::Windows::Forms::TextBox^  textBox6;
	private: System::Windows::Forms::MaskedTextBox^  maskedTextBox2;
	private: System::Windows::Forms::Button^  button7;
	private: System::Windows::Forms::TableLayoutPanel^  tableLayoutPanel4;
	private: System::Windows::Forms::TextBox^  textBox8;
	private: System::Windows::Forms::Button^  button5;
	private: System::Windows::Forms::TextBox^  textBox7;

	private: System::Windows::Forms::TableLayoutPanel^  tableLayoutPanel2;
	private: System::Windows::Forms::TextBox^  textBox3;
	private: System::Windows::Forms::Button^  button13;
	private: System::Windows::Forms::TextBox^  textBox2;
	private: System::Windows::Forms::Button^  button10;
	private: System::Windows::Forms::TextBox^  textBox1;
	private: System::Windows::Forms::MaskedTextBox^  maskedTextBox1;
	private:
		/// <summary>
		/// Требуется переменная конструктора.
		/// </summary>
		System::Collections::ArrayList^ buttons1;
		System::Collections::ArrayList^ buttons2;
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Обязательный метод для поддержки конструктора - не изменяйте
		/// содержимое данного метода при помощи редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			this->statusStrip1 = (gcnew System::Windows::Forms::StatusStrip());
			this->toolStripStatusLabel1 = (gcnew System::Windows::Forms::ToolStripStatusLabel());
			this->tableLayoutPanel1 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->flowLayoutPanel1 = (gcnew System::Windows::Forms::FlowLayoutPanel());
			this->flowLayoutPanel2 = (gcnew System::Windows::Forms::FlowLayoutPanel());
			this->flowLayoutPanel3 = (gcnew System::Windows::Forms::FlowLayoutPanel());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->tableLayoutPanel3 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->textBox4 = (gcnew System::Windows::Forms::TextBox());
			this->button4 = (gcnew System::Windows::Forms::Button());
			this->textBox5 = (gcnew System::Windows::Forms::TextBox());
			this->button11 = (gcnew System::Windows::Forms::Button());
			this->textBox6 = (gcnew System::Windows::Forms::TextBox());
			this->maskedTextBox2 = (gcnew System::Windows::Forms::MaskedTextBox());
			this->button7 = (gcnew System::Windows::Forms::Button());
			this->tableLayoutPanel4 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->textBox8 = (gcnew System::Windows::Forms::TextBox());
			this->button5 = (gcnew System::Windows::Forms::Button());
			this->textBox7 = (gcnew System::Windows::Forms::TextBox());
			this->flowLayoutPanel4 = (gcnew System::Windows::Forms::FlowLayoutPanel());
			this->button8 = (gcnew System::Windows::Forms::Button());
			this->button9 = (gcnew System::Windows::Forms::Button());
			this->tableLayoutPanel2 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->textBox3 = (gcnew System::Windows::Forms::TextBox());
			this->button13 = (gcnew System::Windows::Forms::Button());
			this->textBox2 = (gcnew System::Windows::Forms::TextBox());
			this->button10 = (gcnew System::Windows::Forms::Button());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->maskedTextBox1 = (gcnew System::Windows::Forms::MaskedTextBox());
			this->statusStrip1->SuspendLayout();
			this->tableLayoutPanel1->SuspendLayout();
			this->flowLayoutPanel3->SuspendLayout();
			this->tableLayoutPanel3->SuspendLayout();
			this->tableLayoutPanel4->SuspendLayout();
			this->flowLayoutPanel4->SuspendLayout();
			this->tableLayoutPanel2->SuspendLayout();
			this->SuspendLayout();
			// 
			// statusStrip1
			// 
			this->statusStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->toolStripStatusLabel1 });
			this->statusStrip1->Location = System::Drawing::Point(0, 438);
			this->statusStrip1->Name = L"statusStrip1";
			this->statusStrip1->Size = System::Drawing::Size(617, 22);
			this->statusStrip1->TabIndex = 0;
			this->statusStrip1->Text = L"statusStrip1";
			// 
			// toolStripStatusLabel1
			// 
			this->toolStripStatusLabel1->Name = L"toolStripStatusLabel1";
			this->toolStripStatusLabel1->Size = System::Drawing::Size(255, 17);
			this->toolStripStatusLabel1->Text = L"Author: James Akwuh, BSU FAMI, 28 June, 2015";
			// 
			// tableLayoutPanel1
			// 
			this->tableLayoutPanel1->ColumnCount = 2;
			this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				50)));
			this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				50)));
			this->tableLayoutPanel1->Controls->Add(this->flowLayoutPanel1, 0, 0);
			this->tableLayoutPanel1->Controls->Add(this->flowLayoutPanel2, 1, 0);
			this->tableLayoutPanel1->Controls->Add(this->flowLayoutPanel3, 0, 1);
			this->tableLayoutPanel1->Controls->Add(this->flowLayoutPanel4, 1, 1);
			this->tableLayoutPanel1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->tableLayoutPanel1->Location = System::Drawing::Point(0, 0);
			this->tableLayoutPanel1->Name = L"tableLayoutPanel1";
			this->tableLayoutPanel1->RowCount = 2;
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 37.67123F)));
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 62.32877F)));
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 20)));
			this->tableLayoutPanel1->Size = System::Drawing::Size(617, 438);
			this->tableLayoutPanel1->TabIndex = 1;
			// 
			// flowLayoutPanel1
			// 
			this->flowLayoutPanel1->BackColor = System::Drawing::SystemColors::ControlLightLight;
			this->flowLayoutPanel1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->flowLayoutPanel1->Location = System::Drawing::Point(3, 3);
			this->flowLayoutPanel1->Name = L"flowLayoutPanel1";
			this->flowLayoutPanel1->Size = System::Drawing::Size(302, 158);
			this->flowLayoutPanel1->TabIndex = 1;
			// 
			// flowLayoutPanel2
			// 
			this->flowLayoutPanel2->BackColor = System::Drawing::SystemColors::ControlLightLight;
			this->flowLayoutPanel2->Dock = System::Windows::Forms::DockStyle::Fill;
			this->flowLayoutPanel2->Location = System::Drawing::Point(311, 3);
			this->flowLayoutPanel2->Name = L"flowLayoutPanel2";
			this->flowLayoutPanel2->Size = System::Drawing::Size(303, 158);
			this->flowLayoutPanel2->TabIndex = 2;
			// 
			// flowLayoutPanel3
			// 
			this->flowLayoutPanel3->Controls->Add(this->button1);
			this->flowLayoutPanel3->Controls->Add(this->button2);
			this->flowLayoutPanel3->Controls->Add(this->tableLayoutPanel3);
			this->flowLayoutPanel3->Controls->Add(this->button7);
			this->flowLayoutPanel3->Controls->Add(this->tableLayoutPanel4);
			this->flowLayoutPanel3->Dock = System::Windows::Forms::DockStyle::Fill;
			this->flowLayoutPanel3->Location = System::Drawing::Point(3, 167);
			this->flowLayoutPanel3->Name = L"flowLayoutPanel3";
			this->flowLayoutPanel3->Size = System::Drawing::Size(302, 268);
			this->flowLayoutPanel3->TabIndex = 3;
			// 
			// button1
			// 
			this->button1->Dock = System::Windows::Forms::DockStyle::Top;
			this->button1->Location = System::Drawing::Point(3, 3);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(302, 23);
			this->button1->TabIndex = 4;
			this->button1->Text = L"Сгенерировать элементы";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &MapForm::button1_Click);
			// 
			// button2
			// 
			this->button2->Dock = System::Windows::Forms::DockStyle::Top;
			this->button2->Location = System::Drawing::Point(3, 32);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(302, 23);
			this->button2->TabIndex = 5;
			this->button2->Text = L"Скопировать из другого отображения";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &MapForm::button2_Click);
			// 
			// tableLayoutPanel3
			// 
			this->tableLayoutPanel3->ColumnCount = 2;
			this->tableLayoutPanel3->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				50)));
			this->tableLayoutPanel3->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				50)));
			this->tableLayoutPanel3->Controls->Add(this->textBox4, 0, 2);
			this->tableLayoutPanel3->Controls->Add(this->button4, 1, 1);
			this->tableLayoutPanel3->Controls->Add(this->textBox5, 0, 1);
			this->tableLayoutPanel3->Controls->Add(this->button11, 1, 0);
			this->tableLayoutPanel3->Controls->Add(this->textBox6, 0, 0);
			this->tableLayoutPanel3->Controls->Add(this->maskedTextBox2, 1, 2);
			this->tableLayoutPanel3->Dock = System::Windows::Forms::DockStyle::Top;
			this->tableLayoutPanel3->Location = System::Drawing::Point(3, 61);
			this->tableLayoutPanel3->Name = L"tableLayoutPanel3";
			this->tableLayoutPanel3->RowCount = 3;
			this->tableLayoutPanel3->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 50)));
			this->tableLayoutPanel3->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 50)));
			this->tableLayoutPanel3->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 27)));
			this->tableLayoutPanel3->Size = System::Drawing::Size(285, 85);
			this->tableLayoutPanel3->TabIndex = 17;
			// 
			// textBox4
			// 
			this->textBox4->Dock = System::Windows::Forms::DockStyle::Fill;
			this->textBox4->Location = System::Drawing::Point(3, 61);
			this->textBox4->Name = L"textBox4";
			this->textBox4->Size = System::Drawing::Size(136, 20);
			this->textBox4->TabIndex = 12;
			// 
			// button4
			// 
			this->button4->Dock = System::Windows::Forms::DockStyle::Fill;
			this->button4->Location = System::Drawing::Point(145, 32);
			this->button4->Name = L"button4";
			this->button4->Size = System::Drawing::Size(137, 23);
			this->button4->TabIndex = 11;
			this->button4->Text = L"Заменить/Добавить";
			this->button4->UseVisualStyleBackColor = true;
			this->button4->Click += gcnew System::EventHandler(this, &MapForm::button4_Click);
			// 
			// textBox5
			// 
			this->textBox5->Dock = System::Windows::Forms::DockStyle::Fill;
			this->textBox5->Location = System::Drawing::Point(3, 32);
			this->textBox5->Name = L"textBox5";
			this->textBox5->Size = System::Drawing::Size(136, 20);
			this->textBox5->TabIndex = 9;
			// 
			// button11
			// 
			this->button11->Dock = System::Windows::Forms::DockStyle::Fill;
			this->button11->Location = System::Drawing::Point(145, 3);
			this->button11->Name = L"button11";
			this->button11->Size = System::Drawing::Size(137, 23);
			this->button11->TabIndex = 8;
			this->button11->Text = L"Удалить элемент";
			this->button11->UseVisualStyleBackColor = true;
			this->button11->Click += gcnew System::EventHandler(this, &MapForm::button11_Click);
			// 
			// textBox6
			// 
			this->textBox6->Dock = System::Windows::Forms::DockStyle::Fill;
			this->textBox6->Location = System::Drawing::Point(3, 3);
			this->textBox6->Name = L"textBox6";
			this->textBox6->Size = System::Drawing::Size(136, 20);
			this->textBox6->TabIndex = 0;
			// 
			// maskedTextBox2
			// 
			this->maskedTextBox2->Location = System::Drawing::Point(145, 61);
			this->maskedTextBox2->Mask = L"000";
			this->maskedTextBox2->Name = L"maskedTextBox2";
			this->maskedTextBox2->Size = System::Drawing::Size(100, 20);
			this->maskedTextBox2->TabIndex = 13;
			// 
			// button7
			// 
			this->button7->Dock = System::Windows::Forms::DockStyle::Top;
			this->button7->Location = System::Drawing::Point(3, 152);
			this->button7->Name = L"button7";
			this->button7->Size = System::Drawing::Size(302, 23);
			this->button7->TabIndex = 19;
			this->button7->Text = L"Сравнить отображения";
			this->button7->UseVisualStyleBackColor = true;
			this->button7->Click += gcnew System::EventHandler(this, &MapForm::button7_Click);
			// 
			// tableLayoutPanel4
			// 
			this->tableLayoutPanel4->ColumnCount = 3;
			this->tableLayoutPanel4->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute,
				90)));
			this->tableLayoutPanel4->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute,
				90)));
			this->tableLayoutPanel4->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute,
				119)));
			this->tableLayoutPanel4->Controls->Add(this->textBox8, 2, 0);
			this->tableLayoutPanel4->Controls->Add(this->button5, 1, 0);
			this->tableLayoutPanel4->Controls->Add(this->textBox7, 0, 0);
			this->tableLayoutPanel4->Dock = System::Windows::Forms::DockStyle::Top;
			this->tableLayoutPanel4->Location = System::Drawing::Point(3, 181);
			this->tableLayoutPanel4->Name = L"tableLayoutPanel4";
			this->tableLayoutPanel4->RowCount = 1;
			this->tableLayoutPanel4->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 100)));
			this->tableLayoutPanel4->Size = System::Drawing::Size(299, 28);
			this->tableLayoutPanel4->TabIndex = 20;
			// 
			// textBox8
			// 
			this->textBox8->Dock = System::Windows::Forms::DockStyle::Fill;
			this->textBox8->Location = System::Drawing::Point(183, 3);
			this->textBox8->Name = L"textBox8";
			this->textBox8->Size = System::Drawing::Size(113, 20);
			this->textBox8->TabIndex = 20;
			// 
			// button5
			// 
			this->button5->Dock = System::Windows::Forms::DockStyle::Top;
			this->button5->Location = System::Drawing::Point(93, 3);
			this->button5->Name = L"button5";
			this->button5->Size = System::Drawing::Size(84, 22);
			this->button5->TabIndex = 19;
			this->button5->Text = L"Обменять на";
			this->button5->UseVisualStyleBackColor = true;
			this->button5->Click += gcnew System::EventHandler(this, &MapForm::button5_Click);
			// 
			// textBox7
			// 
			this->textBox7->Dock = System::Windows::Forms::DockStyle::Fill;
			this->textBox7->Location = System::Drawing::Point(3, 3);
			this->textBox7->Name = L"textBox7";
			this->textBox7->Size = System::Drawing::Size(84, 20);
			this->textBox7->TabIndex = 0;
			// 
			// flowLayoutPanel4
			// 
			this->flowLayoutPanel4->Controls->Add(this->button8);
			this->flowLayoutPanel4->Controls->Add(this->button9);
			this->flowLayoutPanel4->Controls->Add(this->tableLayoutPanel2);
			this->flowLayoutPanel4->Dock = System::Windows::Forms::DockStyle::Fill;
			this->flowLayoutPanel4->Location = System::Drawing::Point(311, 167);
			this->flowLayoutPanel4->Name = L"flowLayoutPanel4";
			this->flowLayoutPanel4->Size = System::Drawing::Size(303, 268);
			this->flowLayoutPanel4->TabIndex = 4;
			// 
			// button8
			// 
			this->button8->Dock = System::Windows::Forms::DockStyle::Top;
			this->button8->Location = System::Drawing::Point(3, 3);
			this->button8->Name = L"button8";
			this->button8->Size = System::Drawing::Size(302, 23);
			this->button8->TabIndex = 5;
			this->button8->Text = L"Сгенерировать элементы";
			this->button8->UseVisualStyleBackColor = true;
			this->button8->Click += gcnew System::EventHandler(this, &MapForm::button8_Click);
			// 
			// button9
			// 
			this->button9->Dock = System::Windows::Forms::DockStyle::Top;
			this->button9->Location = System::Drawing::Point(3, 32);
			this->button9->Name = L"button9";
			this->button9->Size = System::Drawing::Size(302, 23);
			this->button9->TabIndex = 6;
			this->button9->Text = L"Скопировать из другого отображения";
			this->button9->UseVisualStyleBackColor = true;
			this->button9->Click += gcnew System::EventHandler(this, &MapForm::button9_Click);
			// 
			// tableLayoutPanel2
			// 
			this->tableLayoutPanel2->ColumnCount = 2;
			this->tableLayoutPanel2->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				50)));
			this->tableLayoutPanel2->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				50)));
			this->tableLayoutPanel2->Controls->Add(this->textBox3, 0, 2);
			this->tableLayoutPanel2->Controls->Add(this->button13, 1, 1);
			this->tableLayoutPanel2->Controls->Add(this->textBox2, 0, 1);
			this->tableLayoutPanel2->Controls->Add(this->button10, 1, 0);
			this->tableLayoutPanel2->Controls->Add(this->textBox1, 0, 0);
			this->tableLayoutPanel2->Controls->Add(this->maskedTextBox1, 1, 2);
			this->tableLayoutPanel2->Dock = System::Windows::Forms::DockStyle::Top;
			this->tableLayoutPanel2->Location = System::Drawing::Point(3, 61);
			this->tableLayoutPanel2->Name = L"tableLayoutPanel2";
			this->tableLayoutPanel2->RowCount = 3;
			this->tableLayoutPanel2->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 50)));
			this->tableLayoutPanel2->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 50)));
			this->tableLayoutPanel2->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 27)));
			this->tableLayoutPanel2->Size = System::Drawing::Size(285, 85);
			this->tableLayoutPanel2->TabIndex = 14;
			// 
			// textBox3
			// 
			this->textBox3->Dock = System::Windows::Forms::DockStyle::Fill;
			this->textBox3->Location = System::Drawing::Point(3, 61);
			this->textBox3->Name = L"textBox3";
			this->textBox3->Size = System::Drawing::Size(136, 20);
			this->textBox3->TabIndex = 12;
			// 
			// button13
			// 
			this->button13->Dock = System::Windows::Forms::DockStyle::Fill;
			this->button13->Location = System::Drawing::Point(145, 32);
			this->button13->Name = L"button13";
			this->button13->Size = System::Drawing::Size(137, 23);
			this->button13->TabIndex = 11;
			this->button13->Text = L"Заменить/Добавить";
			this->button13->UseVisualStyleBackColor = true;
			this->button13->Click += gcnew System::EventHandler(this, &MapForm::button13_Click);
			// 
			// textBox2
			// 
			this->textBox2->Dock = System::Windows::Forms::DockStyle::Fill;
			this->textBox2->Location = System::Drawing::Point(3, 32);
			this->textBox2->Name = L"textBox2";
			this->textBox2->Size = System::Drawing::Size(136, 20);
			this->textBox2->TabIndex = 9;
			// 
			// button10
			// 
			this->button10->Dock = System::Windows::Forms::DockStyle::Fill;
			this->button10->Location = System::Drawing::Point(145, 3);
			this->button10->Name = L"button10";
			this->button10->Size = System::Drawing::Size(137, 23);
			this->button10->TabIndex = 8;
			this->button10->Text = L"Удалить элемент";
			this->button10->UseVisualStyleBackColor = true;
			this->button10->Click += gcnew System::EventHandler(this, &MapForm::button10_Click);
			// 
			// textBox1
			// 
			this->textBox1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->textBox1->Location = System::Drawing::Point(3, 3);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(136, 20);
			this->textBox1->TabIndex = 0;
			// 
			// maskedTextBox1
			// 
			this->maskedTextBox1->Location = System::Drawing::Point(145, 61);
			this->maskedTextBox1->Mask = L"000";
			this->maskedTextBox1->Name = L"maskedTextBox1";
			this->maskedTextBox1->Size = System::Drawing::Size(100, 20);
			this->maskedTextBox1->TabIndex = 13;
			// 
			// MapForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(617, 460);
			this->Controls->Add(this->tableLayoutPanel1);
			this->Controls->Add(this->statusStrip1);
			this->Name = L"MapForm";
			this->Text = L"MultiMap Example";
			this->Load += gcnew System::EventHandler(this, &MapForm::MapForm_Load);
			this->statusStrip1->ResumeLayout(false);
			this->statusStrip1->PerformLayout();
			this->tableLayoutPanel1->ResumeLayout(false);
			this->flowLayoutPanel3->ResumeLayout(false);
			this->tableLayoutPanel3->ResumeLayout(false);
			this->tableLayoutPanel3->PerformLayout();
			this->tableLayoutPanel4->ResumeLayout(false);
			this->tableLayoutPanel4->PerformLayout();
			this->flowLayoutPanel4->ResumeLayout(false);
			this->tableLayoutPanel2->ResumeLayout(false);
			this->tableLayoutPanel2->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

private: System::Void show(){
	for each(System::Object^ obj in buttons1) delete obj;
	for each(System::Object^ obj in buttons2) delete obj;
	buttons1->Clear();
	buttons2->Clear();
	for (auto it : map1) {
		System::Windows::Forms::Button^ button = gcnew System::Windows::Forms::Button();
		button->Dock = System::Windows::Forms::DockStyle::None;
		buttons1->Count;
		button->Name = L"buttons1" + Convert::ToString(buttons1->Count + 100);
		button->AutoSize = true;
		button->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowOnly;
		button->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
		button->Height = 24;
		button->Width = 24;
		button->UseVisualStyleBackColor = true;
		button->Text = gcnew String((it.first + " - " + std::to_string(it.second)).c_str());
		flowLayoutPanel1->Controls->Add(button);
		buttons1->Add(button);
	}
	for (auto it : map2) {
		System::Windows::Forms::Button^ button = gcnew System::Windows::Forms::Button();
		button->Dock = System::Windows::Forms::DockStyle::None;
		buttons2->Count;
		button->Name = L"buttons2" + Convert::ToString(buttons2->Count + 100);
		button->AutoSize = true;
		button->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowOnly;
		button->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
		button->Height = 24;
		button->Width = 24;
		button->UseVisualStyleBackColor = true;
		button->Text = gcnew String((it.first + " - " + std::to_string(it.second)).c_str());
		flowLayoutPanel2->Controls->Add(button);
		buttons2->Add(button);
	}
}

private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
	map1.clear();
	map1.insert(mappair("James", 19));
	map1.insert(mappair("Marina", 18));
	map1.insert(mappair("Denis", 18));
	map1.insert(mappair("Vladimir", 20));
	show();
}
private: System::Void button8_Click(System::Object^  sender, System::EventArgs^  e) {
	map2.clear();
	map2.insert(mappair("James", 19));
	map2.insert(mappair("Marina", 18));
	map2.insert(mappair("Denis", 18));
	map2.insert(mappair("Vladimir", 20));
	show();
}
private: System::Void button2_Click(System::Object^  sender, System::EventArgs^  e) {
	 map1 = map2;
	show();
}
private: System::Void button9_Click(System::Object^  sender, System::EventArgs^  e) {
	 map2 = map1;
	show();
}
private: System::Void button3_Click(System::Object^  sender, System::EventArgs^  e) {

}

private: System::Void button6_Click(System::Object^  sender, System::EventArgs^  e) {
	show();
}
private: System::Void button3_Click_1(System::Object^  sender, System::EventArgs^  e) {
	show();
}
private: System::Void button11_Click(System::Object^  sender, System::EventArgs^  e) {
	 String^ text = textBox6->Text->ToString();
	 map1.erase(msclr::interop::marshal_as<std::string>(text));
	show();
}
private: System::Void button10_Click(System::Object^  sender, System::EventArgs^  e) {
	 String^ text = textBox1->Text->ToString();
	 map2.erase(msclr::interop::marshal_as<std::string>(text));
	show();
}
private: System::Void button4_Click(System::Object^  sender, System::EventArgs^  e) {
	 String^ find = textBox5->Text->ToString();
	 String^ newName = textBox4->Text->ToString();
	 int age = Convert::ToInt32(maskedTextBox2->Text);
	 int count = map1.erase(msclr::interop::marshal_as<std::string>(find));
	 if (count == 0) count = 1;
	 for (int i = 0; i < count; ++i) {
		map1.insert(mappair(msclr::interop::marshal_as<std::string>(newName), age));
	 }
	show();
}
private: System::Void button13_Click(System::Object^  sender, System::EventArgs^  e) {
	 String^ find = textBox2->Text->ToString();
	 String^ newName = textBox3->Text->ToString();
	 int age = Convert::ToInt32(maskedTextBox1->Text);
	 int count = map2.erase(msclr::interop::marshal_as<std::string>(find));
	 if (count == 0) count = 1;
	 for (int i = 0; i < count; ++i) {
		map2.insert(mappair(msclr::interop::marshal_as<std::string>(newName), age));
	 }
	show();
}
private: System::Void button7_Click(System::Object^  sender, System::EventArgs^  e) {
	 if (map1 == map2) MessageBox::Show("Multimaps are equal");
	 else MessageBox::Show("Multimaps differ");
}
private: System::Void button5_Click(System::Object^  sender, System::EventArgs^  e) {
	 String^ first = textBox7->Text->ToString();
	 String^ second = textBox8->Text->ToString();
	 auto it1 = map1.find(msclr::interop::marshal_as<std::string>(first));
	 auto it2 = map2.find(msclr::interop::marshal_as<std::string>(second));
	 if (it1 != map1.end() && it2 != map2.end()) {
		map1.insert(mappair(it2->first, it2->second));
		map2.insert(mappair(it1->first, it1->second));
	 	map1.erase(it1);
	 	map2.erase(it2);
	 }
	 show();
}
private: System::Void MapForm_Load(System::Object^  sender, System::EventArgs^  e) {
	this->buttons1 = gcnew System::Collections::ArrayList;
	this->buttons2 = gcnew System::Collections::ArrayList;
}
};
}
