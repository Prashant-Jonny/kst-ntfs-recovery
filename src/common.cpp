/*
 * $Header$
 */
 #include "common.h"
 int testFor (char *data, int data_len, char *buffer, int buffer_len) {
	int pos=0;
	int data_pos=0;
//printf("data = 0x%x, data_len=%d, buffer=0x%x, buffer_len=%d\n", ( unsigned int )data, data_len, (unsigned int) buffer, buffer_len);

	for (pos=0; pos< (buffer_len-data_len); ) {
/*	printf("."); */
		if (buffer[pos]==data[0]) {
	//		printf("%c",data[0]);
			data_pos=0;
			while (data_pos < data_len) {

/*				printf("%c %c %d\n", buffer[pos], data[data_pos], data_pos);  */
				if (buffer[++pos] != data[++data_pos]) {
					goto notMatched;
				}
				printf("%c",data[data_pos-1]);

			}
			printf("%c",data[data_pos]);
//			printf("founded!\n");
			return ( pos-data_len );
		}
		notMatched: pos++;	
	}
  return -1;
}
