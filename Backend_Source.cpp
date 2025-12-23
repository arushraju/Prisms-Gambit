/*
Welcome to this project of Chess in egypt. 
Its an adaptation of the existing game of "Lazer Chess". Then whats different. Well the first thing is I am making it. And I am different. 
The idea is to make this game as user freindly as chess.com. Some unique ideas includes:

1.  Make a an introductory video demonstating the rules of game, using 3D animations and presentations.
2.  Make this game in C and then somehow translate it to my website. This would include people being able to playt it with each other and
    will have some what similar rating system.
3.  Then One uniquie idea that I came up with, is to have a rough board beside them. This is for those who find it difficult to think
    at first since the game is new. And then with that rough board they could make some tempoaray moves from both sides and could re-think there 
    next move
4.  The next feature could be for audience. If someone wishes to watch the live match, one could do so with a bar, which would show him 
    live status of the board.
*/

#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>

FILE* output_file;

//This will turn true when the game ends
bool game_over;
bool output_print = false;

/*
///////////////////////////////////////////////        RULES OF THE BOARD          //////////////////////////////////////////////////
The game consist of a board which is (10*10).

        GAME PEICES

It also contains many peices that could be played with as follows:
1.  Lazer       (L) :   Each player has one of it. And with it cannot be eliminated, but can be rotated.
2.  Mirror      (M) :   This is just like mirror. It will reflect the laser from two side and will die from the other two adjacent side. 
3.  Sheild      (S) :   This will block the lazer from one side but will die if gets hit by the laser from any other three sides. 
4.  Deflector   (D) :   This will always deflect the lazer, and can not be killed
5.  King        (K) :   This is the soul of the game and if gets hit by lazer from any direction will die.

        PEICE COLOR

The game starts from the blue side. However the first move will be of red. 
Blue        (B)
Red         (R)

        ORIENTATION

There are four orientation of the peices.
Orientation = 1 -> peice facing me. 
Orientation = 2 -> peice is facing right of me
Orientation = 3 -> peicen is facing in opposite to me
Orientation = 4 -> Peice is facing left side

Note: 
1. Orientation of king is going to be zero since it has none
2. Orientation of deflector can only be 2 (if you eject beam and it deflects right) or 4 (if you eject beam and it deflects left)


Form the above convention, I am facing in direction 3. And to my back is direction 1 and to my right is 2, left is 4

        POINTS
Points are only assigned to those peices which could be killed.
King    =   inf
Mirror  =   10
Sheild  =   5
Switch and lazer could not be killed and so holds no points.
And there for their points is zero.
*/
struct peice
{
    int position;
    char peice_color;
    char peice_type;
    int orientation;
    int points;
};

//This function will assign empty space at given position. Note that for empty square, peice type and peice color is 'n'.
void assign_empty(struct peice* board_dash,int position)
{
    board_dash[position].position = position;
    board_dash[position].orientation = 0;
    board_dash[position].peice_color = 'n';
    board_dash[position].peice_type = 'n';
    board_dash[position].points = 0;
}

//This take in two characters (peice board,peice type) and two integer (orientation and points) and assign those to board
void assign(struct peice* board_dash,int _position_,char _peice_color_,char _peice_type_, int _orientation_)
{
    board_dash[_position_].position = _position_;
    board_dash[_position_].orientation = _orientation_;
    board_dash[_position_].peice_color = _peice_color_;
    board_dash[_position_].peice_type = _peice_type_;
    //So deflectors and laser cannot be eliminated from the game thus, no points associated to them.
    if (_peice_type_ == 'm' && _peice_color_ == 'b'){board_dash[_position_].points = 10;}
    else if(_peice_type_ == 's' && _peice_color_ == 'b'){board_dash[_position_].points = 5;}
    else if (_peice_type_ == 'k' && _peice_color_ == 'b'){ board_dash[_position_].points = 100;}
    else if (_peice_type_ == 'm' && _peice_color_ == 'r'){board_dash[_position_].points = -10;}
    else if (_peice_type_ == 's' && _peice_color_ == 'r'){board_dash[_position_].points = -5;}
    else if (_peice_type_ == 'k' && _peice_color_ == 'r'){board_dash[_position_].points = -100;}
    else {board_dash[_position_].points = 0;}
    return;
}


/*
This function will display the  board. Just like how when plotting the aerodynamics, we will plot different aspects of the board in
different plots. It will contain the (color,type,oreintation). For orientation we can ujse the following symbol. 

For Mirrors     | For Deflectors    |   For Sheilds     |   For Lazers
1 -> " #/  "    | 1 -> "  /  "      |   1 -> "  v  "    |   1 -> " +^+ "
2 -> " #\  "    | 2 -> "  \  "      |   2 -> "  >  "    |   2 -> " +>+ "
3 -> "  /# "    |                   |   3 -> "  ^  "    |   3 -> " +v+ "
4 -> "  \# "    |                   |   4 -> "  <  "    |   4 -> " +<+ "
*/
void Display(struct peice* board)
{   
    int t = 8;
    int i;

    //For test the iteration logic
    printf("                                    TESTING LOGIC: \n");
    for(int j = 80;j>=73;j=j-1)
    {
        i = j;
        while(i>=t)
        {
            
            printf("%d ",i);
            i = i - 8;
        }
        t = t - 1;
        printf("\n");
    }



    /*
    t = 8;
    printf("                                    PEICE COLOR: \n");
    for(int i=0;i<10;i++){printf("\033[0;33m________\033[0m");}
    printf("\n");
    for(int j=80;j>=73;j = j-1)
    {
        i = j;
        while(i>=t)
        {
            printf("\033[0;33m|    \033[0m");
            if(board[i].peice_color == 'r'){printf("\033[0;31m(R)\033[0m");}
            else if(board[i].peice_color == 'b'){printf("\033[0;34m(B)\033[0m");}
            else {printf("   ");}
            i = i-8;
        }
        t = t-1;
        printf("\033[0;33m|\033[0m");
        printf("\n");
        for(int i=0;i<10;i++){printf("\033[0;33m|_______\033[0m");}
        printf("\033[0;33m|\033[0m");
        printf("\n");
    }
*/
    printf("                                 PEICE ORIENTATION: \n");
    for(int i=0;i<10;i++){printf("\033[0;32m________\033[0m");}
    printf("\n");
    t = 8;
    for(int j=80;j>=73;j = j-1)
    {
        for(int i=0;i<10;i++){printf("\033[0;32m|       \033[0m");}
        printf("\033[0;32m|\033[0m");
        printf("\n");
        i = j;
        while(i>=t)
        {
            printf("\033[0;32m|  \033[0m");
            if(board[i].peice_type == 'm' && board[i].peice_color == 'r')
            {
                if(board[i].orientation == 1){printf("\033[1;31m#/   \033[0m");}
                else if(board[i].orientation == 2){printf("\033[1;31m#\\   \033[0m");}
                else if(board[i].orientation == 3){printf("\033[1;31m/#   \033[0m");}
                else if(board[i].orientation == 4){printf("\033[1;31m\\#   \033[0m");}
            }
            else if(board[i].peice_type == 'm' && board[i].peice_color == 'b')
            {
                if(board[i].orientation == 1){printf("\033[1;34m#/   \033[0m");}
                else if(board[i].orientation == 2){printf("\033[1;34m#\\   \033[0m");}
                else if(board[i].orientation == 3){printf("\033[1;34m/#   \033[0m");}
                else if(board[i].orientation == 4){printf("\033[1;34m\\#   \033[0m");}
            }
            
            /**********/
            
            else if(board[i].peice_type == 'd' && board[i].peice_color == 'r')
            {
                if(board[i].orientation == 1){printf("\033[1;31m /   \033[0m");}
                else if(board[i].orientation == 2){printf("\033[1;31m \\   \033[0m");}
            }
            else if(board[i].peice_type == 'd' && board[i].peice_color == 'b')
            {
                if(board[i].orientation == 1){printf("\033[1;34m /   \033[0m");}
                else if(board[i].orientation == 2){printf("\033[1;34m \\   \033[0m");}
            }

            /*********/

            else if(board[i].peice_type == 's' && board[i].peice_color == 'r')
            {
                if(board[i].orientation == 1){printf("\033[1;31m v   \033[0m");}
                else if(board[i].orientation == 2){printf("\033[1;31m >   \033[0m");}
                else if(board[i].orientation == 3){printf("\033[1;31m ^   \033[0m");}
                else if(board[i].orientation == 4){printf("\033[1;31m <   \033[0m");}
            }
            else if(board[i].peice_type == 's' && board[i].peice_color == 'b')
            {
                if(board[i].orientation == 1){printf("\033[1;34m v   \033[0m");}
                else if(board[i].orientation == 2){printf("\033[1;34m >   \033[0m");}
                else if(board[i].orientation == 3){printf("\033[1;34m ^   \033[0m");}
                else if(board[i].orientation == 4){printf("\033[1;34m <   \033[0m");}
            }


            else if(board[i].peice_type == 'l' && board[i].peice_color == 'r')
            {
                if(board[i].orientation == 1){printf("\033[1;31m +v+ \033[0m");}
                else if(board[i].orientation == 2){printf("\033[1;31m+>+  \033[0m");}
                else if(board[i].orientation == 3){printf("\033[1;31m+^+  \033[0m");}
                else if(board[i].orientation == 4){printf("\033[1;31m+<+  \033[0m");}
            }
            else if(board[i].peice_type == 'l' && board[i].peice_color == 'b')
            {
                if(board[i].orientation == 1){printf("\033[1;34m +v+ \033[0m");}
                else if(board[i].orientation == 2){printf("\033[1;34m+>+  \033[0m");}
                else if(board[i].orientation == 3){printf("\033[1;34m+^+  \033[0m");}
                else if(board[i].orientation == 4){printf("\033[1;34m+<+  \033[0m");}
            }

            else if(board[i].peice_type == 'k' && board[i].peice_color == 'b')
            {
                printf("\033[1;34m k   \033[0m");
            }
            else if(board[i].peice_type == 'k' && board[i].peice_color == 'r')
            {
                printf("\033[1;31m k   \033[0m");
            }
            
            else {printf("     ");}
            i = i-8;
        }
        t = t-1;
        
        printf("\033[0;32m|\033[0m\n");
        for(int i=0;i<10;i++){printf("\033[0;32m|_______\033[0m");}
        printf("\033[0;32m|\033[0m");
        printf("\n");
    }

}


