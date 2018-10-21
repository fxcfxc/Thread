#include<iostream>
#include<process.h>
#include<Windows.h>

using namespace std;

HANDLE g_threadEvent;

//快进程
unsigned int __stdcall FastThread(void* para)
{
	Sleep(10);                    //用来保证各线程调用等待函数有一定的随机性
	cout << (char*)para << "启动" << endl;

	WaitForSingleObject(&g_threadEvent, INFINITE);
	cout << (char*)para << "等到事件触发，顺利结束。 " << endl;

	return 0;
}

//慢进程
unsigned int __stdcall SlowThread(void* para)
{
	Sleep(100);
	cout << (char*)para << "启动" << endl;

	WaitForSingleObject(g_threadEvent, INFINITE);
	cout << (char*)para << "等到事件触发，顺利结束！" << endl;

	return 0;
}

void main()
{
	cout << "使用PlusEvent函数实例" << endl;
	
	BOOL bManualReset = FALSE;
	g_threadEvent = CreateEvent(NULL, bManualReset, FALSE, NULL);

	if (bManualReset)
	{
		cout << "使用手动置位事件" << endl;
	}
	else
	{
		cout << "使用自动置位事件" << endl;
	}

	char fastThreadName[5][30] = { "快线程1000","快线程1001","快线程1002","快线程1003","快线程1004" };
	char slowThreadName[2][30] = { "慢线程196","慢线程197"};

	for (int i = 0; i < 5; i++)
	{
		_beginthreadex(NULL,0,FastThread,fastThreadName[i],0,NULL);
	}

	for (int i = 0; i < 2; i++)
	{
		_beginthreadex(NULL, 0, SlowThread, slowThreadName[i], 0, NULL);
	}

	Sleep(50);          //保证快线程全部启动

	cout << "现在主线程触发一个脉冲 -- PlusEvent（）" << endl;

	PulseEvent(g_threadEvent);

	Sleep(10000);

	cout << "时间到，主线程运行结束！" << endl;
	CloseHandle(g_threadEvent);

	return;
}
