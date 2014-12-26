
#include "stdafx.h"

#include <windows.h>
#include "resource.h"
#include "about.h"

#define MIN_D 2
#define MAX_D 10

DWORD MIN_BALLS = 3;	//3
DWORD MAX_BALLS = 6;	//6

#define MIN_MASS 20
#define MAX_MASS 80//50

#define MIN_VTTL 20
#define MAX_VTTL 70

EFFECT g_EffectType = GRAY;

struct METABALL{
	int		x;
	int		y;
	int		dx;
	int		dy;
	DWORD	mass;
	DWORD	v_ttl;
};

struct rgb{
	BYTE r;
	BYTE g;
	BYTE b;
	BYTE foo;
};

TCHAR sz_prog[]=TEXT("API Logger 1.9");
TCHAR sz_code[]=TEXT("(c)2004-2012 black_ninja");
TCHAR sz_mail[]=TEXT("mail: black_ninja2000@mail.ru");
TCHAR sz_icq[] =TEXT("ICQ:  404558476");

rgb		*pal;
METABALL *balls;
DWORD	balls_cnt;
DWORD	seed;
DWORD	X_SIZE;
DWORD	Y_SIZE;
HFONT	hFont;

HBITMAP	hDIBSec;
HDC		hMemDC;
void *pdata;
HGDIOBJ hOld1;
HGDIOBJ hOld2;

extern HINSTANCE hInstance;

void _srand(){
	_asm{
		xor eax, eax
		rdtsc
		mov seed, eax
	}
}

//out 0..range. range=[0...0x7FFF]
DWORD _rand(DWORD r){
	seed*=0x343FD;
	seed+=0x269EC3;
	return(((seed>>0x10)&0x7FFF)%r);
}

DWORD range_rand(DWORD min, DWORD max){
	if(min==max) return min;
	return (min+_rand(max-min));
}

rgb* gen_palette(){
	BYTE r_=0, g_=0, b_=0;
	DWORD idx=0, i,j;

	rgb *pal=(rgb*)VirtualAlloc(0, 256*sizeof(rgb), MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);

	if( g_EffectType == RED_PLAZMA ){
		for(j=0; j<256; j++){
			pal[j].r=0xFC;
			pal[j].g=0xFC;
			pal[j].b=0xFC;
		}
		for(j=0; j<3; j++){
			for(i=4; i<=0xFC; i+=4){
				if(j==0)		{r_=(BYTE)i;}
				else if(j==1)	{r_=0xFC; g_=(BYTE)i;}
				else if(j==2)	{r_=0xFC; g_=0xFC; b_=(BYTE)i;}
				
				pal[idx].r=r_;
				pal[idx].g=g_;
				pal[idx].b=b_;
				idx++;
			}
		}
	}
	else{
		int f = 0xff;
		int vv = 0;
		for(j=0; j<256; j++){
			pal[j].r = f & 0xff;
			pal[j].g = f & 0xff;
			pal[j].b = f & 0xff;
			f-=5;
			if( f < 0 ){
				f = 0;
			}
		}
	}

/*
	int f = 0xff;
	int vv = 0;
	for(j=0; j<256; j++){
		pal[j].r = f & 0xff;
		pal[j].g = f & 0xff;
		pal[j].b = f & 0xff;
		f-=5;
		if( f < 0 ){
			f=0;
		}

	}
*/
/*
	for(j=0; j<256; j++){
		BYTE f = 250;
		if(j > 50) f = 0;
		pal[j].r = f;
		pal[j].g = f;
		pal[j].b = f;
	}
*/

/*
	for(j=0; j<256; j++){
		pal[j].r=0xFC;
		pal[j].g=0xFC;
		pal[j].b=0xFC;
	}
	for(j=0; j<3; j++){
		for(i=4; i<=0xFC; i+=4){
			if(j==0)		{r_=(BYTE)i;}
			else if(j==1)	{r_=0xFC; g_=(BYTE)i;}
			else if(j==2)	{r_=0xFC; g_=0xFC; b_=(BYTE)i;}
	 
			pal[idx].r=r_;
			pal[idx].g=g_;
			pal[idx].b=b_;
			idx++;
	 	}
	}
*/
	return pal;
}

