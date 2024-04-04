# include "Board.h"

Board::Board(){
    this->setFromConfig(ALL_AT_HOME);
}
    

Board::Board (const map <color, vector <Box> > & b){
    this->pieces = map<color, vector<Box> >(b);
}

Board::Board(const BoardConfig & config){
    this->setFromConfig(config);
}

bool Board::operator==(const Board & board) const{
    return this->pieces == board.pieces;
}

const Box & Board::getPiece(const color c, const int idx) const{
    return pieces.at(c)[idx];
}

const vector<Box> & Board::getPieces(const color c) const{
    return pieces.at(c);
}

void Board::movePiece(const color c, const int idx, const Box & final_box){
    pieces[c][idx] = final_box;
}

void Board::setFromConfig(const BoardConfig & config){
    //Definimos las siguientes configuraciones especificando en qué casillas empiezan cada
    //una de las piezas.
    switch(config){
        case ALL_AT_HOME:
            this->pieces = map<color, vector<Box>>{
                {color::green, {{0, box_type::home, color::green}, {0, box_type::home, color::green}, {0, box_type::home, color::green}, {0, box_type::home, color::green}}},
                {color::red, {{0, box_type::home, color::red}, {0, box_type::home, color::red}, {0, box_type::home, color::red}, {0, box_type::home, color::red}}},
                {color::blue, {{0, box_type::home, color::blue}, {0, box_type::home, color::blue}, {0, box_type::home, color::blue}, {0, box_type::home, color::blue}}},
                {color::yellow, {{0, box_type::home, color::yellow}, {0, box_type::home, color::yellow}, {0, box_type::home, color::yellow}, {0, box_type::home, color::yellow}}}};
            break;

        case GROUPED:
            this->pieces = map<color, vector<Box>>{
                {color::green, {{0, box_type::home, color::green}, {55, box_type::normal, color::none}, {64, box_type::normal, color::none}, {68, box_type::normal, color::none}}},
                {color::red, {{0, box_type::home, color::red}, {38, box_type::normal, color::none}, {47, box_type::normal, color::none}, {51, box_type::normal, color::none}}},
                {color::blue, {{0, box_type::home, color::blue}, {21, box_type::normal, color::none}, {30, box_type::normal, color::none}, {34, box_type::normal, color::none}}},
                {color::yellow, {{0, box_type::home, color::yellow}, {4, box_type::normal, color::none}, {13, box_type::normal, color::none}, {17, box_type::normal, color::none}}}};
            break;

        case ALTERNED:
            this->pieces = map<color, vector<Box>>{
                {color::green, {{0, box_type::home, color::green}, {55, box_type::normal, color::none}, {13, box_type::normal, color::none}, {34, box_type::normal, color::none}}},
                {color::red, {{0, box_type::home, color::red}, {38, box_type::normal, color::none}, {64, box_type::normal, color::none}, {17, box_type::normal, color::none}}},
                {color::blue, {{0, box_type::home, color::blue}, {21, box_type::normal, color::none}, {47, box_type::normal, color::none}, {68, box_type::normal, color::none}}},
                {color::yellow, {{0, box_type::home, color::yellow}, {4, box_type::normal, color::none}, {30, box_type::normal, color::none}, {51, box_type::normal, color::none}}}};
            break;

        case ALMOST_GOAL:
            this->pieces = map<color, vector<Box>>{
                {color::green, {{51, box_type::normal, color::none}, {1, box_type::final_queue, color::green}, {2, box_type::final_queue, color::green}, {3, box_type::final_queue, color::green}}},
                {color::red, {{34, box_type::normal, color::none}, {1, box_type::final_queue, color::red}, {2, box_type::final_queue, color::red}, {3, box_type::final_queue, color::red}}},
                {color::blue, {{17, box_type::normal, color::none}, {1, box_type::final_queue, color::blue}, {2, box_type::final_queue, color::blue}, {3, box_type::final_queue, color::blue}}},
                {color::yellow, {{68, box_type::normal, color::none}, {1, box_type::final_queue, color::yellow}, {2, box_type::final_queue, color::yellow}, {3, box_type::final_queue, color::yellow}}}};
            break;
        case DEBUG:
            this->pieces = map<color, vector<Box>>{
                {color::green, {{56, box_type::normal, color::none}, {1, box_type::final_queue, color::green}, {2, box_type::final_queue, color::green}, {3, box_type::final_queue, color::green}}},
                {color::red, {{34, box_type::normal, color::none}, {1, box_type::final_queue, color::red}, {2, box_type::final_queue, color::red}, {3, box_type::final_queue, color::red}}},
                {color::blue, {{17, box_type::normal, color::none}, {1, box_type::final_queue, color::blue}, {2, box_type::final_queue, color::blue}, {3, box_type::final_queue, color::blue}}},
                {color::yellow, {{55, box_type::normal, color::none}, {1, box_type::final_queue, color::yellow}, {2, box_type::final_queue, color::yellow}, {3, box_type::final_queue, color::yellow}}}};
            break;
    }
}

