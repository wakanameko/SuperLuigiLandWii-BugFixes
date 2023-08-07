#include <game.h>
#include <newer.h>
#include "levelinfo.h"

int lastLevelIDs[] = {
	-1, /*no world*/
	27, 27, 27, 27, 27, 27, 27, 25,
	10,
	24, 24, 21, 24, 3
};


/*
extern "C" void FuckUpYoshi(void *_this) {
	dEn_c *koopa = (dEn_c*)fBase_c::search(EN_NOKONOKO, 0);
	static int thing = 0;
	thing++;
	nw4r::db::Exception_Printf_("Fruit eaten: %d\n", thing);
	if (thing == 5) {
		nw4r::db::Exception_Printf_("5th fruit eaten\n");
		nw4r::db::Exception_Printf_("Let's try fucking up Yoshi ! \n");
		daPlBase_c *yoshi = (daPlBase_c*)fBase_c::search(YOSHI, 0);
		nw4r::db::Exception_Printf_("Fruit: %p ; Koopa: %p ; Yoshi: %p\n", _this, koopa, yoshi);
		koopa->_vf220(yoshi);
		nw4r::db::Exception_Printf_("Yoshi fucked up. Yay.\n");
		thing = 0;
	}
}

extern "C" void FuckUpYoshi2() {
	dEn_c *koopa = (dEn_c*)fBase_c::search(EN_NOKONOKO, 0);
	nw4r::db::Exception_Printf_("Let's try fucking up Yoshi ! \n");
	daPlBase_c *yoshi = (daPlBase_c*)fBase_c::search(YOSHI, 0);
	koopa->_vf220(yoshi);
	nw4r::db::Exception_Printf_("Yoshi fucked up. Yay.\n");
}

extern "C" void StartAnimOrig(dPlayerModelBase_c *_this, int id, float updateRate, float unk, float frame);
extern "C" void YoshiStartAnimWrapper(dPlayerModelBase_c *_this, int id, float updateRate, float unk, float frame) {
	nw4r::db::Exception_Printf_("[%d] anim %d (%f, %f, %f)\n", GlobalTickCount, id, updateRate, unk, frame);
	StartAnimOrig(_this, id, updateRate, unk, frame);
}
extern "C" void YoshiStateOrig(daPlBase_c *_this, dStateBase_c *state, void *param);
extern "C" void YoshiStateWrapper(daPlBase_c *_this, dStateBase_c *state, void *param) {
	nw4r::db::Exception_Printf_("[%d] %s,%p\n", GlobalTickCount, state->getName(), param);
	YoshiStateOrig(_this, state, param);
}
*/


extern "C" int GetGameLanguage(int nyeh); //nyeh is always 4 for some reasons

//Enormous thanks to kinoko (from the NewerSMBW Translation Team), aoinfonr (from r/translator) and 南無さん (from discord) for the japanese translation !

const wchar_t *level1names[] = {
	L"クリボーあるく すなはま",
	L"たいようサンサン とざん びより",
	L"ドクドクぬまの うごくだいち",
	L"ゆらゆらゆれる ブランコのもり",
	L"せんりつ テレサクルーズ",
	L"かぜ ふきあれる いせき",
	L"はしれ ！ はしれ ！ はしれ ！ "
};
const wchar_t *level2names[] = {
	L"ふりそそぐ ゆきと かざんだん",
	L"ひびくばくおん ボムへいどうくつ",
	L"うすやみにひかるおばけやしき",
	L"しずむ テレサのかくれざと",
	L"ながれるこおりで マグマくだり",
	L"ながれ ながされ すいぼつせん",
	L"すべれ ！ すべれ ！ すべれ ！ "
};
const wchar_t *level3names[] = {
	L"ぶきみなやまみち",
	L"きけん ！ てつばこじごく",
	L"グツグツ ようがんのみずうみ",
	L"あぶないガケわたり",
	L"かなあみと クサリの だいくうどう",
	L"たいけつ ！ さいはてのとう",
	L"のぼれ ！ のぼれ ！ のぼれ ！ "
};
const wchar_t *level4names[] = {
	L"きめろ ！ ふみだいとびエキスパート"
};
const wchar_t *worldnames[] = {
	L"ノコノコへいや",
	L"とけゆくこおりのたに",
	L"じごくれんざん",
	L"おまけワールド"
};