void init_meta(HWND hWin){
	DWORD foo = range_rand(100, 200);
	if( foo >= 100 && foo < 150){
		g_EffectType = RED_PLAZMA;
	}
	else{
		g_EffectType = GRAY;
	}


	if( g_EffectType == RED_PLAZMA ){
		MIN_BALLS = 80;
		MAX_BALLS = 81;
	}
	else{
		MIN_BALLS = 3;
		MAX_BALLS = 6;
	}

	LOGFONT lf;
	BITMAPINFO bi={0};
	ZeroMemory(&lf, sizeof(LOGFONT));
	lf.lfHeight=16;
	lstrcpy((LPTSTR)&lf.lfFaceName, TEXT("Courier New"));
	hFont=CreateFontIndirect(&lf);
	//Calculate size of window
	RECT rc;
	GetWindowRect(hWin, &rc);
	X_SIZE=rc.right-rc.left;
	Y_SIZE=rc.bottom-rc.top;

	_srand();
	pal = gen_palette();
	balls_cnt=range_rand(MIN_BALLS, MAX_BALLS);
	balls=(METABALL*)VirtualAlloc(0, balls_cnt*sizeof(METABALL), MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);

	for(DWORD k=0; k<balls_cnt; k++){
		balls[k].x=(int)range_rand(0, X_SIZE);
		balls[k].y=(int)range_rand(0, Y_SIZE);
		//balls[k].mass=150000;
		balls[k].mass=10000*range_rand(MIN_MASS, MAX_MASS);

		if(_rand(2)==0){
			balls[k].dx=(int)range_rand(MIN_D, MAX_D);
		}
		else{
			balls[k].dx=-(int)range_rand(MIN_D, MAX_D);
		}

		if(_rand(2)==0){
			balls[k].dy=(int)range_rand(MIN_D, MAX_D);
		}
		else{
			balls[k].dy=-(int)range_rand(MIN_D, MAX_D);
		}

		//TTL
		balls[k].v_ttl=range_rand(MIN_VTTL, MAX_VTTL);
	}
	SetTimer(hWin, 1, 25, 0);

	bi.bmiHeader.biSize=sizeof(BITMAPINFOHEADER);
	bi.bmiHeader.biWidth=X_SIZE;
	bi.bmiHeader.biHeight=Y_SIZE;
	bi.bmiHeader.biPlanes=1;
	bi.bmiHeader.biBitCount=32;
	bi.bmiHeader.biCompression=BI_RGB;

	hMemDC =CreateCompatibleDC(0);
	hDIBSec=CreateDIBSection(hMemDC, &bi, DIB_RGB_COLORS, &pdata,0,0);
	hOld1=SelectObject(hMemDC, hDIBSec);
	hOld2=SelectObject(hMemDC, hFont);
	SetBkMode(hMemDC, TRANSPARENT);
	SetTextColor(hMemDC, RGB(255, 255, 255));
}

void uninit_meta(HWND hDlg){
	VirtualFree(pal, 0, MEM_RELEASE);
	VirtualFree(balls, 0, MEM_RELEASE);
	KillTimer(hDlg, 1);

	SelectObject(hMemDC, hOld2);
	DeleteObject(hFont);

	SelectObject(hMemDC, hOld1);
	DeleteObject(hDIBSec);
	
	DeleteDC(hMemDC);
}

