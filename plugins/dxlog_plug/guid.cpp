#include "stdafx.h"
#include <windows.h>
#include <stdio.h>
#include "plugin.h"
#include "dxlogger.h"
#include "commondata.h"
#include "guid.h"


MYGUID IID_IDirect3D					={0x3BBA0080,0x2421,0x11CF,0xA3,0x1A,0x00,0xAA,0x00,0xB9,0x33,0x56};
MYGUID IID_IDirect3D2					={0x6aae1ec1,0x662a,0x11d0,0x88,0x9d,0x00,0xaa,0x00,0xbb,0xb7,0x6a};
MYGUID IID_IDirect3D3					={0xbb223240,0xe72b,0x11d0,0xa9,0xb4,0x00,0xaa,0x00,0xc0,0x99,0x3e};
MYGUID IID_IDirect3D7					={0xf5049e77,0x4861,0x11d2,0xa4,0x7,0x0,0xa0,0xc9,0x6,0x29,0xa8};
MYGUID IID_IDirect3DRampDevice			={0xF2086B20,0x259F,0x11CF,0xA3,0x1A,0x00,0xAA,0x00,0xB9,0x33,0x56};
MYGUID IID_IDirect3DRGBDevice			={0xA4665C60,0x2673,0x11CF,0xA3,0x1A,0x00,0xAA,0x00,0xB9,0x33,0x56};
MYGUID IID_IDirect3DHALDevice			={0x84E63dE0,0x46AA,0x11CF,0x81,0x6F,0x00,0x00,0xC0,0x20,0x15,0x6E};
MYGUID IID_IDirect3DMMXDevice			={0x881949a1,0xd6f3,0x11d0,0x89,0xab,0x00,0xa0,0xc9,0x05,0x41,0x29};
MYGUID IID_IDirect3DRefDevice			={0x50936643, 0x13e9, 0x11d1, 0x89, 0xaa, 0x0, 0xa0, 0xc9, 0x5, 0x41, 0x29};
MYGUID IID_IDirect3DNullDevice			={0x8767df22, 0xbacc, 0x11d1, 0x89, 0x69, 0x0, 0xa0, 0xc9, 0x6, 0x29, 0xa8};
MYGUID IID_IDirect3DTnLHalDevice		={0xf5049e78, 0x4861, 0x11d2, 0xa4, 0x7, 0x0, 0xa0, 0xc9, 0x6, 0x29, 0xa8};
MYGUID IID_IDirect3DDevice				={0x64108800,0x957d,0X11d0,0x89,0xab,0x00,0xa0,0xc9,0x05,0x41,0x29 };
MYGUID IID_IDirect3DDevice2				={0x93281501, 0x8cf8, 0x11d0, 0x89, 0xab, 0x0, 0xa0, 0xc9, 0x5, 0x41, 0x29};
MYGUID IID_IDirect3DDevice3				={0xb0ab3b60, 0x33d7, 0x11d1, 0xa9, 0x81, 0x0, 0xc0, 0x4f, 0xd7, 0xb1, 0x74};
MYGUID IID_IDirect3DDevice7				={0xf5049e79, 0x4861, 0x11d2, 0xa4, 0x7, 0x0, 0xa0, 0xc9, 0x6, 0x29, 0xa8};
MYGUID IID_IDirect3DTexture				={0x2CDCD9E0,0x25A0,0x11CF,0xA3,0x1A,0x00,0xAA,0x00,0xB9,0x33,0x56 };
MYGUID IID_IDirect3DTexture2			={0x93281502, 0x8cf8, 0x11d0, 0x89, 0xab, 0x0, 0xa0, 0xc9, 0x5, 0x41, 0x29};
MYGUID IID_IDirect3DLight				={0x4417C142,0x33AD,0x11CF,0x81,0x6F,0x00,0x00,0xC0,0x20,0x15,0x6E };
MYGUID IID_IDirect3DMaterial			={0x4417C144,0x33AD,0x11CF,0x81,0x6F,0x00,0x00,0xC0,0x20,0x15,0x6E };
MYGUID IID_IDirect3DMaterial2			={0x93281503, 0x8cf8, 0x11d0, 0x89, 0xab, 0x0, 0xa0, 0xc9, 0x5, 0x41, 0x29 };
MYGUID IID_IDirect3DMaterial3			={0xca9c46f4, 0xd3c5, 0x11d1, 0xb7, 0x5a, 0x0, 0x60, 0x8, 0x52, 0xb3, 0x12};
MYGUID IID_IDirect3DExecuteBuffer		={0x4417C145,0x33AD,0x11CF,0x81,0x6F,0x00,0x00,0xC0,0x20,0x15,0x6E };
MYGUID IID_IDirect3DViewport			={0x4417C146,0x33AD,0x11CF,0x81,0x6F,0x00,0x00,0xC0,0x20,0x15,0x6E };
MYGUID IID_IDirect3DViewport2			={0x93281500, 0x8cf8, 0x11d0, 0x89, 0xab, 0x0, 0xa0, 0xc9, 0x5, 0x41, 0x29};
MYGUID IID_IDirect3DViewport3			={0xb0ab3b61, 0x33d7, 0x11d1, 0xa9, 0x81, 0x0, 0xc0, 0x4f, 0xd7, 0xb1, 0x74};
MYGUID IID_IDirect3DVertexBuffer		={0x7a503555, 0x4a83, 0x11d1, 0xa5, 0xdb, 0x0, 0xa0, 0xc9, 0x3, 0x67, 0xf8};
MYGUID IID_IDirect3DVertexBuffer7		={0xf5049e7d, 0x4861, 0x11d2, 0xa4, 0x7, 0x0, 0xa0, 0xc9, 0x6, 0x29, 0xa8};

