#include <windows.h>

class help
	{
   public:
		void wyswietl(char * topic);
   };

help pomoc;

void help::wyswietl(char * topic)
	{
   char * sciezka = "help\\";
   char * tymcz = new char[strlen(sciezka)+strlen(topic)+strlen(".html")+1];
   strcpy(tymcz, sciezka);
   strcat(tymcz, topic);
   strcat(tymcz, ".html");
	ShellExecute(NULL, "open", tymcz, NULL, NULL, 0);
   delete [] tymcz;
   }
