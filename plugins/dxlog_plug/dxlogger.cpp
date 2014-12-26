
#include "stdafx.h"
#include <Windows.h>

#include "plugin.h"
#include "dxlogger.h"
#include "guid.h"
#include "commondata.h"


FUNCDATA table_IDirect3DDevice9[]={
	{"IDirect3DDevice9_QueryInterface",3},//0
	{"IDirect3DDevice9_AddRef",1},//1
	{"IDirect3DDevice9_Release",1},//2
	{"IDirect3DDevice9_TestCooperativeLevel",1},//3
	{"IDirect3DDevice9_GetAvailableTextureMem",1},//4
	{"IDirect3DDevice9_EvictManagedResources",1},//5
	{"IDirect3DDevice9_GetDirect3D",2},//6
	{"IDirect3DDevice9_GetDeviceCaps",2},//7
	{"IDirect3DDevice9_GetDisplayMode",3},//8
	{"IDirect3DDevice9_GetCreationParameters",2},//9
	{"IDirect3DDevice9_SetCursorProperties",4},//10
	{"IDirect3DDevice9_SetCursorPosition",4},//11
	{"IDirect3DDevice9_ShowCursor",2},//12
	{"IDirect3DDevice9_CreateAdditionalSwapChain",3},//13
	{"IDirect3DDevice9_GetSwapChain",3},//14
	{"IDirect3DDevice9_GetNumberOfSwapChains",1},//15
	{"IDirect3DDevice9_Reset",2},//16
	{"IDirect3DDevice9_Present",5},//17
	{"IDirect3DDevice9_GetBackBuffer",5},//18
	{"IDirect3DDevice9_GetRasterStatus",3},//19
	{"IDirect3DDevice9_SetDialogBoxMode",2},//20
	{"IDirect3DDevice9_SetGammaRamp",4},//21
	{"IDirect3DDevice9_GetGammaRamp",3},//22
	{"IDirect3DDevice9_CreateTexture",9},//23
	{"IDirect3DDevice9_CreateVolumeTexture",10},//24
	{"IDirect3DDevice9_CreateCubeTexture",8},//25
	{"IDirect3DDevice9_CreateVertexBuffer",7},//26
	{"IDirect3DDevice9_CreateIndexBuffer",7},//27
	{"IDirect3DDevice9_CreateRenderTarget",9},//28
	{"IDirect3DDevice9_CreateDepthStencilSurface",9},//29
	{"IDirect3DDevice9_UpdateSurface",5},//30
	{"IDirect3DDevice9_UpdateTexture",3},//31
	{"IDirect3DDevice9_GetRenderTargetData",3},//32
	{"IDirect3DDevice9_GetFrontBufferData",3},//33
	{"IDirect3DDevice9_StretchRect",6},//34
	{"IDirect3DDevice9_ColorFill",4},//35
	{"IDirect3DDevice9_CreateOffscreenPlainSurface",7},//36
	{"IDirect3DDevice9_SetRenderTarget",3},//37
	{"IDirect3DDevice9_GetRenderTarget",3},//38
	{"IDirect3DDevice9_SetDepthStencilSurface",2},//39
	{"IDirect3DDevice9_GetDepthStencilSurface",2},//40
	{"IDirect3DDevice9_BeginScene",1},//41
	{"IDirect3DDevice9_EndScene",1},//42
	{"IDirect3DDevice9_Clear",7},//43
	{"IDirect3DDevice9_SetTransform",3},//44
	{"IDirect3DDevice9_GetTransform",3},//45
	{"IDirect3DDevice9_MultiplyTransform",3},//46
	{"IDirect3DDevice9_SetViewport",2},//47
	{"IDirect3DDevice9_GetViewport",2},//48
	{"IDirect3DDevice9_SetMaterial",2},//49
	{"IDirect3DDevice9_GetMaterial",2},//50
	{"IDirect3DDevice9_SetLight",3},//51
	{"IDirect3DDevice9_GetLight",3},//52
	{"IDirect3DDevice9_LightEnable",3},//53
	{"IDirect3DDevice9_GetLightEnable",3},//54
	{"IDirect3DDevice9_SetClipPlane",3},//55
	{"IDirect3DDevice9_GetClipPlane",3},//56
	{"IDirect3DDevice9_SetRenderState",3},//57
	{"IDirect3DDevice9_GetRenderState",3},//58
	{"IDirect3DDevice9_CreateStateBlock",3},//59
	{"IDirect3DDevice9_BeginStateBlock",1},//60
	{"IDirect3DDevice9_EndStateBlock",2},//61
	{"IDirect3DDevice9_SetClipStatus",2},//62
	{"IDirect3DDevice9_GetClipStatus",2},//63
	{"IDirect3DDevice9_GetTexture",3},//64
	{"IDirect3DDevice9_SetTexture",3},//65
	{"IDirect3DDevice9_GetTextureStageState",4},//66
	{"IDirect3DDevice9_SetTextureStageState",4},//67
	{"IDirect3DDevice9_GetSamplerState",4},//68
	{"IDirect3DDevice9_SetSamplerState",4},//69
	{"IDirect3DDevice9_ValidateDevice",2},//70
	{"IDirect3DDevice9_SetPaletteEntries",3},//71
	{"IDirect3DDevice9_GetPaletteEntries",3},//72
	{"IDirect3DDevice9_SetCurrentTexturePalette",2},//73
	{"IDirect3DDevice9_GetCurrentTexturePalette",2},//74
	{"IDirect3DDevice9_SetScissorRect",2},//75
	{"IDirect3DDevice9_GetScissorRect",2},//76
	{"IDirect3DDevice9_SetSoftwareVertexProcessing",2},//77
	{"IDirect3DDevice9_GetSoftwareVertexProcessing",1},//78
	{"IDirect3DDevice9_SetNPatchMode",2},//79
	{"IDirect3DDevice9_GetNPatchMode",1},//80
	{"IDirect3DDevice9_DrawPrimitive",4},//81
	{"IDirect3DDevice9_DrawIndexedPrimitive",7},//82
	{"IDirect3DDevice9_DrawPrimitiveUP",5},//83
	{"IDirect3DDevice9_DrawIndexedPrimitiveUP",9},//84
	{"IDirect3DDevice9_ProcessVertices",7},//85
	{"IDirect3DDevice9_CreateVertexDeclaration",3},//86
	{"IDirect3DDevice9_SetVertexDeclaration",2},//87
	{"IDirect3DDevice9_GetVertexDeclaration",2},//88
	{"IDirect3DDevice9_SetFVF",2},//89
	{"IDirect3DDevice9_GetFVF",2},//90
	{"IDirect3DDevice9_CreateVertexShader",3},//91
	{"IDirect3DDevice9_SetVertexShader",2},//92
	{"IDirect3DDevice9_GetVertexShader",2},//93
	{"IDirect3DDevice9_SetVertexShaderConstantF",4},//94
	{"IDirect3DDevice9_GetVertexShaderConstantF",4},//95
	{"IDirect3DDevice9_SetVertexShaderConstantI",4},//96
	{"IDirect3DDevice9_GetVertexShaderConstantI",4},//97
	{"IDirect3DDevice9_SetVertexShaderConstantB",4},//98
	{"IDirect3DDevice9_GetVertexShaderConstantB",4},//99
	{"IDirect3DDevice9_SetStreamSource",5},//100
	{"IDirect3DDevice9_GetStreamSource",5},//101
	{"IDirect3DDevice9_SetStreamSourceFreq",3},//102
	{"IDirect3DDevice9_GetStreamSourceFreq",3},//103
	{"IDirect3DDevice9_SetIndices",2},//104
	{"IDirect3DDevice9_GetIndices",2},//105
	{"IDirect3DDevice9_CreatePixelShader",3},//106
	{"IDirect3DDevice9_SetPixelShader",2},//107
	{"IDirect3DDevice9_GetPixelShader",2},//108
	{"IDirect3DDevice9_SetPixelShaderConstantF",4},//109
	{"IDirect3DDevice9_GetPixelShaderConstantF",4},//110
	{"IDirect3DDevice9_SetPixelShaderConstantI",4},//111
	{"IDirect3DDevice9_GetPixelShaderConstantI",4},//112
	{"IDirect3DDevice9_SetPixelShaderConstantB",4},//113
	{"IDirect3DDevice9_GetPixelShaderConstantB",4},//114
	{"IDirect3DDevice9_DrawRectPatch",4},//115
	{"IDirect3DDevice9_DrawTriPatch",4},//116
	{"IDirect3DDevice9_DeletePatch",2},//117
	{"IDirect3DDevice9_CreateQuery",3},//118
};


FUNCDATA table_IDirect3D9[]={
	{"IDirect3D9_QueryInterface",3},//0
	{"IDirect3D9_AddRef",1},//1
	{"IDirect3D9_Release",1},//2
	{"IDirect3D9_RegisterSoftwareDevice",2},//3
	{"IDirect3D9_GetAdapterCount",1},//4
	{"IDirect3D9_GetAdapterIdentifier",4},//5
	{"IDirect3D9_GetAdapterModeCount",3},//6
	{"IDirect3D9_EnumAdapterModes",5},//7
	{"IDirect3D9_GetAdapterDisplayMode",3},//8
	{"IDirect3D9_CheckDeviceType",6},//9
	{"IDirect3D9_CheckDeviceFormat",7},//10
	{"IDirect3D9_CheckDeviceMultiSampleType",7},//11
	{"IDirect3D9_CheckDepthStencilMatch",6},//12
	{"IDirect3D9_CheckDeviceFormatConversion",5},//13
	{"IDirect3D9_GetDeviceCaps",4},//14
	{"IDirect3D9_GetAdapterMonitor",2},//15
	{"IDirect3D9_CreateDevice",7},//16
};

FUNCDATA table_IDirect3DVolume8[]={
	{"IDirect3DVolume8_QueryInterface",3},//0
	{"IDirect3DVolume8_AddRef",1},//1
	{"IDirect3DVolume8_Release",1},//2
	{"IDirect3DVolume8_GetDevice",2},//3
	{"IDirect3DVolume8_SetPrivateData",5},//4
	{"IDirect3DVolume8_GetPrivateData",4},//5
	{"IDirect3DVolume8_FreePrivateData",2},//6
	{"IDirect3DVolume8_GetContainer",3},//7
	{"IDirect3DVolume8_GetDesc",2},//8
	{"IDirect3DVolume8_LockBox",4},//9
	{"IDirect3DVolume8_UnlockBox",1},//10
};

