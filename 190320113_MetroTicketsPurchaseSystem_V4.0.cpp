//模拟地铁自动售票系统
//作者：190320113 王英杰
//语言：C++
//使用的拓展包：EasyX库(附带graphics.h) 2020 版 (2020-8-6 更新)
//版本 V4.0.0

/*程序要求：系统的功能需求描述如下：
（1）显示欢迎界面，作者信息和版权信息。
（2）进入系统主菜单，提供购票选项、地图查询选项、退出系统，三个选项。
（3）系统说明界面详细的介绍了购票流程，并且附有用户须知。
（4）用户选择开始购票，进入始发站选择界面，或者由此返回主界面。
（5）用户选择好了始发站后进入终点站的选择，或者由此返回主界面。
（6）根据系统提示然后进入票数的选择，或者由此返回主界面。
（7）根据系统提示进入投币找币流程，或者由此返回主界面。
（8）购票成功。
*****************************************************************************************************/


#include <ctime>
#include <cstdlib>
#include <list>
#include <cmath>
#include <graphics.h>
#include <conio.h>
#include <stdlib.h>

MOUSEMSG mouse;//鼠标结构体

//全局变量
const int PricePerTikect = 2;
//全局变量
int fee = 0;
int In_rect(RECT, POINT);
//函数声明
void begin();
void DrawBackground();
void DrawCountinueButton(int y, int a);
void DrawEscapeButton(int y,int a);
void DrawPurchaseButton(int y, int a);
void DrawMapButton(int y, int a);
void DrawPayButton(int y, int a);
void Draw10yuanButton(int x, int y, int a);
void Draw5yuanButton(int x, int y, int a);
void DrawChangeButton(int x, int y, int a);
void ShowPurchaseMethod();
void Menu();
void ChooseLine();
void ShowMap();
void Pay();
//主程序
int main()
{
	initgraph(800, 600);
	while (1)
	{
		begin();
	}
}
//欢迎界面
void begin()
{
	cleardevice();
	DrawBackground();
	//欢迎
	settextcolor(WHITE);
	settextstyle(150, 0, L"华文中宋", 0, 0, 1000, false, false, false);
	outtextxy(100, 50, L"欢");
	outtextxy(550, 50, L"迎");
	//在中间显示用户须知
	settextstyle(40, 0, L"微软雅黑", 0, 0, 800, false, false, false);
	outtextxy(getwidth() / 2 - textwidth(L"用户须知") / 2, 280, L"用户须知");
	settextstyle(20, 0, L"微软雅黑", 0, 0, 0, false, false, false);
	outtextxy(getwidth() / 2 - textwidth(L"（一）乘客应当持有效车票乘车；") / 2, 320, L"（一）乘客应当持有效车票乘车；");
	outtextxy(getwidth() / 2 - textwidth(L"（二）越站乘车的，应当补交超过部分票款；") / 2, 340, L"（二）越站乘车的，应当补交超过部分票款；");
	outtextxy(getwidth() / 2 - textwidth(L"（三）持票进入收费区后，须在合理时间内出收费区，超出合理时间的，应当按照网络单程最低票价补交票款；") / 2, 360, L"（三）持票进入收费区后，须在合理时间内出收费区，超出合理时间的，应当按照网络单程最低票价补交票款；");
	
	//绘制“继续”按钮
	DrawCountinueButton(400,1);
	MOUSEMSG mouse;
	
	//鼠标放在“继续按钮上”则按钮变色
	do
	{
		DrawCountinueButton(400,1);
		do
		{
			mouse = GetMouseMsg();
		} while (!In_rect({ 350,400,450,440 } ,{mouse.x, mouse.y}));

		DrawCountinueButton(400,2);
		while (In_rect({ 350,400,450,440 }, { mouse.x, mouse.y }) && !mouse.mkLButton)
			mouse = GetMouseMsg();
	} while (!mouse.mkLButton);
	cleardevice();
	
	if (In_rect({ 350,400,450,440 }, { mouse.x, mouse.y }) && mouse.mkLButton)
		ShowPurchaseMethod();

	// 按任意键退出
	//_getch();
	//closegraph();
}

