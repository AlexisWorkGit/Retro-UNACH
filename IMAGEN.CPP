
    #include <alloc.h>
    #include <conio.h>
    #include <graphics.h>
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <dos.h>
    #include <ctype.h>
    #include <iostream.h>
	#define TOP 1
	#define DOWN 2
	#define LEFT 3
	#define RIGHT 4

    struct BMP
    {
      char Type[2];           //Tipo de archivo. Establecer en "BM".
      unsigned long Size;     //Tama¤o en BYTES del archivo.
      unsigned long Reserved;      //Reservado. Poner a cero.
      unsigned long OffSet;   //Dezplazamiento a los datos.
      unsigned long headsize; //Tama¤o del resto de cabecera. Establecer en 40.
      unsigned long Width;     //Ancho del mapa de bits en p¡xeles.
      unsigned long Height;     //Altura del mapa de bits en p¡xeles.
      unsigned int  Planes;    //N£mero de planos. Esstablecer en 1.
      unsigned int  BitsPerPixel;       //N£mero de Bits por p¡xeles.
      unsigned long Compression;   //Compresi¢n. Por lo general se establece en 0.
      unsigned long SizeImage;  //Tama¤o en Bytes del mapa de bits.
      unsigned long XPixelsPreMeter;     //P¡xeles horizontales por metro.
      unsigned long YPixelsPreMeter;     //P¡xeles verticales por metro.
      unsigned long ColorsUsed;   //N£meros de colores usados.
      unsigned long ColorsImportant;  //N£mero de colores "importantes".
    };

    int ShowBMP(int x, int y, char* FileName)
    {
	int b,a;
	struct  BMP Obj;

	unsigned char* Datas;
	int in=0;
	unsigned char c=0;
	FILE * fp;

	fp = fopen(FileName,"rb");  //**Representa Read BMP
	if(!fp){
	printf("Error : No es posible abrir el archivo ..");
	exit(0);
	}

	fread(&Obj, sizeof(Obj), 1, fp);
	if(Obj.BitsPerPixel!=4)  // Esto no es un bmp de 16 colores que podamos leer;
	{
	 fclose(fp);
	 printf("Error : Formato de archivo no soportado ..");
	 exit(0);
	};
	fseek(fp,Obj.OffSet,SEEK_SET);
	Datas=(unsigned char*) calloc(Obj.Width/2+1, sizeof(unsigned char));
	for(b=Obj.Height;b>=0;b--)
	{
	 fread(Datas, sizeof(unsigned char), Obj.Width/2, fp);
	 c=0;
	 in=0;
	 for(a=0;a<=Obj.Width;a+=2)
	 {
	     c = (Datas[in] | 0x00) >>4;
	     putpixel(a+x,b+y,c);
	     c = (Datas[in] | 0xF0) & 0x0F;
	     putpixel(a+1+x,b+y,c);
	     in++;
	 }
	}
	free (Datas);
	fclose(fp);
	return 1;
    }
	void scoree(int s=1)
{
	static unsigned long sc=0;
	window(70,22,78,23);
	if(s)
	{
		sc=sc+100;
		cprintf("      ");
		window(70,22,78,23);
		cprintf("%ld",sc);
	}
	else
		sc=0;
}
void statute(char *s,int c=WHITE)
{
	window(70,23,78,25);
	textcolor(c);
	cprintf("%s",s);
	for(int x=strlen(s);x<7;x++)
	cprintf(" ");
	textcolor(WHITE);
}
    void lines()
{
	textbackground(1);
	clrscr();
	textcolor(11);
	window(19,1,51,24);
	for(int x=0;x<24;x++)
	cprintf("³                              ³ ");
	cprintf("³                              ³");
	window(55,6,77,19);
	cprintf("  Instrucciones         \n");
	cprintf("Pulse <- o -> ");
	cprintf("Der o Iz\n");
	cprintf("Pulse P para pausar       \n");
	cprintf("Pulse X para salir");
	window(55,18,79,20);
	cprintf("SCORE 10000");
	window(55,20,79,24);
	cprintf("GAME OVER");
}