FUNCDATA table_IDirect3DSurface8[]={
	{"IDirect3DSurface8_QueryInterface",3},//0
	{"IDirect3DSurface8_AddRef",1},//1
	{"IDirect3DSurface8_Release",1},//2
	{"IDirect3DSurface8_GetDevice",2},//3
	{"IDirect3DSurface8_SetPrivateData",5},//4
	{"IDirect3DSurface8_GetPrivateData",4},//5
	{"IDirect3DSurface8_FreePrivateData",2},//6
	{"IDirect3DSurface8_GetContainer",3},//7
	{"IDirect3DSurface8_GetDesc",2},//8
	{"IDirect3DSurface8_LockRect",4},//9
	{"IDirect3DSurface8_UnlockRect",1},//10
};

FUNCDATA table_IDirect3DIndexBuffer8[]={
	{"IDirect3DIndexBuffer8_QueryInterface",3},//0
	{"IDirect3DIndexBuffer8_AddRef",1},//1
	{"IDirect3DIndexBuffer8_Release",1},//2
	{"IDirect3DIndexBuffer8_GetDevice",2},//3
	{"IDirect3DIndexBuffer8_SetPrivateData",5},//4
	{"IDirect3DIndexBuffer8_GetPrivateData",4},//5
	{"IDirect3DIndexBuffer8_FreePrivateData",2},//6
	{"IDirect3DIndexBuffer8_SetPriority",2},//7
	{"IDirect3DIndexBuffer8_GetPriority",1},//8
	{"IDirect3DIndexBuffer8_PreLoad",1},//9
	{"IDirect3DIndexBuffer8_GetType",1},//10
	{"IDirect3DIndexBuffer8_Lock",5},//11
	{"IDirect3DIndexBuffer8_Unlock",1},//12
	{"IDirect3DIndexBuffer8_GetDesc",2},//13
};

FUNCDATA table_IDirect3DVertexBuffer8[]={
	{"IDirect3DVertexBuffer8_QueryInterface",3},//0
	{"IDirect3DVertexBuffer8_AddRef",1},//1
	{"IDirect3DVertexBuffer8_Release",1},//2
	{"IDirect3DVertexBuffer8_GetDevice",2},//3
	{"IDirect3DVertexBuffer8_SetPrivateData",5},//4
	{"IDirect3DVertexBuffer8_GetPrivateData",4},//5
	{"IDirect3DVertexBuffer8_FreePrivateData",2},//6
	{"IDirect3DVertexBuffer8_SetPriority",2},//7
	{"IDirect3DVertexBuffer8_GetPriority",1},//8
	{"IDirect3DVertexBuffer8_PreLoad",1},//9
	{"IDirect3DVertexBuffer8_GetType",1},//10
	{"IDirect3DVertexBuffer8_Lock",5},//11
	{"IDirect3DVertexBuffer8_Unlock",1},//12
	{"IDirect3DVertexBuffer8_GetDesc",2},//13
};

FUNCDATA table_IDirect3DCubeTexture8[]={
	{"IDirect3DCubeTexture8_QueryInterface",3},//0
	{"IDirect3DCubeTexture8_AddRef",1},//1
	{"IDirect3DCubeTexture8_Release",1},//2
	{"IDirect3DCubeTexture8_GetDevice",2},//3
	{"IDirect3DCubeTexture8_SetPrivateData",5},//4
	{"IDirect3DCubeTexture8_GetPrivateData",4},//5
	{"IDirect3DCubeTexture8_FreePrivateData",2},//6
	{"IDirect3DCubeTexture8_SetPriority",2},//7
	{"IDirect3DCubeTexture8_GetPriority",1},//8
	{"IDirect3DCubeTexture8_PreLoad",1},//9
	{"IDirect3DCubeTexture8_GetType",1},//10
	{"IDirect3DCubeTexture8_SetLOD",2},//11
	{"IDirect3DCubeTexture8_GetLOD",1},//12
	{"IDirect3DCubeTexture8_GetLevelCount",1},//13
	{"IDirect3DCubeTexture8_GetLevelDesc",3},//14
	{"IDirect3DCubeTexture8_GetCubeMapSurface",4},//15
	{"IDirect3DCubeTexture8_LockRect",6},//16
	{"IDirect3DCubeTexture8_UnlockRect",3},//17
	{"IDirect3DCubeTexture8_AddDirtyRect",3},//18
};

FUNCDATA table_IDirect3DVolumeTexture8[]={
	{"IDirect3DVolumeTexture8_QueryInterface",3},//0
	{"IDirect3DVolumeTexture8_AddRef",1},//1
	{"IDirect3DVolumeTexture8_Release",1},//2
	{"IDirect3DVolumeTexture8_GetDevice",2},//3
	{"IDirect3DVolumeTexture8_SetPrivateData",5},//4
	{"IDirect3DVolumeTexture8_GetPrivateData",4},//5
	{"IDirect3DVolumeTexture8_FreePrivateData",2},//6
	{"IDirect3DVolumeTexture8_SetPriority",2},//7
	{"IDirect3DVolumeTexture8_GetPriority",1},//8
	{"IDirect3DVolumeTexture8_PreLoad",1},//9
	{"IDirect3DVolumeTexture8_GetType",1},//10
	{"IDirect3DVolumeTexture8_SetLOD",2},//11
	{"IDirect3DVolumeTexture8_GetLOD",1},//12
	{"IDirect3DVolumeTexture8_GetLevelCount",1},//13
	{"IDirect3DVolumeTexture8_GetLevelDesc",3},//14
	{"IDirect3DVolumeTexture8_GetVolumeLevel",3},//15
	{"IDirect3DVolumeTexture8_LockBox",5},//16
	{"IDirect3DVolumeTexture8_UnlockBox",2},//17
	{"IDirect3DVolumeTexture8_AddDirtyBox",2},//18
};

FUNCDATA table_IDirect3DBaseTexture8[]={
	{"IDirect3DBaseTexture8_QueryInterface",3},//0
	{"IDirect3DBaseTexture8_AddRef",1},//1
	{"IDirect3DBaseTexture8_Release",1},//2
	{"IDirect3DBaseTexture8_GetDevice",2},//3
	{"IDirect3DBaseTexture8_SetPrivateData",5},//4
	{"IDirect3DBaseTexture8_GetPrivateData",4},//5
	{"IDirect3DBaseTexture8_FreePrivateData",2},//6
	{"IDirect3DBaseTexture8_SetPriority",2},//7
	{"IDirect3DBaseTexture8_GetPriority",1},//8
	{"IDirect3DBaseTexture8_PreLoad",1},//9
	{"IDirect3DBaseTexture8_GetType",1},//10
	{"IDirect3DBaseTexture8_SetLOD",2},//11
	{"IDirect3DBaseTexture8_GetLOD",1},//12
	{"IDirect3DBaseTexture8_GetLevelCount",1},//13
};

FUNCDATA table_IDirect3DResource8[]={
	{"IDirect3DResource8_QueryInterface",3},//0
	{"IDirect3DResource8_AddRef",1},//1
	{"IDirect3DResource8_Release",1},//2
	{"IDirect3DResource8_GetDevice",2},//3
	{"IDirect3DResource8_SetPrivateData",5},//4
	{"IDirect3DResource8_GetPrivateData",4},//5
	{"IDirect3DResource8_FreePrivateData",2},//6
	{"IDirect3DResource8_SetPriority",2},//7
	{"IDirect3DResource8_GetPriority",1},//8
	{"IDirect3DResource8_PreLoad",1},//9
	{"IDirect3DResource8_GetType",1},//10
};

FUNCDATA table_IDirect3DSwapChain8[]={
	{"IDirect3DSwapChain8_QueryInterface",3},//0
	{"IDirect3DSwapChain8_AddRef",1},//1
	{"IDirect3DSwapChain8_Release",1},//2
	{"IDirect3DSwapChain8_Present",5},//3
	{"IDirect3DSwapChain8_GetBackBuffer",4},//4
};

