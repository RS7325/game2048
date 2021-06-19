#include<graphics.h>
#include<conio.h>
#include<stdlib.h>
#include<time.h>
#include<iostream>


int map[4][4] = {
				{0,0,0,0},
				{0,0,0,0},
				{0,0,0,0},
				{0,0,0,0}
};//初始化map数组

int WIDTH = 700; //界面宽
int HEIGHT = 900;  //界面高
int score;//计算分数
int bestScore = 0;
int flag = 0;//填充背景用
int pass;//用来判断是否要放置新数字
int level = 0;//游戏难度
char LEVEL[10] = { 0 };//用于显示难度

void main_menu();//首界面
void info();//游戏介绍
void OI();//操作说明
void pause();//继续游戏界面
void info_2();//操作说明(游戏中)
void refresh(int score);//分数刷新
void show_bk1();//游戏界面背景
void placeElem(int x, int y, int num, int score);//放置元素
void _init();//初始化界面
void game_rand_1();//随机256||512数字
void game_rand_2();//随机2||4数字
void interact();//调用移动判断函数
void interact_up();//向上移动判断
void interact_down();//向下移动判断
void interact_left();//向左移动判断
void interact_right();//向右移动判断
void game();//游戏初始化和运行
void game_resume();//继续游戏
void game_resume_noLimited();//无尽模式:（
int give_up();//游戏认输
int  game_win();//游戏胜利
void game_failed();//游戏失败
int  game_check();//胜负条件检查
void game_clear();//游戏清屏
void base_loop();//数字块的循环放置
void selectLevel();//难度选择



