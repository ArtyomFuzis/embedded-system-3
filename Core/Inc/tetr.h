
#ifndef INC_TETR_H_
#define INC_TETR_H_
#include "shared.h"

#define BASE_HEIGHT 7
#define BASE_WIDTH FIELD_WIDTH-2

enum TetrFigure{
	TFig,
	L1Fig,
	L2Fig,
	Z1Fig,
	Z2Fig,
	SFig,
	LFig
};


struct TetrBlock{
	int x;
	int y;
};

enum TetrRotate{
	Tetr0,
	Tetr90,
	Tetr180,
	Tetr270
};

struct TetrEntity{
	enum TetrFigure figure;
	enum TetrRotate rotate;
	struct TetrBlock blocks [4];
};

struct TetrGenerateReturn{
	struct TetrEntity entity;
	int result;
};


struct TetrGenerateReturn generate_figure();
int move_down_figure(struct TetrEntity *entity);


#endif