FUNCDATA table_IDirect3DDevice8[]={
	{"IDirect3DDevice8_QueryInterface",3},//0
	{"IDirect3DDevice8_AddRef",1},//1
	{"IDirect3DDevice8_Release",1},//2
	{"IDirect3DDevice8_TestCooperativeLevel",1},//3
	{"IDirect3DDevice8_GetAvailableTextureMem",1},//4
	{"IDirect3DDevice8_ResourceManagerDiscardBytes",2},//5
	{"IDirect3DDevice8_GetDirect3D",2},//6
	{"IDirect3DDevice8_GetDeviceCaps",2},//7
	{"IDirect3DDevice8_GetDisplayMode",2},//8
	{"IDirect3DDevice8_GetCreationParameters",2},//9
	{"IDirect3DDevice8_SetCursorProperties",4},//10
	{"IDirect3DDevice8_SetCursorPosition",4},//11
	{"IDirect3DDevice8_ShowCursor",2},//12
	{"IDirect3DDevice8_CreateAdditionalSwapChain",3},//13
	{"IDirect3DDevice8_Reset",2},//14
	{"IDirect3DDevice8_Present",5},//15
	{"IDirect3DDevice8_GetBackBuffer",4},//16
	{"IDirect3DDevice8_GetRasterStatus",2},//17
	{"IDirect3DDevice8_SetGammaRamp",3},//18
	{"IDirect3DDevice8_GetGammaRamp",2},//19
	{"IDirect3DDevice8_CreateTexture",8},//20
	{"IDirect3DDevice8_CreateVolumeTexture",9},//21
	{"IDirect3DDevice8_CreateCubeTexture",7},//22
	{"IDirect3DDevice8_CreateVertexBuffer",6},//23
	{"IDirect3DDevice8_CreateIndexBuffer",6},//24
	{"IDirect3DDevice8_CreateRenderTarget",7},//25
	{"IDirect3DDevice8_CreateDepthStencilSurface",6},//26
	{"IDirect3DDevice8_CreateImageSurface",5},//27
	{"IDirect3DDevice8_CopyRects",6},//28
	{"IDirect3DDevice8_UpdateTexture",3},//29
	{"IDirect3DDevice8_GetFrontBuffer",2},//30
	{"IDirect3DDevice8_SetRenderTarget",3},//31
	{"IDirect3DDevice8_GetRenderTarget",2},//32
	{"IDirect3DDevice8_GetDepthStencilSurface",2},//33
	{"IDirect3DDevice8_BeginScene",1},//34
	{"IDirect3DDevice8_EndScene",1},//35
	{"IDirect3DDevice8_Clear",7},//36
	{"IDirect3DDevice8_SetTransform",3},//37
	{"IDirect3DDevice8_GetTransform",3},//38
	{"IDirect3DDevice8_MultiplyTransform",3},//39
	{"IDirect3DDevice8_SetViewport",2},//40
	{"IDirect3DDevice8_GetViewport",2},//41
	{"IDirect3DDevice8_SetMaterial",2},//42
	{"IDirect3DDevice8_GetMaterial",2},//43
	{"IDirect3DDevice8_SetLight",3},//44
	{"IDirect3DDevice8_GetLight",3},//45
	{"IDirect3DDevice8_LightEnable",3},//46
	{"IDirect3DDevice8_GetLightEnable",3},//47
	{"IDirect3DDevice8_SetClipPlane",3},//48
	{"IDirect3DDevice8_GetClipPlane",3},//49
	{"IDirect3DDevice8_SetRenderState",3},//50
	{"IDirect3DDevice8_GetRenderState",3},//51
	{"IDirect3DDevice8_BeginStateBlock",1},//52
	{"IDirect3DDevice8_EndStateBlock",2},//53
	{"IDirect3DDevice8_ApplyStateBlock",2},//54
	{"IDirect3DDevice8_CaptureStateBlock",2},//55
	{"IDirect3DDevice8_DeleteStateBlock",2},//56
	{"IDirect3DDevice8_CreateStateBlock",3},//57
	{"IDirect3DDevice8_SetClipStatus",2},//58
	{"IDirect3DDevice8_GetClipStatus",2},//59
	{"IDirect3DDevice8_GetTexture",3},//60
	{"IDirect3DDevice8_SetTexture",3},//61
	{"IDirect3DDevice8_GetTextureStageState",4},//62
	{"IDirect3DDevice8_SetTextureStageState",4},//63
	{"IDirect3DDevice8_ValidateDevice",2},//64
	{"IDirect3DDevice8_GetInfo",4},//65
	{"IDirect3DDevice8_SetPaletteEntries",3},//66
	{"IDirect3DDevice8_GetPaletteEntries",3},//67
	{"IDirect3DDevice8_SetCurrentTexturePalette",2},//68
	{"IDirect3DDevice8_GetCurrentTexturePalette",2},//69
	{"IDirect3DDevice8_DrawPrimitive",4},//70
	{"IDirect3DDevice8_DrawIndexedPrimitive",6},//71
	{"IDirect3DDevice8_DrawPrimitiveUP",5},//72
	{"IDirect3DDevice8_DrawIndexedPrimitiveUP",9},//73
	{"IDirect3DDevice8_ProcessVertices",6},//74
	{"IDirect3DDevice8_CreateVertexShader",5},//75
	{"IDirect3DDevice8_SetVertexShader",2},//76
	{"IDirect3DDevice8_GetVertexShader",2},//77
	{"IDirect3DDevice8_DeleteVertexShader",2},//78
	{"IDirect3DDevice8_SetVertexShaderConstant",4},//79
	{"IDirect3DDevice8_GetVertexShaderConstant",4},//80
	{"IDirect3DDevice8_GetVertexShaderDeclaration",4},//81
	{"IDirect3DDevice8_GetVertexShaderFunction",4},//82
	{"IDirect3DDevice8_SetStreamSource",4},//83
	{"IDirect3DDevice8_GetStreamSource",4},//84
	{"IDirect3DDevice8_SetIndices",3},//85
	{"IDirect3DDevice8_GetIndices",3},//86
	{"IDirect3DDevice8_CreatePixelShader",3},//87
	{"IDirect3DDevice8_SetPixelShader",2},//88
	{"IDirect3DDevice8_GetPixelShader",2},//89
	{"IDirect3DDevice8_DeletePixelShader",2},//90
	{"IDirect3DDevice8_SetPixelShaderConstant",4},//91
	{"IDirect3DDevice8_GetPixelShaderConstant",4},//92
	{"IDirect3DDevice8_GetPixelShaderFunction",4},//93
	{"IDirect3DDevice8_DrawRectPatch",4},//94
	{"IDirect3DDevice8_DrawTriPatch",4},//95
	{"IDirect3DDevice8_DeletePatch",2},//96
};

FUNCDATA table_IDirect3D8[]={
	{"IDirect3D8_QueryInterface",3},//0
	{"IDirect3D8_AddRef",1},//1
	{"IDirect3D8_Release",1},//2
	{"IDirect3D8_RegisterSoftwareDevice",2},//3
	{"IDirect3D8_GetAdapterCount",1},//4
	{"IDirect3D8_GetAdapterIdentifier",4},//5
	{"IDirect3D8_GetAdapterModeCount",2},//6
	{"IDirect3D8_EnumAdapterModes",4},//7
	{"IDirect3D8_GetAdapterDisplayMode",3},//8
	{"IDirect3D8_CheckDeviceType",6},//9
	{"IDirect3D8_CheckDeviceFormat",7},//10
	{"IDirect3D8_CheckDeviceMultiSampleType",6},//11
	{"IDirect3D8_CheckDepthStencilMatch",6},//12
	{"IDirect3D8_GetDeviceCaps",4},//13
	{"IDirect3D8_GetAdapterMonitor",2},//14
	{"IDirect3D8_CreateDevice",7},//15
};

FUNCDATA table_IDirect3D3[]={
	{"IDirect3D3_QueryInterface",3},//0
	{"IDirect3D3_AddRef",1},//1
	{"IDirect3D3_Release",1},//2
	{"IDirect3D3_EnumDevices",3},//3
	{"IDirect3D3_CreateLight",3},//4
	{"IDirect3D3_CreateMaterial",3},//5
	{"IDirect3D3_CreateViewport",3},//6
	{"IDirect3D3_FindDevice",3},//7
	{"IDirect3D3_CreateDevice",5},//8
	{"IDirect3D3_CreateVertexBuffer",5},//9
	{"IDirect3D3_EnumZBufferFormats",4},//10
	{"IDirect3D3_EvictManagedTextures",1},//11
};

FUNCDATA table_IDirect3D2[]={
	{"IDirect3D2_QueryInterface",3},//0
	{"IDirect3D2_AddRef",1},//1
	{"IDirect3D2_Release",1},//2
	{"IDirect3D2_EnumDevices",3},//3
	{"IDirect3D2_CreateLight",3},//4
	{"IDirect3D2_CreateMaterial",3},//5
	{"IDirect3D2_CreateViewport",3},//6
	{"IDirect3D2_FindDevice",3},//7
	{"IDirect3D2_CreateDevice",4},//8
};

FUNCDATA table_IDirect3D[]={
	{"IDirect3D_QueryInterface",3},//0
	{"IDirect3D_AddRef",1},//1
	{"IDirect3D_Release",1},//2
	{"IDirect3D_Initialize",2},//3
	{"IDirect3D_EnumDevices",3},//4
	{"IDirect3D_CreateLight",3},//5
	{"IDirect3D_CreateMaterial",3},//6
	{"IDirect3D_CreateViewport",3},//7
	{"IDirect3D_FindDevice",3},//8
};

FUNCDATA table_IDirect3DDevice3[]={
	{"IDirect3DDevice3_QueryInterface",3},//0
	{"IDirect3DDevice3_AddRef",1},//1
	{"IDirect3DDevice3_Release",1},//2
	{"IDirect3DDevice3_GetCaps",3},//3
	{"IDirect3DDevice3_GetStats",2},//4
	{"IDirect3DDevice3_AddViewport",2},//5
	{"IDirect3DDevice3_DeleteViewport",2},//6
	{"IDirect3DDevice3_NextViewport",4},//7
	{"IDirect3DDevice3_EnumTextureFormats",3},//8
	{"IDirect3DDevice3_BeginScene",1},//9
	{"IDirect3DDevice3_EndScene",1},//10
	{"IDirect3DDevice3_GetDirect3D",2},//11
	{"IDirect3DDevice3_SetCurrentViewport",2},//12
	{"IDirect3DDevice3_GetCurrentViewport",2},//13
	{"IDirect3DDevice3_SetRenderTarget",3},//14
	{"IDirect3DDevice3_GetRenderTarget",2},//15
	{"IDirect3DDevice3_Begin",4},//16
	{"IDirect3DDevice3_BeginIndexed",6},//17
	{"IDirect3DDevice3_Vertex",2},//18
	{"IDirect3DDevice3_Index",2},//19
	{"IDirect3DDevice3_End",2},//20
	{"IDirect3DDevice3_GetRenderState",3},//21
	{"IDirect3DDevice3_SetRenderState",3},//22
	{"IDirect3DDevice3_GetLightState",3},//23
	{"IDirect3DDevice3_SetLightState",3},//24
	{"IDirect3DDevice3_SetTransform",3},//25
	{"IDirect3DDevice3_GetTransform",3},//26
	{"IDirect3DDevice3_MultiplyTransform",3},//27
	{"IDirect3DDevice3_DrawPrimitive",6},//28
	{"IDirect3DDevice3_DrawIndexedPrimitive",8},//29
	{"IDirect3DDevice3_SetClipStatus",2},//30
	{"IDirect3DDevice3_GetClipStatus",2},//31
	{"IDirect3DDevice3_DrawPrimitiveStrided",6},//32
	{"IDirect3DDevice3_DrawIndexedPrimitiveStrided",8},//33
	{"IDirect3DDevice3_DrawPrimitiveVB",6},//34
	{"IDirect3DDevice3_DrawIndexedPrimitiveVB",6},//35
	{"IDirect3DDevice3_ComputeSphereVisibility",6},//36
	{"IDirect3DDevice3_GetTexture",3},//37
	{"IDirect3DDevice3_SetTexture",3},//38
	{"IDirect3DDevice3_GetTextureStageState",4},//39
	{"IDirect3DDevice3_SetTextureStageState",4},//40
	{"IDirect3DDevice3_ValidateDevice",2},//41
};

