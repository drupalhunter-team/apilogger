#pragma once
//#include <ddraw.h>


struct FUNCDATA{
	char* pName;
	DWORD Params;
};

void Hook_IDirect3D7(DWORD* p);
void Hook_IDirect3DDevice7(DWORD* p);
void Hook_IDirectDraw7(DWORD* p);
void Hook_IDirectDrawSurface7(DWORD* p);
void Hook_IDirectDrawSurface(DWORD* p);

void Hook_IDirectDraw(DWORD* p);
void Hook_IDirectDraw2(DWORD* p);
void Hook_IDirectDraw4(DWORD* p);
void Hook_IDirectDrawSurface2(DWORD* p);
void Hook_IDirectDrawSurface4(DWORD* p);
void Hook_IDirectDrawSurface3(DWORD* p);
void Hook_IDirect3DDevice(DWORD* p);
void Hook_IDirect3DDevice2(DWORD* p);
void Hook_IDirect3DDevice3(DWORD* p);
void Hook_IDirect3D(DWORD* p);
void Hook_IDirect3D2(DWORD* p);
void Hook_IDirect3D3(DWORD* p);

void Hook_IDirect3DVolume8(DWORD* p);
void Hook_IDirect3DSurface8(DWORD* p);
void Hook_IDirect3DIndexBuffer8(DWORD* p);
void Hook_IDirect3DVertexBuffer8(DWORD* p);
void Hook_IDirect3DCubeTexture8(DWORD* p);
void Hook_IDirect3DVolumeTexture8(DWORD* p);
void Hook_IDirect3DBaseTexture8(DWORD* p);
void Hook_IDirect3DResource8(DWORD* p);
void Hook_IDirect3DSwapChain8(DWORD* p);
void Hook_IDirect3DDevice8(DWORD* p);
void Hook_IDirect3D8(DWORD* p);


void Hook_IDirect3D9(DWORD* p);
DWORD __stdcall before_IDirect3D9_CreateDevice(SPROXYENTRYSTRUCT* pEntry);
void Hook_IDirect3DDevice9(DWORD* p);
