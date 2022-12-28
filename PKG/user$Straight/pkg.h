#pragma once
/*
    패키지 : '직진' 게임 패키지.
    설명 : '직진' 게임 전체를 구성하는 패키지.
*/
#include "./../../HEADER/TGI-library-master.h"
#include "./../../HEADER/Cobject/cobject.h"
#include "./../../HEADER/Timer.h"

// 나아가는 속도.
#define WORK_SPEED 1

// 선택 박스 이동 속도.
#define SELECT_BOX_SPEED 0.03

// 중앙 소실점 좌표.
#define CENTER_X SCWIDTH/2-1
#define CENTER_Y SCHEIGHT/2-1-10

// 화면 아래 양 끝과 길 아래 양 끝의 간격.
#define WAY_MARGIN 40

// 추가 가능한 사이드 오브젝트 최대 갯수.
#define SIDE_OBJ_LENGTH 500

// 디스플레이 테두리 문자.
#define DISPLAY_BORDER_DOT '.'

// 오브젝트 문자.
#define OBJ_CHAR ','

// 오브젝트 안쪽 모서리 문자.
#define OBJ_INSIDE_DOT '_'

// 길 문자.
#define WAYS_DOT '.'

// 문자 구성 문자.
#define STRING_DOT '@'

// 선택 박스 문자.
#define SELECT_BOX_DOT '#'

// 박스 테두리 문자.
#define BOX_BORDER_DOT '+'

// 문자 사이의 간격.
#define STR_MARGIN 1

// 오브젝트 길이.
#define OBJ_LENGTH 1700

// 메인 화면 왼쪽 오브젝트 추가 간격
#define LEFT_OBJ_ADD_DELAY 5500

// 메인 화면 오른쪽 오브젝트 추가 간격
#define RIGHT_OBJ_ADD_DELAY 4000

// 디스플레이 프레임
#define DISPLAY_FRAME 32

// 델타 타임 프레임.
#define DELTA_TIME_FRAME 70

// 길의 왼쪽 대각선의 좌표.
#define LEFT_WAY_LINE_POS left_side_way_pos.x,left_side_way_pos.y,  center_way_pos.x+2, center_way_pos.y

// 길의 오른쪽 대각선의 좌표.
#define RIGHT_WAY_LINE_POS right_side_way_pos.x,right_side_way_pos.y,  center_way_pos.x, center_way_pos.y

// 화면에서 보이는 오브젝트의 최대 높이. 화면 세로 좌표 기준.
#define OBJECT_TALL (SCHEIGHT - SCHEIGHT/16)

// 상단 왼쪽 대각선의 좌표.
#define LEFT_TOP_LINE_POS 0,OBJECT_TALL,  center_way_pos.x,center_way_pos.y

// 상단 오른쪽 대각선의 좌표.
#define RIGHT_TOP_LINE_POS center_way_pos.x,center_way_pos.y,  SCWIDTH-1,OBJECT_TALL

//////////////////////////////// TODO : getLinePos의 좌표는 모두 교체대상!!!

// WAIT_TIME_DEFAULT을 나누는 값, 원근감을 느끼게 해줄 세로선 속도 증가 배수.
#define DOWN_TIMER 1.035

// 오브젝트의 세로선 한 칸씩 움직일 때마다 기다려야 하는 시간 기본값.
#define WAIT_TIME_DEFAULT (500*(WORK_SPEED))


/// 객체 섹션 ///

// 오브젝트 객체.
typedef struct type$class_Straight$obj_t
{
    // 왼쪽 위 점.
    uint16_t topLeftX;
    uint16_t topLeftY;

    // 오른쪽 위 점.
    uint16_t topRightX;
    uint16_t topRightY;

    // 오른쪽 아래 점.
    uint16_t bottomRightX;
    uint16_t bottomRightY;

    // 왼쪽 아래 점.
    uint16_t bottomLeftX;
    uint16_t bottomLeftY;
} obj_t;

// 지나가는 오브젝트 객체.
typedef struct type$class_Straight$side_obj_t
{
    /// 왼쪽 직선 ///
    // 왼쪽 공통 X좌표
    uint16_t leftX;

    // 왼쪽 Y좌표
    uint16_t topLeftY;
    uint16_t bottomLeftY;


    /// 오른쪽 직선 ///
    // 공통 오른쪽 X좌표.
    uint16_t rightX;

    // 오른쪽 Y좌표
    uint16_t topRightY;
    uint16_t bottomRightY;


    /// 왼쪽 세로선 타이머 ///
    // 타이머에 사용되는 시간.
    clock_t left_next_update_time;
    // 타이머 시간 간격 크기.
    uint32_t left_down_time;


    /// 오른쪽 세로선 타이머 ///
    // 타이머에 사용되는 시간.
    clock_t right_next_update_time;
    // 타이머 시간 간격 크기.
    uint32_t right_down_time;

    
    // 두 세로선의 출발 시간차 타이머.
    clock_t wait_time;
    // 두 세로선의 출발 시간차.
    uint32_t set_wait_time;

} side_obj_t;

enum Button_state
{
    // 메뉴 리스트에 보임.
    Start, Exit,

    // 메뉴 리스트에 추가되지 않음. (옵션)
    Nothing, Screen_border, To_menu,
};



