/*
TGI system ���

��� ���� : B���.
*/


// ������ ���� ���. //
typedef int16_t return_code_t;  // �Լ��� ��ȯ�ϴ� ���� �۾� ���� ���� ��Ÿ���� ��� �ÿ�.
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
{ // ���μ��� ���� ���.
	signed char state;
	/* state
	-2 : ���α׷� ���� �ʱ�ȭ ��� ����.(���� �� ����.)
	-1 : �ʱ�ȭ ��� ����.(���� �� ����.)
	0 : ���� ���� ����.
	1 : ���׶��� ���� ����.
	2 : ���� ��. 1�� ����Ǳ� �� ���� ���� ���·� ��ȯ ����.(���� ����)
	3 : ��׶��� ���� ����.
	�� ��: ���� ����� ����.
	*/

	unsigned char priority;
	/* priority
	�켱 ���� ��.
	0���� 7����.
	���� ���� ���� �켱 ���� ����.
	*/
} pcb;

// ��ǥ Ŷ. //
typedef struct
{
	short x, y; // �� ���� ��ǥ.

} coordinate_kit;

typedef struct
{
	// ���簢���� ��Ÿ���� 2�� ���� ��ǥ.
	short x1, y1; // ù ��° ���� ��ǥ.
	short x2, y2; // �� ��° ���� ��ǥ.

} coordinate_simple2D_kit;

typedef struct
{
	// �簢���� ��Ÿ���� 4�� ���� ��ǥ.
	short x1, y1;
	short x2, y2;
	short x3, y3;
	short x4, y4;

} coordinate_RAW2D_kit;

typedef struct
{
	// ������ü�� ��Ÿ���� �������� ��ǥ.
	short x1, y1, z1;
	short x2, y2, z2;
	short x3, y3, z3;
	short x4, y4, z4;

	short x5, y5, z5;
	short x6, y6, z6;
	short x7, y7, z7;
	short x8, y8, z8;

} coordinate_RAW3D_kit;

// ������Ʈ. //

// �ִϸ��̼�. //
typedef struct
{
	// �ִϸ��̼� �Ӽ�.
	short speed;
	unsigned long long count;

	// �ִϸ��̼� ȿ���� �̵��� ��ǥ.
	short set_x;
	short set_y;

} ani_kit;


/*
// ��ȯ ���� ���� ����. //
const return_block_t *__return_set[] = {
	return_block_t
}
*/


// �ý��� �Լ�. //
void systemMessage()
{
	printf("\n[TGI-system] - ");
}

