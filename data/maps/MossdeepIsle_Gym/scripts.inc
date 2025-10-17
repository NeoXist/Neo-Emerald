MossdeepIsle_Gym_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, MossdeepIsle_Gym_OnTransition
	map_script MAP_SCRIPT_ON_LOAD, MossdeepIsle_Gym_OnLoad
	.byte 0

@ NOTE: Mossdeep Gym was redesigned between R/S and E. Leftover (and now functionally unused) scripts are commented below

MossdeepIsle_Gym_OnTransition:
	setflag FLAG_TEMP_HIDE_FOLLOWER @ Hide follower since it can collide with moving statues
	end

@ All the below checks are leftover from RS. FLAG_MOSSDEEP_GYM_SWITCH_X is never set
MossdeepIsle_Gym_OnLoad:
	goto_if_set FLAG_MOSSDEEP_GYM_SWITCH_1, MossdeepIsle_Gym_EventScript_SetSwitch1Metatiles
	goto MossdeepIsle_Gym_EventScript_CheckSwitch2
	end

MossdeepIsle_Gym_EventScript_CheckSwitch2::
	goto_if_set FLAG_MOSSDEEP_GYM_SWITCH_2, MossdeepIsle_Gym_EventScript_SetSwitch2Metatiles
	goto MossdeepIsle_Gym_EventScript_CheckSwitch3
	end

MossdeepIsle_Gym_EventScript_CheckSwitch3::
	goto_if_set FLAG_MOSSDEEP_GYM_SWITCH_3, MossdeepIsle_Gym_EventScript_SetSwitch3Metatiles
	goto MossdeepIsle_Gym_EventScript_CheckSwitch4
	end

MossdeepIsle_Gym_EventScript_CheckSwitch4::
	goto_if_set FLAG_MOSSDEEP_GYM_SWITCH_4, MossdeepIsle_Gym_EventScript_SetSwitch4Metatiles
	end

@ All the below set metatile scripts are leftover from RS and are functionally unused
MossdeepIsle_Gym_EventScript_SetSwitch1Metatiles::
	setmetatile 5, 5, METATILE_RSMossdeepGym_RedArrow_Right, FALSE
	setmetatile 2, 7, METATILE_RSMossdeepGym_Switch_Down, TRUE
	goto MossdeepIsle_Gym_EventScript_CheckSwitch2
	end

MossdeepIsle_Gym_EventScript_SetSwitch2Metatiles::
	setmetatile 8, 14, METATILE_RSMossdeepGym_RedArrow_Right, FALSE
	setmetatile 8, 10, METATILE_RSMossdeepGym_Switch_Down, TRUE
	goto MossdeepIsle_Gym_EventScript_CheckSwitch3
	end

MossdeepIsle_Gym_EventScript_SetSwitch3Metatiles::
	setmetatile 15, 17, METATILE_RSMossdeepGym_RedArrow_Left, FALSE
	setmetatile 17, 15, METATILE_RSMossdeepGym_Switch_Down, TRUE
	goto MossdeepIsle_Gym_EventScript_CheckSwitch4
	end

MossdeepIsle_Gym_EventScript_SetSwitch4Metatiles::
	setmetatile 1, 23, METATILE_RSMossdeepGym_RedArrow_Up, FALSE
	setmetatile 5, 24, METATILE_RSMossdeepGym_Switch_Down, TRUE
	end

MossdeepIsle_Gym_EventScript_TateAndLiza::
	trainerbattle_double TRAINER_TATE_AND_LIZA_1, MossdeepIsle_Gym_Text_TateAndLizaIntro, MossdeepIsle_Gym_Text_TateAndLizaDefeat, MossdeepIsle_Gym_Text_TateAndLizaNeedTwoMons, MossdeepIsle_Gym_EventScript_TateAndLizaDefeated, NO_MUSIC
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, MossdeepIsle_Gym_EventScript_TateAndLizaRematch
	goto_if_unset FLAG_RECEIVED_TM_CALM_MIND, MossdeepIsle_Gym_EventScript_GiveCalmMind2
	msgbox MossdeepIsle_Gym_Text_TateAndLizaPostBattle, MSGBOX_DEFAULT
	release
	end

