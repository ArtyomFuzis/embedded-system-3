#include <stdlib.h>
#include "tetr.h"
//drawSq
//drawLine1
//drawLine2
//drawL
int place_figure(struct TetrEntity entity){
	for(int i = 0 ; i < 4 ; i++){
		if(field[entity.blocks[i].x][entity.blocks[i].y] == 0x1){
			return 1;
		}
		else field[entity.blocks[i].x][entity.blocks[i].y] = 0x1;
	}
	return 0;
}

int generateFigure(){
	int fig_id = rand() % 7;
	struct TetrEntity entity;
	entity.rotate = Tetr0;
	switch(fig_id){
	case 0:
		entity.figure = TFig;
		entity.blocks[0] = (struct TetrBlock){BASE_WIDTH, BASE_HEIGHT};
		entity.blocks[1] = (struct TetrBlock){BASE_WIDTH-1, BASE_HEIGHT};
		entity.blocks[2] = (struct TetrBlock){BASE_WIDTH-1, BASE_HEIGHT-1};
		entity.blocks[3] = (struct TetrBlock){BASE_WIDTH-1, BASE_HEIGHT+1};
		break;
	case 1:
		entity.figure = LFig;
		entity.blocks[0] = (struct TetrBlock){BASE_WIDTH, BASE_HEIGHT};
		entity.blocks[1] = (struct TetrBlock){BASE_WIDTH-1, BASE_HEIGHT};
		entity.blocks[2] = (struct TetrBlock){BASE_WIDTH-2, BASE_HEIGHT};
		entity.blocks[3] = (struct TetrBlock){BASE_WIDTH-3, BASE_HEIGHT};
		break;
	case 2:
		entity.figure = L1Fig;
		entity.blocks[0] = (struct TetrBlock){BASE_WIDTH, BASE_HEIGHT};
		entity.blocks[1] = (struct TetrBlock){BASE_WIDTH-1, BASE_HEIGHT};
		entity.blocks[2] = (struct TetrBlock){BASE_WIDTH-2, BASE_HEIGHT};
		entity.blocks[3] = (struct TetrBlock){BASE_WIDTH-2, BASE_HEIGHT+1};
		break;
	case 3:
		entity.figure = L2Fig;
		entity.blocks[0] = (struct TetrBlock){BASE_WIDTH, BASE_HEIGHT};
		entity.blocks[1] = (struct TetrBlock){BASE_WIDTH-1, BASE_HEIGHT};
		entity.blocks[2] = (struct TetrBlock){BASE_WIDTH-2, BASE_HEIGHT};
		entity.blocks[3] = (struct TetrBlock){BASE_WIDTH-2, BASE_HEIGHT-1};
		break;
	case 4:
		entity.figure = SFig;
		entity.blocks[0] = (struct TetrBlock){BASE_WIDTH, BASE_HEIGHT};
		entity.blocks[1] = (struct TetrBlock){BASE_WIDTH-1, BASE_HEIGHT};
		entity.blocks[2] = (struct TetrBlock){BASE_WIDTH-1, BASE_HEIGHT+1};
		entity.blocks[3] = (struct TetrBlock){BASE_WIDTH, BASE_HEIGHT+1};
		break;
	case 5:
		entity.figure = Z1Fig;
		entity.blocks[0] = (struct TetrBlock){BASE_WIDTH, BASE_HEIGHT};
		entity.blocks[1] = (struct TetrBlock){BASE_WIDTH-1, BASE_HEIGHT};
		entity.blocks[2] = (struct TetrBlock){BASE_WIDTH-1, BASE_HEIGHT+1};
		entity.blocks[3] = (struct TetrBlock){BASE_WIDTH, BASE_HEIGHT-1};
		break;
	case 6:
		entity.figure = Z2Fig;
		entity.blocks[0] = (struct TetrBlock){BASE_WIDTH, BASE_HEIGHT};
		entity.blocks[1] = (struct TetrBlock){BASE_WIDTH-1, BASE_HEIGHT};
		entity.blocks[2] = (struct TetrBlock){BASE_WIDTH-1, BASE_HEIGHT-1};
		entity.blocks[3] = (struct TetrBlock){BASE_WIDTH, BASE_HEIGHT+1};
		break;
	}
	return place_figure(entity);
}