int ConvertEnglishToJapanese(wchar_t *output, int world, int level, int outputLength) {
	if(GetGameLanguage(4) == 0) {
		if(world == 0) {
			wcscpy(output, level1names[level]);
		}
		if(world == 1) {
			wcscpy(output, level2names[level]);
		}
		if(world == 2) {
			wcscpy(output, level3names[level]);
		}
		if(world == 3) {
			wcscpy(output, level4names[level]);
		}
		return wcslen(output);
	}
	else {
		return outputLength;
	}
}

void ConvertEnglishToJapanese(wchar_t *output, int world, int level) {
	if(GetGameLanguage(4) == 0) {
		if(world == 0) {
			wcscpy(output, level1names[level]);
		}
		if(world == 1) {
			wcscpy(output, level2names[level]);
		}
		if(world == 2) {
			wcscpy(output, level3names[level]);
		}
		if(world == 3) {
			wcscpy(output, level4names[level]);
		}
	}
}


void WriteJPWorldNameToTextBox(nw4r::lyt::TextBox *tb, int world) {
	tb->SetString(worldnames[world]);
}

void GetJapaneseWorldName(wchar_t *output, int world) {
	wcscpy(output, worldnames[world]);
}


void WriteAsciiToTextBox(nw4r::lyt::TextBox *tb, const char *source) {
	int i = 0;
	wchar_t buffer[1024];
	while (i < 1023 && source[i]) {
		buffer[i] = (unsigned char)(source[i]);
		i++;
	}
	buffer[i] = 0;

	tb->SetString(buffer);
}

#include "levelinfo.h"
#include "worldnames.h"

void WriteLevelNameToTextBox(nw4r::lyt::TextBox *tb, int world, int level) {
	dLevelInfo_c *levelInfo = &dLevelInfo_c::s_info;
	dLevelInfo_c::entry_s *infEntry = levelInfo->searchBySlot(world, level);

	const char *source = levelInfo->getNameForLevel(infEntry);

	int i = 0;
	wchar_t buffer[1024];
	while (i < 1023 && source[i]) {
		buffer[i] = (unsigned char)(source[i]);
		i++;
	}
	buffer[i] = 0;

	ConvertEnglishToJapanese(buffer, world, level);
	tb->SetString(buffer);
}


void WriteWorldNameToTextBox(nw4r::lyt::TextBox *tb, int world) {
	if(GetGameLanguage(4) != 0) {
		dWorldNames_c *worldNamesList = &dWorldNames_c::s_info;
		// OSReport("SC search for %d-%d\n", world, GetGameLanguage(4));
		dWorldNames_c::entry_s *singleWorldName = worldNamesList->searchBySlot(world-1, GetGameLanguage(4)-1);
		// OSReport("Found %d-%d: %s\n", singleWorldName->worldSlot+1, singleWorldName->levelSlot+1, worldNamesList->getNameForLevel(singleWorldName));
		WriteAsciiToTextBox(tb, worldNamesList->getNameForLevel(singleWorldName));
	}
	else {
		WriteJPWorldNameToTextBox(tb, world-1);
	}
}


