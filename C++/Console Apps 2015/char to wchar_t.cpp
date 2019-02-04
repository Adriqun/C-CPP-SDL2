/*
	@author Adrian Michalek
	@version 08.08.2018
	@email devmichalek@gmail.com
	@email adrmic98@gmail.com
*/

// Function convert char* to wchar_t*
// If compiler has character set as multi-byte then function works fine on windows
// however if you compile on windows and have unicode character set then you should
// avoid using #ifdef, change its behaviour or delete it pernamently

// For windows compilation include <windows.h>

size_t CreateTempWCharArray(wchar_t*& w)
{
	size_t s = poz;
#ifdef _WIN32
	int codePage = 1250;
	int srcLen = (int)strlen(buf);

	s = MultiByteToWideChar(codePage, 0, buf, srcLen, 0, 0);

	w = new wchar_t[s + 1];
	w[s] = 0;

	MultiByteToWideChar(codePage, 0, buf, srcLen, w, (int)s);
#else
	w = new wchar_t[s];
	mbstowcs(w, buf, s);
#endif
	s *= sizeof(wchar_t);
	return s;
}