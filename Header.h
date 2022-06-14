#pragma once
#include<iostream> // for cout "outputting text on screen" 
#include<cstdlib> // for rand() "random no generator"
#include<ctime> // for time(NULL) "seed for random numer genrator" 
#include<conio.h> // for _kbhit() "determining if a key is pressed"
#include <Windows.h>
#include <cmath>
#include<fstream>
#include <stdio.h>
using namespace std; // for cout
int language = 1; // 1: EngLish | 0: tieng viet

// global variable for specifying direction of the ball (gia tri toan cuc de xac dinh huong cua bong)
enum Ball_Direction { STOP, LEFT, UPLEFT, DOWNLEFT, RIGHT, UPRIGHT, DOWNRIGHT };
class Coordinates
{
public:
	int x, y;
};
// Ball Class
class Ball:public Coordinates
{
public:

	int center_x, center_y; // to hold postions (current and center) (vi tri hien tai va giua man hinh)

	Ball_Direction direction; // to hold direction of motion of ball (giu huong chuyen dong cua bong)

	// constructor (Ham khoi tao co tham so)
	Ball(int x, int y);

	// function to bring the ball back to its starting position (center) (ham de dua qua bong ve vi tri ban dau)
	void reset_ball();
	// function to change direction of ball when it hits either a wall or a blade (ham de chuyen quy dao cua qua bong khi cham vao blade hoac tuong)
	void change_ball_direction(Ball_Direction d);

	// function to initialize the direction of ball randomely (ham khai bao quy dao cua bong la ngau nhien)
	void randomize_ball_direction();

	// function to move ball around the screen (ham de dieu khien bong di chuyen)
	void move_ball();
}; // end of Ball class

// Blade Class
class Blade:public Coordinates
{
public:
	int initial_x, initial_y; // to hold position of blades (current and default) (vi tri hien tai va giua man hinh)

	// constructor (ham khoi tao co tham so)
	Blade(int x, int y);

	// to reset blade positions while Ping_Pong restarting (dua blade ve vi tri ban dau khi Ping_Pong khoi dong lai)
	void blade_reset();

	// to move balde up (di chuyen blade di len)
	void blade_move_up();

	// to move balde down(di chuyen blade di xuong)
	void blade_move_down();
	void pauseGame();
}; // end of Blade class


// Ping_Pong Class
class Ping_Pong
{
public:
	int width, height, score_1, score_2;// height and width of the Ping_Pong area (chieu dai va chieu rong cua giao dien choi game)
										// scores  of player 1 and player 2 (diem so cua nguoi choi 1 va 2)
	char up_1, down_1, up_2, down_2, choice, choice1, pgame; // keys used by players to move up or down (phim de nguoi choi su dung de di chuyen blade)
	bool terminate; // to terminate the Ping_Pong (dung de thoat Ping_Pong)


	Ball* ball; // 1 ball
	Blade* player_1, * player_2; // 2 players

	// constructor 	(ham tao)
	Ping_Pong(int width, int height);



	// Incrementing score (Tang diem)
	void increment_score(Blade* player);
	// Incrementing score (Tang diem)
	void increment_scoreVN(Blade* player);

	void clearScreen();//loai bo nhay khi mo chuong trinh
	void ShowCur(bool CursorVisibility);
	// Drawing the board (at each moment -- this will explain the blips) (ve bang choi game moi khi code chay -- dieu nay dan den viec game bi nhap nhay)
	void draw_layout();

	void draw_layoutVN();

	// function to respond to player inputs (ham de nguoi choi co the su dung phim tren may tinh de tuong tac voi tro choi)
	void play();

	// function to moniter ball position (ham de theo doi vi tri cua bong)
	void monitor_ball();

	void monitor_ballVN();

