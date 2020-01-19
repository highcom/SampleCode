#include<stdio.h>
#include<string.h>
#include<stdarg.h>

#define DEBUG

void lib_value_func(const char *funcname, const char *format, ...);
short lib_value_ret_short(const char *funcname);
short lib_value_ret_short_arg_char(const char *funcname, char type);
int lib_value_ret_int_arg_int_short(const char *funcname, int num, short num2);

short lib_func_1(void);
short lib_func_2(char type);
int lib_func_3(int num, short num2);


int main(void)
{
	printf("ret:%d\n", lib_func_1());
	printf("ret:%d\n", lib_func_2('b'));
	printf("ret:%d\n", lib_func_3(10, 20));
	return 0;
}

short lib_func_1(void)
{
#ifdef DEBUG
	short ret;
	lib_value_func(__func__, "s", &ret);
	return ret;
#endif
	return 1;
}

short lib_func_2(char type)
{
#ifdef DEBUG
	short ret;
	lib_value_func(__func__, "sc", &ret, type);
	return ret;
#endif
	return 1;
}

int lib_func_3(int num, short num2)
{
#ifdef DEBUG
	int ret;
	lib_value_func(__func__, "iis", &ret, num, num2);
	return ret;
#endif
	return 1;
}

/*
 * funcname:呼び出し元の巻数名
 * format:後に続く可変長引数の型を順番に並べた文字列
 *			s:short型
 *			i:int型
 *			c:char型
 * 可変長引数の1番目の型は呼び出し元のreturn値の型とし、アドレスで渡されるものとする
 * 可変長引数の2番目移行は呼び出し元の引数の型とする
 */
void lib_value_func(const char *funcname, const char *format, ...)
{
	va_list args;

	va_start(args, format);

	if (strncmp(format, "s", 3) == 0) {
		short *ret = va_arg(args, short *);
		*ret = lib_value_ret_short(funcname);
	} else if (strncmp(format, "sc", 3) == 0) {
		short *ret = va_arg(args, short *);
		char type = va_arg(args, int); /* va_argの第2引数は4byteで取るため代入時の暗黙キャストで良い */
		*ret = lib_value_ret_short_arg_char(funcname, type);
	} else if (strncmp(format, "iis", 3) == 0) {
		int *ret = va_arg(args, int *);
		int num = va_arg(args, int);
		short num2 = va_arg(args, int); /* va_argの第2引数は4byteで取るため代入時の暗黙キャストで良い */
		*ret = lib_value_ret_int_arg_int_short(funcname, num, num2);
	}
	va_end(args);
}

short lib_value_ret_short(const char *funcname)
{
	printf("%s ", funcname);
	return 1;
}

short lib_value_ret_short_arg_char(const char *funcname, char type)
{
	printf("%s ", funcname);
	printf("args[%c] ", type);
	return 2;
}

int lib_value_ret_int_arg_int_short(const char *funcname, int num, short num2)
{
	printf("%s ", funcname);
	printf("args[%d][%d] ", num, num2);
	return 3;
}
