#include<iostream>
#include<vector>
#include<string>

#include"Tokenize.h"
#include"minesweeper.h"

int main(int argc,char** argv){
	std::string command;
	std::vector<std::string> com;
	Minesweeper* mine = nullptr;

	while(command!="exit"){
		std::cout << "~Minesweeper$ ";
		std::getline(std::cin,command);
		if(command=="exit" || command=="quit"){
			std::cout << "goodbye" << std::endl;
			return 0;
		}

		com = Tokenize::tokenize(command);
		if(com.size()==3){
			if((com.at(0)=="uncover" || com.at(0)=="u") && com.at(1)!="all"){//uncover w h
				if(Tokenize::contains(com.at(1),'-') && Tokenize::contains(com.at(2),'-')){//if using ranges
					std::vector<std::string> rw = Tokenize::tokenize(com.at(1),"-");
					std::vector<std::string> rh = Tokenize::tokenize(com.at(2),"-");
					for(int w=std::stoi(rw.at(0));w<=std::stoi(rw.at(1));w++){
						for(int h=std::stoi(rh.at(0));h<=std::stoi(rh.at(1));h++){
							std::cout << mine->uncover(w,h) << std::endl;
						}
					}
				}else if(Tokenize::contains(com.at(1),'-')){//if using w range
					std::vector<std::string> rw = Tokenize::tokenize(com.at(1),"-");
					for(int w=std::stoi(rw.at(0));w<=std::stoi(rw.at(1));w++){
						std::cout << mine->uncover(w,std::stoi(com.at(2))) << std::endl;
					}
				}else if(Tokenize::contains(com.at(2),'-')){//if using h range
					std::vector<std::string> rh = Tokenize::tokenize(com.at(2),"-");
					for(int h=std::stoi(rh.at(0));h<=std::stoi(rh.at(1));h++){
						std::cout << mine->uncover(std::stoi(com.at(1)),h) << std::endl;
					}
				}else{
					std::cout << mine->uncover(std::stoi(com.at(1)),std::stoi(com.at(2))) << std::endl;
				}
			}else if(com.at(0)=="flag" || com.at(0)=="f"){//flag w h
				if(Tokenize::contains(com.at(1),'-') && Tokenize::contains(com.at(2),'-')){//if using ranges
					std::vector<std::string> rw = Tokenize::tokenize(com.at(1),"-");
					std::vector<std::string> rh = Tokenize::tokenize(com.at(2),"-");
					for(int w=std::stoi(rw.at(0));w<=std::stoi(rw.at(1));w++){
						for(int h=std::stoi(rh.at(0));h<=std::stoi(rh.at(1));h++){
							std::cout << mine->flag(w,h) << std::endl;
						}
					}
				}else if(Tokenize::contains(com.at(1),'-')){//if using w range
					std::vector<std::string> rw = Tokenize::tokenize(com.at(1),"-");
					for(int w=std::stoi(rw.at(0));w<=std::stoi(rw.at(1));w++){
						std::cout << mine->flag(w,std::stoi(com.at(2))) << std::endl;
					}
				}else if(Tokenize::contains(com.at(2),'-')){//if using h range
					std::vector<std::string> rh = Tokenize::tokenize(com.at(2),"-");
					for(int h=std::stoi(rh.at(0));h<=std::stoi(rh.at(1));h++){
						std::cout << mine->flag(std::stoi(com.at(1)),h) << std::endl;
					}
				}else{
					std::cout << mine->flag(std::stoi(com.at(1)),std::stoi(com.at(2))) << std::endl;
				}
			}else if((com.at(0)=="uncover" || com.at(0)=="u") && com.at(1)=="all"){
				if(com.at(2)=="false" || com.at(2)=="f"){
					mine->uncover_all(false);
				}else if(com.at(2)=="true" || com.at(2)=="t"){
					mine->uncover_all(true);
				}
			}
		}else if(com.size()==2){
			if(com.at(0)=="new"||com.at(0)=="start"||com.at(0)=="reset"){
				if(mine!=nullptr){
					delete mine;
				}
				mine = new Minesweeper(com.at(1));
			}else if(com.at(0)=="uncover"||com.at(0)=="uncover_all"||com.at(0)=="uncoverall"||com.at(0)=="view"){
				if(com.at(1)=="all"||com.at(1)=="board"){
					mine->uncover_all();
				}else if(com.at(1)=="false" || com.at(1)=="f"){
					mine->uncover_all(false);
				}else if(com.at(1)=="true" || com.at(1)=="t"){
					mine->uncover_all(true);
				}
			}
		}else if(com.size()==4){
			if(com.at(0)=="new"||com.at(0)=="start"||com.at(0)=="reset"){
				if(mine!=nullptr){
					delete mine;
				}
				mine = new Minesweeper(std::stoi(com.at(1)),std::stoi(com.at(2)),stof(com.at(3)));
			}
		}else if(com.size()==1){
			if(com.at(0)=="uncoverall"||com.at(0)=="uncover_all"||com.at(0)=="viewboard"){
				mine->uncover_all();
			}else if(com.at(0)=="help"){
				std::cout << "start a new game               ~$ new <easy|medium|hard>" << std::endl;
				std::cout << "start a new custom game        ~$ new (width[1,99]) (height[1,99]) (bomb chance[0,1]) " << std::endl;
				std::cout << "uncover a tile                 ~$ uncover (x cord) (y cord)" << std::endl;
				std::cout << "flag a tile                    ~$ flag (x cord[0,width]) (y cord[0,height])" << std::endl;
				std::cout << "the flag and uncover commands can take a range of values instead:" << std::endl; 
				std::cout << "Example                        ~$ u 1-3 10-22" << std::endl;
				continue;
			}
		}else{
			std::cout << "unrecognized command" << std::endl;
		}
		if(mine!=nullptr){
			mine->print();
		}
	}
}//end main
