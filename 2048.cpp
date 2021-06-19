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
};//��ʼ��map����

int WIDTH = 700; //�����
int HEIGHT = 900;  //�����
int score;//�������
int bestScore = 0;
int flag = 0;//��䱳����
int pass;//�����ж��Ƿ�Ҫ����������
int level = 0;//��Ϸ�Ѷ�
char LEVEL[10] = { 0 };//������ʾ�Ѷ�

void main_menu();//�׽���
void info();//��Ϸ����
void OI();//����˵��
void pause();//������Ϸ����
void info_2();//����˵��(��Ϸ��)
void refresh(int score);//����ˢ��
void show_bk1();//��Ϸ���汳��
void placeElem(int x, int y, int num, int score);//����Ԫ��
void _init();//��ʼ������
void game_rand_1();//���256||512����
void game_rand_2();//���2||4����
void interact();//�����ƶ��жϺ���
void interact_up();//�����ƶ��ж�
void interact_down();//�����ƶ��ж�
void interact_left();//�����ƶ��ж�
void interact_right();//�����ƶ��ж�
void game();//��Ϸ��ʼ��������
void game_resume();//������Ϸ
void game_resume_noLimited();//�޾�ģʽ:��
int give_up();//��Ϸ����
int  game_win();//��Ϸʤ��
void game_failed();//��Ϸʧ��
int  game_check();//ʤ���������
void game_clear();//��Ϸ����
void base_loop();//���ֿ��ѭ������
void selectLevel();//�Ѷ�ѡ��



