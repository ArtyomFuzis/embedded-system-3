#include "shared.h"

int field[FIELD_WIDTH][FIELD_HEIGHT];

void initSharedMem(){
	for(int i = 0 ; i < FIELD_WIDTH; i++){
		for(int j = 0 ; j < FIELD_HEIGHT; j++){
			field[i][j] = 0x0;
		}
	}
	for(int j = 0 ; j < FIELD_HEIGHT; j++){
		field[0][j] = 0x1;
	}
	for(int j = 0 ; j < FIELD_HEIGHT; j++){
			field[1][j] = 0x1;
		}
	for(int i = 0 ; i < FIELD_WIDTH; i++){
		field[i][0] = 0x1;
	}
	for(int i = 0 ; i < FIELD_WIDTH; i++){
		field[i][FIELD_HEIGHT-1] = 0x1;
	}
	for(int i = 0 ; i < FIELD_WIDTH; i++){
		field[i][1] = 0x1;
	}
	for(int i = 0 ; i < FIELD_WIDTH; i++){
		field[i][FIELD_HEIGHT-2] = 0x1;
	}
}