MossdeepIsle_Gym_EventScript_TateAndLizaDefeated::
	message MossdeepIsle_Gym_Text_ReceivedMindBadge
	waitmessage
	call Common_EventScript_PlayGymBadgeFanfare
	msgbox MossdeepIsle_Gym_Text_ExplainMindBadgeTakeThis, MSGBOX_DEFAULT
	setflag FLAG_DEFEATED_MOSSDEEP_GYM
	setflag FLAG_BADGE07_GET
	setflag FLAG_HIDE_AQUA_HIDEOUT_GRUNTS
	clearflag FLAG_HIDE_SLATEPORT_CITY_STERNS_SHIPYARD_MR_BRINEY
	clearflag FLAG_UNKNOWN_0x393
	setvar VAR_0x8008, 7
	call Common_EventScript_SetGymTrainers
	clearflag FLAG_HIDE_SLATEPORT_CITY_HARBOR_PATRONS
	clearflag FLAG_HIDE_MOSSDEEP_CITY_TEAM_MAGMA
	clearflag FLAG_HIDE_MOSSDEEP_CITY_SPACE_CENTER_1F_TEAM_MAGMA
	clearflag FLAG_HIDE_MOSSDEEP_CITY_SPACE_CENTER_2F_TEAM_MAGMA
	clearflag FLAG_HIDE_MOSSDEEP_CITY_SPACE_CENTER_2F_STEVEN
	setvar VAR_MOSSDEEP_CITY_STATE, 1
	setflag FLAG_HIDE_MOSSDEEP_CITY_SPACE_CENTER_1F_STEVEN
	setvar VAR_MOSSDEEP_SPACE_CENTER_STATE, 1
	call MossdeepIsle_Gym_EventScript_GiveCalmMind
	closemessage
	delay 30
	playfanfare MUS_REGISTER_MATCH_CALL
	msgbox MossdeepIsle_Gym_Text_RegisteredTateAndLiza, MSGBOX_DEFAULT
	waitfanfare
	closemessage
	delay 30
	setflag FLAG_ENABLE_TATE_AND_LIZA_MATCH_CALL
	release
	end

MossdeepIsle_Gym_EventScript_GiveCalmMind2::
	giveitem ITEM_TM_CALM_MIND
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	msgbox MossdeepIsle_Gym_Text_ExplainCalmMind, MSGBOX_DEFAULT
	setflag FLAG_RECEIVED_TM_CALM_MIND
	release
	end

MossdeepIsle_Gym_EventScript_GiveCalmMind::
	giveitem ITEM_TM_CALM_MIND
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_BagIsFull
	msgbox MossdeepIsle_Gym_Text_ExplainCalmMind, MSGBOX_DEFAULT
	setflag FLAG_RECEIVED_TM_CALM_MIND
	return

MossdeepIsle_Gym_EventScript_TateAndLizaRematch::
	trainerbattle_rematch_double TRAINER_TATE_AND_LIZA_1, MossdeepIsle_Gym_Text_TateAndLizaPreRematch, MossdeepIsle_Gym_Text_TateAndLizaRematchDefeat, MossdeepIsle_Gym_Text_TateAndLizaRematchNeedTwoMons
	msgbox MossdeepIsle_Gym_Text_TateAndLizaPostRematch, MSGBOX_AUTOCLOSE
	end

@ All the below switch scripts are leftover from RS and are functionally unused
MossdeepIsle_Gym_EventScript_Switch1::
	lockall
	goto_if_set FLAG_MOSSDEEP_GYM_SWITCH_1, MossdeepIsle_Gym_EventScript_ClearSwitch1
	setflag FLAG_MOSSDEEP_GYM_SWITCH_1
	applymovement LOCALID_PLAYER, MossdeepIsle_Gym_Movement_WaitAfterSwitchUse
	waitmovement 0
	setmetatile 5, 5, METATILE_RSMossdeepGym_RedArrow_Right, FALSE
	setmetatile 2, 7, METATILE_RSMossdeepGym_Switch_Down, TRUE
	goto MossdeepIsle_Gym_EventScript_DrawMapAfterSwitchUsed
	end