FUNCDATA table_IDirect3DDevice2[]={
	{"IDirect3DDevice2_QueryInterface",3},//0
	{"IDirect3DDevice2_AddRef",1},//1
	{"IDirect3DDevice2_Release",1},//2
	{"IDirect3DDevice2_GetCaps",3},//3
	{"IDirect3DDevice2_SwapTextureHandles",3},//4
	{"IDirect3DDevice2_GetStats",2},//5
	{"IDirect3DDevice2_AddViewport",2},//6
	{"IDirect3DDevice2_DeleteViewport",2},//7
	{"IDirect3DDevice2_NextViewport",4},//8
	{"IDirect3DDevice2_EnumTextureFormats",3},//9
	{"IDirect3DDevice2_BeginScene",1},//10
	{"IDirect3DDevice2_EndScene",1},//11
	{"IDirect3DDevice2_GetDirect3D",2},//12
	{"IDirect3DDevice2_SetCurrentViewport",2},//13
	{"IDirect3DDevice2_GetCurrentViewport",2},//14
	{"IDirect3DDevice2_SetRenderTarget",3},//15
	{"IDirect3DDevice2_GetRenderTarget",2},//16
	{"IDirect3DDevice2_Begin",4},//17
	{"IDirect3DDevice2_BeginIndexed",6},//18
	{"IDirect3DDevice2_Vertex",2},//19
	{"IDirect3DDevice2_Index",2},//20
	{"IDirect3DDevice2_End",2},//21
	{"IDirect3DDevice2_GetRenderState",3},//22
	{"IDirect3DDevice2_SetRenderState",3},//23
	{"IDirect3DDevice2_GetLightState",3},//24
	{"IDirect3DDevice2_SetLightState",3},//25
	{"IDirect3DDevice2_SetTransform",3},//26
	{"IDirect3DDevice2_GetTransform",3},//27
	{"IDirect3DDevice2_MultiplyTransform",3},//28
	{"IDirect3DDevice2_DrawPrimitive",6},//29
	{"IDirect3DDevice2_DrawIndexedPrimitive",8},//30
	{"IDirect3DDevice2_SetClipStatus",2},//31
	{"IDirect3DDevice2_GetClipStatus",2},//32
};

FUNCDATA table_IDirect3DDevice[]={
	{"IDirect3DDevice_QueryInterface",3},//0
	{"IDirect3DDevice_AddRef",1},//1
	{"IDirect3DDevice_Release",1},//2
	{"IDirect3DDevice_Initialize",4},//3
	{"IDirect3DDevice_GetCaps",3},//4
	{"IDirect3DDevice_SwapTextureHandles",3},//5
	{"IDirect3DDevice_CreateExecuteBuffer",4},//6
	{"IDirect3DDevice_GetStats",2},//7
	{"IDirect3DDevice_Execute",4},//8
	{"IDirect3DDevice_AddViewport",2},//9
	{"IDirect3DDevice_DeleteViewport",2},//10
	{"IDirect3DDevice_NextViewport",4},//11
	{"IDirect3DDevice_Pick",5},//12
	{"IDirect3DDevice_GetPickRecords",3},//13
	{"IDirect3DDevice_EnumTextureFormats",3},//14
	{"IDirect3DDevice_CreateMatrix",2},//15
	{"IDirect3DDevice_SetMatrix",3},//16
	{"IDirect3DDevice_GetMatrix",3},//17
	{"IDirect3DDevice_DeleteMatrix",2},//18
	{"IDirect3DDevice_BeginScene",1},//19
	{"IDirect3DDevice_EndScene",1},//20
	{"IDirect3DDevice_GetDirect3D",2},//21
};

FUNCDATA table_IDirectDrawSurface4[]={
	{"IDirectDrawSurface4_QueryInterface",3},//0
	{"IDirectDrawSurface4_AddRef",1},//1
	{"IDirectDrawSurface4_Release",1},//2
	{"IDirectDrawSurface4_AddAttachedSurface",2},//3
	{"IDirectDrawSurface4_AddOverlayDirtyRect",2},//4
	{"IDirectDrawSurface4_Blt",6},//5
	{"IDirectDrawSurface4_BltBatch",4},//6
	{"IDirectDrawSurface4_BltFast",6},//7
	{"IDirectDrawSurface4_DeleteAttachedSurface",3},//8
	{"IDirectDrawSurface4_EnumAttachedSurfaces",3},//9
	{"IDirectDrawSurface4_EnumOverlayZOrders",4},//10
	{"IDirectDrawSurface4_Flip",3},//11
	{"IDirectDrawSurface4_GetAttachedSurface",3},//12
	{"IDirectDrawSurface4_GetBltStatus",2},//13
	{"IDirectDrawSurface4_GetCaps",2},//14
	{"IDirectDrawSurface4_GetClipper",2},//15
	{"IDirectDrawSurface4_GetColorKey",3},//16
	{"IDirectDrawSurface4_GetDC",2},//17
	{"IDirectDrawSurface4_GetFlipStatus",2},//18
	{"IDirectDrawSurface4_GetOverlayPosition",3},//19
	{"IDirectDrawSurface4_GetPalette",2},//20
	{"IDirectDrawSurface4_GetPixelFormat",2},//21
	{"IDirectDrawSurface4_GetSurfaceDesc",2},//22
	{"IDirectDrawSurface4_Initialize",3},//23
	{"IDirectDrawSurface4_IsLost",1},//24
	{"IDirectDrawSurface4_Lock",5},//25
	{"IDirectDrawSurface4_ReleaseDC",2},//26
	{"IDirectDrawSurface4_Restore",1},//27
	{"IDirectDrawSurface4_SetClipper",2},//28
	{"IDirectDrawSurface4_SetColorKey",3},//29
	{"IDirectDrawSurface4_SetOverlayPosition",3},//30
	{"IDirectDrawSurface4_SetPalette",2},//31
	{"IDirectDrawSurface4_Unlock",2},//32
	{"IDirectDrawSurface4_UpdateOverlay",6},//33
	{"IDirectDrawSurface4_UpdateOverlayDisplay",2},//34
	{"IDirectDrawSurface4_UpdateOverlayZOrder",3},//35
	{"IDirectDrawSurface4_GetDDInterface",2},//36
	{"IDirectDrawSurface4_PageLock",2},//37
	{"IDirectDrawSurface4_PageUnlock",2},//38
	{"IDirectDrawSurface4_SetSurfaceDesc",3},//39
	{"IDirectDrawSurface4_SetPrivateData",5},//40
	{"IDirectDrawSurface4_GetPrivateData",4},//41
	{"IDirectDrawSurface4_FreePrivateData",2},//42
	{"IDirectDrawSurface4_GetUniquenessValue",2},//43
	{"IDirectDrawSurface4_ChangeUniquenessValue",1},//44
};

FUNCDATA table_IDirectDrawSurface3[]={
	{"IDirectDrawSurface3_QueryInterface",3},//0
	{"IDirectDrawSurface3_AddRef",1},//1
	{"IDirectDrawSurface3_Release",1},//2
	{"IDirectDrawSurface3_AddAttachedSurface",2},//3
	{"IDirectDrawSurface3_AddOverlayDirtyRect",2},//4
	{"IDirectDrawSurface3_Blt",6},//5
	{"IDirectDrawSurface3_BltBatch",4},//6
	{"IDirectDrawSurface3_BltFast",6},//7
	{"IDirectDrawSurface3_DeleteAttachedSurface",3},//8
	{"IDirectDrawSurface3_EnumAttachedSurfaces",3},//9
	{"IDirectDrawSurface3_EnumOverlayZOrders",4},//10
	{"IDirectDrawSurface3_Flip",3},//11
	{"IDirectDrawSurface3_GetAttachedSurface",3},//12
	{"IDirectDrawSurface3_GetBltStatus",2},//13
	{"IDirectDrawSurface3_GetCaps",2},//14
	{"IDirectDrawSurface3_GetClipper",2},//15
	{"IDirectDrawSurface3_GetColorKey",3},//16
	{"IDirectDrawSurface3_GetDC",2},//17
	{"IDirectDrawSurface3_GetFlipStatus",2},//18
	{"IDirectDrawSurface3_GetOverlayPosition",3},//19
	{"IDirectDrawSurface3_GetPalette",2},//20
	{"IDirectDrawSurface3_GetPixelFormat",2},//21
	{"IDirectDrawSurface3_GetSurfaceDesc",2},//22
	{"IDirectDrawSurface3_Initialize",3},//23
	{"IDirectDrawSurface3_IsLost",1},//24
	{"IDirectDrawSurface3_Lock",5},//25
	{"IDirectDrawSurface3_ReleaseDC",2},//26
	{"IDirectDrawSurface3_Restore",1},//27
	{"IDirectDrawSurface3_SetClipper",2},//28
	{"IDirectDrawSurface3_SetColorKey",3},//29
	{"IDirectDrawSurface3_SetOverlayPosition",3},//30
	{"IDirectDrawSurface3_SetPalette",2},//31
	{"IDirectDrawSurface3_Unlock",2},//32
	{"IDirectDrawSurface3_UpdateOverlay",6},//33
	{"IDirectDrawSurface3_UpdateOverlayDisplay",2},//34
	{"IDirectDrawSurface3_UpdateOverlayZOrder",3},//35
	{"IDirectDrawSurface3_GetDDInterface",2},//36
	{"IDirectDrawSurface3_PageLock",2},//37
	{"IDirectDrawSurface3_PageUnlock",2},//38
	{"IDirectDrawSurface3_SetSurfaceDesc",3},//39
};