/*
Now that we have finally created the display function, lets get into the part of rules of the game.
                                        1. Movement of peices:
Note : Be it any peice if its at the edge of the board, there are several restiction.
1. Lazer cannot move and will always be at board[80] and boardp[1]
2. Any blue peice cannot lie at squares [73,79]+[16]+[9]. And Red peices cannot lie at [2,8]+[65]+[72] -> lets call this "STRIP OF RESTRAIN"
3.  3.1) Deflector can swap places with adjacent Deflectors(only) of its own color(only). And not in strip of restrain or in some cell which is occupied or outside the board
    3.2) King can move in any direction but not in strip of restrain or in some cell which is occupied or outside the board
    3.3) Sheid can not move in strip of restrain or in some cell which is occupied or outside the board.
    3.5) Mirror can not move in strip of restrain or in some cell which is occupied or outside the board.
    3.4) Lazer cannot move.

                                        2. Rotation of peices: 
1) Red lazer can only rotate in directions 3 or 4 and Blue lazer can only be oriented in direction 1 or 2.
2) Mirror, Sheild can be oriented in any direction. 
3) Deflector can only rotate in two direction 2,3.
4) King has not direction.

                                        3. Laser and its physics:
1) 
*/

// This function will move the peice as required. If the function moves the peice then it return True, or else it returns False
// This direction will be a function which will be as follows: 
/*
    (-1)    :   down
    (+1)    :   up
    (+8)    :   left
    (-8)    :   right
    (+9)    ;   left-top
    (-9)    ;   right-bottom
    (-7)    :   right-top
    (+7)    ;   left-bottom
*/

//This function will check if the peice could be moved to place where it wants to go. Its a boolean type function.
bool Is_move_possible(struct peice* board_dash,char which_peice,int present_position, int direction)
{
    /*1. This will allow only the movable peices to move*/
    if(which_peice == 'l')
    {
        if(output_print)fprintf(output_file,"Attempt to move the lazer\n");
        return  false;
    }
    
    int moved_position = present_position + direction;
    bool check;

    /*2. This section will not allow any peice to move out of the board*/

    //This means there is a typo
    if(!(moved_position < 80 && moved_position > 1)) 
    {
        if(output_print)fprintf(output_file,"Attempt to move the peice at lazer's position or invalid location.\n");
        return false;
    }
    //Problem will arise at the top and bottom edge of the board.
    else if(moved_position%8 == 1)
    {
        //We know that if the peice is at the bottom edge, then it cannot be moved down, niether can it jump to the top edge.
        if(direction == (-1) || direction == (-9) || direction == (+7))
        {
            if(output_print)fprintf(output_file,"Attempt to jump the bottom peice\n");
            return false;
        }

    }
    //If the peice is at the top edge
    else if(moved_position%8 == 0)
    {
        if(direction == (+1) ||direction == (-7)||direction ==(+9))
        {
            if(output_print)fprintf(output_file,"Attempt to move the top peice to bottom\n");
            return false;
        }
    }

    /*3. This section will check if the peice is moving to place which is already occupied*/
    //But first we will check if the peice is deflector. Since deflector can exchange positions with other delfectors of smae color
    if(which_peice == 'd')
    {
        //Let's check if that adajacent square contains deflector or not.
        if(board_dash[moved_position].peice_type == 'd' && board_dash[moved_position].peice_color == board_dash[present_position].peice_color)
        {
            //int d1 = board[moved_position].orientation;
            //char d2 = board[moved_position].peice_type;
            //char d3 = board[moved_position].peice_color;
            //assign(present_position,d3,d2,d1);
            //assign(moved_position,board[present_position].peice_color,board[present_position].peice_type,board[present_position].orientation);
            if(output_print)fprintf(output_file,"Exchange Successful\n");
            return true;
        }
        else if(board_dash[moved_position].peice_type == 'n')
        {
            if(output_print)fprintf(output_file,"Attempt to move the deflector to unoccupied location\n");
            return true;
        }
        if(output_print)fprintf(output_file,"Attempt of moving deflector to unexchangable peice\n");
        return false;
    }
    //Now if the peice is not deflector and wants to move to some valid cell, then it can move there only if the square is unoccupied.
    if(board_dash[moved_position].peice_color != 'n')
    {
        if(output_print)fprintf(output_file,"Attempt to move to occupied position\n");
        return false;
    }

    if(output_print)fprintf(output_file,"The peice is MOVABLE, the final position is VALID, and is UNOCCUPIED\n");
    return true;
}



//This function will move the peice where ever it is intended to be moved. It takes in the type of peice, its current position, and 
//in which direction does it hae to move. (+1: up ; -1: down; -8: right ; +8: left)
void move_the_peice(struct peice* board_dash,char which_peice,int present_position, int direction)
{
    if(output_print)
    {
        fprintf(output_file,"\n");
        fprintf(output_file,"Inside the 'move_the _peice' function\n");
        fprintf(output_file,"Attempt ot move %c, from %d, in direction %d\n",which_peice,present_position,direction);
    }
    int moved_position = present_position + direction;
    //If the peice is movable to that moved_positon.
    if(Is_move_possible(board_dash,which_peice,present_position,direction))
    {
        /*Lets first think about moving the movable peice*/
        //We have already checked that where the piece wants to go, it can be moved. so we can just move it.
        if(which_peice == 'm'||which_peice =='s'||which_peice == 'k')
        {
            assign(board_dash,moved_position,board_dash[present_position].peice_color,board_dash[present_position].peice_type,board_dash[present_position].orientation);
            assign_empty(board_dash,present_position);
        }

        /*But if the peice is a delfector, then it can move with the above rules, but along with that it can also exchange itself with deflector 
        of its own kind*/
        else if(which_peice =='d')
        {
            int  d1 = board_dash[moved_position].orientation;
            int  d2 = present_position;
            char d3 = board_dash[moved_position].peice_type;
            char d4 = board_dash[moved_position].peice_color;
            assign(board_dash,moved_position,board_dash[present_position].peice_color,board_dash[present_position].peice_type,board_dash[present_position].orientation);
            assign(board_dash,d2,d4,d3,d1);
        }
    }
    if(output_print)
    {
        fprintf(output_file,"Outside the 'move_the_peice' function\n");
        fprintf(output_file,"\n");
    }
}

//Thi function will check if the peice could be oriented or not.
bool Is_orientation_possibe(struct peice* board_dash,char which_peice,int present_position)
{
    if(board_dash[present_position].peice_type == 'k')
    {
        if(output_print)fprintf(output_file,"Attempt to move the king\n");
        return false;
    }

    else if(board_dash[present_position].peice_type == 'm')
    {
        return true;
    }

    else if(board_dash[present_position].peice_type == 'd')
    {
        return true;
    }

    else if(board_dash[present_position].peice_type == 's')
    {
        return true;
    }

    else if(board_dash[present_position].peice_type == 'l')
    {
        //Rememebr that a lazer could be oriented in different directions
        return true;
    }
    return false;
}

/*After the success of making the move peice function, we can finally now owrk on building the changing the orientation function*/
/*A rotation value of 1 would mean we are rotating the peice in anticlockwise and -1 means we are rotating it clockwise.
It takes in which type of peice is it, what is its current position on board, and in what sense does it want to rotate. 
Also note that in case of deflector, no need of rotate integer. So it can be set to 0 whenever needed.
*/
void orient_peice(struct peice* board,char which_peice,int present_position,int rotate)
{
    if(output_print)
    {
        fprintf(output_file,"\n");
        fprintf(output_file,"Inside the 'orient_peice' function\n");
        fprintf(output_file,"Attempt to orient peice %c, at %d,in the sense of %d\n",board[present_position].peice_type,present_position,rotate);
    }
    if(which_peice == 'k')
    {
        if(output_print)fprintf(output_file,"Attempt to rotate king");
        return;
    }
    else
    {
        //If the peice is lazer then blue can only have orientation of 3 and 4, and red can only have orientation of 1 and 2.
        if(which_peice == 'l')
        {
            if(board[present_position].orientation == 1){board[present_position].orientation = 2;}
            else if(board[present_position].orientation == 2){board[present_position].orientation = 1;}
            else if(board[present_position].orientation == 3){board[present_position].orientation = 4;}
            else if(board[present_position].orientation == 4){board[present_position].orientation = 3;}
            if(output_print)fprintf(output_file,"Oriented the lazer\n");
        }

        //This will check for rotating the Shield or Mirror
        else if(which_peice == 's' || which_peice == 'm')
        {
            if(board[present_position].orientation == 1 && rotate == (-1)){board[present_position].orientation = 4;}
            else if(board[present_position].orientation == 4 && rotate == (+1)){board[present_position].orientation = 1;}
            else
            {
                board[present_position].orientation = board[present_position].orientation + rotate;
            }
            if(output_print)fprintf(output_file,"Oriented mirror/shield");
            return;
        }

        //This will check for rotating the deflector
        else if(which_peice == 'd')
        {
            if(board[present_position].orientation == 1){board[present_position].orientation = 2;}/* / */
            else if(board[present_position].orientation == 2){board[present_position].orientation = 1;}/* \ */
            if(output_print)fprintf(output_file,"Oriented Deflector\n");
        }
    }
    if(output_print)
    {
        fprintf(output_file,"Outside the 'oreint' function\n");
        fprintf(output_file,"\n");
    }
}



/**********************************************        LAZER PHYSICS        *************************************************/
/* 
After successfully making the orientation function, we can now move on to make the laser physics. So this function will
take in the information of who is going to hit the lazer, blue or red, and board state. Then it returns where did the lazer hit?
Did it kill a piece? or did it escaped out of board? or was it blocked by sheild.
*/