MossdeepIsle_Gym_EventScript_DrawMapAfterSwitchUsed::
	special DrawWholeMapView
	playse SE_CLICK
	releaseall
	end

MossdeepIsle_Gym_EventScript_ClearSwitch1::
	clearflag FLAG_MOSSDEEP_GYM_SWITCH_1
	applymovement LOCALID_PLAYER, MossdeepIsle_Gym_Movement_WaitAfterSwitchUse
	waitmovement 0
	setmetatile 5, 5, METATILE_RSMossdeepGym_RedArrow_Left, FALSE
	setmetatile 2, 7, METATILE_RSMossdeepGym_Switch_Up, TRUE
	goto MossdeepIsle_Gym_EventScript_DrawMapAfterSwitchUsed
	end

MossdeepIsle_Gym_EventScript_Switch2::
	lockall
	goto_if_set FLAG_MOSSDEEP_GYM_SWITCH_2, MossdeepIsle_Gym_EventScript_ClearSwitch2
	setflag FLAG_MOSSDEEP_GYM_SWITCH_2
	applymovement LOCALID_PLAYER, MossdeepIsle_Gym_Movement_WaitAfterSwitchUse
	waitmovement 0
	setmetatile 8, 14, METATILE_RSMossdeepGym_RedArrow_Right, FALSE
	setmetatile 8, 10, METATILE_RSMossdeepGym_Switch_Down, TRUE
	goto MossdeepIsle_Gym_EventScript_DrawMapAfterSwitchUsed
	end

MossdeepIsle_Gym_EventScript_ClearSwitch2::
	clearflag FLAG_MOSSDEEP_GYM_SWITCH_2
	applymovement LOCALID_PLAYER, MossdeepIsle_Gym_Movement_WaitAfterSwitchUse
	waitmovement 0
	setmetatile 8, 14, METATILE_RSMossdeepGym_RedArrow_Down, FALSE
	setmetatile 8, 10, METATILE_RSMossdeepGym_Switch_Up, TRUE
	goto MossdeepIsle_Gym_EventScript_DrawMapAfterSwitchUsed
	end

MossdeepIsle_Gym_EventScript_Switch3::
	lockall
	goto_if_set FLAG_MOSSDEEP_GYM_SWITCH_3, MossdeepIsle_Gym_EventScript_ClearSwitch3
	setflag FLAG_MOSSDEEP_GYM_SWITCH_3
	applymovement LOCALID_PLAYER, MossdeepIsle_Gym_Movement_WaitAfterSwitchUse
	waitmovement 0
	setmetatile 15, 17, METATILE_RSMossdeepGym_RedArrow_Left, FALSE
	setmetatile 17, 15, METATILE_RSMossdeepGym_Switch_Down, TRUE
	goto MossdeepIsle_Gym_EventScript_DrawMapAfterSwitchUsed
	end

MossdeepIsle_Gym_EventScript_ClearSwitch3::
	clearflag FLAG_MOSSDEEP_GYM_SWITCH_3
	applymovement LOCALID_PLAYER, MossdeepIsle_Gym_Movement_WaitAfterSwitchUse
	waitmovement 0
	setmetatile 15, 17, METATILE_RSMossdeepGym_RedArrow_Right, FALSE
	setmetatile 17, 15, METATILE_RSMossdeepGym_Switch_Up, TRUE
	goto MossdeepIsle_Gym_EventScript_DrawMapAfterSwitchUsed
	end

MossdeepIsle_Gym_EventScript_Switch4::
	lockall
	goto_if_set FLAG_MOSSDEEP_GYM_SWITCH_4, MossdeepIsle_Gym_EventScript_ClearSwitch4
	setflag FLAG_MOSSDEEP_GYM_SWITCH_4
	applymovement LOCALID_PLAYER, MossdeepIsle_Gym_Movement_WaitAfterSwitchUse
	waitmovement 0
	setmetatile 1, 23, METATILE_RSMossdeepGym_RedArrow_Up, FALSE
	setmetatile 5, 24, METATILE_RSMossdeepGym_Switch_Down, TRUE
	goto MossdeepIsle_Gym_EventScript_DrawMapAfterSwitchUsed
	end

