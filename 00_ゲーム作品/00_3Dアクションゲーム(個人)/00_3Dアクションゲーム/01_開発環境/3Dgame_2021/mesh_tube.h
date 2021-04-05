#ifndef _MESH_TUBE_H_
#define _MESH_TUBE_H_
//=====================================================
//
// 立体メッシュの生成クラスヘッダー [mesh_tube.h]
// Author : Konishi Yuuto
//
//=====================================================

//=============================================================================
// インクルードファイル
//=============================================================================
#include "main.h"
#include "mesh_3d.h"

//=============================================================================
// 円柱のクラス
//=============================================================================
class CMeshTube : public CMesh3d
{
public:
	CMeshTube(PRIORITY Priority = PRIORITY_0);			// コンストラクタ
	~CMeshTube();										// デストラクタ

	 HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);	// 初期化処理
	 void Uninit(void);									// 終了処理
	 void Update(void);									// 更新処理
	 void Draw(void);									// 描画処理

	static CMeshTube*Create(D3DXVECTOR3 pos,
		MESH_TYPE MeshNum);								// インスタンス生成

private:
};

#endif