/// 전역 변수 섹션 ///
typedef struct type$Straight$side_obj_list_t
{
    uint8_t is_null[SIDE_OBJ_LENGTH];
    side_obj_t list[SIDE_OBJ_LENGTH];
} side_obj_list_t;

// 오른쪽 오브젝트 담는 배열.
side_obj_list_t right_objs = {
    .is_null = {0},
    .list = {0},
};
// 왼족 오브젝트 담는 배열.
side_obj_list_t left_objs = {
    .is_null = {0},
    .list = {0},
};


// 게임 엑티비티 상태.
// 0 : 게임 실행.
// 1 : 게임 매인 화면.
// 2 : 게임 플레이.
// 3 : 기타.
// uint8_t screen_activity_state = 0;
enum Active
{
    MainHome,
    inGame,
} screen_activity_state = MainHome;

// 나아간 거리.
// uint64_t step_count = 0;

// 나아가는 속도.
uint8_t work_speed = WORK_SPEED;

// 길 대각선의 중앙 좌표값.
pos_t center_way_pos = {
   .x = CENTER_X,
   .y = CENTER_Y,
};

// 길 대각선 왼쪽 사이드 좌표값.
pos_t left_side_way_pos = {
   .x = WAY_MARGIN,
   .y = 0,
};

// 길 대각선 오른쪽 사이드 좌표값.
pos_t right_side_way_pos = {
   .x = SCWIDTH-1-WAY_MARGIN,
   .y = 0,
};


/// 함수 섹션 ///

// side_obj_t 오브젝트를 버퍼에 그려주는 함수.
void Straight$side_obj_Draw( const side_obj_t* const obj )
{   // 이 함수는 왼쪽 대각선의 오브젝트와 오른쪽 대각선의 오브젝트를 그린다.
    // 1. 왼쪽 세로줄.
    screenLine(OBJ_CHAR, obj->leftX,obj->topLeftY,  obj->leftX,obj->bottomLeftY);

    // 2. 오른쪽 세로줄.
    screenLine(OBJ_CHAR, obj->rightX,obj->topRightY,  obj->rightX,obj->bottomRightY);

    // 3. 지붕 가로줄.
    screenLine(OBJ_CHAR, obj->leftX,obj->topLeftY,  obj->rightX,obj->topRightY);

    // 4. 안쪽 위 윤곽선.
    uint16_t pos_y = ( obj->topLeftY < obj->topRightY ) ? ( obj->topLeftY ) : ( obj->topRightY );
    screenLine(
        OBJ_INSIDE_DOT,
        obj->leftX+1, pos_y,
        obj->rightX-1, pos_y
    );
    pos_y = ( obj->bottomLeftY > obj->bottomRightY ) ? ( obj->bottomLeftY ) : ( obj->bottomRightY );;
    screenLine(
        OBJ_INSIDE_DOT,
        obj->leftX+1, pos_y,
        obj->rightX-1, pos_y
    );
}



// 화면 초기화.
void ScreenInit()
{
    for (long i = 0; i < 100; i++) {  // cmd? ?????? ???? ?????? ???? cmd? ???? ???? ???? ????.
		printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
	}

    screenBegin();
    screenFill(' ');
    screenUpdate();
}


// 게임 초기화
void Straight$Game$init()
{
    memset(&left_objs, 0, sizeof(left_objs));
    memset(&right_objs, 0, sizeof(right_objs));
    memset(left_objs.is_null, o_true, sizeof(left_objs.is_null));
    memset(right_objs.is_null, o_true, sizeof(right_objs.is_null));
}


// 왼쪽 오브젝트 리스트에 오브젝트 추가하는 함수.
void Straight$addLeftSideObject( side_obj_t obj )
{
    for ( uint16_t index=0; index<SIDE_OBJ_LENGTH; index++ )
    {

        if ( left_objs.is_null[index] == o_true )
        {   // 비어있다면.
            left_objs.list[index] = obj;
            left_objs.is_null[index] = o_false;

            // 비어있는 공간에 성공적으로 오브젝트를 추가했으므로 함수 종료.
            return;
        }

    }
    // 오브젝트 저장 실패.
    return;
}


// 오른쪽 오브젝트 리스트에 오브젝트 추가하는 함수.
void Straight$addRightSideObject( side_obj_t obj )
{
    for ( uint16_t index=0; index<SIDE_OBJ_LENGTH; index++ )
    {

        if ( right_objs.is_null[index] == o_true )
        {   // 비어있다면.
            right_objs.list[index] = obj;
            right_objs.is_null[index] = o_false;

            // 비어있는 공간에 성공적으로 오브젝트를 추가했으므로 함수 종료.
            return;
        }

    }
    // 오브젝트 저장 실패.
    return;
}


// 왼쪽 오브젝트 리스트에서 오브젝트 제거하는 함수.
void Straight$deleteLeftSideObject( uint16_t delete_index )
{
    // 0. 오브젝트 리스트에 담겨있는 오브젝트 갯수 구하기.
    uint16_t length = 0;
    for ( uint16_t index=0; index<SIDE_OBJ_LENGTH; index++ )
    {
        if ( left_objs.is_null[index] == o_true ) break;
        length++;
    }
    

    left_objs.is_null[delete_index] = o_true;

    for ( uint16_t index=delete_index; index<length-1; index++ )
    {
        left_objs.list[index] = left_objs.list[index+1];
        left_objs.is_null[index] = o_false;
        left_objs.is_null[index+1] = o_true;
    }
}


