#include<iostream>
#include <cstdlib>
#include<ctime>
#include<fstream>
using namespace std;

struct Player {
    char symbol;
    string name;
    int wins;
    int user_mode; 
};

char board[3][3] = {{'1','2','3'}, {'4','5','6'}, {'7','8','9'}};
char turn = 'X', user_ask;
int row, column, total_game, tie_game = 0;
bool draw = false;
Player player_x, player_o;

//for design ============
void printdesign(){
      for(int i=0;i<=45;i++){
        cout<<"=";
    }
}

//for design ------------
void printminus(){
       for(int i=0;i<=45;i++){
        cout<<"-";
    }
}

void game_label(){
    printdesign();
    cout<<endl;
    cout << "\n\t\tTIC TAC TOE GAME" << endl;
    cout<<endl;
    printdesign();
}

void display_board(){
    system("cls");
    if(player_x.user_mode==1){
        game_label();
        cout<<endl;
        cout << "\n\t   PLAYER1 [X] Vs PLAYER2 [O]\n\n";
    }else if(player_x.user_mode==2){
        game_label();
        cout<<endl;
        cout << "\n\t   Computer [O] Vs Player [X]\n\n";
    }
    cout<<endl;
    cout << "\t\t     |     |     \n";
    cout << "\t\t  " << board[0][0] << "  |  " << board[0][1] << "  |  " << board[0][2] << "\n";
    cout<<"\t\t_____|_____|_____\n";
    cout << "\t\t     |     |     \n";
    cout << "\t\t  " << board[1][0] << "  |  " << board[1][1] << "  |  " << board[1][2] << "\n";
    cout<<"\t\t_____|_____|_____\n";
    cout << "\t\t     |     |     \n";
    cout << "\t\t  " << board[2][0] << "  |  " << board[2][1] << "  |  " << board[2][2] << "\n";
    cout << "\t\t     |     |     \n";
}
void player_turn() {
    int choice;
    
    if (turn == 'X') {
        cout << "\n\tPLAYER1 [X] named \"" << player_x.name << "\" turn : ";
    } else if (turn == 'O') {
        cout << "\n\tPLAYER2 [O] named \"" << player_o.name << "\" turn : ";
    }

    cin >> choice;

    // Validate input range
    if (choice < 1 || choice > 9) {
        cout << "\tInvalid choice. Please enter a number between 1 and 9.\n";
        player_turn();
    }
     switch (choice) {
            case 1: row = 0; column = 0; break;
            case 2: row = 0; column = 1; break;
            case 3: row = 0; column = 2; break;
            case 4: row = 1; column = 0; break;
            case 5: row = 1; column = 1; break;
            case 6: row = 1; column = 2; break;
            case 7: row = 2; column = 0; break;
            case 8: row = 2; column = 1; break;
            case 9: row = 2; column = 2; break;
        }
    // Check if the chosen cell is already taken
    if (board[row][column] == 'X' || board[row][column] == 'O') {
        cout << "        Box already filled\n        Please enter another number\n";
        player_turn();
    }

    // Replace the symbol and switch turn
    if (turn == 'X') {
        board[row][column] = 'X';
        turn = 'O';
    } else {
        board[row][column] = 'O';
        turn = 'X';
    }

    display_board();
}

void computer_turn() {
    // Basic computer move logic (random move)
   srand(time(0));
    int choice;
    do {
        choice = rand() % 9 + 1; // Generate a random number between 1 and 9
        switch (choice) {
            case 1: row = 0; column = 0; break;
            case 2: row = 0; column = 1; break;
            case 3: row = 0; column = 2; break;
            case 4: row = 1; column = 0; break;
            case 5: row = 1; column = 1; break;
            case 6: row = 1; column = 2; break;
            case 7: row = 2; column = 0; break;
            case 8: row = 2; column = 1; break;
            case 9: row = 2; column = 2; break;
        }
    } while (board[row][column] == 'X' || board[row][column] == 'O'); // Check if the chosen BLOCK is already taken

    cout << "\n\nComputer [O] turns: " << choice << endl; 
    board[row][column] = 'O'; // The computer's move
    turn = 'X'; // Switch turn to the  player [x]
}