//The above function will return a structure type variable, and it will first have information of did it hit(kill) something or not.
//Then did it escaped? which which peice did it hit? what is its color? and lastly what was its position where it was hit?
struct lazer_hit
{
    bool hit;
    bool escape;
    char peice_type;
    char peice_color;
    int position;
};

/*
This will take in two inputs. One is the position of photon, and other is in which direction is it travelling.
So now direction could be (+1): up, (-1): down, (+8): left, (-8): right
This function is only useful for the below function. Should not be used else where.
*/
bool laser_not_escaped(struct peice* board_dash ,int photon_position,int direction)
{
    while(photon_position<=80 && photon_position>=1)
    {
        //If the photon is at the right top corner
        if(photon_position == 8 && (direction == +1 || direction == -8) && board_dash[photon_position].peice_type =='n') return false;
        //If the photon is at the top edge
        else if(photon_position%8 == 0 && direction == +1 && board_dash[photon_position].peice_type =='n') return false;
    
        //If the photon is at the lazer
        else if(photon_position == 80)
        {
            if(output_print)fprintf(output_file,"Lazer hitting Lazer\n");
            return false;
        }
        else if(photon_position == 1)
        {
            if(output_print)fprintf(output_file,"Lazer is at Lazer\n");
            return false;
        }

        //If photon is at the left bottom corner
        else if(photon_position == 73 && (direction == +8 || direction == -1) && board_dash[photon_position].peice_type =='n') return false;
        //If the photon is at bottom edge of the board
        else if (photon_position%8 == 1 && direction == -1 && board_dash[photon_position].peice_type =='n') return false;
    
        //If lazer is along right edge
        else if((photon_position>1 && photon_position<=8) && (direction == -8) && board_dash[photon_position].peice_type =='n') return false;
        //If the lazer is along left egde.
        else if((photon_position>=73 && photon_position<80) && (direction == +8) && board_dash[photon_position].peice_type =='n') return false;
        else
        {
            return true;
        }
    }
    return false;
}

/*This function simulate the laser and will see if the piece is hit, or did the laser escaped. If a piece is hit, then then it returns information about the piece. And this will actually update the board.*/
struct lazer_hit laser_test(struct peice* board_dash,char which_color)
{
    struct lazer_hit kill_peice;
    kill_peice.escape = false;
    int tracer;
    int photon_position;

    if(which_color == 'b')
    {
        photon_position = 1;
        if(board_dash[1].orientation == 3){tracer = +1;}
        else if(board_dash[1].orientation == 4){tracer = +8;}
        photon_position = photon_position + tracer;
    }
    else if(which_color == 'r')
    {
        photon_position = 80;
        if(board_dash[80].orientation == 1){tracer = -1;}
        else if(board_dash[80].orientation == 2){tracer = -8;}
        photon_position = photon_position + tracer;
    }

    //Laser escape will check if the 
    while(laser_not_escaped(board_dash,photon_position,tracer))
    {
        //Now if the photon gets to hit some object
        if(board_dash[photon_position].peice_type!='n')
            {
                //If the photon hit the king itself.
                if(board_dash[photon_position].peice_type == 'k')
                {
                    if(board_dash[photon_position].peice_color == 'b' && output_print)fprintf(output_file,"Blue King at position %d is killed\n",photon_position);
                    else if(board_dash[photon_position].peice_color == 'r' && output_print)fprintf(output_file,"Red King at position %d is killed\n",photon_position);
                    //updating the board

                    kill_peice.peice_color = board_dash[photon_position].peice_color;
                    game_over = true;//if a king is hit then the game is over
                    kill_peice.hit = true; //yes a piece is hit
                    kill_peice.escape = false;//No the laser did not escape
                    kill_peice.peice_type = 'k';//The peice was king that is killed
                    kill_peice.position = photon_position;//The position of king.
                    assign_empty(board_dash,photon_position);//After the information is stored in the kill piece, we can make it empty.
                    return kill_peice;
                }

                //If the photon hit the shield
                else if(board_dash[photon_position].peice_type == 's')
                {
                    //This means the light is travelling in left direction(4)
                    if(tracer == +8)
                    {
                        if(board_dash[photon_position].orientation == 2)
                        {
                            if(output_print)fprintf(output_file,"Sheild blocked the laser at %d\n",photon_position);
                            kill_peice.peice_color = board_dash[photon_position].peice_color;
                            kill_peice.escape = false;
                            kill_peice.hit = false;
                            kill_peice.peice_type = 's';
                            kill_peice.position = photon_position;
                            return kill_peice;
                        }
                        else 
                        {
                            if(output_print)fprintf(output_file,"Sheild is hit and killed at %d\n",photon_position);
                            kill_peice.peice_color = board_dash[photon_position].peice_color;
                            kill_peice.escape = false;
                            kill_peice.hit = true;
                            kill_peice.peice_type = 's';
                            kill_peice.position = photon_position;
                            assign_empty(board_dash,photon_position);//The piece is hit and hence will be nothing at that place now.
                            return kill_peice;
                        }
                    }

                    //This means the light is travelling in down direction(1)
                    else if(tracer == -1)
                    {
                        //The sheild is blocking the laser
                        if(board_dash[photon_position].orientation == 3)
                        {
                            if(output_print)fprintf(output_file,"Sheild blocked the laser at %d\n",photon_position);
                            kill_peice.peice_color = board_dash[photon_position].peice_color;
                            kill_peice.escape = false;
                            kill_peice.hit = false;
                            kill_peice.peice_type = 's';
                            kill_peice.position = photon_position;
                            return kill_peice;
                        }
                        else 
                        {
                            if(output_print)fprintf(output_file,"Sheild is hit and killed at %d\n",photon_position);
                            kill_peice.peice_color = board_dash[photon_position].peice_color;
                            kill_peice.escape = false;
                            kill_peice.hit = true;
                            kill_peice.peice_type = 's';
                            kill_peice.position = photon_position;
                            assign_empty(board_dash,photon_position);
                            return kill_peice;
                        }
                    }
                    
                    //This mean the light is travelling in right direction(2)
                    else if(tracer == -8)
                    {
                        //And the sheild is blocking the light
                        if(board_dash[photon_position].orientation == 4)
                        {
                            if(output_print)fprintf(output_file,"Sheild blocked the laser at %d\n",photon_position);
                            kill_peice.peice_color = board_dash[photon_position].peice_color;
                            kill_peice.escape = false;
                            kill_peice.hit = false;
                            kill_peice.peice_type = 's';
                            kill_peice.position = photon_position;
                            return kill_peice;
                        }
                        else 
                        {
                            if(output_print)fprintf(output_file,"Sheild is hit and killed at %d\n",photon_position);
                            kill_peice.peice_color = board_dash[photon_position].peice_color;
                            kill_peice.escape = false;
                            kill_peice.hit = true;
                            kill_peice.peice_type = 's';
                            kill_peice.position = photon_position;
                            assign_empty(board_dash,photon_position);
                            return kill_peice;
                        }
                    }
                    
                    //This means the light is travelling in up direction(3)
                    else if(tracer == +1)
                    {
                        //Shield is blocking the light
                        if(board_dash[photon_position].orientation == 1)
                        {
                            if(output_print)fprintf(output_file,"Sheild blocked the laser at %d\n",photon_position);
                            kill_peice.peice_color = board_dash[photon_position].peice_color;
                            kill_peice.escape = false;
                            kill_peice.hit = false;
                            kill_peice.peice_type = 's';
                            kill_peice.position = photon_position;
                            return kill_peice;
                        }
                        else 
                        {
                            if(output_print)fprintf(output_file,"Sheild is hit and killed at %d\n",photon_position);
                            kill_peice.peice_color = board_dash[photon_position].peice_color;
                            kill_peice.escape = false;
                            kill_peice.hit = true;
                            kill_peice.peice_type = 's';
                            kill_peice.position = photon_position;
                            assign_empty(board_dash,photon_position);
                            return kill_peice;
                        }
                    }
                }
                //If the photon hit the mirror
                else if(board_dash[photon_position].peice_type == 'm')
                {
                    //This means photon is travelling in left direction(4)
                    if(tracer == +8)
                    {
                        //And the mirror is like this '#/'
                        if(board_dash[photon_position].orientation == 1)
                        {
                            if(output_print)fprintf(output_file,"The beam reflected in down direction at %d\n",photon_position);
                            tracer = (-1);
                        }
                        //This means mirror is like this '#\'
                        else if(board_dash[photon_position].orientation == 2)
                        {
                            if(output_print)fprintf(output_file,"The beam deflected in up direction at %d\n",photon_position);
                            tracer = (+1);
                        }
                        else 
                        {
                            if(output_print)fprintf(output_file,"Mirror is hit and killed at %d\n",photon_position);
                            kill_peice.peice_color = board_dash[photon_position].peice_color;
                            kill_peice.escape = false;
                            kill_peice.hit = true;
                            kill_peice.peice_type = 'm';
                            kill_peice.position = photon_position;
                            assign_empty(board_dash,photon_position);
                            return kill_peice;
                        }
                    }
                    //This means photon is travelling in right direction(2)
                    else if(tracer == -8)
                    {
                        //this means the mirror is like this '\#'
                        if(board_dash[photon_position].orientation == 4)
                        {
                            if(output_print)fprintf(output_file,"The beam reflected in down direction at %d\n",photon_position);
                            tracer = (-1);
                        }
                        //this means the mirror is like this '/#'
                        else if(board_dash[photon_position].orientation == 3)
                        {
                            if(output_print)fprintf(output_file,"The beam deflected in up direction at %d\n",photon_position);
                            tracer = (+1);
                        }
                        else 
                        {
                            if(output_print)fprintf(output_file,"Mirror is hit and killed at %d\n",photon_position);
                            kill_peice.peice_color = board_dash[photon_position].peice_color;
                            kill_peice.escape = false;
                            kill_peice.hit = true;
                            kill_peice.peice_type = 'm';
                            kill_peice.position = photon_position;
                            assign_empty(board_dash,photon_position);
                            return kill_peice;
                        }
                    }
                    //This means photon is travelling in up direction(3)
                    else if(tracer == +1)
                    {
                        //If the mirror is like this '#/'
                        if(board_dash[photon_position].orientation == 1)
                        {
                            if(output_print)fprintf(output_file,"The beam reflected in right direction at %d\n",photon_position);
                            tracer = (-8);
                        }
                        //If the mirror is like this '\#'
                        else if(board_dash[photon_position].orientation == 4)
                        {
                            if(output_print)fprintf(output_file,"The beam deflected in left direction at %d\n",photon_position);
                            tracer = (+8);
                        }
                        else 
                        {
                            if(output_print)fprintf(output_file,"Mirror is hit and killed at %d\n",photon_position);
                            kill_peice.peice_color = board_dash[photon_position].peice_color;
                            kill_peice.escape = false;
                            kill_peice.hit = true;
                            kill_peice.peice_type = 'm';
                            kill_peice.position = photon_position;
                            assign_empty(board_dash,photon_position);
                            return kill_peice;
                        }
                    }
                    //this means photon is travelling in down direction(1)
                    else if(tracer == -1)
                    {
                        //The means the mirror is like this '/#'
                        if(board_dash[photon_position].orientation == 3)
                        {
                            if(output_print)fprintf(output_file,"The beam reflected in left direction at %d\n",photon_position);
                            tracer = (+8);
                        }
                        //This means the photn is like this '#\'
                        else if(board_dash[photon_position].orientation == 2)
                        {
                            if(output_print)fprintf(output_file,"The beam deflected in right direction at %d\n",photon_position);
                            tracer = (-8);
                        }
                        else 
                        {
                            if(output_print)fprintf(output_file,"Mirror is hit and killed at %d\n",photon_position);
                            kill_peice.peice_color = board_dash[photon_position].peice_color;
                            kill_peice.escape = false;
                            kill_peice.hit = true;
                            kill_peice.peice_type = 'm';
                            kill_peice.position = photon_position;
                            assign_empty(board_dash,photon_position);
                            return kill_peice;
                        }
                    }
                }
                //If the photon hit the deflector
                else if(board_dash[photon_position].peice_type == 'd')
                {
                    //This means photon is travelling in left direction(4)
                    if(tracer == +8)
                    {
                        // So one means '/', and this will move the photon down
                        if(board_dash[photon_position].orientation == 1)
                        {
                            if(output_print)fprintf(output_file,"The beam reflected in down direction at %d\n",photon_position);
                            tracer = (-1);
                        }
                        //This means deflector is like '\'
                        else if(board_dash[photon_position].orientation == 2)
                        {
                            if(output_print)fprintf(output_file,"The beam deflected in up direction at %d\n",photon_position);
                            tracer = (+1);
                        }
                    }
                    //This means photon is travelling in right direction(2)
                    else if(tracer == -8)
                    {
                        //This means the deflector is like this '\'
                        if(board_dash[photon_position].orientation == 2)
                        {
                            if(output_print)fprintf(output_file,"The beam reflected in down direction at %d\n",photon_position);
                            tracer = (-1);
                        }
                        //This means the deflector is like this '/'
                        else if(board_dash[photon_position].orientation == 1)
                        {
                            if(output_print)fprintf(output_file,"The beam deflected in up direction at %d\n",photon_position);
                            tracer = (+1);
                        }
                    }
                    //This means photon is travelling in up direction(3)
                    else if(tracer == +1)
                    {
                        //This means the deflector is like this '/'
                        if(board_dash[photon_position].orientation == 1)
                        {
                            if(output_print)fprintf(output_file,"The beam reflected in right direction at %d\n",photon_position);
                            tracer = (-8);
                        }
                        //This means the deflector is like this '\'
                        else if(board_dash[photon_position].orientation == 2)
                        {
                            if(output_print)fprintf(output_file,"The beam deflected in left direction at %d\n",photon_position);
                            tracer = (+8);
                        }
                    }
                    //this means photn is travelling in down direction(1)
                    else if(tracer == -1)
                    {
                        //This means the deflector is like this '/'
                        if(board_dash[photon_position].orientation == 1)
                        {
                            if(output_print)fprintf(output_file,"The beam reflected in left direction at %d\n",photon_position);
                            tracer = (+8);
                        }
                        //This means the deflector is like this '\'
                        else if(board_dash[photon_position].orientation == 2)
                        {
                            if(output_print)fprintf(output_file,"The beam deflected in right direction at %d\n",photon_position);
                            tracer = (-8);
                        }
                    }
                }
            }
  
        photon_position = photon_position + tracer;

        if(!(photon_position<=80 && photon_position>=1))
        {
            if(output_print)fprintf(output_file,"Lazer escaped the board at %d\n",photon_position);
            kill_peice.hit = false;
            kill_peice.escape = true;
            kill_peice.peice_color = 'n';
            kill_peice.peice_type = 'n';
            kill_peice.position = photon_position;
            return kill_peice;
        }
    }
    //If the laser has not escaped then it must be inside th while loop, and have returned the funcion. But if that did not happedn, then it has surely escaped and thus before that I will assign the properties to this laser and then send it.
    if(output_print)fprintf(output_file,"Lazer escaped the board at %d\n",photon_position);
    kill_peice.hit = false;
    kill_peice.escape = true;
    kill_peice.peice_color = 'n';
    kill_peice.peice_type = 'n';
    kill_peice.position = photon_position;
    return kill_peice;  
}

