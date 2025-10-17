DewfordIsle_Hall_MapScripts::
	.byte 0

DewfordIsle_Hall_EventScript_Girl::
	lock
	faceplayer
	call Common_EventScript_BufferTrendyPhrase
	special IsTrendyPhraseBoring
	goto_if_eq VAR_RESULT, TRUE, DewfordIsle_Hall_EventScript_GirlBoredOfTrend
	msgbox DewfordIsle_Hall_Text_CantImagineLifeWithoutTrend, MSGBOX_DEFAULT
	release
	end

DewfordIsle_Hall_EventScript_GirlBoredOfTrend::
	msgbox DewfordIsle_Hall_Text_GettingBoredOfTrend, MSGBOX_DEFAULT
	release
	end

DewfordIsle_Hall_EventScript_Woman::
	lock
	faceplayer
	call Common_EventScript_BufferTrendyPhrase
	msgbox DewfordIsle_Hall_Text_TeachingMonAboutTrend, MSGBOX_DEFAULT
	release
	end

DewfordIsle_Hall_EventScript_Man::
	lock
	faceplayer
	call Common_EventScript_BufferTrendyPhrase
	special BufferDeepLinkPhrase
	msgbox DewfordIsle_Hall_Text_DeepLinkBetweenXAndY, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, DewfordIsle_Hall_EventScript_ConfirmTrendLink
	goto_if_eq VAR_RESULT, NO, DewfordIsle_Hall_EventScript_RejectTrendLink
	end

DewfordIsle_Hall_EventScript_ConfirmTrendLink::
	msgbox DewfordIsle_Hall_Text_MyHunchWasRight, MSGBOX_DEFAULT
	release
	end

DewfordIsle_Hall_EventScript_RejectTrendLink::
	msgbox DewfordIsle_Hall_Text_NotEasyToKeepUp, MSGBOX_DEFAULT
	release
	end

DewfordIsle_Hall_EventScript_ExpertM::
	lock
	faceplayer
	call Common_EventScript_BufferTrendyPhrase
	msgbox DewfordIsle_Hall_Text_TVShowAboutTrend, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_DEWFORD_HALL_EXPERT_M, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	release
	end

DewfordIsle_Hall_EventScript_Twin::
	lock
	faceplayer
	call Common_EventScript_BufferTrendyPhrase
	msgbox DewfordIsle_Hall_Text_IsTrendMorePopularAcrossSea, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_DEWFORD_HALL_TWIN, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	release
	end

DewfordIsle_Hall_EventScript_LittleBoy::
	lock
	faceplayer
	call Common_EventScript_BufferTrendyPhrase
	msgbox DewfordIsle_Hall_Text_CollectTrendMerchandise, MSGBOX_DEFAULT
	release
	end

DewfordIsle_Hall_EventScript_Bookshelf::
	lockall
	call Common_EventScript_BufferTrendyPhrase
	msgbox DewfordIsle_Hall_Text_BooksAboutTrend, MSGBOX_DEFAULT
	releaseall
	end

DewfordIsle_Hall_EventScript_Painting::
	lockall
	call Common_EventScript_BufferTrendyPhrase
	special GetDewfordHallPaintingNameIndex
	switch VAR_RESULT
	case 0, DewfordIsle_Hall_EventScript_ScreamTitle
	case 4, DewfordIsle_Hall_EventScript_ScreamTitle
	case 1, DewfordIsle_Hall_EventScript_SmileTitle
	case 5, DewfordIsle_Hall_EventScript_ScreamTitle
	case 2, DewfordIsle_Hall_EventScript_LastTitle
	case 6, DewfordIsle_Hall_EventScript_LastTitle
	case 3, DewfordIsle_Hall_EventScript_BirthTitle
	case 7, DewfordIsle_Hall_EventScript_LastTitle
	end

DewfordIsle_Hall_EventScript_ScreamTitle::
	msgbox DewfordIsle_Hall_Text_TrendsScream, MSGBOX_DEFAULT
	releaseall
	end

DewfordIsle_Hall_EventScript_SmileTitle::
	msgbox DewfordIsle_Hall_Text_TrendsSmile, MSGBOX_DEFAULT
	releaseall
	end

DewfordIsle_Hall_EventScript_LastTitle::
	msgbox DewfordIsle_Hall_Text_LastTrend, MSGBOX_DEFAULT
	releaseall
	end

DewfordIsle_Hall_EventScript_BirthTitle::
	msgbox DewfordIsle_Hall_Text_BirthOfTrend, MSGBOX_DEFAULT
	releaseall
	end

DewfordIsle_Hall_EventScript_SchoolKidM::
	lockall
	setvar VAR_0x8008, 0
	goto DewfordIsle_Hall_EventScript_DoTrendDebate
	end