// 判断点是否在矩形中
int In_rect(RECT rect, POINT point)
{
	if (point.x > rect.left && point.x < rect.right && point.y > rect.top && point.y < rect.bottom)
		return 1;
	else
		return 0;
}
//绘制背景界面
void DrawBackground()
{
	
	// 读取图片至绘图窗口
	loadimage(NULL, _T("C:\\Users\\86135\\Desktop\\学习\\2020夏季学期\\创新训练B\\190320113_MetroTicketsPurchaseSystem_V1.0\\Pics\\Welcome_.PNG"));
	//在底部显示版权作者等信息
	setbkcolor(RGB(255, 153, 204));
	settextcolor(BLACK);
	settextstyle(20, 0, L"微软雅黑", 0, 0, 0, false, false, false);
	outtextxy(getwidth() / 2 - textwidth(L"模拟地铁售票系统 V4.0.0") / 2, 540, L"模拟地铁售票系统 V4.0.0");
	outtextxy(getwidth() / 2 - textwidth(L"作者：190320113 王英杰") / 2, 560, L"作者：190320113 王英杰");
	outtextxy(getwidth() / 2 - textwidth(L"版权所有，禁止转载") / 2, 580, L"版权所有，禁止转载");
	
}
//由y坐标生成一个继续按钮
void DrawCountinueButton(int y,int a)
{
	if (a == 1)
	{
		setfillcolor(WHITE);
		fillrectangle(350, y, 450, y + 40);
		setbkcolor(WHITE);
		settextcolor(BLACK);
		settextstyle(40, 0, L"黑体", 0, 0, 800, false, false, false);
	}
	else
	{
		setfillcolor(RGB(220, 220, 220));
		fillrectangle(350, y, 450, y + 40);
		setbkcolor(RGB(220, 220, 220));
		settextcolor(RED);
		settextstyle(40, 0, L"黑体", 0, 0, 800, false, true, false);
	}
	outtextxy(getwidth() / 2 - textwidth(L"继续") / 2, y, L"继续");
}
//由y坐标生产一个退出按钮
void DrawEscapeButton(int y,int a)
{
	if (a == 1)
	{
		setfillcolor(WHITE);
		fillrectangle(350, y, 450, y + 40);
		setbkcolor(WHITE);
		settextcolor(BLACK);
		settextstyle(40, 0, L"黑体", 0, 0, 800, false, false, false);
	}
	else if (a == 2)
	{
		setfillcolor(RGB(220, 220, 220));
		fillrectangle(350, y, 450, y + 40);
		setbkcolor(RGB(220, 220, 220));
		settextcolor(RED);
		settextstyle(40, 0, L"黑体", 0, 0, 800, false, true, false);
	}
	else
	{
		setfillcolor(RGB(220, 220, 220));
		fillrectangle(350, y, 450, y + 40);
		setbkcolor(RGB(220, 220, 220));
		settextcolor(RGB(180, 180, 180));
		settextstyle(40, 0, L"黑体", 0, 0, 800, false, false, false);
	}
	outtextxy(getwidth() / 2 - textwidth(L"退出") / 2, y, L"退出");
}
//生成一个购买按钮
void DrawPurchaseButton(int y, int a)
{
	if (a == 1)
	{
		setfillcolor(WHITE);
		fillrectangle(350, y, 450, y + 40);
		setbkcolor(WHITE);
		settextcolor(BLACK);
		settextstyle(40, 0, L"黑体", 0, 0, 800, false, false, false);
	}
	else
	{
		setfillcolor(RGB(220, 220, 220));
		fillrectangle(350, y, 450, y + 40);
		setbkcolor(RGB(220, 220, 220));
		settextcolor(RED);
		settextstyle(40, 0, L"黑体", 0, 0, 800, false, true, false);
	}
	outtextxy(getwidth() / 2 - textwidth(L"购票") / 2, y, L"购票");
}
//由y坐标生成一个地图按钮
void DrawMapButton(int y,int a)
{
	if (a == 1)
	{
		setfillcolor(WHITE);
		fillrectangle(350, y, 450, y + 40);
		setbkcolor(WHITE);
		settextcolor(BLACK);
		settextstyle(40, 0, L"黑体", 0, 0, 800, false, false, false);
	}
	else
	{
		setfillcolor(RGB(220, 220, 220));
		fillrectangle(350, y, 450, y + 40);
		setbkcolor(RGB(220, 220, 220));
		settextcolor(RED);
		settextstyle(40, 0, L"黑体", 0, 0, 800, false, true, false);
	}
	outtextxy(getwidth() / 2 - textwidth(L"地图") / 2, y, L"地图");
}
//由y坐标生成一个投币按钮
void DrawPayButton(int y, int a)
{
	if (a == 1)
	{
		setfillcolor(WHITE);
		fillrectangle(350, y, 450, y + 40);
		setbkcolor(WHITE);
		settextcolor(BLACK);
		settextstyle(40, 0, L"黑体", 0, 0, 800, false, false, false);
		outtextxy(getwidth() / 2 - textwidth(L"投币") / 2, y, L"投币");
	}
	else
	{
		setfillcolor(RGB(220, 220, 220));
		fillrectangle(350, y, 450, y + 40);
		setbkcolor(RGB(220, 220, 220));
		settextcolor(RED);
		settextstyle(40, 0, L"黑体", 0, 0, 800, false, true, false);
	}
	outtextxy(getwidth() / 2 - textwidth(L"投币") / 2, y, L"投币");
}
//生成模拟10元按钮
void Draw10yuanButton(int x,int y,int a)
{
	settextcolor(WHITE);
	settextstyle(20, 0, L"黑体", 0, 0, 800, false, false, false);
	if (a == 1)
	{
		setfillcolor(RGB(255, 153, 204));
		solidrectangle(x, y - 20, x + 100, y + 20);
		setfillcolor(RGB(67, 93, 106));
		solidrectangle(x, y, x + 100, y + 40);
		setbkcolor(RGB(67, 93, 106));
		outtextxy(x+20, y+10, L"拾圆");
	}
	else if (a == 2)
	{
		setfillcolor(RGB(255,153,204));
		solidrectangle(x, y, x + 100, y+40);
		setfillcolor(RGB(67, 93, 106));
		solidrectangle(x, y - 20, x + 100, y + 20);
		setbkcolor(RGB(67, 93, 106));
		outtextxy(x+20, y - 10, L"拾圆");
	}
	else
	{
		setfillcolor(RGB(255, 153, 204));
		solidrectangle(x, y - 20, x + 100, y + 20);
		setfillcolor(RGB(220,220,220));
		solidrectangle(x, y, x + 100, y + 40);
		setbkcolor(RGB(220,220,220));
		settextcolor(RGB(190, 190, 190));
		outtextxy(x + 20, y + 10, L"拾圆");
	}
}
//生成模拟5元按钮
void Draw5yuanButton(int x, int y, int a)
{
	settextcolor(WHITE);
	settextstyle(20, 0, L"黑体", 0, 0, 800, false, false, false);
	if (a == 1)
	{
		setfillcolor(RGB(255, 153, 204));
		solidrectangle(x, y - 20, x + 100, y + 20);
		setfillcolor(RGB(125, 105, 168));
		solidrectangle(x, y, x + 100, y + 40);
		setbkcolor(RGB(125, 105, 168));
		outtextxy(x + 20, y + 10, L"伍圆");
	}
	else if (a == 2)
	{
		setfillcolor(RGB(255, 153, 204));
		solidrectangle(x, y, x + 100, y + 40);
		setfillcolor(RGB(125, 105, 168));
		solidrectangle(x, y - 20, x + 100, y + 20);
		setbkcolor(RGB(125, 105, 168));
		outtextxy(x + 20, y - 10, L"伍圆");
	}
	else
	{
		setfillcolor(RGB(255, 153, 204));
		solidrectangle(x, y - 20, x + 100, y + 20);
		setfillcolor(RGB(220, 220, 220));
		solidrectangle(x, y, x + 100, y + 40);
		setbkcolor(RGB(220, 220, 220));
		settextcolor(RGB(190, 190, 190));
		outtextxy(x + 20, y + 10, L"伍圆");
	}
}
//由y坐标生成一个找零按钮
void DrawChangeButton(int x, int y, int a)
{
	if (a == 1)
	{
		setfillcolor(WHITE);
		fillrectangle(x, y, x + 150, y + 40);
		setbkcolor(WHITE);
		settextcolor(BLACK);
		settextstyle(40, 0, L"黑体", 0, 0, 800, false, false, false);
	}
	else if (a == 2)
	{
		setfillcolor(RGB(220, 220, 220));
		fillrectangle(x, y, x + 150, y + 40);
		setbkcolor(RGB(220, 220, 220));
		settextcolor(RED);
		settextstyle(40, 0, L"黑体", 0, 0, 800, false, true, false);
	}
	else 
	{
		setfillcolor(RGB(220, 220, 220));
		fillrectangle(x, y, x + 150, y + 40);
		setbkcolor(RGB(220, 220, 220));
		settextcolor(RGB(180,180,180));
		settextstyle(40, 0, L"黑体", 0, 0, 800, false, false, false);
	}

	outtextxy(x, y, L"支付并找零");
}
//购票流程展示界面
void ShowPurchaseMethod()
{
	FlushMouseMsgBuffer();
	cleardevice();
	DrawBackground();
	settextcolor(GREEN);
	settextstyle(60, 0, L"微软雅黑", 0, 0, 800, false, false, false);
	outtextxy(getwidth() / 2 - textwidth(L"购票流程") / 2, 120, L"购票流程");
	settextstyle(40, 0, L"微软雅黑", 0, 0, 0, false, false, false);
	outtextxy(getwidth() / 2 - textwidth(L"（一）点击开始购票按钮开始购票；") / 2, 240, L"（一）点击开始购票按钮开始购票；");
	outtextxy(getwidth() / 2 - textwidth(L"（二）查看地图，然后输入起点站和终点站代码；") / 2, 280, L"（二）查看地图，然后输入起点站和终点站代码；");
	outtextxy(getwidth() / 2 - textwidth(L"（三）投币并等待找零和出票；") / 2, 320, L"（三）投币并等待找零和出票；");
	DrawCountinueButton(400,1);
	//setfillcolor(RGB(255, 153, 204));
	//solidrectangle(350, 400, 450, 440);
	MOUSEMSG mouse;

	//鼠标放在“继续按钮上”则按钮变色
	do
	{
		DrawCountinueButton(400,1);
		do
		{
			mouse = GetMouseMsg();
		} while (!In_rect({ 350,400,450,440 }, { mouse.x, mouse.y }));

		DrawCountinueButton(400,2);
		while (In_rect({ 350,400,450,440 }, { mouse.x, mouse.y }) && !mouse.mkLButton)
			mouse = GetMouseMsg();
	} while (!mouse.mkLButton);
	cleardevice();

	if (In_rect({ 350,400,450,440 }, { mouse.x, mouse.y }) && mouse.mkLButton)
		Menu();

}

