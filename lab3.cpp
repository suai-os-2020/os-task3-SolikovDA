#include "lab3.h"
#include <windows.h> 
#include <stdio.h>

using namespace std;

#define THREADCOUNT 12

HANDLE Thread[THREADCOUNT];
HANDLE Mutex;
HANDLE SemH, SemI, SemM, SemStep, SemNext;

unsigned int lab3_thread_graph_id()
{
	return 13;
}

const char* lab3_unsynchronized_threads()
{
	return "cdef";
}

const char* lab3_sequential_threads()
{
	return "him";
}

DWORD WINAPI thread_a(LPVOID text)
{
	for (int i = 0; i < 3; ++i)
	{
		WaitForSingleObject(Mutex, INFINITE);
		cout << "a" << flush;
		ReleaseMutex(Mutex);
		computation();
	}
	return 0;
}

DWORD WINAPI thread_b(LPVOID text)
{
	for (int i = 0; i < 3; ++i)
	{
		WaitForSingleObject(Mutex, INFINITE);
		cout << "b" << flush;
		ReleaseMutex(Mutex);
		computation();
	}
	return 0;
}

DWORD WINAPI thread_c(LPVOID text)
{
	for (int i = 0; i < 3; ++i)
	{
		WaitForSingleObject(Mutex, INFINITE);
		cout << "c" << flush;
		ReleaseMutex(Mutex);
		computation();
	}

	ReleaseSemaphore(SemStep, 1, NULL);
	WaitForSingleObject(SemNext, INFINITE);
	

	for (int i = 0; i < 3; ++i)
	{
		WaitForSingleObject(Mutex, INFINITE);
		cout << "c" << flush;
		ReleaseMutex(Mutex);
		computation();
	}

	return 0;
}

DWORD WINAPI thread_d(LPVOID text)
{
	for (int i = 0; i < 3; ++i)
	{
		WaitForSingleObject(Mutex, INFINITE);
		cout << "d" << flush;
		ReleaseMutex(Mutex);
		computation();
	}

	ReleaseSemaphore(SemStep, 1, NULL);
	WaitForSingleObject(SemNext, INFINITE);


	for (int i = 0; i < 3; ++i)
	{
		WaitForSingleObject(Mutex, INFINITE);
		cout << "d" << flush;
		ReleaseMutex(Mutex);
		computation();
	}

	return 0;
}

DWORD WINAPI thread_e(LPVOID text)
{
	for (int i = 0; i < 3; ++i)
	{
		WaitForSingleObject(Mutex, INFINITE);
		cout << "e" << flush;
		ReleaseMutex(Mutex);
		computation();
	}
	return 0;
}

DWORD WINAPI thread_f(LPVOID text)
{
	for (int i = 0; i < 3; ++i)
	{
		WaitForSingleObject(Mutex, INFINITE);
		cout << "f" << flush;
		ReleaseMutex(Mutex);
		computation();
	}
	return 0;
}

DWORD WINAPI thread_g(LPVOID text)
{
	for (int i = 0; i < 3; ++i)
	{
		WaitForSingleObject(Mutex, INFINITE);
		cout << "g" << flush;
		ReleaseMutex(Mutex);
		computation();
	}
	return 0;
}


DWORD WINAPI thread_h(LPVOID text)
{
	for (int i = 0; i < 3; ++i)
	{
		WaitForSingleObject(Mutex, INFINITE);
		cout << "h" << flush;
		ReleaseMutex(Mutex);
		computation();
	}

	ReleaseSemaphore(SemStep, 1, NULL);
	WaitForSingleObject(SemNext, INFINITE);
	

	for (int i = 0; i < 3; ++i)
	{
		WaitForSingleObject(SemH, INFINITE);
		WaitForSingleObject(Mutex, INFINITE);
		cout << "h" << flush;
		ReleaseMutex(Mutex);
		computation();
		ReleaseSemaphore(SemI, 1, NULL);
	}

	return 0;
}

DWORD WINAPI thread_i(LPVOID text)
{
	for (int i = 0; i < 3; ++i)
	{
		WaitForSingleObject(SemI, INFINITE);
		WaitForSingleObject(Mutex, INFINITE);
		cout << "i" << flush;
		ReleaseMutex(Mutex);
		computation();
		ReleaseSemaphore(SemM, 1, NULL);
	}
	return 0;
}

DWORD WINAPI thread_k(LPVOID text)
{
	for (int i = 0; i < 3; ++i)
	{
		WaitForSingleObject(Mutex, INFINITE);
		cout << "k" << flush;
		ReleaseMutex(Mutex);
		computation();
	}
	return 0;
}

DWORD WINAPI thread_m(LPVOID text)
{
	for (int i = 0; i < 3; ++i)
	{
		WaitForSingleObject(Mutex, INFINITE);
		cout << "m" << flush;
		ReleaseMutex(Mutex);
		computation();
	}

	ReleaseSemaphore(SemStep, 1, NULL);
	WaitForSingleObject(SemNext, INFINITE);


	for (int i = 0; i < 3; ++i)
	{
		WaitForSingleObject(SemM, INFINITE);
		WaitForSingleObject(Mutex, INFINITE);
		cout << "m" << flush;
		ReleaseMutex(Mutex);
		computation();
		ReleaseSemaphore(SemH, 1, NULL);
	}

	return 0;
}