int strt[3],abj[3],end[3]; //**variables que determinan comienzo del juego
int cars[3],go=0,speed;   //**variables que determinan comienzo del juego
void score(int s=1)
{
	static unsigned int scr=0;     //**valor estatico que no puede ser negativo
	if (s==0)
	{
		scr=0;
		return;
	}
	textcolor(WHITE);
	window(61,18,70,23);
	cprintf("        ");
	window(61,18,70,23);
	cprintf("%d",++scr);
	textcolor(11);
	for (int x=1;x<=10;x++)
	if(scr>=x*100 && speed>20)
		speed--;

}
void status(int s)   //**Funcion que determina el estado actual del juego
{
	textcolor(WHITE);
	window(55,20,65,21);
	switch(s)
	{
		case 1 : cprintf("Jugando..."); break;
		case 2 : cprintf("Pausa    "); break;
		case 3 : cprintf("Game Over ");
	}
	textcolor(11);
}
void myc(int x)
{
	int i;
	textcolor(10);
	window(20+(x*10),21,29+(x*10),25);    //**Dimensiones del jugador
	cprintf("  ²²²²²²  ");
	cprintf("Þ²²²²²²²²Ý");
	cprintf(" ²²Ý²²Þ²² ");
	cprintf("Þ²²Ý²²Þ²²Ý");
	textcolor(WHITE);
	delay(10);
	if (x==0 || x==2)    //**Bug
	{
		x=1;
		window(20+(x*10),21,29+(x*10),25);
		for(i=0;i<4;i++)
		cprintf("          ");
	}
	else             //**Bug
	{
		x=0;
		window(20+(x*10),21,29+(x*10),25);
		for(i=0;i<4;i++)
		cprintf("          ");
		x=2;
		window(20+(x*10),21,29+(x*10),25);
		for(i=0;i<4;i++)
		cprintf("          ");
	}

}
void dc(int x, int car)  //**Funcion de estados del vehiculo
{

	if(strt[x]==25)
	{
		strt[x]=1;
		abj[x]=1;
		end[x]=1;
	}
	if(strt[x]<10)
	window(20+(x*10),1,29+(x*10),5);

	textcolor(12);
	if(end[x]>0)
	{
		window(20+(x*10),end[x]+20,29+(x*10),25);
		if(end[x]==1){
		cprintf("          ");
		cprintf("Þ²²²²²²²²Ý");
		cprintf(" ²²²²²²²² ");
		cprintf("Þ²²²²²²²²Ý");
		}
		else if(end[x]==2)
		{
		cprintf("          ");
		cprintf("Þ²²²²²²²²Ý");
		cprintf(" ²²²²²²²² ");
		}
		else if(end[x]==3)
		{
		cprintf("          ");
		cprintf("Þ²²²²²²²²Ý");
		}
		else
		{
		cprintf("          ");
		end[x]=-1;
		strt[x]=0;
		cars[x]=0;
		}
		end[x]++;
	}
	else
	if(strt[x]>=5)
	{
	window(20+(x*10),abj[x],29+(x*10),abj[x]+5);
	cprintf("          ");
	cprintf("Þ²²²²²²²²Ý");
	cprintf(" ²²²²²²²² ");
	cprintf("Þ²²²²²²²²Ý");
	cprintf("  ²²²²²²  ");
	abj[x]++;
	}
	else if(strt[x]==1)
		cprintf("  ²²²²²²  ");
	else if(strt[x]==2)
	{
		cprintf("Þ²²²²²²²²Ý");
		cprintf("  ²²²²²²  ");
	} else if(strt[x]==3)
	{
		cprintf(" ²²²²²²²² ");
		cprintf("Þ²²²²²²²²Ý");
		cprintf("  ²²²²²²  ");
	}else if(strt[x]==4)
	{
		cprintf("Þ²²²²²²²²Ý");
		cprintf(" ²²²²²²²² ");
		cprintf("Þ²²²²²²²²Ý");
		cprintf("  ²²²²²²  ");
	}
	strt[x]++;
	if(strt[x]==21 && x==car)   //Diferentes velocidades que pueden tomar
	{                          //Los obstaculos
	status(3);
	speed=30;
	score(0);
	sound(60);
	delay(110);
	nosound();
	sound(80);
	delay(150);
	nosound();
	sound(120);
	delay(210);
	nosound();
	go=1;
	getch();
	}
	textcolor(YELLOW);
//
}
    void main()
    {
    int color;
    int gd , gm ;
    gd = VGA ; gm = VGAHI;

    int opcion=0;
    char usuario[80];
    char contra[80];
    char fusuario[80];
    char fcontra[80];
    int registro=0;
    int var=0;
    initgraph(&gd,&gm,"C:\TURBOC3\BGI");
       setfillstyle(SOLID_FILL,BLACK);
     floodfill(540,100,BLACK);
     for(int i=1;i<65;i++)    //**Marco
 {
  gotoxy(7+i,5);
  printf("²");
 }
  for(i=1;i<20;i++)
 {
  gotoxy(8,5+i);
  printf("²");
 }
   for(i=1;i<65;i++)
 {
  gotoxy(7+i,24);
  printf("²");
 }
  for(i=1;i<65;i++)
 {
  gotoxy(7+i,17);
  printf("²");
 }
   for(i=1;i<20;i++)
 {
  gotoxy(71,5+i);
  printf("²");
 }
     setcolor(WHITE);
     settextstyle(DEFAULT_FONT,HORIZ_DIR,2);
     outtextxy(120,310,"DIGITE SU OPCION ->");
     setcolor(WHITE);
     settextstyle(DEFAULT_FONT,HORIZ_DIR,2);
     outtextxy(270,110,"UNACH");
     setcolor(WHITE);
     settextstyle(DEFAULT_FONT,HORIZ_DIR,1);
     outtextxy(140,140,"BIENVENIDO AL SISTEMA DE INGRESO Y REGISTRO");
     settextstyle(DEFAULT_FONT,HORIZ_DIR,1);
     setcolor(WHITE);
     outtextxy(200,175,"INICIAR SESION O REGISTRARSE");
     setcolor(WHITE);
     settextstyle(DEFAULT_FONT,HORIZ_DIR,1);
     outtextxy(120,210,"DIGITE 1 PARA INICIAR SESION O 2 PARA REGISTRASE");
     gotoxy(56,20);
     scanf("%d",&registro);
     if(registro==2)
     {
      FILE* ficheroU;
      ficheroU=fopen("proyecto.txt","a+");
      clrscr();
	      setfillstyle(SOLID_FILL,BLACK);
     floodfill(540,100,BLACK);
     for(int i=1;i<65;i++)    //**Marco
 {
  gotoxy(7+i,5);
  printf("²");
 }
  for(i=1;i<20;i++)
 {
  gotoxy(8,5+i);
  printf("²");
 }
   for(i=1;i<65;i++)
 {
  gotoxy(7+i,24);
  printf("²");
 }
   for(i=1;i<20;i++)
 {
  gotoxy(71,5+i);
  printf("²");
 }
   setcolor(WHITE);
   settextstyle(DEFAULT_FONT,HORIZ_DIR,3);
   outtextxy(220,120,"REGISTRO");
   setcolor(WHITE);
   settextstyle(DEFAULT_FONT,HORIZ_DIR,2);
 outtextxy(80,220,"USUARIO:");           //**Ingreso usuario registro
  setcolor(WHITE);
 settextstyle(DEFAULT_FONT,HORIZ_DIR,2);
 outtextxy(80,300,"CLAVE:");
 setcolor(WHITE);
 line(200,240,530,240);
  setcolor(WHITE);
 line(170,315,530,315);
  gotoxy(28,15);
  scanf("%s",&fusuario);
  fprintf(ficheroU,"%s\n",fusuario);
  gotoxy(24,19);
   scanf("%s",&fcontra);
   fprintf(ficheroU,"%s\n",fcontra);
   clrscr();
  setfillstyle(SOLID_FILL,BLACK);
 floodfill(540,100,BLACK);
 for(i=1;i<65;i++)            //**Marco
 {
  gotoxy(7+i,5);
  printf("²");
 }
  for(i=1;i<20;i++)
 {
  gotoxy(8,5+i);
  printf("²");
 }
   for(i=1;i<65;i++)
 {
  gotoxy(7+i,24);
  printf("²");
 }
   for(i=1;i<20;i++)
 {
  gotoxy(71,5+i);
  printf("²");
 }
  settextstyle(DEFAULT_FONT,HORIZ_DIR,4); //Pantalla de carga
  setcolor(WHITE);
 outtextxy(180,160,"CARGANDO");
  setcolor(WHITE);
 settextstyle(DEFAULT_FONT,HORIZ_DIR,2);
 outtextxy(280,230,"² ²");
 setcolor(WHITE);
 settextstyle(DEFAULT_FONT,HORIZ_DIR,2);
 outtextxy(280,290,"² ²");
  setcolor(WHITE);
 settextstyle(DEFAULT_FONT,HORIZ_DIR,2);
 outtextxy(260,260,"²");
  setcolor(WHITE);
 settextstyle(DEFAULT_FONT,HORIZ_DIR,2);
 outtextxy(330,260,"²");
 getch();
 clrscr();
  setfillstyle(SOLID_FILL,BLACK);
 floodfill(540,100,BLACK);
   for(i=1;i<65;i++)
 {
  gotoxy(7+i,5);
  printf("²");
 }
  for(i=1;i<20;i++)
 {
  gotoxy(8,5+i);
  printf("²");
 }
   for(i=1;i<65;i++)
 {
  gotoxy(7+i,24);
  printf("²");
 }
   for(i=1;i<20;i++)
 {
  gotoxy(71,5+i);
  printf("²");
 }
   settextstyle(DEFAULT_FONT,HORIZ_DIR,4);
  setcolor(WHITE);
 outtextxy(130,160,"USTED SE HA");
  settextstyle(DEFAULT_FONT,HORIZ_DIR,4);
  setcolor(WHITE);
 outtextxy(130,200,"REGISTRADO");
  settextstyle(DEFAULT_FONT,HORIZ_DIR,4);
  setcolor(WHITE);
 outtextxy(130,240,"CORECTAMENTE");
 getch();                     //**Registro Completo
     fclose(ficheroU);
     }

  if(registro==1)              //**Inicio de sesion
  {
	    clrscr();
	    setfillstyle(SOLID_FILL,BLACK);
     floodfill(540,100,BLACK);
     for(int i=1;i<65;i++)      //**Marco
 {
  gotoxy(7+i,5);
  printf("²");
 }
  for(i=1;i<20;i++)
 {
  gotoxy(8,5+i);
  printf("²");
 }
   for(i=1;i<65;i++)
 {
  gotoxy(7+i,24);
  printf("²");
 }
   for(i=1;i<20;i++)
 {
  gotoxy(71,5+i);
  printf("²");
 }
  setcolor(WHITE);
  settextstyle(DEFAULT_FONT,HORIZ_DIR,3);
 outtextxy(220,120,"LOG ING");
  setcolor(WHITE);
  settextstyle(DEFAULT_FONT,HORIZ_DIR,2);
 outtextxy(80,220,"USUARIO:");
  setcolor(WHITE);
 settextstyle(DEFAULT_FONT,HORIZ_DIR,2);
 outtextxy(80,300,"CLAVE:");
 setcolor(WHITE);
 line(200,240,530,240);
  setcolor(WHITE);
 line(170,315,530,315);
  gotoxy(28,15);
  scanf("%s",&usuario);
  gotoxy(24,19);
  scanf("%s",&contra);
 }
   FILE* ficheroU;
  ficheroU=fopen("proyecto.txt","rt");
  do
  {
  fscanf(ficheroU,"%s",fusuario);
  fscanf(ficheroU,"%s",fcontra);
  if(strcmp(fusuario,usuario)==0)
   {                                 //**Comparacion de datos del archivo
   if(strcmp(fcontra,contra)==0)
     {
      var=1;
     }
    }
   }while(!feof(ficheroU));
   if(var==1)
   {
    clrscr();
     setfillstyle(SOLID_FILL,BLACK);
      floodfill(540,100,BLACK);
       for( i=1;i<65;i++)    //**Marco
 {
  gotoxy(7+i,19);
  printf("Í");
 }
  for(i=1;i<6;i++)
 {
  gotoxy(8,19+i);
  printf("þ");
 }
   for(i=1;i<65;i++)
 {
  gotoxy(7+i,24);
  printf("Í");
 }
   for(i=1;i<5;i++)
 {
  gotoxy(71,19+i);
  printf("þ");
 }
  setcolor(WHITE);
      settextstyle(SMALL_FONT,0,5);
      outtextxy(80,310,"NOTA:El fin de este programa es simular");
       setcolor(WHITE);
      settextstyle(SMALL_FONT,0,5);
      outtextxy(80,330,"los videojuegos retro,en honor a estos");
       setcolor(WHITE);
      settextstyle(SMALL_FONT,0,5);
      outtextxy(80,350,"PROGRAMM LAB 2019");
	 setcolor(WHITE);
	  for(i=35;i<555;i++)
	  {
	  line(25+i,170,25+i,200);
	    }

    for(i=35;i<555;i++)
      {
      setcolor(GREEN);
      line(25+i,170,25+i,200);         //** Tamanio barra verde
      delay(1);

      setcolor(WHITE);
      settextstyle(SMALL_FONT,0,16);
      outtextxy(220,220,"CARGANDO");
      delay(10);                       //** Retraso en segundos

      setcolor(rand()%16);             //** Color aleatorio de los puntos.
      settextstyle(SMALL_FONT,HORIZ_DIR,16);
      outtextxy(415,220,"...");
      delay(10);
      }

      do
      {
      clrscr();
    setfillstyle(SOLID_FILL,BLACK);
 floodfill(540,100,BLACK);
    ShowBMP(200,40,"unach.bmp"); /* PONER NOMBRE DE ARCHIVO AQUI */
    ShowBMP(315,200,"sello.bmp"); /* PONER NOMBRE DE ARCHIVO AQUI */

 setfillstyle(SOLID_FILL,BLACK);
 floodfill(540,100,BLACK);

  setcolor(WHITE);
 settextstyle(DEFAULT_FONT,HORIZ_DIR,2);
 outtextxy(170,290,"1.GALERIA DE JUEGOS");
  setcolor(WHITE);
 settextstyle(DEFAULT_FONT,HORIZ_DIR,2);
 outtextxy(170,340,"2.CREDITOS");
  setcolor(WHITE);
 settextstyle(DEFAULT_FONT,HORIZ_DIR,2);
 outtextxy(170,390,"3.SALIR");
  setcolor(WHITE);
  gotoxy(35,40);
  scanf("%d",&opcion);
  switch(opcion)
  {
   case(1):
   clrscr();
    setfillstyle(SOLID_FILL,BLACK);
    floodfill(540,100,BLACK);
    ShowBMP(40,90,"juego1.bmp");     //**Imagenes usadas
    ShowBMP(270,70,"juego2.bmp");
    ShowBMP(490,70,"juego3.bmp");
 for(int i=1;i<22;i++)               //**Marcos
 {
  gotoxy(2+i,3);
  printf("Í");
 }
  for(i=1;i<20;i++)
 {
  gotoxy(3,3+i);
  printf("º");
 }
   for(i=1;i<22;i++)
 {
  gotoxy(2+i,23);
  printf("Í");
 }
  for(i=1;i<20;i++)
 {
  gotoxy(23,3+i);
  printf("º");
 }
  for(i=1;i<22;i++)
 {
  gotoxy(29+i,3);
  printf("Í");
 }
  for(i=1;i<20;i++)
 {
  gotoxy(30,3+i);
  printf("º");
 }
   for(i=1;i<22;i++)
 {
  gotoxy(29+i,23);
  printf("Í");
 }
  for(i=1;i<20;i++)
 {
  gotoxy(50,3+i);
  printf("º");
 }
  for(i=1;i<22;i++)
 {
  gotoxy(56+i,3);
  printf("Í");
 }
  for(i=1;i<20;i++)
 {
  gotoxy(57,3+i);
  printf("º");
 }
   for(i=1;i<22;i++)
 {
  gotoxy(56+i,23);
  printf("Í");
 }
  for(i=1;i<20;i++)
 {
  gotoxy(77,3+i);
  printf("º");
 }

  setcolor(WHITE);
      settextstyle(DEFAULT_FONT,HORIZ_DIR,3);
      outtextxy(90,240,"1");
	setcolor(WHITE);
      settextstyle(DEFAULT_FONT,HORIZ_DIR,2);
      outtextxy(60,280,"RETRO");
      setcolor(WHITE);
      settextstyle(DEFAULT_FONT,HORIZ_DIR,2);
      outtextxy(70,300,"CAR");
       setcolor(CYAN);
      settextstyle(DEFAULT_FONT,HORIZ_DIR,3);
      outtextxy(310,240,"2");
	 setcolor(WHITE);
      settextstyle(DEFAULT_FONT,HORIZ_DIR,2);
      outtextxy(255,280,"AHORCADO");
       setcolor(GREEN);
      settextstyle(DEFAULT_FONT,HORIZ_DIR,3);
      outtextxy(520,240,"3");
	setcolor(WHITE);
      settextstyle(DEFAULT_FONT,HORIZ_DIR,2);
      outtextxy(495,280,"SNAKE ");
      setcolor(WHITE);
      settextstyle(DEFAULT_FONT,HORIZ_DIR,2);
      outtextxy(500,300,"GAME");
      setcolor(WHITE);
     int juego=0;
      scanf("%d",&juego);
      switch(juego)         //**Seleccion de juegos
      {
       case(1):
	   closegraph();    //Juego carritos
	   clrscr();
	   randomize();
	   _setcursortype(_NOCURSOR);
	char c,ch;
	   int i,x;
	   while(1){
	   for(x=0;x<3;x++)
	{
		strt[x]=1;
		abj[x]=1;
		end[x]=0;
		cars[x]=0;
	}

	int salir=0;
	lines();
	status(1);
	speed=30; // 30-20
	x=1;
	myc(x);
	go=0;
	while(!go)
	{
	while(!kbhit())
	{

		if(random(speed)==5 && cars[0]==0 && (cars[1]==0 || cars[2]==0))  //**Condicionales que aumentan
			cars[0]=1;                                                //**O disminuyen los obstaculos
		else if(random(speed)==5 && cars[1]==0 && (cars[0]==0 || cars[2]==0))
			cars[1]=1;
		else if(random(speed)==5 && cars[2]==0 && (cars[1]==0 || cars[0]==0))
			cars[2]=1;
		for(i=0;i<3;i++)
			if(cars[i]!=0)
				dc(i,x);

		sound(100);   //**Sonido de tipo 100
		delay(speed*2);
		nosound();
		score();
	}
	c=getch();
	switch(tolower(c))  //**Nos coloca en minusculas nuestra opcion
	{
	case 'p' :	status(2);        //**Pausa
				sound(1500);
				delay(210);
				nosound();
				sound(350);
				delay(150);
				nosound();
				sound(1000);
				delay(300);
				nosound();
				getch();
				status(1);
				break;
	case 0 : 	ch=getch();      //**Sigue jugando
				if(ch==75 && x>0)
				{
					x--;
					myc(x);
					sound(1200);
					delay(20);
				}
				else if(ch==77 && x<2)
				{
					x++;
					myc(x);
					sound(1200);
					delay(20);
				}
				break;
	case 'x':      //**salir
	  return;
	}
	}
	}//otro while

       break;

       case 2:
       closegraph();
	 clrscr();

       char palabras[5][10],palabra[10],letra,respuesta[10],nick[20];
	int j=0,l=0,intn=0,y=0,op;


	do{
	strcpy(palabras[0],"unach");
	strcpy(palabras[1],"lapiz");
	strcpy(palabras[2],"arbol");
	strcpy(palabras[3],"libro");
	strcpy(palabras[4],"puerco");

	for(int i=0;i<26;i++)
	{
	   gotoxy(i*2+18,7);
	   textcolor(i+1);
	   cprintf("%c",65+i);
	}

	srand(time(0));
	j = 0+rand()%5;

	strcpy(palabra,palabras[j]);
	l=strlen(palabra);

	for(i=1;i<=l;i++)
	{
	     gotoxy(29+i*4,19);
	     cprintf("_");
	}

	do{

	   gotoxy(25,4);
	   textcolor(10);
	   cprintf("BIENVENIDOS AL JUEGO DEL AHORCADO");
	   gotoxy(25,9);
	   cprintf("A D I V I N A    L A    P A L A B R A");
	   gotoxy(28,12);
	   cprintf("introduzca una letra ======>"  );

	   do{
		letra = tolower(getch());

	   }while(!isalpha(letra));

	       gotoxy(intn+10,22);
	       cprintf("%c",letra);

		gotoxy(20,15);
		cprintf("el numero de intentos maximos son 10 y llevas [%d] ",intn+1);

		for(i=0;i<l;i++)
		{
			if(letra==palabra[i])
			{
			   gotoxy(33+i*4,18);
			   cprintf("%c",letra);
			   respuesta[i]=letra;

			}
		   y=strcmp(palabra,respuesta);
		   if(y==0)
			{
			  gotoxy(25,24);
			  cprintf("FELICIDADES ADIVINASTE LA PALABRA");
			  intn=0;
			}
		   else
			if(intn==10)
			{
			  gotoxy(26,24);
			  cprintf("INCORRECTO LA PALABRA ERA ===> %s",palabra);
			  intn=0;
			}


		}
		intn++;
	}while(intn!=10 && y!=0);

	printf("\n\t\t\t desea continuar jugando? :   (S/N)");
	scanf("%s",&letra);
	intn=0;
	clrscr();

	}while(letra=='s' && letra!='n');

	clrscr();
	cprintf("\n\n\n\n\nGRACIAS POR USAR NUESTRO JUEGO");
	getch();
       break;
	   case(3):
	   closegraph();
		clrscr();
	_setcursortype(_NOCURSOR);
	textcolor(WHITE);
	cprintf("\n   ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿  ");
	for(i=0;i<17;i++)
	cprintf("   ³                                                                         ³  ");
	cprintf("   ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ  ");
	cprintf("   ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿   Pulse 'x' Para salir         ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿  ");
	cprintf("   ³  S N A K E  G A M E  ³   Pulse 'p' para pausar y jugar³ SCORE : 0       ³  ");
	cprintf("   ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ                                ³ STATUS: Jugando ³  ");
	cprintf("                                                           ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ  ");
	int snkx[20],snky[20],d=LEFT,p=0,sz=6,restart=1;
	while(1)
	{
		if(restart)
		{
			for(i=0;i<6;i++)
			snkx[i]=30+i*2;
			for(i=6;i<20;i++)
			snkx[i]=0;
			for(i=0;i<20;i++)
			snky[i]=9;
			sz=6;
			p=0;
			d=LEFT;
			restart=0;
			scoree();
			window(6,3,76,19);
			for(i=0;i<610;i++)
			cprintf("  ");
		}
		int x,y;
		if(p!=1)
		{
			randomize();
			do{
						x=random(70)+6;
					}while(x%2==1);
					y=random(16)+3;
			p=1;
			window(x,y,x+1,y+1);
			textcolor(LIGHTGREEN);
			cprintf("%c",1); //**Carita comible
			textcolor(WHITE);
		}
		while(!kbhit())
		{
			statute("Jugando",LIGHTGREEN);
			window(snkx[sz-1],snky[sz-1],snkx[sz-1]+2,snky[sz-1]+2);
			cprintf(" ");
			for(i=0;i<sz-1;i++)
			{
				window(snkx[i],snky[i],snkx[i]+1,snky[i]+1);
				cprintf("þ");
			}
			for(i=sz-1;i>=1;i--)
			{
				snkx[i]=snkx[i-1];
				snky[i]=snky[i-1];
			}
			switch(d)
			{
				case RIGHT : snkx[0]+=2; break;    //**snkx representa la coordenada x para la izquierda
				case LEFT  : snkx[0]-=2; break;    //**snkx representa la coordenada x para la derecha
				case TOP   : snky[0]-=1; break;    //**snky representa la coordenada y para arriba
				case DOWN  : snky[0]+=1;           //**snky representa la coordenada y para abajo
			}
			delay(200); //** Delay representa velocidad de retraso
			if(x==snkx[0] && y==snky[0])
			{
				int f=0;
				do{
					do{
						x=random(70)+6;
					}while(x%2==1);
					y=random(16)+3;
					for(i=0;i<sz;i++)
						if(snkx[i]==x && snky[i]==y)
							f=1;
				}while(f);
				p=1;
				window(x,y,x+1,y+1);
				textcolor(LIGHTGREEN);
				cprintf("%c",1); //**Carita comestible
				textcolor(WHITE);

				scoree();
				sz++;

				switch(d)
				{
					case RIGHT : snkx[sz-1]+=2;                     //**Caso izquierda
								 snky[sz-1]=snky[sz-2];
								 break;
					case LEFT  : snkx[sz-1]-=2;                     //**Caso derecha
								 snky[sz-1]=snky[sz-2];
								 break;
					case TOP   : snky[sz-1]-=1;                     //**Caso arriba
								 snkx[sz-1]=snkx[sz-2];
								 break;
					case DOWN  : snky[sz-1]+=1;                     //**Caso abajo
								 snkx[sz-1]=snkx[sz-2];
				}
			}
			int sflag=0;
			for(i=0;i<sz-1;i++)
				if(snkx[sz-1]==snkx[i] && snky[sz-1]==snky[i])
				{
					sflag=1;
					break;
				}
			if(snkx[0]<5 || snkx[0]>76 || snky[0]<3 || snky[0]>19)
				sflag=1;
			if(sflag)
			{
				textcolor(LIGHTRED);
				for(i=1;i<sz;i++)
				{
					window(snkx[i],snky[i],snkx[i]+1,snky[i]+1);
					cprintf("þ");
				}
				statute("Perdio",LIGHTRED);
				scoree(0);
				restart=1;
				break;
			}
		}
		char ch=getch();
		switch(tolower(ch))
		{
			case 'x' : return;
			case 'p' :
						statute("Pausado"); //**Cambio de estado
						getch();
						break;
			case 0 : {
						char chh=getch();
						switch(chh)
						{
							case 72 :{
									if(d==LEFT || d== RIGHT)
									d=TOP;
									} break;
							case 80 :{
									if(d==LEFT || d== RIGHT)
									d=DOWN;
									} break;
							case 75 :{
									if(d==TOP || d==DOWN)
									d=LEFT;
									} break;
	       /* tope maximo esquinas  */		case 77 :{
									if(d==TOP || d==DOWN)
									d=RIGHT;
									}
						}
					} break;
		}
	}
	   break;
       }
   break;
   case(2):
   clrscr();
   setfillstyle(SOLID_FILL,BLACK);
 floodfill(540,100,BLACK);
  setcolor(WHITE);
 settextstyle(DEFAULT_FONT,HORIZ_DIR,2);
 outtextxy(170,140,"PROGRAMMLAB 2019");     //**Marca Registrada
  setcolor(WHITE);
 settextstyle(DEFAULT_FONT,HORIZ_DIR,2);
 outtextxy(170,190,"EDISON GUERRERO");
  setcolor(WHITE);
 settextstyle(DEFAULT_FONT,HORIZ_DIR,2);
 outtextxy(170,240,"ADRIAN ESTRADA");
  setcolor(WHITE);
  settextstyle(DEFAULT_FONT,HORIZ_DIR,2);
 outtextxy(170,290,"ALEXIS VILLEGAS");
  getch();
   break;
   case(3):
    int salir=0;
    salir=1;        //** Cierra el programa
   break;
  }
  }while(opcion!=3);    //**Fin do while
  }
    fclose(ficheroU);   //**Cierre fichero
 closegraph;
}