/*This is same as lasertest but the difference is it doesnt update the board just give us details about the piece that is hit if not nothing
This function is created just for checking purpose, so that while checking the board actually doesn't get updated.*/
struct lazer_hit Is_laser_test(struct peice* board_dash,char which_color)
{
    struct lazer_hit kill_peice;
    kill_peice.escape = false;
    int tracer;
    int photon_position;

    if(which_color == 'b')
    {
        photon_position = 1;
        if(board_dash[1].orientation == 3){tracer = +1;}
        else if(board_dash[1].orientation == 4){tracer = +8;}
        photon_position = photon_position + tracer;
    }
    else if(which_color == 'r')
    {
        photon_position = 80;
        if(board_dash[80].orientation == 1){tracer = -1;}
        else if(board_dash[80].orientation == 2){tracer = -8;}
        photon_position = photon_position + tracer;
    }

    while(laser_not_escaped(board_dash,photon_position,tracer))
    {
        //Now if the photon gets to hit some object
        if(board_dash[photon_position].peice_type!='n')
        {
            //If the photon hit the king itself.
            if(board_dash[photon_position].peice_type == 'k')
            {
                if(board_dash[photon_position].peice_color == 'b' && output_print)fprintf(output_file,"Blue King at position %d is killed\n",photon_position);
                else if(board_dash[photon_position].peice_color == 'r' && output_print)fprintf(output_file,"Red King at position %d is killed\n",photon_position);
                //updating the board
                kill_peice.peice_color = board_dash[photon_position].peice_color;
                game_over = true;
                kill_peice.hit = true;
                kill_peice.peice_type = 'k';
                kill_peice.position = photon_position;
                kill_peice.escape = false;
                return kill_peice;
            }
            //If the photon hit the shell
            else if(board_dash[photon_position].peice_type == 's')
            {
                //This means the light is travelling in left direction(4)
                if(tracer == +8)
                {
                    if(board_dash[photon_position].orientation == 2)
                    {
                        if(output_print)fprintf(output_file,"Sheild blocked the laser at %d\n",photon_position);
                        kill_peice.peice_color = board_dash[photon_position].peice_color;
                        kill_peice.escape = false;
                        kill_peice.hit = false;
                        kill_peice.peice_type = 's';
                        kill_peice.position = photon_position;
                        return kill_peice;
                    }
                    else 
                    {
                        if(output_print)fprintf(output_file,"Sheild is hit and killed at %d\n",photon_position);
                        //updating the board
                        kill_peice.peice_color = board_dash[photon_position].peice_color;
                        kill_peice.hit = true;
                        kill_peice.escape = false;
                        kill_peice.peice_type = 's';
                        kill_peice.position = photon_position;
                        return kill_peice;
                    }
                }

                //This means the light is travelling in down direction(1)
                else if(tracer == -1)
                {
                    if(board_dash[photon_position].orientation == 3)
                    {
                        if(output_print)fprintf(output_file,"Sheild blocked the laser at %d\n",photon_position);
                        kill_peice.peice_color = board_dash[photon_position].peice_color;
                        kill_peice.escape = false;
                        kill_peice.hit = false;
                        kill_peice.peice_type = 's';
                        kill_peice.position = photon_position;
                        return kill_peice;
                    }
                    else 
                    {
                        if(output_print)fprintf(output_file,"Sheild is hit and killed at %d\n",photon_position);
                        kill_peice.peice_color = board_dash[photon_position].peice_color;
                        kill_peice.escape = false;
                        kill_peice.hit = true;
                        kill_peice.peice_type = 's';
                        kill_peice.position = photon_position;
                        return kill_peice;
                    }
                }
                
                //This mean the light is travelling in right direction(2)
                else if(tracer == -8)
                {
                    if(board_dash[photon_position].orientation == 4)
                    {
                        if(output_print)fprintf(output_file,"Sheild blocked the laser at %d\n",photon_position);
                        kill_peice.peice_color = board_dash[photon_position].peice_color;
                        kill_peice.escape = false;
                        kill_peice.hit = false;
                        kill_peice.peice_type = 's';
                        kill_peice.position = photon_position;
                        return kill_peice;
                    }
                    else 
                    {
                        if(output_print)fprintf(output_file,"Sheild is hit and killed at %d\n",photon_position);
                        kill_peice.peice_color = board_dash[photon_position].peice_color;
                        kill_peice.escape = false;
                        kill_peice.hit = true;
                        kill_peice.peice_type = 's';
                        kill_peice.position = photon_position;
                        return kill_peice;
                    }
                }
                
                //This means the light is travelling in up direction(3)
                else if(tracer == +1)
                {
                    if(board_dash[photon_position].orientation == 1)
                    {
                        if(output_print)fprintf(output_file,"Sheild blocked the laser at %d\n",photon_position);
                        kill_peice.peice_color = board_dash[photon_position].peice_color;
                        kill_peice.escape = false;
                        kill_peice.hit = false;
                        kill_peice.peice_type = 's';
                        kill_peice.position = photon_position;
                        return kill_peice;
                    }
                    else 
                    {
                        if(output_print)fprintf(output_file,"Sheild is hit and killed at %d\n",photon_position);
                        kill_peice.peice_color = board_dash[photon_position].peice_color;
                        kill_peice.escape = false;
                        kill_peice.hit = true;
                        kill_peice.peice_type = 's';
                        kill_peice.position = photon_position;
                        return kill_peice;
                    }
                }
            }
            //If the photon hit the mirror
            else if(board_dash[photon_position].peice_type == 'm')
            {
                //This means photon is travelling in left direction(4)
                if(tracer == +8)
                {
                    if(board_dash[photon_position].orientation == 1)
                    {
                        if(output_print)fprintf(output_file,"The beam reflected in down direction at %d\n",photon_position);
                        tracer = (-1);
                    }
                    else if(board_dash[photon_position].orientation == 2)
                    {
                        if(output_print)fprintf(output_file,"The beam deflected in up direction at %d\n",photon_position);
                        tracer = (+1);
                    }
                    else 
                    {
                        if(output_print)fprintf(output_file,"Mirror is hit and killed at %d\n",photon_position);
                        kill_peice.peice_color = board_dash[photon_position].peice_color;
                        kill_peice.escape = false;
                        kill_peice.hit = true;
                        kill_peice.peice_type = 'm';
                        kill_peice.position = photon_position;
                        return kill_peice;
                    }
                }
                //This means photon is travelling in right direction(2)
                else if(tracer == -8)
                {
                    if(board_dash[photon_position].orientation == 4)
                    {
                        if(output_print)fprintf(output_file,"The beam reflected in down direction at %d\n",photon_position);
                        tracer = (-1);
                    }
                    else if(board_dash[photon_position].orientation == 3)
                    {
                        if(output_print)fprintf(output_file,"The beam deflected in up direction at %d\n",photon_position);
                        tracer = (+1);
                    }
                    else 
                    {
                        if(output_print)fprintf(output_file,"Mirror is hit and killed at %d\n",photon_position);
                        kill_peice.peice_color = board_dash[photon_position].peice_color;
                        kill_peice.escape = false;
                        kill_peice.hit = true;
                        kill_peice.peice_type = 'm';
                        kill_peice.position = photon_position;
                        return kill_peice;
                    }
                }
                //This means photn is travelling in up direction(3)
                else if(tracer == +1)
                {
                    if(board_dash[photon_position].orientation == 1)
                    {
                        if(output_print)fprintf(output_file,"The beam reflected in right direction at %d\n",photon_position);
                        tracer = (-8);
                    }
                    else if(board_dash[photon_position].orientation == 4)
                    {
                        if(output_print)fprintf(output_file,"The beam deflected in left direction at %d\n",photon_position);
                        tracer = (+8);
                    }
                    else 
                    {
                        if(output_print)fprintf(output_file,"Mirror is hit and killed at %d\n",photon_position);
                        kill_peice.peice_color = board_dash[photon_position].peice_color;
                        kill_peice.escape = false;
                        kill_peice.hit = true;
                        kill_peice.peice_type = 'm';
                        kill_peice.position = photon_position;
                        return kill_peice;
                    }
                }
                //this means photn is travelling in down direction(1)
                else if(tracer == -1)
                {
                    if(board_dash[photon_position].orientation == 3)
                    {
                        if(output_print)fprintf(output_file,"The beam reflected in left direction at %d\n",photon_position);
                        tracer = (+8);
                    }
                    else if(board_dash[photon_position].orientation == 2)
                    {
                        if(output_print)fprintf(output_file,"The beam deflected in right direction at %d\n",photon_position);
                        tracer = (-8);
                    }
                    else 
                    {
                        if(output_print)fprintf(output_file,"Mirror is hit and killed at %d\n",photon_position);
                        kill_peice.peice_color = board_dash[photon_position].peice_color;
                        kill_peice.escape = false;
                        kill_peice.hit = true;
                        kill_peice.peice_type = 'm';
                        kill_peice.position = photon_position;
                        return kill_peice;
                    }
                }
            }
            //If the photn hit the deflector
            else if(board_dash[photon_position].peice_type == 'd')
            {
                //This means photon is travelling in left direction(4)
                if(tracer == +8)
                {
                    if(board_dash[photon_position].orientation == 1)
                    {
                        if(output_print)fprintf(output_file,"The beam reflected in down direction at %d\n",photon_position);
                        tracer = (-1);
                    }
                    else if(board_dash[photon_position].orientation == 2)
                    {
                        if(output_print)fprintf(output_file,"The beam deflected in up direction at %d\n",photon_position);
                        tracer = (+1);
                    }
                }
                //This means photon is travelling in right direction(2)
                else if(tracer == -8)
                {
                    if(board_dash[photon_position].orientation == 2)
                    {
                        if(output_print)fprintf(output_file,"The beam reflected in down direction at %d\n",photon_position);
                        tracer = (-1);
                    }
                    else if(board_dash[photon_position].orientation == 1)
                    {
                        if(output_print)fprintf(output_file,"The beam deflected in up direction at %d\n",photon_position);
                        tracer = (+1);
                    }
                }
                //This means photn is travelling in up direction(3)
                else if(tracer == +1)
                {
                    if(board_dash[photon_position].orientation == 1)
                    {
                        if(output_print)fprintf(output_file,"The beam reflected in right direction at %d\n",photon_position);
                        tracer = (-8);
                    }
                    else if(board_dash[photon_position].orientation == 2)
                    {
                        if(output_print)fprintf(output_file,"The beam deflected in left direction at %d\n",photon_position);
                        tracer = (+8);
                    }
                }
                //this means photn is travelling in down direction(1)
                else if(tracer == -1)
                {
                    if(board_dash[photon_position].orientation == 1)
                    {
                        if(output_print)fprintf(output_file,"The beam reflected in left direction at %d\n",photon_position);
                        tracer = (+8);
                    }
                    else if(board_dash[photon_position].orientation == 2)
                    {
                        if(output_print)fprintf(output_file,"The beam deflected in right direction at %d\n",photon_position);
                        tracer = (-8);
                    }
                }
            }
        }
  
        photon_position = photon_position + tracer;

        //If the photn has reached a position which is out of the 
        if(!(photon_position<=80 && photon_position>=1))
            {
                if(output_print && output_print)fprintf(output_file,"Lazer escaped the board at %d\n",photon_position);
                kill_peice.hit = false;
                kill_peice.escape = true;
                kill_peice.peice_color = 'n';
                kill_peice.peice_type = 'n';
                kill_peice.position = photon_position;
                return kill_peice;
            }
    }
    if(output_print && output_print)fprintf(output_file,"Lazer escaped the board at %d\n",photon_position);
    kill_peice.hit = false;
    kill_peice.escape = true;
    kill_peice.peice_color = 'n';
    kill_peice.peice_type = 'n';
    kill_peice.position = photon_position;
    return kill_peice;
}