// 오른쪽 오브젝트 리스트에서 오브젝트 제거하는 함수.
void Straight$deleteRightSideObject( uint16_t delete_index )
{
    uint16_t length = 0;
    for ( uint16_t index=0; index<SIDE_OBJ_LENGTH; index++ )
    {
        if ( right_objs.is_null[index] == o_false ) break;
        length++;
    }

    right_objs.is_null[delete_index] = o_true;

    for ( uint16_t index=delete_index; index<length-1; index++ )
    {
        right_objs.list[index] = right_objs.list[index+1];
        right_objs.is_null[index] = o_false;
        right_objs.is_null[index+1] = o_false;
    }
}


// 왼쪽 오브젝트 리스트에 저장 가능 유무 반환.
uint8_t Straight$leftSideObjectState()
{
    for ( uint16_t index=0; index<SIDE_OBJ_LENGTH; index++ )
    {
        if ( left_objs.is_null[index] == o_true )
        {
            // 비어있는 경우가 있다면 1 반환.
            return( o_true );
        }
    }

    // 리스트가 다 차있는 경우 0 반환.
    return( o_false );
}


// 오른쪽 오브젝트 리스트에 저장 가능 유무 반환.
uint8_t Straight$rightSideObjectState()
{
    for ( uint16_t index=0; index<SIDE_OBJ_LENGTH; index++ )
    {
        if ( right_objs.is_null[index] == o_true )
        {
            // 비어있는 경우가 있다면 1 반환.
            return( o_true );
        }
    }

    // 리스트가 다 차있는 경우 0 반환.
    return( o_false );
}


// 왼쪽 오브젝트 리스트에서 1번째 오브젝트 가져오기 함수. (자동으로 가져오고 삭제됨.)
side_obj_t Straight$leftSideObjectGet()
{
    side_obj_t result = left_objs.list[0];
    Straight$deleteLeftSideObject(0);
    return( result );
}


// 오른쪽 오브젝트 리스트에서 1번째 오브젝트 가져오기 함수. (자동으로 가져오고 삭제됨.)
side_obj_t Straight$rightSideObjectGet()
{
    side_obj_t result = right_objs.list[0];
    Straight$deleteRightSideObject(0);
    return( result );
}


// 새로운 왼쪽 오브젝트 반환하는 함수.
side_obj_t Straight$newLeftSideObject( uint32_t set_wait_time )
{
    return(
        (side_obj_t)
        {
            // 왼쪽 세로선.
            .leftX = center_way_pos.x,
            .topLeftY = center_way_pos.y,
            .bottomLeftY = center_way_pos.y,

            // 오른쪽 세로선.
            .rightX = center_way_pos.x,
            .topRightY = center_way_pos.y,
            .bottomRightY = center_way_pos.y,

            // 오브젝트 정보.
            .left_next_update_time = 0,
            .left_down_time = WAIT_TIME_DEFAULT,
            .right_next_update_time = 0,
            .right_down_time = WAIT_TIME_DEFAULT,
            .wait_time = 0,
            .set_wait_time = set_wait_time,
        }
    );
}


// 새로운 왼쪽 오브젝트 반환하는 함수.
side_obj_t Straight$newRightSideObject( uint32_t set_wait_time )
{
    return(
        (side_obj_t)
        {
            // 오른쪽 세로선.
            .rightX = center_way_pos.x,
            .topRightY = center_way_pos.y,
            .bottomRightY = center_way_pos.y,

            // 왼쪽 세로선.
            .leftX = center_way_pos.x,
            .topLeftY = center_way_pos.y,
            .bottomLeftY = center_way_pos.y,

            // 오브젝트 정보.
            .left_next_update_time = 0,
            .left_down_time = WAIT_TIME_DEFAULT,
            .right_next_update_time = 0,
            .right_down_time = WAIT_TIME_DEFAULT,
            .wait_time = 0,
            .set_wait_time = set_wait_time,
        }
    );
}


