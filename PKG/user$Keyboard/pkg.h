#pragma once
/*
    패키지 : 사용자 정의 키보드 입력 패키지.
    설명 : 고장난 시스템 키보드 패키지 대신 새로 다시 작성된 키보드 입력 패키지.
    
    난 기본 입력 버퍼를 믿는다...



     - 키보드 값을 반환하는 함수는 입력된 키보드 데이터가 담긴 객체를 반환한다.p
*/
#include "pkg.c"


/// 객체 섹션 ///

/// 전역 변수 섹션 ///

/// 함수 섹션 ///

// 키보드 클릭버튼 입력 반환.
key_code_t method$class_user_Keyboard$getCode(void);

// 키보드 버튼 입력 반환.
key_code_t method$class_user_Keyboard$flexible_getCode( key_code_t key_code );


struct class$Keyboard
{
    key_code_t(*getCode)();
    key_code_t(*flexible_getCode)( key_code_t key_code );
} Keyboard = {
    .getCode = method$class_user_Keyboard$getCode,
    .flexible_getCode = method$class_user_Keyboard$flexible_getCode,
};