/*This function will take in the state of board, and the color of lasr that is going to shoot. If the game is lost by anyone of the layer
    it returns true, or else it returns false and the game continues. Note that it doesnt change the board. It just checks without actually 
    updating.*/
bool Is_game_over(struct peice* board_dash,char which_laser)
{
    struct lazer_hit temp_peice = Is_laser_test(board_dash,which_laser);
    if(temp_peice.peice_color == 'b' && temp_peice.peice_type == 'k')
    {
        if(output_print)fprintf(output_file,"Game is lost by Blue\n");
        return true;
    }
    else if(temp_peice.peice_color == 'r' && temp_peice.peice_type == 'k')
    {
        if(output_print)fprintf(output_file,"Game is lost by Red\n");
        return true;
    }
    else return false;
}



/************************************************            GAME TREE              *************************************************/
/*After setting up the complete board, and being able to move and control the peices, we could finally make our tree now*/

/*This function takes in the board the current board state, and returns its evaluation just by looking at the no of peices at both sides*/
int evaluation(struct peice* board_dash)
{
    int blue_peices = 0;//positive
    int red_peices = 0; //negative
    //Count the number of mirror points
    for(int i=1;i<81;i++)
    {
        if(board_dash[i].peice_color == 'b')
        {
            if(board_dash[i].peice_type == 'm') blue_peices = blue_peices + 10;
            else if(board_dash[i].peice_type == 'k')blue_peices = blue_peices + 1000;
            else if(board_dash[i].peice_type == 's') blue_peices = blue_peices + 10;
        }

        else if(board_dash[i].peice_color == 'r')
        {
            if(board_dash[i].peice_type == 'm') red_peices = red_peices + 10;
            else if(board_dash[i].peice_type == 'k')red_peices = red_peices + 1000;
            else if(board_dash[i].peice_type == 's') red_peices = red_peices + 10;
        }
    }

    return (blue_peices-red_peices);

}

/*Now i wish to create function which will add a node to */

/*This structure of a linked list that will store all the data about all the movable peices on the board. Which includes mirrors, 
deflectors, king, and sheilds.*/
struct movable_peice_node
{
    struct peice data;                  //This will contain data about the peice that is movable.
    int position;                       //This will contain the position of the peice
    struct movable_peice_node* next;    //This will point to the next node
};

/*This will add a movable_peice_node to the linked list named movable_peice and it will fill the data with the new movable piece 
 that is detected. This function will update the movable peice linked list and return nothing*/
struct movable_peice_node* add_node_of_movable_peice(struct movable_peice_node* movable_peice,struct peice data,int position_i)
{
    struct movable_peice_node* p;
    p = movable_peice;
    if(p == NULL)
    {
        p = (struct movable_peice_node*)malloc(sizeof(struct movable_peice_node));
        p->data = data;
        p->position = position_i;
        p->next = NULL;
        return p;
    }
    