MossdeepIsle_Gym_EventScript_ClearSwitch4::
	clearflag FLAG_MOSSDEEP_GYM_SWITCH_4
	applymovement LOCALID_PLAYER, MossdeepIsle_Gym_Movement_WaitAfterSwitchUse
	waitmovement 0
	setmetatile 1, 23, METATILE_RSMossdeepGym_RedArrow_Right, FALSE
	setmetatile 5, 24, METATILE_RSMossdeepGym_Switch_Up, TRUE
	goto MossdeepIsle_Gym_EventScript_DrawMapAfterSwitchUsed
	end

MossdeepIsle_Gym_EventScript_WarpToEntrance::
	lockall
	warpmossdeepgym MAP_MOSSDEEP_CITY_GYM, 7, 30
	waitstate
	releaseall
	end

MossdeepIsle_Gym_EventScript_Preston::
	trainerbattle_single TRAINER_PRESTON, MossdeepIsle_Gym_Text_PrestonIntro, MossdeepIsle_Gym_Text_PrestonDefeat
	msgbox MossdeepIsle_Gym_Text_PrestonPostBattle, MSGBOX_AUTOCLOSE
	end

MossdeepIsle_Gym_EventScript_Virgil::
	trainerbattle_single TRAINER_VIRGIL, MossdeepIsle_Gym_Text_VirgilIntro, MossdeepIsle_Gym_Text_VirgilDefeat
	msgbox MossdeepIsle_Gym_Text_VirgilPostBattle, MSGBOX_AUTOCLOSE
	end

MossdeepIsle_Gym_EventScript_Blake::
	trainerbattle_single TRAINER_BLAKE, MossdeepIsle_Gym_Text_BlakeIntro, MossdeepIsle_Gym_Text_BlakeDefeat
	msgbox MossdeepIsle_Gym_Text_BlakePostBattle, MSGBOX_AUTOCLOSE
	end

MossdeepIsle_Gym_EventScript_Hannah::
	trainerbattle_single TRAINER_HANNAH, MossdeepIsle_Gym_Text_HannahIntro, MossdeepIsle_Gym_Text_HannahDefeat
	msgbox MossdeepIsle_Gym_Text_HannahPostBattle, MSGBOX_AUTOCLOSE
	end

MossdeepIsle_Gym_EventScript_Samantha::
	trainerbattle_single TRAINER_SAMANTHA, MossdeepIsle_Gym_Text_SamanthaIntro, MossdeepIsle_Gym_Text_SamanthaDefeat
	msgbox MossdeepIsle_Gym_Text_SamanthaPostBattle, MSGBOX_AUTOCLOSE
	end

MossdeepIsle_Gym_EventScript_Maura::
	trainerbattle_single TRAINER_MAURA, MossdeepIsle_Gym_Text_MauraIntro, MossdeepIsle_Gym_Text_MauraDefeat
	msgbox MossdeepIsle_Gym_Text_MauraPostBattle, MSGBOX_AUTOCLOSE
	end

MossdeepIsle_Gym_EventScript_Sylvia::
	trainerbattle_single TRAINER_SYLVIA, MossdeepIsle_Gym_Text_SylviaIntro, MossdeepIsle_Gym_Text_SylviaDefeat
	msgbox MossdeepIsle_Gym_Text_SylviaPostBattle, MSGBOX_AUTOCLOSE
	end

MossdeepIsle_Gym_EventScript_Nate::
	trainerbattle_single TRAINER_NATE, MossdeepIsle_Gym_Text_NateIntro, MossdeepIsle_Gym_Text_NateDefeat
	msgbox MossdeepIsle_Gym_Text_NatePostBattle, MSGBOX_AUTOCLOSE
	end

MossdeepIsle_Gym_EventScript_Macey::
	trainerbattle_single TRAINER_MACEY, MossdeepIsle_Gym_Text_MaceyIntro, MossdeepIsle_Gym_Text_MaceyDefeat
	msgbox MossdeepIsle_Gym_Text_MaceyPostBattle, MSGBOX_AUTOCLOSE
	end

