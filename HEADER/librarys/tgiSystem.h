/*
TGI system 헤더

헤더 순도 : B등급.
*/


// 데이터 형식 등등. //
typedef int16_t return_code_t;  // 함수가 반환하는 값이 작업 상태 등을 나타내는 경우 시용.
typedef void* pointer;

typedef struct
{
	return_code_t code;
	char *message;
} return_block_t;

typedef union {
	unsigned char RAW;
	struct
	{
		unsigned char t0 : 1;
		unsigned char t1 : 1;
		unsigned char t2 : 1;
		unsigned char t3 : 1;
		unsigned char t4 : 1;
		unsigned char t5 : 1;
		unsigned char t6 : 1;
		unsigned char t7 : 1;
	};
} bitbyte;

typedef struct
{ // 프로세스 정보 기록.
	signed char state;
	/* state
	-2 : 프로그램 최초 초기화 대기 상태.(실행 전 상태.)
	-1 : 초기화 대기 상태.(실행 전 상태.)
	0 : 완전 종료 상태.
	1 : 포그라운드 실행 상태.
	2 : 실행 중. 1로 변경되기 전 까지 종료 상태로 전환 금지.(강제 선점)
	3 : 백그라운드 실행 상태.
	이 외: 이하 사용자 정의.
	*/

	unsigned char priority;
	/* priority
	우선 순위 값.
	0부터 7까지.
	작은 값일 수록 우선 순위 높음.
	*/
} pcb;

// 좌표 킷. //
typedef struct
{
	short x, y; // 한 점의 좌표.

} coordinate_kit;

typedef struct
{
	// 직사각형을 나타내는 2개 점의 좌표.
	short x1, y1; // 첫 번째 점의 좌표.
	short x2, y2; // 두 번째 점의 좌표.

} coordinate_simple2D_kit;

typedef struct
{
	// 사각형을 나타내는 4개 점의 좌표.
	short x1, y1;
	short x2, y2;
	short x3, y3;
	short x4, y4;

} coordinate_RAW2D_kit;

typedef struct
{
	// 직육면체를 나타내는 꼭짓점의 좌표.
	short x1, y1, z1;
	short x2, y2, z2;
	short x3, y3, z3;
	short x4, y4, z4;

	short x5, y5, z5;
	short x6, y6, z6;
	short x7, y7, z7;
	short x8, y8, z8;

} coordinate_RAW3D_kit;

// 오브젝트. //

// 애니메이션. //
typedef struct
{
	// 애니메이션 속성.
	short speed;
	unsigned long long count;

	// 애니메이션 효과로 이동할 좌표.
	short set_x;
	short set_y;

} ani_kit;


/*
// 반환 값에 대한 정의. //
const return_block_t *__return_set[] = {
	return_block_t
}
*/


// 시스템 함수. //
void systemMessage()
{
	printf("\n[TGI-system] - ");
}