FUNCDATA table_IDirectDrawSurface2[]={
	{"IDirectDrawSurface2_QueryInterface",3},//0
	{"IDirectDrawSurface2_AddRef",1},//1
	{"IDirectDrawSurface2_Release",1},//2
	{"IDirectDrawSurface2_AddAttachedSurface",2},//3
	{"IDirectDrawSurface2_AddOverlayDirtyRect",2},//4
	{"IDirectDrawSurface2_Blt",6},//5
	{"IDirectDrawSurface2_BltBatch",4},//6
	{"IDirectDrawSurface2_BltFast",6},//7
	{"IDirectDrawSurface2_DeleteAttachedSurface",3},//8
	{"IDirectDrawSurface2_EnumAttachedSurfaces",3},//9
	{"IDirectDrawSurface2_EnumOverlayZOrders",4},//10
	{"IDirectDrawSurface2_Flip",3},//11
	{"IDirectDrawSurface2_GetAttachedSurface",3},//12
	{"IDirectDrawSurface2_GetBltStatus",2},//13
	{"IDirectDrawSurface2_GetCaps",2},//14
	{"IDirectDrawSurface2_GetClipper",2},//15
	{"IDirectDrawSurface2_GetColorKey",3},//16
	{"IDirectDrawSurface2_GetDC",2},//17
	{"IDirectDrawSurface2_GetFlipStatus",2},//18
	{"IDirectDrawSurface2_GetOverlayPosition",3},//19
	{"IDirectDrawSurface2_GetPalette",2},//20
	{"IDirectDrawSurface2_GetPixelFormat",2},//21
	{"IDirectDrawSurface2_GetSurfaceDesc",2},//22
	{"IDirectDrawSurface2_Initialize",3},//23
	{"IDirectDrawSurface2_IsLost",1},//24
	{"IDirectDrawSurface2_Lock",5},//25
	{"IDirectDrawSurface2_ReleaseDC",2},//26
	{"IDirectDrawSurface2_Restore",1},//27
	{"IDirectDrawSurface2_SetClipper",2},//28
	{"IDirectDrawSurface2_SetColorKey",3},//29
	{"IDirectDrawSurface2_SetOverlayPosition",3},//30
	{"IDirectDrawSurface2_SetPalette",2},//31
	{"IDirectDrawSurface2_Unlock",2},//32
	{"IDirectDrawSurface2_UpdateOverlay",6},//33
	{"IDirectDrawSurface2_UpdateOverlayDisplay",2},//34
	{"IDirectDrawSurface2_UpdateOverlayZOrder",3},//35
	{"IDirectDrawSurface2_GetDDInterface",2},//36
	{"IDirectDrawSurface2_PageLock",2},//37
	{"IDirectDrawSurface2_PageUnlock",2},//38
};

FUNCDATA table_IDirectDraw4[]={
	{"IDirectDraw4_QueryInterface",3},//0
	{"IDirectDraw4_AddRef",1},//1
	{"IDirectDraw4_Release",1},//2
	{"IDirectDraw4_Compact",1},//3
	{"IDirectDraw4_CreateClipper",4},//4
	{"IDirectDraw4_CreatePalette",5},//5
	{"IDirectDraw4_CreateSurface",4},//6
	{"IDirectDraw4_DuplicateSurface",3},//7
	{"IDirectDraw4_EnumDisplayModes",5},//8
	{"IDirectDraw4_EnumSurfaces",5},//9
	{"IDirectDraw4_FlipToGDISurface",1},//10
	{"IDirectDraw4_GetCaps",3},//11
	{"IDirectDraw4_GetDisplayMode",2},//12
	{"IDirectDraw4_GetFourCCCodes",3},//13
	{"IDirectDraw4_GetGDISurface",2},//14
	{"IDirectDraw4_GetMonitorFrequency",2},//15
	{"IDirectDraw4_GetScanLine",2},//16
	{"IDirectDraw4_GetVerticalBlankStatus",2},//17
	{"IDirectDraw4_Initialize",2},//18
	{"IDirectDraw4_RestoreDisplayMode",1},//19
	{"IDirectDraw4_SetCooperativeLevel",3},//20
	{"IDirectDraw4_SetDisplayMode",6},//21
	{"IDirectDraw4_WaitForVerticalBlank",3},//22
	{"IDirectDraw4_GetAvailableVidMem",4},//23
	{"IDirectDraw4_GetSurfaceFromDC",3},//24
	{"IDirectDraw4_RestoreAllSurfaces",1},//25
	{"IDirectDraw4_TestCooperativeLevel",1},//26
	{"IDirectDraw4_GetDeviceIdentifier",3},//27
};

FUNCDATA table_IDirectDraw2[]={
	{"IDirectDraw2_QueryInterface",3},//0
	{"IDirectDraw2_AddRef",1},//1
	{"IDirectDraw2_Release",1},//2
	{"IDirectDraw2_Compact",1},//3
	{"IDirectDraw2_CreateClipper",4},//4
	{"IDirectDraw2_CreatePalette",5},//5
	{"IDirectDraw2_CreateSurface",4},//6
	{"IDirectDraw2_DuplicateSurface",3},//7
	{"IDirectDraw2_EnumDisplayModes",5},//8
	{"IDirectDraw2_EnumSurfaces",5},//9
	{"IDirectDraw2_FlipToGDISurface",1},//10
	{"IDirectDraw2_GetCaps",3},//11
	{"IDirectDraw2_GetDisplayMode",2},//12
	{"IDirectDraw2_GetFourCCCodes",3},//13
	{"IDirectDraw2_GetGDISurface",2},//14
	{"IDirectDraw2_GetMonitorFrequency",2},//15
	{"IDirectDraw2_GetScanLine",2},//16
	{"IDirectDraw2_GetVerticalBlankStatus",2},//17
	{"IDirectDraw2_Initialize",2},//18
	{"IDirectDraw2_RestoreDisplayMode",1},//19
	{"IDirectDraw2_SetCooperativeLevel",3},//20
	{"IDirectDraw2_SetDisplayMode",6},//21
	{"IDirectDraw2_WaitForVerticalBlank",3},//22
	{"IDirectDraw2_GetAvailableVidMem",4},//23
};

FUNCDATA table_IDirectDraw[]={
	{"IDirectDraw_QueryInterface",3},//0
	{"IDirectDraw_AddRef",1},//1
	{"IDirectDraw_Release",1},//2
	{"IDirectDraw_Compact",1},//3
	{"IDirectDraw_CreateClipper",4},//4
	{"IDirectDraw_CreatePalette",5},//5
	{"IDirectDraw_CreateSurface",4},//6
	{"IDirectDraw_DuplicateSurface",3},//7
	{"IDirectDraw_EnumDisplayModes",5},//8
	{"IDirectDraw_EnumSurfaces",5},//9
	{"IDirectDraw_FlipToGDISurface",1},//10
	{"IDirectDraw_GetCaps",3},//11
	{"IDirectDraw_GetDisplayMode",2},//12
	{"IDirectDraw_GetFourCCCodes",3},//13
	{"IDirectDraw_GetGDISurface",2},//14
	{"IDirectDraw_GetMonitorFrequency",2},//15
	{"IDirectDraw_GetScanLine",2},//16
	{"IDirectDraw_GetVerticalBlankStatus",2},//17
	{"IDirectDraw_Initialize",2},//18
	{"IDirectDraw_RestoreDisplayMode",1},//19
	{"IDirectDraw_SetCooperativeLevel",3},//20
	{"IDirectDraw_SetDisplayMode",4},//21
	{"IDirectDraw_WaitForVerticalBlank",3},//22
};

FUNCDATA table_IDirectDrawSurface[]={
	{"IDirectDrawSurface_QueryInterface",3},//0
	{"IDirectDrawSurface_AddRef",1},//1
	{"IDirectDrawSurface_Release",1},//2
	{"IDirectDrawSurface_AddAttachedSurface",2},//3
	{"IDirectDrawSurface_AddOverlayDirtyRect",2},//4
	{"IDirectDrawSurface_Blt",6},//5
	{"IDirectDrawSurface_BltBatch",4},//6
	{"IDirectDrawSurface_BltFast",6},//7
	{"IDirectDrawSurface_DeleteAttachedSurface",3},//8
	{"IDirectDrawSurface_EnumAttachedSurfaces",3},//9
	{"IDirectDrawSurface_EnumOverlayZOrders",4},//10
	{"IDirectDrawSurface_Flip",3},//11
	{"IDirectDrawSurface_GetAttachedSurface",3},//12
	{"IDirectDrawSurface_GetBltStatus",2},//13
	{"IDirectDrawSurface_GetCaps",2},//14
	{"IDirectDrawSurface_GetClipper",2},//15
	{"IDirectDrawSurface_GetColorKey",3},//16
	{"IDirectDrawSurface_GetDC",2},//17
	{"IDirectDrawSurface_GetFlipStatus",2},//18
	{"IDirectDrawSurface_GetOverlayPosition",3},//19
	{"IDirectDrawSurface_GetPalette",2},//20
	{"IDirectDrawSurface_GetPixelFormat",2},//21
	{"IDirectDrawSurface_GetSurfaceDesc",2},//22
	{"IDirectDrawSurface_Initialize",3},//23
	{"IDirectDrawSurface_IsLost",1},//24
	{"IDirectDrawSurface_Lock",5},//25
	{"IDirectDrawSurface_ReleaseDC",2},//26
	{"IDirectDrawSurface_Restore",1},//27
	{"IDirectDrawSurface_SetClipper",2},//28
	{"IDirectDrawSurface_SetColorKey",3},//29
	{"IDirectDrawSurface_SetOverlayPosition",3},//30
	{"IDirectDrawSurface_SetPalette",2},//31
	{"IDirectDrawSurface_Unlock",2},//32
	{"IDirectDrawSurface_UpdateOverlay",6},//33
	{"IDirectDrawSurface_UpdateOverlayDisplay",2},//34
	{"IDirectDrawSurface_UpdateOverlayZOrder",3},//35
};

