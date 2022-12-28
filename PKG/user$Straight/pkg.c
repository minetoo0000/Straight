
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

    ///////////////////////////// 아래에 있는 변수들은 게임 초기화 시에 0으로 설정.
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
    enum Button_state select_btn = Nothing;  // Nothing으로 초기화!.
    uint8_t need_buffer_write = 1;



    // 오브젝트 타임라인.
    enum TimelineOption
    {
        None,  // 아무 옵션도 넣지 않음.
        Up,  // 점점 증가시킴.
        Down,  // 점점 감소시킴.
        // Random,  // 딜레이 랜덤.
    };
    typedef struct _timeline_info_t {
        clock_t left_delay;  // 왼쪽 오브젝트 추가 간격을 저장함.
        clock_t right_delay;  // 오른쪽 오브젝트 추가 간격을 저장함.
        clock_t set_timer;  // 딜레이 지속시간.
        enum TimelineOption option;  // 딜레이 옵션.
    } timeline_info_t;

    timeline_info_t obj_timeline[] = {
        // {   // 처음엔 띄엄 띄엄 오브젝트를 생성.
        //     .left_delay = 8000,
        //     .right_delay = 10000,
        //     .set_timer = 10000,
        //     .option = None,
        // },
        // {   // 조금 더 많이 생성됨.
        //     left_delay : 4000,
        //     right_delay : 5000,
        //     set_timer : 5000,
        //     option : None,
        // },
        // {   // 조금 더 생성됨.
        //     .left_delay = 2500,
        //     .right_delay = 2500,
        //     .set_timer = 5000,
        //     .option = Down,
        // },
        // {   // 촘촘하게 벽처럭 추가됨.
        //     .left_delay = 1700,
        //     .right_delay = 1700,
        //     .set_timer = 20000,
        //     .option = None,
        // },
        // {  // 초동안 빈 화면.
        //     .left_delay = 10000,
        //     .right_delay = 10000,
        //     .set_timer = 9000,
        //     .option = None,
        // },
        // {   // 하얀 벽 생성됨.
        //     .left_delay = 6,
        //     .right_delay = 6,
        //     .set_timer = 20000,
        //     .option = None,
        // },
        // {   // 조금 긴 간격으로 생성됨.
        //     .left_delay = 9000,
        //     .right_delay = 8000,
        //     .set_timer = 20000,
        //     .option = None,
        // },
        // {   // 적당한 간격으로 생성됨.
        //     .left_delay = 4000,
        //     .right_delay = 4000,
        //     .set_timer = 20000,
        //     .option = None,
        // },
        // {   // 조금 작은 간격으로 생성됨.
        //     .left_delay = 2000,
        //     .right_delay = 2000,
        //     .set_timer = 10000,
        //     .option = None,
        // },
        // {   // 10초동안 생성되지 않음.
        //     .left_delay = 10000,
        //     .right_delay = 10000,
        //     .set_timer = 10000,
        //     .option = None,
        // },  // 이제부턴 다시 처음 타임라인으로 돌아간다.
        //////////////////////////// 아래는 시연용 타임라인 (시간단축)
        {   // 처음엔 띄엄 띄엄 오브젝트를 생성.
            .left_delay = 8000,
            .right_delay = 10000,
            .set_timer = 5000,
            .option = None,
        },
        {   // 조금 더 많이 생성됨.
            left_delay : 4000,
            right_delay : 5000,
            set_timer : 5000,
            option : None,
        },
        {   // 조금 더 생성됨.
            .left_delay = 2500,
            .right_delay = 2500,
            .set_timer = 5000,
            .option = Down,
        },
        {   // 촘촘하게 벽처럭 추가됨.
            .left_delay = 1700,
            .right_delay = 1700,
            .set_timer = 10000,
            .option = None,
        },
        {  // 초동안 빈 화면.
            .left_delay = 10000,
            .right_delay = 10000,
            .set_timer = 5000,
            .option = None,
        },
        {   // 하얀 벽 생성됨.
            .left_delay = 6,
            .right_delay = 6,
            .set_timer = 10000,
            .option = None,
        },
        {   // 조금 긴 간격으로 생성됨.
            .left_delay = 9000,
            .right_delay = 8000,
            .set_timer = 9000,
            .option = None,
        },
        {   // 적당한 간격으로 생성됨.
            .left_delay = 4000,
            .right_delay = 4000,
            .set_timer = 9000,
            .option = None,
        },
        {   // 조금 작은 간격으로 생성됨.
            .left_delay = 2000,
            .right_delay = 2000,
            .set_timer = 5000,
            .option = None,
        },
        {   // 10초동안 생성되지 않음.
            .left_delay = 10000,
            .right_delay = 10000,
            .set_timer = 10000,
            .option = None,
        },  // 이제부턴 다시 처음 타임라인으로 돌아간다.
    };
    

    screen_activity_state = MainHome;

    while ( 1 )
    {

        current_time = clock_ms();
        btn_key_code = Keyboard.getCode();
        key_code = Keyboard.flexible_getCode( btn_key_code );


        if ( screen_activity_state == MainHome )
        {
            


            // 0. 화면 프레임 카운트
            if ( current_time >= fps_timer )
            {
                fps_timer = current_time + 1000;
                fps_capture = fps_counter;
                fps_counter = 0;
                // sprintf(fps_screen_bf, "TARGET FPS : %d  CURRENT FPS : %d  FLEXIBLE FPS : %d", target_fps, fps_capture, flexible_fps);
                
                // 디스플레이 프레임 보정.
                if ( fps_capture > target_fps )
                {
                    flexible_fps--;
                }
                else if ( fps_capture < target_fps )
                {
                    flexible_fps++;
                }
            }

            // 1. 게임 애니메이션 업데이트.
            {            
                // 1. 메뉴 선택 박스를 위한 버튼 변수 및 업데이트.
                static key_code_t this_key = {0};
                // - 버튼이 다 사용됐을 때만 업데이트.
                if ( this_key.key_code == 0 )
                {
                    this_key = btn_key_code;
                }
                if  ( current_time >= animate_next_update_time )
                {
                    // 0. 타이머 업데이트.
                    // animate_next_update_time = current_time + 1000/DELTA_TIME_FRAME;
                    animate_next_update_time += 1000/DELTA_TIME_FRAME;
                    // 1. 게임 그래픽 그리기.
                    Straight$Game$AnimateUpdate();
                    // 2. 선택 박스 그래픽 그리기 및 버튼 선택 상태 가져오기.
                    select_btn = Straight.Menu.animateUpdate(this_key, screen_activity_state);
                    // 3. 버튼이 다 사용됐으므로 초기화.
                    this_key = (key_code_t){
                        .option = 0,
                        .key_code = 0,
                    };
                    
                }
            }

            if ( need_buffer_write )
            {
                sprintf(fps_screen_bf, "TARGET FPS : %d  CURRENT FPS : %d  FLEXIBLE FPS : %d", target_fps, fps_capture, flexible_fps);
                Straight$Game$GraphicDraw(2, fps_screen_bf, "Developed by iDSLR & 이기훈");
                Straight.Menu.draw();
                Straight.Menu.drawSelectBox();

                need_buffer_write = 0;
            }

            // 2. 게임 그래픽 그리기 및 디스플레이 업데이트.
            if ( current_time >= display_next_update_time )
            {
                // display_next_update_time = current_time + 1000/flexible_fps;
                display_next_update_time += 1000/flexible_fps;
                fps_counter++;

                //// 버퍼 그래픽 그리기와 동시에 버퍼를 출력하므로 수직 동기화임.
                // sprintf(fps_screen_bf, "TARGET FPS : %d  CURRENT FPS : %d  FLEXIBLE FPS : %d", target_fps, fps_capture, flexible_fps);
                // Straight$Game$GraphicDraw(2, fps_screen_bf, "Developed by iDSLR & 이기훈");
                // Straight.Menu.draw();
                // Straight.Menu.drawSelectBox();
                screenUpdate();
                need_buffer_write = 1;
            }

            // 3. 왼쪽 오브젝트 추가.
            if ( current_time >= add_left_obj_timer )
            {
                // 1. 타이머 업데이트.
                add_left_obj_timer = current_time + LEFT_OBJ_ADD_DELAY;
                // 2. 오브젝트 추가.
                side_obj_t obj = Straight$newLeftSideObject(OBJ_LENGTH);
                Straight$addLeftSideObject(obj);
            }

            // 4. 오른쪽 오브젝트 추가.
            if ( current_time >= add_right_obj_timer )
            {
                // 1. 타이머 업데이트.
                add_right_obj_timer = current_time + RIGHT_OBJ_ADD_DELAY;
                // 2. 오브젝트 추가.
                side_obj_t obj = Straight.Game.Object.newRightSideObject(OBJ_LENGTH);
                Straight.Game.Object.addRightSideObject(obj);
            }

            // 5. 키보드 입력 받기.
            {
                // 0. 버퍼 키변수, 업데이트.
                static key_code_t this_key = {0};
                // - 버튼이 다 사용됐을 때 버튼 변수 업데이트.
                if ( this_key.key_code == 0 )
                {
                    this_key = btn_key_code;
                }



                // - 시작 버튼이 눌린 경우.
                if ( select_btn == Start )
                {
                    screen_activity_state = inGame;
                }
                // - 종료 버튼이 눌린 경우.
                else if ( select_btn == Exit )
                {
                    // 1. 프로그램 종료.
                    return( 0 );
                }



                // 2. 버튼이 사용됐으므로 초기화.
                this_key = (key_code_t){
                    .option = 0,
                    .key_code = 0,
                };

            }            



        }

        else if ( screen_activity_state == inGame )
        {



            // 0. 프레임 카운터 1초 마다 업데이트.
            if ( current_time >= fps_timer )
            {
                fps_timer = current_time + 1000;
                fps_capture = fps_counter;
                fps_counter = 0;
                
                // 디스플레이 프레임 보정.
                if ( fps_capture > target_fps )
                {
                    flexible_fps--;
                }
                else if ( fps_capture < target_fps )
                {
                    flexible_fps++;
                }
            }

            // 1. 게임 애니메이션 업데이트.
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
                    // - 선택 박스 메뉴 복귀를 위한 목적임.
                    select_btn = Straight.Menu.animateUpdate(this_key, screen_activity_state);
                    this_key = (key_code_t){ .option=0, .key_code=0 };
                }

            }
            
            // 2. 게임 그래픽 그리기 및 디스플레이 업데이트.
            if ( current_time >= display_next_update_time )
            {
                display_next_update_time = current_time + 1000/flexible_fps;
                fps_counter++;
                sprintf(fps_screen_bf, "TARGET FPS : %d  CURRENT FPS : %d  FLEXIBLE FPS : %d", target_fps, fps_capture, flexible_fps);
                Straight$Game$GraphicDraw(1, fps_screen_bf);
                Straight.Menu.drawSelectBox();
                screenUpdate();
            }

            // 3. 왼쪽 오브젝트 추가.
            if ( current_time >= add_left_obj_timer && Straight.key_is_move(key_code) )
            {
                // 1. 타이머 업데이트.
                add_left_obj_timer = current_time + o_Function(
                    clock_t,
                    aot01,

                    // 1. 타이머가 완료된 경우.
                    if ( current_time >= timeline_timer )
                    {
                        // 0. 타임라인 업데이트.
                        timeline_timer?timeline_current_index++:0;
                        if ( timeline_current_index >= sizeof( obj_timeline )/sizeof( timeline_info_t ) )
                        {
                            timeline_current_index = 0;
                        }
                        // 1. 타이머 업데이트.
                        timeline_timer = current_time + obj_timeline[timeline_current_index].set_timer;
                    }
                    // 2. 현재 타임라인의 왼쪽 딜레이 반환.
                    Freturn(aot01, obj_timeline[timeline_current_index].left_delay);
                );
                
                // 2. 왼쪽 오브젝트 추가.
                side_obj_t obj = Straight$newLeftSideObject(OBJ_LENGTH);
                Straight$addLeftSideObject(obj);
            }

            // 4. 오른족 오브젝트 추가.
            if ( current_time >= add_right_obj_timer && Straight.key_is_move(key_code) )
            {
                // 1. 타이머 업데이트.
                add_right_obj_timer = current_time + o_Function(
                    clock_t,
                    aot02,

                    // 1. 현재 타임라인의 오른쪽 딜레이 반환.
                    // - 왼쪽 오브젝트 추가 타이머에서 타임라인을 업데이트 해주므로 여기에는 타이머 코드를 쓰지 않는다.
                    Freturn(aot02, obj_timeline[timeline_current_index].right_delay);
                );

                // 2. 오른쪽 오브젝트 추가.
                Straight$addRightSideObject( Straight$newRightSideObject(OBJ_LENGTH) );
            }

            // 5. 게임 매인화면으로 복귀.
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

        // 전역 키보드 입력.
        {
            // 1. 키값 변수.
            static key_code_t this_key = {0};
            // 2. 키값 사용 완료시 키값 업데이트.
            if ( this_key.key_code == 0 )
            {
                this_key = btn_key_code;
            }


            
            // 3. 키값 처리.
            // '='키가 눌리면 타겟 프레임 증가.
            if ( this_key.key_code == '=' )
            {
                if ( target_fps < 1000 ) target_fps++;
                flexible_fps = target_fps;
            }
            // '-'키가 눌리면 타겟 프레임 감소.
            else if ( this_key.key_code == '-' )
            {
                if ( target_fps > 1 ) target_fps--;
                flexible_fps = target_fps;
            }
            // - p : 타이머 제외, 게임 전체 일시 정지.
            else if ( this_key.option != 224 && this_key.key_code == 'P' )
            {
                key_code_t now_key = Keyboard.getCode();
                while ( !(now_key.option == 0 && now_key.key_code == 'P') )
                {
                    now_key = Keyboard.getCode();
                }
            }




            // 2. 모두 확인 후 키값 초기화.
            this_key = (key_code_t){
                .option = 0,
                .key_code = 0,
            };
        }


        // 한 턴을 끝냈을 때 버튼 변수 초기화.
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