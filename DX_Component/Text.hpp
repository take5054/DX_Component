// Text.hpp
#pragma once

#include <string>
#include <vector>
#include <d3d11.h>
#include <DirectXMath.h>

// CreateTextで使うので仮定義
ID3D11Device* g_pDevice;
ID3D11DeviceContext* g_pContext;
ID3D11Device* GetDevice()
{
	return g_pDevice;
}

ID3D11DeviceContext* GetContext()
{
	return g_pContext;
}

/// <summary>
/// Textのテクスチャを作成する
/// </summary>
class Text
{
public:
	Text();

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="[In_strText]">テキスト</param>
	/// <param name="[In_nFontSize]">フォントサイズ</param>
	Text(const std::string& In_strText, const int& In_nFontSize);
	~Text();

	/// <summary>
	/// テキストの作成
	/// </summary>
	/// <param name="[In_szText]">テキスト</param>
	/// <param name="[In_nFontSize]">フォントサイズ</param>
	void CreateText(const std::string& In_strText, const int& In_nFontSize);
	inline ID3D11ShaderResourceView* GetTexture() const noexcept { return m_pSRV; }

private:

	/// <summary>
	/// テキストの属性
	/// </summary>
	struct SSpriteAttributes
	{
		int nTotalWidth = 0;		// 全体の幅
		int nMaxBaseline = 0;		// ベースラインの最大値
		int nAdjustedHeight = 0;	// 調整された高さ
		std::vector<GLYPHMETRICS> vecGlyphMetrics;	// グリフメトリクス
		std::vector<BYTE*> vecFontBitmaps;	// フォントビットマップ
	};

	ID3D11ShaderResourceView* m_pSRV;	// シェーダーリソースビュー(実質テクスチャ)

	// CreateTextの依存関数
	void DeleteHandlings(HDC& hdc, HFONT& hFont);
	// CreateTextの依存関数
	SSpriteAttributes GenerateSprite(const std::string& In_strText, const HDC& hdc);
	// CreateTextの依存関数
	D3D11_TEXTURE2D_DESC GenerateTextureDesc(const int& In_nWidth, const int& In_nHeight);
	// CreateTextの依存関数
	BYTE* GenerateFontBitmap(SSpriteAttributes& In_sSpriteAttri,
		const D3D11_MAPPED_SUBRESOURCE& In_mappedResource,
		const D3D11_TEXTURE2D_DESC& In_texDesc);
};
