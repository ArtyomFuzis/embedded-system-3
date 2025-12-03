#include <stdlib.h>
#include "tetr.h"
//drawSq
//drawLine1
//drawLine2
//drawL
void unplace_figure(struct TetrEntity entity){
	for(int i = 0 ; i < 4 ; i++){
		field[entity.blocks[i].x][entity.blocks[i].y] = 0x0;
	}
}

int place_figure(struct TetrEntity entity){
	for(int i = 0 ; i < 4 ; i++){
		if(field[entity.blocks[i].x][entity.blocks[i].y] == 0x1){
			return 1;
		}
	}
	for(int i = 0 ; i < 4 ; i++){
		field[entity.blocks[i].x][entity.blocks[i].y] = 0x1;
	}
	return 0;
}

int rotate_figure(struct TetrEntity entity, enum TetrRotate rotate){
	switch(entity.figure){
	case TFig:
		if(rotate == Tetr0){

		} else if(rotate == Tetr90){

		}
		break;
	}
}

int move_left_figure(struct TetrEntity entity){
	unplace_figure(*entity);
	for(int i = 0 ; i < 4; i++){
		entity->blocks[i].y--;
	}
	int res = place_figure(*entity);
	if(res){
		for(int i = 0 ; i < 4; i++){
			entity->blocks[i].y++;
		}
		place_figure(*entity);
	}
	return res;
}

int move_right_figure(struct TetrEntity entity){
	unplace_figure(*entity);
	for(int i = 0 ; i < 4; i++){
		entity->blocks[i].y++;
	}
	int res = place_figure(*entity);
	if(res){
		for(int i = 0 ; i < 4; i++){
			entity->blocks[i].y--;
		}
		place_figure(*entity);
	}
	return res;
}

int move_down_figure(struct TetrEntity *entity){
	unplace_figure(*entity);
	for(int i = 0 ; i < 4; i++){
		entity->blocks[i].x--;
	}
	int res = place_figure(*entity);
	if(res){
		for(int i = 0 ; i < 4; i++){
			entity->blocks[i].x++;
		}
		place_figure(*entity);
	}
	return res;
}

struct TetrGenerateReturn generate_figure(){
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
	return (struct TetrGenerateReturn){entity,place_figure(entity)};
}

