#include"ChessBoard.h"
#include<iostream>
using namespace std;

ChessBoard::ChessBoard()
{
	initialise_board();
}
ChessBoard::~ChessBoard()
{
	
	for (int i=0;i<8;i++)
		for (int j=0;j<8;j++)
			delete board[i][j];


}
void ChessBoard::initialise_board()
{
	cout<<"A new chess game is started! "<<endl;
	player_color=white;
	game_already_ended=0;
	stalemate=0;
	castling_flag=0;

	for (int i=0;i<8;i++)
	{
		board[1][i]=new Pawn(this,white,1,i);
		board[6][i]=new Pawn(this,black,6,i);
	}
	        board[0][1]=new Knight(this,white,0,1);
		board[0][6]=new Knight(this,white,0,6);
		board[7][1]=new Knight(this,black,7,1);
		board[7][6]=new Knight(this,black,7,6);
	        board[0][4]=new King(this,white,0,4);
		board[7][4]=new King(this,black,7,4);
	        board[0][0]=new Rook(this,white,0,0);
		board[0][7]=new Rook(this,white,0,7);
		board[7][0]=new Rook(this,black,7,0);
		board[7][7]=new Rook (this,black,7,7);
                board[0][3]=new Queen(this,white,0,3);
		board[7][3]=new Queen(this,black,7,3);
		board[0][2]=new Bishop(this,white,0,2);
		board[0][5]=new Bishop(this,white,0,5);
		board[7][2]=new Bishop(this,black,7,2);
		board[7][5]=new Bishop(this,black,7,5);

	for(int i=2;i<6;i++)
		for (int j=0;j<8;j++)
			board[i][j]=nullptr;

	
}

void ChessBoard::resetBoard()
{
	for (int i=0;i<8;i++)
		for (int  j=0;j<8;j++)
			delete board[i][j];

	initialise_board();
}

void ChessBoard::submitMove(string from,string to)
{
	int i_from=from[1]-'1';
	int j_from=from[0]-'A';
	int i_to=to[1]-'1';
	int j_to=to[0]-'A';

	if(game_already_ended==1)
	{
		if (stalemate==1)
		{
		cout<<"No possible further moves as game already ended! "<<get_player_color()<<" is in stalemate"<<endl;
		return;
		} else {
		cout<<"No possible further moves as game already ended! "<<get_player_color()<<" is in checkmate"<<endl;

		return ;
	}
	}

	
        
	if(allow_move(i_from,j_from,i_to,j_to,from, to,1))
	{
		     if(castling_flag==1)
		     {
			             print_castling(i_from,j_from,i_to,j_to,from, to);
 
                                     move_castling(i_from,j_from,i_to,j_to);
				     castling_flag=0;
				     goto SKIP;
		     }

		     print_move(i_from,j_from,i_to,j_to,from,to);
		     move(i_from,j_from,i_to,j_to);
		     if(board[i_to][j_to]->first_move==1)
		     {
		     board[i_to][j_to]->first_move=0;
		     }
                     SKIP:;
		     player_color=(!player_color);

	             if(game_over(player_color) && is_check(player_color))
		     {
			     cout<<get_player_color()<<" is in checkmate"<<endl<<endl;
			     game_already_ended=1;
		     	     return;
		     }
	             if(game_over(player_color))
			     {
				     cout<<get_player_color()<<" is in stalemate"<<endl; 
				     game_already_ended=1;
		       		     stalemate=1;
		     		     return;
		     	     }
		     if(is_check(player_color))
		     {
			     
			     cout<<get_player_color()<<" is in check"<<endl;


		     }

	}
        


}

bool ChessBoard::allow_move(int i_from, int j_from, int i_to, int j_to,string from, string to,int flag) 
{
	if (from.size()!=2||to.size()!=2)
	{
		if (flag==1)
		{
		cout<<"Invalid input "<<endl;
		}
		return false;
	}
	if(!check_coordinates(i_from,j_from,i_to,j_to))
	{
		if (flag==1)
		{
		cout<<"Coordinates are not valid "<<endl;
		}
		return false;
	}
	if (board[i_from][j_from]==nullptr)
	{
		if (flag==1)
		{
		cout<<"There is no piece at position "<<from<<"!"<<endl;
		}
		return false;
	}

	if(board[i_from][j_from]->get_color()!=player_color)
	{
		if(board[i_from][j_from]->get_color()==black)
		{
			if (flag==1)
			{
		cout<<"it is not Black's turn to move!"<<endl;
			}
		return false;
		} else {
			if (flag==1)
			{
			cout<<"It is not White's turn to move!"<<endl;
			}
                return false;
		}
	}
	if(i_from==i_to && j_from==j_to)
	{
		if (flag==1)
		{
		cout<<"Invalid move: destination is same as Source!"<<endl;
		}
		return false;
	}
	auto save=board[i_to][j_to];
        
	if(allow_castling(i_from,j_from,i_to,j_to))
	{
		castling_flag=1;
	         return true;	
	}
	if(board[i_from][j_from]->can_access(i_to, j_to))
	{
		move(i_from,j_from,i_to,j_to);
	if(is_check(player_color))
	{
		undo_move(i_from,j_from,i_to,j_to,save);
		if (flag==1)
		{
		not_allow_move(i_from,j_from,from,to);
		}
	return false;  
	}
	undo_move(i_from,j_from,i_to,j_to,save);
	return true;
	}
	if (flag==1)
	{
	not_allow_move(i_from,j_from,from,to);
	}
	return false;
}

