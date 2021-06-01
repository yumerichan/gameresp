#pragma once

bool IsHitRect(int red_pos_x, int red_pos_y, int red_xw, int red_yw, int green_pos_x, int green_pos_y, int green_xw, int green_yw) {

	if ((red_pos_x + red_xw > green_pos_x) && (red_pos_x < green_pos_x + green_xw) &&
		(red_pos_y + red_yw > green_pos_y) && (red_pos_y < green_pos_y + green_yw)) {
		return true;
	}

	return false;
}


bool atari(int ax, int ay, int ahalf, int bx, int by, int bhalf) {

	int A1, A2, A, D;
	A1 = ((ax - bx));//ŠÔ‚Ì’·‚³
	A1 *= A1;
	A2 = ((ay - by));
	A2 *= A2;
	A = A1 + A2;

	D = ahalf + bhalf;
	D *= D;

	/*DrawFormatString(100, 50, GetColor(255, 255, 255), "A = %d,D = %d", A, D);*/

	if (D > A) {
		return true;
	}
	return false;
}