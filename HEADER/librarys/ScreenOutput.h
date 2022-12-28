/*
ï¿½ì†•ï§Žï¿½ ï¿½ë¸¿ï¿½ë‹” ï¿½ë¿¤ï¿½ëœ‘

ï¿½ë¿¤ï¿½ëœ‘ ï¿½ë‹šï¿½ë£„ : Bï¿½ë²‘æ¹²ï¿½.
*/

#define SCWIDTH 150
#define SCHEIGHT 80

const int __screen_width = SCWIDTH;
const int __screen_height = SCHEIGHT;
const int __screen_bf_len = SCHEIGHT*SCWIDTH+SCHEIGHT;
char* __cursor_nonespace = "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
unsigned char __screen_bf[SCWIDTH*SCHEIGHT+SCHEIGHT] = {0};



// ÁÂÇ¥ °´Ã¼.
typedef struct type$class_TGI$pos_t
{
    int16_t x;
    int16_t y;
} pos_t;

// Æú¸®°ï °´Ã¼.
typedef struct type$class_TGI$poly_obj_t
{
    pos_t* poly_dots;
    uint32_t length;
} poly_obj_t;

// Ææ ±×¸² °´Ã¼.
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


//* æ¹²ê³ ï¿½ï¿½ *//
unsigned long xy2Index(int x, int y) {
	//////////////////////////////////µð¹ö±ë Å×½ºÆ®
	// if ( (x>=__screen_width || x<0) || (y>=__screen_height || y<0) ) return 0;
	if ( (x>=__screen_width || x<0) || (y>=__screen_height || y<0) )
	{
		// printf("\n low level debug, x : %d, y : %d\n", x, y);
		// while(!_kbhit());
		return 0;
	}
	return (__screen_width+1)*(__screen_height-1-y)+x;
}

//* æ¹²ê³•?‚¯ ï¿½ë¸¿ï¿½ë‹” - ?¥?‡ë¦°ï¿½?†•, æ´¹ëªƒ?”æ¹²ï¿½, ï¿½ë¾½ï¿½ëœ²ï¿½ì” ï¿½ë“ƒ*//
void screenBegin() {  // ï¿½ì†•ï§Žï¿½ ?•°?’•? °??¨ï¿½ ï¿½ì—¯ï¿½ì ° ï¿½ì˜‰ï¿½ë¾½ï¿½ì“£ ï¿½ë¸¯æ¹²ï¿½ ï¿½ìŸ¾ï¿½ë¿‰ ï¿½ì†•ï§Žï¿½ è¸°ê¾ª??‘œï¿? ï¿½ê¶—ï¿½ìŠœï¿½ë¸· ï¿½ë‹” ï¿½ì—³ï¿½ë’— ï¿½ê¸½ï¿½ê¹­æ¿¡ï¿½ ?¥?‡ë¦°ï¿½?†• ï¿½ë¸¯æ¹²ï¿½ ï¿½ìžï¿½ë¸³ ï¿½ë¸¿ï¿½ë‹”.
	int loop = __screen_bf_len-1;
	for (int index=0; index<loop; index++) {
        __screen_bf[index] = ((index+1)%(__screen_width+1))?' ':'\n';  
    }
    __screen_bf[loop] = '\0';
}

void screenDot(unsigned char ch, int x, int y) {  // ï¿½ì†•ï§Žï¿½ è¸°ê¾ª?ï¿½ë¿‰ ï¿½ë¹ï¿½ë–¦ï¿½ë¸¯ï¿½ë’— ï¿½ìžç§»ì„ë¿? ?‡¾ëª„ì˜„ ï¿½ë¸¯ï¿½êµ¹?‘œï¿? è¸°ê¾ª?ï¿½ë¿‰ ï¿½ëœ®ï¿½ë¼± ï¿½ï¿½ï¿?.
    if ( (xy2Index(x, y) != -1) && ( __screen_bf[xy2Index(x, y)] = ch ) );
    
}

void screenFill(char ch) {  // ï¿½ì†•ï§Žï¿½ è¸°ê¾ª??‘œï¿? ï¿½ë¹ï¿½ë–¦ï¿½ë¸¯ï¿½ë’— ?‡¾ëª„ì˜„æ¿¡ï¿½ ï§â‘¤ëª? ï§?ê¾©ï¿½ï¿?.
    int loop = __screen_bf_len-1;
    for (int index=0; index<loop; index++) {
        ((index+1)%(__screen_width+1))?(__screen_bf[index]=ch):0;
    }
}

int screenUpdate() {  // ï¿½ì†•ï§Žï¿½ è¸°ê¾ª?ï¿½ì“½ ï¿½ëœ²ï¿½ì” ï¿½ê½£?‘œï¿? ?‚„?„?„„ï§¡ìŽŒë¿? ?•°?’•? °ï¿½ë¸¿.
    // printf(__cursor_nonespace);
    // printf(__cursor_nonespace);
    // printf(__cursor_nonespace);
    puts(__cursor_nonespace);
    puts(__screen_bf);
}