MossdeepIsle_Gym_EventScript_Clifford::
	trainerbattle_single TRAINER_CLIFFORD, MossdeepIsle_Gym_Text_CliffordIntro, MossdeepIsle_Gym_Text_CliffordDefeat
	msgbox MossdeepIsle_Gym_Text_CliffordPostBattle, MSGBOX_AUTOCLOSE
	end

MossdeepIsle_Gym_EventScript_Nicholas::
	trainerbattle_single TRAINER_NICHOLAS, MossdeepIsle_Gym_Text_NicholasIntro, MossdeepIsle_Gym_Text_NicholasDefeat
	msgbox MossdeepIsle_Gym_Text_NicholasPostBattle, MSGBOX_AUTOCLOSE
	end

MossdeepIsle_Gym_EventScript_Kathleen::
	trainerbattle_single TRAINER_KATHLEEN, MossdeepIsle_Gym_Text_KathleenIntro, MossdeepIsle_Gym_Text_KathleenDefeat
	msgbox MossdeepIsle_Gym_Text_KathleenPostBattle, MSGBOX_AUTOCLOSE
	end

MossdeepIsle_Gym_EventScript_GymGuide::
	lock
	faceplayer
	goto_if_set FLAG_DEFEATED_MOSSDEEP_GYM, MossdeepIsle_Gym_EventScript_GymGuidePostVictory
	msgbox MossdeepIsle_Gym_Text_GymGuideAdvice, MSGBOX_DEFAULT
	release
	end

MossdeepIsle_Gym_EventScript_GymGuidePostVictory::
	msgbox MossdeepIsle_Gym_Text_GymGuidePostVictory, MSGBOX_DEFAULT
	release
	end

@ Leftover from RS, functionally unused
MossdeepIsle_Gym_Movement_WaitAfterSwitchUse:
	delay_16
	delay_16
	step_end

MossdeepIsle_Gym_EventScript_LeftGymStatue::
	lockall
	goto_if_set FLAG_BADGE07_GET, MossdeepIsle_Gym_EventScript_GymStatueCertified
	goto MossdeepIsle_Gym_EventScript_GymStatue
	end

MossdeepIsle_Gym_EventScript_RightGymStatue::
	lockall
	goto_if_set FLAG_BADGE07_GET, MossdeepIsle_Gym_EventScript_GymStatueCertified
	goto MossdeepIsle_Gym_EventScript_GymStatue
	end

MossdeepIsle_Gym_EventScript_GymStatueCertified::
	msgbox MossdeepIsle_Gym_Text_GymStatueCertified, MSGBOX_DEFAULT
	releaseall
	end

MossdeepIsle_Gym_EventScript_GymStatue::
	msgbox MossdeepIsle_Gym_Text_GymStatue, MSGBOX_DEFAULT
	releaseall
	end

MossdeepIsle_Gym_EventScript_YellowFloorSwitch::
	playse SE_SWITCH
	waitse
	playse SE_REPEL
	initrotatingtilepuzzle FALSE
	moverotatingtileobjects 0
	waitmovement 0
	turnrotatingtileobjects
	waitmovement 0
	freerotatingtilepuzzle
	end

MossdeepIsle_Gym_EventScript_BlueFloorSwitch::
	playse SE_SWITCH
	waitse
	playse SE_REPEL
	initrotatingtilepuzzle FALSE
	moverotatingtileobjects 1
	waitmovement 0
	turnrotatingtileobjects
	waitmovement 0
	freerotatingtilepuzzle
	end

MossdeepIsle_Gym_EventScript_GreenFloorSwitch::
	playse SE_SWITCH
	waitse
	playse SE_REPEL
	initrotatingtilepuzzle FALSE
	moverotatingtileobjects 2
	waitmovement 0
	turnrotatingtileobjects
	waitmovement 0
	freerotatingtilepuzzle
	end

MossdeepIsle_Gym_EventScript_PurpleFloorSwitch::
	playse SE_SWITCH
	waitse
	playse SE_REPEL
	initrotatingtilepuzzle FALSE
	moverotatingtileobjects 3
	waitmovement 0
	turnrotatingtileobjects
	waitmovement 0
	freerotatingtilepuzzle
	end

