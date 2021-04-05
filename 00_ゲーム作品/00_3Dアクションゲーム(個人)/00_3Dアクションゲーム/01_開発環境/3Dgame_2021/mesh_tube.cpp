//=============================================================================
//
// 円柱メッシュクラス [mesh_tube.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "mesh_tube.h"
#include "renderer.h"
#include "manager.h"
#include "texture.h"
#include "resource_manager.h"

//=============================================================================
// コンストラクタ
//=============================================================================
CMeshTube::CMeshTube(PRIORITY Priority) :CMesh3d(Priority)
{

}

//=============================================================================
// デストラクタ
//=============================================================================
CMeshTube::~CMeshTube()
{
}

//=============================================================================
// ポリゴン生成
//=============================================================================
CMeshTube * CMeshTube::Create(D3DXVECTOR3 pos, MESH_TYPE MeshNum)
{
	// メモリ確保
	CMeshTube *pMeshCylinder = new CMeshTube;
	CTexture *pTexture = CManager::GetResourceManager()->GetTextureClass();

	// 初期化処理
	if (pMeshCylinder != nullptr)
	{
		pMeshCylinder->SetMeshNum(MeshNum);												// 何角形か
		pMeshCylinder->Init(pos, ZeroVector3);											// 座標・サイズ
		pMeshCylinder->BindTexture(pTexture->GetTexture(CTexture::TEXTURE_NUM_FLOOR));	// テクスチャ設定
	}

	return pMeshCylinder;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CMeshTube::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// Rendererクラスからデバイスを取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	VERTEX_3D *pVtx;

	// ローカル変数
	int nCount = 0;			// for文用
	int nCntIndex = 0;		// 頂点の生成番号
	int nCntH = 0;			// 縦の頂点カウンタ
	int nCntV = 0;			// 横の頂点カウンタ

	// 頂点の数
	int nWidth = GetMesh3D(GetMeshNum()).CylinderNum.nNumX;
	int nHeight = GetMesh3D(GetMeshNum()).CylinderNum.nNumY;

	// メッシュのサイズ設定
	D3DXVECTOR2 MeshSize = D3DXVECTOR2(GetMesh3D(GetMeshNum()).size.x, GetMesh3D(GetMeshNum()).size.y);

	// 値の初期化
	SetNumVertex((nWidth + 1) * (nHeight + 1));
	SetNumIndex((nWidth + 1) * nHeight * 2 + (nHeight - 1) * 2);					// 5*(4*2)+3*2	46

	SetNumPolygon(nWidth * nHeight * 2 + (nWidth - 1) * 4); 						// 4*8+3*4	44	36
	
	D3DXVECTOR2 OneSize = D3DXVECTOR2(MeshSize.x * 2 / nWidth, MeshSize.y * 2 / nHeight);
	SetOneSize(OneSize);		// 24000/4

	// バッファの宣言
	LPDIRECT3DVERTEXBUFFER9 pVtxBuff = nullptr;
	LPDIRECT3DINDEXBUFFER9 pIdxBuff = nullptr;

	// オブジェクトの頂点バッファを生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * GetNumVertex(),
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&pVtxBuff,
		nullptr);

	// インデックスバッファ生成
	pDevice->CreateIndexBuffer(sizeof(WORD) * GetNumIndex(),
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&pIdxBuff,
		nullptr);

	// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
	pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntV = 0; nCntV < nHeight + 1; nCntV++)
	{
		for (nCntH = 0; nCntH < nWidth + 1; nCntH++)
		{
			// 頂点の設定
			pVtx[(nCntV * (nWidth + 1)) + nCntH].pos = D3DXVECTOR3(
				pos.x + MeshSize.x*cosf(D3DXToRadian((360 / (nWidth))*nCntH)),
				pos.y + (nCntV * MeshSize.y),
				pos.z + MeshSize.x*sinf(D3DXToRadian((360 / (nWidth))*nCntH)));

			// 法線ベクトルの設定
			pVtx[(nCntV * (nWidth + 1)) + nCntH].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

			// 色の設定
			pVtx[(nCntV * (nWidth + 1)) + nCntH].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			// テクスチャ座標の設定
			pVtx[(nCntV * (nWidth + 1)) + nCntH].tex = D3DXVECTOR2(float(nCntH), float(nCntV));
		}
	}

	// 頂点データをアンロックする
	pVtxBuff->Unlock();

	// バッファ情報を渡す
	BindVtxBuff(pVtxBuff);

	// インデックスバッファの設定
	WORD *pIdx;

	// インデックスバッファをロックし、インデックスデータへのポインタを取得
	pIdxBuff->Lock(0, 0, (void**)&pIdx, 0);

	// インデックス数
	int nNumIndex = GetNumIndex();
	for (nCount = 0, nCntIndex = 0; nCount < nNumIndex; nCount += 2)
	{
		if (((nCount + 2) % (((nWidth + 1) * 2) + 2)) == 0 && nCount != 0)
		{
			// インデックスの設定
			pIdx[nCount] = nCntIndex - 1;

			// インデックスの設定
			pIdx[nCount + 1] = nWidth + nCntIndex + 1;
		}
		else
		{
			// インデックスの設定
			pIdx[nCount] = nWidth + nCntIndex + 1;

			// インデックスの設定
			pIdx[nCount + 1] = nCntIndex;

			nCntIndex++;
		}

	}

	// 頂点データをアンロックする
	pIdxBuff->Unlock();

	// インデックスバッファを渡す
	BindIdxBuff(pIdxBuff);

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CMeshTube::Uninit(void)
{
	// 削除フラグ
	Release();
}

//=============================================================================
// 更新処理
//=============================================================================
void CMeshTube::Update(void)
{

}

//=============================================================================
// 描画処理
//=============================================================================
void CMeshTube::Draw(void)
{
	// 親クラス描画処理
	CMesh3d::Draw();
}