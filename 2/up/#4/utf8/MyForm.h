#pragma once

#include "stack.h"

namespace up {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Сводка для MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			stackInt = 0;
			stackChar = 0;
			stackDouble = 0;
			//
			//TODO: добавьте код конструктора
			//
		}

	protected:
		/// <summary>
		/// Освободить все используемые ресурсы.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^  button1;
	protected:
	private: System::Windows::Forms::TableLayoutPanel^  tableLayoutPanel1;
	private: System::Windows::Forms::FlowLayoutPanel^  flowLayoutPanel1;
	private: System::Windows::Forms::Panel^  panel1;







	private: System::Windows::Forms::Button^  button3;
	private: System::Windows::Forms::Button^  button2;

	private:
		/// <summary>
		/// Требуется переменная конструктора.
		/// </summary>
		System::Collections::ArrayList^ buttons;
		::Stack<int>* stackInt;
		::Stack<double>* stackDouble;
		::Stack<char>* stackChar;
	private: System::Windows::Forms::TableLayoutPanel^  tableLayoutPanel2;
	private: System::Windows::Forms::Button^  button4;
	private: System::Windows::Forms::Button^  button6;
	private: System::Windows::Forms::MaskedTextBox^  maskedTextBox1;
	private: System::Windows::Forms::Button^  button5;
	private: System::Windows::Forms::StatusStrip^  statusStrip1;
	private: System::Windows::Forms::ToolStripStatusLabel^  toolStripStatusLabel1;

		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Обязательный метод для поддержки конструктора - не изменяйте
		/// содержимое данного метода при помощи редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->tableLayoutPanel1 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->flowLayoutPanel1 = (gcnew System::Windows::Forms::FlowLayoutPanel());
			this->panel1 = (gcnew System::Windows::Forms::Panel());
			this->tableLayoutPanel2 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->button4 = (gcnew System::Windows::Forms::Button());
			this->button6 = (gcnew System::Windows::Forms::Button());
			this->maskedTextBox1 = (gcnew System::Windows::Forms::MaskedTextBox());
			this->button5 = (gcnew System::Windows::Forms::Button());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->statusStrip1 = (gcnew System::Windows::Forms::StatusStrip());
			this->toolStripStatusLabel1 = (gcnew System::Windows::Forms::ToolStripStatusLabel());
			this->tableLayoutPanel1->SuspendLayout();
			this->panel1->SuspendLayout();
			this->tableLayoutPanel2->SuspendLayout();
			this->statusStrip1->SuspendLayout();
			this->SuspendLayout();
			// 
			// button1
			// 
			this->button1->Dock = System::Windows::Forms::DockStyle::Top;
			this->button1->Location = System::Drawing::Point(0, 0);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(252, 24);
			this->button1->TabIndex = 0;
			this->button1->Text = L"Создать Stack<int>";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &MyForm::button1_Click);
			// 
			// tableLayoutPanel1
			// 
			this->tableLayoutPanel1->AutoSize = true;
			this->tableLayoutPanel1->ColumnCount = 2;
			this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				50)));
			this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				50)));
			this->tableLayoutPanel1->Controls->Add(this->flowLayoutPanel1, 0, 0);
			this->tableLayoutPanel1->Controls->Add(this->panel1, 1, 0);
			this->tableLayoutPanel1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->tableLayoutPanel1->Location = System::Drawing::Point(0, 0);
			this->tableLayoutPanel1->Name = L"tableLayoutPanel1";
			this->tableLayoutPanel1->RowCount = 1;
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 50)));
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 50)));
			this->tableLayoutPanel1->Size = System::Drawing::Size(516, 419);
			this->tableLayoutPanel1->TabIndex = 1;
			// 
			// flowLayoutPanel1
			// 
			this->flowLayoutPanel1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->flowLayoutPanel1->Location = System::Drawing::Point(3, 3);
			this->flowLayoutPanel1->Name = L"flowLayoutPanel1";
			this->flowLayoutPanel1->Size = System::Drawing::Size(252, 413);
			this->flowLayoutPanel1->TabIndex = 1;
			// 
			// panel1
			// 
			this->panel1->Controls->Add(this->tableLayoutPanel2);
			this->panel1->Controls->Add(this->button3);
			this->panel1->Controls->Add(this->button2);
			this->panel1->Controls->Add(this->button1);
			this->panel1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->panel1->Location = System::Drawing::Point(261, 3);
			this->panel1->Name = L"panel1";
			this->panel1->Size = System::Drawing::Size(252, 413);
			this->panel1->TabIndex = 2;
			// 
			// tableLayoutPanel2
			// 
			this->tableLayoutPanel2->ColumnCount = 2;
			this->tableLayoutPanel2->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				50)));
			this->tableLayoutPanel2->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				50)));
			this->tableLayoutPanel2->Controls->Add(this->button4, 1, 0);
			this->tableLayoutPanel2->Controls->Add(this->button6, 1, 1);
			this->tableLayoutPanel2->Controls->Add(this->maskedTextBox1, 0, 0);
			this->tableLayoutPanel2->Controls->Add(this->button5, 0, 1);
			this->tableLayoutPanel2->Dock = System::Windows::Forms::DockStyle::Top;
			this->tableLayoutPanel2->Location = System::Drawing::Point(0, 72);
			this->tableLayoutPanel2->Name = L"tableLayoutPanel2";
			this->tableLayoutPanel2->RowCount = 2;
			this->tableLayoutPanel2->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 50)));
			this->tableLayoutPanel2->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 50)));
			this->tableLayoutPanel2->Size = System::Drawing::Size(252, 60);
			this->tableLayoutPanel2->TabIndex = 4;
			// 
			// button4
			// 
			this->button4->Dock = System::Windows::Forms::DockStyle::Fill;
			this->button4->Location = System::Drawing::Point(129, 3);
			this->button4->Name = L"button4";
			this->button4->Size = System::Drawing::Size(120, 24);
			this->button4->TabIndex = 6;
			this->button4->Text = L"Добавить элемент";
			this->button4->UseVisualStyleBackColor = true;
			this->button4->Click += gcnew System::EventHandler(this, &MyForm::button4_Click);
			// 
			// button6
			// 
			this->button6->Dock = System::Windows::Forms::DockStyle::Fill;
			this->button6->Location = System::Drawing::Point(129, 33);
			this->button6->Name = L"button6";
			this->button6->Size = System::Drawing::Size(120, 24);
			this->button6->TabIndex = 5;
			this->button6->Text = L"Очистить";
			this->button6->UseVisualStyleBackColor = true;
			this->button6->Click += gcnew System::EventHandler(this, &MyForm::button6_Click);
			// 
			// maskedTextBox1
			// 
			this->maskedTextBox1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->maskedTextBox1->Location = System::Drawing::Point(3, 3);
			this->maskedTextBox1->Name = L"maskedTextBox1";
			this->maskedTextBox1->Size = System::Drawing::Size(120, 20);
			this->maskedTextBox1->TabIndex = 8;
			// 
			// button5
			// 
			this->button5->Dock = System::Windows::Forms::DockStyle::Fill;
			this->button5->Location = System::Drawing::Point(3, 33);
			this->button5->Name = L"button5";
			this->button5->Size = System::Drawing::Size(120, 24);
			this->button5->TabIndex = 7;
			this->button5->Text = L"Удалить элемент";
			this->button5->UseVisualStyleBackColor = true;
			this->button5->Click += gcnew System::EventHandler(this, &MyForm::button5_Click);
			// 
			// button3
			// 
			this->button3->Dock = System::Windows::Forms::DockStyle::Top;
			this->button3->Location = System::Drawing::Point(0, 48);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(252, 24);
			this->button3->TabIndex = 3;
			this->button3->Text = L"Создать Stack<char>";
			this->button3->UseVisualStyleBackColor = true;
			this->button3->Click += gcnew System::EventHandler(this, &MyForm::button3_Click);
			// 
			// button2
			// 
			this->button2->Dock = System::Windows::Forms::DockStyle::Top;
			this->button2->Location = System::Drawing::Point(0, 24);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(252, 24);
			this->button2->TabIndex = 2;
			this->button2->Text = L"Создать Stack<double>";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &MyForm::button2_Click);
			// 
			// statusStrip1
			// 
			this->statusStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->toolStripStatusLabel1 });
			this->statusStrip1->Location = System::Drawing::Point(0, 397);
			this->statusStrip1->Name = L"statusStrip1";
			this->statusStrip1->Size = System::Drawing::Size(516, 22);
			this->statusStrip1->TabIndex = 6;
			this->statusStrip1->Text = L"statusStrip1";
			// 
			// toolStripStatusLabel1
			// 
			this->toolStripStatusLabel1->Name = L"toolStripStatusLabel1";
			this->toolStripStatusLabel1->Size = System::Drawing::Size(255, 17);
			this->toolStripStatusLabel1->Text = L"Author: James Akwuh, BSU FAMI, 28 June, 2015";
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(516, 419);
			this->Controls->Add(this->statusStrip1);
			this->Controls->Add(this->tableLayoutPanel1);
			this->Name = L"MyForm";
			this->Text = L"Stack Adapter Example";
			this->Load += gcnew System::EventHandler(this, &MyForm::MyForm_Load);
			this->tableLayoutPanel1->ResumeLayout(false);
			this->panel1->ResumeLayout(false);
			this->tableLayoutPanel2->ResumeLayout(false);
			this->tableLayoutPanel2->PerformLayout();
			this->statusStrip1->ResumeLayout(false);
			this->statusStrip1->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

