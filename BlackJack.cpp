#include <iostream>
#include <string>
#include <random>
#include <algorithm>
#include <vector>
using namespace std;

int first_money = 1000;
random_device engine;

class Game {
public:
	int round;
	int money;
	int card_top;
	bool is_end;
	vector <int> card_list;

};


void Separation() {
	printf("__________________________________________________________\n\n");
}


void ShowRound(Game game) {

	Separation();
	cout << game.round;
	if (game.round % 10 == 1)cout << "st round\n";
	else if (game.round % 10 == 2)cout << "nd round\n";
	else if (game.round % 10 == 3)cout << "rd round\n";
	else cout << "th round\n";

	cout << "Your money : " << game.money << "$" << endl;

	return;
}

void Show2Card() {
	cout << " -------      -------\n|///////|    |///////|\n|///////|    |///////|\n|///////|    |///////|\n|///////|    |///////|\n|///////|    |///////|\n -------      -------\n";
}

void InitGame(Game &game) {
	cout << "--------------------------\n< Welcome to Black Jack!!>\n--------------------------\n";
	Show2Card();
	Separation();

	game.round = 0;
	game.money = first_money;
	game.card_top = 0;
	game.is_end = false;
	game.card_list.resize(52, 0);
	for (int i = 0; i < 52; i++) {
		game.card_list[i] = i;
	}
	shuffle(game.card_list.begin(), game.card_list.end(), engine);

	return;
}

int EnterBetMoney(Game &game) {
	int bet_money;
	cout << "Bet money : "; cin >> bet_money; cout << endl;

	while (bet_money > game.money || bet_money <= 0) {
		if (bet_money > game.money)cout << "You don't hane enough money\n";
		if (bet_money <= 0)cout << "Enter positive value\n";
		bet_money = EnterBetMoney(game);
	}

	return bet_money;
}

char ChangeNumber(int num) {
	char c;
	num %= 13;
	if (num == 0)c = 'A';
	else if (num == 1)c = '2';
	else if (num == 2)c = '3';
	else if (num == 3)c = '4';
	else if (num == 4)c = '5';
	else if (num == 5)c = '6';
	else if (num == 6)c = '7';
	else if (num == 7)c = '8';
	else if (num == 8)c = '9';
	else if (num == 9)c = '0';
	else if (num == 10)c = 'J';
	else if (num == 11)c = 'Q';
	else if (num == 12)c = 'K';
	return c;
}

string ChangeSuit(int num) {
	string s;
	num /= 13;
	if (num == 0)s = "Spade  ";
	else if (num == 1)s = "Heart  ";
	else if (num == 2)s = "Diamond";
	else s = "Club   ";

	return s;
}

void Open1Card(int a) {
	char c = ChangeNumber(a);
	string s = ChangeSuit(a);

	a %= 13;
	if (a != 9)cout << " -------      -------\n|" << s << "|    |///////|\n|       |    |///////|\n|   " << c << "   |    |///////|\n|       |    |///////|\n|       |    |///////|\n -------      -------\n";
	else cout << " -------      -------\n|" << s << "|    |///////|\n|       |    |///////|\n|  1 " << c << "  |    |///////|\n|       |    |///////|\n|       |    |///////|\n -------      -------\n";
}

void Open2Card(int a, int b) {
	char c1 = ChangeNumber(a), c2 = ChangeNumber(b);
	string s1 = ChangeSuit(a), s2 = ChangeSuit(b);

	a %= 13; b %= 13;
	if (a != 9 && b != 9)cout << " -------      -------\n|" << s1 << "|    |" << s2 << "|\n|       |    |       |\n|   " << c1 << "   |    |   " << c2 << "   |\n|       |    |       |\n|       |    |       |\n -------      -------\n";
	else if (a == 9 && b == 9)cout << " -------      -------\n|" << s1 << "|    |" << s2 << "|\n|       |    |       |\n|  1 " << c1 << "  |    |  1 " << c2 << "  |\n|       |    |       |\n|       |    |       |\n -------      -------\n";
	else if (a == 9 && b != 9)cout << " -------      -------\n|" << s1 << "|    |" << s2 << "|\n|       |    |       |\n|  1 " << c1 << "  |    |   " << c2 << "   |\n|       |    |       |\n|       |    |       |\n -------      -------\n";
	else if (a != 9 && b == 9)cout << " -------      -------\n|" << s1 << "|    |" << s2 << "|\n|       |    |       |\n|   " << c1 << "   |    |  1 " << c2 << "  |\n|       |    |       |\n|       |    |       |\n -------      -------\n";
}

void Add1Card(int a) {
	char c = ChangeNumber(a);
	string s = ChangeSuit(a);

	a %= 13;
	if (a != 9)cout << " -------\n|" << s << "|\n|       |\n|   " << c << "   | \n|       |\n|       |\n ------- \n";
	else cout << " -------\n|" << s << "|\n|       |\n|  1 " << c << "  | \n|       |\n|       |\n ------- \n";
}