// 왼쪽 오브젝트의 좌표 업데이트.
void Straight$Game$leftSideObjectUpdate( side_obj_list_t* full_obj, uint16_t index )
{
    // 0. 현재 시간 저장(캡처) & 오브젝트 분리.
    register clock_t current_time = clock_ms();
    side_obj_t* obj = full_obj->list+index;

    // 1. 시간차를 두어 업데이트 시키기 위해 타이머 초기화.
    if ( obj->wait_time == 0 ) //타이머 정보가 없는 새로운 오브젝트인 경우.
    {
        // 1. 현재 오브젝트에 담겨있는 시간차 정보로 타이머를 설정함.
        obj->wait_time = obj->set_wait_time + current_time;
    }

    // 2. 오른쪽 세로선에 대한 타이머. 다만 시간차를 두고 좌표 업데이트.
    // - 타이머 정보가 없는 새로운 오브젝트인지 아니면 타이머가 작동중인 오브젝트인지 구별해야함.
    if ( current_time > obj->wait_time )  // 타이머가 완료된 경우 좌표 업데이트.
    {
        // 0. 세로선 업데이트 타이머.
        if ( current_time > obj->right_next_update_time )
        {
            // 1. 오른쪽 세로선 X좌표 업데이트 & 좌표 이탈 방지.
            if ( obj->rightX > 0 ) obj->rightX--;

            // 2. 오른쪽 세로선 상단 Y좌표 업데이트 & 좌표 이탈 방지.
            if ( obj->topRightY < SCHEIGHT-1 ) obj->topRightY = getLinePos(LEFT_TOP_LINE_POS, obj->rightX, -1)+1;  // 자연스러움을 위해 오브젝트의 기본 높이 추가.

            // 3. 오른쪽 세로선 하단 Y좌표 업데이트 & 좌표 이탈 방지.
            if ( obj->bottomRightY > 0 ) obj->bottomRightY = getLinePos(LEFT_WAY_LINE_POS, obj->rightX, -1);

            // 4. 타이머 업데이트.
            obj->right_next_update_time = obj->right_down_time + current_time;
        }
        // 1. 타이머 변화량 업데이트 & 음수 및 오버플로우 방지.
        if ( obj->right_down_time > 0 ) obj->right_down_time -= 2 * WORK_SPEED;
    }

    // 3. 왼쪽 세로선에 대한 타이머.
    if ( current_time > obj->left_next_update_time )
    {
        // 1. 왼쪽 세로선 X좌표 업데이트 & 좌표 이탈 방지.
        if ( obj->leftX > 0 ) obj->leftX--;

        // 2. 왼쪽 세로선 상단 Y좌표 업데이트 & 좌표 이탈 방지.
        if ( obj->topLeftY < SCHEIGHT-1 ) obj->topLeftY = getLinePos(LEFT_TOP_LINE_POS, obj->leftX, -1)+1;

        // 3. 왼쪽 세로선 하단 Y좌표 업데이트 & 좌표 이탈 방지.
        if ( obj->bottomLeftY > 0 ) obj->bottomLeftY = getLinePos(LEFT_WAY_LINE_POS, obj->leftX, -1);

        // 4. 타이머 업데이트.
        obj->left_next_update_time = obj->left_down_time + current_time;

    }
    // 4. 타이머 변화량 업데이트 & 음수 및 오버플로우 방지.
    if ( obj->left_down_time > 0 ) obj->left_down_time -= 2 * WORK_SPEED;
}


// 오른쪽 오브젝트의 좌표 업데이트.
void Straight$Game$rightSideObjectUpdate( side_obj_list_t* full_obj, uint16_t index )
{
    // 0. 현재 시간 저장(캡처) & 오브젝트 분리.
    register clock_t current_time = clock_ms();
    side_obj_t* obj = full_obj->list+index;

    // 1. 시간차를 두어 업데이트 시키기 위해 타이머 초기화.
    if ( obj->wait_time == 0 )  // 새로운 오브젝트인 경우.
    {
        // 1. 현재 오브젝트에 담겨있는 시간차 정보로 타이머를 설정함.
        obj->wait_time = obj->set_wait_time + current_time;
    }
    
    // 2. 왼쪽 세로선에 대한 타이머. 다만 시간차를 두고 좌표를 업데이트 시킨다.
    if ( current_time > obj->wait_time )
    {
        if ( current_time > obj->left_next_update_time )
        {
            // 1. 왼쪽 세로선 X좌표 업데이트 & 좌표 이탈 방지.
            if ( obj->leftX < SCWIDTH-1 ) obj->leftX++;

            // 2. 왼쪽 세로선 상단 Y좌표 업데이트 & 좌표 이탈 방지.
            if ( obj->topLeftY < SCHEIGHT-1 ) obj->topLeftY = getLinePos(RIGHT_TOP_LINE_POS, obj->leftX, -1)+1;

            // 3. 왼쪽 세로선 하단 Y좌표 업데이트 & 좌표 이탈 방지.
            if ( obj->bottomLeftY > 0 ) obj->bottomLeftY = getLinePos(RIGHT_WAY_LINE_POS, obj->leftX, -1);
            
            // 4. 타이머 업데이트.
            obj->left_next_update_time = obj->left_down_time + current_time;
        }
        // 3. 타이머 변화량 업데이트 & 음수 및 오버플로우 방지.
        if ( obj->left_down_time > 0 ) obj->left_down_time -= 2 * WORK_SPEED;
    }


    // 4. 오른쪽 세로선에 대한 타이머.
    if ( current_time > obj->right_next_update_time )
    {
        // 1. 오른쪽 세로선 X좌표 업데이트 & 좌표 이탈 방지.
        if ( obj->rightX < SCWIDTH-1 ) obj->rightX++;

        // 2. 오른쪽 세로선 상단 Y좌표 업데이트 & 좌표 이탈 방지.
        if ( obj->topRightY < SCHEIGHT-1 ) obj->topRightY = getLinePos(RIGHT_TOP_LINE_POS, obj->rightX, -1)+1;

        // 3. 오른쪽 세로선 하단 Y좌표 업데이트 & 좌표 이탈 방지.
        if ( obj->bottomRightY > 0 ) obj->bottomRightY = getLinePos(RIGHT_WAY_LINE_POS, obj->rightX, -1);

        // 4. 타이머 업데이트.
        obj->right_next_update_time = obj->right_down_time + current_time;
    }
    // 5. 타이머 변화량 업데이트 & 음수 및 오버플로우 방지.
    if ( obj->right_down_time > 0 ) obj->right_down_time -= 2 * WORK_SPEED;
}


