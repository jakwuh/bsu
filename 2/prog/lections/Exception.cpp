Exceptions {
	...

	void f() throw (char*, struct_name) { // все тело функции - блок try -- deprecated in c++11
		...
		throw struct_name();
		...
		catch (struct_name& e) {};
		...
	}
}