//主菜单界面
void Menu()
{
	FlushMouseMsgBuffer();
	cleardevice();
	DrawBackground();
	settextcolor(GREEN);
	settextstyle(60, 0, L"微软雅黑", 0, 0, 800, false, false, false);
	outtextxy(getwidth() / 2 - textwidth(L"主 菜 单") / 2, 100, L"主 菜 单");


	do
	{
		DrawPurchaseButton(200,1);
		DrawMapButton(250,1);
		DrawEscapeButton(300,1);
		do
		{
			mouse = GetMouseMsg();
		} while ( (!In_rect({ 350,200,450,240 }, { mouse.x, mouse.y })) && (!In_rect({ 350,250,450,290 }, { mouse.x, mouse.y }))  && (!In_rect({ 350,300,450,340 }, { mouse.x, mouse.y }))   );


		if((In_rect({ 350,200,450,240 }, { mouse.x, mouse.y })) && !mouse.mkLButton)
			DrawPurchaseButton(200,2);
		if ((In_rect({ 350,250,450,290 }, { mouse.x, mouse.y })) && !mouse.mkLButton)
			DrawMapButton(250,2);
		if ((In_rect({ 350,300,450,340 }, { mouse.x, mouse.y })) && !mouse.mkLButton)
			DrawEscapeButton(300,2);
		while ( ((In_rect({ 350,200,450,240 }, { mouse.x, mouse.y })) || (In_rect({ 350,250,450,290 }, { mouse.x, mouse.y })) || (In_rect({ 350,300,450,340 }, { mouse.x, mouse.y }))) && !mouse.mkLButton)
			mouse = GetMouseMsg();
	} while (!mouse.mkLButton);

	if (In_rect({ 350,200,450,240 }, { mouse.x, mouse.y }) && mouse.mkLButton)
		ChooseLine();
	if (In_rect({ 350,250,450,290 }, { mouse.x, mouse.y }) && mouse.mkLButton)
		ShowMap();
	if (In_rect({ 350,300,450,340 }, { mouse.x, mouse.y }) && mouse.mkLButton)
		begin();
}

