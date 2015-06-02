VC++ CLR - Common Language Runtime (Basic, C++, C#)

Form.h   __ Code
        |
        Designer

Данные располагаются в управляемой области памяти. Обработка всех переменных производится через ссылки

Data types:
Byte        UINT16
SByte       UINT32
Int16       UINT64
Int32       Object
Int64       String
Single(32b) Double (64 bits)

private: System::Void  Button_Click (System::Object^ sender, System::EventArgs^ e);

ButtonEvents = { Click, Enter, MouseHover, MouseLeave };
ButtonMethods = { Focus(), Hide(), Show() };

String^ s = gcnew System::String(char*);
String^ s = gcnew System::String(wchar_t*);
String^ s = gcnew System::String(std::string obj.c_str());

pin_ptr< const wchar_t > wch = OtrToStringChars(Inp ? ... )