void move_balls(){
	DWORD k;
	for(k=0; k<balls_cnt; k++){
		balls[k].x+=balls[k].dx;
		balls[k].y+=balls[k].dy;
		//x
		if(balls[k].x<0){
			balls[k].x=0;
			balls[k].dx=range_rand(MIN_D, MAX_D);
		}
		if(balls[k].x>X_SIZE){
			balls[k].x=X_SIZE;
			balls[k].dx=-(int)range_rand(MIN_D, MAX_D);
		}

		//y
		if(balls[k].y<0){
			balls[k].y=0;
			balls[k].dy=range_rand(MIN_D, MAX_D);
		}
		if(balls[k].y>Y_SIZE){
			balls[k].y=Y_SIZE;
			balls[k].dy=-(int)range_rand(MIN_D, MAX_D);
		}

		//TTL
		if(balls[k].v_ttl!=0){
			balls[k].v_ttl--;
		}
		else{
			balls[k].v_ttl=range_rand(MIN_VTTL, MAX_VTTL);
			if(_rand(2)==0){
				balls[k].dx=(int)range_rand(MIN_D, MAX_D);
			}
			else{
				balls[k].dx=-(int)range_rand(MIN_D, MAX_D);
			}

			if(_rand(2)==0){
				balls[k].dy=(int)range_rand(MIN_D, MAX_D);
			}
			else{
				balls[k].dy=-(int)range_rand(MIN_D, MAX_D);
			}
		}
	}
}

void process_meta(){
	DWORD xn, yn, k;
	DWORD d;
	DWORD cc, c;
	RGBQUAD *b=(RGBQUAD*)pdata;

	for(yn=0; yn<Y_SIZE; yn++){
		for(xn=0; xn<X_SIZE; xn++){
			c=0;
			for(k=0; k<balls_cnt; k++){
				d=(balls[k].x-xn)*(balls[k].x-xn)+(balls[k].y-yn)*(balls[k].y-yn);
				if(d==0){
					cc=0xFF;			
				}
				else{
					cc=balls[k].mass/d;
					if(cc>=0x100) cc=0xFF;
				}
				c+=cc;
			}
			b[yn*X_SIZE+xn].rgbBlue	=pal[(BYTE)(c/balls_cnt)].b;
			b[yn*X_SIZE+xn].rgbGreen=pal[(BYTE)(c/balls_cnt)].g;
			b[yn*X_SIZE+xn].rgbRed	=pal[(BYTE)(c/balls_cnt)].r;
		}
	}
	move_balls();
}

void render_meta(HWND hWin, HDC hDC){
	SetTextColor( hMemDC, RGB(0xff, 0xff, 0xff) );
	const DWORD z = 10;
	TextOut(hMemDC, 20, Y_SIZE-55-z, sz_prog, lstrlen(sz_prog));
	TextOut(hMemDC, 20, Y_SIZE-38-z, sz_code, lstrlen(sz_code));
	TextOut(hMemDC, 20, Y_SIZE-25-z, sz_mail, lstrlen(sz_mail));
	TextOut(hMemDC, 20, Y_SIZE-12-z, sz_icq,  lstrlen(sz_icq));
	BitBlt(hDC, 0, 0, X_SIZE, Y_SIZE, hMemDC, 0, 0, SRCCOPY);
}

LRESULT CALLBACK AboutDlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam){
	PAINTSTRUCT Ps;
	HDC hDC;

	switch (message)
	{
	case WM_INITDIALOG:
		init_meta(hDlg);//Demo init

		SetFocus(GetDlgItem(hDlg, IDOK));
		return FALSE;
	case WM_COMMAND:
		if((LOWORD(wParam) == IDOK)||(LOWORD(wParam) == IDCANCEL)){
			uninit_meta(hDlg);//Demo uninit
			EndDialog(hDlg, LOWORD(wParam));
			return TRUE;
		}
		break;
	case WM_PAINT:
		hDC=BeginPaint(hDlg, &Ps);
		render_meta(hDlg, hDC);
		EndPaint(hDlg, &Ps);
		break;
	case WM_TIMER:
		process_meta();
		InvalidateRect(hDlg, 0, FALSE);
		break;
	case WM_LBUTTONDOWN:
	case WM_RBUTTONDOWN:
	case WM_MBUTTONDOWN:
		uninit_meta(hDlg);//Demo uninit
		EndDialog(hDlg, LOWORD(wParam));
		return TRUE;
	}
	return FALSE;
}

