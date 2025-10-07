MossdeepIsle_House4_MapScripts::
	.byte 0

MossdeepIsle_House4_EventScript_Woman::
	lock
	faceplayer
	goto_if_set FLAG_SYS_GAME_CLEAR, MossdeepIsle_House4_EventScript_CanBattleAtSecretBases
	msgbox MossdeepIsle_House4_Text_BrotherLikesToFindBases, MSGBOX_DEFAULT
	release
	end

MossdeepIsle_House4_EventScript_CanBattleAtSecretBases::
	msgbox MossdeepIsle_House4_Text_BrotherLikesToVisitBasesAndBattle, MSGBOX_DEFAULT
	release
	end

MossdeepIsle_House4_EventScript_NinjaBoy::
	lock
	faceplayer
	special CheckPlayerHasSecretBase
	goto_if_eq VAR_RESULT, FALSE, MossdeepIsle_House4_EventScript_NoSecretBase
	special GetSecretBaseNearbyMapName
	msgbox MossdeepIsle_House4_Text_YouMadeSecretBaseNearX, MSGBOX_DEFAULT
	release
	end

MossdeepIsle_House4_EventScript_NoSecretBase::
	msgbox MossdeepIsle_House4_Text_MakeSecretBase, MSGBOX_DEFAULT
	release
	end

MossdeepIsle_House4_EventScript_Skitty::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_SKITTY, CRY_MODE_NORMAL
	msgbox MossdeepIsle_House4_Text_Skitty, MSGBOX_DEFAULT
	waitmoncry
	release
	end

MossdeepIsle_House4_Text_BrotherLikesToFindBases:
	.string "My little brother says he likes to go\n"
	.string "find people's SECRET BASES.$"

MossdeepIsle_House4_Text_BrotherLikesToVisitBasesAndBattle:
	.string "My little brother says he likes to\n"
	.string "visit people's SECRET BASES and have\l"
	.string "POKéMON battles.$"

MossdeepIsle_House4_Text_YouMadeSecretBaseNearX:
	.string "Was it you who made a SECRET BASE\n"
	.string "near {STR_VAR_1}?$"

MossdeepIsle_House4_Text_MakeSecretBase:
	.string "You should make a SECRET BASE\n"
	.string "somewhere. I'll go find it!$"

MossdeepIsle_House4_Text_Skitty:
	.string "SKITTY: Miyaan?$"