private: System::Void add(System::String^ text) {
	System::Windows::Forms::Button^ button = gcnew System::Windows::Forms::Button();
	button->Dock = System::Windows::Forms::DockStyle::None;
	buttons->Count;
	button->Name = L"button" + Convert::ToString(buttons->Count + 100);
	button->AutoSize = true;
	button->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowOnly;
	button->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
	button->Height = 24;
	button->Width = 24;
	button->UseVisualStyleBackColor = true;
	button->Text = text;
	flowLayoutPanel1->Controls->Add(button);
	buttons->Add(button);
}

private: System::Void pop() {
	delete buttons[buttons->Count - 1];
	buttons->RemoveAt(buttons->Count - 1);
}

private: System::Void clear() {
	for each(System::Object^ obj in buttons) delete obj;
	buttons->Clear();
}

private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
	delete stackInt;
	clear();
	stackInt = new ::Stack < int >;
	stackDouble = 0;
	stackChar = 0;
	maskedTextBox1->Mask = "000000000";
	stackInt->push(1);
	stackInt->push(2);
	stackInt->push(3);
	add("1");
	add("2");
	add("3");
}

private: System::Void button2_Click(System::Object^  sender, System::EventArgs^  e) {
	delete stackDouble;
	clear();
	stackInt = 0;
	stackChar = 0;
	stackDouble = new ::Stack < double >;
	maskedTextBox1->Mask = "00000.00000";
	stackDouble->push(3.141592653);
	stackDouble->push(2.718281828);
	stackDouble->push(9.816);
	add("3.141592653");
	add("2.718281828");
	add("9.816");
}
private: System::Void button3_Click(System::Object^  sender, System::EventArgs^  e) {
	delete stackChar;
	clear();
	stackInt = 0;
	stackDouble = 0;
	stackChar = new ::Stack < char >;
	maskedTextBox1->Mask = "C";
	stackChar->push('J');
	stackChar->push('a');
	stackChar->push('m');
	stackChar->push('e');
	stackChar->push('s');
	add("J");
	add("a");
	add("m");
	add("e");
	add("s");
}
private: System::Void button4_Click(System::Object^  sender, System::EventArgs^  e) {
	String^ text = maskedTextBox1->Text->ToString();
	if (stackInt) {
		text = text->Replace(" ", "");
		stackInt->push(Convert::ToInt32(text));
		add(text);
	}
	else if (stackDouble) {
		text = text->Replace(" ", "");
		stackDouble->push(Convert::ToDouble(text));
		add(text);
	}
	else if (stackChar) {
		stackChar->push(Convert::ToChar(text));
		add(maskedTextBox1->Text);
	}
	else MessageBox::Show("Please, create Stack first of all");
	delete text;
}

private: System::Void button5_Click(System::Object^  sender, System::EventArgs^  e) {
	if (stackInt)
		if (stackInt->empty()) MessageBox::Show("Stack is empty");
		else {
			stackInt->pop();
			pop();
		}
	if (stackDouble)
		if (stackDouble->empty()) MessageBox::Show("Stack is empty");
		else {
			stackDouble->pop();
			pop();
		}
	if (stackChar)
		if (stackChar->empty()) MessageBox::Show("Stack is empty");
		else {
			stackChar->pop();
			pop();
		}
}

private: System::Void button6_Click(System::Object^  sender, System::EventArgs^  e) {
	if (stackInt) {
		stackInt->clear();
		clear();
	}
	if (stackDouble) {
		stackDouble->clear();
		clear();
	}
	if (stackChar) {
		stackChar->clear();
		clear();
	}
}
private: System::Void MyForm_Load(System::Object^  sender, System::EventArgs^  e) {
	this->buttons = gcnew System::Collections::ArrayList;
}
};
}
