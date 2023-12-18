#pragma warning(disable : 4996)
#include <windows.h>
#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <conio.h>
#include <process.h>
#include <vector>

using namespace std;

FILE*out;
string binary_name, text;
int message_amount;
int sender_amount;
HANDLE hWriterSemaphore, hReadySemaphore, hMutex, hEvent;
STARTUPINFO* si;
PROCESS_INFORMATION* pi;
int critical = 0;
ofstream out1;

void init()
{	
	printf("Enter the name the binary file: ");
	cin >> binary_name;
	
	do
	{
		printf("Enter the amount of messages in the file: ");
		scanf("%d", &message_amount);
		printf("Enter the amount of Senders: ");
		scanf("%d", &sender_amount);

		if(message_amount <= 0 || sender_amount <= 0)
			printf("Positive numbers were expected. Enter again\n");
	}
	while (message_amount <= 0 || sender_amount <= 0);
	
	out = fopen(binary_name.c_str(), "rb");
	fclose(out);

	hWriterSemaphore = CreateSemaphore(NULL, message_amount, message_amount, (LPCSTR)"WriterSemaphore");
	if (hWriterSemaphore == NULL)
	{
		cout << "Create semaphore failed.\n";
		critical = 1;
		getchar();
		return;
	}


	hReadySemaphore = CreateSemaphore(NULL, 1 - message_amount, 1, (LPCSTR)"ReadySemaphore");
	if (hWriterSemaphore == NULL)
	{
		cout << "Create semaphore failed.\n";
		critical = 1;
		getchar();
		return;
	}

	hMutex = CreateMutex(NULL, FALSE, (LPCSTR)"DemoMutex"); 
	if (hMutex == NULL)
	{
		cout << "Create mutex failed.\n";
		critical = 1;
		getchar();
		return;
	}

	hEvent = CreateEvent(NULL, TRUE, FALSE, (LPCSTR)"Event");
	if (hEvent == NULL) return;

	si = new STARTUPINFO[sender_amount];
	pi = new PROCESS_INFORMATION[sender_amount];

	char sender_launcher2[200] = "sender.exe ";
	strcat(sender_launcher2, binary_name.c_str());

	for (int i = 0; i < sender_amount; i++) 
	{
		ZeroMemory(&si[i], sizeof(STARTUPINFO));
		si[i].cb = sizeof(STARTUPINFO);
		ZeroMemory(&pi[i], sizeof(PROCESS_INFORMATION));


		if (!CreateProcess(NULL, sender_launcher2, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si[i], &pi[i])) 
		{
			cout << GetLastError();
			ExitProcess(0);
		}
	}
}

void finit()
{
	for (int i = 0; i < sender_amount; i++) 
	{
		TerminateProcess(pi[i].hProcess, 0);
		CloseHandle(pi[i].hThread);
		CloseHandle(pi[i].hProcess);
	}
	CloseHandle(hMutex);
}

void loop()
{
	vector<string> v;
	v.reserve(message_amount);
	WaitForSingleObject(hReadySemaphore, INFINITE);


	while (1) 
	{
        printf("Would you like to keep reading messages? [y/n]\n");
		cin >> text;
		if (text == "n" || text == "N")
		{
			break;
		}
		else if (text == "Y" || text == "y")
		{
			ifstream in;
			in.open(binary_name, fstream::binary);
			if (in.peek() == ifstream::traits_type::eof())
			{
				ResetEvent(hEvent);
				WaitForSingleObject(hEvent, INFINITE);
				ResetEvent(hEvent);
			}
			WaitForSingleObject(hMutex, INFINITE);

			in.seekg(0, in.end);
			int pos = in.tellg() / 21;
			in.seekg(in.beg);
			v.clear();
			for (int i = 0; i < pos; ++i)
			{
				char mess[21];
				in.read(mess, 21);
				string s = mess;
				v.push_back(s);
			}
			in.close();

			out1.open(binary_name, ofstream::binary | ofstream::out | ofstream::trunc);
			for (int i = 1; i < v.size(); ++i)
			{
				char mess[21];
				strcpy(mess, v[i].c_str());
				out1.write(mess, 21);
			}
			out1.close();
			cout << v[0] << "\n";
			ReleaseSemaphore(hWriterSemaphore, 1, NULL);
			ReleaseMutex(hMutex);
		}
		else cout << "Error with input, try again .\n";
	}
}

int main() 
{
	init();

	if(!critical)
	{
		loop();
		finit();
	}

	return 0;
}
