#ifndef CHESSBOARD_H
#define CHESSBOARD_H
#include"piece.h"
class Piece;


class ChessBoard
{
	public:
	Piece * get_board(int i, int j) {return board[i][j];};
	ChessBoard();
        ~ChessBoard();

	void resetBoard();
	void submitMove(std::string from,std::string to);
        private:
	Piece* board[8][8] ;//2d array of pointer to class Piece. so we have the two classes pointing to each other. 

        void initialise_board();

	int player_color;//0 for white and 1 for black

	int game_already_ended;//0 if game not already ended else 1. useful if a player try to submit a move so that output is nice

	int stalemate;//1 if stalemate and 0 else. useful to differentiate between checkmate and stalemate.

	int castling_flag;//1 if castling 0 else. useful as king cannot move 2 square so put put a castling flag before checking for standard piece move in allow_move();

	bool check_coordinates(int i_from,int j_from, int i_to, int j_to);//check if inout coordinates are valid and if so return true else false

	bool same_destination(int i, int j);//if source is same as destination then return false

	bool castling_basic_condition(int i_from, int j_from, int i_to, int j_to);//return true if some castling basic conditions are satisfied else false
	bool allow_castling(int i_from, int j_from, int i_to, int j_to);//return true if the castling move is valid

        bool allow_move(int i_from, int j_from, int i_to, int j_to,std::string from, std::string to,int flag);//return true if the submitted move is valid else false

	void move(int i_from,int j_from,int i_to, int j_to);//responsible for moving pieces

        void undo_move(int i_from,int j_from,int i_to,int j_to,Piece* save);//undo a move. very useful for when testing for game_over and is_check, so that if move is valid we leave submitMove function responsible for submitting the move

        void move_castling(int i_from,int j_from,int i_to,int j_to);//similar as above for castling 
	void undo_move_castling(int i_from,int j_from,int i_to,int j_to,Piece* rook, Piece* king, int dir);//similar as above for castling

        void print_move(int i_from,int j_from,int i_to, int j_to,std::string from,std::string to);//print output

        void print_castling(int i_from,int j_from,int i_to,int j_to,std::string from,std::string to);//print castling output

	void not_allow_move(int i_from, int j_from, std::string form, std::string to);//print output when move is not allowed

        std::string get_player_color() { return (player_color==0 ? "White":"Black");};	

	bool is_check(int player_col);//return true if player_col is in check else false

	bool game_over(int player_col);//return true if player_col lost.

};
#endif