MYGUID IID_IDirectDraw					={0x6C14DB80,0xA733,0x11CE,0xA5,0x21,0x00,0x20,0xAF,0x0B,0xE5,0x60 };
MYGUID IID_IDirectDraw2                 ={0xB3A6F3E0,0x2B43,0x11CF,0xA2,0xDE,0x00,0xAA,0x00,0xB9,0x33,0x56 };
MYGUID IID_IDirectDraw4                 ={0x9c59509a,0x39bd,0x11d1,0x8c,0x4a,0x00,0xc0,0x4f,0xd9,0x30,0xc5 };
MYGUID IID_IDirectDraw7                 ={0x15e65ec0,0x3b9c,0x11d2,0xb9,0x2f,0x00,0x60,0x97,0x97,0xea,0x5b };
MYGUID IID_IDirectDrawSurface           ={0x6C14DB81,0xA733,0x11CE,0xA5,0x21,0x00,0x20,0xAF,0x0B,0xE5,0x60 };
MYGUID IID_IDirectDrawSurface2			={0x57805885,0x6eec,0x11cf,0x94,0x41,0xa8,0x23,0x03,0xc1,0x0e,0x27 };
MYGUID IID_IDirectDrawSurface3			={0xDA044E00,0x69B2,0x11D0,0xA1,0xD5,0x00,0xAA,0x00,0xB8,0xDF,0xBB };
MYGUID IID_IDirectDrawSurface4			={0x0B2B8630,0xAD35,0x11D0,0x8E,0xA6,0x00,0x60,0x97,0x97,0xEA,0x5B };
MYGUID IID_IDirectDrawSurface7			={0x06675a80,0x3b9b,0x11d2,0xb9,0x2f,0x00,0x60,0x97,0x97,0xea,0x5b };
MYGUID IID_IDirectDrawPalette			={0x6C14DB84,0xA733,0x11CE,0xA5,0x21,0x00,0x20,0xAF,0x0B,0xE5,0x60 };
MYGUID IID_IDirectDrawClipper			={0x6C14DB85,0xA733,0x11CE,0xA5,0x21,0x00,0x20,0xAF,0x0B,0xE5,0x60 };
MYGUID IID_IDirectDrawColorControl		={0x4B9F0EE0,0x0D7E,0x11D0,0x9B,0x06,0x00,0xA0,0xC9,0x03,0xA3,0xB8 };
MYGUID IID_IDirectDrawGammaControl		={0x69C11C3E,0xB46B,0x11D1,0xAD,0x7A,0x00,0xC0,0x4F,0xC2,0x9B,0x4E };