FUNCDATA table_IDirectDrawSurface7[]={
	{"IDirectDrawSurface7_QueryInterface",3},//0
	{"IDirectDrawSurface7_AddRef",1},//1
	{"IDirectDrawSurface7_Release",1},//2
	{"IDirectDrawSurface7_AddAttachedSurface",2},//3
	{"IDirectDrawSurface7_AddOverlayDirtyRect",2},//4
	{"IDirectDrawSurface7_Blt",6},//5
	{"IDirectDrawSurface7_BltBatch",4},//6
	{"IDirectDrawSurface7_BltFast",6},//7
	{"IDirectDrawSurface7_DeleteAttachedSurface",3},//8
	{"IDirectDrawSurface7_EnumAttachedSurfaces",3},//9
	{"IDirectDrawSurface7_EnumOverlayZOrders",4},//10
	{"IDirectDrawSurface7_Flip",3},//11
	{"IDirectDrawSurface7_GetAttachedSurface",3},//12
	{"IDirectDrawSurface7_GetBltStatus",2},//13
	{"IDirectDrawSurface7_GetCaps",2},//14
	{"IDirectDrawSurface7_GetClipper",2},//15
	{"IDirectDrawSurface7_GetColorKey",3},//16
	{"IDirectDrawSurface7_GetDC",2},//17
	{"IDirectDrawSurface7_GetFlipStatus",2},//18
	{"IDirectDrawSurface7_GetOverlayPosition",3},//19
	{"IDirectDrawSurface7_GetPalette",2},//20
	{"IDirectDrawSurface7_GetPixelFormat",2},//21
	{"IDirectDrawSurface7_GetSurfaceDesc",2},//22
	{"IDirectDrawSurface7_Initialize",3},//23
	{"IDirectDrawSurface7_IsLost",1},//24
	{"IDirectDrawSurface7_Lock",5},//25
	{"IDirectDrawSurface7_ReleaseDC",2},//26
	{"IDirectDrawSurface7_Restore",1},//27
	{"IDirectDrawSurface7_SetClipper",2},//28
	{"IDirectDrawSurface7_SetColorKey",3},//29
	{"IDirectDrawSurface7_SetOverlayPosition",3},//30
	{"IDirectDrawSurface7_SetPalette",2},//31
	{"IDirectDrawSurface7_Unlock",2},//32
	{"IDirectDrawSurface7_UpdateOverlay",6},//33
	{"IDirectDrawSurface7_UpdateOverlayDisplay",2},//34
	{"IDirectDrawSurface7_UpdateOverlayZOrder",3},//35
	{"IDirectDrawSurface7_GetDDInterface",2},//36
	{"IDirectDrawSurface7_PageLock",2},//37
	{"IDirectDrawSurface7_PageUnlock",2},//38
	{"IDirectDrawSurface7_SetSurfaceDesc",3},//39
	{"IDirectDrawSurface7_SetPrivateData",5},//40
	{"IDirectDrawSurface7_GetPrivateData",4},//41
	{"IDirectDrawSurface7_FreePrivateData",2},//42
	{"IDirectDrawSurface7_GetUniquenessValue",2},//43
	{"IDirectDrawSurface7_ChangeUniquenessValue",1},//44
	{"IDirectDrawSurface7_SetPriority",2},//45
	{"IDirectDrawSurface7_GetPriority",2},//46
	{"IDirectDrawSurface7_SetLOD",2},//47
	{"IDirectDrawSurface7_GetLOD",2},//48
};

FUNCDATA table_IDirectDraw7[]=
{
	{"IDirectDraw7_QueryInterface",3},//0
	{"IDirectDraw7_AddRef",1},//1
	{"IDirectDraw7_Release",1},//2
	{"IDirectDraw7_Compact",1},//3
	{"IDirectDraw7_CreateClipper",4},//4
	{"IDirectDraw7_CreatePalette",5},//5
	{"IDirectDraw7_CreateSurface",4},//6
	{"IDirectDraw7_DuplicateSurface",3},//7
	{"IDirectDraw7_EnumDisplayModes",5},//8
	{"IDirectDraw7_EnumSurfaces",5},//9
	{"IDirectDraw7_FlipToGDISurface",1},//10
	{"IDirectDraw7_GetCaps",3},//11
	{"IDirectDraw7_GetDisplayMode",2},//12
	{"IDirectDraw7_GetFourCCCodes",3},//13
	{"IDirectDraw7_GetGDISurface",2},//14
	{"IDirectDraw7_GetMonitorFrequency",2},//15
	{"IDirectDraw7_GetScanLine",2},//16
	{"IDirectDraw7_GetVerticalBlankStatus",2},//17
	{"IDirectDraw7_Initialize",2},//18
	{"IDirectDraw7_RestoreDisplayMode",1},//19
	{"IDirectDraw7_SetCooperativeLevel",3},//20
	{"IDirectDraw7_SetDisplayMode",6},//21
	{"IDirectDraw7_WaitForVerticalBlank",3},//22
	{"IDirectDraw7_GetAvailableVidMem",4},//23
	{"IDirectDraw7_GetSurfaceFromDC",3},//24
	{"IDirectDraw7_RestoreAllSurfaces",1},//25
	{"IDirectDraw7_TestCooperativeLevel",1},//26
	{"IDirectDraw7_GetDeviceIdentifier",3},//27
	{"IDirectDraw7_StartModeTest",4},//28
	{"IDirectDraw7_EvaluateMode",3}//29
};



FUNCDATA table_IDirect3D7[]=
{
	{"IDirect3D7_QueryInterface",3},//0
	{"IDirect3D7_AddRef",1},//1
	{"IDirect3D7_Release",1},//2
	{"IDirect3D7_EnumDevices",3},//3
	{"IDirect3D7_CreateDevice",4},//4
	{"IDirect3D7_CreateVertexBuffer",4},//5
	{"IDirect3D7_EnumZBufferFormats",4},//6
	{"IDirect3D7_EvictManagedTextures",1}//7
};

FUNCDATA table_IDirect3DDevice7[]=
{
	{"IDirect3DDevice7_QueryInterface",3},//0
	{"IDirect3DDevice7_AddRef",1},//1
	{"IDirect3DDevice7_Release",1},//2
	{"IDirect3DDevice7_GetCaps",2},//3
	{"IDirect3DDevice7_EnumTextureFormats",3},//4
	{"IDirect3DDevice7_BeginScene",1},//5
	{"IDirect3DDevice7_EndScene",1},//6
	{"IDirect3DDevice7_GetDirect3D",2},//7
	{"IDirect3DDevice7_SetRenderTarget",3},//8
	{"IDirect3DDevice7_GetRenderTarget",2},//9
	{"IDirect3DDevice7_Clear",7},//10
	{"IDirect3DDevice7_SetTransform",3},//11
	{"IDirect3DDevice7_GetTransform",3},//12
	{"IDirect3DDevice7_SetViewport",2},//13
	{"IDirect3DDevice7_MultiplyTransform",3},//14
	{"IDirect3DDevice7_GetViewport",2},//15
	{"IDirect3DDevice7_SetMaterial",2},//16
	{"IDirect3DDevice7_GetMaterial",2},//17
	{"IDirect3DDevice7_SetLight",3},//18
	{"IDirect3DDevice7_GetLight",3},//19
	{"IDirect3DDevice7_SetRenderState",3},//20
	{"IDirect3DDevice7_GetRenderState",3},//21
	{"IDirect3DDevice7_BeginStateBlock",1},//22
	{"IDirect3DDevice7_EndStateBlock",2},//23
	{"IDirect3DDevice7_PreLoad",2},//24
	{"IDirect3DDevice7_DrawPrimitive",6},//25
	{"IDirect3DDevice7_DrawIndexedPrimitive",8},//26
	{"IDirect3DDevice7_SetClipStatus",2},//27
	{"IDirect3DDevice7_GetClipStatus",2},//28
	{"IDirect3DDevice7_DrawPrimitiveStrided",6},//29
	{"IDirect3DDevice7_DrawIndexedPrimitiveStrided",8},//30
	{"IDirect3DDevice7_DrawPrimitiveVB",6},//31
	{"IDirect3DDevice7_DrawIndexedPrimitiveVB",8},//32
	{"IDirect3DDevice7_ComputeSphereVisibility",6},//33
	{"IDirect3DDevice7_GetTexture",3},//34
	{"IDirect3DDevice7_SetTexture",3},//35
	{"IDirect3DDevice7_GetTextureStageState",4},//36
	{"IDirect3DDevice7_SetTextureStageState",4},//37
	{"IDirect3DDevice7_ValidateDevice",2},//38
	{"IDirect3DDevice7_ApplyStateBlock",2},//39
	{"IDirect3DDevice7_CaptureStateBlock",2},//40
	{"IDirect3DDevice7_DeleteStateBlock",2},//41
	{"IDirect3DDevice7_CreateStateBlock",3},//42
	{"IDirect3DDevice7_Load",6},//43
	{"IDirect3DDevice7_LightEnable",3},//44
	{"IDirect3DDevice7_GetLightEnable",3},//45
	{"IDirect3DDevice7_SetClipPlane",3},//46
	{"IDirect3DDevice7_GetClipPlane",3},//47
	{"IDirect3DDevice7_GetInfo",4}//48
};

DWORD __stdcall before_IUnknown_QueryInterface(SPROXYENTRYSTRUCT* pEntry){	
	DWORD retv = ((PFN_F3)GetUnhookedFuncAddrById(pEntry->funcid))(
		pEntry->parameters[0],
		pEntry->parameters[1],
		pEntry->parameters[2]
	);

	HookByIID((LPCVOID)pEntry->parameters[1], (LPCVOID)pEntry->parameters[2]);
	pEntry->eax=(DWORD)retv;
	return (DWORD)stub_3;
}

void Hook_IDirect3DDevice7(DWORD* p){
	static int fNotFirst = 0;

	if(!fNotFirst){
		fNotFirst = 1;
		for(DWORD i = 0; i < 49; i++){
			DWORD MethodAddress = GetMethodAddr((DWORD**)*p, i);
			SFUNCTION finfo={0};
			if(i==0){
				finfo.BeforeFunc = (PPLUG_BEFORE)before_IUnknown_QueryInterface;
			}
			finfo.pName = table_IDirect3DDevice7[i].pName;
			finfo.params= table_IDirect3DDevice7[i].Params;
			SetHook(MethodAddress, &finfo);
		}
	}
}

DWORD __stdcall before_IDirectDraw7_CreateSurface(SPROXYENTRYSTRUCT* pEntry){	
	DWORD retv = ((PFN_F4)GetUnhookedFuncAddrById(pEntry->funcid))(
		pEntry->parameters[0],
		pEntry->parameters[1],
		pEntry->parameters[2],
		pEntry->parameters[3]
		);

		Hook_IDirectDrawSurface7((DWORD*)pEntry->parameters[2]);

		pEntry->eax=(DWORD)retv;
		return (DWORD)stub_4;
}

DWORD __stdcall before_IDirect3D7_CreateDevice(SPROXYENTRYSTRUCT* pEntry){
	HRESULT retv = ((PFN_F4)GetUnhookedFuncAddrById(pEntry->funcid))(
		pEntry->parameters[0],
		pEntry->parameters[1],
		pEntry->parameters[2],
		pEntry->parameters[3]
		);

		//Set hook to IDirect3DDevice7 interface
		if(pEntry->parameters[3])
			Hook_IDirect3DDevice7((DWORD*)pEntry->parameters[3]);

		pEntry->eax=(DWORD)retv;//Save return value for future use
		return (DWORD)stub_4;
}

