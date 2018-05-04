#pragma once

#include "Block.h"

class BlockMatrix {
	public:
		Block blockArray[10][10];
		float block_width;
		float block_height;
		int x_matrix_origin;
		int y_matrix_origin;
		int x_matrix_max;
		int y_matrix_max;
		int block_probability; // 1-100

		BlockMatrix(float block_width, float block_height, int x_matrix_origin, int y_matrix_origin, int x_matrix_max, 
			int y_matrix_max, int block_probability) :
			block_width(block_width),
			block_height(block_height),
			x_matrix_origin(x_matrix_origin),
			y_matrix_origin(y_matrix_origin),
			x_matrix_max(x_matrix_max),
			y_matrix_max(y_matrix_max),
			block_probability(block_probability)
		{}

		void initiliaseBricks(void) {
			for (int x = 0; x < 10; x++) {
				for (int y = 0; y < 10; y++) {
					blockArray[x][y].setValues(block_width, block_height, x_matrix_origin+(x*55), y_matrix_origin+(y*15), 1);
				}
			}
		}
};