    while(p->next != NULL)
    {
        p = p->next;
    }
    
    struct movable_peice_node* add;
    add = (struct movable_peice_node*)malloc(sizeof(struct movable_peice_node));
    add->data = data;
    add->position = position_i;
    add->next = NULL;
    p->next = add;
    return movable_peice;
}

/*This function will ask which color's movable peices do you want to store in the returning linked list? and it will 
return the linked list's header pointer*/
struct movable_peice_node* create_movable(struct peice* current_board,char which_color)
{
    struct movable_peice_node* movable_peice_linked_list = NULL;
    
    if(which_color == 'b')
    {
        for(int i=1;i<81;i++)
        {
            //So all the peices that is blue is color is movable, except the laser
            if(current_board[i].peice_color == 'b' && current_board[i].peice_type != 'l')
            {
                movable_peice_linked_list = add_node_of_movable_peice(movable_peice_linked_list,current_board[i],i);
            }
        }
    }
    
    else if(which_color == 'r')
    {
        for(int i=1;i<81;i++)
        {
            if(current_board[i].peice_color == 'r' && current_board[i].peice_type != 'l')
            {
                movable_peice_linked_list = add_node_of_movable_peice(movable_peice_linked_list,current_board[i],i);
            }
        }
    }
    
    return movable_peice_linked_list;
}

/*This function will generate tree of all the possible moves and return the bext move, in the form of tree node. This node will
contain the desired move to be taken, in the form of updated board state.*/
struct tree_node
{
    //This is the board state of stored inside the tree node
    struct peice* data;
    //struct peice* best_child;//I am making this to track the best possible board state.
    //This will be the evaluation of the tree node.
    int evaluation;
};

//This function will take in a pointer type board state of game, and will return a new pointer board that points to the copied board
struct peice* copy_board(struct peice* current_board)
{
    struct peice* copied_board;
    copied_board = (struct peice*)malloc(sizeof(struct peice)*81);
    for(int i = 1;i<81;i++)
    {
        copied_board[i] = current_board[i];
    }
    return copied_board;
}

//This function will just return the maximum of two number
int max(int a,int b)
{
    if(a>=b){return a;}
    else return b;
}
//THis function will return minimum of two numbers
int min(int a,int b)
{
    if(a>b)return b;
    else return a;
}

/*MEMORY MANAGEMENT*/
//So there is this p linked list that is formed and we wish to delete it completly so the following function will take in the
//head of the linked list and returns nothing, but it being deleted completly
void delete_linked_list(struct movable_peice_node* p)
{
    struct movable_peice_node* temp = p;
    while(p != NULL)
    {
        p = p->next;
        free(temp);
        temp = p;
    }
    return;
}

/*This function will return the tree_node of the step taken and it will contain the information about the next board step*/
/**
 *  1) is_root_call :
 *      This is the varibale that will be sued to get the first child from all the sub sequent child that the tree will explore. And this will be set to true when called from the main function, but wille set to false when the recursive calling is done of minimax.
 */
struct tree_node* minimax(struct peice* current_board,int depth,bool maximizer_blue,int alpha,int beta,bool is_root_call)
{
    // if(output_print)
    // {
    //     fprintf(output_file,"\n");
    //     fprintf(output_file,"Inside the minimax function\n");
    //     fprintf(output_file,"depth = %d, aplha = %d, beta = %d\n",depth,alpha,beta);
    // }
    //This will be the child node of the current_board that will be passed to the recursive function of minimax
    struct peice* child_board = NULL;   //This pointer will store the current board, and will be used for iterations.
    struct tree_node* child = NULL;     //This pointer will store the data from recursion (child board and its evaluation) 
    struct peice* best_child = NULL;    //This will store the best child for the parent.

    //If it is blue's turn
    if(maximizer_blue)
    {
        if(output_print)fprintf(output_file,"Inside Blue's turn\n");
        //Before blue's turn red laser will be shooted and see if the game is over.
        if(depth == 0 || Is_game_over(current_board,'r'))
        {
            laser_test(current_board,'r');//This will update the board with the peice that is killed.
            
            //Here we are preparing for the node to be returned which will contain the evaluation of this board after the lazer is shot
            //and will also contain the board it self.
            struct tree_node* node = (struct tree_node*)malloc(sizeof(struct tree_node));
            if(is_root_call) node->data = copy_board(current_board);
            node->evaluation = evaluation(current_board);
            //node->best_child = current_board;
            if(output_print)fprintf(output_file,"Evaluation of this node is %d\n",node->evaluation);
            if(output_print)fprintf(output_file,"Outside the minimax function from blue node\n");

            //Memory management
            if(child != NULL)free(child);
            if(child_board!=NULL)free(child_board);
            if(best_child!=NULL)free(best_child);

            return node;
        }
        
        //Before Blue plays the game once, red lazer must be fired
        laser_test(current_board,'r');

        fprintf(output_file,"So Blue is not loosing after Red laser is fired\n");
        int maxEval = -10000;//Must be set to negative infinity

        /*This will generate the linked list of all the movable peices of blue. But this doesn't mean they could be moved to all the 
        squares around them*/
        struct movable_peice_node* blue_movable_peices = create_movable(current_board,'b');
        struct movable_peice_node* p = blue_movable_peices;//This pointer will be pointing the above formed linked list so that it could be used.

        //This is the part where we explore all the childs of this current board.
        while(p!=NULL)
        {
            if(output_print)fprintf(output_file,"The next child is '%c' at position %d\n",p->data.peice_type,p->data.position);
            if(output_print)fprintf(output_file,"\n");
            //First we will move the peice forward
            if(Is_move_possible(current_board,p->data.peice_type,p->data.position,+1))
            {
                if(child_board!=NULL)free(child_board);
                //This pointer will point to a current board that will be a copy of the original current board
                child_board = copy_board(current_board);
                //This will move the peice in the copied board and will not change the current board.
                move_the_peice(child_board,p->data.peice_type,p->data.position,+1);
                //This child will return struct tree type node which will contain the data of that child node its evaluation and 
                if(child!=NULL)free(child);
                child = minimax(child_board,depth-1,false,alpha,beta,false);

                //maxEval = max(maxEval,child->evaluation);
                if(child!=NULL && child->evaluation>maxEval)
                {
                    if(best_child!=NULL)free(best_child);
                    maxEval = child->evaluation;
                    if(is_root_call) best_child = copy_board(child_board); 
                }
                if(child!=NULL)alpha = max(alpha,child->evaluation);
                if(beta<=alpha)
                {
                    break;
                }
            }
            //Then we will move the peice forward-right
            if(Is_move_possible(current_board,p->data.peice_type,p->data.position,-7))
            {
                if(child_board!=NULL)free(child_board);
                child_board = copy_board(current_board);
                move_the_peice(child_board,p->data.peice_type,p->data.position,-7);
                if(child!=NULL)free(child);
                child = minimax(child_board,depth-1,false,alpha,beta,false);
                
                //maxEval = max(maxEval,child->evaluation);
                if(child!=NULL && child->evaluation>maxEval)
                {
                    if(best_child!=NULL)free(best_child);
                    maxEval = child->evaluation;
                    if(is_root_call) best_child = copy_board(child_board); 
                }
                if(child!=NULL)alpha = max(alpha,child->evaluation);
                if(beta<=alpha)
                {
                    break;
                }
            }
            //Then we will move the peice forward-left
            if(Is_move_possible(current_board,p->data.peice_type,p->data.position,+9))
            {
                if(child_board!=NULL)free(child_board);
                child_board = copy_board(current_board);
                move_the_peice(child_board,p->data.peice_type,p->data.position,+9);
                if(child!=NULL)free(child);
                child = minimax(child_board,depth-1,false,alpha,beta,false);
                
                //maxEval = max(maxEval,child->evaluation);
                if(child!=NULL && child->evaluation>maxEval)
                {
                    if(best_child!=NULL)free(best_child);
                    maxEval = child->evaluation;
                    if(is_root_call) best_child = copy_board(child_board); 
                }
                if(child!=NULL)alpha = max(alpha,child->evaluation);
                if(beta<=alpha)
                {
                    break;
                }
            }
            //Then we will move the peice to right
            if(Is_move_possible(current_board,p->data.peice_type,p->data.position,-8))
            {
                if(child_board!=NULL)free(child_board);
                child_board = copy_board(current_board);
                move_the_peice(child_board,p->data.peice_type,p->data.position,-8);
                if(child!=NULL)free(child);
                child = minimax(child_board,depth-1,false,alpha,beta,false);
                
                //maxEval = max(maxEval,child->evaluation);
                if(child!=NULL && child->evaluation>maxEval)
                {
                    if(best_child!=NULL)free(best_child);
                    maxEval = child->evaluation;
                    if(is_root_call) best_child = copy_board(child_board); 
                }
                if(child!=NULL)alpha = max(alpha,child->evaluation);
                if(beta<=alpha)
                {
                    break;
                }
            }
            //Thne we will move the peice to left
            if(Is_move_possible(current_board,p->data.peice_type,p->data.position,+8))
            {
                if(child_board!=NULL)free(child_board);
                child_board = copy_board(current_board);
                move_the_peice(child_board,p->data.peice_type,p->data.position,+8);
                if(child!=NULL)free(child);
                child = minimax(child_board,depth-1,false,alpha,beta,false);
                
                //maxEval = max(maxEval,child->evaluation);
                if(child!=NULL && child->evaluation>maxEval)
                {
                    if(best_child!=NULL)free(best_child);
                    maxEval = child->evaluation;
                    if(is_root_call) best_child = copy_board(child_board); 
                }
                if(child!=NULL)alpha = max(alpha,child->evaluation);
                if(beta<=alpha)
                {
                    break;
                }
            }
            //Then we will move the peice right-bottom
            if(Is_move_possible(current_board,p->data.peice_type,p->data.position,-9))
            {
                if(child_board!=NULL)free(child_board);
                child_board = copy_board(current_board);
                move_the_peice(child_board,p->data.peice_type,p->data.position,-9);
                if(child!=NULL)free(child);
                child = minimax(child_board,depth-1,false,alpha,beta,false);
                
                //maxEval = max(maxEval,child->evaluation);
                if(child!=NULL && child->evaluation>maxEval)
                {
                    if(best_child!=NULL)free(best_child);
                    maxEval = child->evaluation;
                    if(is_root_call) best_child = copy_board(child_board); 
                }
                if(child!=NULL)alpha = max(alpha,child->evaluation);
                if(beta<=alpha)
                {
                    break;
                }
            }
            //Then we will move the peice left-bottom
            if(Is_move_possible(current_board,p->data.peice_type,p->data.position,+7))
            {
                if(child_board!=NULL)free(child_board);
                child_board = copy_board(current_board);
                move_the_peice(child_board,p->data.peice_type,p->data.position,+7);
                if(child!=NULL)free(child);
                child = minimax(child_board,depth-1,false,alpha,beta,false);
                
                //maxEval = max(maxEval,child->evaluation);
                if(child!=NULL && child->evaluation>maxEval)
                {
                    if(best_child!=NULL)free(best_child);
                    maxEval = child->evaluation;
                    if(is_root_call) best_child = copy_board(child_board); 
                }
                if(child!=NULL)alpha = max(alpha,child->evaluation);
                if(beta<=alpha)
                {
                    break;
                }
            }
            //The we will move the peice to bottom
            if(Is_move_possible(current_board,p->data.peice_type,p->data.position,-1))
            {
                if(child_board!=NULL)free(child_board);
                child_board = copy_board(current_board);
                move_the_peice(child_board,p->data.peice_type,p->data.position,-1);
                if(child!=NULL)free(child);
                child = minimax(child_board,depth-1,false,alpha,beta,false);
                
                //maxEval = max(maxEval,child->evaluation);
                if(child!=NULL && child->evaluation>maxEval)
                {
                    if(best_child!=NULL)free(best_child);
                    maxEval = child->evaluation;
                    if(is_root_call) best_child = copy_board(child_board); 
                }
                if(child!=NULL)alpha = max(alpha,child->evaluation);
                if(beta<=alpha)
                {
                    break;
                }
            }


            //Then we will move to peice clockwise
            if(Is_orientation_possibe(current_board,p->data.peice_type,p->data.position))
            {
                if(child_board!=NULL)free(child_board);
                child_board = copy_board(current_board);
                orient_peice(child_board,p->data.peice_type,p->data.position,-1);
                if(child!=NULL)free(child);
                child = minimax(child_board,depth-1,false,alpha,beta,false);
                
                //maxEval = max(maxEval,child->evaluation);
                if(child!=NULL && child->evaluation>maxEval)
                {
                    if(best_child!=NULL)free(best_child);
                    maxEval = child->evaluation;
                    if(is_root_call) best_child = copy_board(child_board); 
                }
                if(child!=NULL)alpha = max(alpha,child->evaluation);
                if(beta<=alpha)
                {
                    fprintf(output_file,"Puring occured\n");
                    break;
                }
            }
            //Then we will move the peice anticlockwise
            if(Is_orientation_possibe(current_board,p->data.peice_type,p->data.position))
            {
                if(child_board!=NULL)free(child_board);
                child_board = copy_board(current_board);
                orient_peice(child_board,p->data.peice_type,p->data.position,+1);
                if(child!=NULL)free(child);
                child = minimax(child_board,depth-1,false,alpha,beta,false);
                
                //maxEval = max(maxEval,child->evaluation);
                if(child!=NULL && child->evaluation>maxEval)
                {
                    if(best_child!=NULL)free(best_child);
                    maxEval = child->evaluation;
                    if(is_root_call) best_child = copy_board(child_board); 
                }
                if(child!=NULL)alpha = max(alpha,child->evaluation);
                if(beta<=alpha)
                {
                    break;
                }
            }
            fprintf(output_file,"\n");
            fprintf(output_file,"Now lets move to the next child\n");
            
            p = p->next;
        }
        
        //After the branches are complete, we no longer need the linked list of all the movable peices so we free them
        if(blue_movable_peices!=NULL)delete_linked_list(blue_movable_peices);
        struct tree_node* node = (struct tree_node*)malloc(sizeof(struct tree_node));
        if(best_child!=NULL) node->data = copy_board(best_child);
        node->evaluation = maxEval;

        if(child != NULL)free(child);
        if(child_board!=NULL)free(child_board);
        //if(best_child!=NULL)free(best_child);

        return node;
    }