bool game_over(){
    // Check which player wins the game
    for(int i=0; i<3; ++i){
        // Check current row
        if (board[i][0] == board[i][1] && board[i][0] == board[i][2])
            return false;

        // Check current column
        if(board[0][i] == board[1][i] && board[0][i] == board[2][i])
            return false;
    }

    // Check left top to bottom diagonal
    if(board[0][0] == board[1][1] && board[0][0] == board[2][2])
        return false;

    // Check right top to bottom diagonal
    if(board[0][2] == board[1][1] && board[0][2] == board[2][0])
        return false;

    // Check if all boxes are not filled
    for(int i=0; i<3; ++i){
        for(int j=0; j<3; ++j){
            if(board[i][j] != 'X' && board[i][j] != 'O')
                return true;
        }
    }
// game draw 
    draw = true;
    return false;
}

void scoreboard(){ 
//create file
    ofstream file("tictactoe.txt");
    if(!file)
    {
	   cout<<"File not created.\n";
	
    }
   else
    {
    cout<<"File created successfuly.\n";
    system("cls");
    printdesign();
    cout<<"\n\t\tScoreboard\n";
    printdesign();
     cout << endl;
     if(player_x.user_mode==2){
    cout<<"\t   Computer[O] VS Player[X] ";
    file<<"--------------------------------------------";
    file<<" Computer[O] VS Player[X] ";
    file<<"--------------------------------------------";
    cout<<endl;
     printdesign();
     cout<<endl;}
     else{
    cout<<"\t   Player[X] VS Player[O] ";
    file<<"--------------------------------------------";
    file<<" Player[X] VS Player[O] ";
    file<<"--------------------------------------------";
    cout<<endl;
   printdesign();
   cout<<endl;
    }
    cout << endl;
    total_game=player_x.wins+player_o.wins+tie_game;
    cout<<endl<<"Total games played: "<<total_game;
    cout<<endl;
    file<<endl<<"Total games played: "<<total_game;
    
    cout << "\nPLAYER1 [X] named \"" << player_x.name << "\" wins: " << player_x.wins;
    cout << endl;
    file<<"\nPLAYER1 [X] named \"" << player_x.name << "\" wins: " << player_x.wins;
    
    if(player_x.user_mode==2){
        cout<<endl<< player_o.name<<" [O] wins: "<<player_o.wins;
        file<<endl<< player_o.name<<" [O] wins: "<<player_o.wins;
    }
	else{
    cout << "\nPLAYER2 [O] named \"" << player_o.name << "\" wins: " << player_o.wins;
    file<<"\nPLAYER2 [O] named \"" << player_o.name << "\" wins: " << player_o.wins;
	}
	
    cout << endl;
    cout << "\nTie games: " << tie_game << endl;
    file<< "\nTie games: " << tie_game << endl;
    cout << endl;
    printdesign();
    cout << endl;
    cout<<"\t\t Result: "<<endl;
    file<<"--------------------------------------------";
    file<<" Result: ";
    file<<"--------------------------------------------";
    printminus();
      if (player_x.wins > player_o.wins) {
    cout << "\nPLAYER1 [X] named: \"" << player_x.name << "\" WINS THIS GAME!";
    file<<"\nPLAYER1 [X] named: \"" << player_x.name << "\" WINS THIS GAME!";
    }
    else if (player_o.wins > player_x.wins) {
     if(player_x.user_mode==2){
        cout<<endl<< player_o.name<<" [O]  WINS THIS GAME!";
        file<<endl<< player_o.name<<" [O]  WINS THIS GAME!";
    }
	else{
    cout << "\nPLAYER2 [O] named: \"" << player_o.name << "\" WINS THIS GAME!";
	file<< "\nPLAYER2 [O] named: \"" << player_o.name << "\" WINS THIS GAME!";
	}
    }
    else if (player_o.wins==player_x.wins) {
    cout << "\nIt is a tie!! no one wins the game!";
    file<< "\nIt is a tie!! no one wins the game!";
    }
    }

    }

