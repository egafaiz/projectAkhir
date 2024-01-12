void MarqueeText(char *kalimat, int speed){
	int x; double y;
   	for(x=0; kalimat[x]!='\0'; x++){
	    printf("%c",kalimat[x]);
	    for(y=0; y<=speed; y++){
		}
   }
}

void Breadcrumb(char *kalimat[], int length) {
    int i;
    char simbol = '>';

    for (i = 0; i < length; i++) {
        printf("%s %c ", kalimat[i], (i == length - 1) ? '\0' : simbol);
    }
}