	// function to call the functions --> yeah that's pretty much it (goi lai ham tuy thuoc vao language minh chon se la Viet Nam hoac Tieng Anh)
	void lets_ping_pong(int language);
};
int Menu(Ping_Pong& game);//hien menu de nguoi choi tuong tac de lua chon cau lenh phu hop
int MenuVN(Ping_Pong& game);
// Ball Class
Ball::Ball(int x, int y) {
	this->center_x = x; // center_X and center_y store the initial value (center_X va center_y chua gia tri khoi dau)
	this->center_y = y;
	this->x = x; // x and y store current value of the ball position (x va y chua gia tri cua vi tri qua bong hien tai)
	this->y = y;
	this->direction = STOP; // ball is initialized static (qua bong duoc khoi tao tinh)
}
void Ball::reset_ball() {
	x = center_x;
	y = center_y;
	direction = STOP; // to stop the motion of ball (dung qua bong)
}
void Ball::change_ball_direction(Ball_Direction d) {
	direction = d;
}

void Ball::randomize_ball_direction() {
	direction = (Ball_Direction)((rand() % 6) + 1);
}
void Ball::move_ball() { // x increases along right (tang theo chieu ngang ve ben phai)
	switch (direction) { // y increases along bottom (tang theo chieu doc xuong duoi)
	case STOP:
		break;
	case LEFT:
		x--;
		break;
	case RIGHT:
		x++;
		break;
	case UPLEFT:
		x--;
		y--;
		break;
	case DOWNLEFT:
		x--;
		y++;
		break;
	case UPRIGHT:
		x++;
		y--;
		break;
	case DOWNRIGHT:
		x++;
		y++;
		break;
	default: // in case direction take execptional value, ignore it. (tru truong hop qua bong co quy dao ki la, bo qua)
		break;
	}
}
Blade::Blade(int x, int y) {
	this->initial_x = x;
	this->initial_y = y;
	this->x = x;
	this->y = y;
}
void Blade::blade_reset() {
	x = initial_x;
	y = initial_y;
}
void Blade::blade_move_up() {
	y--;
}
void Blade::blade_move_down() {
	y++;
}
Ping_Pong::Ping_Pong(int width, int height) {
	srand(time(NULL)); // seeding random number generator to generate random directions (su dung ham random de lam ngau nhien quy dao cua qua bong)

	// initializing variables (khai bao bien)
	this->terminate = false;
	this->up_1 = 'w'; // player_1 move up using 'w' (nguoi choi 1 di chuyen len tren dung 'w')
	this->up_2 = 'i'; // player_2 move up using 'i'(nguoi choi 1 di chuyen len tren dung 'i')
	this->down_1 = 's'; // player_1 move down using 's'(nguoi choi 1 di chuyen xuong duoi dung 's')
	this->down_2 = 'k'; // player_2 move down using 'k'(nguoi choi di chuyen xuong duoi dung 'k')
	this->score_1 = 0; // both players get initial score = 0 (khoi tao diem so ban dau la 0)
	this->score_2 = 0;

	this->width = width; // user can specify the dimesions of the grid (nguoi dung co the cho ch�nh xac cac chieu cua giao dien game)
	this->height = height;

	this->ball = new Ball(width / 2, height / 2);
	this->player_1 = new Blade(1, height / 2 - 3);
	this->player_2 = new Blade(width - 2, height / 2 - 3);
}
void Ping_Pong::increment_score(Blade* player)
{
	do
	{
		if (player == player_1) score_1 += 1; // increment player 1 score (tang diem nguoi choi 1 len 1)
		else score_2 += 1;// increment player 2 score(tang diem nguoi choi 2 len 1)

		ball->reset_ball(); // put ball back at center (gui bong lai chinh giua)
		player_1->blade_reset(); // put both blades at starting position (gui blade lai vi tri ban dau )
		player_2->blade_reset();

		if (score_1 >= 5 || score_2 >= 5)//1 trong 2 nguoi choi co diem > 5 thi neu ai hon 2 diem so voi doi phuong thi thang
		{
			if (abs(score_1 - score_2) >= 2)
			{
				if (score_1 > score_2) //ai co diem cao hon la thang, hoi xem co muon tiep tuc choi khong
				{
					cout << endl << "-----PLAYER 1 WINS-----";
					cout << endl << "Do you want to stop playing?(Yes[y]/No[others])";
					cin >> choice;
					choice1 = choice;
					if (choice == 'Y' || choice == 'y')//neu khong thoat chuong trinh
					{
						cout << endl << "Thanks for playing!" << endl;
						system("pause");
						exit(0);
					}
					else//khoi tao diem 2 nguoi bang 0
					{
						score_1 = 0;
						score_2 = 0;
					}
				}
				else if (score_2 > score_1)
				{
					cout << endl << "-----PLAYER 2 WINS-----";
					cout << endl << "Do you want to stop playing?(Yes[y]/No[others])";
					cin >> choice;
					choice1 = choice;
					if (choice == 'Y' || choice == 'y')
					{
						cout << endl << "Thanks for playing!" << endl;
						system("pause");
						exit(0);
					}
					else
					{
						score_1 = 0;
						score_2 = 0;
					}
				}
			}
		}
		system("cls");
	} while (choice1 == 'y' || choice1 == 'Y');

}