return_code_t returnEvent(return_code_t return_code)
{  // ????? return ??? ????? ????? ????? ??? ??????? ?��?? ????. ??? ???? ?? ???? ????? ???? ???.
	if (!__DEBUG_MODE) return return_code;
	
	systemMessage();
    if (return_code >= 0)
    {
        switch (return_code)
        {
        	case 0: printf("�� �� ���� ��ȯ �̺�Ʈ�� �߻��Ͽ����ϴ�"); break;
        	
        	// 110����� ���ù��� �Լ� ����. //
        	case 111: printf("�� ���ù��ۿ� �����Ͱ� Ǫ���Ǿ����ϴ�"); break;
        	case 112: printf("���ù��ۿ� �����Ͱ� Ǫ���Ǿ����ϴ�"); break;
        	
        	default : printf("���ǵ��� ���� ��ȯ �ڵ��Դϴ�"); break;
        }
        printf(". Return code : %d", return_code);
    }
    else
    {
        if ( return_code >= -100 && return_code <= -91 )
        {
        	printf("�ҽ��ڵ� ������ �ý��� ������ �ʿ��մϴ�. �ý����� ������ �����˴ϴ�.");
        	
        	switch (return_code)
        	{
        		case -99: printf("\n	���� ���� : ������ ���� �ý��� ���� ��Ż. �ſ� ���������� ERRORPASS_ESCAPE_SYSTEM_LOOP�� �̿��� �� ������ ������ �� �ֽ��ϴ�"); break;
				
				default: printf("���ǵ��� ���� ���� �ڵ��Դϴ�"); break;
        	}
        	
        }
        else
        {
        	switch (return_code)
        	{
        		case -1: printf("������ ���� �Ǵ� �۾��� �߻��Ͽ����ϴ�"); break;
        		case -2: printf("�������� �ùٸ��� ���� �ڵ� �����Դϴ�"); break;
        		case -3: printf("��Ȯ���� ���� ���� ������ �߻��Ͽ����ϴ�"); break;
        		case -4: printf("������ ������ ��ġ���� �ʽ��ϴ�"); break;
        		case -5: printf("�� �� ���� �������Դϴ�"); break;
        		case -6: printf("��Ȯ���� ���� �۾� ������ �߻��Ͽ����ϴ�"); break;
        		case -7: printf("�ý��� ������� �ʿ��մϴ�. ��쿡 ���� �ҽ��ڵ� ������ �ý��� ������ �ʿ��� �� �ֽ��ϴ�"); break;
        		case -8: printf("�ý��� ������ �����߽��ϴ�. ������ �ʿ��մϴ�"); break;
        		case -9: printf("���ѷ����� �����Ǿ����ϴ�"); break;
        		case -10: printf("����� �� ������ �߻��߽��ϴ�"); break;
        		
        		case -111: printf("���ù��� ���� ���� ũ��� 1 �̻��̾�� �մϴ�."); break;
        		case -113: printf("���ù��ۿ� �� �۾��� �õ�������"); break;
        		case -114: printf("���ù��ۿ� Ǫ�� �۾��� �õ������� �ش� ���ù��۴� ���ù��� ���İ� ��ġ���� �ʽ��ϴ�. �ش� ���ù��۴� ��� 0�� �ƴ� �����ͷ� ä���� �ֽ��ϴ�"); break;
        		case -115: printf("���ù��ۿ� �� �۾��� �õ������� �ش� ���ù��۴� ���ù��� ���İ� ��ġ���� �ʽ��ϴ�. �ش� ���ù��۴� ��� 0�� �ƴ� �����ͷ� ä���� �ֽ��ϴ�"); break;
        		case -116: printf("���ù��ۿ� Ǫ�� �۾��� �õ������� �ش� ���ù��ۿ��� �� ������ ���� Ǫ�� �۾��� ��ҵƽ��ϴ�"); break;
        		
        		default: printf("���ǵ��� ���� ���� �ڵ��Դϴ�"); break;
        	}
        }
        
        printf(". Error code : %d", return_code);
    }
    
	getch();getch();
    return return_code;
}

