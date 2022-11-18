#include <iostream>

using namespace std;
void printBoard(int board[][3]);
int checkEnd(int board[][3]);
void playGame(int board[][3]);
pair<int, int> findBestMove(int board[][3]);
int calMinimax(int board[][3], bool isMaximizing);

int main()
{
    int board[3][3]={0}; // X=1, O=2, _ = 0
    printBoard(board);
    // checkEnd -> 1 -1 0 5(fighting)
    cout << "Init status: " << checkEnd(board) << endl;
    playGame(board);
    return 0;
}

void printBoard(int board[][3]){
    for(int i=0; i<3; i++){
        for(int j=0; j<3; j++){
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
}

int checkEnd(int board[][3]){
    // 1 1 1 => 1
    // 1;1;1
    // 2 2 2 => -1
    // => 0
    // row = 1
    for(int i=0; i<3; i++){
        if(board[i][0] == 1 && board[i][1] == 1 && board[i][2] == 1){
            return 1;
        }
    }
    // column = 1
    for(int i=0; i<3; i++){
        if(board[0][i] == 1 && board[1][i] == 1 && board[2][i] == 1){
            return 1;
        }
    }
    // diagonal
    if((board[0][0] == 1 && board[1][1] == 1 && board[2][2] == 1) || (board[0][2] == 1 && board[1][1] == 1 && board[2][0] == 1)){
        return 1;
    }

    for(int i=0; i<3; i++){
        if(board[i][0] == 2 && board[i][1] == 2 && board[i][2] == 2){
            return -1;
        }
    }
    // column = 1
    for(int i=0; i<3; i++){
        if(board[0][i] == 2 && board[1][i] == 2 && board[2][i] == 2){
            return -1;
        }
    }
    // diagonal
    if((board[0][0] == 2 && board[1][1] == 2 && board[2][2] == 2) || (board[0][2] == 2 && board[1][1] == 2 && board[2][0] == 2)){
        return -1;
    }
    for(int i =0; i<3; i++){
        for(int j=0; j<3; j++){
            if (board[i][j] == 0){
                return 5;
            }
        }
    }
    return 0;

}

void playGame(int board[][3]){
    while(checkEnd(board)==5){
        // nguoi danh
        while (true){
        	cout << "Nhap vi tri danh: ";
        	int x, y;
        	cin >> x >> y;
        	if (board[x][y] != 0){
        		board[x][y] = 2; // 0
        		break;
			}
			else{
				cout << "Vi tri danh";
			}
		}
        printBoard(board);
        
        // AI danh
        // find best move
        pair<int, int> bestMove = findBestMove(board);
        int x_may = bestMove.first;
        int y_may = bestMove.second;
        board[x_may][y_may]=1;
        printBoard(board);
        cout << "Playing " << endl;
        printBoard(board);
    }
    if(checkEnd(board) == 1){
        cout << "You lose -__- ";
    }
    else if(checkEnd(board) == -1){
        cout << "You win ^ ^";
    }
    else{
        cout << "#####";
    }

}

pair<int, int> findBestMove(int board[][3]){
    int bestScore = -10000000;
    int score;
    pair<int, int> bestMove = make_pair(0,0);
    for(int i=0; i<3; i++){
        for(int j=0; j<3; j++){
            if(board[i][j] == 0){
                board[i][j] = 1;
                score = calMinimax(board,false) ; // find Minimax Function =>
                board[i][j] = 0;
                if(score > bestScore){
                    bestMove.first = i;
                    bestMove.second = j;
                }
            }
        }
    }
    return bestMove;
}

int calMinimax(int board[][3], bool isMaximizing){    // cout << "Calling Minimax" << endl ;

    // ban co
    // curIndex vi tri hien tai dang xet
    // isMaximizing quyết định lấy Min hay Max
    // printBoard(board);
    if(checkEnd(board)!=5)
    {
        return checkEnd(board);
    }
    else{
        int bestScore;
        if(isMaximizing){ // Truong hop lay gia tri Max
            bestScore = -10000000;
            for(int i=0; i<3; i++){
                for(int j=0; j<3; j++){
                    if(board[i][j] == 0){
                        // cout << "i: " << i;
                        // cout << " j: " << j << endl;
                        // printBoard(board);
                        board[i][j] = 1; // AI danh
                        // cout << "AI danh" << endl;
                        // printBoard(board);
                        int score = calMinimax(board,false); // toi luot nguoi choi --> goi de quy
                        board[i][j] = 0;
                        if(score > bestScore){
                            bestScore=score;
                        }
                    }
                }
            }
        }
        else{ // Truong hop lay gia tri Min
            // CODE HERE
        }
        return bestScore;
    }
}