    //If it is red's turn
    else
    {
        if(output_print)fprintf(output_file,"Inside red's turn\n");
        //Before red's turn red laser will be shooted and see if the game is over.
        if(depth == 0 || Is_game_over(current_board,'b'))
        {
            laser_test(current_board,'b');
            struct tree_node* node = (struct tree_node*)malloc(sizeof(struct tree_node));
            if(is_root_call) node->data = current_board;
            node->evaluation = evaluation(current_board);
            if(output_print)fprintf(output_file,"Evaluation of this node is %d\n",node->evaluation);
            if(output_print)fprintf(output_file,"Outside the minimax function from red node\n");

            if(child != NULL)free(child);
            if(child_board!=NULL)free(child_board);
            if(best_child!=NULL)free(best_child);

            return node;
        }

        //Before Blue plays the game once, red lazer must be fired
        laser_test(current_board,'b');

        int minEval = 10000;
        struct movable_peice_node* red_movable_peices;
        /*This will generate the linked list of all the movable peices. But this doesn't mean they could be moved to all the peices 
          around them*/
        red_movable_peices = create_movable(current_board,'r');
        struct movable_peice_node* p;
        p = red_movable_peices;
        /*Lets also include the lazer peices into this list of movable peice*/

        while(p!=NULL)
        {
            //First we will move the peice forward
            if(Is_move_possible(current_board,p->data.peice_type,p->data.position,+1))
            {
                if(child_board!=NULL)free(child_board);
                child_board = copy_board(current_board);
                move_the_peice(child_board,p->data.peice_type,p->data.position,+1);
                if(child!=NULL)free(child);
                child = minimax(child_board,depth-1,true,alpha,beta,false);
                
                //minEval = min(minEval,child->evaluation);
                if(child!=NULL && minEval>child->evaluation)
                {
                    if(best_child!=NULL)free(best_child);
                    minEval = child->evaluation;
                    if(is_root_call) best_child = copy_board(child_board);
                }
                if(child!=NULL)beta = min(beta,child->evaluation);
                if(beta<=alpha)
                {
                    break;
                }
            }
            //Then we will move the peice forward-right
            if(Is_move_possible(current_board,p->data.peice_type,p->data.position,-7))
            {
                if(child_board!=NULL)free(child_board);
                child_board = copy_board(current_board);
                move_the_peice(child_board,p->data.peice_type,p->data.position,-7);
                if(child!=NULL)free(child);
                child = minimax(child_board,depth-1,true,alpha,beta,false);
                
                //minEval = min(minEval,child->evaluation);
                //beta = min(beta,child->evaluation);
                if(child!=NULL && minEval>child->evaluation)
                {
                    if(best_child!=NULL)free(best_child);
                    minEval = child->evaluation;
                    if(is_root_call) best_child = copy_board(child_board);
                }
                if(child!=NULL)beta = min(beta,child->evaluation);
                if(beta<=alpha)
                {
                    break;
                }
            }
            //Then we will move the peice forward-left
            if(Is_move_possible(current_board,p->data.peice_type,p->data.position,+9))
            {
                if(child_board!=NULL)free(child_board);
                child_board = copy_board(current_board);
                move_the_peice(child_board,p->data.peice_type,p->data.position,+9);
                if(child!=NULL)free(child);
                struct tree_node* child = minimax(child_board,depth-1,true,alpha,beta,false);
                
                //minEval = min(minEval,child->evaluation);
                //beta = min(beta,child->evaluation);
                if(child!=NULL && minEval>child->evaluation)
                {
                    if(best_child!=NULL)free(best_child);
                    minEval = child->evaluation;
                    if(is_root_call) best_child = copy_board(child_board);
                }
                if(child!=NULL)beta = min(beta,child->evaluation);
                if(beta<=alpha)
                {
                    break;
                }
            }
            //Then we will move the peice to right
            if(Is_move_possible(current_board,p->data.peice_type,p->data.position,-8))
            {
                if(child_board!=NULL)free(child_board);
                child_board = copy_board(current_board);
                move_the_peice(child_board,p->data.peice_type,p->data.position,-8);
                if(child!=NULL)free(child);
                struct tree_node* child = minimax(child_board,depth-1,true,alpha,beta,false);
                
                //minEval = min(minEval,child->evaluation);
                if(child!=NULL && minEval>child->evaluation)
                {
                    if(best_child!=NULL)free(best_child);
                    minEval = child->evaluation;
                    if(is_root_call) best_child = copy_board(child_board);
                }
                if(child!=NULL)beta = min(beta,child->evaluation);
                if(beta<=alpha)
                {
                    break;
                }
            }
            //Thne we will move the peice to left
            if(Is_move_possible(current_board,p->data.peice_type,p->data.position,+8))
            {
                if(child_board!=NULL)free(child_board);
                child_board = copy_board(current_board);
                move_the_peice(child_board,p->data.peice_type,p->data.position,+8);
                if(child!=NULL)free(child);
                struct tree_node* child = minimax(child_board,depth-1,true,alpha,beta,false);
                
                //minEval = min(minEval,child->evaluation);
                if(child!=NULL && minEval>child->evaluation)
                {
                    if(best_child!=NULL)free(best_child);
                    minEval = child->evaluation;
                    if(is_root_call) best_child = copy_board(child_board);
                }
                if(child!=NULL )beta = min(beta,child->evaluation);
                if(beta<=alpha)
                {
                    break;
                }
            }
            //Then we will move the peice right-bottom
            if(Is_move_possible(current_board,p->data.peice_type,p->data.position,-9))
            {
                if(child_board!=NULL)free(child_board);
                child_board = copy_board(current_board);
                move_the_peice(child_board,p->data.peice_type,p->data.position,-9);
                struct tree_node* child = minimax(child_board,depth-1,true,alpha,beta,false);
                
                //minEval = min(minEval,child->evaluation);
                if(child!=NULL && minEval>child->evaluation)
                {
                    if(best_child!=NULL)free(best_child);
                    minEval = child->evaluation;
                    if(is_root_call) best_child = copy_board(child_board);
                }
                if(child!=NULL)beta = min(beta,child->evaluation);
                if(beta<=alpha)
                {
                    break;
                }
            }
            //Then we will move the peice left-bottom
            if(Is_move_possible(current_board,p->data.peice_type,p->data.position,+7))
            {
                if(child_board!=NULL)free(child_board);
                child_board = copy_board(current_board);
                move_the_peice(child_board,p->data.peice_type,p->data.position,+7);
                if(child!=NULL)free(child);
                struct tree_node* child = minimax(child_board,depth-1,true,alpha,beta,false);
                
                //minEval = min(minEval,child->evaluation);
                if(child!=NULL && minEval>child->evaluation)
                {
                    if(best_child!=NULL)free(best_child);
                    minEval = child->evaluation;
                    if(is_root_call) best_child = copy_board(child_board);
                }
                if(child!=NULL)beta = min(beta,child->evaluation);
                if(beta<=alpha)
                {
                    break;
                }
            }
            //The we will move the peice to bottom
            if(Is_move_possible(current_board,p->data.peice_type,p->data.position,-1))
            {
                if(child_board!=NULL)free(child_board);
                child_board = copy_board(current_board);
                move_the_peice(child_board,p->data.peice_type,p->data.position,-1);
                if(child!=NULL)free(child);
                struct tree_node* child = minimax(child_board,depth-1,true,alpha,beta,false);
                
                //minEval = min(minEval,child->evaluation);
                if(child!=NULL && minEval>child->evaluation)
                {
                    if(best_child!=NULL)free(best_child);
                    minEval = child->evaluation;
                    if(is_root_call) best_child = copy_board(child_board);
                }
                if(child!=NULL)beta = min(beta,child->evaluation);
                if(beta<=alpha)
                {
                    break;
                }
            }


            //Then we will move to peice clockwise
            if(Is_orientation_possibe(current_board,p->data.peice_type,p->data.position))
            {
                if(child_board!=NULL)free(child_board);
                child_board = copy_board(current_board);
                orient_peice(child_board,p->data.peice_type,p->data.position,-1);
                if(child!=NULL)free(child);
                struct tree_node* child = minimax(child_board,depth-1,true,alpha,beta,false);
                
                //minEval = min(minEval,child->evaluation);
                if(child!=NULL && minEval>child->evaluation)
                {
                    if(best_child!=NULL)free(best_child);
                    minEval = child->evaluation;
                    if(is_root_call) best_child = copy_board(child_board);
                }
                if(child!=NULL)beta = min(beta,child->evaluation);
                if(beta<=alpha)
                {
                    break;
                }
            }
            //Then we will move the peice anticlockwise
            if(Is_orientation_possibe(current_board,p->data.peice_type,p->data.position))
            {
                if(child_board!=NULL)free(child_board);
                child_board = copy_board(current_board);
                orient_peice(child_board,p->data.peice_type,p->data.position,+1);
                if(child!=NULL)free(child);
                struct tree_node* child = minimax(child_board,depth-1,true,alpha,beta,false);
                
                //minEval = min(minEval,child->evaluation);
                if(child!=NULL && minEval>child->evaluation)
                {
                    if(best_child!=NULL)free(best_child);
                    minEval = child->evaluation;
                    if(is_root_call) best_child = copy_board(child_board);
                }
                if(child!=NULL)beta = min(beta,child->evaluation);
                if(beta<=alpha)
                {
                    break;
                }
            }
            p = p->next;
        }
        
        //After the branches are complete, we no longer need the linked list of all the movable peices so we free them

        if(red_movable_peices!=NULL)delete_linked_list(red_movable_peices);
        struct tree_node* node = (struct tree_node*)malloc(sizeof(struct tree_node));
        if(best_child!=NULL)node->data = copy_board(best_child);
        node->evaluation = minEval;

        if(child != NULL)free(child);
        if(child_board!=NULL)free(child_board);
        //if(best_child!=NULL)free(best_child);

        return node;
    }