DewfordIsle_Hall_EventScript_PsychicM::
	lockall
	setvar VAR_0x8008, 1
	goto DewfordIsle_Hall_EventScript_DoTrendDebate
	end

DewfordIsle_Hall_EventScript_DoTrendDebate::
	call Common_EventScript_BufferTrendyPhrase
	special GetDewfordHallPaintingNameIndex
	switch VAR_RESULT
	case 0, DewfordIsle_Hall_EventScript_TrendDebate1
	case 1, DewfordIsle_Hall_EventScript_TrendDebate1
	case 2, DewfordIsle_Hall_EventScript_TrendDebate2
	case 3, DewfordIsle_Hall_EventScript_TrendDebate2
	case 4, DewfordIsle_Hall_EventScript_TrendDebate3
	case 5, DewfordIsle_Hall_EventScript_TrendDebate3
	case 6, DewfordIsle_Hall_EventScript_TrendDebate4
	case 7, DewfordIsle_Hall_EventScript_TrendDebate5
	end

DewfordIsle_Hall_EventScript_TrendDebate1::
	call DewfordIsle_Hall_EventScript_DebateReact1
	msgbox DewfordIsle_Hall_Text_SawTrendCoolestThing, MSGBOX_DEFAULT
	call DewfordIsle_Hall_EventScript_DebateReact2
	msgbox DewfordIsle_Hall_Text_AllegedTrendNotAuthentic, MSGBOX_DEFAULT
	releaseall
	end

DewfordIsle_Hall_EventScript_TrendDebate2::
	call DewfordIsle_Hall_EventScript_DebateReact1
	msgbox DewfordIsle_Hall_Text_ComposedTrendThemeSong, MSGBOX_DEFAULT
	call DewfordIsle_Hall_EventScript_DebateReact2
	msgbox DewfordIsle_Hall_Text_WorkOnYourSinging, MSGBOX_DEFAULT
	releaseall
	end

DewfordIsle_Hall_EventScript_TrendDebate3::
	call DewfordIsle_Hall_EventScript_DebateReact1
	msgbox DewfordIsle_Hall_Text_OrganizeTrendParty, MSGBOX_DEFAULT
	call DewfordIsle_Hall_EventScript_DebateReact2
	msgbox DewfordIsle_Hall_Text_BrilliantIndeed, MSGBOX_DEFAULT
	releaseall
	end

DewfordIsle_Hall_EventScript_TrendDebate4::
	call DewfordIsle_Hall_EventScript_DebateReact1
	msgbox DewfordIsle_Hall_Text_TrendHasBecomePartOfLife, MSGBOX_DEFAULT
	call DewfordIsle_Hall_EventScript_DebateReact2
	msgbox DewfordIsle_Hall_Text_TrendWeighsHeavilyOnMind, MSGBOX_DEFAULT
	releaseall
	end

DewfordIsle_Hall_EventScript_TrendDebate5::
	call DewfordIsle_Hall_EventScript_DebateReact1
	msgbox DewfordIsle_Hall_Text_IfWeTeamUpWellBeInvincible, MSGBOX_DEFAULT
	call DewfordIsle_Hall_EventScript_DebateReact2
	msgbox DewfordIsle_Hall_Text_WellBeTrendDuo, MSGBOX_DEFAULT
	releaseall
	end

DewfordIsle_Hall_EventScript_DontMovePlayer1::
	return

DewfordIsle_Hall_EventScript_DebateReact1::
	applymovement LOCALID_DEWFORD_HALL_PSYCHIC_M, DewfordIsle_Hall_Movement_PsychicWalkInPlaceLeft
	waitmovement 0
	goto_if_eq VAR_0x8008, 0, DewfordIsle_Hall_EventScript_PlayerReactWest
	goto_if_eq VAR_0x8008, 1, DewfordIsle_Hall_EventScript_DontMovePlayer2
	end

DewfordIsle_Hall_EventScript_PlayerReactWest::
	goto_if_eq VAR_FACING, DIR_EAST, DewfordIsle_Hall_EventScript_DontMovePlayer1
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	return

DewfordIsle_Hall_EventScript_DontMovePlayer2::
	return

DewfordIsle_Hall_EventScript_DebateReact2::
	applymovement LOCALID_DEWFORD_HALL_SCHOOL_KID_M, DewfordIsle_Hall_Movement_SchoolKidWalkInPlaceRight
	waitmovement 0
	goto_if_eq VAR_0x8008, 0, DewfordIsle_Hall_EventScript_PlayerReactNorthSouth
	goto_if_eq VAR_0x8008, 1, DewfordIsle_Hall_EventScript_PlayerReactEast
	end

