//#include "Shadow.h"
//
//extern int g_ModelHandles[MaxModelKindNum];
//
//extern int g_ShadowMapHandles[ShadowMapTypeMax];
//
//void LoadShadow()
//{
//	// ライトの初期化
//	InitializedLight();
//
//	// シャドウマップの初期化
//	InitializedShadowMap();
//
//	// Ｚバッファに対する描画を有効にする
//	EnableZbuffer(g_ModelHandles[2], g_ModelHandles[0]);
//
//	// ゲーム開始前の初期化でやるべきことはここより上に書く
//	MV1SetupCollInfo(g_ModelHandles[2], -1, 10, 10, 10);
//}
//
//void InitializedLight()
//{
//	SetUseLighting(true);
//	SetLightEnable(true);
//	SetGlobalAmbientLight(GetColorF(1.0f, 1.0f, 1.0f, 1.0f));
//	ChangeLightTypeDir(g_LightDir);
//	SetLightDifColor(GetColorF(1.0f, 1.0f, 1.0f, 1.0f));
//	SetLightAmbColor(GetColorF(0.2f, 0.2f, 0.2f, 1.0f));
//
//}
//
//void InitializedShadowMap()
//{	
//	int map_size = 2048;
//	g_ShadowMapHandles[(int)ShadowMapType::Stage] = MakeShadowMap(map_size, map_size);
//	g_ShadowMapHandles[(int)ShadowMapType::Chara] = MakeShadowMap(map_size, map_size);
//	SetShadowMapDrawArea(g_ShadowMapHandles[(int)ShadowMapType::Stage],
//		VGet(-500.0f, -10.0f, -500.0f), VGet(500.0f, 500.0f, 500.0f));
//
//	SetShadowMapDrawArea(g_ShadowMapHandles[(int)ShadowMapType::Chara],
//		VGet(-10.0f, -10.0f, -10.0f), VGet(10.0f, 10.0f, 10.0f));
//	SetShadowMapLightDirection(g_ShadowMapHandles[(int)ShadowMapType::Stage], g_LightDir);
//	SetShadowMapLightDirection(g_ShadowMapHandles[(int)ShadowMapType::Chara], g_LightDir);
//
//}
//
//void EnableZbuffer(int stage_handle_, int miku_handle_)
//{
//	SetUseZBufferFlag(TRUE);
//	SetWriteZBufferFlag(TRUE);
//	MV1SetWriteZBuffer(stage_handle_, true);
//	MV1SetWriteZBuffer(miku_handle_, true);
//}
