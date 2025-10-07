MossdeepIsle_House3_MapScripts::
	.byte 0

MossdeepIsle_House3_EventScript_SuperRodFisherman::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_SUPER_ROD, MossdeepIsle_House3_EventScript_ReceivedSuperRod
	msgbox MossdeepIsle_House3_Text_YouWantSuperRod, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, MossdeepIsle_House3_EventScript_DeclineSuperRod
	msgbox MossdeepIsle_House3_Text_SuperRodIsSuper, MSGBOX_DEFAULT
	giveitem ITEM_SUPER_ROD
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setflag FLAG_RECEIVED_SUPER_ROD
	msgbox MossdeepIsle_House3_Text_TryDroppingRodInWater, MSGBOX_DEFAULT
	release
	end

MossdeepIsle_House3_EventScript_ReceivedSuperRod::
	msgbox MossdeepIsle_House3_Text_GoAfterSeafloorPokemon, MSGBOX_DEFAULT
	release
	end

MossdeepIsle_House3_EventScript_DeclineSuperRod::
	msgbox MossdeepIsle_House3_Text_DontYouLikeToFish, MSGBOX_DEFAULT
	release
	end

MossdeepIsle_House3_Text_YouWantSuperRod:
	.string "Hey there, TRAINER!\n"
	.string "A SUPER ROD really is super!\p"
	.string "Say all you want, but this baby can\n"
	.string "catch POKéMON off the seafloor!\p"
	.string "What do you think?\n"
	.string "You want it, don't you?$"

MossdeepIsle_House3_Text_SuperRodIsSuper:
	.string "You bet, you bet!\n"
	.string "After all, a SUPER ROD is really super!$"

MossdeepIsle_House3_Text_TryDroppingRodInWater:
	.string "If there's any water, try dropping in\n"
	.string "your ROD and see what bites!$"

MossdeepIsle_House3_Text_DontYouLikeToFish:
	.string "Hunh?\n"
	.string "Don't you like to fish?$"

MossdeepIsle_House3_Text_GoAfterSeafloorPokemon:
	.string "Go after the seafloor POKéMON with\n"
	.string "your SUPER ROD.$"

