#include <stdio.h>
#include <string.h>

int int2string(int n, char* room){

	char charlist[10] = {'0', '1', '2', '3', '4',
                 '5', '6', '7', '8', '9'};

	int digit;
	int decimal;
	int hundred;

	if ((n % 1000) != n){
		return -1;
	}
	digit = n % 10;
	decimal = (n - digit)%100/10;
	hundred = (n - 10 * decimal - digit)/100;

	room[0] = charlist[hundred];
	room[1] = charlist[decimal];
	room[2] = charlist[digit];
	room[3] = '\0';

	return 0;
}
int main(){
	int width = 176;
	int height = 144;
	int size_per_frame = width * height * 1.5;
	int frame_num = 300;

	int i;

	const char* src_filename = "../resource/akiyo_qcif.yuv";

	char of_header[] = "img";
	char of_tail[] = ".yuv";
	char of_idx[4];
	char output_file[11];

	unsigned char *buf = (unsigned char*)malloc(size_per_frame);

	FILE *fp_read;
	FILE *fp_write;

	fp_read = fopen(src_filename, "rb");

	for (i = 0; i < frame_num; i++){
		int2string(i, of_idx);
		strcpy(output_file, of_header);
		strcat(output_file, of_idx);
		strcat(output_file, of_tail);

		fp_write = fopen(output_file, "wb");

		fread(buf, 1, size_per_frame, fp_read);
		fwrite(buf, 1, size_per_frame, fp_write);

	}
	fclose(fp_read);
	fclose(fp_write);
	return 0;
}