void show_bk1()//��Ϸ���汳��
{
	setbkcolor(RGB(250, 248, 239));//����ɫ
	IMAGE img0, img2, img4, img8, img16, img32, img64, img128, img256, img512, img1024, img2048;
	settextstyle(80, 0, "����");
	settextcolor(RGB(120, 116, 101));
	outtextxy(35, 0, "2048");

	RECT r1 = { 30,150,200,190 };
	RECT r2 = { 200,150,280,190 };
	RECT r3 = { 350,110,720,150 };
	RECT r4 = { 350,150,720,190 };


	settextstyle(30, 0, "����");
	if (level == 1) strcpy(LEVEL, "��");
	else if (level == 2)strcpy(LEVEL, "��ͨ");
	drawtext("�Ѷȣ�", &r1, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	drawtext(LEVEL, &r2, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	settextstyle(20, 0, "����");
	drawtext("Press \"ESC\" to pause", &r3, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	drawtext("Press \"G\" to give up", &r4, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	setfillcolor(RGB(184, 175, 160));//���Ͻ� SCORE��� BEST��
	solidroundrect(390, 30, 530, 100, 15, 15);
	settextstyle(28, 0, "Microsoft Yahei UI Bold");
	setbkcolor(RGB(184, 175, 160));
	settextcolor(RGB(248, 247, 241));
	outtextxy(425, 35, "SCORE");
	solidroundrect(550, 30, 690, 100, 15, 15);
	outtextxy(595, 35, "BEST");

	setfillcolor(RGB(187, 173, 160));//�·���Ϸ����
	solidroundrect(10, 210, 690, 890, 20, 20);

}

void selectLevel()//��Ϸ��ͣ��
{
	cleardevice();
	setbkcolor(RGB(251, 248, 241));
	settextcolor(RGB(150, 126, 104));
	settextstyle(70, 0, "�����кڼ���");
	RECT r1 = { 0, 0, WIDTH, HEIGHT / 3 };
	drawtext("��ѡ�������Ѷ�", &r1, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	settextstyle(30, 0, "΢���ź�");

	RECT r2 = { WIDTH / 2 - 45,HEIGHT / 3 - 30,WIDTH / 2 + 45,HEIGHT / 3 };
	drawtext("���Ѷ�", &r2, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	RECT r3 = { WIDTH / 2 - 45,HEIGHT / 3 + 30,WIDTH / 2 + 45,HEIGHT / 3 + 60 };
	drawtext("��ͨ�Ѷ�", &r3, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	RECT r4 = { WIDTH / 2 - 45,HEIGHT / 3 + 90,WIDTH / 2 + 45,HEIGHT / 3 + 120 };
	drawtext("����", &r4, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

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
		case WM_MOUSEMOVE://��ȡ����ƶ�
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


void refresh(int score) {//����ˢ��
	char str[10], best_str[10] = { 0 };
	setbkcolor(RGB(184, 175, 160));
	_itoa(score, str, 10);
	outtextxy(440, 65, str);//����
	if (score >= bestScore) {
		bestScore = score;
		_itoa(bestScore, best_str, 10);
		outtextxy(610, 65, best_str);//��÷���
	}
	if (flag == 0)
		show_bk1();
	flag++;
}

void placeElem(int x, int y, int num, int score)
{
	setbkcolor(RGB(251, 248, 241));//����ɫ
	IMAGE img0, img2, img4, img8, img16, img32, img64, img128, img256, img512, img1024, img2048;
	refresh(score);

	switch (num)//��ȡͼƬ
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

void _init()//��ʼ������
{
	initgraph(WIDTH, HEIGHT);//����
	setbkcolor(RGB(251, 248, 241));//����
	settextcolor(RGB(150, 126, 104));
	main_menu();
}



void main_menu()//�׽���
{
	cleardevice();

	settextstyle(100, 0, "����");
	LOGFONT f;
	gettextstyle(&f);
	_tcscpy(f.lfFaceName, _T("����"));
	f.lfQuality = ANTIALIASED_QUALITY;
	settextstyle(&f);

	RECT r1 = { 0, 0, WIDTH, HEIGHT / 3 };

	drawtext("2048", &r1, DT_CENTER | DT_VCENTER | DT_SINGLELINE);


	RECT r2 = { WIDTH / 2 - 80,HEIGHT / 2,WIDTH / 2 + 80,HEIGHT / 2 + 50 };
	RECT r3 = { WIDTH / 2 - 80,HEIGHT / 2 + 70,WIDTH / 2 + 80,HEIGHT / 2 + 120 };
	RECT r4 = { WIDTH / 2 - 80,HEIGHT / 2 + 140,WIDTH / 2 + 80,HEIGHT / 2 + 190 };
	RECT r5 = { WIDTH / 2 - 80,HEIGHT / 2 + 210,WIDTH / 2 + 80,HEIGHT / 2 + 260 };

	settextstyle(30, 0, "����");
	LOGFONT f1;
	gettextstyle(&f1);					//��ȡ������ʽ
	f1.lfQuality = ANTIALIASED_QUALITY;    // �������Ч��Ϊ�����  
	settextstyle(&f1);                     // ����������ʽ
	settextcolor(BLACK);				//BLACK��graphic.hͷ�ļ����汻����Ϊ��ɫ����ɫ����

	drawtext("��ʼ��Ϸ", &r2, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	drawtext("��Ϸ����", &r3, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	drawtext("����˵��", &r4, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	drawtext("�˳���Ϸ", &r5, DT_CENTER | DT_VCENTER | DT_SINGLELINE);


	setfillcolor(RGB(115, 106, 98));
	solidroundrect(216, 50, 484, 318, 50, 50);
	settextstyle(145, 0, "΢���ź�");
	setbkcolor(RGB(115, 106, 98));
	settextcolor(RGB(254, 253, 249));
	outtextxy(216, 107, "2048");

	setbkcolor(RGB(251, 248, 241));
	settextcolor(RGB(254, 253, 249));
	settextstyle(30, 0, "Microsoft Yahei UI");

	MOUSEMSG m;//�����λ�õ��ж�
	while (1)
	{
		BeginBatchDraw();
		m = GetMouseMsg();
		switch (m.uMsg)
		{
		case WM_MOUSEMOVE://��ȡ����ƶ�
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
			if (m.x > WIDTH / 2 - 82 && m.x<WIDTH / 2 + 82 && m.y>HEIGHT / 2 - 1 && m.y < HEIGHT / 2 + 50)//��ʼ��Ϸ
			{
				game_clear();
				cleardevice();
				flag = 0;
				selectLevel();
				//game_win();
				//game_failed();
				break;
			}
			else if (m.x > WIDTH / 2 - 82 && m.x<WIDTH / 2 + 82 && m.y>HEIGHT / 2 + 69 && m.y < HEIGHT / 2 + 120)//��Ϸ����
			{
				info();
				break;
			}
			else if (m.x > WIDTH / 2 - 82 && m.x < WIDTH / 2 + 82 && m.y > HEIGHT / 2 + 139 && m.y < HEIGHT / 2 + 190)//����˵��
			{
				OI();
				break;
			}
			else if (m.x > WIDTH / 2 - 82 && m.x < WIDTH / 2 + 82 && m.y > HEIGHT / 2 + 209 && m.y < HEIGHT / 2 + 260)//�˳���Ϸ
			{
				exit(0);
			}
			break;
		}
	}
	_getch();
}

void info()//��Ϸ����
{
	cleardevice();
	RECT C2 = { 60,60,640,790 };
	settextcolor(BLACK);
	drawtext("\n\n\n\n\n\n��Ϸ���ܣ�\n\n\n\nÿ�ο���ѡ���������һ�����ÿ����һ�Σ����е����ַ��鶼���������ķ���£��ϵͳҲ���ڰ׵ĵط��������һ�����ַ��飬��ͬ���ֵķ����ڿ�£����ײʱ����ӡ����ϵĵ�������ƴ�ճ�2048������־���ɹ���", &C2, DT_WORDBREAK);


	RECT R1 = { WIDTH - WIDTH + 2,HEIGHT - 200,WIDTH - 2,HEIGHT - 2 };
	drawtext("����", &R1, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	MOUSEMSG m;
	while (1)//���ؼ�������
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

void OI()//����˵��
{
	cleardevice();
	RECT C3 = { 60,60,640,790 };
	settextcolor(BLACK);
	drawtext("\n\n\n����˵����\n\n���ƣ������ ��\n\n���ƣ������ ��\n\n���ƣ������ ��\n\n���ƣ������ ��\n\n", &C3, DT_WORDBREAK);
	RECT R1 = { WIDTH - WIDTH + 2,HEIGHT - 200,WIDTH - 2,HEIGHT - 2 };
	drawtext("����", &R1, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	MOUSEMSG m;
	while (1)//���ؼ�������
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
	settextstyle(70, 0, "�����кڼ���");
	RECT r1 = { 0, 0, WIDTH, HEIGHT / 3 };
	drawtext("��ͣ��", &r1, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	settextstyle(30, 0, "΢���ź�");

	RECT r6 = { WIDTH / 2 - 45,HEIGHT / 3 - 30,WIDTH / 2 + 45,HEIGHT / 3 };
	drawtext("����Ϸ", &r6, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	RECT r2 = { WIDTH / 2 - 100,HEIGHT / 3 + 30,WIDTH / 2 + 100,HEIGHT / 3 + 60 };
	drawtext("������Ϸ", &r2, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	RECT r3 = { WIDTH / 2 - 100,HEIGHT / 3 + 90,WIDTH / 2 + 100,HEIGHT / 3 + 120 };
	drawtext("�������˵�", &r3, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	RECT r4 = { WIDTH / 2 - 100,HEIGHT / 3 + 150,WIDTH / 2 + 100,HEIGHT / 3 + 180 };
	drawtext("����˵��", &r4, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	RECT r5 = { WIDTH / 2 - 100,HEIGHT / 3 + 210,WIDTH / 2 + 100,HEIGHT / 3 + 240 };
	drawtext("�˳���Ϸ", &r5, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

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
		case WM_MOUSEMOVE://��ȡ����ƶ�
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

int give_up()//�������
{
	//setbkmode(TRANSPARENT);
	setbkcolor(RGB(250, 240, 230));//����ɫ
	COLORREF ref;
	int r, g, b;
	int x, y;
	char* yes, * no, * giveup;
	srand((int)time(0));
	BeginBatchDraw();
	FlushBatchDraw();
	EndBatchDraw();
	yes = "ȷ��";
	no = "ȡ��";
	giveup = "�������Ƿ�Ҫ����?";
	settextcolor(BLUE);
	settextstyle(100, 30, "����");
	outtextxy(WIDTH / 2 - 220, 50, giveup);
	settextstyle(50, 25, "����");
	settextcolor(GREEN);
	settextcolor(BLUE);
	outtextxy(220, 250, yes);
	outtextxy(420, 250, no);
	setfillcolor(RED);

	MOUSEMSG m;//�����������Ϸ�����˳�
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
				setbkcolor(RGB(250, 248, 239));//����ɫ
				cleardevice();
				flag = 0;
				game_resume();
				return 2;
				break;
			}
		}
	}
}


void info_2()//����˵��
{
	cleardevice();
	RECT C3 = { 60,60,640,790 };
	settextcolor(BLACK);
	drawtext("\n\n\n����˵����\n\n���ƣ������ ��\n\n���ƣ������ ��\n\n���ƣ������ ��\n\n���ƣ������ ��\n\n", &C3, DT_WORDBREAK);
	RECT R1 = { WIDTH - WIDTH + 2,HEIGHT - 200,WIDTH - 2,HEIGHT - 2 };
	drawtext("����", &R1, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	MOUSEMSG m;
	while (1)//���ؼ�������
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

int game_win()//��Ϸ�ɹ�����
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
	yes = "ȷ��";
	no = "�˳�";
	giveup = "��Ϸʤ����";
	for (x = 0; x < 10; x++)
	{
		settextcolor(RGB(rand() % 255, rand() % 255, rand() % 255));
		settextstyle(100, 50, "����");
		outtextxy(WIDTH / 2 - 250, 50, giveup);
		Sleep(200);
	}

	settextstyle(50, 25, "����");
	settextcolor(GREEN);
	outtextxy(WIDTH / 2 - 70, 150, "������");
	settextcolor(BLUE);
	outtextxy(220, 250, yes);
	outtextxy(420, 250, no);
	setfillcolor(RED);

	MOUSEMSG m;//�����������Ϸ�����˳�
	while (1) {
		FlushMouseMsgBuffer();
		m = GetMouseMsg();
		if (m.uMsg == WM_LBUTTONDOWN)
		{
			x = m.x; y = m.y;
			if (x > 220 && x < 320 && y>250 && y < 300)
			{
				cleardevice();
				setbkcolor(RGB(250, 248, 239));//����ɫ
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

void game_failed()//��Ϸʧ�ܽ���
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
		settextstyle(80, 40, "����");
		outtextxy(WIDTH / 2 - 100, HEIGHT / 2 - 100, "ʧ�ܣ�");
		Sleep(200);
	}

	settextstyle(50, 0, "����");
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

void game()//��Ϸ�ĳ�ʼ��������
{

	while (1)
	{

		score = 0;//������ʼ��
		if (level == 1) {
			game_rand_1();//�������������
			game_rand_1();
		}
		else if (level == 2) {
			game_rand_2();
			game_rand_2();
		}

		base_loop();//������
		while (1)
		{
			if (_kbhit)//����
			{
				pass = 0;
				interact();//������
				fflush(stdin);//������뻺��
				if (pass) {
					if (level == 1) {
						game_rand_1();
					}
					else if (level == 2) {
						game_rand_2();

					}
				}
				if (game_check())//��� ���check����
				{
					if (game_check() == 1)//��� ���check����
					{
						if (game_win() == 1) {
							setbkcolor(RGB(250, 248, 239));//����ɫ
							break;//���� �޾�ģʽ
						}

					}
					else if (game_check() == -1)//��� ���check����
					{
						base_loop();
						game_failed();
						break;
					}
				}
				base_loop();//������
			}
			else Sleep(1);
		}
		game_clear();//����
		continue;
	}
}

void game_resume()
{
	show_bk1();
	base_loop();
	while (1)
	{
		if (_kbhit)//����
		{
			pass = 0;
			interact();//������
			fflush(stdin);//������뻺��
			if (pass) {
				if (level == 1) {//�������������
					game_rand_1();
				}
				else if (level == 2) {
					game_rand_2();
				}
			}
			if (game_check())//���
			{
				if (game_check() == 1)//���
				{
					if (game_win() == 2) {
						main_menu();
						break;
					}//ʤ������

				}
				else if (game_check() == -1)//���
				{
					base_loop();
					game_failed();
					break;
				}
			}
			base_loop();//��������
		}
		else Sleep(1);
	}
	game_clear();//����
}

void game_resume_noLimited()
{

	show_bk1();
	base_loop();
	while (1)
	{
		if (_kbhit)//����
		{
			pass = 0;
			interact();//������
			fflush(stdin);//������뻺��
			if (pass) {
				if (level == 1) {
					game_rand_1();//�������������
				}
				else if (level == 2) {
					game_rand_2();//�������������
				}
			}
			base_loop();//������
		}
		else Sleep(1);
	}
	game_clear();//����
}

void game_rand_1()//���256 512(�Ѷ�1)
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
			map[y][x] = num;//������
			break;
		}
	}
}

void game_rand_2()//���2 4(�Ѷ�2)
{
	int x, y, temp, num;
	srand((int)time(0));
	while (1)
	{
		x = rand() % 4;
		y = rand() % 4;
		temp = rand() % 5;
		if (temp == 1)num = 4;//���4
		else num = 2;//���2
		if (map[y][x] == 0)
		{
			map[y][x] = num;//������
			break;
		}
	}
}

void interact()//����Ϸ�л�ȡ���������
{
	char keyboard;
	keyboard = _getch();
	if (keyboard == 'w' || keyboard == 'W' || keyboard == 72)interact_up();//��
	if (keyboard == 's' || keyboard == 'S' || keyboard == 80)interact_down();//��
	if (keyboard == 'a' || keyboard == 'A' || keyboard == 75)interact_left();//��
	if (keyboard == 'd' || keyboard == 'D' || keyboard == 77)interact_right();//��
	if (keyboard == 27)//esc���˵�
	{
		flag = 0;
		setbkcolor(RGB(251, 248, 241));
		pause();
	}
	if (keyboard == 'G' || keyboard == 'g') {
		give_up();
	}
}

void interact_up()//�����ƶ�
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
					if (map[j - 1][n] == 0)//����û��
					{
						map[j - 1][n] = map[j][n];
						map[j][n] = 0;
						pass = 1;
						base_loop();
					}
					else if (map[j - 1][n] == map[j][n])//�����пɺϲ�����
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

void interact_down()//�����ƶ�
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

void interact_left()//�����ƶ�
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

void interact_right()//�����ƶ�
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

	int a = 0;//��ָ��Ϊ��������λ�����ֲ���ͬ��Ԫ�ؽ��м���
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

void base_loop()//ѭ������
{
	int i, n;
	for (i = 0; i < 4; i++)
	{
		for (n = 0; n < 4; n++)
		{
			placeElem(i, n, map[n][i], score);//���һ������ �������
		}
	}
}

void game_clear()//����
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
