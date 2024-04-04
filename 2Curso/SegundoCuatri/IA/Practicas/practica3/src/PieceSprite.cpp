# include "PieceSprite.h"
# include "ParchisGUI.h"

const map<color, vector<int>> PieceSprite::col2textrec = {
    {yellow, {0, 0, 30, 30}},
    {blue, {0, 30, 30, 30}},
    {red, {30, 30, 30, 30}},
    {green, {30, 0, 30, 30}},
};

const map<color, vector<int>> PieceSprite::col2selectedrec = {
    {yellow, {0, 60, 30, 30}},
    {blue, {0, 90, 30, 30}},
    {red, {30, 90, 30, 30}},
    {green, {30, 60, 30, 30}},
};

PieceSprite::PieceSprite(const Texture & t, int id, color c) : ClickableSprite(t){
    this->id = id;
    this->c = c;
    this->setTextureRect(IntRect(col2textrec.at(c).at(0), col2textrec.at(c).at(1), col2textrec.at(c).at(2), col2textrec.at(c).at(3)));
}


void PieceSprite::onClickAction(Window & container){

    ParchisGUI * gui = dynamic_cast<ParchisGUI*>(&container);

    if(enabled && !locked && clicked){
        GUIPlayer * player = static_cast<GUIPlayer*>(&gui->model->getCurrentPlayer());
        player->setNextMove(this->getModelColor(), this->id, gui->last_dice);
        player->confirmNextMove();
        //gui->last_dice = -1;

        /*
        Box origin = gui->model->getBoard().getPiece(this->getModelColor(), this->id);

        gui->model->movePiece(this->getModelColor(), this->id,  gui->last_dice);

        cout << "Jugador actual: " << gui->model->getCurrentPlayerId() << endl;
        cout << "Color actual: " << str(gui->model->getCurrentColor()) << endl;

        vector<tuple<color, int, Box, Box>> last_moves = gui->model->getLastMoves();


        for (int i = 0; i < last_moves.size(); i++){
            color col = get<0>(last_moves[i]);
            int id = get<1>(last_moves[i]);
            Box origin = get<2>(last_moves[i]);
            Box dest = get<3>(last_moves[i]);

            gui->queueMove(col, id, origin, dest);
        }

        gui->startGameLoop();
        */
    }
    else if(clicked && (locked || !enabled)){
        gui->playForbiddenSound();
    }
    
    
}

void PieceSprite::onEnableAction(Window & container){
    if(enabled)
        this->setColor(Color::White); // Color completo si enabled
    else
        this->setColor(Color(128, 128, 128));  // Oscurecido si disabled.
}

void PieceSprite::onSelectionAction(Window & container){}

void PieceSprite::onLockAction(Window & container){}

void PieceSprite::onHoverAction(Window & container){
    if(hovered){
        ParchisGUI *gui = dynamic_cast<ParchisGUI *>(&container);
        if (locked || !enabled){
            gui->setForbiddenCursor();
        }
        else{
            this->setTextureRect(IntRect(col2selectedrec.at(c).at(0), col2selectedrec.at(c).at(1), col2selectedrec.at(c).at(2), col2selectedrec.at(c).at(3)));
            gui->setHandCursor();
        }
    }
    else{
        this->setTextureRect(IntRect(col2textrec.at(c).at(0), col2textrec.at(c).at(1), col2textrec.at(c).at(2), col2textrec.at(c).at(3)));
    }
}