MossdeepIsle_Gym_EventScript_RedFloorSwitch::
	playse SE_SWITCH
	waitse
	playse SE_REPEL
	initrotatingtilepuzzle FALSE
	moverotatingtileobjects 4
	waitmovement 0
	turnrotatingtileobjects
	waitmovement 0
	freerotatingtilepuzzle
	end

MossdeepIsle_Gym_Text_GymGuideAdvice:
	.string "Yo, how's it going, CHAMPION-bound\n"
	.string "{PLAYER}?\p"
	.string "The GYM LEADERS here use\n"
	.string "PSYCHIC-type POKéMON.\p"
	.string "If you go up against them with\n"
	.string "FIGHTING- or POISON-type POKéMON,\l"
	.string "they'll inflict horrible damage!\p"
	.string "Plus, they'll come at you with\n"
	.string "outstanding combination attacks.\p"
	.string "If you want to win, you'll need to show\n"
	.string "them how tight you are with your\l"
	.string "POKéMON. Go for it!$"

MossdeepIsle_Gym_Text_GymGuidePostVictory:
	.string "Wow, you're astounding!\n"
	.string "You're one great TRAINER!$"

MossdeepIsle_Gym_Text_PrestonIntro:
	.string "Battles hinge on the strength of your\n"
	.string "spirit! The weak-spirited will never win!$"

MossdeepIsle_Gym_Text_PrestonDefeat:
	.string "I lost!\n"
	.string "I must temper my spirit again!$"

MossdeepIsle_Gym_Text_PrestonPostBattle:
	.string "The indecisive lose.\n"
	.string "That's my warning to you.$"

MossdeepIsle_Gym_Text_VirgilIntro:
	.string "Let me see your talent!$"

MossdeepIsle_Gym_Text_VirgilDefeat:
	.string "You possess spectacular talent!$"

MossdeepIsle_Gym_Text_VirgilPostBattle:
	.string "If there are prodigies in the world,\n"
	.string "then our GYM LEADERS are them!\p"
	.string "However, you may be even more talented\n"
	.string "than them…$"

MossdeepIsle_Gym_Text_BlakeIntro:
	.string "Fufufufu… Watch me levitate a POKé\n"
	.string "BALL telekinetically!\p"
	.string "Wrooooooooaaaar!\n"
	.string "… … … … … … …\p"
	.string "Sometimes, I'm out of sync…$"

MossdeepIsle_Gym_Text_BlakeDefeat:
	.string "My POKéMON battling skills are out\n"
	.string "of sync, too!$"

MossdeepIsle_Gym_Text_BlakePostBattle:
	.string "A POKé BALL was too heavy to lift\n"
	.string "psychically. But this dust bunny…\p"
	.string "Whoooooooooooooooh!\n"
	.string "… … … … … …\p"
	.string "No, I'm not cheating!\n"
	.string "I didn't blow on it! Honestly!$"

MossdeepIsle_Gym_Text_HannahIntro:
	.string "When you lose to me, don't be too hard\n"
	.string "on yourself.\p"
	.string "It's not that you're weak--I'm just\n"
	.string "too strong!$"

MossdeepIsle_Gym_Text_HannahDefeat:
	.string "You're just too strong!$"

MossdeepIsle_Gym_Text_HannahPostBattle:
	.string "I'm not going to get down on myself for\n"
	.string "losing. I just need to train harder.\p"
	.string "Positive thinking--that's my strong\n"
	.string "point!$"

MossdeepIsle_Gym_Text_SamanthaIntro:
	.string "I see it…\n"
	.string "I see your future…\p"
	.string "If you can beat me, I will tell you\n"
	.string "your future!$"

MossdeepIsle_Gym_Text_SamanthaDefeat:
	.string "I surrender!$"

MossdeepIsle_Gym_Text_SamanthaPostBattle:
	.string "You will wage a terrifically intense\n"
	.string "battle with our GYM LEADERS…\p"
	.string "The result…\n"
	.string "You won't hear it from me!$"

