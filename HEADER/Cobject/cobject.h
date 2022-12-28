
#pragma once
////
////

// ���Ἲ�� ���� : �ش��ϴ� �����Ͱ� ����ó���Լ��� ���� ������ �Ǿ��ų� ����ó���Լ��� �Ȱ��ų� ������ �������?? ������ �� �����͸� ����.
// !! ���� ���ɼ� ����. ���� �����͸� ���������� �����ϴ� ���?? ���ڴ� ������. (���?? ������ �Լ��� ���� R/W ����)

// ���Ἲ�� ������ ���??
// - ������ �����Ͱ��� ������ ��.
// - ������ �����Ͱ� �����Ǿ��� ��.
// - �����Ͱ� ��ȯ�� ��.

// (uint8_t)return_state_t.success : ��ȯ�� �Ϸ��� �Լ��� �������� �۾� �Ǵ� �ǵ��� �۾��� �������� �� 1�� ������. �ǵ�ġ ���� ���ܳ� ����, ���� �� ��� 0�� ������.

// (uint8_t:1)return_state_t.is_verify : ��ȯ�Ϸ��� (var)return_state_t.data ������ ���Ἲ ���θ� ������.
// (var)return_state_t.data ������ ���Ἲ�� �����ִٸ� 0�� ������.

// ���� var ������ : Cobject�� �����?? ��ȯ�Ǵ� Bool, Number, Array, String, Null, Undefined ���������� ��ü�� �ǹ��ϴ� �߻����� ��������.
// ���� ������ : char, short, int, long, double ���?? ���� C�����?? �⺻���� ���������� ���� �ǹ̸� ������ ������.

// Bool : ���� ������ ��Ÿ���� ���������Դϴ�.
// Number : �Ǽ��� ǥ���� �� �ִ� ���������Դϴ�.
// Array : type$array_t$value ũ�⸸ŭ�� �����͸� �迭�� ��Ÿ�� �� �ִ� ���������Դϴ�.
// String : ���ڿ� �����͸� ��Ÿ���� ���������Դϴ�.
// Null : �ƹ��͵� ������, ������ ���� ������ ��Ÿ���� ���������Դϴ�.
	// - Null �������� ���� �����ʹ� 0 �Դϴ�.
// Undefined : �������� ���� ���?? ��Ÿ���� �������Դϴ�. R-value�� Undefined �����͸� L-value�� ������ �� �����ϴ�.
	// - Undefined �������� ���� �����ʹ� 0 �Դϴ�.
	// - Undefined �����ʹ� �׻� R-value�� �����մϴ�. (L-value�� ������ �� �����ϴ�.)
	// - Undefined �����ʹ� ���ǵ��� ���� ���?? ��Ÿ���ϴ�. C���� void�� ���� �����մϴ�.
	// - �ڵ忡�� �ۼ��� Undefined �����ʹ� �񱳸� ���� �����?? �� �ֽ��ϴ�.

// Cobject �����ӿ�ũ �۾���.
	// - o_Function(INLINE_CODE, RETURN_VALUE) : �͸��Լ��Դϴ�. ��ȯ�ϴ� ���� RETURN_VALUE �Դϴ�.
	// - Function(INLINE_CODE, RETURN_VALUE) : �͸��Լ��Դϴ�. ��ȯ�ϴ� ���� return_state_t �������� (const var)return_state_t.data = RETURN_VALUE �Դϴ�.
	// - Run(VAR_INIT_CODE, INLINE_CODE) : ���� ������ ���ִ� �ڵ� ����. ���� ����, �ʱ�ȭ �κа� �۾� �κ��� �и��ؼ� �۾��� �� �ִ�.
	// - New_var(VAR_TYPE, VAR_NAME, __va_list_tag) : ���ο� ������ �����մϴ�. ��ũ�� �Լ��̸� ��ȯ���� �����ϴ�.
	// ] VAR_TYPE : Bool, Number, Array, String, Null, Undefined
	// - get(VAR_TYPE) : var ���������� �������� C���� �����?? ������ ���� �����ͷ� ��ȯ�Ͽ� ��ȯ�Ѵ�. ��ũ�� �Լ��̴�.

////
////

////
////
// ���� �۾� ����.
// 1. verify ��ġ Ȯ��

