#pragma once
#include <string.h>
/*
���� �Լ� ���.

������� : B���.
*/
signed char __DEBUG_MODE = 1;

/* ���� �Լ� */
double sinEX(float speed, float min_num, float max_num, long long upbit, unsigned char absis) {  // ???, ???, ??????? ?????? ?? ??? ???? ??? ???.
    return absis ? min_num + ceil( fabs( sin( upbit / speed ) * (max_num-min_num) ) ) : min_num + ceil( sin( upbit / speed ) * (max_num-min_num) );
}

int64_t sinEx( int64_t start, int64_t end, double deg )
{
	return ( start + ( ( fabs(sin(deg)) * (end-start) ) ) + 0.5 );  // 0���� 1����.
	// return ( start + ( ( (sin(deg+1.570796)*-1.0+1.0)/2.0 * (end-start) ) ) + 0.5 );  // 1���� -1���� -> 0���� 1����.
	// return ( start + ( ( fabs(1.0-cos(upbit)) * (end-start) ) ) );
}

double cosEX(float speed, float min_num, float max_num, long long upbit, unsigned char absis) {  // ???, ???, ??????? ?????? ?? ??? ????? ??? ???.
    return absis ? min_num + ceil( fabs( cos( upbit / speed ) * (max_num-min_num) ) ) : min_num + ceil( cos( upbit / speed ) * (max_num-min_num) );
}

double distanceDot(float x1, float y1, float x2, float y2) {
	return sqrt( pow(x2-x1, x2-x1) + pow(y2-y1, y2-y1) );
}

double inclinationLine(float x1, float y1,  float x2, float y2) {
	return (y2-y1) / (x2-x1);
}

double distanceLineDot(float lineX1, float lineY1, float lineX2, float lineY2,  float dotX, float dotY) {
	return fabs( (( lineY2-lineY1 )*dotX) - (dotY) + ( lineY1-( ((double)(lineY2-lineY1)/(lineX2-lineX1))*lineX1 ) ) );
}

unsigned short fps2delay(unsigned char fps) {
	return 1000 / fps;
}

#include <time.h>

clock_t clock_ms() {  // ?????? ??? clock()???? ????? ?????? ??�� ???? ?��??? ?????? ????? ?????? ???? ??? ?????? ???? ???? ??????.
	return clock() / ( (clock_t)CLOCKS_PER_SEC / (clock_t)1000 );
}

void delay(unsigned long long wait) {  // ?????? ???.
    clock_t _time = clock_ms();
    while (clock_ms()-_time<wait);
}

void printAnimation(char* str)
{
	for ( uint32_t index=0; str[index]; index++ )
	{
		putch(str[index]);
		delay(100);
	}
}

void printfAnimationEUCKR( char* KO_str )
{
	// printf("%s", KO_str);
	for ( uint32_t index=0; index<10; index+=2 )
	{
		char buf[256] = {0};
		char *buf_ptr = buf;
		strcpy(buf_ptr, KO_str);/////// �����ͽἭ ����
		(buf_ptr+=index)[2] = 0;
		// printf(buf_ptr );
		delay(100);
	}
}

typedef struct _Point
{
    int x;
    int y;
} Point;

typedef struct _Line
{
    Point point1;
    Point point2;
} Line;

int getLinePos(int x1, int y1,  int x2, int y2, int getX, int getY) {  // �� ���� �����ϴ� ������ �׸�.

	uint8_t output_mode = 0; // 0 : X ��ȯ�Ұ�. 1: Y ��ȯ��.
	if ( getX == -1 && getY >= 0 )
	{	// getY�� ���� ��� X ��ȯ.
		output_mode = 0;
	}
	else if ( getY == -1 && getX >= 0 )
	{	// getX�� ���� ��� Y��ȯ.
		output_mode = 1;
	}

	const int upY = (y2-y1);
	const int upX = (x2-x1);  // x, y������.
	
	if (!upX) {  // x�������� 0�� ���, y�࿡ ������ ������ �׸�.
		int ymin = y2 < y1 ? y2 : y1;
		return( output_mode==1 ? 0 : x1 );
	}
	else if (!upY) {  // X�࿡ ������ ����.
		int xmin = x2 < x1 ? x2 : x1;
		return( output_mode==1 ? y1 : 0 );
	}
	
	else if ( abs(upY) >= abs(upX) ) {
		double up = fabs( (double)upX / upY )-0.001;
		int xmax = x1 > x2 ? x1 : x2;
		int xmin = x2 < x1 ? x2 : x1;
		double yxM = (double)upY / upX;  // (y��/x��) ����.

		
		for (double X=xmin; (int)X<=xmax; X+=up) {
			if ( output_mode == 1 )
			{	// Y���� ��ȯ�ؾ��ϴ� ���.
				if ( ((int)X) == getX )
				{
					return(int)( (yxM*X)+( y1-(yxM*x1) ) );
				}
			}
			else if ( output_mode == 0 )
			{	// X�� ��ȯ�ؾ��ϴ� ���.
				if ( (int)( (yxM*X)+( y1-(yxM*x1) ) ) == getY )
				{
					return( (int)X );
				}
			}
		}
		
	}
	else if ( abs(upY) < abs(upX) ) {
		double up = fabs( (double)upY / upX )-0.001;
		int ymax = y1 > y2 ? y1 : y2;
		int ymin = y2 < y1 ? y2 : y1;
		double xyM = (double)upX / upY;  // (x��/y��) ����.
		
		for (double Y=ymin; (int)Y<=ymax; Y+=up) {
			if ( output_mode == 1 )
			{	// Y���� ��ȯ�ؾ��ϴ� ���.
				if ( getX == (int)( (xyM*Y)+( x1-(xyM*y1) ) ) )
				{
					return( (int)Y );
				}
			}
			else if ( output_mode == 0 )
			{	// X���� ��ȯ�ؾ��ϴ� ���.
				if ( getY == ((int)Y) )
				{
					return(int)( (xyM*Y)+( x1-(xyM*y1) ) );
				}
			}
		}
		
	}
	return( 0 );
}
