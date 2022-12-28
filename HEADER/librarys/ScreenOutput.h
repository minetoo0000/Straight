/*
�솕硫� �븿�닔 �뿤�뜑

�뿤�뜑 �닚�룄 : B�벑湲�.
*/

#define SCWIDTH 150
#define SCHEIGHT 80

const int __screen_width = SCWIDTH;
const int __screen_height = SCHEIGHT;
const int __screen_bf_len = SCHEIGHT*SCWIDTH+SCHEIGHT;
char* __cursor_nonespace = "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
unsigned char __screen_bf[SCWIDTH*SCHEIGHT+SCHEIGHT] = {0};



// ��ǥ ��ü.
typedef struct type$class_TGI$pos_t
{
    int16_t x;
    int16_t y;
} pos_t;

// ������ ��ü.
typedef struct type$class_TGI$poly_obj_t
{
    pos_t* poly_dots;
    uint32_t length;
} poly_obj_t;

// �� �׸� ��ü.
typedef struct type$class_TGI$line_set_t
{
	enum Move_mode
	{
		Draw, Move
	} pen_mode;
	uint8_t dot;
	int16_t move_x;
	int16_t move_y;
} line_set_t;
typedef struct type$class_TGI$draw_tool_obj_t
{
	uint16_t length;
	line_set_t* line_set;
} draw_tool_obj_t;


//* 湲고�� *//
unsigned long xy2Index(int x, int y) {
	//////////////////////////////////����� �׽�Ʈ
	// if ( (x>=__screen_width || x<0) || (y>=__screen_height || y<0) ) return 0;
	if ( (x>=__screen_width || x<0) || (y>=__screen_height || y<0) )
	{
		// printf("\n low level debug, x : %d, y : %d\n", x, y);
		// while(!_kbhit());
		return 0;
	}
	return (__screen_width+1)*(__screen_height-1-y)+x;
}

//* 湲곕?�� �븿�닔 - ?��?��린�?��, 洹몃?��湲�, �뾽�뜲�씠�듃*//
void screenBegin() {  // �솕硫� ?��?��?��??�� �엯�젰 �옉�뾽�쓣 �븯湲� �쟾�뿉 �솕硫� 踰꾪?��?���? �궗�슜�븷 �닔 �엳�뒗 �긽�깭濡� ?��?��린�?�� �븯湲� �읞�븳 �븿�닔.
	int loop = __screen_bf_len-1;
	for (int index=0; index<loop; index++) {
        __screen_bf[index] = ((index+1)%(__screen_width+1))?' ':'\n';  
    }
    __screen_bf[loop] = '\0';
}

void screenDot(unsigned char ch, int x, int y) {  // �솕硫� 踰꾪?���뿉 �빝�떦�븯�뒗 �읞移석�? ?��몄옄 �븯�굹?���? 踰꾪?���뿉 �뜮�뼱 ���?.
    if ( (xy2Index(x, y) != -1) && ( __screen_bf[xy2Index(x, y)] = ch ) );
    
}

void screenFill(char ch) {  // �솕硫� 踰꾪?��?���? �빝�떦�븯�뒗 ?��몄옄濡� 利⑤�? �?꾩��?.
    int loop = __screen_bf_len-1;
    for (int index=0; index<loop; index++) {
        ((index+1)%(__screen_width+1))?(__screen_bf[index]=ch):0;
    }
}

int screenUpdate() {  // �솕硫� 踰꾪?���쓽 �뜲�씠�꽣?���? ?��?��?��李쎌�? ?��?��?���븿.
    // printf(__cursor_nonespace);
    // printf(__cursor_nonespace);
    // printf(__cursor_nonespace);
    puts(__cursor_nonespace);
    puts(__screen_bf);
}


//* 吏곸�? �븿�닔 *//
void screenYline(const char ch, const int x, const int y, const int len) {  // Y?��뺤뿉 �룊�뻾�븳 �꽑?��꾩쓣 洹몃?��.
    for (int line=0; line<len; line++) {
        screenDot(ch, x, y+line);
    }
}

void screenXline(const char ch, const int x, const int y, const int len) {  // X?��뺤뿉 �룊�뻾�븳 �꽑?��꾩쓣 洹몃?��.
    for (int line=0; line<len; line++) {
        screenDot(ch, x+line, y);
    }
}