// 화면 밖으로 나간 왼쪽 오브젝트 자동으로 제거.
void Straight$Game$leftSideObjectAutoDelete( side_obj_list_t* full_obj, uint16_t index )
{
    // 0. 오브젝트 분리.
    side_obj_t* obj = full_obj->list+index;
    
    // 1. 오른쪽 세로선 X좌표가 0인지 확인.
    if ( obj->rightX <= 0 )
    {
        // 2. 해당 오브젝트를 삭제.
        Straight$deleteLeftSideObject(index);
    }
}


// 화면 밖으로 나간 오른쪽 오브젝트 자동으로 제거.
void Straight$Game$rightSideObjectAutoDelete( side_obj_list_t* full_obj, uint16_t index )
{
    // 0. 오브젝트 분리.
    side_obj_t* obj = full_obj->list+index;
    
    // 1. 왼쪽 세로선 X좌표가 화면 제일 오른쪽에 있는지 확인.
    if ( obj->leftX >= SCWIDTH-1 )
    {
        // 2. 해당 오브젝트를 삭제.
        Straight$deleteRightSideObject(index);
    }
}


// 게임 플레이 전체에 대한 좌표 업데이트 함수.
void Straight$Game$AnimateUpdate()
{
    // 0. 현재 시간 변수에 저장.
    register clock_t current_time = clock_ms();

    // 1. 왼쪽 오브젝트 좌표값 업데이트.
    for ( uint16_t index=0; index<SIDE_OBJ_LENGTH; index++ )
    {
        // 0. 비어진 오브젝트는 처리 안 함.
        if ( left_objs.is_null[index] == o_true )
        {
            continue;
        }
        
        // 0. 왼쪽 오브젝트 자동 삭제.
        Straight$Game$leftSideObjectAutoDelete(&left_objs, index);
        
        // 1. 현재 왼쪽 오브젝트 좌표 업데이트.
        Straight$Game$leftSideObjectUpdate(&left_objs, index);
    }
    
    // 2. 오른쪽 오브젝트 좌표값 업데이트.
    for ( uint16_t index=0; index<SIDE_OBJ_LENGTH; index++ )
    {
        // 0. 비어진 오브젝트는 처리 안 함.
        if ( right_objs.is_null[index] == o_true )
        {
            continue;
        }

        // 0. 오른쪽 오브젝트 자동 삭제.
        Straight$Game$rightSideObjectAutoDelete(&right_objs, index);        

        // 1. 현재 오른쪽 오브젝트 좌표 업데이트.
        Straight$Game$rightSideObjectUpdate(&right_objs, index);        
    }
}


// 게임 그래픽 그리기 함수.
void Straight$Game$GraphicDraw( uint16_t str_number, ... )
{
    // 0. 화면 비우기.
    screenFill(' ');


    // 펜툴 테스트.
    // line_set_t line_set[] = {
    //     {
    //         .pen_mode = Move,
    //         .dot = 0,
    //         .move_x = 6,
    //         .move_y = 8,
    //     },
    //     {
    //         .pen_mode = Draw,
    //         .dot = STRING_DOT,
    //         .move_x = -6,
    //         .move_y = 0,
    //     },
    //     {
    //         .pen_mode = Draw,
    //         .dot = STRING_DOT,
    //         .move_x = 0,
    //         .move_y = -4,
    //     },
    //     {
    //         .pen_mode = Draw,
    //         .dot = STRING_DOT,
    //         .move_x = 6,
    //         .move_y = 0,
    //     },
    //     {
    //         .pen_mode = Draw,
    //         .dot = STRING_DOT,
    //         .move_x = 0,
    //         .move_y = -4,
    //     },
    //     {
    //         .pen_mode = Draw,
    //         .dot = STRING_DOT,
    //         .move_x = -6,
    //         .move_y = 0,
    //     },
    // };
    // draw_tool_obj_t obj = {
    //     .length = o_arraylen(line_set_t, line_set),
    //     .line_set = line_set,
    // };
    // screenDrawTool(obj, 0, 0);

    // 1. 오브젝트 그리기.
    for ( int index=0; index<SIDE_OBJ_LENGTH; index++ )
    {
        // 0. 화면 왼쪽 오브젝트 그리기.
        if ( left_objs.is_null[index] == o_false )
        {
            Straight$side_obj_Draw(&left_objs.list[index]);  // 오브젝트가 리스트에 존재하면, 해당 오브젝트 데이터로 그림.
        }

        // 1. 화면 오른쪽 오브젝트 그리기.
        if ( right_objs.is_null[index] == o_false )
        {
            Straight$side_obj_Draw(&right_objs.list[index]);
        }   
    }

    // 2. 길 그리기.
    screenLine(WAYS_DOT, LEFT_WAY_LINE_POS);  // 왼쪽 대각선. 오차 때문에 +1 붙임.
    screenLine(WAYS_DOT, RIGHT_WAY_LINE_POS);  // 오른쪽 대각선.

    // 3. 창 테두리 그리기.
    screenBorder(DISPLAY_BORDER_DOT, 0,0,  SCWIDTH-1,SCHEIGHT-1);

    // 4. fps 출력.
    for ( uint16_t index=0; index<str_number; index++ )
    {
        screenPrint(5,2 + ( 3*index ), 1, getProp(str_number, uint8_t*, index));
    }
}