void Ping_Pong::increment_scoreVN(Blade* player)//giong voi increment_score nhung in chu Viet Nam
{
	do
	{
		if (player == player_1) score_1 += 1; // increment player 1 score 
		else score_2 += 1;// increment player 2 score

		ball->reset_ball(); // put ball back at center 
		player_1->blade_reset(); // put both blades at starting position
		player_2->blade_reset();

		if (score_1 >= 5 || score_2 >= 5)
		{
			if (abs(score_1 - score_2) >= 2)
			{
				if (score_1 > score_2)
				{
					cout << endl << "-----Nguoi choi 1 chien thang-----";
					cout << endl << "Ban co muon nghi choi luon khong?(Co[y]/Khong[Phim bat ky])";
					cin >> choice;
					choice1 = choice;
					if (choice == 'Y' || choice == 'y')
					{
						cout << endl << "Xin cam on!" << endl;
						system("pause");
						exit(0);
					}
					else
					{
						score_1 = 0;
						score_2 = 0;
					}
				}
				else if (score_2 > score_1)
				{
					cout << endl << "-----Nguoi choi 2 chien thang-----";
					cout << endl << "Ban co muon nghi choi luon khong?(Co[y]/Khong[Phim bat ky])";
					cin >> choice;
					choice1 = choice;
					if (choice == 'Y' || choice == 'y')
					{
						cout << endl << "Xin cam on!" << endl;
						system("pause");
						exit(0);
					}
					else
					{
						score_1 = 0;
						score_2 = 0;
					}
				}
			}
		}
		system("cls");
	} while (choice1 == 'y' || choice1 == 'Y');

}
void Ping_Pong::clearScreen() {
	HANDLE hOut;
	COORD Position;

	hOut = GetStdHandle(STD_OUTPUT_HANDLE);

	Position.X = 0;
	Position.Y = 0;
	SetConsoleCursorPosition(hOut, Position);
}

void Ping_Pong :: ShowCur(bool CursorVisibility)
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursor = { 1, CursorVisibility };
	SetConsoleCursorInfo(handle, &cursor);
}