void Hook_IDirectDraw7(DWORD* p){
	static int fNotFirst = 0;

	if(!fNotFirst){
		fNotFirst = 1;
		for(DWORD i = 0; i < 30; i++){
			SFUNCTION finfo={0};
			if(i==0){
				finfo.BeforeFunc = (PPLUG_BEFORE)before_IUnknown_QueryInterface;
			}
			else if(i==6){//IDirectDraw7_CreateSurface
				finfo.BeforeFunc = (PPLUG_BEFORE)before_IDirectDraw7_CreateSurface;
			}
			DWORD MethodAddress = GetMethodAddr((DWORD**)*p, i);
			finfo.pName = table_IDirectDraw7[i].pName;
			finfo.params= table_IDirectDraw7[i].Params;
			SetHook(MethodAddress, &finfo);
		}
	}
}

void Hook_IDirect3D7(DWORD* p){
	static int fNotFirst = 0;

	if(!fNotFirst){
		fNotFirst = 1;
		for(DWORD i = 0; i < 8; i++){
			SFUNCTION finfo={0};
			if(i==0){
				finfo.BeforeFunc = (PPLUG_BEFORE)before_IUnknown_QueryInterface;
			}
			else if(i==4){
				finfo.BeforeFunc=(PPLUG_BEFORE)before_IDirect3D7_CreateDevice;
			}
			DWORD MethodAddress = GetMethodAddr((DWORD**)*p, i);
			finfo.pName = table_IDirect3D7[i].pName;
			finfo.params= table_IDirect3D7[i].Params;
			SetHook(MethodAddress, &finfo);
		}
	}
}

void Hook_IDirectDrawSurface7(DWORD* p){
	static int fNotFirst = 0;

	if(!fNotFirst){
		fNotFirst = 1;
		for(DWORD i = 0; i < 49; i++){
			SFUNCTION finfo={0};
			if(i==0){
				finfo.BeforeFunc = (PPLUG_BEFORE)before_IUnknown_QueryInterface;
			}

			DWORD MethodAddress = GetMethodAddr((DWORD**)*p, i);
			finfo.pName = table_IDirectDrawSurface7[i].pName;
			finfo.params= table_IDirectDrawSurface7[i].Params;
			SetHook(MethodAddress, &finfo);
		}
	}
}

void Hook_IDirectDrawSurface(DWORD* p){
	static int fNotFirst = 0;

	if(!fNotFirst){
		fNotFirst = 1;
		for(DWORD i = 0; i < 36; i++){
			SFUNCTION finfo={0};
			if(i==0){
				finfo.BeforeFunc = (PPLUG_BEFORE)before_IUnknown_QueryInterface;
			}

			DWORD MethodAddress = GetMethodAddr((DWORD**)*p, i);
			finfo.pName = table_IDirectDrawSurface[i].pName;
			finfo.params= table_IDirectDrawSurface[i].Params;
			SetHook(MethodAddress, &finfo);
		}
	}
}


void Hook_IDirectDraw(DWORD* p){
	static int fNotFirst = 0;

	if(!fNotFirst){
		fNotFirst = 1;
		for(DWORD i = 0; i < 23; i++){
			SFUNCTION finfo={0};
			if(i==0){
				finfo.BeforeFunc = (PPLUG_BEFORE)before_IUnknown_QueryInterface;
			}

			DWORD MethodAddress = GetMethodAddr((DWORD**)*p, i);
			finfo.pName = table_IDirectDraw[i].pName;
			finfo.params= table_IDirectDraw[i].Params;
			SetHook(MethodAddress, &finfo);
		}
	}
}


void Hook_IDirectDraw2(DWORD* p){
	static int fNotFirst = 0;

	if(!fNotFirst){
		fNotFirst = 1;
		for(DWORD i = 0; i < 24; i++){
			SFUNCTION finfo={0};
			if(i==0){
				finfo.BeforeFunc = (PPLUG_BEFORE)before_IUnknown_QueryInterface;
			}

			DWORD MethodAddress = GetMethodAddr((DWORD**)*p, i);
			finfo.pName = table_IDirectDraw2[i].pName;
			finfo.params= table_IDirectDraw2[i].Params;
			SetHook(MethodAddress, &finfo);
		}
	}
}


void Hook_IDirectDraw4(DWORD* p){
	static int fNotFirst = 0;

	if(!fNotFirst){
		fNotFirst = 1;
		for(DWORD i = 0; i < 28; i++){
			SFUNCTION finfo={0};
			if(i==0){
				finfo.BeforeFunc = (PPLUG_BEFORE)before_IUnknown_QueryInterface;
			}

			DWORD MethodAddress = GetMethodAddr((DWORD**)*p, i);
			finfo.pName = table_IDirectDraw4[i].pName;
			finfo.params= table_IDirectDraw4[i].Params;
			SetHook(MethodAddress, &finfo);
		}
	}
}

void Hook_IDirectDrawSurface2(DWORD* p){
	static int fNotFirst = 0;

	if(!fNotFirst){
		fNotFirst = 1;
		for(DWORD i = 0; i < 39; i++){
			SFUNCTION finfo={0};
			if(i==0){
				finfo.BeforeFunc = (PPLUG_BEFORE)before_IUnknown_QueryInterface;
			}

			DWORD MethodAddress = GetMethodAddr((DWORD**)*p, i);
			finfo.pName = table_IDirectDrawSurface2[i].pName;
			finfo.params= table_IDirectDrawSurface2[i].Params;
			SetHook(MethodAddress, &finfo);
		}
	}
}


void Hook_IDirectDrawSurface3(DWORD* p){
	static int fNotFirst = 0;

	if(!fNotFirst){
		fNotFirst = 1;
		for(DWORD i = 0; i < 40; i++){
			SFUNCTION finfo={0};
			if(i==0){
				finfo.BeforeFunc = (PPLUG_BEFORE)before_IUnknown_QueryInterface;
			}

			DWORD MethodAddress = GetMethodAddr((DWORD**)*p, i);
			finfo.pName = table_IDirectDrawSurface3[i].pName;
			finfo.params= table_IDirectDrawSurface3[i].Params;
			SetHook(MethodAddress, &finfo);
		}
	}
}

void Hook_IDirectDrawSurface4(DWORD* p){
	static int fNotFirst = 0;

	if(!fNotFirst){
		fNotFirst = 1;
		for(DWORD i = 0; i < 45; i++){
			SFUNCTION finfo={0};
			if(i==0){
				finfo.BeforeFunc = (PPLUG_BEFORE)before_IUnknown_QueryInterface;
			}

			DWORD MethodAddress = GetMethodAddr((DWORD**)*p, i);
			finfo.pName = table_IDirectDrawSurface4[i].pName;
			finfo.params= table_IDirectDrawSurface4[i].Params;
			SetHook(MethodAddress, &finfo);
		}
	}
}


void Hook_IDirect3DDevice(DWORD* p){
	static int fNotFirst = 0;

	if(!fNotFirst){
		fNotFirst = 1;
		for(DWORD i = 0; i < 22; i++){
			SFUNCTION finfo={0};
			if(i==0){
				finfo.BeforeFunc = (PPLUG_BEFORE)before_IUnknown_QueryInterface;
			}

			DWORD MethodAddress = GetMethodAddr((DWORD**)*p, i);
			finfo.pName = table_IDirect3DDevice[i].pName;
			finfo.params= table_IDirect3DDevice[i].Params;
			SetHook(MethodAddress, &finfo);
		}
	}
}

void Hook_IDirect3DDevice2(DWORD* p){
	static int fNotFirst = 0;

	if(!fNotFirst){
		fNotFirst = 1;
		for(DWORD i = 0; i < 33; i++){
			SFUNCTION finfo={0};
			if(i==0){
				finfo.BeforeFunc = (PPLUG_BEFORE)before_IUnknown_QueryInterface;
			}

			DWORD MethodAddress = GetMethodAddr((DWORD**)*p, i);
			finfo.pName = table_IDirect3DDevice2[i].pName;
			finfo.params= table_IDirect3DDevice2[i].Params;
			SetHook(MethodAddress, &finfo);
		}
	}
}

void Hook_IDirect3DDevice3(DWORD* p){
	static int fNotFirst = 0;

	if(!fNotFirst){
		fNotFirst = 1;
		for(DWORD i = 0; i < 42; i++){
			SFUNCTION finfo={0};
			if(i==0){
				finfo.BeforeFunc = (PPLUG_BEFORE)before_IUnknown_QueryInterface;
			}

			DWORD MethodAddress = GetMethodAddr((DWORD**)*p, i);
			finfo.pName = table_IDirect3DDevice3[i].pName;
			finfo.params= table_IDirect3DDevice3[i].Params;
			SetHook(MethodAddress, &finfo);
		}
	}
}

void Hook_IDirect3D(DWORD* p){
	static int fNotFirst = 0;

	if(!fNotFirst){
		fNotFirst = 1;
		for(DWORD i = 0; i < 9; i++){
			SFUNCTION finfo={0};
			if(i==0){
				finfo.BeforeFunc = (PPLUG_BEFORE)before_IUnknown_QueryInterface;
			}

			DWORD MethodAddress = GetMethodAddr((DWORD**)*p, i);
			finfo.pName = table_IDirect3D[i].pName;
			finfo.params= table_IDirect3D[i].Params;
			SetHook(MethodAddress, &finfo);
		}
	}
}

void Hook_IDirect3D2(DWORD* p){
	static int fNotFirst = 0;

	if(!fNotFirst){
		fNotFirst = 1;
		for(DWORD i = 0; i < 9; i++){
			SFUNCTION finfo={0};
			if(i==0){
				finfo.BeforeFunc = (PPLUG_BEFORE)before_IUnknown_QueryInterface;
			}

			DWORD MethodAddress = GetMethodAddr((DWORD**)*p, i);
			finfo.pName = table_IDirect3D2[i].pName;
			finfo.params= table_IDirect3D2[i].Params;
			SetHook(MethodAddress, &finfo);
		}
	}
}

void Hook_IDirect3D3(DWORD* p){
	static int fNotFirst = 0;

	if(!fNotFirst){
		fNotFirst = 1;
		for(DWORD i = 0; i < 12; i++){
			SFUNCTION finfo={0};
			if(i==0){
				finfo.BeforeFunc = (PPLUG_BEFORE)before_IUnknown_QueryInterface;
			}

			DWORD MethodAddress = GetMethodAddr((DWORD**)*p, i);
			finfo.pName = table_IDirect3D3[i].pName;
			finfo.params= table_IDirect3D3[i].Params;
			SetHook(MethodAddress, &finfo);
		}
	}
}

