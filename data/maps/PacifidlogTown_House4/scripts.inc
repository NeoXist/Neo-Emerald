PacifidlogIsle_House4_MapScripts::
	.byte 0

PacifidlogIsle_House4_EventScript_LittleGirl::
	msgbox PacifidlogIsle_House4_Text_SkyPokemon, MSGBOX_NPC
	end

PacifidlogIsle_House4_EventScript_Woman::
	msgbox PacifidlogIsle_House4_Text_PeopleSawHighFlyingPokemon, MSGBOX_NPC
	end

PacifidlogIsle_House4_EventScript_Boy::
	lock
	faceplayer
	msgbox PacifidlogIsle_House4_Text_WhereDidYouComeFrom, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, PacifidlogIsle_House4_EventScript_Yes
	goto_if_eq VAR_RESULT, NO, PacifidlogIsle_House4_EventScript_No
	end

PacifidlogIsle_House4_EventScript_Yes::
	msgbox PacifidlogIsle_House4_Text_YesTown, MSGBOX_DEFAULT
	release
	end

PacifidlogIsle_House4_EventScript_No::
	msgbox PacifidlogIsle_House4_Text_YouHaveToComeFromSomewhere, MSGBOX_DEFAULT
	release
	end

PacifidlogIsle_House4_Text_PeopleSawHighFlyingPokemon:
	.string "People were saying they saw a POKéMON\n"
	.string "flying high above HOENN.\p"
	.string "Is it flying around all the time?\n"
	.string "Doesn't it need to rest somewhere?$"

PacifidlogIsle_House4_Text_SkyPokemon:
	.string "A sky POKéMON!\n"
	.string "A sky POKéMON!$"

PacifidlogIsle_House4_Text_WhereDidYouComeFrom:
	.string "Where did you come from?$"

PacifidlogIsle_House4_Text_YesTown:
	.string "Yes?\n"
	.string "YES TOWN?\p"
	.string "I've never heard of a place like that.$"

PacifidlogIsle_House4_Text_YouHaveToComeFromSomewhere:
	.string "No? That doesn't make any sense.\n"
	.string "You have to come from somewhere.\p"
	.string "Oh! Wait! You're not going to say you\n"
	.string "were born at the bottom of the sea?$"

