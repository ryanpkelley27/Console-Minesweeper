#ifndef minesweeper_h_Grey_8_26_2022
#define minesweeper_h_Grey_8_26_2022

#include<vector>
#include<string>
#include<iostream>
#include<ctime>
#include<cassert>
#include<cmath>
#include<cstdlib>
#include<time.h>

class Tile{
	public:
		bool covered;
		int value;
		bool flagged;
		int x;
		int y;
		Tile(int x=0,int y=0,int v=0,bool c=true,bool f=false){
			this->covered = c;
			this->value=v;
			this->flagged=f;
			this->x = x;//x cord
			this->y = y;//y cord
		}
};

class Minesweeper{
	private:
		std::vector<std::vector<Tile*>> board;
		int width;
		int height;

		float chance;
		int num_bombs;
		int bombs_left;
		bool populated;
		std::string difficulty;

		std::clock_t time;


		bool setup(){
			//std::cout << "setup" << std::endl;
			//create empty board
			srand(std::time(0));
			for(int w=0;w<width;w++){
				board.push_back({});//insert blank column
				for(int h=0;h<height;h++){
					board[w].push_back(new Tile(w,h));
				}
			}
			return true;
		}
		bool pop_bombs(int fw, int fh){
			//populate bombs
			int first_uncover_buffer = 1;
			int count = 0;
			for(int w=0;w<width;w++){
				for(int h=0;h<height;h++){
					if(static_cast<float> (rand())/static_cast<float>(RAND_MAX) < chance){//plant bomb
						if(w>fw+first_uncover_buffer || w<fw-first_uncover_buffer || h>fh+first_uncover_buffer || h<fh-first_uncover_buffer){//if not near first uncover
							count+=1;
							board[w][h]->value=-1;
						}
					}
				}
			}
			num_bombs = count;
			bombs_left = count;
			//calulate tile values
			for(int w=0;w<width;w++){
				for(int h=0;h<height;h++){
					if(board[w][h]->value>=0){
						count = 0;
						if(w-1>=0 && h-1>=0 && board[w-1][h-1]->value<0){
							count+=1;
						}
						if(h-1>=0 && board[w][h-1]->value<0){
							count+=1;
						}
						if(w+1<width && h-1>=0 && board[w+1][h-1]->value<0){
							count+=1;
						}
						if(w-1>=0 && board[w-1][h]->value<0){
							count+=1;
						}
						if(w+1<width && board[w+1][h]->value<0){
							count+=1;
						}
						if(w-1>=0 && h+1<height && board[w-1][h+1]->value<0){
							count+=1;
						}
						if(h+1<height && board[w][h+1]->value<0){
							count+=1;
						}
						if(w+1<width && h+1<height && board[w+1][h+1]->value<0){
							count+=1;
						}
						board[w][h]->value=count;//count;
					}
				}
			}
			return true;
		}//end pop_bombs()
		void init(int w,int h,float c){
			width = w;
			height = h;
			chance = c;
			num_bombs=0;
			bombs_left=0;
			populated = false;
			setup();
		}
	public:
		Minesweeper(std::string d="hard"){
			//std::cout << "construct" << std::endl;
			difficulty = d;
			if(difficulty=="easy"){//easy
				init(9,9,0.1);
			}else if(difficulty=="medium"){//medium
				init(16,16,0.15);
			}else{//hard
				init(30,16,0.2);
			}
		}
		Minesweeper(int w, int h=16, float c=0.2){//custom size
			difficulty = "custom";
			init(w,h,c);
		}
		~Minesweeper(){
			for(int w=0;w<width;w++){
				for(int h=0;h<height;h++){
					delete board[w][h];
				}
			}
		}
		void print(){//prints board
			int digits = 0;
			std::cout << " Total Number of Bombs: " << num_bombs << "   Bombs left: " << bombs_left << std::endl;
			std::cout << " ";
			for(int w = 0;w<width;w++){
				if(w!=0){
					digits = std::ceil( std::log10(w+1) );//how many digits
				}else{
					digits=1;
				}
				std::cout << " ";
				for(int i=0;i<std::ceil((3.0-digits)/2);i++){
					std::cout << " ";
				}
				std::cout << w;//w;
				//std::cout <<" "<< digits<<" ";
				for(int i=0;i<std::floor((3.0-digits)/2);i++){
					std::cout << " ";
				}
			}
			std::cout << std::endl;

			std::cout << " ";
			if(board[0][0]->covered && board[0][0]->flagged){//top left corner
				std::cout << "\033[38;5;0m\033[48;5;8m-\033[0m";
			}else if(board[0][0]->covered && board[0][0]->flagged==false){
				std::cout << "\033[38;5;0m\033[48;5;255m-\033[0m";
			}else if(board[0][0]->value<0){
				std::cout << "\033[38;5;15m\033[48;5;0m-\033[0m";
			}else{
				std::cout << "\033[38;5;0m\033[48;5;7m-\033[0m";
			}
			for(int w=0;w<width;w++){
				for(int i=0;i<4;i++){//top row of -
					if(board[w][0]->covered && board[w][0]->flagged){
						std::cout << "\033[38;5;0m\033[48;5;8m-\033[0m";
					}else if(board[w][0]->covered && board[w][0]->flagged==false){
						std::cout << "\033[38;5;0m\033[48;5;255m-\033[0m";
					}else if(board[w][0]->value<0){
						std::cout << "\033[38;5;15m\033[48;5;0m-\033[0m";
					}else{
						std::cout << "\033[38;5;0m\033[48;5;7m-\033[0m";
					}
				}
			}
			std::cout << std::endl;

			for(int h = 0;h<height;h++){
				if(board[0][h]->covered && board[0][h]->flagged==false){
					std::cout << " \033[38;5;0m\033[48;5;255m"<<"|"<<"\033[0m";//start of every row
				}else if(board[0][h]->covered && board[0][h]->flagged){
					std::cout << " \033[38;5;0m\033[48;5;8m"<<"|"<<"\033[0m";
				}else if(board[0][h]->value<0){
					std::cout << " \033[38;5;15m\033[48;5;0m"<<"|"<<"\033[0m";
				}else{
					std::cout << " \033[38;5;0m\033[48;5;7m"<<"|"<<"\033[0m";
				}

				for(int w=0;w<width;w++){
					if(board[w][h]->covered){
						if(board[w][h]->flagged){
							std::cout << "\033[38;5;0m\033[48;5;8m" << " F " << "\033[0m";
							std::cout << "\033[38;5;0m\033[48;5;8m|\033[0m";
						}else{
							std::cout << "\033[48;5;255m" << "   " << "\033[0m";
							std::cout << "\033[38;5;0m\033[48;5;255m|\033[0m";
						}
					}else{//is not covered
						if(board[w][h]->value==0){
							std::cout << "\033[48;5;7m   \033[0m";
							std::cout << "\033[38;5;0m\033[48;5;7m|\033[0m";
						}else if(board[w][h]->value<0){
							std::cout << "\033[38;5;15m" << " B " << "\033[0m";
							std::cout << "\033[38;5;15m|\033[0m";
						}else{
							switch(board[w][h]->value){
								//std::cout << "\033[48;5;7m";
								case 1://color code 12
									std::cout << "\033[38;5;12m\033[48;5;7m" << " " << board[w][h]->value << " " << "\033[0m";
									std::cout << "\033[38;5;0m\033[48;5;7m|\033[0m";
									break;
								case 2://color code 2
									std::cout << "\033[38;5;2m\033[48;5;7m" << " " << board[w][h]->value << " " << "\033[0m";
									std::cout << "\033[38;5;0m\033[48;5;7m|\033[0m";
									break;
								case 3://color code 9
									std::cout << "\033[38;5;9m\033[48;5;7m" << " " << board[w][h]->value << " " << "\033[0m";
									std::cout << "\033[38;5;0m\033[48;5;7m|\033[0m";
									break;
								case 4://color code 4
									std::cout << "\033[38;5;4m\033[48;5;7m" << " " << board[w][h]->value << " " << "\033[0m";
									std::cout << "\033[38;5;0m\033[48;5;7m|\033[0m";
									break;
								case 5://color code 1
									std::cout << "\033[38;5;1m\033[48;5;7m" << " " << board[w][h]->value << " " << "\033[0m";
									std::cout << "\033[38;5;0m\033[48;5;7m|\033[0m";
									break;
								case 6://color code 6
									std::cout << "\033[38;5;6m\033[48;5;7m" << " " << board[w][h]->value << " " << "\033[0m";
									std::cout << "\033[38;5;0m\033[48;5;7m|\033[0m";
									break;
								case 7://color code 0
									std::cout << "\033[38;5;0m\033[48;5;7m" << " " << board[w][h]->value << " " << "\033[0m";
									std::cout << "\033[38;5;0m\033[48;5;7m|\033[0m";
									break;
								case 8://color code 8
									std::cout << "\033[38;5;8m\033[48;5;7m" << " " << board[w][h]->value << " " << "\033[0m";
									std::cout << "\033[38;5;0m\033[48;5;7m|\033[0m";
									break;
								default:
									std::cout << board[w][h]->value;
									std::cout << "\033[38;5;0m\033[48;5;7m|\033[0m";
									break;
							}
						}
					}
				}
				std::cout << " " << h;//end of every tile row
				std::cout << std::endl;
				std::cout << " ";
				if(board[0][h]->covered && board[0][h]->flagged==false){
					std::cout << "\033[38;5;0m\033[48;5;255m"<<"-"<<"\033[0m";//start of every - row
				}else if(board[0][h]->covered && board[0][h]->flagged){
					std::cout << "\033[38;5;0m\033[48;5;8m"<<"-"<<"\033[0m";
				}else if(board[0][h]->value<0){
					std::cout << "\033[38;5;15m\033[48;5;0m"<<"-"<<"\033[0m";
				}else{
					std::cout << "\033[38;5;0m\033[48;5;7m"<<"-"<<"\033[0m";
				}
				for(int w=0;w<width;w++){
					for(int i=0;i<4;i++){
						if(board[w][h]->covered && board[w][h]->flagged==false){
							std::cout << "\033[38;5;0m\033[48;5;255m"<<"-"<<"\033[0m";//start of every - row
						}else if(board[w][h]->covered && board[w][h]->flagged){
							std::cout << "\033[38;5;0m\033[48;5;8m"<<"-"<<"\033[0m";
						}else if(board[w][h]->value<0){
							std::cout << "\033[38;5;15m\033[48;5;0m"<<"-"<<"\033[0m";
						}else{
							std::cout << "\033[38;5;0m\033[48;5;7m"<<"-"<<"\033[0m";
						}
					}
				}
				std::cout << std::endl;
			}
		}