return_code_t returnEvent(return_code_t return_code)
{  // ????? return ??? ????? ????? ????? ??? ??????? ?뵵?? ????. ??? ???? ?? ???? ????? ???? ???.
	if (!__DEBUG_MODE) return return_code;
	
	systemMessage();
    if (return_code >= 0)
    {
        switch (return_code)
        {
        	case 0: printf("알 수 없는 반환 이벤트가 발생하였습니다"); break;
        	
        	// 110번대는 스택버퍼 함수 영역. //
        	case 111: printf("새 스택버퍼에 데이터가 푸쉬되었습니다"); break;
        	case 112: printf("스택버퍼에 데이터가 푸쉬되었습니다"); break;
        	
        	default : printf("정의되지 않은 반환 코드입니다"); break;
        }
        printf(". Return code : %d", return_code);
    }
    else
    {
        if ( return_code >= -100 && return_code <= -91 )
        {
        	printf("소스코드 수준의 시스템 점검이 필요합니다. 시스템이 완전히 정지됩니다.");
        	
        	switch (return_code)
        	{
        		case -99: printf("\n	세부 사항 : 허용되지 않은 시스템 루프 이탈. 매우 위험하지만 ERRORPASS_ESCAPE_SYSTEM_LOOP를 이용해 본 에러를 무시할 수 있습니다"); break;
				
				default: printf("정의되지 않은 에러 코드입니다"); break;
        	}
        	
        }
        else
        {
        	switch (return_code)
        	{
        		case -1: printf("금지된 행위 또는 작업이 발생하였습니다"); break;
        		case -2: printf("논리적으로 올바르지 않은 코드 실행입니다"); break;
        		case -3: printf("명확하지 않은 접근 문제가 발생하였습니다"); break;
        		case -4: printf("데이터 형식이 일치하지 않습니다"); break;
        		case -5: printf("알 수 없는 데이터입니다"); break;
        		case -6: printf("명확하지 않은 작업 문제가 발생하였습니다"); break;
        		case -7: printf("시스템 재시작이 필요합니다. 경우에 따라 소스코드 수준의 시스템 점검이 필요할 수 있습니다"); break;
        		case -8: printf("시스템 문제를 감지했습니다. 점검이 필요합니다"); break;
        		case -9: printf("무한로프가 감지되었습니다"); break;
        		case -10: printf("디버깅 중 에러가 발생했습니다"); break;
        		
        		case -111: printf("스택버퍼 생성 시의 크기는 1 이상이어야 합니다."); break;
        		case -113: printf("스택버퍼에 픽 작업을 시도했지만"); break;
        		case -114: printf("스택버퍼에 푸쉬 작업을 시도했지만 해당 스택버퍼는 스택버퍼 형식과 일치하지 않습니다. 해당 스택버퍼는 모두 0이 아닌 데이터로 채워져 있습니다"); break;
        		case -115: printf("스택버퍼에 픽 작업을 시도했지만 해당 스택버퍼는 스택버퍼 형식과 일치하지 않습니다. 해당 스택버퍼는 모두 0이 아닌 데이터로 채워져 있습니다"); break;
        		case -116: printf("스택버퍼에 푸쉬 작업을 시도했지만 해당 스택버퍼에는 빈 공간이 없어 푸쉬 작업이 취소됐습니다"); break;
        		
        		default: printf("정의되지 않은 에러 코드입니다"); break;
        	}
        }
        
        printf(". Error code : %d", return_code);
    }
    
	getch();getch();
    return return_code;
}

void debugPause(int const *str) {  // ??????? ????? ??? ???? ??? ????? ?뵵?? ????.
    printf("\n[Debug] : %s\n", str);
    _getch();
}

/*
 pSetAutoStart()
{
	
}
*/
signed char pKill(pcb *p)
{
	if (p -> state == 2)
	{
		return -1;
	}
	else
		p->state = 0;
	return 1;
}
/*
signed char pRun(pcb *p)
{
	switch (p->state)
	{
	case 2:  // 실행상태 변경 금지.
	case -2:  // 최초 초기화
		return -1;
	}
}

signed char pOpen(pcb *p, signed char )
{
	switch (p -> state)
	{
		case 
	}
}
*/
// 프로세서 초기화, 오픈, 백그라운드, 재시작 추가.



// push pick 버퍼. //
typedef uint16_t PUSH_BUFFER_SIZE_T;  // 푸쉬 버퍼 헤더 크기. 2바이트.

// push 가능한 버퍼를 생성한다.
pointer new_Stack(size_t type_size, PUSH_BUFFER_SIZE_T buffer_len)
{
	if (buffer_len < 1) return( returnEvent(-111), (pointer)0 );
	
	pointer buf = 0;
	// 버퍼의 크기는 헤더 영역 크기와 사용할 버퍼 크기와 기준점 크기의 합이다.
	if (  !(buf = calloc( (sizeof(PUSH_BUFFER_SIZE_T))+((type_size*buffer_len)+type_size), 1 ))  )
	{
		free(buf);
		return( returnEvent(-116), (pointer)0 );
	}
	
	*((PUSH_BUFFER_SIZE_T *)buf) = type_size*buffer_len;  // 바이트 크기 헤더에 저장.
	
	return buf;
}