void screenLine(const char ch, int x1, int y1,  int x2, int y2) {  // �몢 �젝�쓣 �뿰寃고�?�뒗 �꽑?��꾩쓣 洹몃?��.

	int upY = (y2-y1), upX = (x2-x1);  // x, y利앷���웾.
	
	if (!upX) {  // x利앷���웾�씠 0�씤 寃쎌?��, y?��뺤뿉 �룊�뻾�븳 �꽑?��꾩쓣 洹몃?��.
		int ymin = y2 < y1 ? y2 : y1;
		screenYline(ch, x1, ymin, abs(y2-y1));
	}
	else if (!upY) {
		int xmin = x2 < x1 ? x2 : x1;
		screenXline(ch, xmin, y1, abs(x2-x1));
	}
	
	else if ( abs(y2-y1) >= abs(x2-x1) ) {
		double up = fabs( (double)upX / upY )-0.001;
		int xmax = x1 > x2 ? x1 : x2;
		int xmin = x2 < x1 ? x2 : x1;
		double yxM = (double)upY / upX;  // (y利�/x利�) 湲곗?��湲�.
		
		for (double X=xmin; X<=xmax; X+=up) {
			screenDot(ch, (int)X, ( (yxM*X)+( y1-(yxM*x1) ) ));
			
		}
		
	}
	else if ( abs(y2-y1) < abs(x2-x1) ) {
		double up = fabs( (double)upY / upX )-0.001;
		int ymax = y1 > y2 ? y1 : y2;
		int ymin = y2 < y1 ? y2 : y1;
		double xyM = (double)upX / upY;  // (x利�/y利�) 湲곗?��湲�.
		
		for (double Y=ymin; Y<=ymax; Y+=up) {
			screenDot(ch, ( (xyM*Y)+( x1-(xyM*y1) ) ), (int)Y);
		}
		
	}
	
}




//* �룄�삎 �븿�닔 *//
void screenBorder(const char ch, const int x1, const int y1, const int x2, const int y2) {  // �궗媛곹?���쓽 ��?��몢由?���? 洹몃?��.
    screenYline(ch, x1, y1, y2-y1);
	screenXline(ch, x1+1, y1, x2-x1);
	screenYline(ch, x2, y1+1, y2-y1);
	screenXline(ch, x1, y2, x2-x1);
}


//* ?��몄옄 ?��?��?�� �븿�닔 *//
// void screenPrint(const char* const str, const int x, const int y) {  // ONLY ASCII CODE
// 	strncpy(__screen_bf+xy2Index(x,y), str, strlen(str));
// }
void screenPrint(const int x, const int y, uint16_t column, ...)
{
	for ( uint16_t index=0; index<column; index++ )
	{
		const uint8_t* const str = getProp(column, const uint8_t* const, index);
		strncpy(__screen_bf+xy2Index(x,y+(column-1)-index), str, strlen(str));
	}
}

// ������ �׸���.
void screenPoly( const uint8_t dot, const poly_obj_t* const poly )
{
    for ( uint32_t index=0; index<poly->length-1; index++ )
    {
        screenLine(dot, poly->poly_dots[index].x, poly->poly_dots[index].y,  poly->poly_dots[index+1].x, poly->poly_dots[index+1].y);
    }
}

// �� �׸��� ��.
void screenDrawTool( const draw_tool_obj_t draw, volatile const uint16_t start_pos_x, volatile const uint16_t start_pos_y )
{
	// ���� ��ġ ��� ����.
	volatile int16_t current_x = start_pos_x;
	volatile int16_t current_y = start_pos_y;

	for ( uint16_t index=0; index<draw.length; index++ )
	{
		// ���� ���� �����̴� ���.
		if ( draw.line_set[index].pen_mode == Draw )
		{
			screenLine(
				draw.line_set[index].dot,
				current_x+=draw.line_set[index].move_x,
				current_y+=draw.line_set[index].move_y,
				current_x,
				current_y
			);
		}
		// ���� ���� �����̴� ���.
		else if ( draw.line_set[index].pen_mode == Move )
		{
			current_x += draw.line_set[index].move_x;
			current_y += draw.line_set[index].move_y;
		}

	}
}