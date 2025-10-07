DewfordIsle_House1_MapScripts::
	.byte 0

DewfordIsle_House1_EventScript_Man::
	msgbox DewfordIsle_House1_Text_LotToBeSaidForLivingOnIsland, MSGBOX_NPC
	end

DewfordIsle_House1_EventScript_Woman::
	msgbox DewfordIsle_House1_Text_LifeGoesSlowlyOnIsland, MSGBOX_NPC
	end

DewfordIsle_House1_EventScript_Zigzagoon::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_ZIGZAGOON, CRY_MODE_NORMAL
	msgbox DewfordIsle_House1_Text_Zigzagoon, MSGBOX_DEFAULT
	waitmoncry
	release
	end

DewfordIsle_House1_Text_LotToBeSaidForLivingOnIsland:
	.string "There's a lot to be said for living on\n"
	.string "a small island like this in harmony with\l"
	.string "POKéMON and the family.$"

DewfordIsle_House1_Text_LifeGoesSlowlyOnIsland:
	.string "I left the major port of SLATEPORT\n"
	.string "CITY when I married my husband here.\p"
	.string "Life goes by slowly on this little\n"
	.string "island. But being surrounded by the\l"
	.string "beautiful sea--that's happiness, too.$"

DewfordIsle_House1_Text_Zigzagoon:
	.string "ZIGZAGOON: Guguuh!$"