void reset_game(){

    // Reset the board to its initial state with numbers from 1 to 9
    char value='1';
    for(int i=0;i<3;i++)
	{
      for(int k=0;k<3;k++){
        board[i][k]=value;
        value++;
       }
    }
    turn = 'X';   // Set the starting player to X
    draw = false;  // Reset the draw state
}

void playervsplayer(){
    system("cls");
    game_label();
    cout<<endl;
    cout << "\n\t   PLAYER1 [X] Vs PLAYER2 [O]\n\n";
    cin.ignore();
    cout <<endl<<"Enter your name Player[X]: ";
    getline(cin, player_x.name);
    player_x.symbol = 'X';
    player_x.wins = 0;
    cout << "Enter your name Player[O]: ";
    getline(cin, player_o.name);
    player_o.symbol = 'O';
    player_o.wins = 0;

    do {
        reset_game();
        while (game_over()) {
            display_board();
            player_turn();
        }

        if (turn == 'X' && !draw) {
            cout << "Player2 [" << player_o.symbol << "] named: \"" << player_o.name << "\" WINS THIS GAME\nCONGRATULATIONS!\n";
            player_o.wins++;
        } else if (turn == 'O' && !draw) {
            cout << "Player1 [" << player_x.symbol << "] named: \"" << player_x.name << "\" WINS THIS GAME\nCONGRATULATIONS!\n";
            player_x.wins++;
        } else {
            cout << "IT'S A TIE!\n";
            tie_game++;
        }

        cout << "Do you want to play more?\nEnter (Y) for Yes and (N) for No : ";
        cin >> user_ask;
    } while (user_ask == 'Y' || user_ask == 'y');

    scoreboard();
}

void computervsplayer() {
    system("cls");
    //showing label
    game_label();
    cout << endl;
    cout << "\n\t   Computer [O] Vs Player [X]\n\n";
    cin.ignore();
    cout << endl << "Enter your name Player[X]: ";
    getline(cin, player_x.name);
    player_x.symbol = 'X';
    player_x.wins = 0;
    player_o.name = "Computer";
    player_o.symbol = 'O';
    player_o.wins = 0;

    do {
        reset_game();
        while (game_over()) {
            if (turn == 'X') {
                display_board();  // Display the board before the human player's turn
                player_turn();    // Human player's turn
            } else {
                computer_turn();  // Computer's turn
                display_board();  // Display the board after the computer's move
            }
        }

        if (turn == 'X' && !draw) {
            cout << "Computer[" << player_o.symbol << "] WINS THIS GAME\nCONGRATULATIONS!\n";
            player_o.wins++;
        } else if (turn == 'O' && !draw) {
            cout << "Player1 [" << player_x.symbol << "] named: \"" << player_x.name << "\" WINS THIS GAME\nCONGRATULATIONS!\n";
            player_x.wins++;
        } else {
            cout << "IT'S A TIE!\n";
            tie_game++;
        }

        cout << "Do you want to play more?\nEnter (Y) for Yes and (N) for No : ";
        cin >> user_ask;
    } while (user_ask == 'Y' || user_ask == 'y');

    scoreboard();
}

int main()
{
    //asking for modes
    do {
            game_label();
        cout << "\n\t\t  Choose mode:\n";
        printminus();
        cout << "\n\t1.Player1 VS Player 2 (P1vsP2)\n";
        cout << "\t2.Computer VS Player (CvsP)\n";
        printminus();
        cout << "\n\nEnter \"1\" for (P1vsP2) and \"2\" for (CvsP): ";
        cin >> player_x.user_mode;

        if (player_x.user_mode == 1) {
            playervsplayer();
            break;
        } else if (player_x.user_mode == 2) {
           computervsplayer();
        } else {
            cout << "Invalid request for mode\n";
        }
        
    } while (player_x.user_mode != 1 && player_x.user_mode != 2);


	return 0;
}


 
