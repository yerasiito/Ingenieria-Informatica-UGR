package tracks.singlePlayer;

import java.security.AlgorithmConstraints;
import java.util.Random;

import tools.Utils;
import tracks.ArcadeMachine;
import java.util.ArrayList;
import java.util.Arrays;

/**
 * Created with IntelliJ IDEA. User: Diego Date: 04/10/13 Time: 16:29 This is a
 * Java port from Tom Schaul's VGDL - https://github.com/schaul/py-vgdl
 */
public class Test {

    public static void main(String[] args) {

		// Available tracks:
		String sampleRandomController = "tracks.singlePlayer.simple.sampleRandom.Agent";
		String doNothingController = "tracks.singlePlayer.simple.doNothing.Agent";
		String sampleOneStepController = "tracks.singlePlayer.simple.sampleonesteplookahead.Agent";
		String sampleFlatMCTSController = "tracks.singlePlayer.simple.greedyTreeSearch.Agent";

		String sampleMCTSController = "tracks.singlePlayer.advanced.sampleMCTS.Agent";
        String sampleRSController = "tracks.singlePlayer.advanced.sampleRS.Agent";
        String sampleRHEAController = "tracks.singlePlayer.advanced.sampleRHEA.Agent";
		String sampleOLETSController = "tracks.singlePlayer.advanced.olets.Agent";
        String camelloAgente = "src_LOPEZ_RAMIREZ_YERAY.myAgent_Camel";
        String agenteDijkstra = "src_LOPEZ_RAMIREZ_YERAY.AgenteDijkstra";
        String agenteAStar = "src_LOPEZ_RAMIREZ_YERAY.AgenteAStar";
        String agenteRTAstar = "src_LOPEZ_RAMIREZ_YERAY.AgenteRTAStar";
        String agenteLRTAstar = "src_LOPEZ_RAMIREZ_YERAY.AgenteLRTAStar";
        String agenteCompeticion = "src_LOPEZ_RAMIREZ_YERAY.AgenteCompeticion";

		//Load available games
		String spGamesCollection =  "examples/all_games_sp.csv";
		String[][] games = Utils.readGames(spGamesCollection);

		//Game settings
		boolean visuals = true;
		int seed = new Random().nextInt();

		// Game and level to play
		int gameIdx = 58; //122 extendidos
		int levelIdx = 6; // level names from 0 to 4 (game_lvlN.txt).
		String gameName = games[gameIdx][1];
		String game = games[gameIdx][0];
		String level1 = game.replace(gameName, gameName + "_lvl" + levelIdx);
//		String level1 = game.replace(gameName, "labyrinthExtended_lvl6");
		
		String recordActionsFile = null;// "actions_" + games[gameIdx] + "_lvl"
						// + levelIdx + "_" + seed + ".txt";
						// where to record the actions
						// executed. null if not to save.

		// 1. This starts a game, in a level, played by a human.
//		ArcadeMachine.playOneGame(game, level1, recordActionsFile, seed);

		// 2. This plays a game in a level by the controller.
//		ArcadeMachine.runOneGame(game, level1, visuals, agenteLRTAstar, recordActionsFile, seed, 0);


		// 3. This replays a game from an action file previously recorded
	//	 String readActionsFile = recordActionsFile;
	//	 ArcadeMachine.replayGame(game, level1, visuals, readActionsFile);

		// 4. This plays a single game, in N levels, M times :
//		String level2 = new String(game).replace(gameName, gameName + "_lvl" + 1);
//		int M = 10;
//		for(int i=0; i<games.length; i++){
//			game = games[i][0];
//			gameName = games[i][1];
//			level1 = game.replace(gameName, gameName + "_lvl" + levelIdx);
//			ArcadeMachine.runGames(game, new String[]{level1}, M, sampleMCTSController, null);
//		}

		//5. This plays N games, in the first L levels, M times each. Actions to file optional (set saveActions to true).
		int N = 2, L = 3;
		String level;
		int gameIndex[] = new int[]{58,122};
		ArrayList<String> algorithms = new ArrayList<String>(Arrays.asList(agenteCompeticion));
		ArrayList<String> algorithmsNames = new ArrayList<String> (Arrays.asList("Dijkstra","A*", "RTA*", "LRTA*", "IDA*"));
		for(int j = 0; j < algorithms.size(); ++j) { // Ejecuta cada algoritmo
			System.out.println("\n-------------------------Algoritmo: " + algorithmsNames.get(j) + "-----------------------------");
			for(int i = 0; i < N; ++i) { // Ejecuta cada juego (normal y extendido)
//				if(i == 1 && j < 2)
//					break;
				
				game = games[gameIndex[i]][0];
				gameName = games[gameIndex[i]][1];
				System.out.println(gameName);
			
				for(int k = 0; k < L; ++k){ // Ejecuta cada nivel
					level = game.replace(gameName, gameName + "_lvl" + (k+6));
					System.out.println("\n################# JUEGO " + gameName + " - NIVEL " + (k+6) + " ####################");
					ArcadeMachine.runOneGame(game, level, true, algorithms.get(j), recordActionsFile, seed, 0);
				}
			}
		}
		//ArcadeMachine.runOneGame(game, level1, visuals, agenteLRTAstar, recordActionsFile, seed, 0);
		System.out.println("Acabo");
    }
}