void getNewerLevelNumberString(int world, int level, wchar_t *dest) {
	static const wchar_t *numberKinds[] = {
		// 0-19 are handled by code
		// To insert a picturefont character:
		// \x0B\x01YY\xZZZZ
		// YY is the character code, ZZZZ is ignored
		L"F", // 20, final
		L"\x0B\x0148\xBEEF", // 21, tower
		L"\x0B\x0148\xBEEF" L"2", // 22, tower 2
		L"\x0B\x012E\xBEEF", // 23, castle
		L"\x0B\x012F\xBEEF", // 24, fortress
		L"\x0B\x013D\xBEEF", // 25, final castle
		L"\x0B\x014D\xBEEF", // 26, train
		L"\x0B\x0132\xBEEF", // 27, airship
		((GetGameLanguage(4) == 0) ? L"ボーナス" : L"Bonus"), // 28, Bonus levels
		L"\x0B\x0147\xBEEF", // 29, yoshi's house
		L"\x0B\x014E\xBEEF" L"1", // 30, key 1
		L"\x0B\x014E\xBEEF" L"2", // 31, key 2
		L"\x0B\x014E\xBEEF" L"3", // 32, key 3
		L"\x0B\x014E\xBEEF" L"4", // 33, key 4
		L"\x0B\x014E\xBEEF" L"5", // 34, key 5
		L"\x0B\x014E\xBEEF" L"6", // 35, key 6
		L"\x0B\x0138\xBEEF", // 36, music house
		L"\x0B\x0133\xBEEF", // 37, shop
		L"\x0B\x0139\xBEEF", // 38, challenge house
		L"\x0B\x0151\xBEEF", // 39, red switch palace
		L"\x0B\x0152\xBEEF", // 40, blue switch palace
		L"\x0B\x0153\xBEEF", // 41, yellow switch palace
		L"\x0B\x0154\xBEEF", // 42, green switch palace
	};

	dest[0] = (world >= 10) ? (world-10+'A') : (world+'0');
	dest[1] = '-';
	if (level >= 20) {
		wcscpy(&dest[2], numberKinds[level-20]);
	} else if (level >= 10) {
		dest[2] = '1';
		dest[3] = ('0' - 10) + level;
		dest[4] = 0;
	} else {
		dest[2] = '0' + level;
		dest[3] = 0;
	}
}

int getUnspentStarCoinCount() {
	SaveBlock *save = GetSaveFile()->GetBlock(-1);
	int coinsSpent = save->spentStarCoins;
	return getStarCoinCount() - coinsSpent;
}

int getStarCoinCount() {
	SaveBlock *save = GetSaveFile()->GetBlock(-1);
	int coinsEarned = 0;

	for (int w = 0; w < 10; w++) {
		for (int l = 0; l < 42; l++) {
			u32 conds = save->GetLevelCondition(w, l);

			if (conds & COND_COIN1) { coinsEarned++; }
			if (conds & COND_COIN2) { coinsEarned++; }
			if (conds & COND_COIN3) { coinsEarned++; }
		}
	}

	return coinsEarned;
}

struct GEIFS {
	int starCoins, exits;
};
extern "C" GEIFS *GrabExitInfoForFileSelect(GEIFS *out, SaveBlock *save) {
	out->starCoins = 0;
	out->exits = 0;

	for (int i = 0; i < dLevelInfo_c::s_info.sectionCount(); i++) {
		dLevelInfo_c::section_s *section = dLevelInfo_c::s_info.getSectionByIndex(i);

		for (int j = 0; j < section->levelCount; j++) {
			dLevelInfo_c::entry_s *l = &section->levels[j];
			if (l->flags & 2) {
				//OSReport("Checking %d-%d...\n", l->worldSlot+1, l->levelSlot+1);
				u32 cond = save->GetLevelCondition(l->worldSlot, l->levelSlot);
				if ((l->flags & 0x10) && (cond & COND_NORMAL))
					out->exits++;
				if ((l->flags & 0x20) && (cond & COND_SECRET))
					out->exits++;
				if (cond & COND_COIN1)
					out->starCoins++;
				if (cond & COND_COIN2)
					out->starCoins++;
				if (cond & COND_COIN3)
					out->starCoins++;
			}
		}
	}

	OSReport("Done, got %d coins and %d exits\n", out->starCoins, out->exits);

	return out;
}


void Newer_WriteBMGToTextBox_VAList(nw4r::lyt::TextBox *textBox, dScript::Res_c *res, int category, int message, int argCount, va_list *args) {
	GameMgrP->layoutShadowFlag = false;
	if (textBox->GetExtUserDataNum())
		CheckForUSD1ShadowEntry(textBox);

	GameMgrP->msgCategory = category;
	GameMgrP->msgID = message;

	const wchar_t *str = res->findStringForMessageID(category, message);
	WriteParsedStringToTextBox(textBox, str, argCount, args, res);
}
void Newer_WriteBMGToTextBox(nw4r::lyt::TextBox *textBox, dScript::Res_c *res, int category, int message, int argCount, ...) {
	va_list vl;

	// from Clang lib/Headers/stdarg.h
	// Is this even interoperable with CodeWarrior's va_list?
	// Not sure, and I have a feeling that it's not.....

	__builtin_va_start(vl, argCount);

	Newer_WriteBMGToTextBox_VAList(textBox, res, category, message, argCount, &vl);

	__builtin_va_end(vl);
}
