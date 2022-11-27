#include <stdio.h>
#include <fcntl.h>
#include <time.h>
#include <termios.h>
#include <sys/types.h>
#include <string.h>
#include <unistd.h>

void result(int time1, int time2, char text1[], int total_error){
	int time_tmp;
	float typing_speed;
	
	time_tmp = time2 - time1;
	printf("걸린 시간 : %dsec \n", time_tmp);
	
	typing_speed = ((strlen(text1)) - total_error / time_tmp) * 60;
	printf("분당 타수 : %.1f \n", typing_speed);
}

int main(){
	int first_word_d;
	int first_word_r, first_word_count = 0, first_word_error = 0;
	

	
	int total_error = 0;
	
	char first_word, first_word_text[] = "This is exercise no.4 of System programming lab3";
	
	struct termios init_attr, new_attr;
	time_t time1, time2;
	
	first_word_d = open(ttyname(fileno(stdin)), O_RDWR);
	
	tcgetattr(first_word_d, &init_attr);
	new_attr = init_attr;
	new_attr.c_lflag &= ICANON;
	new_attr.c_lflag &= ~ECHO;
	new_attr.c_cc[VMIN] = 1;
	new_attr.c_cc[VTIME] = 0;
	
	if(tcsetattr(first_word_d, TCSANOW, &init_attr) != 0){
		fprintf(stderr, "터미널 속성을 설정할 수 없음.\n");
	}
	printf("This is typing program.\n\n");
	time(&time1);
	
	printf("다음 문장을 그대로 입력하세요.\n\n%s\n", first_word_text);
	
	while((first_word_r = read(first_word_d, &first_word, 1)) > 0 && first_word != '\n'){
		if(first_word == first_word_text[first_word_count++]){
			write(first_word_d, &first_word,1);
		}
		else{
			write(first_word_d, "*", 1);
			first_word_error++;
		}
	}
	
	tcsetattr(first_word_d, TCSANOW, &init_attr);
	close(first_word_d);
	
	
	
	total_error = first_word_error;
	printf("\n\n타이핑 오류 횟수 %d\n", total_error);
	time(&time2);
	result(time1, time2, first_word_text, total_error);
	
	return 0;
}

		