DWORD WINAPI thread_n(LPVOID text)
{
	for (int i = 0; i < 3; ++i)
	{
		WaitForSingleObject(Mutex, INFINITE);
		cout << "n" << flush;
		ReleaseMutex(Mutex);
		computation();
	}
	return 0;
}


int lab3_init()
{
	DWORD ThreadID;

	Mutex = CreateMutex(NULL, FALSE, NULL);
	if (Mutex == NULL)
	{
		cout << "CreateMutex error " << GetLastError() << endl;
		return 1;
	}

	SemH = CreateSemaphore(NULL, 1, 1, NULL);
	if (SemH == NULL)
	{
		cout << "CreateSemaphore error: SemH" << GetLastError() << endl;
		return 1;
	}

	SemI = CreateSemaphore(NULL, 0, 1, NULL);
	if (SemI == NULL)
	{
		cout << "CreateSemaphore error: SemI " << GetLastError() << endl;
		return 1;
	}

	SemM = CreateSemaphore(NULL, 0, 1, NULL);
	if (SemM == NULL)
	{
		cout << "CreateSemaphore error: SemM" << GetLastError() << endl;
		return 1;
	}

	SemStep = CreateSemaphore(NULL, 0, 2, NULL);
	if (SemStep == NULL)
	{
		cout << "CreateSemaphore error: SemM" << GetLastError() << endl;
		return 1;
	}

	SemNext = CreateSemaphore(NULL, 0, 2, NULL);
	if (SemNext == NULL)
	{
		cout << "CreateSemaphore error: SemM" << GetLastError() << endl;
		return 1;
	}

	///STEP1///
	
	Thread[0] = CreateThread(NULL, 0, thread_a, NULL, 0, &ThreadID);

	if (Thread[0] == NULL) {

		return GetLastError();

	}

	WaitForSingleObject(Thread[0], INFINITE);

	///STEP2///

	Thread[1] = CreateThread(NULL, 0, thread_b, NULL, 0, &ThreadID);

	if (Thread[1] == NULL) {

		return GetLastError();

	}

	Thread[2] = CreateThread(NULL, 0, thread_c, NULL, 0, &ThreadID);

	if (Thread[2] == NULL) {

		return GetLastError();

	}

	WaitForSingleObject(Thread[1], INFINITE);
	WaitForSingleObject(SemStep, INFINITE);

///STEP3///
	ReleaseSemaphore(SemNext, 1, NULL);
	Thread[3] = CreateThread(NULL, 0, thread_d, NULL, 0, &ThreadID);

	if (Thread[3] == NULL) {

		return GetLastError();

	}
	Thread[4] = CreateThread(NULL, 0, thread_e, NULL, 0, &ThreadID);

	if (Thread[4] == NULL) {

		return GetLastError();

	}
	Thread[5] = CreateThread(NULL, 0, thread_f, NULL, 0, &ThreadID);

	if (Thread[5] == NULL) {

		return GetLastError();

	}
	WaitForSingleObject(Thread[2], INFINITE);
	WaitForSingleObject(Thread[4], INFINITE);
	WaitForSingleObject(Thread[5], INFINITE);
	WaitForSingleObject(SemStep, INFINITE);

	///STEP4///
	ReleaseSemaphore(SemNext, 1, NULL);

	Thread[6] = CreateThread(NULL, 0, thread_g, NULL, 0, &ThreadID);

	if (Thread[6] == NULL) {

		return GetLastError();

	}
	Thread[7] = CreateThread(NULL, 0, thread_h, NULL, 0, &ThreadID);

	if (Thread[7] == NULL) {

		return GetLastError();

	}
	Thread[9] = CreateThread(NULL, 0, thread_k, NULL, 0, &ThreadID);

	if (Thread[9] == NULL) {

		return GetLastError();

	}
	Thread[10] = CreateThread(NULL, 0, thread_m, NULL, 0, &ThreadID);

	if (Thread[4] == NULL) {

		return GetLastError();

	}

	WaitForSingleObject(Thread[3], INFINITE);
	WaitForSingleObject(Thread[6], INFINITE);
	WaitForSingleObject(Thread[9], INFINITE);
	WaitForSingleObject(SemStep, INFINITE);
	WaitForSingleObject(SemStep, INFINITE);

	///STEP5///
	ReleaseSemaphore(SemNext, 1, NULL);
	ReleaseSemaphore(SemNext, 1, NULL);
	Thread[8] = CreateThread(NULL, 0, thread_i, NULL, 0, &ThreadID);

	if (Thread[8] == NULL) {

		return GetLastError();

	}
	WaitForSingleObject(Thread[7], INFINITE);
	WaitForSingleObject(Thread[8], INFINITE);
	WaitForSingleObject(Thread[10], INFINITE);

	///STEP6///
	Thread[11] = CreateThread(NULL, 0, thread_n, NULL, 0, &ThreadID);

	if (Thread[11] == NULL) {

		return GetLastError();

	}
	WaitForSingleObject(Thread[11], INFINITE);
	

	CloseHandle(SemH);
	CloseHandle(SemI);
	CloseHandle(SemM);
	CloseHandle(SemStep);
	CloseHandle(SemNext);
	CloseHandle(Mutex);

	cout << endl;

	return 0;
}
