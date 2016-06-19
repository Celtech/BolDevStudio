#include "Debugging.h"

Debugging::Debugging()
{
	#ifdef DEBUG
	time(&rawtime);
	timeinfo = localtime(&rawtime);
	AllocConsole();
	freopen("CONOUT$", "w", stdout);
	#endif
}

Debugging::~Debugging()
{
}

void Debugging::Message(const char *fmt, ...)
{
	#ifdef DEBUG
	char buffer[80];
	//strftime(buffer, 80, "[%T]", timeinfo);

	if (!fmt) { return; }
	va_list va_alist;
	char logbuf[256] = { 0 };
	va_start(va_alist, fmt);
	_vsnprintf(logbuf + strlen(logbuf), sizeof(logbuf) - strlen(logbuf), fmt, va_alist);
	va_end(va_alist);

	cout << /*buffer <<*/ logbuf << endl;
	#endif
}
