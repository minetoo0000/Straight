#pragma once
/*
    ��Ű�� : '����' ���� ��Ű��.
    ���� : '����' ���� ��ü�� �����ϴ� ��Ű��.
*/
#include "./../../HEADER/TGI-library-master.h"
#include "./../../HEADER/Cobject/cobject.h"
#include "./../../HEADER/Timer.h"

// ���ư��� �ӵ�.
#define WORK_SPEED 1

// ���� �ڽ� �̵� �ӵ�.
#define SELECT_BOX_SPEED 0.03

// �߾� �ҽ��� ��ǥ.
#define CENTER_X SCWIDTH/2-1
#define CENTER_Y SCHEIGHT/2-1-10

// ȭ�� �Ʒ� �� ���� �� �Ʒ� �� ���� ����.
#define WAY_MARGIN 40

// �߰� ������ ���̵� ������Ʈ �ִ� ����.
#define SIDE_OBJ_LENGTH 500

// ���÷��� �׵θ� ����.
#define DISPLAY_BORDER_DOT '.'

// ������Ʈ ����.
#define OBJ_CHAR ','

// ������Ʈ ���� �𼭸� ����.
#define OBJ_INSIDE_DOT '_'

// �� ����.
#define WAYS_DOT '.'

// ���� ���� ����.
#define STRING_DOT '@'

// ���� �ڽ� ����.
#define SELECT_BOX_DOT '#'

// �ڽ� �׵θ� ����.
#define BOX_BORDER_DOT '+'

// ���� ������ ����.
#define STR_MARGIN 1

// ������Ʈ ����.
#define OBJ_LENGTH 1700

// ���� ȭ�� ���� ������Ʈ �߰� ����
#define LEFT_OBJ_ADD_DELAY 5500

// ���� ȭ�� ������ ������Ʈ �߰� ����
#define RIGHT_OBJ_ADD_DELAY 4000

// ���÷��� ������
#define DISPLAY_FRAME 32

// ��Ÿ Ÿ�� ������.
#define DELTA_TIME_FRAME 70

// ���� ���� �밢���� ��ǥ.
#define LEFT_WAY_LINE_POS left_side_way_pos.x,left_side_way_pos.y,  center_way_pos.x+2, center_way_pos.y

// ���� ������ �밢���� ��ǥ.
#define RIGHT_WAY_LINE_POS right_side_way_pos.x,right_side_way_pos.y,  center_way_pos.x, center_way_pos.y

// ȭ�鿡�� ���̴� ������Ʈ�� �ִ� ����. ȭ�� ���� ��ǥ ����.
#define OBJECT_TALL (SCHEIGHT - SCHEIGHT/16)

// ��� ���� �밢���� ��ǥ.
#define LEFT_TOP_LINE_POS 0,OBJECT_TALL,  center_way_pos.x,center_way_pos.y

// ��� ������ �밢���� ��ǥ.
#define RIGHT_TOP_LINE_POS center_way_pos.x,center_way_pos.y,  SCWIDTH-1,OBJECT_TALL

//////////////////////////////// TODO : getLinePos�� ��ǥ�� ��� ��ü���!!!

// WAIT_TIME_DEFAULT�� ������ ��, ���ٰ��� ������ ���� ���μ� �ӵ� ���� ���.
#define DOWN_TIMER 1.035

// ������Ʈ�� ���μ� �� ĭ�� ������ ������ ��ٷ��� �ϴ� �ð� �⺻��.
#define WAIT_TIME_DEFAULT (500*(WORK_SPEED))


/// ��ü ���� ///

// ������Ʈ ��ü.
typedef struct type$class_Straight$obj_t
{
    // ���� �� ��.
    uint16_t topLeftX;
    uint16_t topLeftY;

    // ������ �� ��.
    uint16_t topRightX;
    uint16_t topRightY;

    // ������ �Ʒ� ��.
    uint16_t bottomRightX;
    uint16_t bottomRightY;

    // ���� �Ʒ� ��.
    uint16_t bottomLeftX;
    uint16_t bottomLeftY;
} obj_t;

