// Text.hpp
#pragma once

#include <string>
#include <vector>
#include <d3d11.h>
#include <DirectXMath.h>

// CreateText�Ŏg���̂ŉ���`
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
/// Text�̃e�N�X�`�����쐬����
/// </summary>
class Text
{
public:
	Text();

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="[In_strText]">�e�L�X�g</param>
	/// <param name="[In_nFontSize]">�t�H���g�T�C�Y</param>
	Text(const std::string& In_strText, const int& In_nFontSize);
	~Text();

	/// <summary>
	/// �e�L�X�g�̍쐬
	/// </summary>
	/// <param name="[In_szText]">�e�L�X�g</param>
	/// <param name="[In_nFontSize]">�t�H���g�T�C�Y</param>
	void CreateText(const std::string& In_strText, const int& In_nFontSize);
	inline ID3D11ShaderResourceView* GetTexture() const noexcept { return m_pSRV; }

private:

	/// <summary>
	/// �e�L�X�g�̑���
	/// </summary>
	struct SSpriteAttributes
	{
		int nTotalWidth = 0;		// �S�̂̕�
		int nMaxBaseline = 0;		// �x�[�X���C���̍ő�l
		int nAdjustedHeight = 0;	// �������ꂽ����
		std::vector<GLYPHMETRICS> vecGlyphMetrics;	// �O���t���g���N�X
		std::vector<BYTE*> vecFontBitmaps;	// �t�H���g�r�b�g�}�b�v
	};

	ID3D11ShaderResourceView* m_pSRV;	// �V�F�[�_�[���\�[�X�r���[(�����e�N�X�`��)

	// CreateText�̈ˑ��֐�
	void DeleteHandlings(HDC& hdc, HFONT& hFont);
	// CreateText�̈ˑ��֐�
	SSpriteAttributes GenerateSprite(const std::string& In_strText, const HDC& hdc);
	// CreateText�̈ˑ��֐�
	D3D11_TEXTURE2D_DESC GenerateTextureDesc(const int& In_nWidth, const int& In_nHeight);
	// CreateText�̈ˑ��֐�
	BYTE* GenerateFontBitmap(SSpriteAttributes& In_sSpriteAttri,
		const D3D11_MAPPED_SUBRESOURCE& In_mappedResource,
		const D3D11_TEXTURE2D_DESC& In_texDesc);
};
