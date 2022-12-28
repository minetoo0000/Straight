/*
키보드 입력 처리 헤더

헤더 순도 : A등급.
*/
//#define _IS_WINDOWS = 0

int __key_buf[150] = {0};

signed char keyRead() {
	int _key = -1;
	
	if (_kbhit())
	{
#if (_IS_WINDOWS == 0)
		if ( (_key = _getch()) == 27 )  // Mobile : 27 Desktop : 224
		{
			if ( (_key = _getch()) == 91 )  // Mobile : 91 Desktop : none
			{
				if ((_key = _getch()) == 65) return 0;  // UP M : 65 D : 72
				else if (_key == 67) return 1;  // RIGHT M : 67 D : 77
				else if (_key == 66) return 2;  // DOWN M : 66 D : 80
				else if (_key == 68) return 3;  // LEFT M : 68 D : 75
				else return _key;
			}

		} else if (_key == 10) return 10;  // ENTER M : 10 D : 13

#elif (_IS_WINDOWS == 1)
		if ((_key = _getch()) == 224) {
			if ((_key = _getch()) == 72) return 0;  // UP M : 65 D : 72
			else if (_key == 77) return 1;  // RIGHT M : 67 D : 77
			else if (_key == 80) return 2;  // DOWN M : 66 D : 80
			else if (_key == 75) return 3;  // LEFT M : 68 D : 75
			else return _key;
		}
		else if (_key == 13) return 10;  // ENTER M : 10 D : 13
#endif
		return _key;
	}
	
	return -1;
}

void updateKey()
{
	
}

int pickKey()
{
	
}