MossdeepIsle_Gym_Text_MauraIntro:
	.string "The roads you have traveled…\n"
	.string "What you have experienced…\p"
	.string "Come at me with everything you've\n"
	.string "learned!$"

MossdeepIsle_Gym_Text_MauraDefeat:
	.string "You've traveled a path of greatness!$"

MossdeepIsle_Gym_Text_MauraPostBattle:
	.string "A bright future awaits those who have\n"
	.string "worked diligently.\p"
	.string "For those who lazed idly, there is\n"
	.string "only despair at the end.\p"
	.string "What goes around comes around…$"

MossdeepIsle_Gym_Text_SylviaIntro:
	.string "Even at the risk of life, I will win\n"
	.string "this battle!$"

MossdeepIsle_Gym_Text_SylviaDefeat:
	.string "What you do…\n"
	.string "It horrifies me…$"

MossdeepIsle_Gym_Text_SylviaPostBattle:
	.string "How dare you beat me…\p"
	.string "It won't be my fault if something\n"
	.string "horrible befalls you…$"

MossdeepIsle_Gym_Text_NateIntro:
	.string "Hohoho.\p"
	.string "You need me to show you how tenacious\n"
	.string "the PSYCHIC type can be.$"

MossdeepIsle_Gym_Text_NateDefeat:
	.string "Oh! My, my!\n"
	.string "Your battle style is fantastic!$"

MossdeepIsle_Gym_Text_NatePostBattle:
	.string "I… I don't let defeat rattle m-me,\n"
	.string "however b-badly.$"

MossdeepIsle_Gym_Text_KathleenIntro:
	.string "Let me show you a perfectly awful,\n"
	.string "horrifying time!$"

MossdeepIsle_Gym_Text_KathleenDefeat:
	.string "N-nooooo!$"

MossdeepIsle_Gym_Text_KathleenPostBattle:
	.string "Your vitality is contagious!\n"
	.string "Get away from me quickly!$"

MossdeepIsle_Gym_Text_CliffordIntro:
	.string "I may be past my prime, but I suggest\n"
	.string "you not patronize me.$"

MossdeepIsle_Gym_Text_CliffordDefeat:
	.string "Ah, you overflow with the power\n"
	.string "of youth!$"

MossdeepIsle_Gym_Text_CliffordPostBattle:
	.string "It seems that I could not overcome\n"
	.string "your youthful energy.$"

MossdeepIsle_Gym_Text_MaceyIntro:
	.string "You're not getting through to the end!\n"
	.string "Not if I can help it!$"

MossdeepIsle_Gym_Text_MaceyDefeat:
	.string "How could you be so ludicrously\n"
	.string "strong?$"

MossdeepIsle_Gym_Text_MaceyPostBattle:
	.string "Humph! You may be strong, but you're\n"
	.string "not suitable for the PSYCHIC type!\p"
	.string "The way you battle is somehow brutal!$"

MossdeepIsle_Gym_Text_NicholasIntro:
	.string "Wroooar! Have a taste of my super\n"
	.string "POKéMON hard-battling power!$"

MossdeepIsle_Gym_Text_NicholasDefeat:
	.string "Oh!\n"
	.string "Done in!$"

MossdeepIsle_Gym_Text_NicholasPostBattle:
	.string "All right! I think I'll develop a special\n"
	.string "invincible POKéMON power next.$"

MossdeepIsle_Gym_Text_TateAndLizaIntro:
	.string "TATE: Hehehe… Were you surprised?\p"
	.string "LIZA: Fufufu… Were you surprised?\p"
	.string "TATE: That there are two GYM LEADERS?\n"
	.string "LIZA: That there are two GYM LEADERS?\p"
	.string "TATE: We're twins!\n"
	.string "LIZA: We're twins!\p"
	.string "TATE: We don't need to talk because…\n"
	.string "LIZA: We can each determine what…\p"
	.string "TATE: The other is thinking…\n"
	.string "LIZA: All in our minds!\p"
	.string "TATE: This combination of ours…\n"
	.string "LIZA: Can you beat it?$"

