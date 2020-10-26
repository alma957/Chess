#ifndef PIECE_H
#define PIECE_H
#include<string>
#include"ChessBoard.h"
enum Color {white,black};
class ChessBoard;

class Piece
{

	protected:
	ChessBoard* cb;//pointer to chessboard.
	Color color;
	int row;
	int column;
        Piece(ChessBoard* cb, Color color,int row, int column): cb(cb), color(color),row(row),column(column){};
	public:

	void modify_coordinates(int i,int j);//when a move is submitted this is responsible for modifying row and column

	Color get_color() {return color;};

        virtual ~Piece() {} ;//destructor

	int first_move=1;///=1 if piece never moves else 0

	virtual bool can_access(int i, int j)=0;//test whether a given piece can access rank i and file j.

	virtual std::string type()=0;//return string with name of piece. useful for output and checking for check and game_over

	std::string color_type() { return (color==white ? "White" : "Black") ; };//return string color . useful for output

	bool is_enemy(int i, int j);///test whether a piece is an enemy, a piece cannot access a square occupied by a friend.

	bool rook_move(int i, int j);//rook_type move so that it can be shared by both queen and rook to save some lines of coding

};

class Pawn : public Piece
{
	public:
	Pawn(ChessBoard* cb, Color color,int row, int column): Piece(cb,color,row,column) {}
	std::string type() { return "Pawn ";} ;
	bool can_access(int i, int j) override;
        ~Pawn() {} ;
};
class Knight : public Piece
{
        public:
        Knight(ChessBoard* cb, Color color,int row, int column): Piece(cb,color,row,column) {}
        std::string type() { return "Knight ";} ;
        bool can_access(int i, int j) override;
	~Knight() {};
};


class Rook : public Piece
{
	public:
	Rook(ChessBoard* cb, Color color,int row, int column): Piece(cb,color,row,column) {}
        std::string type() { return "Rook ";} ;
	bool can_access(int i, int j) override;

	~Rook() {};

};

class King : public Piece
{
	public:
	King(ChessBoard* cb, Color color,int row, int column): Piece(cb,color,row,column) {}
        std::string type() { return "King ";} ;
	bool can_access(int i, int j) override;
	~King() {};
};


class Bishop : public Piece
{
	public:
        Bishop(ChessBoard* cb, Color color,int row, int column): Piece(cb,color,row,column) {}
        std::string type() { return "Bishop ";} ;
        bool can_access(int i, int j) override;
        ~Bishop() {};
};

class Queen : public Piece
{
        public:
        Queen(ChessBoard* cb, Color color,int row, int column): Piece(cb,color,row,column) {}
        std::string type() { return "Queen ";} ;
        bool can_access(int i, int j) override;
	~Queen() {};
};


#endif 
