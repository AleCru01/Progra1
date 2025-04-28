#include <stdio.h>

main(){
	
	int espacios, i, j,k;
	
	printf("Dame las lineas de altitud: \n");
	scanf("%d", &espacios);
	
	for(i = 0; i<espacios; i++){
		for(j = espacios; j>=i; j--){
			printf(" ");
		}
		for(k = 0; k <= i; k++){
			printf("* ");
		}
		printf("\n");
	}
}