// 문자 위치 계산 함수.
// int16_t strRowPosition( const uint16_t str_row, const uint16_t row_margin, const uint32_t str_index )
// {
//     return( (str_row+row_margin)*str_index );
// }
#define strRowPosition( str_row, row_margin, str_index )\
( ((str_row)+(row_margin))*(str_index) )


// 선택 박스 오브젝트.
const pos_t start_box_obj[2] = {
    (pos_t){
        .x = SCWIDTH-SCWIDTH/3+strRowPosition(6,STR_MARGIN,0)-1-2,
        .y = SCHEIGHT-(SCHEIGHT/3)*1-1-2,
    },
    (pos_t){
        .x = SCWIDTH-SCWIDTH/3+strRowPosition(6,STR_MARGIN,4)+5-1+2,
        .y = SCHEIGHT-(SCHEIGHT/3)*1-1+8+2,
    },
};

const pos_t exit_box_obj[2] = {
    (pos_t){
        .x = SCWIDTH-SCWIDTH/3+strRowPosition(6,STR_MARGIN,0)-1-2,
        .y = SCHEIGHT-(SCHEIGHT/3)*2-1-2,
    },
    (pos_t){
        .x = SCWIDTH-SCWIDTH/3+strRowPosition(6,STR_MARGIN,3)+5-1+2-2,
        .y = SCHEIGHT-(SCHEIGHT/3)*2-1+8+2,
    },
};

const pos_t game_border_box_obj[2] = {
    {
        .x = 1,
        .y = 1,
    },
    {
        .x = SCWIDTH-2,
        .y = SCHEIGHT-2,
    },
};


// 메뉴 그리기.
void Straight$Menu$draw()
{
    screenPrint(
        SCWIDTH - SCWIDTH/3 + strRowPosition(6,STR_MARGIN,0) - 1, SCHEIGHT - (SCHEIGHT/3)*1 - 1,
        9,  // 6*9
        " @@@@ ",
        "@    @",
        "@     ",
        " @    ",
        "  @@  ",
        "    @ ",
        "     @",
        "@    @",
        " @@@@ "
    );
    screenPrint(
        SCWIDTH - SCWIDTH/3 + strRowPosition(6,STR_MARGIN,1) - 1, SCHEIGHT - (SCHEIGHT/3)*1 - 1,
        9,  // 6*9
        " @    ",
        " @    ",
        "@@@@@ ",
        " @    ",
        " @    ",
        " @    ",
        " @    ",
        " @    ",
        " @@@@@"
    );
    screenPrint(
        SCWIDTH - SCWIDTH/3 + strRowPosition(6,STR_MARGIN,2) - 1, SCHEIGHT - (SCHEIGHT/3)*1 - 1,
        9,  // 6*9
        "      ",
        " @@@  ",
        "@   @ ",
        "    @ ",
        "  @@@ ",
        " @  @ ",
        "@   @ ",
        "@   @ ",
        " @@@ @"
    );
    screenPrint(
        SCWIDTH - SCWIDTH/3 + strRowPosition(6,STR_MARGIN,3) - 1, SCHEIGHT - (SCHEIGHT/3)*1 - 1,
        9,  // 6*9
        "      ",
        " @    ",
        " @ @@ ",
        " @@  @",
        " @    ",
        " @    ",
        " @    ",
        " @    ",
        " @    "
    );
    screenPrint(
        SCWIDTH - SCWIDTH/3 + strRowPosition(6,STR_MARGIN,4) - 1, SCHEIGHT - (SCHEIGHT/3)*1 - 1,
        9,  // 6*9
        " @    ",
        " @    ",
        "@@@@@ ",
        " @    ",
        " @    ",
        " @    ",
        " @    ",
        " @    ",
        " @@@@@"
    );
    // screenBorder('~', SCWIDTH-SCWIDTH/3+strRowPosition(6,STR_MARGIN,0)-1-2, SCHEIGHT-(SCHEIGHT/3)*1-1-2,  SCWIDTH-SCWIDTH/3+strRowPosition(6,STR_MARGIN,4)+5-1+2, SCHEIGHT-(SCHEIGHT/3)*1-1+8+2);
    screenBorder(BOX_BORDER_DOT, start_box_obj[0].x, start_box_obj[0].y,  start_box_obj[1].x, start_box_obj[1].y);


    screenPrint(
        SCWIDTH - SCWIDTH/3 + strRowPosition(6,STR_MARGIN,0) - 1, SCHEIGHT - (SCHEIGHT/3)*2 - 1,
        9,  // 6*9
        "@@@@@@",
        "@     ",
        "@     ",
        "@     ",
        "@@@@@@",
        "@     ",
        "@     ",
        "@     ",
        "@@@@@@"
    );
    screenPrint(
        SCWIDTH - SCWIDTH/3 + strRowPosition(6,STR_MARGIN,1) - 1, SCHEIGHT - (SCHEIGHT/3)*2 - 1,
        9,  // 6*9
        "      ",
        "      ",
        "@    @",
        "@    @",
        " @  @ ",
        "  @@  ",
        " @  @ ",
        "@    @",
        "@    @"
    );
    screenPrint(
        SCWIDTH - SCWIDTH/3 + strRowPosition(6,STR_MARGIN,2) - 1, SCHEIGHT - (SCHEIGHT/3)*2 - 1,
        9,  // 6*9
        "  @   ",
        "      ",
        "  @   ",
        "  @   ",
        "  @   ",
        "  @   ",
        "  @   ",
        "  @   ",
        "  @   "
    );
    screenPrint(
        SCWIDTH - SCWIDTH/3 + strRowPosition(6,STR_MARGIN,3) - 1 - 2, SCHEIGHT - (SCHEIGHT/3)*2 - 1,
        9,  // 6*9
        " @    ",
        " @    ",
        "@@@@@ ",
        " @    ",
        " @    ",
        " @    ",
        " @    ",
        " @    ",
        " @@@@@"
    );
    // screenBorder('~', SCWIDTH-SCWIDTH/3+strRowPosition(6,STR_MARGIN,0)-1-2, SCHEIGHT-(SCHEIGHT/3)*2-1-2,  SCWIDTH-SCWIDTH/3+strRowPosition(6,STR_MARGIN,3)+5-1+2-2, SCHEIGHT-(SCHEIGHT/3)*2-1+8+2);
    screenBorder(BOX_BORDER_DOT, exit_box_obj[0].x, exit_box_obj[0].y,  exit_box_obj[1].x, exit_box_obj[1].y);
}