		std::string flag(int w,int h){//place/remove flag on w,h
			if(board[w][h]->covered==false){return "\033[38;5;11mCould not flag tile because tile is uncovered\033[0m";}
			if(board[w][h]->flagged){
				board[w][h]->flagged=false;
			}else{
				board[w][h]->flagged=true;
			}

			return update_bombs_left();;
		}
		std::string uncover(int w, int h){//uncover w,h
			if(board[w][h]->flagged){
				return "\033[38;5;11mCould not uncover tile because tile is flagged\033[0m";
			}else{
				if(!populated){//first uncover
					populated = true;
					pop_bombs(w,h);
				}
				board[w][h]->covered=false;
				if(board[w][h]->value<0){
					return "\033[38;5;11mYou have uncovered a bomb! You lose!\033[0m";
					update_bombs_left();
				}
			}
			//clear larger areas with value==0
			if(board[w][h]->value==0){
				clear(w,h);
			}
			return update_bombs_left();
		}
		void clear(int w, int h){
			board[w][h]->covered=false;
			if(w-1>=0 && h-1>=0 && board[w-1][h-1]->covered){
				board[w-1][h-1]->covered=false;
				if(board[w-1][h-1]->value==0){
					clear(w-1,h-1);
				}
			}
			if(h-1>=0 && board[w][h-1]->covered){
				board[w][h-1]->covered=false;
				if(board[w][h-1]->value==0){
					clear(w,h-1);
				}
			}
			if(w+1<width && h-1>=0 && board[w+1][h-1]->covered){
				board[w+1][h-1]->covered=false;
				if(board[w+1][h-1]->value==0){
					clear(w+1,h-1);
				}
			}
			if(w-1>=0 && board[w-1][h]->covered){
				board[w-1][h]->covered=false;
				if(board[w-1][h]->value==0){
					clear(w-1,h);
				}
			}
			if(w+1<width && board[w+1][h]->covered){
				board[w+1][h]->covered=false;
				if(board[w+1][h]->value==0){
					clear(w+1,h);
				}
			}

			if(w-1>=0 && h+1<height && board[w-1][h+1]->covered){
				board[w-1][h+1]->covered=false;
				if(board[w-1][h+1]->value==0){
					clear(w-1,h+1);
				}
			}
			if(h+1<height && board[w][h+1]->covered){
				board[w][h+1]->covered=false;
				if(board[w][h+1]->value==0){
					clear(w,h+1);
				}
			}
			if(w+1<width && h+1<height && board[w+1][h+1]->covered){
				board[w+1][h+1]->covered=false;
				if(board[w+1][h+1]->value==0){
					clear(w+1,h+1);
				}
			}
		}
		void uncover_all(bool ignore_flags=true){//debug uncover all tiles
			for(int w=0;w<width;w++){
				for(int h=0;h<height;h++){
					if(board[w][h]->flagged==false || ignore_flags){
						board[w][h]->covered=false;
					}
				}
			}
			//return true;
		}
		std::string update_bombs_left(){//return bombs left and updates variable = total-flags-uncovered bombs
			int count_bl = 0;
			bool won = true;
			for(int w = 0;w<width;w++){
				for(int h = 0;h<height;h++){
					if(board[w][h]->flagged){//count bombs left
						count_bl++;
					}else if(board[w][h]->covered==false && board[w][h]->value<0){
						count_bl++;
					}

					if(board[w][h]->value>=0 && board[w][h]->covered){
						won=false;
					}
				}
			}

			bombs_left = num_bombs-count_bl;

			if(won){
				return "\033[38;5;11mYou have uncovered all of the safe tiles! You Win!\033[0m";
			}else{
				return "";
			}
		}
};

#endif
