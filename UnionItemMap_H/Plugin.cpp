// This file added in headers queue
// File: "Sources.h"

namespace GOTHIC_ENGINE {

	// TO DO
	// Your code ...

	void Game_Entry() {
		iMap = new ItemMap();
	}

	void Game_Init() {
		if ( iMap ) 
			iMap->Init();
	}

	void Game_Exit() {
	}

	void Game_Loop() {
		if ( iMap )
			iMap->Loop();
	}

	void Game_SaveBegin() {
	}

	void Game_SaveEnd() {
	}

	void LoadBegin() {
	}

	void LoadEnd() {
	}

	void Game_LoadBegin_NewGame() {
		LoadBegin();
	}

	void Game_LoadEnd_NewGame() {
		LoadEnd();
	}

	void Game_LoadBegin_SaveGame() {
		LoadBegin();
	}

	void Game_LoadEnd_SaveGame() {
		LoadEnd();
	}

	void Game_LoadBegin_ChangeLevel() {
		LoadBegin();
	}

	void Game_LoadEnd_ChangeLevel() {
		LoadEnd();
	}

	void Game_LoadBegin_Trigger() {
	}

	void Game_LoadEnd_Trigger() {
	}

	void Game_Pause() {
	}

	void Game_Unpause() {
	}

	void Game_DefineExternals() {

	}

	// A multiplatform application reference.
	// please disable unused functions.
	// write 'false' in 'Enabled' macro.
#define AppDefault True
	CApplication* lpApplication = !CHECK_THIS_ENGINE?Null:CApplication::CreateRefApplication(
		Enabled( FALSE ) Game_Entry,
		Enabled( AppDefault ) Game_Init,
		Enabled( FALSE ) Game_Exit,
		Enabled( AppDefault ) Game_Loop,
		Enabled( FALSE ) Game_SaveBegin,
		Enabled( FALSE ) Game_SaveEnd,
		Enabled( FALSE ) Game_LoadBegin_NewGame,
		Enabled( FALSE ) Game_LoadEnd_NewGame,
		Enabled( FALSE ) Game_LoadBegin_SaveGame,
		Enabled( FALSE ) Game_LoadEnd_SaveGame,
		Enabled( FALSE ) Game_LoadBegin_ChangeLevel,
		Enabled( FALSE ) Game_LoadEnd_ChangeLevel,
		Enabled( FALSE ) Game_LoadBegin_Trigger,
		Enabled( FALSE ) Game_LoadEnd_Trigger,
		Enabled( FALSE ) Game_Pause,
		Enabled( FALSE ) Game_Unpause,
		Enabled( FALSE ) Game_DefineExternals
	);
}