// 선택 박스 오브젝트.
pos_t select_box_obj[2] = {
    {
        .x = game_border_box_obj[0].x,
        .y = game_border_box_obj[0].y,
    },
    {
        .x = game_border_box_obj[1].x,
        .y = game_border_box_obj[1].y,
    },
};

// 선택 박스 그리기.
void Straight$Menu$drawSelectBox()
{
    screenBorder(SELECT_BOX_DOT, select_box_obj[0].x-1, select_box_obj[0].y-1,  select_box_obj[1].x+1, select_box_obj[1].y+1);    
}

// 선택 박스 애니메이션.
enum Button_state Straight$Menu$animateUpdate( const key_code_t set, enum Active active )
{
    // 1. 이전 상태 저장 변수.
    static enum Button_state selected_btn = Start;
    static enum Move_state
    {
        Not_moving, First_moving, Moving
    } is_moving = First_moving;  // 게임 시작시부터 애니메이션 활성화.
    // static int64_t animate_slider = 0;
    static double animate_slider = 0.0;
    static pos_t animate_start_pos[2] = {
        {
            .x = 0,
            .y = 0,
        },
        {
            .x = 0,
            .y = 0,
        },
    };
    static pos_t animate_end_pos[2] = {
        {
            .x = 0,
            .y = 0,
        },
        {
            .x = 0,
            .y = 0,
        },
    };
    // 2. 임시 변수.
    // - 방향키 변수.
    enum Key
    {
        Key_Nothing, Arrow_top, Arrow_right, Arrow_bottom, Arrow_left, Enter,
    } key;
    // - 반환할 버튼 상태 변수.
    enum Button_state return_selected_btn = Nothing;



    // 3. 방향키 감지.
    if ( set.option == 0 && set.key_code == 0 )
        key = Key_Nothing;
    else if ( set.option == 224 && set.key_code == 72 )
        key = Arrow_top;
    else if ( set.option == 224 && set.key_code == 80 )
        key = Arrow_bottom;
    else if ( set.option == 0 && set.key_code == 13 )
        key = Enter;
    else key = Key_Nothing;
    
    // 3. 키가 눌렸을 때.
    if ( key != Key_Nothing || !(set.option==0 && set.key_code==0) )
    {
        // 1. 애니메이션 처음 시작 상태로 전환.
        // is_moving = First_moving;
        // is_moving = Not_moving;

        // 2. 버튼 상태 업데이트.
        if ( active == MainHome && key == Arrow_top )
        {
            // 0. 애니메이션 시작 상태로 변경.
            is_moving = First_moving;
            // 1. 위로 버튼.
            selected_btn--;
            // 2. 키 되돌아가기.
            if ( ((signed)selected_btn) < Start )
            {
                selected_btn = Exit;
            }
        }
        else if ( active == MainHome && key == Arrow_bottom )
        {
            // 0. 애니메이션 시작 상태로 변경.
            is_moving = First_moving;
            // 1. 아래 버튼.
            selected_btn++;
            // 2. 되돌아가기.
            if ( (signed)selected_btn > Exit )
            {
                selected_btn = Start;
            }
        }
        // 3. 엔터키가 눌렸고 애니메이션이 끝나있다면.
        else if ( active == MainHome && key == Enter && is_moving == Not_moving )
        {
            // 1. 시작 버튼에서 엔터 누를 시 시작 상태 반환.
            if ( selected_btn == Start )
            {
                // return_selected_btn = Start;
                // 0. 애니메이션 시작 상태로 변경.
                is_moving = First_moving;
                // 1. 스크린 보더선택.
                selected_btn = Screen_border;
            }
            // 2. 종료 버튼에서 엔터 누를 시 종료 상태 반환.
            else if ( selected_btn == Exit )
            {
                return_selected_btn = Exit;
            }
        }
        else if ( active == inGame && set.option == 0 && set.key_code == 27 && selected_btn == Screen_border )
        {
            is_moving = First_moving;
            selected_btn = Start;
            return_selected_btn = To_menu;
        }
    }

