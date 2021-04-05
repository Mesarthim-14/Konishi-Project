//=============================================================================
//
// 岩の生成クラス [stone_effect.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "stone_effect.h"
#include "manager.h"
#include "renderer.h"
#include "particle.h"
#include "texture.h"
#include "stone.h"
#include "xfile.h"
#include "effect_factory.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define STONE_TEXTURE_NAME	("data/Text/stone_effect.txt")	// ファイルの名前
#define STONE_EFFECT_RADIAN	(400.0f)						// 岩のエフェクトの半径

//=============================================================================
// static初期化
//=============================================================================
CStoneEffect::STONE CStoneEffect::m_Stone[STONE_NUM_MAX] = {};			// パーティクル

//=============================================================================
// コンストラクタ
//=============================================================================
CStoneEffect::CStoneEffect()
{

}

//=============================================================================
// デストラクタ
//=============================================================================
CStoneEffect::~CStoneEffect()
{

}

//=============================================================================
// 岩のエフェクト生成
//=============================================================================
void CStoneEffect::CreateStone(D3DXVECTOR3 pos)
{
	// 岩の種類のfor分
	for (int nStoneCnt = 0; nStoneCnt < STONE_NUM_MAX; nStoneCnt++)
	{
		// 岩の個数分回す
		for (int nCount = 0; nCount < m_Stone[nStoneCnt].nNum; nCount++)
		{
			D3DXVECTOR3 TargetPos = D3DXVECTOR3(
				pos.x + STONE_EFFECT_RADIAN * cosf(D3DXToRadian(nCount * 360 / m_Stone[nStoneCnt].nNum)),
				pos.y,
				pos.z + STONE_EFFECT_RADIAN * sinf(D3DXToRadian(nCount * 360 / m_Stone[nStoneCnt].nNum)));

			D3DXVECTOR3 move = D3DXVECTOR3(
				cosf(D3DXToRadian(360 / m_Stone[nStoneCnt].nNum *nCount)) *m_Stone[nStoneCnt].move.x,
				(float)(rand() % (int)m_Stone[nStoneCnt].move.y + rand() % (int)m_Stone[nStoneCnt].move.y),
				sinf(D3DXToRadian(nCount * (360 / m_Stone[nStoneCnt].nNum)))*m_Stone[nStoneCnt].move.z);

			// 岩の生成
			CStone::Create(pos, move, m_Stone[nStoneCnt], (CXfile::XFILE_NUM)((int)CXfile::XFILE_NUM_STONE_000 + nStoneCnt));
		}
	}

	// 土煙エフェクトの生成
	CEffectFactory::CreateEffect(pos, CEffectFactory::EFFECT_NUM_SAND_SMOKE);
}

//=============================================================================
// 岩のファイル読み込み
//=============================================================================
HRESULT CStoneEffect::ReadFile(void)
{
	FILE *pFile = NULL;		//FILEポインタ
	char aHeadData[1024];
	char aStoneName[1024];
	int nStoneIndex = 0;	// モデルのインデックス

	// ファイルオープン
	pFile = fopen(STONE_TEXTURE_NAME, "r");

	if (pFile != NULL)
	{
		do
		{
			//一列読み込んでモード情報を抽出
			fgets(aHeadData, sizeof(aHeadData), pFile);
			sscanf(aHeadData, "%s", aStoneName);

			if (strcmp(aStoneName, "STONESET") == 0)
			{
				//インデックスを最初に戻す
				nStoneIndex = 0;

				//END_MOTIONSETを読み込むまで繰り返す
				while (strcmp(aStoneName, "END_STONESET") != 0)
				{
					//一列読み込んでモード情報を抽出
					fgets(aHeadData, sizeof(aHeadData), pFile);
					sscanf(aHeadData, "%s", aStoneName);

					if (strcmp(aStoneName, "EFFECTSET") == 0)
					{
						//END_PARTSSETを読み込むまで繰り返す
						while (strcmp(aStoneName, "END_EFFECTSET") != 0)
						{
							//一列読み込んでモード情報を抽出
							fgets(aHeadData, sizeof(aHeadData), pFile);
							sscanf(aHeadData, "%s", aStoneName);

							if (strcmp(aStoneName, "SIZE") == 0)
							{
								// サイズの設定
								sscanf(aHeadData, "%*s %*s %f %f %f",
									&m_Stone[nStoneIndex].size.x,
									&m_Stone[nStoneIndex].size.y,
									&m_Stone[nStoneIndex].size.z);
							}
							if (strcmp(aStoneName, "RANDMOVE") == 0)
							{
								// 移動量
								sscanf(aHeadData, "%*s %*s %f %f %f",
									&m_Stone[nStoneIndex].move.x,
									&m_Stone[nStoneIndex].move.y,
									&m_Stone[nStoneIndex].move.z);
							}
							if (strcmp(aStoneName, "DISTANCE") == 0)
							{
								// 距離
								sscanf(aHeadData, "%*s %*s %f %f %f",
									&m_Stone[nStoneIndex].Distance.x,
									&m_Stone[nStoneIndex].Distance.y,
									&m_Stone[nStoneIndex].Distance.z);
							}
							if (strcmp(aStoneName, "LIFE") == 0)
							{
								// 体力
								sscanf(aHeadData, "%*s %*s %d", &m_Stone[nStoneIndex].nLife);
							}
							if (strcmp(aStoneName, "NUM") == 0)
							{
								// 数
								sscanf(aHeadData, "%*s %*s %d", &m_Stone[nStoneIndex].nNum);
							}
							if (strcmp(aStoneName, "COLOR") == 0)
							{
								// 色
								sscanf(aHeadData, "%*s %*s %f %f %f %f",
									&m_Stone[nStoneIndex].color.r,
									&m_Stone[nStoneIndex].color.g,
									&m_Stone[nStoneIndex].color.b,
									&m_Stone[nStoneIndex].color.a);
							}
						}

						//インデックスを１つ進める
						nStoneIndex++;
					}
				}
			}

		} while (strcmp(aStoneName, "END_SCRIPT") != 0);

		//ファイルクローズ
		fclose(pFile);

		return S_OK;
	}
	else
	{
		//失敗した場合メッセージボックスを表示
		MessageBox(NULL, "モーションファイルを開くのに失敗しました", "警告", MB_OK | MB_ICONEXCLAMATION);

		return	E_FAIL;
	}
}