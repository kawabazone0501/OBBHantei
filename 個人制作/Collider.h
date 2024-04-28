#pragma once

#include "Common.h"
#include <vector>
#include <utility>

/*
	OBBは8つの頂点座標で疑似的な直方体を作り対応する

	１．辺の長さ１の立方体を作る
	２．変換行列を作る
	３．１の立方体の頂点 * 変換行列で直方体の頂点座標を求める
*/
// OBB構造体
struct OBBCollider
{
public:
	static constexpr int MaxVertex = 8;

	OBBCollider(Vec3 pos_, Vec3 size_, Vec3 angle_);

	//変更関数
	void ChangePos(Vec3& pos_);
	void ChangeAngle(Vec3& angle_);
	void ChangeSize(Vec3& size_);
	void ChangeParentMatrix(MATRIX& parent_mat);

	//OBBからローカル軸を取得する
	void GetAxis(Vec3& x_axis, Vec3& y_axis_, Vec3& z_axis_);
	void GetAxis(Axis& axis_);

#if defined(DEBUG)
	//ワイヤーフレームで描画
	void Draw();
#endif

public:
	//現在の頂点座標
	Vec3 currentVertices[MaxVertex]{};

private:
	//行列更新
	void UpDate();

	MATRIX translateMat{ MGetIdent() };	// 平行移動行列
	MATRIX rotateMat{ MGetIdent() };	// 回転行列
	MATRIX scaleMat{ MGetIdent() };		// 拡縮行列		
	MATRIX transformMat{ MGetIdent() };	// 変換行列
	MATRIX parentMat{ MGetIdent() };	// 親の変換行列
};