bool ChessBoard::check_coordinates(int i_from, int j_from, int i_to, int j_to)
{
	if(i_from>7||i_from<0||j_from>7||j_from<0||i_to>7||i_to<0||j_to>7||j_to<0)
	{
		return false;
	}

		return true;
}

bool ChessBoard::castling_basic_condition(int i_from, int j_from, int i_to, int j_to)
{
        int dir=(j_to-j_from>0 ? 1 : -1);
        if(board[i_from][j_from]->type()!="King ")
        return false;

        if(board[i_from][j_from]->get_color()==white)
	{
        if(i_from!=0 || i_to!=0)
                return false;
	}
	if(board[i_from][j_from]->get_color()==black)
	{
		if(i_from!=7||i_to!=7)
			return false;
	}

        if (abs(j_from-j_to)!=2)
                return false;

        if(dir>0)

        {

                if(board[i_from][j_from]->first_move==1 && board[i_to][j_to+dir]->first_move==1)
                {
                        if(board[i_to][j_to+dir]->type()=="Rook " && board[i_to][j_to+dir]->get_color()==board[i_from][j_from]->get_color())
                        return true;
                }

        } else {
                if(board[i_from][j_from]->first_move==1 && board[i_to][j_to+dir+dir]->first_move==1)

                        {
                                if(board[i_to][j_to+dir+dir]->type()=="Rook " && board[i_to][j_to+dir+dir]->get_color()==board[i_from][j_from]->get_color())
                return true;
                        }
        }


        return false;
}

bool ChessBoard::allow_castling(int i_from, int j_from, int i_to, int j_to)
{
	
	if(!castling_basic_condition(i_from,j_from,i_to,j_to))
		return false;

	if(is_check(player_color))
		return false;

         Piece* save_king=board[i_from][j_from];
	 Piece* save_rook;
        int dir=(j_to-j_from>0 ? 1 : -1);

	if (dir>0)
	{
	       save_rook=board[i_from][j_to+dir];
	       

		for(int m=0;m<2;m++)
		{
			if(board[i_to][j_to-m]!=nullptr)
			{
				return false;
			}
				auto save=board[i_to][j_to-m];
				move(i_from,j_from,i_to,j_to-m);
				if(is_check(player_color))
				{
					undo_move(i_from,j_from,i_to,j_to-m,save);
					return false;
				}
				undo_move(i_from,j_from,i_to,j_to-m,save);

		}
		
	} else {
		save_rook=board[i_to][j_to+2*dir];
		for(int m=1;m<4;m++)
		{
			if(board[i_to][j_from-m]!=nullptr)
                        {
				return false;
			}
			        if(m<3) {
				auto save=board[i_to][j_from-m];
                                move(i_from,j_from,i_to,j_from-m);
                                if(is_check(player_color))
                                {
                                        undo_move(i_from,j_from,i_to,j_from-m,save);
                                        return false;
                                }
				undo_move(i_from,j_from,i_to,j_from-m,save);
				}

                        }
                }
	
         move_castling(i_from,j_from,i_to,j_to);
         if(is_check(player_color))
	 {
	       undo_move_castling(i_from,j_from,i_to,j_to,save_rook,save_king,dir);   
	       return false;
	 }
               undo_move_castling(i_from,j_from,i_to,j_to,save_rook,save_king,dir);

	return true;
}






bool ChessBoard::is_check(int player_col)
{
	int king_row;
	int king_column;
	for(int i=0;i<8;i++)
	{
		for(int j=0;j<8;j++)
		{
			if(board[i][j]!=nullptr && board[i][j]->get_color()==player_col && this->board[i][j]->type()=="King ")
			{
				king_row=i;
				king_column=j;
				break;
			}
		}
	}


	for (int i=0;i<8;i++)
	{
		for(int j=0;j<8;j++)
		{
			if(board[i][j]!=nullptr && board[i][j]->get_color()!=player_col && board[i][j]->can_access(king_row,king_column))
			{
				return true;
			}
		}
	}
	return false;
}










