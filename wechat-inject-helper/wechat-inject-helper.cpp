﻿// wechat-inject-helper.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include <stdio.h>
#include "resource.h"
#include "wechat-info-get.h"
#include "InitWeChat.h"
#include <tchar.h>

// 读取内存数据
VOID readWechatData(HWND hDlg) {
	wxMyUserInfo userInfo = getUserInfo();
	wchar_t buff[0x1000] = { 0 };
	string asVer = GetWxVersion();
	swprintf_s(buff, L"微信号：%s \r\n昵称：%s \r\n头像：%s \r\n手机号：%s \r\n设备：%s \r\n版本：%s",
		userInfo.wxid,
		userInfo.wxNick,
		userInfo.wxHeadPic,
		userInfo.wxBindPhone,
		userInfo.wxDevice,
		AnsiToUnicode(asVer.data()));
	SetDlgItemText(hDlg, SHOW_DATA, buff);

	//查找微信小助手窗口句柄
	HWND hWxHelper = FindWindow(NULL, L"微信小助手");
	if (hWxHelper == NULL)
	{
		MessageBoxA(NULL, "未查找到微信小助手窗口", "错误", MB_OK);
		return;
	}
	//const wchar_t* sz = L"这是一条测试消息";
	const wchar_t* sz = L"This is a test message from wechat-inject-helper.";
	COPYDATASTRUCT msg;
	msg.cbData = wcslen(sz)*2 + 1; // 宽字符需要*2,数组完整需要+1
	msg.dwData = sizeof(COPYDATASTRUCT);
	msg.lpData = (LPVOID)sz;
	//发送消息给控制端
	SendMessage(hWxHelper, WM_COPYDATA, (WPARAM)hWxHelper, (LPARAM)&msg);
}