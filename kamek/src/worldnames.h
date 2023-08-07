#ifndef __NEWER_WORLDNAMES_H
#define __NEWER_WORLDNAMES_H

#include <game.h>

class dWorldNames_c {
public:
	struct header_s {
		u32 magic;
		u32 sectionCount;
		u32 sectionOffsets[1];
	};

	struct entry_s {
		u8 worldSlot;
		u8 levelSlot;
		u8 displayWorld;
		u8 displayLevel;
		u8 nameLength;
		u8 reserved3;
		u16 flags;
		u32 nameOffset;
	};

	struct section_s {
		u32 levelCount;
		entry_s levels[1];
	};

private:
	header_s *data;

public:
	void load(void *buffer);

	entry_s *searchBySlot(int world, int level);
	entry_s *searchByDisplayNum(int world, int level);

	u32 sectionCount() {
		return data->sectionCount;
	}

	section_s *getSectionByIndex(u32 index) {
		return (section_s*)(((char*)data) + data->sectionOffsets[index]);
	}

	const char *getNameForLevel(entry_s *entry) {
		return (const char*)data + entry->nameOffset;
	}

	static dWorldNames_c s_info;
};


#endif

