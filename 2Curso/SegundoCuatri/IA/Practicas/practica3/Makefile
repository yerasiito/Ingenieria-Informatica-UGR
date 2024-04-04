all: dirs bin/Parchis

obj/main.o: src/main.cpp
	g++ -O2 -g -c src/main.cpp -o obj/main.o -I include/ -std=c++14

obj/ParchisGUI.o: src/ParchisGUI.cpp include/ParchisGUI.h
	g++ -O2 -g -c src/ParchisGUI.cpp -o obj/ParchisGUI.o -I include/ -std=c++14

obj/Parchis.o: src/Parchis.cpp include/Parchis.h
	g++ -O2 -g -c src/Parchis.cpp -o obj/Parchis.o -I include/ -std=c++14

obj/Board.o: src/Board.cpp include/Board.h
	g++ -O2 -g -c src/Board.cpp -o obj/Board.o -I include/ -std=c++14

obj/Dice.o: src/Dice.cpp include/Dice.h
	g++ -O2 -g -c src/Dice.cpp -o obj/Dice.o -I include/ -std=c++14

obj/ClickableSprite.o: src/ClickableSprite.cpp include/ClickableSprite.h
	g++ -O2 -g -c src/ClickableSprite.cpp -o obj/ClickableSprite.o -I include/ -std=c++14

obj/BoardSprite.o: src/BoardSprite.cpp include/BoardSprite.h
	g++ -O2 -g -c src/BoardSprite.cpp -o obj/BoardSprite.o -I include/ -std=c++14

obj/DiceSprite.o: src/DiceSprite.cpp include/DiceSprite.h
	g++ -O2 -g -c src/DiceSprite.cpp -o obj/DiceSprite.o -I include/ -std=c++14

obj/PieceSprite.o: src/PieceSprite.cpp include/PieceSprite.h
	g++ -O2 -g -c src/PieceSprite.cpp -o obj/PieceSprite.o -I include/ -std=c++14

obj/Player.o: src/Player.cpp include/Player.h
	g++ -O2 -g -c src/Player.cpp -o obj/Player.o -I include/ -std=c++14

obj/AIPlayer.o: src/AIPlayer.cpp include/AIPlayer.h
	g++ -O2 -g -c src/AIPlayer.cpp -o obj/AIPlayer.o -I include/ -std=c++14

obj/Ninja.o: src/Ninja.cpp include/Ninja.h
	g++ -O2 -g -c src/Ninja.cpp -o obj/Ninja.o -I include/ -std=c++14

obj/GUIPlayer.o: src/GUIPlayer.cpp include/GUIPlayer.h
	g++ -O2 -g -c src/GUIPlayer.cpp -o obj/GUIPlayer.o -I include/ -std=c++14

obj/RemotePlayer.o: src/RemotePlayer.cpp include/RemotePlayer.h
	g++ -O2 -g -c src/RemotePlayer.cpp -o obj/RemotePlayer.o -I include/ -std=c++14

obj/SpriteAnimator.o: src/SpriteAnimator.cpp include/SpriteAnimator.h
	g++ -O2 -g -c src/SpriteAnimator.cpp -o obj/SpriteAnimator.o -I include/ -std=c++14

obj/Button.o: src/Button.cpp include/Button.h
	g++ -O2 -g -c src/Button.cpp -o obj/Button.o -I include/ -std=c++14

obj/Connection.o: src/Connection.cpp include/Connection.h
	g++ -O2 -g -c src/Connection.cpp -o obj/Connection.o -I include/ -std=c++14

obj/GameSelector.o: src/GameSelector.cpp include/GameSelector.h
	g++ -O2 -g -c src/GameSelector.cpp -o obj/GameSelector.o -I include/ -std=c++14

bin/Parchis: obj/main.o obj/ParchisGUI.o obj/Parchis.o obj/Board.o obj/Dice.o obj/SpriteAnimator.o obj/DiceSprite.o obj/PieceSprite.o obj/BoardSprite.o obj/Button.o obj/ClickableSprite.o obj/RemotePlayer.o obj/GUIPlayer.o obj/Ninja.o obj/AIPlayer.o obj/Player.o obj/Connection.o obj/GameSelector.o
	g++ -O2 -g obj/main.o obj/ParchisGUI.o obj/Parchis.o obj/Board.o obj/Dice.o obj/DiceSprite.o obj/SpriteAnimator.o obj/PieceSprite.o obj/BoardSprite.o obj/Button.o obj/ClickableSprite.o obj/RemotePlayer.o obj/GUIPlayer.o obj/Ninja.o obj/AIPlayer.o obj/Player.o obj/Connection.o obj/GameSelector.o -o bin/Parchis -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lsfml-network -lpthread

clean:
	rm -rf ./obj/*.o ./bin/*

dirs: 
	mkdir -p obj
	mkdir -p bin

.PHONY: clean dirs