void Ping_Pong::draw_layout() {
	clearScreen(); // first clearing the screen to remove prev timestep (xoa khoang thoi gian nhay de tranh bi nhap nhay)
	ShowCur(0);
	// printing above wall(in tuong tren)
	for (int i = 0; i < width + 2; i++) cout << "\xB2";
	cout << endl;

	// printing side walls, ball and blades (in tuong 2 ben, bong va vot)
	for (int i = 0; i < height; i++) { // to traverse along height (de di chuyen theo chieu cao)
		for (int j = 0; j < width; j++) { // to traverse along width (de di chuyen theo chieu rong)

			if (j == 0) cout << "\xB2"; // left wall element (tuong phia ben trai)

			if (ball->x == j && ball->y == i) cout << "O"; // printing ball at its(in bong tai vi tri cua no)
														// position
			// printing player_1 blade (length=4)(in vot cua nguoi choi 1)
			else if (player_1->x == j && player_1->y == i) cout << "\xDB";
			else if (player_1->x == j && player_1->y + 1 == i) cout << "\xDB";
			else if (player_1->x == j && player_1->y + 2 == i) cout << "\xDB";
			else if (player_1->x == j && player_1->y + 3 == i) cout << "\xDB";

			// printing player_2 blade (length=4)(in vot cua nguoi choi 2)
			else if (player_2->x == j && player_2->y == i) cout << "\xDB";
			else if (player_2->x == j && player_2->y + 1 == i) cout << "\xDB";
			else if (player_2->x == j && player_2->y + 2 == i) cout << "\xDB";
			else if (player_2->x == j && player_2->y + 3 == i) cout << "\xDB";


			else cout << " "; // rest of the area is blank (vung con lai bo trong)

			if (j == width - 1) cout << "\xB2"; // right wall element (tuong phai)
		} // end of inner for loop

		cout << "\xB2" << endl;
	} // end of outer for loop

	// printing bottom wall (in tuong duoi)
	for (int i = 0; i < width + 2; i++) cout << "\xB2";
	cout << endl;

	// printing scores (in diem)
	cout << "Score 1: " << score_1 << "\t\t\tScore 2: " << score_2 << endl;

} // end of Draw function

