/*
    [ 라이브러리 ]
    Timer.h

    [ 설명 ]
    pause, resum이 가능한 타이머 라이브러리.
*/

#pragma once
#include <time.h>

enum enum$class_Timer
{
    Timer_state_pause,
    Timer_state_run,
};

struct type$class_Timer$timer_t
{
    // 타이머 상태.
    enum enum$class_Timer state;
    // 남은 시간.
    clock_t current_timer;
    // 시작 ~ 정지, 시작 ~ 타이머 측정을 위한 "시작" 시간 저장.
    clock_t resum_time;
};



// 밀리초 단위 시간 함수.
clock_t method$Timer$clock_ms()
{
    return( clock() / ( CLOCKS_PER_SEC / (clock_t)1000 ) );
}

// 타이머 생성자 함수.
struct type$class_Timer$timer_t method$class_Timer$newTimer( const clock_t setup_timer, const clock_t use_custom_clock_time )
{
    return(
        (struct type$class_Timer$timer_t)
        {
            .state = Timer_state_pause,
            .current_timer = setup_timer,
            .resum_time = use_custom_clock_time ? use_custom_clock_time : method$Timer$clock_ms(),
        }
    );
}

// 타이머 시작 함수.
void method$class_Timer$resum( struct type$class_Timer$timer_t* const obj, const clock_t use_custom_clock_time )
{
    if ( obj->state == Timer_state_pause )
    {
        obj->state = Timer_state_run;
        obj->resum_time = use_custom_clock_time ? use_custom_clock_time : method$Timer$clock_ms();
    }
}

// 타이머 정지 함수.
void method$class_Timer$pause( struct type$class_Timer$timer_t* const obj, const clock_t use_custom_clock_time )
{
    if ( obj->state == Timer_state_run )
    {
        obj->state = Timer_state_pause;
        obj->current_timer -= ( (use_custom_clock_time ? use_custom_clock_time : method$Timer$clock_ms()) - obj->resum_time );
    }
}


// 타이머 남은 시간 반환 함수.
clock_t method$class_Timer$get_current_timer( const struct type$class_Timer$timer_t* const obj, const clock_t use_custom_clock_time )
{
    if ( obj->state == Timer_state_run )
    {
        return( obj->current_timer - ( (use_custom_clock_time ? use_custom_clock_time : method$Timer$clock_ms()) - obj->resum_time ) );
    }
    else if ( obj->state == Timer_state_pause )
    {
        return( obj->current_timer );
    }
    else
    {
        return( 0 );
    }
}



// Timer 클래스 객체.
struct class$Timer
{
    clock_t(*const clock_ms)(void);
    struct type$class_Timer$timer_t(*const newTimer)( const clock_t setup_timer, const clock_t use_custom_clock_time );
    void(*const resum)( struct type$class_Timer$timer_t* const obj, const clock_t use_custom_clock_time );
    void(*const pause)( struct type$class_Timer$timer_t* const obj, const clock_t use_custom_clock_time );
    clock_t(*const get_current_timer)( const struct type$class_Timer$timer_t* const obj, const clock_t use_custom_clock_time );
} Timer = {
    .clock_ms = method$Timer$clock_ms,
    .newTimer = method$class_Timer$newTimer,
    .resum = method$class_Timer$resum,
    .pause = method$class_Timer$pause,
    .get_current_timer = method$class_Timer$get_current_timer,
};
