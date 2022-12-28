
#include <stdio.h>
#include "./../user$Keyboard/pkg.h"
#include "./pkg.h"



int main()
{
    ScreenInit();
    Straight$Game$init();
    
    register clock_t current_time = clock_ms();
    register clock_t display_next_update_time = current_time;
    register clock_t add_obj_next_update_time = current_time;
    register clock_t add_left_obj_timer = current_time;
    register clock_t add_right_obj_timer = current_time;
    uint16_t timeline_current_index = 0;
    register clock_t animate_next_update_time = current_time;
    // register uint8_t key_code = 0;
    register clock_t fps_timer = current_time;
    uint8_t fps_screen_bf[128] = {0};
    uint16_t flexible_fps = DISPLAY_FRAME;
    uint16_t target_fps = DISPLAY_FRAME;

    ///////////////////////////// �Ʒ��� �ִ� �������� ���� �ʱ�ȭ �ÿ� 0���� ����.
    register uint16_t fps_counter = 0;
    register uint16_t fps_capture = 0;
    register clock_t timeline_timer = 0;
    register key_code_t key_code = {
        .key_code = 0,
        .option = 0,
    };
    register key_code_t btn_key_code = {
        .key_code = 0,
        .option = 0,
    };
    enum Button_state select_btn = Nothing;  // Nothing���� �ʱ�ȭ!.
    uint8_t need_buffer_write = 1;



    // ������Ʈ Ÿ�Ӷ���.
    enum TimelineOption
    {
        None,  // �ƹ� �ɼǵ� ���� ����.
        Up,  // ���� ������Ŵ.
        Down,  // ���� ���ҽ�Ŵ.
        // Random,  // ������ ����.
    };
    typedef struct _timeline_info_t {
        clock_t left_delay;  // ���� ������Ʈ �߰� ������ ������.
        clock_t right_delay;  // ������ ������Ʈ �߰� ������ ������.
        clock_t set_timer;  // ������ ���ӽð�.
        enum TimelineOption option;  // ������ �ɼ�.
    } timeline_info_t;

    timeline_info_t obj_timeline[] = {
        // {   // ó���� ��� ��� ������Ʈ�� ����.
        //     .left_delay = 8000,
        //     .right_delay = 10000,
        //     .set_timer = 10000,
        //     .option = None,
        // },
        // {   // ���� �� ���� ������.
        //     left_delay : 4000,
        //     right_delay : 5000,
        //     set_timer : 5000,
        //     option : None,
        // },
        // {   // ���� �� ������.
        //     .left_delay = 2500,
        //     .right_delay = 2500,
        //     .set_timer = 5000,
        //     .option = Down,
        // },
        // {   // �����ϰ� ��ó�� �߰���.
        //     .left_delay = 1700,
        //     .right_delay = 1700,
        //     .set_timer = 20000,
        //     .option = None,
        // },
        // {  // �ʵ��� �� ȭ��.
        //     .left_delay = 10000,
        //     .right_delay = 10000,
        //     .set_timer = 9000,
        //     .option = None,
        // },
        // {   // �Ͼ� �� ������.
        //     .left_delay = 6,
        //     .right_delay = 6,
        //     .set_timer = 20000,
        //     .option = None,
        // },
        // {   // ���� �� �������� ������.
        //     .left_delay = 9000,
        //     .right_delay = 8000,
        //     .set_timer = 20000,
        //     .option = None,
        // },
        // {   // ������ �������� ������.
        //     .left_delay = 4000,
        //     .right_delay = 4000,
        //     .set_timer = 20000,
        //     .option = None,
        // },
        // {   // ���� ���� �������� ������.
        //     .left_delay = 2000,
        //     .right_delay = 2000,
        //     .set_timer = 10000,
        //     .option = None,
        // },
        // {   // 10�ʵ��� �������� ����.
        //     .left_delay = 10000,
        //     .right_delay = 10000,
        //     .set_timer = 10000,
        //     .option = None,
        // },  // �������� �ٽ� ó�� Ÿ�Ӷ������� ���ư���.
        //////////////////////////// �Ʒ��� �ÿ��� Ÿ�Ӷ��� (�ð�����)
        {   // ó���� ��� ��� ������Ʈ�� ����.
            .left_delay = 8000,
            .right_delay = 10000,
            .set_timer = 5000,
            .option = None,
        },
        {   // ���� �� ���� ������.
            left_delay : 4000,
            right_delay : 5000,
            set_timer : 5000,
            option : None,
        },
        {   // ���� �� ������.
            .left_delay = 2500,
            .right_delay = 2500,
            .set_timer = 5000,
            .option = Down,
        },
        {   // �����ϰ� ��ó�� �߰���.
            .left_delay = 1700,
            .right_delay = 1700,
            .set_timer = 10000,
            .option = None,
        },
        {  // �ʵ��� �� ȭ��.
            .left_delay = 10000,
            .right_delay = 10000,
            .set_timer = 5000,
            .option = None,
        },
        {   // �Ͼ� �� ������.
            .left_delay = 6,
            .right_delay = 6,
            .set_timer = 10000,
            .option = None,
        },
        {   // ���� �� �������� ������.
            .left_delay = 9000,
            .right_delay = 8000,
            .set_timer = 9000,
            .option = None,
        },
        {   // ������ �������� ������.
            .left_delay = 4000,
            .right_delay = 4000,
            .set_timer = 9000,
            .option = None,
        },
        {   // ���� ���� �������� ������.
            .left_delay = 2000,
            .right_delay = 2000,
            .set_timer = 5000,
            .option = None,
        },
        {   // 10�ʵ��� �������� ����.
            .left_delay = 10000,
            .right_delay = 10000,
            .set_timer = 10000,
            .option = None,
        },  // �������� �ٽ� ó�� Ÿ�Ӷ������� ���ư���.
    };
    

    screen_activity_state = MainHome;

    while ( 1 )
    {

        current_time = clock_ms();
        btn_key_code = Keyboard.getCode();
        key_code = Keyboard.flexible_getCode( btn_key_code );


        if ( screen_activity_state == MainHome )
        {
            


            // 0. ȭ�� ������ ī��Ʈ
            if ( current_time >= fps_timer )
            {
                fps_timer = current_time + 1000;
                fps_capture = fps_counter;
                fps_counter = 0;
                // sprintf(fps_screen_bf, "TARGET FPS : %d  CURRENT FPS : %d  FLEXIBLE FPS : %d", target_fps, fps_capture, flexible_fps);
                
                // ���÷��� ������ ����.
                if ( fps_capture > target_fps )
                {
                    flexible_fps--;
                }
                else if ( fps_capture < target_fps )
                {
                    flexible_fps++;
                }
            }

            // 1. ���� �ִϸ��̼� ������Ʈ.
            {            
                // 1. �޴� ���� �ڽ��� ���� ��ư ���� �� ������Ʈ.
                static key_code_t this_key = {0};
                // - ��ư�� �� ������ ���� ������Ʈ.
                if ( this_key.key_code == 0 )
                {
                    this_key = btn_key_code;
                }
                if  ( current_time >= animate_next_update_time )
                {
                    // 0. Ÿ�̸� ������Ʈ.
                    // animate_next_update_time = current_time + 1000/DELTA_TIME_FRAME;
                    animate_next_update_time += 1000/DELTA_TIME_FRAME;
                    // 1. ���� �׷��� �׸���.
                    Straight$Game$AnimateUpdate();
                    // 2. ���� �ڽ� �׷��� �׸��� �� ��ư ���� ���� ��������.
                    select_btn = Straight.Menu.animateUpdate(this_key, screen_activity_state);
                    // 3. ��ư�� �� �������Ƿ� �ʱ�ȭ.
                    this_key = (key_code_t){
                        .option = 0,
                        .key_code = 0,
                    };
                    
                }
            }

            if ( need_buffer_write )
            {
                sprintf(fps_screen_bf, "TARGET FPS : %d  CURRENT FPS : %d  FLEXIBLE FPS : %d", target_fps, fps_capture, flexible_fps);
                Straight$Game$GraphicDraw(2, fps_screen_bf, "Developed by iDSLR & �̱���");
                Straight.Menu.draw();
                Straight.Menu.drawSelectBox();

                need_buffer_write = 0;
            }

            // 2. ���� �׷��� �׸��� �� ���÷��� ������Ʈ.
            if ( current_time >= display_next_update_time )
            {
                // display_next_update_time = current_time + 1000/flexible_fps;
                display_next_update_time += 1000/flexible_fps;
                fps_counter++;

                //// ���� �׷��� �׸���� ���ÿ� ���۸� ����ϹǷ� ���� ����ȭ��.
                // sprintf(fps_screen_bf, "TARGET FPS : %d  CURRENT FPS : %d  FLEXIBLE FPS : %d", target_fps, fps_capture, flexible_fps);
                // Straight$Game$GraphicDraw(2, fps_screen_bf, "Developed by iDSLR & �̱���");
                // Straight.Menu.draw();
                // Straight.Menu.drawSelectBox();
                screenUpdate();
                need_buffer_write = 1;
            }

            // 3. ���� ������Ʈ �߰�.
            if ( current_time >= add_left_obj_timer )
            {
                // 1. Ÿ�̸� ������Ʈ.
                add_left_obj_timer = current_time + LEFT_OBJ_ADD_DELAY;
                // 2. ������Ʈ �߰�.
                side_obj_t obj = Straight$newLeftSideObject(OBJ_LENGTH);
                Straight$addLeftSideObject(obj);
            }

            // 4. ������ ������Ʈ �߰�.
            if ( current_time >= add_right_obj_timer )
            {
                // 1. Ÿ�̸� ������Ʈ.
                add_right_obj_timer = current_time + RIGHT_OBJ_ADD_DELAY;
                // 2. ������Ʈ �߰�.
                side_obj_t obj = Straight.Game.Object.newRightSideObject(OBJ_LENGTH);
                Straight.Game.Object.addRightSideObject(obj);
            }

            // 5. Ű���� �Է� �ޱ�.
            {
                // 0. ���� Ű����, ������Ʈ.
                static key_code_t this_key = {0};
                // - ��ư�� �� ������ �� ��ư ���� ������Ʈ.
                if ( this_key.key_code == 0 )
                {
                    this_key = btn_key_code;
                }



                // - ���� ��ư�� ���� ���.
                if ( select_btn == Start )
                {
                    screen_activity_state = inGame;
                }
                // - ���� ��ư�� ���� ���.
                else if ( select_btn == Exit )
                {
                    // 1. ���α׷� ����.
                    return( 0 );
                }



                // 2. ��ư�� �������Ƿ� �ʱ�ȭ.
                this_key = (key_code_t){
                    .option = 0,
                    .key_code = 0,
                };

            }            



        }

        else if ( screen_activity_state == inGame )
        {



            // 0. ������ ī���� 1�� ���� ������Ʈ.
            if ( current_time >= fps_timer )
            {
                fps_timer = current_time + 1000;
                fps_capture = fps_counter;
                fps_counter = 0;
                
                // ���÷��� ������ ����.
                if ( fps_capture > target_fps )
                {
                    flexible_fps--;
                }
                else if ( fps_capture < target_fps )
                {
                    flexible_fps++;
                }
            }

            // 1. ���� �ִϸ��̼� ������Ʈ.
            {
                static key_code_t this_key = { .option=0, .key_code=0 };
                if ( this_key.option==0 && this_key.key_code==0 ) this_key = btn_key_code;



                if ( current_time >= animate_next_update_time && Straight.key_is_move( key_code ) )
                {
                    animate_next_update_time = current_time + 1000/DELTA_TIME_FRAME;
                    Straight$Game$AnimateUpdate();
                }
                else if ( current_time >= animate_next_update_time )
                {
                    // - ���� �ڽ� �޴� ���͸� ���� ������.
                    select_btn = Straight.Menu.animateUpdate(this_key, screen_activity_state);
                    this_key = (key_code_t){ .option=0, .key_code=0 };
                }

            }
            
            // 2. ���� �׷��� �׸��� �� ���÷��� ������Ʈ.
            if ( current_time >= display_next_update_time )
            {
                display_next_update_time = current_time + 1000/flexible_fps;
                fps_counter++;
                sprintf(fps_screen_bf, "TARGET FPS : %d  CURRENT FPS : %d  FLEXIBLE FPS : %d", target_fps, fps_capture, flexible_fps);
                Straight$Game$GraphicDraw(1, fps_screen_bf);
                Straight.Menu.drawSelectBox();
                screenUpdate();
            }

            // 3. ���� ������Ʈ �߰�.
            if ( current_time >= add_left_obj_timer && Straight.key_is_move(key_code) )
            {
                // 1. Ÿ�̸� ������Ʈ.
                add_left_obj_timer = current_time + o_Function(
                    clock_t,
                    aot01,

                    // 1. Ÿ�̸Ӱ� �Ϸ�� ���.
                    if ( current_time >= timeline_timer )
                    {
                        // 0. Ÿ�Ӷ��� ������Ʈ.
                        timeline_timer?timeline_current_index++:0;
                        if ( timeline_current_index >= sizeof( obj_timeline )/sizeof( timeline_info_t ) )
                        {
                            timeline_current_index = 0;
                        }
                        // 1. Ÿ�̸� ������Ʈ.
                        timeline_timer = current_time + obj_timeline[timeline_current_index].set_timer;
                    }
                    // 2. ���� Ÿ�Ӷ����� ���� ������ ��ȯ.
                    Freturn(aot01, obj_timeline[timeline_current_index].left_delay);
                );
                
                // 2. ���� ������Ʈ �߰�.
                side_obj_t obj = Straight$newLeftSideObject(OBJ_LENGTH);
                Straight$addLeftSideObject(obj);
            }

            // 4. ������ ������Ʈ �߰�.
            if ( current_time >= add_right_obj_timer && Straight.key_is_move(key_code) )
            {
                // 1. Ÿ�̸� ������Ʈ.
                add_right_obj_timer = current_time + o_Function(
                    clock_t,
                    aot02,

                    // 1. ���� Ÿ�Ӷ����� ������ ������ ��ȯ.
                    // - ���� ������Ʈ �߰� Ÿ�̸ӿ��� Ÿ�Ӷ����� ������Ʈ ���ֹǷ� ���⿡�� Ÿ�̸� �ڵ带 ���� �ʴ´�.
                    Freturn(aot02, obj_timeline[timeline_current_index].right_delay);
                );

                // 2. ������ ������Ʈ �߰�.
                Straight$addRightSideObject( Straight$newRightSideObject(OBJ_LENGTH) );
            }

            // 5. ���� ����ȭ������ ����.
            // if(key_code.key_code == 27){
            if ( select_btn == To_menu )
            {
                screen_activity_state = MainHome;
                fps_counter = 0;
                fps_capture = 0;
                timeline_timer = 0;
                select_btn = Nothing;
                key_code = (key_code_t){
                    .key_code = 0,
                    .option = 0,
                };
                btn_key_code = (key_code_t){
                    .key_code = 0,
                    .option = 0,
                };
            }



        }

        // ���� Ű���� �Է�.
        {
            // 1. Ű�� ����.
            static key_code_t this_key = {0};
            // 2. Ű�� ��� �Ϸ�� Ű�� ������Ʈ.
            if ( this_key.key_code == 0 )
            {
                this_key = btn_key_code;
            }


            
            // 3. Ű�� ó��.
            // '='Ű�� ������ Ÿ�� ������ ����.
            if ( this_key.key_code == '=' )
            {
                if ( target_fps < 1000 ) target_fps++;
                flexible_fps = target_fps;
            }
            // '-'Ű�� ������ Ÿ�� ������ ����.
            else if ( this_key.key_code == '-' )
            {
                if ( target_fps > 1 ) target_fps--;
                flexible_fps = target_fps;
            }
            // - p : Ÿ�̸� ����, ���� ��ü �Ͻ� ����.
            else if ( this_key.option != 224 && this_key.key_code == 'P' )
            {
                key_code_t now_key = Keyboard.getCode();
                while ( !(now_key.option == 0 && now_key.key_code == 'P') )
                {
                    now_key = Keyboard.getCode();
                }
            }




            // 2. ��� Ȯ�� �� Ű�� �ʱ�ȭ.
            this_key = (key_code_t){
                .option = 0,
                .key_code = 0,
            };
        }


        // �� ���� ������ �� ��ư ���� �ʱ�ȭ.
        key_code = (key_code_t){
            .option = 0,
            .key_code = 0,
        };
        btn_key_code = (key_code_t){
            .option = 0,
            .key_code = 0,
        };



    }

    return( 0 );
}