MYGUID  IID_IDirectInputA				={0x89521360,0xAA8A,0x11CF,0xBF,0xC7,0x44,0x45,0x53,0x54,0x00,0x00};
MYGUID  IID_IDirectInputW				={0x89521361,0xAA8A,0x11CF,0xBF,0xC7,0x44,0x45,0x53,0x54,0x00,0x00};
MYGUID  IID_IDirectInput2A				={0x5944E662,0xAA8A,0x11CF,0xBF,0xC7,0x44,0x45,0x53,0x54,0x00,0x00};
MYGUID  IID_IDirectInput2W				={0x5944E663,0xAA8A,0x11CF,0xBF,0xC7,0x44,0x45,0x53,0x54,0x00,0x00};
MYGUID  IID_IDirectInput7A				={0x9A4CB684,0x236D,0x11D3,0x8E,0x9D,0x00,0xC0,0x4F,0x68,0x44,0xAE};
MYGUID  IID_IDirectInput7W				={0x9A4CB685,0x236D,0x11D3,0x8E,0x9D,0x00,0xC0,0x4F,0x68,0x44,0xAE};
MYGUID  IID_IDirectInput8A				={0xBF798030,0x483A,0x4DA2,0xAA,0x99,0x5D,0x64,0xED,0x36,0x97,0x00};
MYGUID  IID_IDirectInput8W				={0xBF798031,0x483A,0x4DA2,0xAA,0x99,0x5D,0x64,0xED,0x36,0x97,0x00};
MYGUID  IID_IDirectInputDeviceA			={0x5944E680,0xC92E,0x11CF,0xBF,0xC7,0x44,0x45,0x53,0x54,0x00,0x00};
MYGUID  IID_IDirectInputDeviceW			={0x5944E681,0xC92E,0x11CF,0xBF,0xC7,0x44,0x45,0x53,0x54,0x00,0x00};
MYGUID  IID_IDirectInputDevice2A		={0x5944E682,0xC92E,0x11CF,0xBF,0xC7,0x44,0x45,0x53,0x54,0x00,0x00};
MYGUID  IID_IDirectInputDevice2W		={0x5944E683,0xC92E,0x11CF,0xBF,0xC7,0x44,0x45,0x53,0x54,0x00,0x00};
MYGUID  IID_IDirectInputDevice7A		={0x57D7C6BC,0x2356,0x11D3,0x8E,0x9D,0x00,0xC0,0x4F,0x68,0x44,0xAE};
MYGUID  IID_IDirectInputDevice7W		={0x57D7C6BD,0x2356,0x11D3,0x8E,0x9D,0x00,0xC0,0x4F,0x68,0x44,0xAE};
MYGUID  IID_IDirectInputDevice8A		={0x54D41080,0xDC15,0x4833,0xA4,0x1B,0x74,0x8F,0x73,0xA3,0x81,0x79};
MYGUID  IID_IDirectInputDevice8W		={0x54D41081,0xDC15,0x4833,0xA4,0x1B,0x74,0x8F,0x73,0xA3,0x81,0x79};
MYGUID  IID_IDirectInputEffect			={0xE7E1F7C0,0x88D2,0x11D0,0x9A,0xD0,0x00,0xA0,0xC9,0xA0,0x6E,0x35};
MYGUID  GUID_XAxis						={0xA36D02E0,0xC9F3,0x11CF,0xBF,0xC7,0x44,0x45,0x53,0x54,0x00,0x00};
MYGUID  GUID_YAxis						={0xA36D02E1,0xC9F3,0x11CF,0xBF,0xC7,0x44,0x45,0x53,0x54,0x00,0x00};
MYGUID  GUID_ZAxis						={0xA36D02E2,0xC9F3,0x11CF,0xBF,0xC7,0x44,0x45,0x53,0x54,0x00,0x00};
MYGUID  GUID_RxAxis						={0xA36D02F4,0xC9F3,0x11CF,0xBF,0xC7,0x44,0x45,0x53,0x54,0x00,0x00};
MYGUID  GUID_RyAxis						={0xA36D02F5,0xC9F3,0x11CF,0xBF,0xC7,0x44,0x45,0x53,0x54,0x00,0x00};
MYGUID  GUID_RzAxis						={0xA36D02E3,0xC9F3,0x11CF,0xBF,0xC7,0x44,0x45,0x53,0x54,0x00,0x00};
MYGUID  GUID_Slider						={0xA36D02E4,0xC9F3,0x11CF,0xBF,0xC7,0x44,0x45,0x53,0x54,0x00,0x00};
MYGUID  GUID_Button						={0xA36D02F0,0xC9F3,0x11CF,0xBF,0xC7,0x44,0x45,0x53,0x54,0x00,0x00};
MYGUID  GUID_Key						={0x55728220,0xD33C,0x11CF,0xBF,0xC7,0x44,0x45,0x53,0x54,0x00,0x00};
MYGUID  GUID_POV						={0xA36D02F2,0xC9F3,0x11CF,0xBF,0xC7,0x44,0x45,0x53,0x54,0x00,0x00};
MYGUID  GUID_Unknown					={0xA36D02F3,0xC9F3,0x11CF,0xBF,0xC7,0x44,0x45,0x53,0x54,0x00,0x00};
MYGUID  GUID_SysMouse					={0x6F1D2B60,0xD5A0,0x11CF,0xBF,0xC7,0x44,0x45,0x53,0x54,0x00,0x00};
MYGUID  GUID_SysKeyboard				={0x6F1D2B61,0xD5A0,0x11CF,0xBF,0xC7,0x44,0x45,0x53,0x54,0x00,0x00};
MYGUID  GUID_Joystick					={0x6F1D2B70,0xD5A0,0x11CF,0xBF,0xC7,0x44,0x45,0x53,0x54,0x00,0x00};
MYGUID  GUID_SysMouseEm					={0x6F1D2B80,0xD5A0,0x11CF,0xBF,0xC7,0x44,0x45,0x53,0x54,0x00,0x00};
MYGUID  GUID_SysMouseEm2				={0x6F1D2B81,0xD5A0,0x11CF,0xBF,0xC7,0x44,0x45,0x53,0x54,0x00,0x00};
MYGUID  GUID_SysKeyboardEm				={0x6F1D2B82,0xD5A0,0x11CF,0xBF,0xC7,0x44,0x45,0x53,0x54,0x00,0x00};
MYGUID  GUID_SysKeyboardEm2				={0x6F1D2B83,0xD5A0,0x11CF,0xBF,0xC7,0x44,0x45,0x53,0x54,0x00,0x00};
MYGUID  GUID_ConstantForce				={0x13541C20,0x8E33,0x11D0,0x9A,0xD0,0x00,0xA0,0xC9,0xA0,0x6E,0x35};
MYGUID  GUID_RampForce					={0x13541C21,0x8E33,0x11D0,0x9A,0xD0,0x00,0xA0,0xC9,0xA0,0x6E,0x35};
MYGUID  GUID_Square						={0x13541C22,0x8E33,0x11D0,0x9A,0xD0,0x00,0xA0,0xC9,0xA0,0x6E,0x35};
MYGUID  GUID_Sine						={0x13541C23,0x8E33,0x11D0,0x9A,0xD0,0x00,0xA0,0xC9,0xA0,0x6E,0x35};
MYGUID  GUID_Triangle					={0x13541C24,0x8E33,0x11D0,0x9A,0xD0,0x00,0xA0,0xC9,0xA0,0x6E,0x35};
MYGUID  GUID_SawtoothUp					={0x13541C25,0x8E33,0x11D0,0x9A,0xD0,0x00,0xA0,0xC9,0xA0,0x6E,0x35};
MYGUID  GUID_SawtoothDown				={0x13541C26,0x8E33,0x11D0,0x9A,0xD0,0x00,0xA0,0xC9,0xA0,0x6E,0x35};
MYGUID  GUID_Spring						={0x13541C27,0x8E33,0x11D0,0x9A,0xD0,0x00,0xA0,0xC9,0xA0,0x6E,0x35};
MYGUID  GUID_Damper						={0x13541C28,0x8E33,0x11D0,0x9A,0xD0,0x00,0xA0,0xC9,0xA0,0x6E,0x35};
MYGUID  GUID_Inertia					={0x13541C29,0x8E33,0x11D0,0x9A,0xD0,0x00,0xA0,0xC9,0xA0,0x6E,0x35};
MYGUID  GUID_Friction					={0x13541C2A,0x8E33,0x11D0,0x9A,0xD0,0x00,0xA0,0xC9,0xA0,0x6E,0x35};
MYGUID  GUID_CustomForce				={0x13541C2B,0x8E33,0x11D0,0x9A,0xD0,0x00,0xA0,0xC9,0xA0,0x6E,0x35};

