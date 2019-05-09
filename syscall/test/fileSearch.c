#include <stdio.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
   	char *file_name  = argv[1];
	int ret = 0;
	
	if ((ret = access( file_name, F_OK)) == 0){
		printf( "%s 파일이 있습니다.\n", file_name);
	      
	      	if (access( file_name, R_OK | W_OK) == 0){
			printf( "읽거나 쓰기가 가능합니다.\n");
	      	}
	
		else{
		printf("읽지 못하거나 내용을 변경할 수 없습니다.\n");
	}
	}
}
