#include <time.h>
#include <stdint.h>
#include <conio.h>
#include "./../../HEADER/Cobject/cobject.h"
#include "./../../HEADER/TGI-library-master.h"


typedef struct type$class_Keyboard$key_code_t
{
    // 옵션.
    uint8_t option;
    // 키 값.
    uint8_t key_code;
} key_code_t;

// void delay_ms(clock_t n)
// {

//   clock_t start = clock();

//   while(clock() - start < n);

// }

static key_code_t method$class_user_Keyboard$getCode(void)
{
    if ( _kbhit() ){
        // 1. 키값 변수 생성.
        key_code_t set = {
            .option = 0,
            .key_code = 0,
        };

        // 2. 키 옵션 구별.
        if ( (set.key_code = _getch()) == 224 )
        {
            set = (key_code_t){
                .option = set.key_code,
                .key_code = _getch(),
            };
        }
        return(set);
    }
    
    // return( 0 );
}
// 여기에서 키보드 관련 함수들을 작성할 거거든.혹시 괜찮을까? 음....
// 디코로 적은 키보드 입력 문제 어떤건지는 이해 됐지. 지금 위에 있는 함수를 수정해도 되고 아니면 새로 만들어도 되.
// 방식은 편한대로 !
// 

static key_code_t method$class_user_Keyboard$flexible_getCode( key_code_t key_code )
{
    // 0. 변수.
    // static uint8_t key_bf = 0;
    static key_code_t set_bf = {
        .option = 0,
        .key_code = 0,
    };
    static clock_t timer = 0;
    static uint8_t timer_mode = 0;  // 0 : 처음 입력 타이머, 1 : 연속 입력 타이머.
    clock_t current_time = 0;
    current_time = clock_ms();

    // 1. 키 입력이 감지 됨.
    if ( key_code.key_code != 0 )
    {
        // 1. 처음엔 약 0.4초동안 무조건 키값이 유지된다.
        // - 0.4초 타이머 설정.
        if ( current_time > timer )
        {
            // printf("\n 타이머 초기화.\n");
            // 1. 타이머 설정.
            // - 처음엔 0.4초, 연속 입력인 경우엔 0.15초 타이머 설정.
            // timer = current_time + ( timer_mode==0 ? 400 : 150 );
            timer = current_time + o_Function(
                clock_t,
                Ktv01,

                clock_t return_timer = 0;
                if ( timer_mode == 0 )
                {
                    // printf("\n 0.4초 설정됨.\n");
                    return_timer = 500;
                    // 1. 타이머를 길게 설정한 이후엔 짧은 타이머 모드로 변환.
                    timer_mode = 1;
                }
                else
                {
                    // printf("\n 0.15초 설정됨.\n");
                    return_timer = 150;
                }
                Freturn(Ktv01, return_timer);
            );

            // 2. 키버퍼 업데이트 및 반환.
            // key_bf = _getch();
            // if ( (set_bf.key_code = _getch()) == 224 )
            if ( key_code.option == 224 )
            {
                // set_bf = (key_code_t){
                //     .option = set_bf.key_code,
                //     .key_code = _getch(),
                // };
                set_bf.option = 224;
            }
            // else set_bf.option = 0;
            else
            {
                set_bf.option = 0;
            }
            set_bf.key_code = key_code.key_code;

            // printf("\n kye_bf 업데이트 : %d\n", key_bf);
            // getchar();
            return( set_bf );
        }

        // 2. 타이머가 완료되지 않았다면 키버퍼를 반환.
        else
        {
            return( set_bf );
        }
    }

    // 2. 키가 눌리지 않는 상태인 경우 정해진 타이머 동안 키버퍼를 반환.
    else if ( current_time <= timer )
    {
        return( set_bf );
    }

    // 3. 모든 타이머가 완료되어있고, 다시 처음부터 키를 감지해야할 때.
    else
    {
        timer_mode = 0;
        return(
            (key_code_t)
            {
                .option = 0,
                .key_code = 0,
            }
        );
    }
}