int ChangeScore(int num) {
	int score;
	num %= 13;
	num += 1;
	if (num <= 10)score = num;
	else if (num > 10)score = 10;
	return score;
}

int CalcScore(vector<int> pd_card_list) {
	int score = 0, ace=0;
	for (auto num : pd_card_list) {
		num %= 13;
		num += 1;
		if (num > 10)num = 10;
		if (num == 1)ace++;

		score += num;
	}
	if (ace == 1 && score + 10 <= 21)score += 10;

	return score;
}

bool Wait() {
	string option;
	cout << "END(e) or CONTINUE(c) : "; cin >> option;
	if (option.size() >= 2) {
		cout << "Type e or c\n";
		return Wait();
	}
	else if (option == "e")return true;
	else if (option == "c")return false;
	else {
		cout << "Type e or c\n";
		return Wait();
	}

}

void BlackJack(Game &game) {
	
	int bet_money = EnterBetMoney(game);


	vector<int> player_card_list, dealer_card_list;
	player_card_list.push_back(game.card_list[game.card_top]); game.card_top++;
	player_card_list.push_back(game.card_list[game.card_top]); game.card_top++;
	dealer_card_list.push_back(game.card_list[game.card_top]); game.card_top++;
	dealer_card_list.push_back(game.card_list[game.card_top]); game.card_top++;

	int player_score = CalcScore(player_card_list);
	int dealer_score = ChangeScore(dealer_card_list[0]);

	cout << "Dealer : Score = " << dealer_score << endl;
	Open1Card(dealer_card_list[0]);
	cout << "You : Score = " << player_score << endl;
	Open2Card(player_card_list[0], player_card_list[1]);

	bool player_bust_flag = false;//BUSTしたときはtrue,それ以外はfalseでループを抜ける
	while (!player_bust_flag) {//playerがターンを追えるまで
		string option;
		cout << "STAND(s) or HIT(h) : "; cin >> option;
		while (option.size() != 1 && option != "h" && option != "s") {
			cout << "Please enter s or h";
			cout << "STAND(s) or HIT(h) : ";
			cin >> option;
		}
		if (option == "s")break;

		Separation();
		player_card_list.push_back(game.card_list[game.card_top]); game.card_top++;
		player_score = CalcScore(player_card_list);

		cout << "Dealer : Score = " << dealer_score << endl;
		Open1Card(dealer_card_list[0]);
		cout << "You : Score = " << player_score << endl;
		Open2Card(player_card_list[0], player_card_list[1]);
		for (int i = 2; i < player_card_list.size(); i++)Add1Card(player_card_list[i]);

		if (player_score > 21) {
			cout << "-BUST!!-\n";
			player_bust_flag = true;
		}
	}

	bool dealer_bust_flag = false;
	dealer_score = CalcScore(dealer_card_list);
	while (!dealer_bust_flag) {//Scoreが17以上になるまで引き続ける
		if (dealer_score >= 17)break;

		dealer_card_list.push_back(game.card_list[game.card_top]); game.card_top++;
		dealer_score = CalcScore(dealer_card_list);

		if (dealer_score > 21)dealer_bust_flag = true;
	}
	Separation();
	cout << "Dealer : Score = " << dealer_score << endl;
	Open2Card(dealer_card_list[0], dealer_card_list[1]);
	for (int i = 2; i < dealer_card_list.size(); i++)Add1Card(dealer_card_list[i]);
	if (dealer_bust_flag)cout << "-BUST!!-\n";
	cout << "You : Score = " << player_score << endl;
	Open2Card(player_card_list[0], player_card_list[1]);
	for (int i = 2; i < player_card_list.size(); i++)Add1Card(player_card_list[i]);
	if (player_bust_flag)cout << "-BUST!!-\n";

	if (player_bust_flag) {
		if (dealer_bust_flag) {
			cout << "<< Drow!!>> You were returned" << bet_money << "$\n";
		}
		else {
			cout << "<<You lose!!>> You lost " << bet_money << "$\n";
			game.money -= bet_money;
		}
	}
	else {
		if (dealer_bust_flag) {
			cout << "<<You win!!>> You got " << bet_money << "$\n";
			game.money += bet_money;
		}
		else {
			if (player_score > dealer_score) {
				cout << "<<You win!!>> You got " << bet_money << "$\n";
				game.money += bet_money;
			}
			else if (dealer_score > player_score) {
				cout << "<<You lose!!>> You lost " << bet_money << "$\n";
				game.money -= bet_money;
			}
			else {
				cout << "<< Drow!!>> You were returned" << bet_money << "$\n";
			}
		}
	}

	return;
}

int main() {

	Game game;
	InitGame(game);

	while (!game.is_end) {
		game.round++;

		ShowRound(game);

		BlackJack(game);

		if (game.money == 0) {
			cout << "Game over!\n";
			break;
		}
		game.is_end = Wait();
	}

	cout << "\n\nYou " << (game.money >= first_money ? "won " : "losed ") << abs(game.money - first_money) << "$ ";
	cout << "in " << game.round << " round" << (game.round == 1 ? "" : "s") << "! " << "Bye!\n";

	return 0;
}