// null Ÿ���� ����.
// void �������� �Լ��� �ƹ� ���� ��ȯ���� �ʾ� �ڵ带 �ۼ��ϴµ� �ణ�� ������ �����??.
// void�� �����?? ��ȯ ���� ���� ���·� null�� ����Ѵ�??. �� �ܿ��� �ƹ� ���� �ƴ� ���?? null�� �����?? ���� ������ ���?? �뵵/������ �ڵ� �ۼ��� �����̴�.
////
////

#include <stdio.h>
#include <stdint.h>
#include <malloc.h>
#include <string.h>


#define DEFINE_TEXT(TEXT)   #TEXT
#define LOG(NOTICE_TEXT)   _Pragma(DEFINE_TEXT(message("[ LOG ] : " #NOTICE_TEXT)))

#define o_getVerify(VAR_DATA)   ((uint8_t)( ~(uint64_t)(&VAR_DATA) ))

#define o_true   1
#define o_false   0
#define true   (Cobject.Bool(o_true))
#define false   (Cobject.Bool(o_false))

#define o_void   ((void)0)
#define o_null   ((uint8_t)0)

#define TYPE$undefined   (int8_t)-1
#define TYPE$null   (int8_t)0
#define TYPE$Bool   (int8_t)1
#define TYPE$Number   (int8_t)2
#define TYPE$Array   (int8_t)3
#define TYPE$String   (int8_t)4
#define TYPE$Json   (int8_t)5

#define o_Function(RETURN_TYPE, FUNC_ID, CODE, ...)\
({\
	RETURN_TYPE Cobject$Utility$Function$return_value_##FUNC_ID;\
	CODE,##__VA_ARGS__\
	Cobject$Utility$Function$goto_##FUNC_ID:(RETURN_TYPE)Cobject$Utility$Function$return_value_##FUNC_ID;\
})

#define Function(INLINE_CODE, RETURN_VAR_VALUE)\
({INLINE_CODE ((return_state_t)Cobject.Return(RETURN_VAR_VALUE));})