MYGUID  IID_IDirect3D8					={0x1dd9e8da, 0x1c77, 0x4d40, 0xb0, 0xcf, 0x98, 0xfe, 0xfd, 0xff, 0x95, 0x12};
MYGUID  IID_IDirect3DDevice8			={0x7385e5df, 0x8fe8, 0x41d5, 0x86, 0xb6, 0xd7, 0xb4, 0x85, 0x47, 0xb6, 0xcf};
MYGUID  IID_IDirect3DResource8			={0x1b36bb7b, 0x9b7, 0x410a, 0xb4, 0x45, 0x7d, 0x14, 0x30, 0xd7, 0xb3, 0x3f};
MYGUID  IID_IDirect3DBaseTexture8		={0xb4211cfa, 0x51b9, 0x4a9f, 0xab, 0x78, 0xdb, 0x99, 0xb2, 0xbb, 0x67, 0x8e};
MYGUID  IID_IDirect3DTexture8			={0xe4cdd575, 0x2866, 0x4f01, 0xb1, 0x2e, 0x7e, 0xec, 0xe1, 0xec, 0x93, 0x58};
MYGUID  IID_IDirect3DCubeTexture8		={0x3ee5b968, 0x2aca, 0x4c34, 0x8b, 0xb5, 0x7e, 0x0c, 0x3d, 0x19, 0xb7, 0x50};
MYGUID  IID_IDirect3DVolumeTexture8		={0x4b8aaafa, 0x140f, 0x42ba, 0x91, 0x31, 0x59, 0x7e, 0xaf, 0xaa, 0x2e, 0xad};
MYGUID  IID_IDirect3DVertexBuffer8		={0x8aeeeac7, 0x05f9, 0x44d4, 0xb5, 0x91, 0x00, 0x0b, 0x0d, 0xf1, 0xcb, 0x95};
MYGUID  IID_IDirect3DIndexBuffer8		={0x0e689c9a, 0x053d, 0x44a0, 0x9d, 0x92, 0xdb, 0x0e, 0x3d, 0x75, 0x0f, 0x86};
MYGUID  IID_IDirect3DSurface8			={0xb96eebca, 0xb326, 0x4ea5, 0x88, 0x2f, 0x2f, 0xf5, 0xba, 0xe0, 0x21, 0xdd};
MYGUID  IID_IDirect3DVolume8			={0xbd7349f5, 0x14f1, 0x42e4, 0x9c, 0x79, 0x97, 0x23, 0x80, 0xdb, 0x40, 0xc0};
MYGUID  IID_IDirect3DSwapChain8			={0x928c088b, 0x76b9, 0x4c6b, 0xa5, 0x36, 0xa5, 0x90, 0x85, 0x38, 0x76, 0xcd};

MYGUID  IID_IDirect3D9					={0x81bdcbca, 0x64d4, 0x426d, 0xae, 0x8d, 0xad, 0x1, 0x47, 0xf4, 0x27, 0x5c};
MYGUID  IID_IDirect3DDevice9			={0xd0223b96, 0xbf7a, 0x43fd, 0x92, 0xbd, 0xa4, 0x3b, 0xd, 0x82, 0xb9, 0xeb};
MYGUID  IID_IDirect3DResource9			={0x5eec05d, 0x8f7d, 0x4362, 0xb9, 0x99, 0xd1, 0xba, 0xf3, 0x57, 0xc7, 0x4};
MYGUID  IID_IDirect3DBaseTexture9		={0x580ca87e, 0x1d3c, 0x4d54, 0x99, 0x1d, 0xb7, 0xd3, 0xe3, 0xc2, 0x98, 0xce};
MYGUID  IID_IDirect3DTexture9			={0x85c31227, 0x3de5, 0x4f00, 0x9b, 0x3a, 0xf1, 0x1a, 0xc3, 0x8c, 0x18, 0xb5};
MYGUID  IID_IDirect3DCubeTexture9		={0xfff32f81, 0xd953, 0x473a, 0x92, 0x23, 0x93, 0xd6, 0x52, 0xab, 0xa9, 0x3f};
MYGUID  IID_IDirect3DVolumeTexture9		={0x2518526c, 0xe789, 0x4111, 0xa7, 0xb9, 0x47, 0xef, 0x32, 0x8d, 0x13, 0xe6};
MYGUID  IID_IDirect3DVertexBuffer9		={0xb64bb1b5, 0xfd70, 0x4df6, 0xbf, 0x91, 0x19, 0xd0, 0xa1, 0x24, 0x55, 0xe3};
MYGUID  IID_IDirect3DIndexBuffer9		={0x7c9dd65e, 0xd3f7, 0x4529, 0xac, 0xee, 0x78, 0x58, 0x30, 0xac, 0xde, 0x35};
MYGUID  IID_IDirect3DSurface9			={0xcfbaf3a, 0x9ff6, 0x429a, 0x99, 0xb3, 0xa2, 0x79, 0x6a, 0xf8, 0xb8, 0x9b};
MYGUID  IID_IDirect3DVolume9			={0x24f416e6, 0x1f67, 0x4aa7, 0xb8, 0x8e, 0xd3, 0x3f, 0x6f, 0x31, 0x28, 0xa1};
MYGUID  IID_IDirect3DSwapChain9			={0x794950f2, 0xadfc, 0x458a, 0x90, 0x5e, 0x10, 0xa1, 0xb, 0xb, 0x50, 0x3b};
MYGUID  IID_IDirect3DVertexDeclaration9 ={0xdd13c59c, 0x36fa, 0x4098, 0xa8, 0xfb, 0xc7, 0xed, 0x39, 0xdc, 0x85, 0x46};
MYGUID  IID_IDirect3DVertexShader9		={0xefc5557e, 0x6265, 0x4613, 0x8a, 0x94, 0x43, 0x85, 0x78, 0x89, 0xeb, 0x36};
MYGUID  IID_IDirect3DPixelShader9		={0x6d3bdbdc, 0x5b02, 0x4415, 0xb8, 0x52, 0xce, 0x5e, 0x8b, 0xcc, 0xb2, 0x89};
MYGUID  IID_IDirect3DStateBlock9		={0xb07c4fe5, 0x310d, 0x4ba8, 0xa2, 0x3c, 0x4f, 0xf, 0x20, 0x6f, 0x21, 0x8b};
MYGUID  IID_IDirect3DQuery9				={0xd9771460, 0xa695, 0x4f26, 0xbb, 0xd3, 0x27, 0xb8, 0x40, 0xb5, 0x41, 0xcc};
MYGUID  IID_HelperName					={0xe4a36723, 0xfdfe, 0x4b22, 0xb1, 0x46, 0x3c, 0x4, 0xc0, 0x7f, 0x4c, 0xc8};
MYGUID  IID_IDirect3D9Ex				={0x02177241, 0x69FC, 0x400C, 0x8F, 0xF1, 0x93, 0xA4, 0x4D, 0xF6, 0x86, 0x1D};
MYGUID  IID_IDirect3DDevice9Ex			={0xb18b10ce, 0x2649, 0x405a, 0x87, 0xf, 0x95, 0xf7, 0x77, 0xd4, 0x31, 0x3a};
MYGUID  IID_IDirect3DSwapChain9Ex		={0x91886caf, 0x1c3d, 0x4d2e, 0xa0, 0xab, 0x3e, 0x4c, 0x7d, 0x8d, 0x33, 0x3};
MYGUID  IID_IDirect3D9ExOverlayExtension={0x187aeb13, 0xaaf5, 0x4c59, 0x87, 0x6d, 0xe0, 0x59, 0x8, 0x8c, 0xd, 0xf8};
MYGUID  IID_IDirect3DDevice9Video		={0x26dc4561, 0xa1ee, 0x4ae7, 0x96, 0xda, 0x11, 0x8a, 0x36, 0xc0, 0xec, 0x95};
MYGUID  IID_IDirect3DAuthenticatedChannel9={0xff24beee, 0xda21, 0x4beb, 0x98, 0xb5, 0xd2, 0xf8, 0x99, 0xf9, 0x8a, 0xf9};
MYGUID  IID_IDirect3DCryptoSession9={0xfa0ab799, 0x7a9c, 0x48ca, 0x8c, 0x5b, 0x23, 0x7e, 0x71, 0xa5, 0x44, 0x34};