//输出并显示路线界面
void ChooseLine()
{
	again:
	
	cleardevice();
	DrawBackground();
	int StartNum =7;
	int TerminalNum =0;
	int TicketNum = 0;
	int ReturnOrNot = 0;
	int i;
	do
	{
		wchar_t a[10];                                                                           // 定义字符串缓冲区，并接收用户输入
		InputBox(a, 10, L"请键入起点站的编号 【1】~【6】，\n欲返回主菜单请输入【0】");
		StartNum = _wtoi(a);                                                                 // 将用户输入转换为数字 
	} while (StartNum != 0 && StartNum != 1 && StartNum != 2 && StartNum != 3 && StartNum != 4 && StartNum != 5 && StartNum != 6);
	if (StartNum == 0)
		Menu();
	do
	{
		wchar_t b[10];
		InputBox(b, 10, L"请键入终点站的编号 【1】~【6】，\n欲返回主菜单请输入【0】");
		TerminalNum = _wtoi(b);
	} while ((TerminalNum==StartNum) || TerminalNum != 0 &&  TerminalNum != 1 && TerminalNum != 2 && TerminalNum != 3 && TerminalNum != 4 && TerminalNum != 5 && TerminalNum != 6);
	if (TerminalNum == 0)
		Menu();
	do
	{
		wchar_t c[10];
		InputBox(c, 10, L"请键入所要购买的车票张数 【1】~【99】，\n欲返回主菜单请输入【0】");
		TicketNum = _wtoi(c);
	} while (TicketNum <= -1 || TicketNum >= 100);
	if (TicketNum == 0)
		Menu();

	fee = abs(StartNum-TerminalNum)*PricePerTikect*TicketNum;                                      //计算车票费用
	settextcolor(BLACK);
	setbkcolor(RGB(255, 153, 204));
	settextstyle(20, 0, L"微软雅黑", 0, 0, 800, false, false, false);
	outtextxy(150, 90, L"您的行程是：");
	outtextxy(100, 150, L"从");
	outtextxy(220, 150, L"前往");
	outtextxy(500, 90, L"车票费用合计:");
	outtextxy(520, 150, L"张票");
	outtextxy(560, 150, L"合计");
	outtextxy(640, 150, L"元");	
	TCHAR s[5];
	swprintf_s(s, _T("%d"), TicketNum);
	TCHAR t[5];
	swprintf_s(t, _T("%d"), fee);
	settextcolor(GREEN);
	outtextxy(480, 150, s);
	outtextxy(600, 150, t);
	
	if (StartNum == 1)
	{
		outtextxy(150, 150, L"工大 站");
	}
	else if (StartNum == 2)
	{
		outtextxy(150, 150, L"清华 站");
	}
	else if (StartNum == 3)
	{
		outtextxy(150, 150, L"北大 站");
	}
	else if (StartNum == 4)
	{
		outtextxy(150, 150, L"体育馆 站");
	}
	else if (StartNum == 5)
	{
		outtextxy(150, 150, L"工大南门 站");
	}
	else if (StartNum == 6)
	{
		outtextxy(150, 150, L"5号线大学城 站");
	}
	if (TerminalNum == 1)
	{
		outtextxy(270, 150, L"工大 站");
	}
	else if (TerminalNum == 2)
	{
		outtextxy(270, 150, L"清华 站");
	}
	else if (TerminalNum == 3)
	{
		outtextxy(270, 150, L"北大 站");
	}
	else if (TerminalNum == 4)
	{
		outtextxy(270, 150, L"体育馆 站");
	}
	else if (TerminalNum == 5)
	{
		outtextxy(270, 150, L"工大南门 站");
	}
	else if (TerminalNum == 6)
	{
		outtextxy(270, 150, L"5号线大学城 站");
	}

	do
	{
		DrawPayButton(430,1);
		DrawEscapeButton(470,1);
		do
		{
			mouse = GetMouseMsg();
		} while ( !(In_rect({ 350,470,450,510 }, { mouse.x, mouse.y })) && !(In_rect({ 350,430,450,470 }, { mouse.x, mouse.y })));

		if (In_rect({ 350,430,450,470 }, { mouse.x, mouse.y }) && !mouse.mkLButton)
			DrawPayButton(430,2);
		if (In_rect({ 350,470,450,510 }, { mouse.x, mouse.y }) && !mouse.mkLButton)
			DrawEscapeButton(470,2);
		while(  ((In_rect({ 350,430,450,470 }, { mouse.x, mouse.y })) || (In_rect({ 350,470,450,510 }, { mouse.x, mouse.y }))) && !mouse.mkLButton)
			mouse = GetMouseMsg();
	} while (!mouse.mkLButton);
	cleardevice();

	if (In_rect({ 350,470,450,510 }, { mouse.x, mouse.y }) && mouse.mkLButton)
		Menu();
	if (In_rect({ 350,430,450,470 }, { mouse.x, mouse.y }) && mouse.mkLButton)
		Pay();

}

