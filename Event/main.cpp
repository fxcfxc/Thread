#include<iostream>
#include<process.h>
#include<Windows.h>

using namespace std;

HANDLE g_threadEvent;

//�����
unsigned int __stdcall FastThread(void* para)
{
	Sleep(10);                    //������֤���̵߳��õȴ�������һ���������
	cout << (char*)para << "����" << endl;

	WaitForSingleObject(&g_threadEvent, INFINITE);
	cout << (char*)para << "�ȵ��¼�������˳�������� " << endl;

	return 0;
}

//������
unsigned int __stdcall SlowThread(void* para)
{
	Sleep(100);
	cout << (char*)para << "����" << endl;

	WaitForSingleObject(g_threadEvent, INFINITE);
	cout << (char*)para << "�ȵ��¼�������˳��������" << endl;

	return 0;
}

void main()
{
	cout << "ʹ��PlusEvent����ʵ��" << endl;
	
	BOOL bManualReset = FALSE;
	g_threadEvent = CreateEvent(NULL, bManualReset, FALSE, NULL);

	if (bManualReset)
	{
		cout << "ʹ���ֶ���λ�¼�" << endl;
	}
	else
	{
		cout << "ʹ���Զ���λ�¼�" << endl;
	}

	char fastThreadName[5][30] = { "���߳�1000","���߳�1001","���߳�1002","���߳�1003","���߳�1004" };
	char slowThreadName[2][30] = { "���߳�196","���߳�197"};

	for (int i = 0; i < 5; i++)
	{
		_beginthreadex(NULL,0,FastThread,fastThreadName[i],0,NULL);
	}

	for (int i = 0; i < 2; i++)
	{
		_beginthreadex(NULL, 0, SlowThread, slowThreadName[i], 0, NULL);
	}

	Sleep(50);          //��֤���߳�ȫ������

	cout << "�������̴߳���һ������ -- PlusEvent����" << endl;

	PulseEvent(g_threadEvent);

	Sleep(10000);

	cout << "ʱ�䵽�����߳����н�����" << endl;
	CloseHandle(g_threadEvent);

	return;
}