    if(output_print)
    {
        fprintf(output_file,"Outside the minimax function\n");
        fprintf(output_file,"\n");
    }
}

/*This function is for taking the input from the user*/
struct peice* input(struct peice* board_dash)
{
    char move_or_rotate;
    do{
        char peice_type;
        int orient;
        int present_positon;
        int direction;
        int sense;
        //printf("\033[1;31mIf you are not seeing this message not the first time, you may have mistyped in previous attempt.\033[0m");
        printf("So do you want to rotate (r) or move (m) the peice? ");
        scanf(" %c",&move_or_rotate);
        if(move_or_rotate == 'm')
        {
            do
            {
                //printf("\033[1;31mIf you are not seeing this message not the first time, you may have mistyped in previous attempt.\033[0m");
                printf("What type of peice do you want to move?\nMirror (m) | Deflector (d) | Sheild (s) | King (k)? ");
                scanf(" %c",&peice_type);
                printf("Where is it on the board? ");
                scanf("%d",&present_positon);
                printf("Which direction do you want to take the peice? ");
                scanf("%d",&direction);
            } while (!Is_move_possible(board_dash,peice_type,present_positon,direction));

            move_the_peice(board_dash,peice_type,present_positon,direction);
        }
        else if(move_or_rotate == 'r')
        {
            do
            {
                //printf("\033[1;31mIf you are not seeing this message not the first time, you may have mistyped in previous attempt.\033[0m");
                printf("What type of peice do you want to rotate?\nMirror (m) | Deflector (d) | Sheild (s) | King (k) ");
                scanf(" %c",&peice_type);
                printf("Where is it on the board? ");
                scanf("%d",&present_positon);
                printf("In what sense? ");
                scanf("%d",&sense);
            } while (!Is_orientation_possibe(board_dash,peice_type,present_positon));

            orient_peice(board_dash,peice_type,present_positon,sense);
        }
    } while(!(move_or_rotate == 'm' || move_or_rotate == 'r'));
    return board_dash;
}

//This function will check if there is blue or red king on the board
bool Is_king_present(struct peice* board_dash)
{
    int count_blue_king = 0;
    int count_red_king = 0;
    for(int i=1;i<81;i++)
    {
        if(board_dash[i].peice_type == 'k' && board_dash[i].peice_color == 'b')
        {
            count_blue_king++;
        }
        else if (board_dash[i].peice_type == 'k' && board_dash[i].peice_color == 'r')
        {
            count_red_king++;
        }
    }
    if(count_blue_king + count_red_king == 2)return true;
    else if(count_blue_king == 1 && count_red_king == 0)
    {
        printf("Blue has won the game!\n");
        return false;
    }
    else if(count_red_king == 1 && count_blue_king == 0)
    {
        printf("Red has won the game!\n");
        return false;
    }
    return false;
}

//This function will take the the encoded array amd will give prepare the board for the minimax algorithm
peice* decode(int* array,peice* board){
    for(int i=0;i<320;){
        //First I will set the postion of the baord that we are talking about
        int board_position = array[i];
        i++;

        //Color Checking
        char color;
        char type;

        //Checking the color
        if(array[i] == 0){color = 'n';i++;}//Empty Cell (No Color)
        else if(array[i] == 1){color = 'r';i++;} //Red color
        else if(array[i] == 2){color = 'b';i++;} //Blue color

        //Checking the piece type
        if(array[i] == 1){type = 'm';i++;} //Mirror
        else if(array[i] == 2){type = 'd';i++;} //Defelctor
        else if(array[i] == 3){type = 's';i++;} //Sheild
        else if(array[i] == 4){type = 'k';i++;} //King
        else if(array[i] == 5){type = 'l';i++;} //Laser
        else if(array[i] == 0){type = 'n';i++;} // Nothing


        assign(board,board_position,color,type,array[i]);
        i++;
    }
    return board;
}

//This function wil tkae in the board, and will create the encoded array out of it
int* encode(peice* board,int* array ){
    int array_index = 0;
    for(int position = 1; position<81; position++ ){
        //First checking the position of the board
        array[array_index] = position;
        array_index++;

        //Now we will add the color
        if(board[position].peice_color == 'r'){array[array_index] = 1;}
        else if(board[position].peice_color == 'b'){array[array_index] = 2;}
        else if(board[position].peice_color == 'n'){array[array_index] = 0;}
        array_index++;

        //Now we will check for the piece type
        if(board[position].peice_type == 'm'){array[array_index] = 1;}
        else if(board[position].peice_type == 's'){array[array_index] = 3;}
        else if(board[position].peice_type == 'd'){array[array_index] = 2;}
        else if(board[position].peice_type == 'k'){array[array_index] = 4;}
        else if(board[position].peice_type == 'l'){array[array_index] = 5;}
        else if(board[position].peice_type == 'n'){array[array_index] = 0;}
        array_index++;

        //Now I wil check for the orientation
        array[array_index] = board[position].orientation;
        array_index++;
    }
    return array;
}

int main(int argc, char* argv[])
{
    if (argc < 322) {
        printf("No input detected\n");
        return 1;
    }

    struct peice* board = (struct peice*)malloc(sizeof(struct peice) * 81);

    struct tree_node* best_move;

    int depth = atoi(argv[1]);

    int encoded_array[320];
    int decoded_array[320];

    for (int i = 0; i < 320; i++) {
        encoded_array[i] = atoi(argv[i + 2]);
    }

    board = decode(encoded_array, board);


    best_move = minimax(board, depth, false, -10000, 10000, true);
    board = best_move->data;

    encode(board, decoded_array);

    for (int i = 0; i < 320; i++) {
        printf("%d ", decoded_array[i]);
    }
    return 0;
}