//* ï§žê³¸ê½? ï¿½ë¸¿ï¿½ë‹” *//
void screenYline(const char ch, const int x, const int y, const int len) {  // Y?•°ëº¤ë¿‰ ï¿½ë£Šï¿½ë»¾ï¿½ë¸³ ï¿½ê½‘?ºê¾©ì“£ æ´¹ëªƒ?”.
    for (int line=0; line<len; line++) {
        screenDot(ch, x, y+line);
    }
}

void screenXline(const char ch, const int x, const int y, const int len) {  // X?•°ëº¤ë¿‰ ï¿½ë£Šï¿½ë»¾ï¿½ë¸³ ï¿½ê½‘?ºê¾©ì“£ æ´¹ëªƒ?”.
    for (int line=0; line<len; line++) {
        screenDot(ch, x+line, y);
    }
}

void screenLine(const char ch, int x1, int y1,  int x2, int y2) {  // ï¿½ëª¢ ï¿½ì ï¿½ì“£ ï¿½ë¿°å¯ƒê³ ë¸?ï¿½ë’— ï¿½ê½‘?ºê¾©ì“£ æ´¹ëªƒ?”.

	int upY = (y2-y1), upX = (x2-x1);  // x, yï§ì•·ï¿½ï¿½ï¿½ì›¾.
	
	if (!upX) {  // xï§ì•·ï¿½ï¿½ï¿½ì›¾ï¿½ì”  0ï¿½ì”¤ å¯ƒìŽŒ?Š¦, y?•°ëº¤ë¿‰ ï¿½ë£Šï¿½ë»¾ï¿½ë¸³ ï¿½ê½‘?ºê¾©ì“£ æ´¹ëªƒ?”.
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
		double yxM = (double)upY / upX;  // (yï§ï¿½/xï§ï¿½) æ¹²ê³—?Š±æ¹²ï¿½.
		
		for (double X=xmin; X<=xmax; X+=up) {
			screenDot(ch, (int)X, ( (yxM*X)+( y1-(yxM*x1) ) ));
			
		}
		
	}
	else if ( abs(y2-y1) < abs(x2-x1) ) {
		double up = fabs( (double)upY / upX )-0.001;
		int ymax = y1 > y2 ? y1 : y2;
		int ymin = y2 < y1 ? y2 : y1;
		double xyM = (double)upX / upY;  // (xï§ï¿½/yï§ï¿½) æ¹²ê³—?Š±æ¹²ï¿½.
		
		for (double Y=ymin; Y<=ymax; Y+=up) {
			screenDot(ch, ( (xyM*Y)+( x1-(xyM*y1) ) ), (int)Y);
		}
		
	}
	
}




//* ï¿½ë£„ï¿½ì‚Ž ï¿½ë¸¿ï¿½ë‹” *//
void screenBorder(const char ch, const int x1, const int y1, const int x2, const int y2) {  // ï¿½ê¶—åª›ê³¹?‚Žï¿½ì“½ ï¿½ë?’ï¿½ëª¢ç”±?‰ï¿½ï¿? æ´¹ëªƒ?”.
    screenYline(ch, x1, y1, y2-y1);
	screenXline(ch, x1+1, y1, x2-x1);
	screenYline(ch, x2, y1+1, y2-y1);
	screenXline(ch, x1, y2, x2-x1);
}


//* ?‡¾ëª„ì˜„ ?•°?’•? ° ï¿½ë¸¿ï¿½ë‹” *//
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

// Æú¸®°ï ±×¸®±â.
void screenPoly( const uint8_t dot, const poly_obj_t* const poly )
{
    for ( uint32_t index=0; index<poly->length-1; index++ )
    {
        screenLine(dot, poly->poly_dots[index].x, poly->poly_dots[index].y,  poly->poly_dots[index+1].x, poly->poly_dots[index+1].y);
    }
}

// Ææ ±×¸®±â Åø.
void screenDrawTool( const draw_tool_obj_t draw, volatile const uint16_t start_pos_x, volatile const uint16_t start_pos_y )
{
	// ÇöÀç À§Ä¡ ±â¾ï º¯¼ö.
	volatile int16_t current_x = start_pos_x;
	volatile int16_t current_y = start_pos_y;

	for ( uint16_t index=0; index<draw.length; index++ )
	{
		// ÆæÀ» ³õ°í ¿òÁ÷ÀÌ´Â °æ¿ì.
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
		// ÆæÀ» ¶§°í ¿òÁ÷ÀÌ´Â °æ¿ì.
		else if ( draw.line_set[index].pen_mode == Move )
		{
			current_x += draw.line_set[index].move_x;
			current_y += draw.line_set[index].move_y;
		}

	}
}