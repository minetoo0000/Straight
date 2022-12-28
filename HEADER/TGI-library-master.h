#pragma once

#define _IS_WINDOWS 1
/* -_IS_WINDOWS
0 : ANDROID and more
1 : WINDOWS
*/

#define ERRORPASS_ESCAPE_SYSTEM_LOOP 0
// - ERRORPASS_ESCAPE_SYSTEM_LOOP
// 0 : 기본값. 시스템의 매인 루프를 이탈하였을 때 에러 발생.
// 1 : 시스템 매인 루프 이탈 시 바로 시스템 매인 루프 시작 지점으로 강제 복귀.
//	알 수 없는 상태, 위치에서 시스템 매인 루프를 이탈했기 때문에
//	런타임 문제가 생길 수 있음.
//	본 에러 무시는 매우 실험적인 기능이며 심각한 문제를 발생시킬 수 있음.



#include <stdio.h>
#include <stdint.h>
#include <conio.h>
#include <time.h>
#include <math.h>
#include <malloc.h>

#include "./librarys/etc.h"
// tgiSystem 헤더 위에 포함되는 모든 헤더들은 헤더순도 B등급 이상이여야 함.
#include "./librarys/tgiSystem.h"
#include "./librarys/ScreenOutput.h"
#include "./librarys/keyboardInput.h"
#include "./librarys/CursorInput.h"



/*

[ 상태 코드 설명 ]

+0, 0 : 정상 종료 됨.

-0번대 : 대략적, 일반적인 에러.
	-1 : 금지 된 행위 발생.
	-2 : 논리적으로 옳지 않은 실행.
	-3 : 접근 문제 발생.
	-4 : 데이터 형식 불일치.
	-5 : 잘못 된 데이터.
	-6 : 작업 실패.
	-7 : 재시작 필요. (경우에 따라 강제 재시작됨.)
	-8 : 시스템 문제 감지.
	-9 : 무한 로프 감지.
	-10 : 디버깅 중 문제 발생.
	
-10번대 : 메모리 에러 확장.
	-11 :메모리 읽기 불가.
	-12 : 메모리 수정 불가.
	-13 : 메모리 할당 불가.
	-14 : 메모리와 관련된 읽기 작업 불가.
	-15 : 메모리와 관련된 수정 작업 불가.
	-16 : 메모리와 관련된 할당 작업 불가.
	-17 : 잘못 된 메모리 포인터.
	-18 : 메모리 작업 권한 없음.
	-19 : 메모리 작업이 금지됨.
	-20 : 잘못 된 메모리 접근.
	
*/
