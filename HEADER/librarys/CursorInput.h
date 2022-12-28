/*
커서 함수 헤더

헤더 순도 : D등급.
*/


unsigned char __cursor_pointer = '_';
int __cursor_xmin = 0, __cursor_xmax = SCWIDTH - 1;
int __cursor_ymin = 0, __cursor_ymax = SCHEIGHT - 1;
int __cursor_x = 0;
int __cursor_y = 0;
unsigned long __cursor_timer = 0;
int __cursor_blink = 350;
unsigned char __cursor_start = 0;


void cursorMove(int x, int y) {  // Ŀ���� ��ġ�� ������ ��ġ�� �̵���Ų��. Ŀ�� ��ġ���� �ٲ�.

	if (x > __cursor_xmax) x = __cursor_xmax;
	else if (x < __cursor_xmin) x = __cursor_xmin;
	
	if (y > __cursor_ymax) y = __cursor_ymax;
	else if (y < __cursor_ymin) y = __cursor_ymin;
	
	__cursor_x = x;
	__cursor_y = y;
}

void cursorUpdate() {  // Ŀ���� ���� ��ġ���� ������ ȭ�� ���ۿ� �׸�.
	static unsigned char blink = 2;
	if (!__cursor_start) {
		__cursor_x = __cursor_xmin;
		__cursor_y = __cursor_ymin;
		__cursor_start = 1;
	}

	if (clock_ms() > __cursor_timer + __cursor_blink) {
		blink = blink?0:2;
		__cursor_timer = clock_ms();
	}
	
	if ( blink ) {
		if ( blink == 2 ) {
			blink = 1;
		}
		screenDot(__cursor_pointer, __cursor_x, __cursor_y);
	}

}

unsigned char cursorHover(int x1, int y1, int x2, int y2) {  // Ŀ���� ��ġ�� ������ ��ġ�� ���ԵǾ��ִ��� �˻�.
	return (__cursor_x <= (x2 >= x1 ? x2 : x1) && __cursor_x >= (x1 < x2 ? x1 : x2) && __cursor_y <= (y2 >= y1 ? y2 : y1) && __cursor_y >= (y1 < y2 ? y1 : y2));
}

