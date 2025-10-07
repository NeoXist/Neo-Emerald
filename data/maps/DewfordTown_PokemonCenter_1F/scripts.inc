DewfordIsle_PokemonCenter_1F_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, DewfordIsle_PokemonCenter_1F_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, CableClub_OnResume
	.byte 0

DewfordIsle_PokemonCenter_1F_OnTransition:
	setrespawn HEAL_LOCATION_DEWFORD_ISLE
	call Common_EventScript_UpdateBrineyLocation
	end

DewfordIsle_PokemonCenter_1F_EventScript_Nurse::
	setvar VAR_0x800B, LOCALID_DEWFORD_NURSE
	call Common_EventScript_PkmnCenterNurse
	waitmessage
	waitbuttonpress
	release
	end

DewfordIsle_PokemonCenter_1F_EventScript_PokefanF::
	msgbox DewfordIsle_PokemonCenter_1F_Text_StoneCavern, MSGBOX_NPC
	end

DewfordIsle_PokemonCenter_1F_EventScript_Man::
	msgbox DewfordIsle_PokemonCenter_1F_Text_FaintedMonCanUseHM, MSGBOX_NPC
	end

DewfordIsle_PokemonCenter_1F_Text_StoneCavern:
	.string "There's a stone cavern at the edge\n"
	.string "of town.\p"
	.string "I've heard you can find rare stones\n"
	.string "there.$"

DewfordIsle_PokemonCenter_1F_Text_FaintedMonCanUseHM:
	.string "Even if a POKéMON faints and can't\n"
	.string "battle, it can still use a move learned\l"
	.string "from a HIDDEN MACHINE (HM).$"