// uint32_t형의 데이터를 push하는 함수.
return_code_t push_uint32(pointer buf, uint32_t data)
{
	// 버퍼의 헤더에서 사용될 버퍼의 크기를 가져옴.
	// 그 다음 버퍼 포인터를 버퍼 영역을 가리키도록 함.
	PUSH_BUFFER_SIZE_T buf_len = *((PUSH_BUFFER_SIZE_T*)buf) / sizeof(uint32_t);
	PUSH_BUFFER_SIZE_T pointing = 0;

	buf = (uint8_t*)buf + sizeof(PUSH_BUFFER_SIZE_T);  // 1바이트 단위로 총 2바이트 이동.



	// 버퍼스택의 처음 위치부터 0이 채워져있는 경우, 0을 모두 건너 뛴 다음에 데이터블록 위의 0의 위치 찾기.
	while ( !((uint32_t *)buf)[pointing] )
	{
		// 버퍼스택을 모두 탐색했지만 0밖에 없다면 빈 버퍼스택이므로 0번 위치에 data를 푸쉬.
		if ( pointing >= buf_len )
		{
			((uint32_t *)buf)[0] = data+1;

			return(returnEvent(111));//새 스택버퍼 생성.
		}
		pointing++;
	}  // pointing은 현재 스택버퍼의 첫 번째 데이터블록을 가리키고 있음.
	
	// 데이터블록 위에 0이 있는 위치를 찾음.
	while ( ((uint32_t *)buf)[pointing] )
	{
		// 버퍼스택을 모두 탐색했지만 모두 데이터로 채워져있다면 데이터 형식 불일치 에러 발생.
		if ( pointing >= buf_len ) return(returnEvent(-114));
		pointing++;
	}  // pointing은 현재 버퍼스택의 데이터블록 위의 0을 가리키고 있음.
	
	// pointing이 현재 가리키고있는 0이 기준점이라면.
	// (바로 그 다음 위치에 데이터블록이 있다면 현재 pointing이 가리키고있는 0은 기준점임.)
	if ( ((uint32_t *)buf)[pointing+1] )
	{
		// 스택버퍼가 꽉 차있으므로 푸쉬 불가. 에러 이벤트 발생.
		return(returnEvent(-116));
	}
	// 푸쉬 가능한 경우.
	else
	{
		// 스택버퍼에 data 쌓아 올림.
		((uint32_t *)buf)[pointing] = data+1;
		return(returnEvent(112));
	}
	
}

// 버퍼스택에서 가장 마지막으로 저장된 데이터를 가져옴, peek. //
int64_t pick_uint32(pointer buf)
{
	//스택버퍼의 헤더에서 버퍼스택의 길이를 구함.
	// PUSH_BUFFER_SIZET buf_len = ( *((PUSH_BUFFER_SIZET*)buf++) ) / 4;
	PUSH_BUFFER_SIZE_T buf_len = *((PUSH_BUFFER_SIZE_T*)buf) / sizeof(uint32_t);
	PUSH_BUFFER_SIZE_T pointing = 0;

	// 버퍼 포인터의 기준점을 데이터 구역으로 이동시킴.
	buf = (uint8_t*)buf + sizeof(PUSH_BUFFER_SIZE_T);  // 1바이트 단위로 초 2바이트 이동.

	

	// 기준점 찾기. //
	
	//스택버퍼의 처음 위치에서부터 있는 0이 아닌 연속된 데이터블록들을 모두 건너 뜀.
	while ( ((uint32_t *)buf)[pointing] )
	{
		//스택버퍼가 0이 아닌 데이터로 모두 채워져있으므로 데이터 형식 불일치 에러 발생.
		if ( pointing >= buf_len ) return(returnEvent(-115));
		pointing++;
	}//pointing은 현재 0이 아닌 연속된 데이터블록 다음에 있는 0의 위치를 가리키고 있음.



	//스택버퍼 처음 위치에 있는 0을 모두 건너 뜀.
	while ( !(((uint32_t *)buf)[pointing]) )
	{
		
		//스택버퍼가 빈 공간임. 이런 경우 -1을 반환.
		if ( pointing >= buf_len )
		{
			//기준점이 스택버퍼의 맨 위에 있고, 첫 번째 데이터블록이 0번 위치에 있을 경우
			if ( ((uint32_t *)buf)[0] )
			{
				//버퍼스택의 0번 위치에서 픽.
				uint32_t result = ((uint32_t *)buf)[0] - 1;
				((uint32_t *)buf)[0] = 0;
				
				return( result );
			}
			return(returnEvent(-112), -1);
		}
		pointing++;
	}//pointing은 현재 0 다음에 있는 0이 아닌 값을 가리키고 있음.


	
	//pointing이 가리키는 위치에서 데이터를 가져옴.
	uint32_t result = ((uint32_t *)buf)[pointing] - 1;
	((uint32_t *)buf)[pointing] = 0;

	return( result );
}