//查看线路图界面
void ShowMap()
{
	loadimage(NULL, _T("C:\\Users\\86135\\Desktop\\学习\\2020夏季学期\\创新训练B\\190320113_MetroTicketsPurchaseSystem_V1.0\\Pics\\Map.PNG"));
	do
	{
		DrawEscapeButton(70,1);
		do
		{
			mouse = GetMouseMsg();
		} while (!In_rect({ 350,70,450,110 }, { mouse.x, mouse.y }));

		DrawEscapeButton(70,2);
		while (In_rect({ 350,70,450,110 }, { mouse.x, mouse.y }) && !mouse.mkLButton)
			mouse = GetMouseMsg();
	} while (!mouse.mkLButton);
	cleardevice();

	if (In_rect({ 350,70,450,110 }, { mouse.x, mouse.y }) && mouse.mkLButton)
		Menu();
}

//投币找零界面
void Pay()
{
	int i = 0;
	TCHAR s[5];
click0:
	if (i >= fee)
	{
		do
		{
			DrawChangeButton(450, 150, 1);
			Draw10yuanButton(90, 150, 3);
			Draw5yuanButton(210, 150, 3);
			DrawEscapeButton(470, 3);
			do
			{
				mouse = GetMouseMsg();
			} while (!(In_rect({ 450,150,600,190 }, { mouse.x, mouse.y })));
			if (((In_rect({ 450,150,600,190 }, { mouse.x, mouse.y }))) && !mouse.mkLButton)
				DrawChangeButton(450, 150, 2);
			while ((In_rect({ 450,150,600,190 }, { mouse.x, mouse.y })) && !mouse.mkLButton)
				mouse = GetMouseMsg();
		} while (!mouse.mkLButton);

		if ((In_rect({ 450,150,600,190 }, { mouse.x, mouse.y })) && mouse.mkLButton)
		{
			settextcolor(BLACK);
			setbkcolor(RGB(255, 153, 204));
			settextstyle(40, 0, L"微软雅黑", 0, 0, 800, false, false, false);
			outtextxy(getwidth() / 2 - textwidth(L"购票成功！！！找零         元，请收好零钱与车票") / 2, 260, L"购票成功！！！找零         元，请收好零钱与车票");
			settextcolor(GREEN);
			int change;
			change = i - fee; //计算找零金额
			swprintf_s(s, _T("%d"), change);
			outtextxy(getwidth() / 2 - textwidth(L"购票成功！！！找零         元，请收好零钱与车票") / 2 + textwidth(L"购票成功！！！找零   "), 260, s);
			do
			{
				
				DrawEscapeButton(470, 1);
				do
				{
					mouse = GetMouseMsg();
				} while (!In_rect({ 350,470,450,510 }, { mouse.x, mouse.y }));
				if((In_rect({ 350,470,450,510 }, { mouse.x, mouse.y })) && !mouse.mkLButton)
					DrawEscapeButton(470, 2);
				while ((In_rect({ 350,470,450,510 }, { mouse.x, mouse.y }))  && !mouse.mkLButton)
					mouse = GetMouseMsg();
			} while (!mouse.mkLButton);

			if ((In_rect({ 350,470,450,510 }, { mouse.x, mouse.y })) && mouse.mkLButton)
			{
				begin();
			}
		}
	}
	else
	{
		DrawBackground();
		settextcolor(BLACK);
		setbkcolor(RGB(255, 153, 204));
		settextstyle(20, 0, L"微软雅黑", 0, 0, 800, false, false, false);
		outtextxy(150, 90, L"共需               元，您已投币：                     元");
		settextcolor(GREEN);
		setbkcolor(RGB(255, 153, 204));
		TCHAR p[5];
		swprintf_s(p, _T("%d"), fee);
		settextstyle(30, 0, L"微软雅黑", 0, 0, 800, false, false, false);
		outtextxy(190, 80, p);

		swprintf_s(s, _T("%d"), i);
		outtextxy(350, 80, s);

		DrawChangeButton(450, 150, 3);

		do
		{
			Draw10yuanButton(90, 150, 1);
			Draw5yuanButton(210, 150, 1);
			DrawEscapeButton(470, 1);
			do
			{
				mouse = GetMouseMsg();
			} while (!(In_rect({ 90,150,190,190 }, { mouse.x, mouse.y })) && (!In_rect({ 350,470,450,510 }, { mouse.x, mouse.y })) && (!In_rect({ 210,150,310,190 }, { mouse.x, mouse.y })));


			if (In_rect({ 90,150,190,190 }, { mouse.x, mouse.y }) && !mouse.mkLButton)
				Draw10yuanButton(90, 150, 2);
			if (In_rect({ 210,150,310,190 }, { mouse.x, mouse.y }) && !mouse.mkLButton)
				Draw5yuanButton(210, 150, 2);
			if (In_rect({ 350,470,450,510 }, { mouse.x, mouse.y }) && !mouse.mkLButton)
				DrawEscapeButton(470, 2);
			while (((In_rect({ 90,150,190,190 }, { mouse.x, mouse.y })) || (In_rect({ 350,470,450,510 }, { mouse.x, mouse.y })) || (In_rect({ 210,150,310,190 }, { mouse.x, mouse.y }))) && !mouse.mkLButton)
				mouse = GetMouseMsg();
		} while (!mouse.mkLButton);

		if ((In_rect({ 350,470,450,510 }, { mouse.x, mouse.y })) && mouse.mkLButton)
			Menu();

		//模拟投10一张	
		if ((In_rect({ 90,150,190,190 }, { mouse.x, mouse.y })) && mouse.mkLButton)
		{
			i += 10;
			swprintf_s(s, _T("%d"), i);
			settextcolor(GREEN);
			setbkcolor(RGB(255, 153, 204));
			settextstyle(30, 0, L"微软雅黑", 0, 0, 800, false, false, false);
			outtextxy(350, 80, s);
			do
			{
				Draw10yuanButton(90, 150, 1);
				DrawEscapeButton(470, 3);
				do
				{
					mouse = GetMouseMsg();
				} while ((!(In_rect({ 90,150,190,190 }, { mouse.x, mouse.y }))) && (!(In_rect({ 210,150,310,190 }, { mouse.x, mouse.y }))));
				Draw10yuanButton(90, 150, 2);
				while ((In_rect({ 90,150,190,190 }, { mouse.x, mouse.y })) || (In_rect({ 210,150,310,190 }, { mouse.x, mouse.y })) && !mouse.mkLButton)
					mouse = GetMouseMsg();
				goto click0;
			} while (!mouse.mkLButton);
		}

		//模拟投币5元一张
		if ((In_rect({ 210,150,310,190 }, { mouse.x, mouse.y })) && mouse.mkLButton)
		{
			i += 5;
			swprintf_s(s, _T("%d"), i);
			settextcolor(GREEN);
			setbkcolor(RGB(255, 153, 204));
			settextstyle(30, 0, L"微软雅黑", 0, 0, 800, false, false, false);
			outtextxy(350, 80, s);
			do
			{
				Draw5yuanButton(210, 150, 1);
				DrawEscapeButton(470, 3);
				do
				{
					mouse = GetMouseMsg();
				} while ((!(In_rect({ 90,150,190,190 }, { mouse.x, mouse.y }))) && (!(In_rect({ 210,150,310,190 }, { mouse.x, mouse.y }))));
				Draw5yuanButton(210, 150, 2);
				while ((In_rect({ 90,150,190,190 }, { mouse.x, mouse.y })) || (In_rect({ 210,150,310,190 }, { mouse.x, mouse.y })) && !mouse.mkLButton)
					mouse = GetMouseMsg();
				goto click0;
			} while (!mouse.mkLButton);
		}
	}



}