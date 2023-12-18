#pragma warning(disable: 4996)
#include <iostream>
#include <fstream>
#include <string>
#include "windows.h"

using namespace std;

HANDLE hWriterSemaphore, hReadySemaphore, hEvent, hMutex;
ofstream in, out;
string message, binary_name;
int critical = 0;

void init()
{
	hWriterSemaphore = OpenSemaphore(SEMAPHORE_ALL_ACCESS, FALSE, "WriterSemaphore");
	if (hWriterSemaphore == NULL)
	{
		cout << "Create semaphore failed.\n";
		critical = 1;
		return;
	}

	hReadySemaphore = OpenSemaphore(SEMAPHORE_ALL_ACCESS, FALSE, "ReadySemaphore");
	if (hWriterSemaphore == NULL)
	{
		cout << "Create semaphore failed.\n";
		critical = 1;
		return;
	}

	hMutex = OpenMutex(SYNCHRONIZE, FALSE, "DemoMutex");
	if (hMutex == NULL)
	{
		cout << "Open mutex failed.\n";
		critical = 1;
		return;
	}

	hEvent = CreateEvent(NULL, TRUE, FALSE, "Event");
	if (hEvent == NULL) return;
}

void loop()
{
	out.open(binary_name, ofstream::binary | std::ios_base::app);
	if(!out.is_open()) cout << "File not found.\n";

	ReleaseSemaphore(hReadySemaphore, 1, NULL);
	while (1) 
	{
		bool request = true;
		printf("Would you like to send a new message[1] or exit[0]? [1/0]\n");
		cin >> message;
		if (message == "0")
		{
			break;
		}
		else if (message == "1")
		{

			while (request)
			{
				WaitForSingleObject(hWriterSemaphore, INFINITE);
				cout << "Input your message under 20 characters:\n";
				cin >> message;
				if (message.size() > 20)
				{
					cout << "The message is too long. Try again.\n";
					ReleaseSemaphore(hWriterSemaphore, 1, NULL);
				}
				else request = false;
			}
			
			WaitForSingleObject(hMutex, INFINITE);

			if (!out.is_open()) out.open(binary_name, ofstream::binary | std::ios_base::app);
			out.write(message.c_str(), 21);
			out.close();
			ReleaseMutex(hMutex);
			SetEvent(hEvent);
		}
		else printf("Error with input, new attempt\n");
	}
}

int main(int argc, char* argv[]) 
{
	init();

	if(critical)
	{
		printf("Error, press to terminate the process\n");
		getchar();
	}
	else
	{
		binary_name = argv[1];
		cout << binary_name << endl;

		loop();
	}
	CloseHandle(hMutex);
	return 0;
}