MossdeepIsle_Gym_Text_TateAndLizaDefeat:
	.string "TATE: What?! Our combination…\n"
	.string "LIZA: Was shattered!\p"
	.string "TATE: It can't be helped. You've won…\n"
	.string "LIZA: So, in recognition, take this.$"

MossdeepIsle_Gym_Text_ReceivedMindBadge:
	.string "{PLAYER} received the MIND BADGE\n"
	.string "from TATE and LIZA.$"

MossdeepIsle_Gym_Text_ExplainMindBadgeTakeThis:
	.string "TATE: The MIND BADGE enhances the\n"
	.string "SP. ATK and SP. DEF of POKéMON.\p"
	.string "LIZA: It also lets you use the HM move\n"
	.string "DIVE outside of battle.\p"
	.string "TATE: You should also take this, too.$"

MossdeepIsle_Gym_Text_ExplainCalmMind:
	.string "TATE: That TM04 contains…\n"
	.string "LIZA: CALM MIND!\p"
	.string "TATE: It raises SP. ATK and…\n"
	.string "LIZA: It raises SP. DEF!\p"
	.string "TATE: It's a move that's perfect…\n"
	.string "LIZA: For PSYCHIC POKéMON!\p"
	.string "… … … … … …$"

MossdeepIsle_Gym_Text_RegisteredTateAndLiza:
	.string "Registered GYM LEADERS TATE & LIZA\n"
	.string "in the POKéNAV.$"

MossdeepIsle_Gym_Text_TateAndLizaPostBattle:
	.string "TATE: Looks like the bond between you\n"
	.string "and your POKéMON is far stronger than\l"
	.string "the bond that we share as twins.\p"
	.string "LIZA: You will become even stronger!\n"
	.string "We've battled you, so we know.$"

MossdeepIsle_Gym_Text_TateAndLizaNeedTwoMons:
	.string "TATE: Hehehe… Were you surprised?\p"
	.string "LIZA: That there are two GYM LEADERS?\p"
	.string "TATE: Oops, you have only one…\n"
	.string "LIZA: POKéMON that can battle.\p"
	.string "TATE: We can't battle that way!\p"
	.string "LIZA: If you want to challenge us,\n"
	.string "bring some more POKéMON.$"

MossdeepIsle_Gym_Text_GymStatue:
	.string "MOSSDEEP CITY POKéMON GYM$"

MossdeepIsle_Gym_Text_GymStatueCertified:
	.string "MOSSDEEP CITY POKéMON GYM\p"
	.string "LIZA AND TATE'S CERTIFIED TRAINERS:\n"
	.string "{PLAYER}$"

MossdeepIsle_Gym_Text_TateAndLizaPreRematch:
	.string "TATE: POKéMON…\n"
	.string "LIZA: POKéMON…\p"
	.string "TATE: By changing the party's mix…\n"
	.string "LIZA: The battle style changes.\p"
	.string "TATE: But me…\n"
	.string "LIZA: But me…\p"
	.string "TATE: I'll always be with LIZA!\n"
	.string "LIZA: I'll always be with TATE!\p"
	.string "TATE: Our combination…\n"
	.string "LIZA: We'll show you again and again!$"

MossdeepIsle_Gym_Text_TateAndLizaRematchDefeat:
	.string "TATE: You and your POKéMON…\n"
	.string "LIZA: It's as if you were siblings!$"

MossdeepIsle_Gym_Text_TateAndLizaPostRematch:
	.string "TATE: You can knock us down,\n"
	.string "but we'll never stay down!\p"
	.string "LIZA: Because the two of us,\n"
	.string "we always support each other!$"

MossdeepIsle_Gym_Text_TateAndLizaRematchNeedTwoMons:
	.string "TATE: You're back again…\n"
	.string "LIZA: You're back again…\p"
	.string "TATE: To give us a rematch.\n"
	.string "LIZA: To give us a rematch.\p"
	.string "TATE: But…\n"
	.string "LIZA: For our match…\p"
	.string "TATE: You brought just one POKéMON!\n"
	.string "LIZA: You brought just one POKéMON!\p"
	.string "TATE: We need you to bring at least…\n"
	.string "LIZA: Two POKéMON when you come back.$"