DewfordIsle_Hall_EventScript_PlayerReactNorthSouth::
	call_if_eq VAR_FACING, DIR_NORTH, DewfordIsle_Hall_EventScript_PlayerWalkInPlaceUp
	call_if_eq VAR_FACING, DIR_SOUTH, DewfordIsle_Hall_EventScript_PlayerWalkInPlaceDown
	return

DewfordIsle_Hall_EventScript_PlayerWalkInPlaceUp::
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	return

DewfordIsle_Hall_EventScript_PlayerWalkInPlaceDown::
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	return

DewfordIsle_Hall_EventScript_PlayerReactEast::
	goto_if_eq VAR_FACING, DIR_WEST, DewfordIsle_Hall_EventScript_DontMovePlayer1
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	return

DewfordIsle_Hall_Movement_PsychicWalkInPlaceLeft:
	walk_in_place_left
	step_end

DewfordIsle_Hall_Movement_SchoolKidWalkInPlaceRight:
	walk_in_place_right
	step_end

DewfordIsle_Hall_EventScript_SludgeBombMan::
	lock
	faceplayer
	call Common_EventScript_BufferTrendyPhrase
	goto_if_set FLAG_RECEIVED_TM_SLUDGE_BOMB, DewfordIsle_Hall_EventScript_ReceivedSludgeBomb
	msgbox DewfordIsle_Hall_Text_GiveYouSludgeBomb, MSGBOX_DEFAULT
	giveitem ITEM_TM_SLUDGE_BOMB
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setflag FLAG_RECEIVED_TM_SLUDGE_BOMB
	release
	end

DewfordIsle_Hall_EventScript_ReceivedSludgeBomb::
	msgbox DewfordIsle_Hall_Text_LoveSludgeBombButTrendInToo, MSGBOX_DEFAULT
	release
	end

DewfordIsle_Hall_Text_CantImagineLifeWithoutTrend:
	.string "What's in vogue? Why, it has to be\n"
	.string "“{STR_VAR_1}”!\p"
	.string "I can't imagine what life would be like\n"
	.string "without “{STR_VAR_1}”!$"

DewfordIsle_Hall_Text_GettingBoredOfTrend:
	.string "What's in vogue? Why, it has to be\n"
	.string "“{STR_VAR_1}”!\p"
	.string "But I'm getting kind of bored with it.\p"
	.string "I should look for the next big thing.$"

DewfordIsle_Hall_Text_TeachingMonAboutTrend:
	.string "I'm teaching my POKéMON about\n"
	.string "“{STR_VAR_1},”\l"
	.string "but it's not going well.\p"
	.string "It's a bit too much, I think.$"

DewfordIsle_Hall_Text_DeepLinkBetweenXAndY:
	.string "I'm studying up on the hip and trendy\n"
	.string "“{STR_VAR_1}” now.\p"
	.string "Is it true that there's a deep link\n"
	.string "between “{STR_VAR_1}”\l"
	.string "and “{STR_VAR_2}”?$"

DewfordIsle_Hall_Text_MyHunchWasRight:
	.string "Oh!\n"
	.string "So, my hunch was right!\p"
	.string "I'm one step closer to being hip and\n"
	.string "happening, yowza!$"

DewfordIsle_Hall_Text_NotEasyToKeepUp:
	.string "What?!\n"
	.string "Is that so?!\p"
	.string "It's not easy for an older fellow like\n"
	.string "me to keep up with trends!$"

DewfordIsle_Hall_Text_TVShowAboutTrend:
	.string "This whole business about\n"
	.string "“{STR_VAR_1}”…\l"
	.string "Isn't there a TV show on it?$"

DewfordIsle_Hall_Text_IsTrendMorePopularAcrossSea:
	.string "Across the sea…\p"
	.string "Is “{STR_VAR_1}”\n"
	.string "even more popular?$"

DewfordIsle_Hall_Text_CollectTrendMerchandise:
	.string "I collect official\n"
	.string "“{STR_VAR_1}”\l"
	.string "licensed merchandise.\p"
	.string "I have official\n"
	.string "“{STR_VAR_1}” DOLLS…\p"
	.string "Official “{STR_VAR_1}”\n"
	.string "brand clothing…\p"
	.string "And officially licensed\n"
	.string "“{STR_VAR_1}”\l"
	.string "picture books.\p"
	.string "Heheh, I own!\n"
	.string "I'm not sharing anything with you!$"

DewfordIsle_Hall_Text_BooksAboutTrend:
	.string "IDENTIFYING GOOD\n"
	.string "“{STR_VAR_1}” &\l"
	.string "BAD “{STR_VAR_1}”…\p"
	.string "THE LINK BETWEEN\n"
	.string "“{STR_VAR_1}” AND\l"
	.string "POKéMON…\p"
	.string "USEFUL\n"
	.string "“{STR_VAR_1}”…\p"
	.string "It's neatly jammed with books about\n"
	.string "“{STR_VAR_1}.”$"