bool ChessBoard::game_over(int player_col)
{

	for(int i=0;i<8;i++)
	{
		for(int j=0;j<8;j++)
		{
			if(board[i][j]!=nullptr && board[i][j]->get_color()==player_col)
			{
				for(int m=0;m<8;m++)
				{
					for(int k=0;k<8;k++)
					{
						string from={(char)(j+65),(char)(i+49)};
						string to={(char)(k+65),(char)(m+49)};
					        auto save=board[m][k];
						if(allow_move(i,j,m,k,from,to,0))
						{

							move(i,j,m,k);

							if(!is_check(player_col))
						{
							undo_move(i,j,m,k,save);
						
							return false;
						}

						undo_move(i,j,m,k,save);
						}

					}
				}
			}
		}
	}
	return true;
}
	
	
	
void ChessBoard::undo_move(int i_from,int j_from,int i_to,int j_to,Piece* save)
{
	board[i_from][j_from]=board[i_to][j_to];
	board[i_to][j_to]=save;
	board[i_from][j_from]->modify_coordinates(i_from,j_from);
}
void ChessBoard::move(int i_from,int j_from,int i_to, int j_to)
{

	board[i_to][j_to]=board[i_from][j_from];
	board[i_from][j_from]=nullptr;
	board[i_to][j_to]->modify_coordinates(i_to,j_to);

}


void ChessBoard::move_castling(int i_from,int j_from,int i_to,int j_to)
{
        int dir=(j_to-j_from>0 ? 1 : -1);
        if(dir>0)
        {
                move(i_from,j_from,i_to,j_to);
                move(i_from,j_from+3*dir,i_to,j_to-dir);
		if(castling_flag==1)
		{
			board[i_to][j_to]->first_move=0;
			board[i_to][j_to-dir]->first_move=0;
		}
        } else {
                move(i_from,j_from,i_to,j_to);
                move(i_from,j_from+4*dir,i_to,j_to-dir);
		if(castling_flag==1)
		{
			board[i_to][j_to]->first_move=0;
			board[i_to][j_to-dir]->first_move=0;
        }
}
}

void ChessBoard::undo_move_castling(int i_from,int j_from,int i_to,int j_to,Piece* rook, Piece* king, int dir)
{
        undo_move(i_from,j_from,i_to,j_to,king);
        if(dir>0)
        {
        undo_move(i_from,j_from+3,i_to,j_to-dir,rook);
        return;
        }

        undo_move(i_from,j_from-4,i_to,j_to-dir,rook);
}



void ChessBoard::print_castling(int i_from,int j_from,int i_to,int j_to,string from,string to)
{
        int dir=(j_to-j_from>0 ? 1 : -1);
        if(dir>0)
        {
        string _from={(char)(j_from+65+3),(char)(i_from+49)};
        string _to={(char)(j_to+65-1),(char)(i_to+49)};
        cout<<"Castling!: "<<board[i_from][j_from]->color_type()<<" "<<board[i_from][j_from]->type()<<"moves from "<<from<<" to "<<to<<" and "<<board[i_from][j_from+3]->color_type()<<" "<<board[i_to][j_from+3]->type()<<"moves from "<<_from<<" to "<<_to<<endl;

        } else {
                 string _from={(char)(j_from+65-4),(char)(i_from+49)};
                 string _to={(char)(j_to+65+1),(char)(i_to+49)};
        cout<<"Castling!: "<<board[i_from][j_from]->color_type()<<" "<<board[i_from][j_from]->type()<<"moves from "<<from<<" to "<<to<<" and "<<board[i_from][j_from-4]->color_type()<<" "<<board[i_from][j_from-4]->type()<<"moves from "<<_from<<" to "<<_to<<endl;
        }
}

void ChessBoard::print_move(int i_from,int j_from,int i_to, int j_to,string from, string to)
{
        if(board[i_to][j_to]==nullptr)
        {
                cout<<board[i_from][j_from]->color_type()<<"'s "<<board[i_from][j_from]->type()<<"moves from "<<from<<" to "<<to<<endl;
                return;
        } else {
                cout<<board[i_from][j_from]->color_type()<<"'s "<<board[i_from][j_from]->type()<<"moves from "<<from<<" to "<<to<< " taking "<<board[i_to][j_to]->color_type()<<"'s "<<board[i_to][j_to]->type()<<endl;

        }
        return ;
}



void ChessBoard::not_allow_move(int i_from,int j_from,string from, string to)
{
	cout<<board[i_from][j_from]->color_type()<<" "<<this->board[i_from][j_from]->type()<< " in "<<from<<" cannot move to "<<to<<endl;
	return;
}