    // 4. 애니메이션 처리.
    // - 애니메이션 처음 시작인 경우 초기화.
    if ( is_moving == First_moving )
    {
        // 1. 애니메이션 슬라이더 초기화.
        animate_slider = 0;

        // 2. 애니메이션 박스 출발 좌표 초기화.
        // - 현재 선택 박스의 위치부터 시작함.
        animate_start_pos[0] = (pos_t){
            .x = select_box_obj[0].x,
            .y = select_box_obj[0].y,
        };
        animate_start_pos[1] = (pos_t){
            .x = select_box_obj[1].x,
            .y = select_box_obj[1].y,
        };

        // 3. 애니메이션 박스 도착 좌표 초기화.
        pos_t pos[2] = {0};
        switch ( selected_btn )
        {
            // 1. 시작 버튼으로 이동해야하는 경우.
            case Start :
            pos[0].x = start_box_obj[0].x;
            pos[0].y = start_box_obj[0].y;
            pos[1].x = start_box_obj[1].x;
            pos[1].y = start_box_obj[1].y;
            break;

            // 2. 종료 버튼으로 이동해야하는 경우.
            case Exit :
            pos[0].x = exit_box_obj[0].x;
            pos[0].y = exit_box_obj[0].y;
            pos[1].x = exit_box_obj[1].x;
            pos[1].y = exit_box_obj[1].y;
            break;

            // 3. 창 테두리로 이동해야하는 경우.
            case Screen_border :
            // - 또는 그 외의 경우.
            default :
            pos[0].x = game_border_box_obj[0].x;
            pos[0].y = game_border_box_obj[0].y;
            pos[1].x = game_border_box_obj[1].x;
            pos[1].y = game_border_box_obj[1].y;
        }

        animate_end_pos[0] = pos[0];
        animate_end_pos[1] = pos[1];
        
        // 4. 다음으로 넘어가기 위해 애니메이션 상태 변경.
        is_moving = Moving;
    }
    if ( is_moving == Moving )
    {
        // 1. 현재 선택 박스 오브젝트 좌표 업데이트.
        select_box_obj[0].x = sinEx(
            animate_start_pos[0].x,
            animate_end_pos[0].x,
            animate_slider
        );
        select_box_obj[0].y = sinEx(
            animate_start_pos[0].y,
            animate_end_pos[0].y,
            animate_slider
        );
        select_box_obj[1].x = sinEx(
            animate_start_pos[1].x,
            animate_end_pos[1].x,
            animate_slider
        );
        select_box_obj[1].y = sinEx(
            animate_start_pos[1].y,
            animate_end_pos[1].y,
            animate_slider
        );


        // if ( animate_slider == 156 )
        
        if ( animate_slider > 1.57096 )
        {
            animate_slider = 1.57096;
        }
        else if ( animate_slider == 1.57096 )
        {
            // 1. 종료상태로 변경.
            is_moving = Not_moving;

            switch ( selected_btn )
            {
                // 1. 만약 시작 매뉴를 엔터하고 화면 보더까지 애니메이션이 완료된 것이라면 시작 상태 반환.
                case Screen_border :  return_selected_btn = Start;break;
                default:;
            }
            
        }
        else
        {
            animate_slider+=SELECT_BOX_SPEED;
        }

    }
    
    return( return_selected_btn );
}



uint8_t Straight$key_is_move( key_code_t get_set )
{
    // switch ( get_key_code )
    // {
    //     case 'w':
    //     case 'W': return( 1 );
    //     default : return( 0 );
    // }
    if (
        (
            get_set.option == 224 &&
            get_set.key_code == 72
        ) ||
        get_set.key_code == 'w' ||
        get_set.key_code == 'W'
    )
    {
        return( 1 );
    }
    return( 0 );
}


struct class$Straight
{
    uint8_t(*const key_is_move)( key_code_t get_set );
    struct _Game
    {
        struct _Object
        {
            side_obj_t(*const newRightSideObject)( uint32_t set_wait_time );
            side_obj_t(*const newLeftSideObject)( uint32_t set_wait_time );
            void(*const addLeftSideObject)( side_obj_t obj );
            void(*const addRightSideObject)( side_obj_t obj );
        } Object;
    } Game;
    struct _Menu
    {
        void(*const draw)(void);
        void(*const drawSelectBox)(void);
        enum Button_state(*const animateUpdate)( const key_code_t set, enum Active active );
    } Menu;
} Straight = {
    .Game = {
        .Object = {
            .addLeftSideObject = Straight$addLeftSideObject,
            .addRightSideObject = Straight$addRightSideObject,
            .newLeftSideObject = Straight$newLeftSideObject,
            .newRightSideObject = Straight$newRightSideObject,
        },
    },
    Menu : {
        draw : Straight$Menu$draw,
        drawSelectBox : Straight$Menu$drawSelectBox,
        animateUpdate : Straight$Menu$animateUpdate,
    },
    key_is_move : Straight$key_is_move,
};
