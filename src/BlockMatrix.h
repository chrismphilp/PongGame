#pragma once

#include "Block.h"

class BlockMatrix {
	public:
		Block* arrayBlock;
		int x_rows;
		int y_columns;
		int block_probability; // 1-100

		BlockMatrix(int x_rows, int y_columns, int block_probability) :
			blockArray(new Block[x_rows][y_columns]),
			block_probability(block_probability)
		{}

		initiliaseBricks() {
			for (int x = 0; x < x_rows; x++) {
				for (int y = 0; y < y_columns; y++) {
					blockArray[x][y] = new Block(1, 10, 20);
				}
			}
		}
};