DWORD GetMethodAddr(DWORD **pvtbl, DWORD idx){
	if(pvtbl==0)
		return 0;

	if(*pvtbl==0)
		return 0;

	DWORD *vtbl=*pvtbl;
	return vtbl[idx];
}

DWORD IsEqIID(const void* p0, const void* p1){
	return !memcmp(p0, p1, sizeof(GUID));
}

void dump_IID(PBYTE pIIDd){
	DWORD	D1;
	WORD	D2;
	WORD	D3;
	BYTE	D4, D5, D6, D7, D8, D9, D10, D11;

	D1=*(PDWORD)(pIIDd);
	D2=*(PWORD)(pIIDd+4);
	D3=*(PWORD)(pIIDd+6);

	D4=*(PBYTE)(pIIDd+8);
	D5=*(PBYTE)(pIIDd+9);
	D6=*(PBYTE)(pIIDd+10);
	D7=*(PBYTE)(pIIDd+11);

	D8=*(PBYTE)(pIIDd+12);
	D9=*(PBYTE)(pIIDd+13);
	D10=*(PBYTE)(pIIDd+14);
	D11=*(PBYTE)(pIIDd+15);

	Logger("-> IID Dump: %08X, %04X, %04X, %02X, %02X, %02X, %02X, %02X, %02X, %02X, %02X\r\n", D1, D2, D3, D4, D5, D6, D7,  D8, D9, D10, D11);

}