// �������� ������Ʈ ��ü.
typedef struct type$class_Straight$side_obj_t
{
    /// ���� ���� ///
    // ���� ���� X��ǥ
    uint16_t leftX;

    // ���� Y��ǥ
    uint16_t topLeftY;
    uint16_t bottomLeftY;


    /// ������ ���� ///
    // ���� ������ X��ǥ.
    uint16_t rightX;

    // ������ Y��ǥ
    uint16_t topRightY;
    uint16_t bottomRightY;


    /// ���� ���μ� Ÿ�̸� ///
    // Ÿ�̸ӿ� ���Ǵ� �ð�.
    clock_t left_next_update_time;
    // Ÿ�̸� �ð� ���� ũ��.
    uint32_t left_down_time;


    /// ������ ���μ� Ÿ�̸� ///
    // Ÿ�̸ӿ� ���Ǵ� �ð�.
    clock_t right_next_update_time;
    // Ÿ�̸� �ð� ���� ũ��.
    uint32_t right_down_time;

    
    // �� ���μ��� ��� �ð��� Ÿ�̸�.
    clock_t wait_time;
    // �� ���μ��� ��� �ð���.
    uint32_t set_wait_time;

} side_obj_t;

enum Button_state
{
    // �޴� ����Ʈ�� ����.
    Start, Exit,

    // �޴� ����Ʈ�� �߰����� ����. (�ɼ�)
    Nothing, Screen_border, To_menu,
};



/// ���� ���� ���� ///
typedef struct type$Straight$side_obj_list_t
{
    uint8_t is_null[SIDE_OBJ_LENGTH];
    side_obj_t list[SIDE_OBJ_LENGTH];
} side_obj_list_t;

// ������ ������Ʈ ��� �迭.
side_obj_list_t right_objs = {
    .is_null = {0},
    .list = {0},
};
// ���� ������Ʈ ��� �迭.
side_obj_list_t left_objs = {
    .is_null = {0},
    .list = {0},
};


// ���� ��Ƽ��Ƽ ����.
// 0 : ���� ����.
// 1 : ���� ���� ȭ��.
// 2 : ���� �÷���.
// 3 : ��Ÿ.
// uint8_t screen_activity_state = 0;
enum Active
{
    MainHome,
    inGame,
} screen_activity_state = MainHome;

// ���ư� �Ÿ�.
// uint64_t step_count = 0;

// ���ư��� �ӵ�.
uint8_t work_speed = WORK_SPEED;

// �� �밢���� �߾� ��ǥ��.
pos_t center_way_pos = {
   .x = CENTER_X,
   .y = CENTER_Y,
};

// �� �밢�� ���� ���̵� ��ǥ��.
pos_t left_side_way_pos = {
   .x = WAY_MARGIN,
   .y = 0,
};

// �� �밢�� ������ ���̵� ��ǥ��.
pos_t right_side_way_pos = {
   .x = SCWIDTH-1-WAY_MARGIN,
   .y = 0,
};


/// �Լ� ���� ///

