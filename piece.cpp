#include"piece.h"
using namespace std;


void Piece::modify_coordinates(int i,int j)
{
	row=i;
	column=j;
}


bool Pawn::can_access(int i, int j)
{
	auto _row=row;
	auto _col=column;


	
		int dir=(color==white ? 1 : -1);
		
	if (first_move==1)
	{
		if(i-_row==dir && j==_col && cb->get_board(i,j)==nullptr)
		{
			return true;
		}

		if(i-_row==2*dir && j==_col)
		{
			if(cb->get_board(i-dir,j)==nullptr && cb->get_board(i,j)==nullptr)
				return true;
		}


	}

	
			if((i-_row!=dir) && (j- _col!=dir))
			{
				return false;
			}

		 if(cb->get_board(i,j)==nullptr && i- _row==dir && j==_col)
		 {
			 return true;
	 	 }
	if(abs(i-_row)==abs(j-_col)&& i-_row==dir && abs(j-_col)==abs(dir))
	{
		if(cb->get_board(i,j)==nullptr)
		{
			return false;
		}
		if(!is_enemy(i,j))
		{
			return false;
		}
		      
		 
			 return true;
	}
	
	return false;

}
bool Knight::can_access(int i, int j)
{
        auto _row=row;
        auto _col=column;

        
	if((abs(i-_row)==2&&abs(j-_col)==1)||(abs(i-_row)==1&&abs(j-_col)==2))
	{
		if(cb->get_board(i,j)==nullptr)
		{
			return true;

		} else 	if(!is_enemy(i,j))
			{
				return false;
			} else {
				return true;
			}
	}
	return false;
}


bool King::can_access(int i, int j)
{
	auto _row=row;
	auto _col=column;
        

		if(abs(i-_row)>1 || abs(j-_col)>1)
		{
			return false;
		}

		if(cb->get_board(i,j)!=nullptr)
		{
			if(!is_enemy(i,j))
			{
					return false;
			}
		}

		return true;
}

bool Bishop::can_access(int i, int j)
{
	auto _row=row;
	auto _col=column;


	if(abs(_row-i)!=abs(_col-j))
	{
		return false;
	}
	int dir_col=((j-_col)>0 ? 1 : -1);
	int dir_row=((i-_row)>0 ? 1 : -1);
        int d_col=dir_col;
        int d_row=dir_row;
	for(int m=abs(i-_row)+1;m<2*abs(i-_row);m++)
	{
		if(cb->get_board(_row+dir_row,_col+dir_col)!=nullptr)
		{
			return false;
		}
		dir_row=dir_row+d_row;
		dir_col=dir_col+d_col;
		
	}

        if(cb->get_board(i,j)!=nullptr)
	{
		if(!is_enemy(i,j))
		{
			return false;
		}
	}

	return true;
}

	

bool Queen::can_access(int i, int j)
{
	auto _row=row;
	auto _col=column;


         if(abs(_row-i)==abs(_col-j))
	 {
	     int dir_col=((j-_col)>0 ? 1 : -1);
	     int dir_row=((i-_row)>0 ? 1 : -1);
	     int d_col=dir_col;
	     int d_row=dir_row;
	     
	     for(int m=abs(i-_row)+1;m<2*abs(i-_row);m++)
	     {
                if(cb->get_board(_row+dir_row,_col+dir_col)!=nullptr)
                {
                        return false;
                }
		dir_col=dir_col+d_col;
		dir_row=dir_row+d_row;
	     }
	     if(cb->get_board(i,j)!=nullptr)
                {
			if(!is_enemy(i,j))
			{

                        return false;
			}
		}

	return true;
	 }

	 if(abs(i-_row)!=abs(j-_col))
	 {
		 if(rook_move(i, j))
		 {
			 return true;
		 }
	 }
	 return false;
}


	
bool Piece::rook_move(int i, int j)
{
	auto _row=row;
	auto _col=column;  
        if (_row!=i && _col!=j)///one of the two must be the same
        {
                return false;
        }
	if ((_row==i &&_col!=j))
        {
		int dir=((j-_col)>0 ? 1 : -1);
		int dir_1=dir;
                for(int m=abs(j-_col)+1;m<2*abs(j-_col);m++)
                {
                        if (cb->get_board(_row,_col+dir)!=nullptr)
                        {
                                return false;
                        }
			dir=dir+dir_1;
                }
        }
	

       if ((_row!=i&&_col==j))
        {
		int dir((i-_row)>0 ? 1 : -1);
		int dir_1=dir;
                for(int m=abs(i-_row)+1;m<2*abs(i-_row);m++)
                {
                        if (cb->get_board(_row+dir,_col)!=nullptr)
                        {
                                return false;
                        }
			dir=dir+dir_1;

                }
        }


       if(cb->get_board(i,j)!=nullptr)
       {
               if(is_enemy(i,j)!=1)
               {
               return false;
               }
       }


       return true;
};





bool Rook::can_access(int i, int j) 
{

	if(rook_move(i,j))
	{


       return true;
	}

	return false;
}








bool Piece::is_enemy(int i, int j)
{
	if(cb->get_board(i,j)->get_color()!=color)
		return true;

	return false;
}