#define Freturn( FUNC_ID, RETURN_VALUE )\
({Cobject$Utility$Function$return_value_##FUNC_ID=RETURN_VALUE;goto Cobject$Utility$Function$goto_##FUNC_ID;})

#define Var(VAR_TYPE, VAR_NAME, ...)\
var VAR_NAME=Cobject.VAR_TYPE(__VA_ARGS__);Cobject.Update(&VAR_NAME)

#define Auto(VAR_TYPE, VAR_NAME, ...)\
var VAR_NAME=0;case __COUNTER__+1:;Cobject$Memory$AutoUnload$is_unload==0?({VAR_NAME=Cobject.VAR_TYPE(__VA_ARGS__);Cobject.Update(&VAR_NAME);Cobject$Memory$AutoUnload$var_count++;}):({Cobject.Unload(VAR_NAME);Cobject$Memory$AutoUnload$unload_pointer+=1;break;});

#define Run(VARS, INLINE_CODE)\
{\
	uint8_t Cobject$Memory$AutoUnload$is_unload=0;\
	uint8_t Cobject$Memory$AutoUnload$is_scan=1;\
	uint16_t Cobject$Memory$AutoUnload$unload_pointer=0;\
	uint16_t Cobject$Memory$AutoUnload$var_count=0;\
	\
	while(Cobject$Memory$AutoUnload$is_scan==1){\
		switch(Cobject$Memory$AutoUnload$unload_pointer){\
			case 0:;\
			VARS\
			INLINE_CODE\
			Cobject$Memory$AutoUnload$is_unload=1;\
			if(Cobject$Memory$AutoUnload$var_count==0){Cobject$Memory$AutoUnload$is_scan=0;break;}\
			Cobject$Memory$AutoUnload$unload_pointer==0?(Cobject$Memory$AutoUnload$unload_pointer=__COUNTER__+1-Cobject$Memory$AutoUnload$var_count):0;\
			break;\
			default:;Cobject$Memory$AutoUnload$is_scan=0;\
		}\
	}\
}

// #define Get(VAR_TYPE, VAR_DATA)\
// ({\
// 	var Cobject$Framework$Get$get_cash = VAR_DATA;\
// 	(  ( Cobject$Framework$Get$get_cash.type==TYPE$Bool )\
// 	? Cobject$Framework$Get$get_cash.datas.VAR_TYPE.value\
// 	: ( Cobject$Framework$Get$get_cash.type==TYPE$Number )\
// 	? Cobject$Framework$Get$get_cash.datas.VAR_TYPE.value\
// 	: ( Cobject$Framework$Get$get_cash.type==TYPE$Array )\
// 	? (var)Cobject$Framework$Get$get_cash.datas.VAR_TYPE.value\
// 	: ( Cobject$Framework$Get$get_cash.type==TYPE$String )\
// 	? Cobject$Framework$Get$get_cash.datas.VAR_TYPE.value\
// 	: ( Cobject$Framework$Get$get_cash.type==TYPE$null )\
// 	? (uint8_t)0\
// 	: (uint8_t)0  );\
// })
#define Get(VAR_TYPE, VAR_DATA)\
(VAR_DATA.datas.VAR_TYPE.value)

#define getProp(START_VAR, GET_TYPE, INDEX)   (*(GET_TYPE*)((((void**)&(START_VAR)))+(1+INDEX)))

#define o_arraylen( ARRAY_TYPE, ARRAY )\
sizeof(ARRAY)/sizeof(ARRAY_TYPE)

#define AppExit( RETURN_CODE )\
Cobject$Utility$Thread$value_kit=(struct type$class_Cobject$Utility$Thread$value_kit){.exit_code=RETURN_CODE,.is_exit=o_true};return

#define setupThread(...)\
static void(*Cobject$Utility$Thread$setupThread[])()={__VA_ARGS__}

#define loopThread(...)\
static void(*Cobject$Utility$Thread$loopThread[])()={__VA_ARGS__}

#define startThread()\
int main()\
{\
	uint16_t setup_count = sizeof(Cobject$Utility$Thread$setupThread) / sizeof(void(*)());\
	uint16_t loop_count = sizeof(Cobject$Utility$Thread$loopThread) / sizeof(void(*)());\
	for ( uint16_t index=0; index<setup_count; index++ )\
	{\
		(Cobject$Utility$Thread$value_kit.is_exit==o_false)?(Cobject$Utility$Thread$setupThread[index](), 0):(({return(Cobject$Utility$Thread$value_kit.exit_code); 0;}));\
	}\
	for ( uint16_t index=0; o_true; index++ )\
	{\
		if ( index >= loop_count )\
		{\
			index = 0;\
		}\
		(Cobject$Utility$Thread$value_kit.is_exit==o_false)?(Cobject$Utility$Thread$loopThread[index](), 0):(({return(Cobject$Utility$Thread$value_kit.exit_code);0;}));\
	}\
}



// ��, ���� ��������.
typedef struct _bool_t
{
	uint8_t value : 1;
} bool_t;

// ���� ��������.
typedef double type$number_t$value;
typedef struct _number_t
{
	type$number_t$value value;
} number_t;

// �迭 ��������.
typedef uint16_t type$array_t$array_len;
typedef void* type$array_t$value;
// typedef struct _array_t
// {
// 	type$array_t$array_len array_len;
// 	type$array_t$value value;

// } array_t;

// ���ڿ� ��������.
typedef uint16_t type$string_t$string_len;
typedef uint16_t type$string_t$string_size;
typedef uint8_t type$string_t$value;
typedef struct _string_t
{
	type$string_t$string_len string_len;
	type$string_t$string_size string_size;
	type$string_t$value* value;
} string_t;

// // null ��������.
typedef struct _null_t
{
	uint8_t value : 1;
} null_t;

// // undefined ��������.
// // undefined �������� ������ ���� Ư���� �ִ� �������̴�.
// // 1. ��ȯ�Ǵ� �����Ͱ� ���� ���?? ���?? undefined�� ��ȯ�ȴ�.
// // 2. JavaScript�� ���� �����ϴ�.
typedef struct _undefined_t
{
	uint8_t value : 1;
} undefined_t;



typedef struct type$class_Cobject$Object_type$var
{
	uint8_t is_lvalue : 1;
	int8_t type : 7;
	union _datas
	{
		bool_t Bool;
		number_t Number;
		// array_t Array;
		struct _array_t
		{
			type$array_t$array_len array_len;
			struct type$class_Cobject$Object_type$var* value;
		} Array;
		string_t String;
		null_t Null;
		undefined_t Undefined;
		
	} datas;
} var;



// ��ȯ ��������.
typedef uint8_t type$return_state_t$log; 
typedef struct _return_state_t
{
	const uint8_t success : 7;
	const type$return_state_t$log* const log;
	const var data;
} return_state_t;



/// ���� ���� ///
return_state_t method$class_Cobject$Update(var* const data);




// Bool ������ ��ȯ �Լ�.
static var method$class_Cobject$Bool(uint8_t bool)
{
	return(
		(var)
		{
			.is_lvalue = o_false,
			.type = TYPE$Bool,
			.datas = {
				.Bool = {
					.value = bool,
				},
			},
		}
	);
}
var(*Bool)(uint8_t bool) = method$class_Cobject$Bool;

// Number ������ ��ȯ �Լ�.
static var method$class_Cobject$Number(type$number_t$value number)
{
	return(
		(var)
		{
			.is_lvalue = o_false,
			.type = TYPE$Number,
			.datas = {
				.Number = {
					.value = number,
				},
			},
		}
	);
}
var(*Number)(type$number_t$value number) = method$class_Cobject$Number;

// Array ������ ��ȯ �Լ�.
static var method$class_Cobject$Array(const type$array_t$array_len array_len, const var data, .../*const var data*/)
{
	// 1. ���� �޸𸮷� �Ҵ�.
	var* output_array = calloc(array_len, sizeof(var));
	// 2. ���� �޸� ������ �迭 �� ����.
	for ( type$array_t$array_len index=0; index<array_len; index++)
	{
		output_array[index] = getProp(array_len, var, index);
	}
	
	// 3. ������ ��ȯ.
	return(
		(var)
		{
			.is_lvalue = o_false,
			.type = TYPE$Array,
			.datas = {
				.Array = {
					.array_len = array_len,
					.value = output_array,
				},
			},
		}
	);

}
var(*Array)(type$array_t$array_len array_len, const var data, ...) = method$class_Cobject$Array;

// String ������ ��ȯ �Լ�.
var method$class_Cobject$String(const type$string_t$value* const string)
{
	// 1. ���� �޸� �Ҵ�. ���ڿ� ���� + �ι��� ũ��.
	type$string_t$value* output_string = (type$string_t$value*)calloc(strlen(string)+sizeof(type$string_t$value), sizeof(type$string_t$value));
	// 2. ���� �޸� ������ ���ڿ� ����.
	strcpy(output_string, string);

	// 3. �����Ͱ� ��ȯ.
	return(
		(var)
		{
			.is_lvalue = o_false,
			.type = TYPE$String,
			.datas = {
				.String = {
					.string_size = ({

						uint32_t result = 0;
						for (result=0; output_string[result]; result++); 

						(result);//return;
					}),
					.string_len = strlen(output_string),
					.value = output_string,
				},
			},
		}
	);
}
var(*String)(const type$string_t$value* const string) = method$class_Cobject$String;

// null ������ ��ȯ �Լ�.
var method$class_Cobject$Null()
{
	return(
		(var)
		{
			.is_lvalue = o_false,
			.type = TYPE$null,
			.datas = 0,
		}
	);
}
var(*Null)() = method$class_Cobject$Null;

// undefined ������ ��ȯ �Լ�.
var method$class_Cobject$Undefined()
{
	return(
		(var)
		{
			.is_lvalue = o_false,
			.type = TYPE$undefined,
			.datas = 0,
		}
	);
}
var(*Undefined)() = method$class_Cobject$Undefined;



// ������ ��ȯ�� ���� �Լ�.
// return_state_t method$class_Cobject$Return(const var* const data)
// {
// 	return(
// 		(return_state_t)
// 		{
// 			.success = 1,
// 			.log = 0,
// 			.data = 
// 		}
// 	);
// }
// return_state_t(*Return)(const var* const data) = method$class_Cobject$Return;



// �������� ���Ἲ ������Ʈ.
// return_state_t method$class_Cobject$Update(var* const data)
// {
// 	// ���Ἲ ������Ʈ.
// 	(*data)->verify = o_getVerify(*data);
	
// 	return(
// 		(return_state_t)
// 		{
// 			success : 1,
// 			log : 0,
// 			is_verify : 1,
// 			data : *data,
// 		}
// 	);
// }
// return_state_t(*Update)(var* const data) = method$class_Cobject$Update;



// var ���� �޸� ���� �Լ�.
return_state_t method$class_Cobject$Unload(const var data)
{
	switch ( data.type )
	{
		case TYPE$Array : free( data.datas.Array.value );
		goto OUT;
		case TYPE$String : free( data.datas.String.value );
		goto OUT;
		OUT:
		default:;
	}

	return(
		(return_state_t)
		{
			success : 1,
			log : 0,
			data : 0,
		}
	);
}
return_state_t(*Unload)(const var data) = method$class_Cobject$Unload;



// ���� ������ ���� �Լ�.
// return_state_t method$class_Cobject$Copy(var* const Lvalue, const var const LRvalue)
// {
// 	// 1. ��ü ������ ����.
// 	**Lvalue = *LRvalue;
// 	// 2. ���Ἲ ������Ʈ.
// 	method$class_Cobject$Update(Lvalue);

// 	// 3. ���� ��ȯ.
// 	return(
// 		(return_state_t)
// 		{
// 			success : 1,
// 			log : 0,
// 			is_verify : o_getVerify(*Lvalue),
// 			data : *Lvalue,
// 		}
// 	);
// }



var method$class_Cobject$Equel( const var get0, const var get1 )
{
	// 0. Ÿ���� ������ Ȯ��.
	if ( get0.type == get1.type )
	{

		// 1. Ÿ�Կ� ���� ó��.
		if ( get0.type == TYPE$Bool )
		{	// Bool Ÿ�� ó��.
			return ( get0.datas.Bool.value == get1.datas.Bool.value ) ? ( Bool(o_true) ) : ( Bool(o_false) );

		}
		else if ( get0.type == TYPE$Number )
		{	// Number Ÿ�� ó��.
			// return( get0->datas.Number.value == get1->datas.Number.value );
			return( get0.datas.Number.value == get1.datas.Number.value ) ? ( Bool(o_true) ) : ( Bool(o_false) );
		}
		else if ( get0.type == TYPE$Array )
		{	// Array Ÿ�� ó��. ���? ȣ�� ���ɼ� ����.
			///////////////////////////////////////////////////////////////////////////////////////////////// �迭 �� �ڵ嵵 �߰�!!!!
			printf("\n\n [ �����? ���� : cobject.h - Equel() ] \n\n");
			getchar();
			getchar();
		}
		else if ( get0.type == TYPE$String )
		{	// String Ÿ�� ó��.

			// ���ڿ� ���̰� �ٸ� ���? ���� ��ȯ.
			if ( get0.datas.String.string_size == get1.datas.String.string_size ) return( Bool(o_false) );

			// ���ڿ� ���� ���� �ٸ� ���?.
			for ( uint64_t index=0; index<get0.datas.String.string_size; index++ )
			{
				if ( get0.datas.String.value[index] != get1.datas.String.value[index] )
				{	// ���ڿ��� ���� �ٸ� ���? ���� ��ȯ.
					return( Bool(o_false) );
				};
			}
			// ���ڿ��� ���� ���? ���� ���? �� ��ȯ.
			return( Bool(o_true) );
		}
		else if ( get0.type == TYPE$null )
		{	// null Ÿ�� ó��.
			// ������ Ÿ���� �����Ƿ� �� ��ȯ.
			return( Bool(o_true) );
		}
		else if ( get0.type == TYPE$undefined )
		{	// ���� Ÿ���� �����Ƿ� �� ��ȯ.
			return( Bool(o_true) );
		}
		else
		{	// �� �ܿ��� ���? ���� ��ȯ.
			return( Bool(o_false) );
		}

	}
}



// Cobject Ŭ����.
// #ifdef __GNUC__
// #pragma GCC diagnostic push
// #pragma GCC diagnostic ignored "-Wincompatible-pointer-types"
// #endif
struct class$Cobject
{
	var(*Bool)(uint8_t bool);
	var(*Number)(type$number_t$value number);
	var(*Array)(type$array_t$array_len array_len, const var const data, ...);
	var(*String)(const type$string_t$value* const string);
	var(*Null)();
	var(*Undefined)();

	// return_state_t(*Update)(var* const data);
	// return_state_t(*Return)(const var* const data);
	return_state_t(*Unload)(const var const data);
	var(*Equel)( const var get0, const var get1 );
} Cobject = {
	Bool : method$class_Cobject$Bool,
	Number : method$class_Cobject$Number,
	Array : method$class_Cobject$Array,
	String : method$class_Cobject$String,
	Null : method$class_Cobject$Null,
	Undefined : method$class_Cobject$Undefined,

	// Update : method$class_Cobject$Update,
	// Return : method$class_Cobject$Return,
	Unload : method$class_Cobject$Unload,
	Equel : method$class_Cobject$Equel,
};
// #ifdef __GNUC__
// #pragma GCC diagnostic pop
// #endif

struct type$class_Cobject$Utility$Thread$value_kit
{
	uint8_t is_exit:4;
	int16_t exit_code:12;
} Cobject$Utility$Thread$value_kit = {
	.exit_code = 0,
	.is_exit = o_false,
};