void HookByIID(LPCVOID pIID, LPCVOID pObj){
	if		(IsEqIID(&IID_IDirectDraw,				(const void*)pIID)){Logger("-> IID_IDirectDraw\r\n");  Hook_IDirectDraw ((DWORD*)pObj);}
	else if	(IsEqIID(&IID_IDirectDraw2,				(const void*)pIID)){Logger("-> IID_IDirectDraw2\r\n"); Hook_IDirectDraw2((DWORD*)pObj);}
	else if	(IsEqIID(&IID_IDirectDraw4,				(const void*)pIID)){Logger("-> IID_IDirectDraw4\r\n"); Hook_IDirectDraw4((DWORD*)pObj);}
	else if	(IsEqIID(&IID_IDirectDraw7,				(const void*)pIID)){Logger("-> IID_IDirectDraw7\r\n"); Hook_IDirectDraw7((DWORD*)pObj);}
	else if	(IsEqIID(&IID_IDirectDrawSurface ,		(const void*)pIID)){Logger("-> IID_IDirectDrawSurface\r\n");  Hook_IDirectDrawSurface ((DWORD*)pObj);}
	else if	(IsEqIID(&IID_IDirectDrawSurface2,		(const void*)pIID)){Logger("-> IID_IDirectDrawSurface2\r\n"); Hook_IDirectDrawSurface2((DWORD*)pObj);}
	else if	(IsEqIID(&IID_IDirectDrawSurface3,		(const void*)pIID)){Logger("-> IID_IDirectDrawSurface3\r\n"); Hook_IDirectDrawSurface3((DWORD*)pObj);}
	else if	(IsEqIID(&IID_IDirectDrawSurface4,		(const void*)pIID)){Logger("-> IID_IDirectDrawSurface4\r\n"); Hook_IDirectDrawSurface4((DWORD*)pObj);}
	else if	(IsEqIID(&IID_IDirectDrawSurface7,		(const void*)pIID)){Logger("-> IID_IDirectDrawSurface7\r\n"); Hook_IDirectDrawSurface7((DWORD*)pObj);}
	else if	(IsEqIID(&IID_IDirectDrawPalette,		(const void*)pIID)){Logger("-> IID_IDirectDrawPalette\r\n");}
	else if	(IsEqIID(&IID_IDirectDrawClipper,		(const void*)pIID)){Logger("-> IID_IDirectDrawClipper\r\n");}
	else if	(IsEqIID(&IID_IDirectDrawColorControl,	(const void*)pIID)){Logger("-> IID_IDirectDrawColorControl\r\n");}
	else if	(IsEqIID(&IID_IDirectDrawGammaControl,	(const void*)pIID)){Logger("-> IID_IDirectDrawGammaControl\r\n");}
	else if	(IsEqIID(&IID_IDirect3DDevice,			(const void*)pIID)){Logger("-> IID_IDirect3DDevice\r\n");  Hook_IDirect3DDevice ((DWORD*)pObj);}
	else if	(IsEqIID(&IID_IDirect3DDevice2,			(const void*)pIID)){Logger("-> IID_IDirect3DDevice2\r\n"); Hook_IDirect3DDevice2((DWORD*)pObj);}
	else if	(IsEqIID(&IID_IDirect3DDevice3,			(const void*)pIID)){Logger("-> IID_IDirect3DDevice3\r\n"); Hook_IDirect3DDevice3((DWORD*)pObj);}
	else if	(IsEqIID(&IID_IDirect3DDevice7,			(const void*)pIID)){Logger("-> IID_IDirect3DDevice7\r\n"); Hook_IDirect3DDevice7((DWORD*)pObj);}
	else if	(IsEqIID(&IID_IDirect3DTexture,			(const void*)pIID)){Logger("-> IID_IDirect3DTexture\r\n");}
	else if	(IsEqIID(&IID_IDirect3DTexture2,		(const void*)pIID)){Logger("-> IID_IDirect3DTexture2\r\n");}
	else if	(IsEqIID(&IID_IDirect3DLight,			(const void*)pIID)){Logger("-> IID_IDirect3DLight\r\n");}
	else if	(IsEqIID(&IID_IDirect3DMaterial,		(const void*)pIID)){Logger("-> IID_IDirect3DMaterial\r\n");}
	else if	(IsEqIID(&IID_IDirect3DMaterial2,		(const void*)pIID)){Logger("-> IID_IDirect3DMaterial2\r\n");}
	else if	(IsEqIID(&IID_IDirect3DMaterial3,		(const void*)pIID)){Logger("-> IID_IDirect3DMaterial3\r\n");}
	else if	(IsEqIID(&IID_IDirect3DExecuteBuffer,	(const void*)pIID)){Logger("-> IID_IDirect3DExecuteBuffer\r\n");}
	else if	(IsEqIID(&IID_IDirect3DViewport,		(const void*)pIID)){Logger("-> IID_IDirect3DViewport\r\n");}
	else if	(IsEqIID(&IID_IDirect3DViewport2,		(const void*)pIID)){Logger("-> IID_IDirect3DViewport2\r\n");}
	else if	(IsEqIID(&IID_IDirect3DViewport3,		(const void*)pIID)){Logger("-> IID_IDirect3DViewport3\r\n");}
	else if	(IsEqIID(&IID_IDirect3DVertexBuffer,	(const void*)pIID)){Logger("-> IID_IDirect3DVertexBuffer\r\n");}
	else if	(IsEqIID(&IID_IDirect3DVertexBuffer7,	(const void*)pIID)){Logger("-> IID_IDirect3DVertexBuffer7\r\n");}
	else if	(IsEqIID(&IID_IDirect3D,				(const void*)pIID)){Logger("-> IID_IDirect3D\r\n");  Hook_IDirect3D ((DWORD*)pObj);}
	else if	(IsEqIID(&IID_IDirect3D2,				(const void*)pIID)){Logger("-> IID_IDirect3D2\r\n"); Hook_IDirect3D2((DWORD*)pObj);}
	else if	(IsEqIID(&IID_IDirect3D3,				(const void*)pIID)){Logger("-> IID_IDirect3D3\r\n"); Hook_IDirect3D3((DWORD*)pObj);}
	else if	(IsEqIID(&IID_IDirect3D7,				(const void*)pIID)){Logger("-> IID_IDirect3D7\r\n"); Hook_IDirect3D7((DWORD*)pObj);}
	else if	(IsEqIID(&IID_IDirect3DRampDevice,		(const void*)pIID)){Logger("-> IID_IDirect3DRampDevice\r\n");}
	else if	(IsEqIID(&IID_IDirect3DRGBDevice,		(const void*)pIID)){Logger("-> IID_IDirect3DRGBDevice\r\n");}
	else if	(IsEqIID(&IID_IDirect3DHALDevice,		(const void*)pIID)){Logger("-> IID_IDirect3DHALDevice\r\n"); Hook_IDirect3DDevice ((DWORD*)pObj);}
	else if	(IsEqIID(&IID_IDirect3DMMXDevice,		(const void*)pIID)){Logger("-> IID_IDirect3DMMXDevice\r\n");}
	else if	(IsEqIID(&IID_IDirect3DRefDevice,		(const void*)pIID)){Logger("-> IID_IDirect3DRefDevice\r\n");}
	else if	(IsEqIID(&IID_IDirect3DNullDevice,		(const void*)pIID)){Logger("-> IID_IDirect3DNullDevice\r\n");}
	else if	(IsEqIID(&IID_IDirect3DTnLHalDevice,	(const void*)pIID)){Logger("-> IID_IDirect3DTnLHalDevice\r\n");}

	//dinput.dll
	else if	(IsEqIID(&IID_IDirectInputA	,			(const void*)pIID)){Logger("-> IID_IDirectInputA\r\n");}
	else if	(IsEqIID(&IID_IDirectInputW,			(const void*)pIID)){Logger("-> IID_IDirectInputW\r\n");}
	else if	(IsEqIID(&IID_IDirectInput2A,			(const void*)pIID)){Logger("-> IID_IDirectInput2A\r\n");}
	else if	(IsEqIID(&IID_IDirectInput2W,			(const void*)pIID)){Logger("-> IID_IDirectInput2W\r\n");}
	else if	(IsEqIID(&IID_IDirectInput7A,			(const void*)pIID)){Logger("-> IID_IDirectInput7A\r\n");}
	else if	(IsEqIID(&IID_IDirectInput7W,			(const void*)pIID)){Logger("-> IID_IDirectInput7W\r\n");}
	else if	(IsEqIID(&IID_IDirectInput8A,			(const void*)pIID)){Logger("-> IID_IDirectInput8A\r\n");}
	else if	(IsEqIID(&IID_IDirectInput8W,			(const void*)pIID)){Logger("-> IID_IDirectInput8W\r\n");}
	else if	(IsEqIID(&IID_IDirectInputDeviceA,		(const void*)pIID)){Logger("-> IID_IDirectInputDeviceA\r\n");}
	else if	(IsEqIID(&IID_IDirectInputDeviceW,		(const void*)pIID)){Logger("-> IID_IDirectInputDeviceW\r\n");}
	else if	(IsEqIID(&IID_IDirectInputDevice2A,		(const void*)pIID)){Logger("-> IID_IDirectInputDevice2A\r\n");}
	else if	(IsEqIID(&IID_IDirectInputDevice2W,		(const void*)pIID)){Logger("-> IID_IDirectInputDevice2W\r\n");}
	else if	(IsEqIID(&IID_IDirectInputDevice7A,		(const void*)pIID)){Logger("-> IID_IDirectInputDevice7A\r\n");}
	else if	(IsEqIID(&IID_IDirectInputDevice7W,		(const void*)pIID)){Logger("-> IID_IDirectInputDevice7W\r\n");}
	else if	(IsEqIID(&IID_IDirectInputDevice8A,		(const void*)pIID)){Logger("-> IID_IDirectInputDevice8A\r\n");}
	else if	(IsEqIID(&IID_IDirectInputDevice8W,		(const void*)pIID)){Logger("-> IID_IDirectInputDevice8W\r\n");}
	else if	(IsEqIID(&IID_IDirectInputEffect,		(const void*)pIID)){Logger("-> IID_IDirectInputEffect\r\n");}

	else if	(IsEqIID(&GUID_XAxis,					(const void*)pIID)){Logger("-> GUID_XAxis\r\n");}
	else if	(IsEqIID(&GUID_YAxis,					(const void*)pIID)){Logger("-> GUID_YAxis\r\n");}
	else if	(IsEqIID(&GUID_ZAxis,					(const void*)pIID)){Logger("-> GUID_ZAxis\r\n");}
	else if	(IsEqIID(&GUID_RxAxis,					(const void*)pIID)){Logger("-> GUID_RxAxis\r\n");}
	else if	(IsEqIID(&GUID_RyAxis,					(const void*)pIID)){Logger("-> GUID_RyAxis\r\n");}
	else if	(IsEqIID(&GUID_RzAxis,					(const void*)pIID)){Logger("-> GUID_RzAxis\r\n");}
	else if	(IsEqIID(&GUID_Slider,					(const void*)pIID)){Logger("-> GUID_Slider\r\n");}
	else if	(IsEqIID(&GUID_Button,					(const void*)pIID)){Logger("-> GUID_Button\r\n");}
	else if	(IsEqIID(&GUID_Key,						(const void*)pIID)){Logger("-> GUID_Key\r\n");}
	else if	(IsEqIID(&GUID_POV,						(const void*)pIID)){Logger("-> GUID_POV\r\n");}
	else if	(IsEqIID(&GUID_Unknown,					(const void*)pIID)){Logger("-> GUID_Unknown\r\n");}
	else if	(IsEqIID(&GUID_SysMouse,				(const void*)pIID)){Logger("-> GUID_SysMouse\r\n");}
	else if	(IsEqIID(&GUID_SysKeyboard,				(const void*)pIID)){Logger("-> GUID_SysKeyboard\r\n");}
	else if	(IsEqIID(&GUID_Joystick,				(const void*)pIID)){Logger("-> GUID_Joystick\r\n");}
	else if	(IsEqIID(&GUID_SysMouseEm,				(const void*)pIID)){Logger("-> GUID_SysMouseEm\r\n");}
	else if	(IsEqIID(&GUID_SysMouseEm2,				(const void*)pIID)){Logger("-> GUID_SysMouseEm2\r\n");}
	else if	(IsEqIID(&GUID_SysKeyboardEm,			(const void*)pIID)){Logger("-> GUID_SysKeyboardEm\r\n");}
	else if	(IsEqIID(&GUID_SysKeyboardEm2,			(const void*)pIID)){Logger("-> GUID_SysKeyboardEm2\r\n");}
	else if	(IsEqIID(&GUID_ConstantForce,			(const void*)pIID)){Logger("-> GUID_ConstantForce\r\n");}
	else if	(IsEqIID(&GUID_RampForce,				(const void*)pIID)){Logger("-> GUID_RampForce\r\n");}
	else if	(IsEqIID(&GUID_Square,					(const void*)pIID)){Logger("-> GUID_Square\r\n");}
	else if	(IsEqIID(&GUID_Sine,					(const void*)pIID)){Logger("-> GUID_Sine\r\n");}
	else if	(IsEqIID(&GUID_Triangle,				(const void*)pIID)){Logger("-> GUID_Triangle\r\n");}
	else if	(IsEqIID(&GUID_SawtoothUp,				(const void*)pIID)){Logger("-> GUID_SawtoothUp\r\n");}
	else if	(IsEqIID(&GUID_SawtoothDown,			(const void*)pIID)){Logger("-> GUID_SawtoothDown\r\n");}
	else if	(IsEqIID(&GUID_Spring,					(const void*)pIID)){Logger("-> GUID_Spring\r\n");}
	else if	(IsEqIID(&GUID_Damper,					(const void*)pIID)){Logger("-> GUID_Damper\r\n");}
	else if	(IsEqIID(&GUID_Inertia,					(const void*)pIID)){Logger("-> GUID_Inertia\r\n");}
	else if	(IsEqIID(&GUID_Friction,				(const void*)pIID)){Logger("-> GUID_Friction\r\n");}
	else if	(IsEqIID(&GUID_CustomForce,				(const void*)pIID)){Logger("-> GUID_CustomForce\r\n");}

	//d3d8.dll
	else if	(IsEqIID(&IID_IDirect3D8,				(const void*)pIID)){Logger("-> IID_IDirect3D8\r\n"); Hook_IDirect3D8((DWORD*)pObj);}
	else if	(IsEqIID(&IID_IDirect3DDevice8,			(const void*)pIID)){Logger("-> IID_IDirect3DDevice8\r\n"); Hook_IDirect3DDevice8((DWORD*)pObj);}
	else if	(IsEqIID(&IID_IDirect3DResource8,		(const void*)pIID)){Logger("-> IID_IDirect3DResource8\r\n"); Hook_IDirect3DResource8((DWORD*)pObj);}
	else if	(IsEqIID(&IID_IDirect3DBaseTexture8,	(const void*)pIID)){Logger("-> IID_IDirect3DBaseTexture8\r\n"); Hook_IDirect3DBaseTexture8((DWORD*)pObj);}
	else if	(IsEqIID(&IID_IDirect3DTexture8,		(const void*)pIID)){Logger("-> IID_IDirect3DTexture8\r\n");}
	else if	(IsEqIID(&IID_IDirect3DCubeTexture8,	(const void*)pIID)){Logger("-> IID_IDirect3DCubeTexture8\r\n"); Hook_IDirect3DCubeTexture8((DWORD*)pObj);}
	else if	(IsEqIID(&IID_IDirect3DVolumeTexture8,	(const void*)pIID)){Logger("-> IID_IDirect3DVolumeTexture8\r\n"); Hook_IDirect3DVolumeTexture8((DWORD*)pObj);}
	else if	(IsEqIID(&IID_IDirect3DVertexBuffer8,	(const void*)pIID)){Logger("-> IID_IDirect3DVertexBuffer8\r\n"); Hook_IDirect3DVertexBuffer8((DWORD*)pObj);}
	else if	(IsEqIID(&IID_IDirect3DIndexBuffer8,	(const void*)pIID)){Logger("-> IID_IDirect3DIndexBuffer8\r\n"); Hook_IDirect3DIndexBuffer8((DWORD*)pObj);}
	else if	(IsEqIID(&IID_IDirect3DSurface8,		(const void*)pIID)){Logger("-> IID_IDirect3DSurface8\r\n"); Hook_IDirect3DSurface8((DWORD*)pObj);}
	else if	(IsEqIID(&IID_IDirect3DVolume8,			(const void*)pIID)){Logger("-> IID_IDirect3DVolume8\r\n"); Hook_IDirect3DVolume8((DWORD*)pObj);}
	else if	(IsEqIID(&IID_IDirect3DSwapChain8,		(const void*)pIID)){Logger("-> IID_IDirect3DSwapChain8\r\n"); Hook_IDirect3DSwapChain8((DWORD*)pObj);}

	//ERROR in compilation "unresolved symbol" ...
	//d3d9.dll
	else if	(IsEqIID(&IID_IDirect3D9,				(const void*)pIID)){Logger("-> IID_IDirect3D9\r\n");}
	else if	(IsEqIID(&IID_IDirect3DDevice9,			(const void*)pIID)){Logger("-> IID_IDirect3DDevice9\r\n");}
	else if	(IsEqIID(&IID_IDirect3DResource9,		(const void*)pIID)){Logger("-> IID_IDirect3DResource9\r\n");}
	else if	(IsEqIID(&IID_IDirect3DBaseTexture9,	(const void*)pIID)){Logger("-> IID_IDirect3DBaseTexture9\r\n");}
	else if	(IsEqIID(&IID_IDirect3DTexture9,		(const void*)pIID)){Logger("-> IID_IDirect3DTexture9\r\n");}
	else if	(IsEqIID(&IID_IDirect3DCubeTexture9,	(const void*)pIID)){Logger("-> IID_IDirect3DCubeTexture9\r\n");}
	else if	(IsEqIID(&IID_IDirect3DVolumeTexture9,	(const void*)pIID)){Logger("-> IID_IDirect3DVolumeTexture9\r\n");}
	else if	(IsEqIID(&IID_IDirect3DVertexBuffer9,	(const void*)pIID)){Logger("-> IID_IDirect3DVertexBuffer9\r\n");}
	else if	(IsEqIID(&IID_IDirect3DIndexBuffer9,	(const void*)pIID)){Logger("-> IID_IDirect3DIndexBuffer9\r\n");}
	else if	(IsEqIID(&IID_IDirect3DSurface9,		(const void*)pIID)){Logger("-> IID_IDirect3DSurface9\r\n");}
	else if	(IsEqIID(&IID_IDirect3DVolume9,			(const void*)pIID)){Logger("-> IID_IDirect3DVolume9\r\n");}
	else if	(IsEqIID(&IID_IDirect3DSwapChain9,		(const void*)pIID)){Logger("-> IID_IDirect3DSwapChain9\r\n");}
	else if	(IsEqIID(&IID_IDirect3DVertexDeclaration9,(const void*)pIID)){Logger("-> IID_IDirect3DVertexDeclaration9\r\n");}
	else if	(IsEqIID(&IID_IDirect3DVertexShader9,	(const void*)pIID)){Logger("-> IID_IDirect3DVertexShader9\r\n");}
	else if	(IsEqIID(&IID_IDirect3DPixelShader9,	(const void*)pIID)){Logger("-> IID_IDirect3DPixelShader9\r\n");}
	else if	(IsEqIID(&IID_IDirect3DStateBlock9,		(const void*)pIID)){Logger("-> IID_IDirect3DStateBlock9\r\n");}
	else if	(IsEqIID(&IID_IDirect3DQuery9,			(const void*)pIID)){Logger("-> IID_IDirect3DQuery9\r\n");}

	else	dump_IID((PBYTE)pIID);
}