DewfordIsle_Hall_Text_TrendsScream:
	.string "“{STR_VAR_1}'S\n"
	.string "SCREAM” is the title.$"

DewfordIsle_Hall_Text_TrendsSmile:
	.string "“{STR_VAR_1}'S\n"
	.string "SMILE” is the title.$"

DewfordIsle_Hall_Text_LastTrend:
	.string "It's titled “THE LAST\n"
	.string "{STR_VAR_1}”.$"

DewfordIsle_Hall_Text_BirthOfTrend:
	.string "It's titled “THE BIRTH OF\n"
	.string "{STR_VAR_1}”.$"

DewfordIsle_Hall_Text_SawTrendCoolestThing:
	.string "I saw “{STR_VAR_1}”!\n"
	.string "Cool, huh?\p"
	.string "It's, like, the coolest thing going!\p"
	.string "It was awesome!\n"
	.string "It was the real thing, oh yeah!$"

DewfordIsle_Hall_Text_AllegedTrendNotAuthentic:
	.string "Oh, no, no, no.\p"
	.string "That alleged\n"
	.string "“{STR_VAR_1}”\l"
	.string "you claim to have seen--it's not.\p"
	.string "The authentic article is much…\n"
	.string "How should I say it?\l"
	.string "Sharper, yet more mellow!\p"
	.string "Ah, no matter. It's astonishing!$"

DewfordIsle_Hall_Text_ComposedTrendThemeSong:
	.string "Hey, listen, I composed a theme song\n"
	.string "for “{STR_VAR_1}.”\p"
	.string "“{STR_VAR_1}”\n"
	.string "is really popular right now.\p"
	.string "Okay, listen!\n"
	.string "… …\p"
	.string "Oh!\n"
	.string "{STR_VAR_1}!\p"
	.string "Wonderful\n"
	.string "{STR_VAR_1}!$"

DewfordIsle_Hall_Text_WorkOnYourSinging:
	.string "… …\p"
	.string "I dare say, chap, it would pay for you\n"
	.string "to work on your singing before you\l"
	.string "trifle yourself with\l"
	.string "“{STR_VAR_1}.”$"

DewfordIsle_Hall_Text_OrganizeTrendParty:
	.string "Anyway, as I was saying earlier, we\n"
	.string "should get together and organize a\l"
	.string "“{STR_VAR_1}” party\l"
	.string "on the island.$"

DewfordIsle_Hall_Text_BrilliantIndeed:
	.string "Oh, a smashing good idea!\p"
	.string "It will settle once and for all\n"
	.string "who is the best at\l"
	.string "“{STR_VAR_1}.”\l"
	.string "Brilliant, indeed!\p"
	.string "Starting today, our lives will revolve\n"
	.string "around “{STR_VAR_1}”!$"

DewfordIsle_Hall_Text_TrendHasBecomePartOfLife:
	.string "I was thinking, though…\p"
	.string "Wouldn't you agree that\n"
	.string "“{STR_VAR_1}” has\l"
	.string "grown from being something trendy to\l"
	.string "being a part of our daily lives?$"

DewfordIsle_Hall_Text_TrendWeighsHeavilyOnMind:
	.string "Beg pardon?\n"
	.string "That much, what?\p"
	.string "However, it's true that\n"
	.string "“{STR_VAR_1}”\l"
	.string "weighs heavily on your mind, whether\l"
	.string "you're awake or asleep.\p"
	.string "Absolutely, you're the\n"
	.string "“{STR_VAR_1}”\l"
	.string "PROFESSOR, old sport!$"

DewfordIsle_Hall_Text_IfWeTeamUpWellBeInvincible:
	.string "If you and me team up as a combo,\n"
	.string "we'll be invincible when it comes to all\l"
	.string "things “{STR_VAR_1}”!$"

DewfordIsle_Hall_Text_WellBeTrendDuo:
	.string "Spot on, my friend!\p"
	.string "We shall be the\n"
	.string "“{STR_VAR_1}” DUO!\p"
	.string "Isn't that a ripe image?\n"
	.string "Hahahah!$"

DewfordIsle_Hall_Text_GiveYouSludgeBomb:
	.string "For me, SLUDGE BOMB is at the peak\n"
	.string "of popularity. It's the one.\p"
	.string "Hunh? You're telling me that you don't\n"
	.string "know about SLUDGE BOMB?\p"
	.string "That's outright pitiful.\n"
	.string "I'll give you one.$"

DewfordIsle_Hall_Text_LoveSludgeBombButTrendInToo:
	.string "I love SLUDGE BOMB.\p"
	.string "But POKéMON with the move\n"
	.string "“{STR_VAR_1}”\l"
	.string "are in, too.$"