void Ping_Pong::draw_layoutVN()//giong voi draw_layout nhung la Tieng Viet 
{
	clearScreen(); // first clearing the screen to remove prev timestep

	// printing above wall
	for (int i = 0; i < width + 2; i++) cout << "\xB2";
	cout << endl;

	// printing side walls, ball and blades
	for (int i = 0; i < height; i++) { // to traverse along height
		for (int j = 0; j < width; j++) { // to traverse along width

			if (j == 0) cout << "\xB2"; // left wall element

			if (ball->x == j && ball->y == i) cout << "O"; // printing ball at its
														// position
			// printing player_1 blade (length=4)
			else if (player_1->x == j && player_1->y == i) cout << "\xDB";
			else if (player_1->x == j && player_1->y + 1 == i) cout << "\xDB";
			else if (player_1->x == j && player_1->y + 2 == i) cout << "\xDB";
			else if (player_1->x == j && player_1->y + 3 == i) cout << "\xDB";

			// printing player_2 blade (length=4)
			else if (player_2->x == j && player_2->y == i) cout << "\xDB";
			else if (player_2->x == j && player_2->y + 1 == i) cout << "\xDB";
			else if (player_2->x == j && player_2->y + 2 == i) cout << "\xDB";
			else if (player_2->x == j && player_2->y + 3 == i) cout << "\xDB";


			else cout << " "; // rest of the area is blank

			if (j == width - 1) cout << "\xB2"; // right wall element
		} // end of inner for loop

		cout << "\xB2" << endl;
	} // end of outer for loop

	// printing bottom wall
	for (int i = 0; i < width + 2; i++) cout << "\xB2";
	cout << endl;

	// printing scores
	cout << "Nguoi choi 1: " << score_1 << "\t\t\tNguoi choi 2: " << score_2 << endl;

} // end of Draw function
void Ping_Pong::play() {
	ball->move_ball(); // to move the ball in direction specified by 'direction' (di chuyen qua bong duoc chi dan boi 'direction')

	if (_kbhit()) { // if any key is pressed : take action (nhan nut thi thuc hien lenh)
		char key = _getch(); // get the pressed key character(nhan dang nut bam tren ban phim)
		// player_1 move up(nguoi choi 1 di chuyen len tren)
		if (key == up_1 && player_1->y > 0) player_1->blade_move_up();
		// player_2 move up	(nguoi choi 2 di chuyen len tren)
		else if (key == up_2 && player_2->y > 0) player_2->blade_move_up();
		// player_1 move down(nguoi choi 1 di chuyen xuong)
		else if (key == down_1 && player_1->y + 4 < height) player_1->blade_move_down();
		// player_2 move down(nguoi choi 2 di chuyen xuong)
		else if (key == down_2 && player_2->y + 4 < height) player_2->blade_move_down();
		// terminate if 't' is pressed (thoat neu bam t)
		else if(key == 27) {system("pause"); system("cls");}
		else if(key == 8) {	
			system("cls");
			Ping_Pong game(40, 20); // instanciating game
			Menu(game);
			game.lets_ping_pong(::language); // playing
		}
		else if (key == 't') terminate = true;

		// if it's new game move the ball in random directions	(bat dau game voi huong bong ngau nhien)			
		if (ball->direction == STOP) ball->randomize_ball_direction();
	}
} // end of input
void Ping_Pong::monitor_ball()
{

	// if ball hits player_1 blade
	for (int i = 0; i < 4; i++)
		if (ball->x == player_1->x + 1)
			if (ball->y == player_1->y + i)
				ball->change_ball_direction((Ball_Direction)(rand() % 3 + 4));

	// if ball hits player_2 blade
	for (int i = 0; i < 4; i++)
		if (ball->x == player_2->x - 1)
			if (ball->y == player_2->y + i)
				ball->change_ball_direction((Ball_Direction)(rand() % 3 + 1));

	// if ball hits bottom wall
	if (ball->y == height - 1)
		ball->change_ball_direction(ball->direction == DOWNRIGHT ? UPRIGHT : UPLEFT);

	// if ball hits top wall
	if (ball->y == 0)
		ball->change_ball_direction(ball->direction == UPRIGHT ? DOWNRIGHT : DOWNLEFT);

	// if ball hits right wall --> player_1 wins
	if (ball->x == width - 1)
		increment_score(player_1);

	// if ball hits left wall --> player_2 wins
	if (ball->x == 0)
		increment_score(player_2);

}
void Ping_Pong::monitor_ballVN()//giong voi monitor_ball nhung tieng viet
{

	// if ball hits player_1 blade
	for (int i = 0; i < 4; i++)
		if (ball->x == player_1->x + 1)
			if (ball->y == player_1->y + i)
				ball->change_ball_direction((Ball_Direction)(rand() % 3 + 4));

	// if ball hits player_2 blade
	for (int i = 0; i < 4; i++)
		if (ball->x == player_2->x - 1)
			if (ball->y == player_2->y + i)
				ball->change_ball_direction((Ball_Direction)(rand() % 3 + 1));

	// if ball hits bottom wall
	if (ball->y == height - 1)
		ball->change_ball_direction(ball->direction == DOWNRIGHT ? UPRIGHT : UPLEFT);

	// if ball hits top wall
	if (ball->y == 0)
		ball->change_ball_direction(ball->direction == UPRIGHT ? DOWNRIGHT : DOWNLEFT);

	// if ball hits right wall --> player_1 wins
	if (ball->x == width - 1)
		increment_scoreVN(player_1);

	// if ball hits left wall --> player_2 wins
	if (ball->x == 0)
		increment_scoreVN(player_2);

}
void Ping_Pong::lets_ping_pong(int language)
{
	while (!terminate)
	{
		if (language == 1)
		{
			draw_layout();
			play();
			monitor_ball();
		}
		else if (language == 2)
		{
			draw_layoutVN();
			play();
			monitor_ballVN();
		}
	}
}
int MenuVN(Ping_Pong& game)//in menu tieng viet
{
	cout << "           Pong game!" << endl;
	cout << "--------------Menu--------------" << endl;
	cout << "             1.Choi" << endl;
	cout << "             2.Huong Dan" << endl;
	cout << "             3.Cai dat" << endl;
	cout << "             4.Thoat" << endl;
	int choice;
	cin >> choice;
	if (choice == 4)
	{
		cout << endl << "Tam biet!" << endl;
		system("pause");
		exit(0);
	}
	else if (choice == 1)
	{
		system("cls");
		return 1;
	}
	else if (choice == 2)
	{
		system("cls");
		ifstream fileInput("pingpongVN.txt");

		if (fileInput.fail())
		{
			cout << "Loi thu muc!" << std::endl;
			return -1;
		}
		while (!fileInput.eof())
		{
			char temp[255];
			fileInput.getline(temp, 255);
			std::string line = temp;
			std::cout << line << std::endl;
		}
		std::cout << std::endl;

		fileInput.close();
		system("pause");
		system("cls");
		return MenuVN(game);
	}
	else if (choice == 3)
	{
		int CHOICE;
		system("cls");
		cout << "--------------Cai dat--------------" << endl;
		cout << "1.Ngon ngu" << endl << "2.Doi phim bam" << endl;
		cin >> CHOICE;

		char up1, up2, down1, down2;
		switch (CHOICE)
		{
		case 1:
			int language;
			system("cls");
			cout << "--------------Ngon ngu--------------" << endl;
			cout << "1.Tieng Anh" << endl << "2.Tieng Viet" << endl;
			cin >> language;
			::language = language;
			system("pause");
			system("cls");

			if (::language == 1)
			{
				return Menu(game);
			}
			else if (::language == 2)
			{
				return MenuVN(game);
			}

			break;
		case 2:
			cout << "--------------Doi phim bam--------------" << endl;
			cout << "Nguoi choi 1: " << endl;
			cout << "Len : ";
			cin >> up1;
			cout << "Xuong :";
			cin >> down1;
			cout << "Nguoi choi 2: " << endl;
			cout << "Len : ";
			cin >> up2;
			cout << "Xuong :";
			cin >> down2;
			game.up_1 = up1;
			game.up_2 = up2;
			game.down_1 = down1;
			game.down_2 = down2;
			system("pause");
			system("cls");
			return MenuVN(game);
		}
	}
}
int Menu(Ping_Pong& game)//in menu tieng anh
{
	cout << "       Welcome to Pong game!" << endl;
	cout << "--------------Menu--------------" << endl;
	cout << "             1.Play" << endl;
	cout << "             2.Instruction" << endl;
	cout << "             3.Setting" << endl;
	cout << "             4.Quit" << endl;
	int choice;
	cin >> choice;
	if (choice == 4)
	{
		cout << endl << "Thanks for your attention!" << endl;
		system("pause");
		exit(0);
	}
	else if (choice == 1)
	{
		system("cls");
		return 1;
	}
	else if (choice == 2)
	{
		system("cls");
		ifstream fileInput("pingpong.txt");

		if (fileInput.fail())
		{
			cout << "Failed to open this file!" << std::endl;
			return -1;
		}
		while (!fileInput.eof())
		{
			char temp[255];
			fileInput.getline(temp, 255);
			std::string line = temp;
			std::cout << line << std::endl;
		}
		std::cout << std::endl;

		fileInput.close();
		system("pause");
		system("cls");
		return Menu(game);
	}
	else if (choice == 3)
	{
		int CHOICE;
		system("cls");
		cout << "--------------Setting--------------" << endl;
		cout << "1.Language" << endl << "2.Switch keyboard" << endl;
		cin >> CHOICE;

		char up1, up2, down1, down2;
		switch (CHOICE)
		{
		case 1:
			int language;
			system("cls");
			cout << "--------------Language--------------" << endl;
			cout << "1.English" << endl << "2.Vietnamese" << endl;
			cin >> language;
			::language = language;
			system("pause");
			system("cls");

			if (::language == 1)
			{
				return Menu(game);
			}
			else if (::language == 2)
			{
				return MenuVN(game);
			}

			break;
		case 2:
			cout << "--------------Switch keyboard--------------" << endl;
			cout << "Player 1: " << endl;
			cout << "up : ";
			cin >> up1;
			cout << "down :";
			cin >> down1;
			cout << "Player 2: " << endl;
			cout << "up : ";
			cin >> up2;
			cout << "down :";
			cin >> down2;
			game.up_1 = up1;
			game.up_2 = up2;
			game.down_1 = down1;
			game.down_2 = down2;
			system("pause");
			system("cls");
			return Menu(game);
		}
	}
}