// side_obj_t ������Ʈ�� ���ۿ� �׷��ִ� �Լ�.
void Straight$side_obj_Draw( const side_obj_t* const obj )
{   // �� �Լ��� ���� �밢���� ������Ʈ�� ������ �밢���� ������Ʈ�� �׸���.
    // 1. ���� ������.
    screenLine(OBJ_CHAR, obj->leftX,obj->topLeftY,  obj->leftX,obj->bottomLeftY);

    // 2. ������ ������.
    screenLine(OBJ_CHAR, obj->rightX,obj->topRightY,  obj->rightX,obj->bottomRightY);

    // 3. ���� ������.
    screenLine(OBJ_CHAR, obj->leftX,obj->topLeftY,  obj->rightX,obj->topRightY);

    // 4. ���� �� ������.
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



// ȭ�� �ʱ�ȭ.
void ScreenInit()
{
    for (long i = 0; i < 100; i++) {  // cmd? ?????? ???? ?????? ???? cmd? ???? ???? ???? ????.
		printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
	}

    screenBegin();
    screenFill(' ');
    screenUpdate();
}


// ���� �ʱ�ȭ
void Straight$Game$init()
{
    memset(&left_objs, 0, sizeof(left_objs));
    memset(&right_objs, 0, sizeof(right_objs));
    memset(left_objs.is_null, o_true, sizeof(left_objs.is_null));
    memset(right_objs.is_null, o_true, sizeof(right_objs.is_null));
}


// ���� ������Ʈ ����Ʈ�� ������Ʈ �߰��ϴ� �Լ�.
void Straight$addLeftSideObject( side_obj_t obj )
{
    for ( uint16_t index=0; index<SIDE_OBJ_LENGTH; index++ )
    {

        if ( left_objs.is_null[index] == o_true )
        {   // ����ִٸ�.
            left_objs.list[index] = obj;
            left_objs.is_null[index] = o_false;

            // ����ִ� ������ ���������� ������Ʈ�� �߰������Ƿ� �Լ� ����.
            return;
        }

    }
    // ������Ʈ ���� ����.
    return;
}


// ������ ������Ʈ ����Ʈ�� ������Ʈ �߰��ϴ� �Լ�.
void Straight$addRightSideObject( side_obj_t obj )
{
    for ( uint16_t index=0; index<SIDE_OBJ_LENGTH; index++ )
    {

        if ( right_objs.is_null[index] == o_true )
        {   // ����ִٸ�.
            right_objs.list[index] = obj;
            right_objs.is_null[index] = o_false;

            // ����ִ� ������ ���������� ������Ʈ�� �߰������Ƿ� �Լ� ����.
            return;
        }

    }
    // ������Ʈ ���� ����.
    return;
}


// ���� ������Ʈ ����Ʈ���� ������Ʈ �����ϴ� �Լ�.
void Straight$deleteLeftSideObject( uint16_t delete_index )
{
    // 0. ������Ʈ ����Ʈ�� ����ִ� ������Ʈ ���� ���ϱ�.
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


// ������ ������Ʈ ����Ʈ���� ������Ʈ �����ϴ� �Լ�.
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


// ���� ������Ʈ ����Ʈ�� ���� ���� ���� ��ȯ.
uint8_t Straight$leftSideObjectState()
{
    for ( uint16_t index=0; index<SIDE_OBJ_LENGTH; index++ )
    {
        if ( left_objs.is_null[index] == o_true )
        {
            // ����ִ� ��찡 �ִٸ� 1 ��ȯ.
            return( o_true );
        }
    }

    // ����Ʈ�� �� ���ִ� ��� 0 ��ȯ.
    return( o_false );
}


// ������ ������Ʈ ����Ʈ�� ���� ���� ���� ��ȯ.
uint8_t Straight$rightSideObjectState()
{
    for ( uint16_t index=0; index<SIDE_OBJ_LENGTH; index++ )
    {
        if ( right_objs.is_null[index] == o_true )
        {
            // ����ִ� ��찡 �ִٸ� 1 ��ȯ.
            return( o_true );
        }
    }

    // ����Ʈ�� �� ���ִ� ��� 0 ��ȯ.
    return( o_false );
}


// ���� ������Ʈ ����Ʈ���� 1��° ������Ʈ �������� �Լ�. (�ڵ����� �������� ������.)
side_obj_t Straight$leftSideObjectGet()
{
    side_obj_t result = left_objs.list[0];
    Straight$deleteLeftSideObject(0);
    return( result );
}


// ������ ������Ʈ ����Ʈ���� 1��° ������Ʈ �������� �Լ�. (�ڵ����� �������� ������.)
side_obj_t Straight$rightSideObjectGet()
{
    side_obj_t result = right_objs.list[0];
    Straight$deleteRightSideObject(0);
    return( result );
}


// ���ο� ���� ������Ʈ ��ȯ�ϴ� �Լ�.
side_obj_t Straight$newLeftSideObject( uint32_t set_wait_time )
{
    return(
        (side_obj_t)
        {
            // ���� ���μ�.
            .leftX = center_way_pos.x,
            .topLeftY = center_way_pos.y,
            .bottomLeftY = center_way_pos.y,

            // ������ ���μ�.
            .rightX = center_way_pos.x,
            .topRightY = center_way_pos.y,
            .bottomRightY = center_way_pos.y,

            // ������Ʈ ����.
            .left_next_update_time = 0,
            .left_down_time = WAIT_TIME_DEFAULT,
            .right_next_update_time = 0,
            .right_down_time = WAIT_TIME_DEFAULT,
            .wait_time = 0,
            .set_wait_time = set_wait_time,
        }
    );
}


// ���ο� ���� ������Ʈ ��ȯ�ϴ� �Լ�.
side_obj_t Straight$newRightSideObject( uint32_t set_wait_time )
{
    return(
        (side_obj_t)
        {
            // ������ ���μ�.
            .rightX = center_way_pos.x,
            .topRightY = center_way_pos.y,
            .bottomRightY = center_way_pos.y,

            // ���� ���μ�.
            .leftX = center_way_pos.x,
            .topLeftY = center_way_pos.y,
            .bottomLeftY = center_way_pos.y,

            // ������Ʈ ����.
            .left_next_update_time = 0,
            .left_down_time = WAIT_TIME_DEFAULT,
            .right_next_update_time = 0,
            .right_down_time = WAIT_TIME_DEFAULT,
            .wait_time = 0,
            .set_wait_time = set_wait_time,
        }
    );
}


// ���� ������Ʈ�� ��ǥ ������Ʈ.
void Straight$Game$leftSideObjectUpdate( side_obj_list_t* full_obj, uint16_t index )
{
    // 0. ���� �ð� ����(ĸó) & ������Ʈ �и�.
    register clock_t current_time = clock_ms();
    side_obj_t* obj = full_obj->list+index;

    // 1. �ð����� �ξ� ������Ʈ ��Ű�� ���� Ÿ�̸� �ʱ�ȭ.
    if ( obj->wait_time == 0 ) //Ÿ�̸� ������ ���� ���ο� ������Ʈ�� ���.
    {
        // 1. ���� ������Ʈ�� ����ִ� �ð��� ������ Ÿ�̸Ӹ� ������.
        obj->wait_time = obj->set_wait_time + current_time;
    }

    // 2. ������ ���μ��� ���� Ÿ�̸�. �ٸ� �ð����� �ΰ� ��ǥ ������Ʈ.
    // - Ÿ�̸� ������ ���� ���ο� ������Ʈ���� �ƴϸ� Ÿ�̸Ӱ� �۵����� ������Ʈ���� �����ؾ���.
    if ( current_time > obj->wait_time )  // Ÿ�̸Ӱ� �Ϸ�� ��� ��ǥ ������Ʈ.
    {
        // 0. ���μ� ������Ʈ Ÿ�̸�.
        if ( current_time > obj->right_next_update_time )
        {
            // 1. ������ ���μ� X��ǥ ������Ʈ & ��ǥ ��Ż ����.
            if ( obj->rightX > 0 ) obj->rightX--;

            // 2. ������ ���μ� ��� Y��ǥ ������Ʈ & ��ǥ ��Ż ����.
            if ( obj->topRightY < SCHEIGHT-1 ) obj->topRightY = getLinePos(LEFT_TOP_LINE_POS, obj->rightX, -1)+1;  // �ڿ��������� ���� ������Ʈ�� �⺻ ���� �߰�.

            // 3. ������ ���μ� �ϴ� Y��ǥ ������Ʈ & ��ǥ ��Ż ����.
            if ( obj->bottomRightY > 0 ) obj->bottomRightY = getLinePos(LEFT_WAY_LINE_POS, obj->rightX, -1);

            // 4. Ÿ�̸� ������Ʈ.
            obj->right_next_update_time = obj->right_down_time + current_time;
        }
        // 1. Ÿ�̸� ��ȭ�� ������Ʈ & ���� �� �����÷ο� ����.
        if ( obj->right_down_time > 0 ) obj->right_down_time -= 2 * WORK_SPEED;
    }

    // 3. ���� ���μ��� ���� Ÿ�̸�.
    if ( current_time > obj->left_next_update_time )
    {
        // 1. ���� ���μ� X��ǥ ������Ʈ & ��ǥ ��Ż ����.
        if ( obj->leftX > 0 ) obj->leftX--;

        // 2. ���� ���μ� ��� Y��ǥ ������Ʈ & ��ǥ ��Ż ����.
        if ( obj->topLeftY < SCHEIGHT-1 ) obj->topLeftY = getLinePos(LEFT_TOP_LINE_POS, obj->leftX, -1)+1;

        // 3. ���� ���μ� �ϴ� Y��ǥ ������Ʈ & ��ǥ ��Ż ����.
        if ( obj->bottomLeftY > 0 ) obj->bottomLeftY = getLinePos(LEFT_WAY_LINE_POS, obj->leftX, -1);

        // 4. Ÿ�̸� ������Ʈ.
        obj->left_next_update_time = obj->left_down_time + current_time;

    }
    // 4. Ÿ�̸� ��ȭ�� ������Ʈ & ���� �� �����÷ο� ����.
    if ( obj->left_down_time > 0 ) obj->left_down_time -= 2 * WORK_SPEED;
}


// ������ ������Ʈ�� ��ǥ ������Ʈ.
void Straight$Game$rightSideObjectUpdate( side_obj_list_t* full_obj, uint16_t index )
{
    // 0. ���� �ð� ����(ĸó) & ������Ʈ �и�.
    register clock_t current_time = clock_ms();
    side_obj_t* obj = full_obj->list+index;

    // 1. �ð����� �ξ� ������Ʈ ��Ű�� ���� Ÿ�̸� �ʱ�ȭ.
    if ( obj->wait_time == 0 )  // ���ο� ������Ʈ�� ���.
    {
        // 1. ���� ������Ʈ�� ����ִ� �ð��� ������ Ÿ�̸Ӹ� ������.
        obj->wait_time = obj->set_wait_time + current_time;
    }
    
    // 2. ���� ���μ��� ���� Ÿ�̸�. �ٸ� �ð����� �ΰ� ��ǥ�� ������Ʈ ��Ų��.
    if ( current_time > obj->wait_time )
    {
        if ( current_time > obj->left_next_update_time )
        {
            // 1. ���� ���μ� X��ǥ ������Ʈ & ��ǥ ��Ż ����.
            if ( obj->leftX < SCWIDTH-1 ) obj->leftX++;

            // 2. ���� ���μ� ��� Y��ǥ ������Ʈ & ��ǥ ��Ż ����.
            if ( obj->topLeftY < SCHEIGHT-1 ) obj->topLeftY = getLinePos(RIGHT_TOP_LINE_POS, obj->leftX, -1)+1;

            // 3. ���� ���μ� �ϴ� Y��ǥ ������Ʈ & ��ǥ ��Ż ����.
            if ( obj->bottomLeftY > 0 ) obj->bottomLeftY = getLinePos(RIGHT_WAY_LINE_POS, obj->leftX, -1);
            
            // 4. Ÿ�̸� ������Ʈ.
            obj->left_next_update_time = obj->left_down_time + current_time;
        }
        // 3. Ÿ�̸� ��ȭ�� ������Ʈ & ���� �� �����÷ο� ����.
        if ( obj->left_down_time > 0 ) obj->left_down_time -= 2 * WORK_SPEED;
    }


    // 4. ������ ���μ��� ���� Ÿ�̸�.
    if ( current_time > obj->right_next_update_time )
    {
        // 1. ������ ���μ� X��ǥ ������Ʈ & ��ǥ ��Ż ����.
        if ( obj->rightX < SCWIDTH-1 ) obj->rightX++;

        // 2. ������ ���μ� ��� Y��ǥ ������Ʈ & ��ǥ ��Ż ����.
        if ( obj->topRightY < SCHEIGHT-1 ) obj->topRightY = getLinePos(RIGHT_TOP_LINE_POS, obj->rightX, -1)+1;

        // 3. ������ ���μ� �ϴ� Y��ǥ ������Ʈ & ��ǥ ��Ż ����.
        if ( obj->bottomRightY > 0 ) obj->bottomRightY = getLinePos(RIGHT_WAY_LINE_POS, obj->rightX, -1);

        // 4. Ÿ�̸� ������Ʈ.
        obj->right_next_update_time = obj->right_down_time + current_time;
    }
    // 5. Ÿ�̸� ��ȭ�� ������Ʈ & ���� �� �����÷ο� ����.
    if ( obj->right_down_time > 0 ) obj->right_down_time -= 2 * WORK_SPEED;
}


// ȭ�� ������ ���� ���� ������Ʈ �ڵ����� ����.
void Straight$Game$leftSideObjectAutoDelete( side_obj_list_t* full_obj, uint16_t index )
{
    // 0. ������Ʈ �и�.
    side_obj_t* obj = full_obj->list+index;
    
    // 1. ������ ���μ� X��ǥ�� 0���� Ȯ��.
    if ( obj->rightX <= 0 )
    {
        // 2. �ش� ������Ʈ�� ����.
        Straight$deleteLeftSideObject(index);
    }
}


// ȭ�� ������ ���� ������ ������Ʈ �ڵ����� ����.
void Straight$Game$rightSideObjectAutoDelete( side_obj_list_t* full_obj, uint16_t index )
{
    // 0. ������Ʈ �и�.
    side_obj_t* obj = full_obj->list+index;
    
    // 1. ���� ���μ� X��ǥ�� ȭ�� ���� �����ʿ� �ִ��� Ȯ��.
    if ( obj->leftX >= SCWIDTH-1 )
    {
        // 2. �ش� ������Ʈ�� ����.
        Straight$deleteRightSideObject(index);
    }
}


// ���� �÷��� ��ü�� ���� ��ǥ ������Ʈ �Լ�.
void Straight$Game$AnimateUpdate()
{
    // 0. ���� �ð� ������ ����.
    register clock_t current_time = clock_ms();

    // 1. ���� ������Ʈ ��ǥ�� ������Ʈ.
    for ( uint16_t index=0; index<SIDE_OBJ_LENGTH; index++ )
    {
        // 0. ����� ������Ʈ�� ó�� �� ��.
        if ( left_objs.is_null[index] == o_true )
        {
            continue;
        }
        
        // 0. ���� ������Ʈ �ڵ� ����.
        Straight$Game$leftSideObjectAutoDelete(&left_objs, index);
        
        // 1. ���� ���� ������Ʈ ��ǥ ������Ʈ.
        Straight$Game$leftSideObjectUpdate(&left_objs, index);
    }
    
    // 2. ������ ������Ʈ ��ǥ�� ������Ʈ.
    for ( uint16_t index=0; index<SIDE_OBJ_LENGTH; index++ )
    {
        // 0. ����� ������Ʈ�� ó�� �� ��.
        if ( right_objs.is_null[index] == o_true )
        {
            continue;
        }

        // 0. ������ ������Ʈ �ڵ� ����.
        Straight$Game$rightSideObjectAutoDelete(&right_objs, index);        

        // 1. ���� ������ ������Ʈ ��ǥ ������Ʈ.
        Straight$Game$rightSideObjectUpdate(&right_objs, index);        
    }
}


// ���� �׷��� �׸��� �Լ�.
void Straight$Game$GraphicDraw( uint16_t str_number, ... )
{
    // 0. ȭ�� ����.
    screenFill(' ');


    // ���� �׽�Ʈ.
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

    // 1. ������Ʈ �׸���.
    for ( int index=0; index<SIDE_OBJ_LENGTH; index++ )
    {
        // 0. ȭ�� ���� ������Ʈ �׸���.
        if ( left_objs.is_null[index] == o_false )
        {
            Straight$side_obj_Draw(&left_objs.list[index]);  // ������Ʈ�� ����Ʈ�� �����ϸ�, �ش� ������Ʈ �����ͷ� �׸�.
        }

        // 1. ȭ�� ������ ������Ʈ �׸���.
        if ( right_objs.is_null[index] == o_false )
        {
            Straight$side_obj_Draw(&right_objs.list[index]);
        }   
    }

    // 2. �� �׸���.
    screenLine(WAYS_DOT, LEFT_WAY_LINE_POS);  // ���� �밢��. ���� ������ +1 ����.
    screenLine(WAYS_DOT, RIGHT_WAY_LINE_POS);  // ������ �밢��.

    // 3. â �׵θ� �׸���.
    screenBorder(DISPLAY_BORDER_DOT, 0,0,  SCWIDTH-1,SCHEIGHT-1);

    // 4. fps ���.
    for ( uint16_t index=0; index<str_number; index++ )
    {
        screenPrint(5,2 + ( 3*index ), 1, getProp(str_number, uint8_t*, index));
    }
}



// ���� ��ġ ��� �Լ�.
// int16_t strRowPosition( const uint16_t str_row, const uint16_t row_margin, const uint32_t str_index )
// {
//     return( (str_row+row_margin)*str_index );
// }
#define strRowPosition( str_row, row_margin, str_index )\
( ((str_row)+(row_margin))*(str_index) )


// ���� �ڽ� ������Ʈ.
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


// �޴� �׸���.
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

// ���� �ڽ� ������Ʈ.
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

// ���� �ڽ� �׸���.
void Straight$Menu$drawSelectBox()
{
    screenBorder(SELECT_BOX_DOT, select_box_obj[0].x-1, select_box_obj[0].y-1,  select_box_obj[1].x+1, select_box_obj[1].y+1);    
}

// ���� �ڽ� �ִϸ��̼�.
enum Button_state Straight$Menu$animateUpdate( const key_code_t set, enum Active active )
{
    // 1. ���� ���� ���� ����.
    static enum Button_state selected_btn = Start;
    static enum Move_state
    {
        Not_moving, First_moving, Moving
    } is_moving = First_moving;  // ���� ���۽ú��� �ִϸ��̼� Ȱ��ȭ.
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
    // 2. �ӽ� ����.
    // - ����Ű ����.
    enum Key
    {
        Key_Nothing, Arrow_top, Arrow_right, Arrow_bottom, Arrow_left, Enter,
    } key;
    // - ��ȯ�� ��ư ���� ����.
    enum Button_state return_selected_btn = Nothing;



    // 3. ����Ű ����.
    if ( set.option == 0 && set.key_code == 0 )
        key = Key_Nothing;
    else if ( set.option == 224 && set.key_code == 72 )
        key = Arrow_top;
    else if ( set.option == 224 && set.key_code == 80 )
        key = Arrow_bottom;
    else if ( set.option == 0 && set.key_code == 13 )
        key = Enter;
    else key = Key_Nothing;
    
    // 3. Ű�� ������ ��.
    if ( key != Key_Nothing || !(set.option==0 && set.key_code==0) )
    {
        // 1. �ִϸ��̼� ó�� ���� ���·� ��ȯ.
        // is_moving = First_moving;
        // is_moving = Not_moving;

        // 2. ��ư ���� ������Ʈ.
        if ( active == MainHome && key == Arrow_top )
        {
            // 0. �ִϸ��̼� ���� ���·� ����.
            is_moving = First_moving;
            // 1. ���� ��ư.
            selected_btn--;
            // 2. Ű �ǵ��ư���.
            if ( ((signed)selected_btn) < Start )
            {
                selected_btn = Exit;
            }
        }
        else if ( active == MainHome && key == Arrow_bottom )
        {
            // 0. �ִϸ��̼� ���� ���·� ����.
            is_moving = First_moving;
            // 1. �Ʒ� ��ư.
            selected_btn++;
            // 2. �ǵ��ư���.
            if ( (signed)selected_btn > Exit )
            {
                selected_btn = Start;
            }
        }
        // 3. ����Ű�� ���Ȱ� �ִϸ��̼��� �����ִٸ�.
        else if ( active == MainHome && key == Enter && is_moving == Not_moving )
        {
            // 1. ���� ��ư���� ���� ���� �� ���� ���� ��ȯ.
            if ( selected_btn == Start )
            {
                // return_selected_btn = Start;
                // 0. �ִϸ��̼� ���� ���·� ����.
                is_moving = First_moving;
                // 1. ��ũ�� ��������.
                selected_btn = Screen_border;
            }
            // 2. ���� ��ư���� ���� ���� �� ���� ���� ��ȯ.
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

    // 4. �ִϸ��̼� ó��.
    // - �ִϸ��̼� ó�� ������ ��� �ʱ�ȭ.
    if ( is_moving == First_moving )
    {
        // 1. �ִϸ��̼� �����̴� �ʱ�ȭ.
        animate_slider = 0;

        // 2. �ִϸ��̼� �ڽ� ��� ��ǥ �ʱ�ȭ.
        // - ���� ���� �ڽ��� ��ġ���� ������.
        animate_start_pos[0] = (pos_t){
            .x = select_box_obj[0].x,
            .y = select_box_obj[0].y,
        };
        animate_start_pos[1] = (pos_t){
            .x = select_box_obj[1].x,
            .y = select_box_obj[1].y,
        };

        // 3. �ִϸ��̼� �ڽ� ���� ��ǥ �ʱ�ȭ.
        pos_t pos[2] = {0};
        switch ( selected_btn )
        {
            // 1. ���� ��ư���� �̵��ؾ��ϴ� ���.
            case Start :
            pos[0].x = start_box_obj[0].x;
            pos[0].y = start_box_obj[0].y;
            pos[1].x = start_box_obj[1].x;
            pos[1].y = start_box_obj[1].y;
            break;

            // 2. ���� ��ư���� �̵��ؾ��ϴ� ���.
            case Exit :
            pos[0].x = exit_box_obj[0].x;
            pos[0].y = exit_box_obj[0].y;
            pos[1].x = exit_box_obj[1].x;
            pos[1].y = exit_box_obj[1].y;
            break;

            // 3. â �׵θ��� �̵��ؾ��ϴ� ���.
            case Screen_border :
            // - �Ǵ� �� ���� ���.
            default :
            pos[0].x = game_border_box_obj[0].x;
            pos[0].y = game_border_box_obj[0].y;
            pos[1].x = game_border_box_obj[1].x;
            pos[1].y = game_border_box_obj[1].y;
        }

        animate_end_pos[0] = pos[0];
        animate_end_pos[1] = pos[1];
        
        // 4. �������� �Ѿ�� ���� �ִϸ��̼� ���� ����.
        is_moving = Moving;
    }
    if ( is_moving == Moving )
    {
        // 1. ���� ���� �ڽ� ������Ʈ ��ǥ ������Ʈ.
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
            // 1. ������·� ����.
            is_moving = Not_moving;

            switch ( selected_btn )
            {
                // 1. ���� ���� �Ŵ��� �����ϰ� ȭ�� �������� �ִϸ��̼��� �Ϸ�� ���̶�� ���� ���� ��ȯ.
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