void show_bk1()//游戏界面背景
{
	setbkcolor(RGB(250, 248, 239));//背景色
	IMAGE img0, img2, img4, img8, img16, img32, img64, img128, img256, img512, img1024, img2048;
	settextstyle(80, 0, "黑体");
	settextcolor(RGB(120, 116, 101));
	outtextxy(35, 0, "2048");

	RECT r1 = { 30,150,200,190 };
	RECT r2 = { 200,150,280,190 };
	RECT r3 = { 350,110,720,150 };
	RECT r4 = { 350,150,720,190 };


	settextstyle(30, 0, "黑体");
	if (level == 1) strcpy(LEVEL, "简单");
	else if (level == 2)strcpy(LEVEL, "普通");
	drawtext("难度：", &r1, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	drawtext(LEVEL, &r2, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	settextstyle(20, 0, "黑体");
	drawtext("Press \"ESC\" to pause", &r3, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	drawtext("Press \"G\" to give up", &r4, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	setfillcolor(RGB(184, 175, 160));//右上角 SCORE框和 BEST框
	solidroundrect(390, 30, 530, 100, 15, 15);
	settextstyle(28, 0, "Microsoft Yahei UI Bold");
	setbkcolor(RGB(184, 175, 160));
	settextcolor(RGB(248, 247, 241));
	outtextxy(425, 35, "SCORE");
	solidroundrect(550, 30, 690, 100, 15, 15);
	outtextxy(595, 35, "BEST");

	setfillcolor(RGB(187, 173, 160));//下方游戏区域
	solidroundrect(10, 210, 690, 890, 20, 20);

}

void selectLevel()//游戏暂停等
{
	cleardevice();
	setbkcolor(RGB(251, 248, 241));
	settextcolor(RGB(150, 126, 104));
	settextstyle(70, 0, "方正行黑简体");
	RECT r1 = { 0, 0, WIDTH, HEIGHT / 3 };
	drawtext("请选择您的难度", &r1, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	settextstyle(30, 0, "微软雅黑");

	RECT r2 = { WIDTH / 2 - 45,HEIGHT / 3 - 30,WIDTH / 2 + 45,HEIGHT / 3 };
	drawtext("简单难度", &r2, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	RECT r3 = { WIDTH / 2 - 45,HEIGHT / 3 + 30,WIDTH / 2 + 45,HEIGHT / 3 + 60 };
	drawtext("普通难度", &r3, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	RECT r4 = { WIDTH / 2 - 45,HEIGHT / 3 + 90,WIDTH / 2 + 45,HEIGHT / 3 + 120 };
	drawtext("返回", &r4, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	setbkcolor(RGB(251, 248, 241));
	settextcolor(RGB(150, 126, 104));
	settextstyle(30, 0, "Microsoft Yahei UI");


	MOUSEMSG m;
	while (1)
	{

		BeginBatchDraw();
		m = GetMouseMsg();
		switch (m.uMsg)
		{
		case WM_MOUSEMOVE://获取鼠标移动
			EndBatchDraw();
			setlinecolor(RGB(230, 20, 20));
			setlinestyle(PS_SOLID | PS_JOIN_BEVEL, 2);

			if (m.x > WIDTH / 2 - 45 && m.x<WIDTH / 2 + 45 && m.y>HEIGHT / 3 - 30 && m.y < HEIGHT / 3)
			{
				rectangle(WIDTH / 2 - 45, HEIGHT / 3 - 30, WIDTH / 2 + 45, HEIGHT / 3);
				break;
			}
			else if (m.x > WIDTH / 2 - 45 && m.x<WIDTH / 2 + 45 && m.y>HEIGHT / 3 + 30 && m.y < HEIGHT / 3 + 60)
			{
				rectangle(WIDTH / 2 - 45, HEIGHT / 3 + 30, WIDTH / 2 + 45, HEIGHT / 3 + 60);
				break;
			}
			else if (m.x > WIDTH / 2 - 45 && m.x<WIDTH / 2 + 45 && m.y>HEIGHT / 3 + 90 && m.y < HEIGHT / 3 + 120)
			{
				rectangle(WIDTH / 2 - 45, HEIGHT / 3 + 90, WIDTH / 2 + 45, HEIGHT / 3 + 120);
				break;
			}
			else {
				setlinecolor(RGB(251, 248, 241));
				setlinestyle(PS_SOLID | PS_JOIN_BEVEL, 5);
				rectangle(WIDTH / 2 - 45, HEIGHT / 3 - 30, WIDTH / 2 + 45, HEIGHT / 3);
				rectangle(WIDTH / 2 - 45, HEIGHT / 3 + 30, WIDTH / 2 + 45, HEIGHT / 3 + 60);
				rectangle(WIDTH / 2 - 45, HEIGHT / 3 + 90, WIDTH / 2 + 45, HEIGHT / 3 + 120);

			}
			break;
		case WM_LBUTTONDOWN:
			EndBatchDraw();
			if (m.x > WIDTH / 2 - 45 && m.x<WIDTH / 2 + 45 && m.y>HEIGHT / 3 - 30 && m.y < HEIGHT / 3)
			{
				level = 1;
				cleardevice();
				flag = 0;
				game_clear();
				game();
				break;
			}

			else if (m.x > WIDTH / 2 - 45 && m.x<WIDTH / 2 + 45 && m.y>HEIGHT / 3 + 30 && m.y < HEIGHT / 3 + 60)
			{
				level = 2;
				cleardevice();
				flag = 0;
				game_clear();
				game();
				break;
			}

			else if (m.x > WIDTH / 2 - 45 && m.x<WIDTH / 2 + 45 && m.y>HEIGHT / 3 + 90 && m.y < HEIGHT / 3 + 120)
			{
				cleardevice();
				flag = 0;
				main_menu();
				break;
			}


			break;
		}
	}
	_getch();
}


void refresh(int score) {//分数刷新
	char str[10], best_str[10] = { 0 };
	setbkcolor(RGB(184, 175, 160));
	_itoa(score, str, 10);
	outtextxy(440, 65, str);//分数
	if (score >= bestScore) {
		bestScore = score;
		_itoa(bestScore, best_str, 10);
		outtextxy(610, 65, best_str);//最好分数
	}
	if (flag == 0)
		show_bk1();
	flag++;
}

void placeElem(int x, int y, int num, int score)
{
	setbkcolor(RGB(251, 248, 241));//背景色
	IMAGE img0, img2, img4, img8, img16, img32, img64, img128, img256, img512, img1024, img2048;
	refresh(score);

	switch (num)//调取图片
	{
	case 0:loadimage(&img0, "pic\\0.jpg"); putimage(x * 165 + 30, y * 165 + 230, &img0); break;
	case 2:loadimage(&img2, "pic\\2.jpg"); putimage(x * 165 + 30, y * 165 + 230, &img2); break;
	case 4:loadimage(&img4, "pic\\4.jpg"); putimage(x * 165 + 30, y * 165 + 230, &img4); break;
	case 8:loadimage(&img8, "pic\\8.jpg"); putimage(x * 165 + 30, y * 165 + 230, &img8); break;
	case 16:loadimage(&img16, "pic\\16.jpg"); putimage(x * 165 + 30, y * 165 + 230, &img16); break;
	case 32:loadimage(&img32, "pic\\32.jpg"); putimage(x * 165 + 30, y * 165 + 230, &img32); break;
	case 64:loadimage(&img64, "pic\\64.jpg"); putimage(x * 165 + 30, y * 165 + 230, &img64); break;
	case 128:loadimage(&img128, "pic\\128.jpg"); putimage(x * 165 + 30, y * 165 + 230, &img128); break;
	case 256:loadimage(&img256, "pic\\256.jpg"); putimage(x * 165 + 30, y * 165 + 230, &img256); break;
	case 512:loadimage(&img512, "pic\\512.jpg"); putimage(x * 165 + 30, y * 165 + 230, &img512); break;
	case 1024:loadimage(&img1024, "pic\\1024.jpg"); putimage(x * 165 + 30, y * 165 + 230, &img1024); break;
	case 2048:loadimage(&img2048, "pic\\2048.jpg"); putimage(x * 165 + 30, y * 165 + 230, &img2048); break;
	}
}

void _init()//初始化界面
{
	initgraph(WIDTH, HEIGHT);//长宽
	setbkcolor(RGB(251, 248, 241));//背景
	settextcolor(RGB(150, 126, 104));
	main_menu();
}



void main_menu()//首界面
{
	cleardevice();

	settextstyle(100, 0, "黑体");
	LOGFONT f;
	gettextstyle(&f);
	_tcscpy(f.lfFaceName, _T("黑体"));
	f.lfQuality = ANTIALIASED_QUALITY;
	settextstyle(&f);

	RECT r1 = { 0, 0, WIDTH, HEIGHT / 3 };

	drawtext("2048", &r1, DT_CENTER | DT_VCENTER | DT_SINGLELINE);


	RECT r2 = { WIDTH / 2 - 80,HEIGHT / 2,WIDTH / 2 + 80,HEIGHT / 2 + 50 };
	RECT r3 = { WIDTH / 2 - 80,HEIGHT / 2 + 70,WIDTH / 2 + 80,HEIGHT / 2 + 120 };
	RECT r4 = { WIDTH / 2 - 80,HEIGHT / 2 + 140,WIDTH / 2 + 80,HEIGHT / 2 + 190 };
	RECT r5 = { WIDTH / 2 - 80,HEIGHT / 2 + 210,WIDTH / 2 + 80,HEIGHT / 2 + 260 };

	settextstyle(30, 0, "黑体");
	LOGFONT f1;
	gettextstyle(&f1);					//获取字体样式
	f1.lfQuality = ANTIALIASED_QUALITY;    // 设置输出效果为抗锯齿  
	settextstyle(&f1);                     // 设置字体样式
	settextcolor(BLACK);				//BLACK在graphic.h头文件里面被定义为黑色的颜色常量

	drawtext("开始游戏", &r2, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	drawtext("游戏介绍", &r3, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	drawtext("操作说明", &r4, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	drawtext("退出游戏", &r5, DT_CENTER | DT_VCENTER | DT_SINGLELINE);


	setfillcolor(RGB(115, 106, 98));
	solidroundrect(216, 50, 484, 318, 50, 50);
	settextstyle(145, 0, "微软雅黑");
	setbkcolor(RGB(115, 106, 98));
	settextcolor(RGB(254, 253, 249));
	outtextxy(216, 107, "2048");

	setbkcolor(RGB(251, 248, 241));
	settextcolor(RGB(254, 253, 249));
	settextstyle(30, 0, "Microsoft Yahei UI");

	MOUSEMSG m;//鼠标点击位置的判断
	while (1)
	{
		BeginBatchDraw();
		m = GetMouseMsg();
		switch (m.uMsg)
		{
		case WM_MOUSEMOVE://获取鼠标移动
			EndBatchDraw();
			setlinecolor(RGB(230, 20, 20));
			setlinestyle(PS_SOLID | PS_JOIN_BEVEL, 5);

			if (m.x > WIDTH / 2 - 82 && m.x<WIDTH / 2 + 82 && m.y>HEIGHT / 2 - 1 && m.y < HEIGHT / 2 + 50)
			{
				rectangle(WIDTH / 2 - 82, HEIGHT / 2 - 1, WIDTH / 2 + 82, HEIGHT / 2 + 50);
				break;
			}
			else if (m.x > WIDTH / 2 - 82 && m.x<WIDTH / 2 + 82 && m.y>HEIGHT / 2 + 69 && m.y < HEIGHT / 2 + 120)
			{
				rectangle(WIDTH / 2 - 82, HEIGHT / 2 + 69, WIDTH / 2 + 82, HEIGHT / 2 + 120);
				break;
			}
			else if (m.x > WIDTH / 2 - 82 && m.x < WIDTH / 2 + 82 && m.y > HEIGHT / 2 + 139 && m.y < HEIGHT / 2 + 190)
			{
				rectangle(WIDTH / 2 - 82, HEIGHT / 2 + 139, WIDTH / 2 + 82, HEIGHT / 2 + 190);
				break;
			}
			else if (m.x > WIDTH / 2 - 82 && m.x < WIDTH / 2 + 82 && m.y > HEIGHT / 2 + 209 && m.y < HEIGHT / 2 + 260)
			{
				rectangle(WIDTH / 2 - 82, HEIGHT / 2 + 209, WIDTH / 2 + 82, HEIGHT / 2 + 260);
				break;
			}
			else {
				setlinecolor(RGB(251, 248, 241));
				setlinestyle(PS_SOLID | PS_JOIN_BEVEL, 10);
				rectangle(WIDTH / 2 - 82, HEIGHT / 2 - 1, WIDTH / 2 + 82, HEIGHT / 2 + 50);
				rectangle(WIDTH / 2 - 82, HEIGHT / 2 + 69, WIDTH / 2 + 82, HEIGHT / 2 + 120);
				rectangle(WIDTH / 2 - 82, HEIGHT / 2 + 139, WIDTH / 2 + 82, HEIGHT / 2 + 190);
				rectangle(WIDTH / 2 - 82, HEIGHT / 2 + 209, WIDTH / 2 + 82, HEIGHT / 2 + 260);
			}
			break;
		case WM_LBUTTONDOWN:
			EndBatchDraw();
			if (m.x > WIDTH / 2 - 82 && m.x<WIDTH / 2 + 82 && m.y>HEIGHT / 2 - 1 && m.y < HEIGHT / 2 + 50)//开始游戏
			{
				game_clear();
				cleardevice();
				flag = 0;
				selectLevel();
				//game_win();
				//game_failed();
				break;
			}
			else if (m.x > WIDTH / 2 - 82 && m.x<WIDTH / 2 + 82 && m.y>HEIGHT / 2 + 69 && m.y < HEIGHT / 2 + 120)//游戏介绍
			{
				info();
				break;
			}
			else if (m.x > WIDTH / 2 - 82 && m.x < WIDTH / 2 + 82 && m.y > HEIGHT / 2 + 139 && m.y < HEIGHT / 2 + 190)//操作说明
			{
				OI();
				break;
			}
			else if (m.x > WIDTH / 2 - 82 && m.x < WIDTH / 2 + 82 && m.y > HEIGHT / 2 + 209 && m.y < HEIGHT / 2 + 260)//退出游戏
			{
				exit(0);
			}
			break;
		}
	}
	_getch();
}

void info()//游戏介绍
{
	cleardevice();
	RECT C2 = { 60,60,640,790 };
	settextcolor(BLACK);
	drawtext("\n\n\n\n\n\n游戏介绍：\n\n\n\n每次可以选择上下左右滑动，每滑动一次，所有的数字方块都会往滑动的方向靠拢，系统也会在白的地方随机出现一个数字方块，相同数字的方块在靠拢、相撞时会相加。不断的叠加最终拼凑出2048这个数字就算成功。", &C2, DT_WORDBREAK);


	RECT R1 = { WIDTH - WIDTH + 2,HEIGHT - 200,WIDTH - 2,HEIGHT - 2 };
	drawtext("返回", &R1, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	MOUSEMSG m;
	while (1)//返回键的设置
	{
		m = GetMouseMsg();
		switch (m.uMsg)
		{
		case WM_LBUTTONDOWN:
			if (m.x > WIDTH - WIDTH + 2 && m.x<WIDTH - 2 && m.y>HEIGHT - 200 && m.y < HEIGHT - 2)
				main_menu();
		}
	}
}

void OI()//操作说明
{
	cleardevice();
	RECT C3 = { 60,60,640,790 };
	settextcolor(BLACK);
	drawtext("\n\n\n操作说明：\n\n左移：方向键 ←\n\n右移：方向键 →\n\n上移：方向键 ↑\n\n下移：方向键 ↓\n\n", &C3, DT_WORDBREAK);
	RECT R1 = { WIDTH - WIDTH + 2,HEIGHT - 200,WIDTH - 2,HEIGHT - 2 };
	drawtext("返回", &R1, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	MOUSEMSG m;
	while (1)//返回键的设置
	{
		m = GetMouseMsg();
		switch (m.uMsg)
		{
		case WM_LBUTTONDOWN:
			if (m.x > WIDTH - WIDTH + 2 && m.x<WIDTH - 2 && m.y>HEIGHT - 200 && m.y < HEIGHT - 2)
				main_menu();
		}
	}
}

void pause()
{
	cleardevice();
	setbkcolor(RGB(251, 248, 241));
	settextcolor(RGB(150, 126, 104));
	settextstyle(70, 0, "方正行黑简体");
	RECT r1 = { 0, 0, WIDTH, HEIGHT / 3 };
	drawtext("暂停中", &r1, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	settextstyle(30, 0, "微软雅黑");

	RECT r6 = { WIDTH / 2 - 45,HEIGHT / 3 - 30,WIDTH / 2 + 45,HEIGHT / 3 };
	drawtext("新游戏", &r6, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	RECT r2 = { WIDTH / 2 - 100,HEIGHT / 3 + 30,WIDTH / 2 + 100,HEIGHT / 3 + 60 };
	drawtext("继续游戏", &r2, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	RECT r3 = { WIDTH / 2 - 100,HEIGHT / 3 + 90,WIDTH / 2 + 100,HEIGHT / 3 + 120 };
	drawtext("返回主菜单", &r3, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	RECT r4 = { WIDTH / 2 - 100,HEIGHT / 3 + 150,WIDTH / 2 + 100,HEIGHT / 3 + 180 };
	drawtext("操作说明", &r4, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	RECT r5 = { WIDTH / 2 - 100,HEIGHT / 3 + 210,WIDTH / 2 + 100,HEIGHT / 3 + 240 };
	drawtext("退出游戏", &r5, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	setbkcolor(RGB(251, 248, 241));
	settextcolor(RGB(150, 126, 104));
	settextstyle(30, 0, "Microsoft Yahei UI");


	MOUSEMSG m;
	while (1)
	{
		BeginBatchDraw();
		m = GetMouseMsg();
		switch (m.uMsg)
		{
		case WM_MOUSEMOVE://获取鼠标移动
			EndBatchDraw();
			setlinecolor(RGB(230, 20, 20));
			setlinestyle(PS_SOLID | PS_JOIN_BEVEL, 2);

			if (m.x > WIDTH / 2 - 100 && m.x<WIDTH / 2 + 100 && m.y>HEIGHT / 3 - 30 && m.y < HEIGHT / 3)
			{
				rectangle(WIDTH / 2 - 45, HEIGHT / 3 - 30, WIDTH / 2 + 45, HEIGHT / 3);
				break;
			}
			else if (m.x > WIDTH / 2 - 100 && m.x<WIDTH / 2 + 100 && m.y>HEIGHT / 3 + 30 && m.y < HEIGHT / 3 + 60)
			{
				rectangle(WIDTH / 2 - 100, HEIGHT / 3 + 30, WIDTH / 2 + 100, HEIGHT / 3 + 60);
				break;
			}
			else if (m.x > WIDTH / 2 - 100 && m.x<WIDTH / 2 + 100 && m.y>HEIGHT / 3 + 90 && m.y < HEIGHT / 3 + 120)
			{
				rectangle(WIDTH / 2 - 100, HEIGHT / 3 + 90, WIDTH / 2 + 100, HEIGHT / 3 + 120);
				break;
			}
			else if (m.x > WIDTH / 2 - 100 && m.x<WIDTH / 2 + 100 && m.y>HEIGHT / 3 + 150 && m.y < HEIGHT / 3 + 180)
			{
				rectangle(WIDTH / 2 - 100, HEIGHT / 3 + 150, WIDTH / 2 + 100, HEIGHT / 3 + 180);
				break;
			}
			else if (m.x > WIDTH / 2 - 100 && m.x<WIDTH / 2 + 100 && m.y>HEIGHT / 3 + 210 && m.y < HEIGHT / 3 + 240)
			{
				rectangle(WIDTH / 2 - 100, HEIGHT / 3 + 210, WIDTH / 2 + 100, HEIGHT / 3 + 240);
				break;
			}
			else {
				setlinecolor(RGB(251, 248, 241));
				setlinestyle(PS_SOLID | PS_JOIN_BEVEL, 10);
				rectangle(WIDTH / 2 - 45, HEIGHT / 3 - 30, WIDTH / 2 + 45, HEIGHT / 3 + 2);
				rectangle(WIDTH / 2 - 100, HEIGHT / 3 + 30, WIDTH / 2 + 100, HEIGHT / 3 + 62);
				rectangle(WIDTH / 2 - 100, HEIGHT / 3 + 90, WIDTH / 2 + 100, HEIGHT / 3 + 122);
				rectangle(WIDTH / 2 - 100, HEIGHT / 3 + 150, WIDTH / 2 + 100, HEIGHT / 3 + 182);
				rectangle(WIDTH / 2 - 100, HEIGHT / 3 + 210, WIDTH / 2 + 100, HEIGHT / 3 + 242);
			}
			break;
		case WM_LBUTTONDOWN:
			EndBatchDraw();
			if (m.x > WIDTH / 2 - 100 && m.x<WIDTH / 2 + 100 && m.y>HEIGHT / 3 - 30 && m.y < HEIGHT / 3)
			{
				cleardevice();
				flag = 0;
				game_clear();
				game();
				break;
			}
			else if (m.x > WIDTH / 2 - 100 && m.x<WIDTH / 2 + 100 && m.y>HEIGHT / 3 + 30 && m.y < HEIGHT / 3 + 60)
			{
				cleardevice();
				flag = 0;
				game_resume();
				break;
			}
			else if (m.x > WIDTH / 2 - 100 && m.x<WIDTH / 2 + 100 && m.y>HEIGHT / 3 + 90 && m.y < HEIGHT / 3 + 120)
			{
				cleardevice();
				_init();
				break;
			}
			else if (m.x > WIDTH / 2 - 100 && m.x<WIDTH / 2 + 100 && m.y>HEIGHT / 3 + 150 && m.y < HEIGHT / 3 + 180)
			{
				info_2();
				break;
			}
			else if (m.x > WIDTH / 2 - 100 && m.x<WIDTH / 2 + 100 && m.y>HEIGHT / 3 + 210 && m.y < HEIGHT / 3 + 240)
			{
				exit(0);
			}
			break;
		}
	}
	_getch();
}

int give_up()//认输界面
{
	//setbkmode(TRANSPARENT);
	setbkcolor(RGB(250, 240, 230));//背景色
	COLORREF ref;
	int r, g, b;
	int x, y;
	char* yes, * no, * giveup;
	srand((int)time(0));
	BeginBatchDraw();
	FlushBatchDraw();
	EndBatchDraw();
	yes = "确定";
	no = "取消";
	giveup = "请问您是否要认输?";
	settextcolor(BLUE);
	settextstyle(100, 30, "楷体");
	outtextxy(WIDTH / 2 - 220, 50, giveup);
	settextstyle(50, 25, "楷体");
	settextcolor(GREEN);
	settextcolor(BLUE);
	outtextxy(220, 250, yes);
	outtextxy(420, 250, no);
	setfillcolor(RED);

	MOUSEMSG m;//鼠标点击继续游戏或者退出
	while (1) {
		FlushMouseMsgBuffer();
		m = GetMouseMsg();
		if (m.uMsg == WM_LBUTTONDOWN)
		{
			x = m.x; y = m.y;
			if (x > 220 && x < 320 && y>250 && y < 300)
			{
				cleardevice();
				game_failed();
				return 1;
				break;
			}
			if (x > 420 && x < 520 && y>250 && y < 300)
			{
				setbkcolor(RGB(250, 248, 239));//背景色
				cleardevice();
				flag = 0;
				game_resume();
				return 2;
				break;
			}
		}
	}
}


void info_2()//操作说明
{
	cleardevice();
	RECT C3 = { 60,60,640,790 };
	settextcolor(BLACK);
	drawtext("\n\n\n操作说明：\n\n左移：方向键 ←\n\n右移：方向键 →\n\n上移：方向键 ↑\n\n下移：方向键 ↓\n\n", &C3, DT_WORDBREAK);
	RECT R1 = { WIDTH - WIDTH + 2,HEIGHT - 200,WIDTH - 2,HEIGHT - 2 };
	drawtext("返回", &R1, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	MOUSEMSG m;
	while (1)//返回键的设置
	{
		m = GetMouseMsg();
		switch (m.uMsg)
		{
		case WM_LBUTTONDOWN:
			if (m.x > WIDTH - WIDTH + 2 && m.x<WIDTH - 2 && m.y>HEIGHT - 200 && m.y < HEIGHT - 2)
			cleardevice();
			flag = 0;
			game_resume();
		}
	}
}

int game_win()//游戏成功界面
{
	setbkcolor(RGB(250, 248, 239));
	COLORREF ref;
	int r, g, b;
	int x, y;
	char* yes, * no, * giveup;
	srand((int)time(0));
	BeginBatchDraw();
	for (x = 0; x < 700; x++)
	{
		for (y = 0; y < 900; y++){
			ref = getpixel(x, y);
			r = GetRValue(ref);
			g = GetGValue(ref);
			b = GetBValue(ref);
			putpixel(x, y, RGB(r * 0.5, g * 0.5, b * 0.5));
		}
	}

	FlushBatchDraw();
	EndBatchDraw();
	yes = "确定";
	no = "退出";
	giveup = "游戏胜利！";
	for (x = 0; x < 10; x++)
	{
		settextcolor(RGB(rand() % 255, rand() % 255, rand() % 255));
		settextstyle(100, 50, "黑体");
		outtextxy(WIDTH / 2 - 250, 50, giveup);
		Sleep(200);
	}

	settextstyle(50, 25, "黑体");
	settextcolor(GREEN);
	outtextxy(WIDTH / 2 - 70, 150, "继续？");
	settextcolor(BLUE);
	outtextxy(220, 250, yes);
	outtextxy(420, 250, no);
	setfillcolor(RED);

	MOUSEMSG m;//鼠标点击继续游戏或者退出
	while (1) {
		FlushMouseMsgBuffer();
		m = GetMouseMsg();
		if (m.uMsg == WM_LBUTTONDOWN)
		{
			x = m.x; y = m.y;
			if (x > 220 && x < 320 && y>250 && y < 300)
			{
				cleardevice();
				setbkcolor(RGB(250, 248, 239));//背景色
				show_bk1();
				game_resume_noLimited();
				return 1;
			}
			if (x > 420 && x < 520 && y>250 && y < 300)
			{
				cleardevice();
				setbkcolor(RGB(251, 248, 241));
				main_menu();
				return 2;
			}
		}
	}
}

void game_failed()//游戏失败界面
{
	COLORREF ref;
	int r, g, b;
	int x, y;
	srand((int)time(0));
	BeginBatchDraw();
	FlushBatchDraw();
	EndBatchDraw();

	for (x = 0; x < 5; x++)
	{
		settextcolor(RGB(rand() % 255, rand() % 255, rand() % 255));
		settextstyle(80, 40, "黑体");
		outtextxy(WIDTH / 2 - 100, HEIGHT / 2 - 100, "失败！");
		Sleep(200);
	}

	settextstyle(50, 0, "黑体");
	settextcolor(GREEN);
	outtextxy(WIDTH / 3 + 90, HEIGHT / 2 + 50, "OK");

	MOUSEMSG m;
	while (1)
	{
		FlushMouseMsgBuffer();
		m = GetMouseMsg();
		if (m.uMsg == WM_LBUTTONDOWN)
		{
			x = m.x;
			y = m.y;

			if (x > WIDTH / 3 + 90 && x<WIDTH / 3 + 140 && y>HEIGHT / 2 + 50 && y < HEIGHT / 2 + 100)
			{
				cleardevice();
				setbkcolor(RGB(251, 248, 241));
				main_menu();
				break;
			}
		}
	}
}

void game()//游戏的初始化和运行
{

	while (1)
	{

		score = 0;//分数初始化
		if (level == 1) {
			game_rand_1();//随机生成两个数
			game_rand_1();
		}
		else if (level == 2) {
			game_rand_2();
			game_rand_2();
		}

		base_loop();//放数字
		while (1)
		{
			if (_kbhit)//按键
			{
				pass = 0;
				interact();//方向走
				fflush(stdin);//清空输入缓存
				if (pass) {
					if (level == 1) {
						game_rand_1();
					}
					else if (level == 2) {
						game_rand_2();

					}
				}
				if (game_check())//检查 详见check函数
				{
					if (game_check() == 1)//检查 详见check函数
					{
						if (game_win() == 1) {
							setbkcolor(RGB(250, 248, 239));//背景色
							break;//进入 无尽模式
						}

					}
					else if (game_check() == -1)//检查 详见check函数
					{
						base_loop();
						game_failed();
						break;
					}
				}
				base_loop();//放数字
			}
			else Sleep(1);
		}
		game_clear();//清屏
		continue;
	}
}

void game_resume()
{
	show_bk1();
	base_loop();
	while (1)
	{
		if (_kbhit)//按键
		{
			pass = 0;
			interact();//方向走
			fflush(stdin);//清空输入缓存
			if (pass) {
				if (level == 1) {//随机生成两个数
					game_rand_1();
				}
				else if (level == 2) {
					game_rand_2();
				}
			}
			if (game_check())//检查
			{
				if (game_check() == 1)//检查
				{
					if (game_win() == 2) {
						main_menu();
						break;
					}//胜利界面

				}
				else if (game_check() == -1)//检查
				{
					base_loop();
					game_failed();
					break;
				}
			}
			base_loop();//放置数字
		}
		else Sleep(1);
	}
	game_clear();//清屏
}

void game_resume_noLimited()
{

	show_bk1();
	base_loop();
	while (1)
	{
		if (_kbhit)//按键
		{
			pass = 0;
			interact();//方向走
			fflush(stdin);//清空输入缓存
			if (pass) {
				if (level == 1) {
					game_rand_1();//随机出来两个数
				}
				else if (level == 2) {
					game_rand_2();//随机出来两个数
				}
			}
			base_loop();//放数字
		}
		else Sleep(1);
	}
	game_clear();//清屏
}

void game_rand_1()//随机256 512(难度1)
{
	int x, y, temp, num;
	srand((int)time(0));
	while (1)
	{
		x = rand() % 4;
		y = rand() % 4;
		temp = rand() % 5;
		if (temp == 1)num = 256;
		else num = 512;
		if (map[y][x] == 0)
		{
			map[y][x] = num;//放数字
			break;
		}
	}
}

void game_rand_2()//随机2 4(难度2)
{
	int x, y, temp, num;
	srand((int)time(0));
	while (1)
	{
		x = rand() % 4;
		y = rand() % 4;
		temp = rand() % 5;
		if (temp == 1)num = 4;//随机4
		else num = 2;//随机2
		if (map[y][x] == 0)
		{
			map[y][x] = num;//放数字
			break;
		}
	}
}

void interact()//在游戏中获取按键和鼠标
{
	char keyboard;
	keyboard = _getch();
	if (keyboard == 'w' || keyboard == 'W' || keyboard == 72)interact_up();//上
	if (keyboard == 's' || keyboard == 'S' || keyboard == 80)interact_down();//下
	if (keyboard == 'a' || keyboard == 'A' || keyboard == 75)interact_left();//左
	if (keyboard == 'd' || keyboard == 'D' || keyboard == 77)interact_right();//右
	if (keyboard == 27)//esc主菜单
	{
		flag = 0;
		setbkcolor(RGB(251, 248, 241));
		pause();
	}
	if (keyboard == 'G' || keyboard == 'g') {
		give_up();
	}
}

void interact_up()//向上移动
{
	int n, i, j, k;
	for (n = 0; n < 4; n++)
	{
		k = 0;
		for (i = 0; i < 4; i++)
		{
			if (map[i][n] != 0)
			{
				for (j = i; j > k; j--)
				{
					if (map[j - 1][n] == 0)//上面没数
					{
						map[j - 1][n] = map[j][n];
						map[j][n] = 0;
						pass = 1;
						base_loop();
					}
					else if (map[j - 1][n] == map[j][n])//上面有可合并数字
					{
						map[j - 1][n] = 2 * map[j - 1][n];
						score += map[j - 1][n];
						map[j][n] = 0;
						k = j;
						pass = 1;
						base_loop();
						break;
					}
					else break;
				}
			}
		}
	}
}

void interact_down()//向下移动
{
	int n, i, j, k;
	for (n = 0; n < 4; n++)
	{
		k = 3;
		for (i = 4; i >= 0; i--)
		{
			if (map[i][n] != 0)
			{
				for (j = i; j < k; j++)
				{
					if (map[j + 1][n] == 0)
					{
						map[j + 1][n] = map[j][n];
						map[j][n] = 0;
						pass = 1;
						base_loop();
						Sleep(1);
					}
					else if (map[j + 1][n] == map[j][n])
					{
						map[j + 1][n] = 2 * map[j + 1][n];
						score += map[j + 1][n];
						map[j][n] = 0;
						k = j;
						base_loop();
						Sleep(1);
						pass = 1;
						break;
					}
					else break;
				}
			}
		}
	}
}

void interact_left()//向左移动
{
	int n, i, j, k;
	for (i = 0; i < 4; i++)
	{
		k = 0;
		for (n = 0; n < 4; n++)
		{
			if (map[i][n] != 0)
			{
				for (j = n; j > k; j--)
				{
					if (map[i][j - 1] == 0)
					{
						map[i][j - 1] = map[i][j];
						map[i][j] = 0;
						pass = 1;
						base_loop();
						Sleep(1);
					}
					else if (map[i][j - 1] == map[i][j])
					{
						map[i][j - 1] = 2 * map[i][j - 1];
						score += map[i][j - 1];
						map[i][j] = 0;
						k = j;
						base_loop();
						Sleep(1);
						pass = 1;
						break;
					}
					else break;
				}
			}
		}
	}
}

void interact_right()//向右移动
{
	int n, i, j, k;
	for (i = 0; i < 4; i++)
	{
		k = 3;
		for (n = 3; n >= 0; n--)
		{
			if (map[i][n] != 0)
			{
				for (j = n; j < k; j++)
				{
					if (map[i][j + 1] == 0)
					{
						map[i][j + 1] = map[i][j];
						map[i][j] = 0;
						pass = 1;
						base_loop();
						Sleep(1);
					}
					else if (map[i][j + 1] == map[i][j])
					{
						map[i][j + 1] = 2 * map[i][j + 1];
						score += map[i][j + 1];
						map[i][j] = 0;
						k = j;
						base_loop();
						Sleep(1);
						pass = 1;
						break;
					}
					else break;
				}
			}
		}
	}
}

int game_check()
{
	int success = 0;

	int i, n;

	int a = 0;//对指不为零且相邻位置数字不相同的元素进行计数
	if ((map[0][0] != 0) && (map[0][1] != 0) && (map[0][0] != 0) && (map[0][0] != map[0][1]) && (map[0][0] != map[1][0]))a++;
	if ((map[3][3] != 0) && (map[3][2] != 0) && (map[2][3] != 0) && (map[3][3] != map[3][2]) && (map[3][3] != map[2][3]))a++;
	if ((map[0][3] != 0) && (map[0][2] != 0) && (map[1][3] != 0) && (map[0][3] != map[0][2]) && (map[0][3] != map[1][3]))a++;
	if ((map[3][0] != 0) && (map[3][1] != 0) && (map[2][0] != 0) && (map[3][0] != map[3][1]) && (map[3][0] != map[2][0]))a++;
	if ((map[0][1] != 0) && (map[0][0] != 0) && (map[0][2] != 0) && (map[0][1] != map[0][0]) && (map[0][1] != map[0][2]))a++;
	if ((map[0][2] != 0) && (map[0][1] != 0) && (map[0][3] != 0) && (map[0][2] != map[0][1]) && (map[0][2] != map[0][3]))a++;
	if ((map[3][1] != 0) && (map[3][0] != 0) && (map[3][2] != 0) && (map[3][1] != map[3][0]) && (map[3][1] != map[3][2]))a++;
	if ((map[3][2] != 0) && (map[3][1] != 0) && (map[3][3] != 0) && (map[3][2] != map[3][1]) && (map[3][2] != map[3][3]))a++;
	if ((map[1][0] != 0) && (map[0][0] != 0) && (map[2][0] != 0) && (map[1][0] != map[0][0]) && (map[1][0] != map[2][0]))a++;
	if ((map[2][0] != 0) && (map[3][0] != 0) && (map[1][0] != 0) && (map[2][0] != map[1][0]) && (map[2][0] != map[3][0]))a++;
	if ((map[1][3] != 0) && (map[0][3] != 0) && (map[2][3] != 0) && (map[1][3] != map[0][3]) && (map[1][3] != map[2][3]))a++;
	if ((map[2][3] != 0) && (map[3][3] != 0) && (map[1][3] != 0) && (map[2][3] != map[1][3]) && (map[2][3] != map[3][3]))a++;
	for (i = 1; i < 3; i++)
		for (n = 1; n < 3; n++)
			if ((map[n][i] != 0) && (map[n - 1][i] != 0) && (map[n + 1][i] != 0) && (map[n][i - 1] != 0) && (map[n][i + 1] != 0) && 
					(map[n][i] != map[n + 1][i]) && (map[n][i] != map[n - 1][i]) && (map[n][i] != map[n][i + 1]) && (map[n][i] != map[n][i - 1]))a++;
	if (a == 16)success = -1;
	for (i = 0; i < 4; i++)
		for (n = 0; n < 4; n++)if (map[n][i] == 2048)
			success = 1;
	return success;
}

void base_loop()//循环放置
{
	int i, n;
	for (i = 0; i < 4; i++)
	{
		for (n = 0; n < 4; n++)
		{
			placeElem(i, n, map[n][i], score);//最后一个参数 传入分数
		}
	}
}

void game_clear()//清屏
{
	int i, n;
	for (i = 0; i < 4; i++)
	{
		for (n = 0; n < 4; n++)
		{
			map[n][i] = 0;
		}
	}
}

int main()
{

	_init();
	return 0;
}
