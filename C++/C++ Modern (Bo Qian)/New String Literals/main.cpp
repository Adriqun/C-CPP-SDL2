
int main()
{
	// C++ 03
	const char* a = "string";

	// C++ 11
	const char* b = u8"string";		// to define an UTF-8 string
	const char16_t* c = u"string";	// to define an utf-16 string
	const char32_t* d = U"string";	// to define an utf-32 string
	//const char* e = R"string";		// to define raw string

	return 0;
}