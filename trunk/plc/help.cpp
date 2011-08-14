#include <windows.h>
#include <string>
using namespace std;
class help
{
public:
	void wyswietl(wstring topic);
};

help pomoc;

void help::wyswietl(wstring topic)
{
	wstring sciezka = L"help\\";
	sciezka += topic;
	sciezka += L".html";
	ShellExecute(NULL, L"open", sciezka.c_str(), NULL, NULL, 0);
}