//d3d8
DWORD __stdcall before_IDirect3D8_CreateDevice(SPROXYENTRYSTRUCT* pEntry){
	HRESULT retv = ((PFN_F7)GetUnhookedFuncAddrById(pEntry->funcid))(
		pEntry->parameters[0],
		pEntry->parameters[1],
		pEntry->parameters[2],
		pEntry->parameters[3],
		pEntry->parameters[4],
		pEntry->parameters[5],
		pEntry->parameters[6]
		);

		//Set hook to IDirect3DDevice8 interface
		if(pEntry->parameters[6])
			Hook_IDirect3DDevice8((DWORD*)pEntry->parameters[6]);

		pEntry->eax=(DWORD)retv;//Save return value for future use
		return (DWORD)stub_7;
}

void Hook_IDirect3D8(DWORD* p){
	static int fNotFirst = 0;

	if(!fNotFirst){
		fNotFirst = 1;
		for(DWORD i = 0; i < 16; i++){
			SFUNCTION finfo={0};
			if(i==0){
				finfo.BeforeFunc = (PPLUG_BEFORE)before_IUnknown_QueryInterface;
			}
			else if(i==15){
				finfo.BeforeFunc = (PPLUG_BEFORE)before_IDirect3D8_CreateDevice;
			}
			DWORD MethodAddress = GetMethodAddr((DWORD**)*p, i);
			finfo.pName = table_IDirect3D8[i].pName;
			finfo.params= table_IDirect3D8[i].Params;
			SetHook(MethodAddress, &finfo);
		}
	}
}

void Hook_IDirect3DDevice8(DWORD* p){
	static int fNotFirst = 0;

	if(!fNotFirst){
		fNotFirst = 1;
		for(DWORD i = 0; i < 97; i++){
			SFUNCTION finfo={0};
			if(i==0){
				finfo.BeforeFunc = (PPLUG_BEFORE)before_IUnknown_QueryInterface;
			}

			DWORD MethodAddress = GetMethodAddr((DWORD**)*p, i);
			finfo.pName = table_IDirect3DDevice8[i].pName;
			finfo.params= table_IDirect3DDevice8[i].Params;
			SetHook(MethodAddress, &finfo);
		}
	}
}

void Hook_IDirect3DSwapChain8(DWORD* p){
	static int fNotFirst = 0;

	if(!fNotFirst){
		fNotFirst = 1;
		for(DWORD i = 0; i < 5; i++){
			SFUNCTION finfo={0};
			if(i==0){
				finfo.BeforeFunc = (PPLUG_BEFORE)before_IUnknown_QueryInterface;
			}

			DWORD MethodAddress = GetMethodAddr((DWORD**)*p, i);
			finfo.pName = table_IDirect3DSwapChain8[i].pName;
			finfo.params= table_IDirect3DSwapChain8[i].Params;
			SetHook(MethodAddress, &finfo);
		}
	}
}

void Hook_IDirect3DResource8(DWORD* p){
	static int fNotFirst = 0;

	if(!fNotFirst){
		fNotFirst = 1;
		for(DWORD i = 0; i < 11; i++){
			SFUNCTION finfo={0};
			if(i==0){
				finfo.BeforeFunc = (PPLUG_BEFORE)before_IUnknown_QueryInterface;
			}

			DWORD MethodAddress = GetMethodAddr((DWORD**)*p, i);
			finfo.pName = table_IDirect3DResource8[i].pName;
			finfo.params= table_IDirect3DResource8[i].Params;
			SetHook(MethodAddress, &finfo);
		}
	}
}

void Hook_IDirect3DBaseTexture8(DWORD* p){
	static int fNotFirst = 0;

	if(!fNotFirst){
		fNotFirst = 1;
		for(DWORD i = 0; i < 14; i++){
			SFUNCTION finfo={0};
			if(i==0){
				finfo.BeforeFunc = (PPLUG_BEFORE)before_IUnknown_QueryInterface;
			}

			DWORD MethodAddress = GetMethodAddr((DWORD**)*p, i);
			finfo.pName = table_IDirect3DBaseTexture8[i].pName;
			finfo.params= table_IDirect3DBaseTexture8[i].Params;
			SetHook(MethodAddress, &finfo);
		}
	}
}

void Hook_IDirect3DVolumeTexture8(DWORD* p){
	static int fNotFirst = 0;

	if(!fNotFirst){
		fNotFirst = 1;
		for(DWORD i = 0; i < 19; i++){
			SFUNCTION finfo={0};
			if(i==0){
				finfo.BeforeFunc = (PPLUG_BEFORE)before_IUnknown_QueryInterface;
			}

			DWORD MethodAddress = GetMethodAddr((DWORD**)*p, i);
			finfo.pName = table_IDirect3DVolumeTexture8[i].pName;
			finfo.params= table_IDirect3DVolumeTexture8[i].Params;
			SetHook(MethodAddress, &finfo);
		}
	}
}

void Hook_IDirect3DCubeTexture8(DWORD* p){
	static int fNotFirst = 0;

	if(!fNotFirst){
		fNotFirst = 1;
		for(DWORD i = 0; i < 19; i++){
			SFUNCTION finfo={0};
			if(i==0){
				finfo.BeforeFunc = (PPLUG_BEFORE)before_IUnknown_QueryInterface;
			}

			DWORD MethodAddress = GetMethodAddr((DWORD**)*p, i);
			finfo.pName = table_IDirect3DCubeTexture8[i].pName;
			finfo.params= table_IDirect3DCubeTexture8[i].Params;
			SetHook(MethodAddress, &finfo);
		}
	}
}

void Hook_IDirect3DVertexBuffer8(DWORD* p){
	static int fNotFirst = 0;

	if(!fNotFirst){
		fNotFirst = 1;
		for(DWORD i = 0; i < 14; i++){
			SFUNCTION finfo={0};
			if(i==0){
				finfo.BeforeFunc = (PPLUG_BEFORE)before_IUnknown_QueryInterface;
			}

			DWORD MethodAddress = GetMethodAddr((DWORD**)*p, i);
			finfo.pName = table_IDirect3DVertexBuffer8[i].pName;
			finfo.params= table_IDirect3DVertexBuffer8[i].Params;
			SetHook(MethodAddress, &finfo);
		}
	}
}

void Hook_IDirect3DIndexBuffer8(DWORD* p){
	static int fNotFirst = 0;

	if(!fNotFirst){
		fNotFirst = 1;
		for(DWORD i = 0; i < 14; i++){
			SFUNCTION finfo={0};
			if(i==0){
				finfo.BeforeFunc = (PPLUG_BEFORE)before_IUnknown_QueryInterface;
			}

			DWORD MethodAddress = GetMethodAddr((DWORD**)*p, i);
			finfo.pName = table_IDirect3DIndexBuffer8[i].pName;
			finfo.params= table_IDirect3DIndexBuffer8[i].Params;
			SetHook(MethodAddress, &finfo);
		}
	}
}
void Hook_IDirect3DSurface8(DWORD* p){
	static int fNotFirst = 0;

	if(!fNotFirst){
		fNotFirst = 1;
		for(DWORD i = 0; i < 11; i++){
			SFUNCTION finfo={0};
			if(i==0){
				finfo.BeforeFunc = (PPLUG_BEFORE)before_IUnknown_QueryInterface;
			}

			DWORD MethodAddress = GetMethodAddr((DWORD**)*p, i);
			finfo.pName = table_IDirect3DSurface8[i].pName;
			finfo.params= table_IDirect3DSurface8[i].Params;
			SetHook(MethodAddress, &finfo);
		}
	}
}

void Hook_IDirect3DVolume8(DWORD* p){
	static int fNotFirst = 0;

	if(!fNotFirst){
		fNotFirst = 1;
		for(DWORD i = 0; i < 11; i++){
			SFUNCTION finfo={0};
			if(i==0){
				finfo.BeforeFunc = (PPLUG_BEFORE)before_IUnknown_QueryInterface;
			}

			DWORD MethodAddress = GetMethodAddr((DWORD**)*p, i);
			finfo.pName = table_IDirect3DVolume8[i].pName;
			finfo.params= table_IDirect3DVolume8[i].Params;
			SetHook(MethodAddress, &finfo);
		}
	}
}


//////////////////////////////////////////////////////////////////////////

//d3d9.dll
void Hook_IDirect3D9(DWORD* p){
	static int fNotFirst = 0;

	if(!fNotFirst){
		fNotFirst = 1;
		for(DWORD i = 0; i < 17; i++){
			SFUNCTION finfo={0};
			if(i==0){
				finfo.BeforeFunc = (PPLUG_BEFORE)before_IUnknown_QueryInterface;
			}
			else if(i==16){
				finfo.BeforeFunc = (PPLUG_BEFORE)before_IDirect3D9_CreateDevice;
			}
			DWORD MethodAddress = GetMethodAddr((DWORD**)*p, i);
			finfo.pName = table_IDirect3D9[i].pName;
			finfo.params= table_IDirect3D9[i].Params;
			SetHook(MethodAddress, &finfo);
		}
	}
}


DWORD __stdcall before_IDirect3D9_CreateDevice(SPROXYENTRYSTRUCT* pEntry){
	HRESULT retv = ((PFN_F7)GetUnhookedFuncAddrById(pEntry->funcid))(
		pEntry->parameters[0],
		pEntry->parameters[1],
		pEntry->parameters[2],
		pEntry->parameters[3],
		pEntry->parameters[4],
		pEntry->parameters[5],
		pEntry->parameters[6]
		);

	if(retv==0){//Not set hook, if IDirect3D9::CreateDevice return error
		//Set hook to IDirect3DDevice9 interface
		if(pEntry->parameters[6])
			Hook_IDirect3DDevice9((DWORD*)pEntry->parameters[6]);
	}
	pEntry->eax=(DWORD)retv;//Save return value for future use
	return (DWORD)stub_7;
}
void Hook_IDirect3DDevice9(DWORD* p){
	static int fNotFirst = 0;

	if(!fNotFirst){
		fNotFirst = 1;
		for(DWORD i = 0; i < 119; i++){
			SFUNCTION finfo={0};
			if(i==0){
				finfo.BeforeFunc = (PPLUG_BEFORE)before_IUnknown_QueryInterface;
			}

			DWORD MethodAddress = GetMethodAddr((DWORD**)*p, i);
			finfo.pName = table_IDirect3DDevice9[i].pName;
			finfo.params= table_IDirect3DDevice9[i].Params;
			SetHook(MethodAddress, &finfo);
		}
	}
}