void debugPause(int const *str) {  // ??????? ????? ??? ???? ??? ????? ?��?? ????.
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
	case 2:  // ������� ���� ����.
	case -2:  // ���� �ʱ�ȭ
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
// ���μ��� �ʱ�ȭ, ����, ��׶���, ����� �߰�.



// push pick ����. //
typedef uint16_t PUSH_BUFFER_SIZE_T;  // Ǫ�� ���� ��� ũ��. 2����Ʈ.

// push ������ ���۸� �����Ѵ�.
pointer new_Stack(size_t type_size, PUSH_BUFFER_SIZE_T buffer_len)
{
	if (buffer_len < 1) return( returnEvent(-111), (pointer)0 );
	
	pointer buf = 0;
	// ������ ũ��� ��� ���� ũ��� ����� ���� ũ��� ������ ũ���� ���̴�.
	if (  !(buf = calloc( (sizeof(PUSH_BUFFER_SIZE_T))+((type_size*buffer_len)+type_size), 1 ))  )
	{
		free(buf);
		return( returnEvent(-116), (pointer)0 );
	}
	
	*((PUSH_BUFFER_SIZE_T *)buf) = type_size*buffer_len;  // ����Ʈ ũ�� ����� ����.
	
	return buf;
}

// uint32_t���� �����͸� push�ϴ� �Լ�.
return_code_t push_uint32(pointer buf, uint32_t data)
{
	// ������ ������� ���� ������ ũ�⸦ ������.
	// �� ���� ���� �����͸� ���� ������ ����Ű���� ��.
	PUSH_BUFFER_SIZE_T buf_len = *((PUSH_BUFFER_SIZE_T*)buf) / sizeof(uint32_t);
	PUSH_BUFFER_SIZE_T pointing = 0;

	buf = (uint8_t*)buf + sizeof(PUSH_BUFFER_SIZE_T);  // 1����Ʈ ������ �� 2����Ʈ �̵�.



	// ���۽����� ó�� ��ġ���� 0�� ä�����ִ� ���, 0�� ��� �ǳ� �� ������ �����ͺ�� ���� 0�� ��ġ ã��.
	while ( !((uint32_t *)buf)[pointing] )
	{
		// ���۽����� ��� Ž�������� 0�ۿ� ���ٸ� �� ���۽����̹Ƿ� 0�� ��ġ�� data�� Ǫ��.
		if ( pointing >= buf_len )
		{
			((uint32_t *)buf)[0] = data+1;

			return(returnEvent(111));//�� ���ù��� ����.
		}
		pointing++;
	}  // pointing�� ���� ���ù����� ù ��° �����ͺ���� ����Ű�� ����.
	
	// �����ͺ�� ���� 0�� �ִ� ��ġ�� ã��.
	while ( ((uint32_t *)buf)[pointing] )
	{
		// ���۽����� ��� Ž�������� ��� �����ͷ� ä�����ִٸ� ������ ���� ����ġ ���� �߻�.
		if ( pointing >= buf_len ) return(returnEvent(-114));
		pointing++;
	}  // pointing�� ���� ���۽����� �����ͺ�� ���� 0�� ����Ű�� ����.
	
	// pointing�� ���� ����Ű���ִ� 0�� �������̶��.
	// (�ٷ� �� ���� ��ġ�� �����ͺ���� �ִٸ� ���� pointing�� ����Ű���ִ� 0�� ��������.)
	if ( ((uint32_t *)buf)[pointing+1] )
	{
		// ���ù��۰� �� �������Ƿ� Ǫ�� �Ұ�. ���� �̺�Ʈ �߻�.
		return(returnEvent(-116));
	}
	// Ǫ�� ������ ���.
	else
	{
		// ���ù��ۿ� data �׾� �ø�.
		((uint32_t *)buf)[pointing] = data+1;
		return(returnEvent(112));
	}
	
}

// ���۽��ÿ��� ���� ���������� ����� �����͸� ������, peek. //
int64_t pick_uint32(pointer buf)
{
	//���ù����� ������� ���۽����� ���̸� ����.
	// PUSH_BUFFER_SIZET buf_len = ( *((PUSH_BUFFER_SIZET*)buf++) ) / 4;
	PUSH_BUFFER_SIZE_T buf_len = *((PUSH_BUFFER_SIZE_T*)buf) / sizeof(uint32_t);
	PUSH_BUFFER_SIZE_T pointing = 0;

	// ���� �������� �������� ������ �������� �̵���Ŵ.
	buf = (uint8_t*)buf + sizeof(PUSH_BUFFER_SIZE_T);  // 1����Ʈ ������ �� 2����Ʈ �̵�.

	

	// ������ ã��. //
	
	//���ù����� ó�� ��ġ�������� �ִ� 0�� �ƴ� ���ӵ� �����ͺ�ϵ��� ��� �ǳ� ��.
	while ( ((uint32_t *)buf)[pointing] )
	{
		//���ù��۰� 0�� �ƴ� �����ͷ� ��� ä���������Ƿ� ������ ���� ����ġ ���� �߻�.
		if ( pointing >= buf_len ) return(returnEvent(-115));
		pointing++;
	}//pointing�� ���� 0�� �ƴ� ���ӵ� �����ͺ�� ������ �ִ� 0�� ��ġ�� ����Ű�� ����.



	//���ù��� ó�� ��ġ�� �ִ� 0�� ��� �ǳ� ��.
	while ( !(((uint32_t *)buf)[pointing]) )
	{
		
		//���ù��۰� �� ������. �̷� ��� -1�� ��ȯ.
		if ( pointing >= buf_len )
		{
			//�������� ���ù����� �� ���� �ְ�, ù ��° �����ͺ���� 0�� ��ġ�� ���� ���
			if ( ((uint32_t *)buf)[0] )
			{
				//���۽����� 0�� ��ġ���� ��.
				uint32_t result = ((uint32_t *)buf)[0] - 1;
				((uint32_t *)buf)[0] = 0;
				
				return( result );
			}
			return(returnEvent(-112), -1);
		}
		pointing++;
	}//pointing�� ���� 0 ������ �ִ� 0�� �ƴ� ���� ����Ű�� ����.


	
	//pointing�� ����Ű�� ��ġ���� �����͸� ������.
	uint32_t result = ((uint32_t *)buf)[pointing] - 1;
	((uint32_t *)buf)[pointing] = 0;

	return( result );
}
