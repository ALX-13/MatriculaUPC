#include "UPC.h"

int main() {
	Console::CursorVisible = false;
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	UPC_Vbeta();
	return 0;
}