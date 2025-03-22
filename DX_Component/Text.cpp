// Text.cpp

// ==============================
//	include
// ==============================
#include "Text.hpp"
#include <algorithm>

// ==============================
//	�}�N����`
// ==============================
#define SAFE_RELEASE(p) { if(p) { (p)->Release(); (p) = nullptr; } }
#define SAFE_DELETE_ARRAY(p) { if(p) { delete[] (p); (p) = nullptr; } }
// min, max�̃}�N���𖳌���
#undef max
#undef min

// ==============================
//	�萔��`
// ==============================
constexpr int cx_nmaText = 2; // �e�L�X�g�̗]��(All)
constexpr int cx_nHalfmaText = static_cast<int>(cx_nmaText * 0.5f); // �e�L�X�g�̗]��(Half)

Text::Text()
	: m_pSRV(nullptr)
{

}

Text::Text(const std::string& In_strText, const int& In_nFontSize)
	: m_pSRV(nullptr)
{
	CreateText(In_strText.c_str(), In_nFontSize);
}

Text::~Text()
{
    SAFE_RELEASE(m_pSRV);
}

void Text::CreateText(const std::string& In_strText, const int& In_nFontSize)
{
	// �e�N�X�`�������ɑ��݂��Ă���ꍇ�͍폜
    SAFE_RELEASE(m_pSRV);

    // �t�H���g�n���h���̐���
    LOGFONT lfFontHandle = {
        In_nFontSize, 0, 0, 0, FW_BOLD, 0, 0, 0,
        SHIFTJIS_CHARSET, OUT_TT_ONLY_PRECIS, CLIP_DEFAULT_PRECIS,
        PROOF_QUALITY, DEFAULT_PITCH | FF_MODERN,
        L"�l�r �o����"
    };
    HFONT hFont = CreateFontIndirect(&lfFontHandle);

    // ���݂̃E�B���h�E�ɓK�p
    HDC hdc = GetDC(NULL);
    HFONT oldFont = (HFONT)SelectObject(hdc, hFont);

	// �e�L�X�g�̃T�C�Y���擾
	SSpriteAttributes sSpriteSize = GenerateSprite(In_strText, hdc);

    // �傫�ȃe�N�X�`�����쐬
	D3D11_TEXTURE2D_DESC texDesc =
        GenerateTextureDesc(sSpriteSize.nTotalWidth, sSpriteSize.nAdjustedHeight);

    // DirectX 11 �f�o�C�X�ƃR���e�L�X�g�̎擾
    ID3D11Device* pDevice = GetDevice();
    ID3D11DeviceContext* pDeviceContext = GetContext();

    ID3D11Texture2D* pTex = nullptr;
    if (FAILED(pDevice->CreateTexture2D(&texDesc, nullptr, &pTex)))
    {
		DeleteHandlings(hdc, hFont);
        return;
    }

    // �e�N�X�`���Ƀt�H���g�r�b�g�}�b�v������������
    D3D11_MAPPED_SUBRESOURCE mappedResource;
    if (FAILED(pDeviceContext->Map(pTex, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource)))
    {
        pTex->Release();
		DeleteHandlings(hdc, hFont);
        return;
    }

	BYTE* pTexBuf = GenerateFontBitmap(sSpriteSize, mappedResource, texDesc);

    pDeviceContext->Unmap(pTex, 0);

    // �V�F�[�_�[���\�[�X�r���[�̍쐬
    if (FAILED(pDevice->CreateShaderResourceView(pTex, nullptr, &m_pSRV)))
    {
        pTex->Release();
		DeleteHandlings(hdc, hFont);
        return;
    }

	SAFE_RELEASE(pTex);
	DeleteHandlings(hdc, hFont);
}

void Text::DeleteHandlings(HDC& hdc, HFONT& hFont)
{
    // �f�o�C�X�R���e�L�X�g�ƃt�H���g�n���h���̉��
	SelectObject(hdc, hFont);
	ReleaseDC(NULL, hdc);
	DeleteObject(hFont);
}

Text::SSpriteAttributes Text::GenerateSprite(const std::string& In_strText, const HDC& hdc)
{
    SSpriteAttributes sSpriteSize{};

    int nLen = MultiByteToWideChar(CP_ACP, 0, In_strText.c_str(), -1, NULL, 0);
    wchar_t* pwcText = new wchar_t[nLen];
    MultiByteToWideChar(CP_ACP, 0, In_strText.c_str(), -1, pwcText, nLen);

	int nMaxHeight = 0;
	int nMaxDescent = 0;

    // �e�����̃e�N�X�`���T�C�Y���v�Z
    for (const wchar_t* pCurrentChar = pwcText; *pCurrentChar != L'\0'; ++pCurrentChar)
    {
        wchar_t character = *pCurrentChar;

        GLYPHMETRICS GM;
        const MAT2 mat = { {0,1},{0,0},{0,0},{0,1} };
        DWORD dwSize = GetGlyphOutlineW(hdc, character, GGO_GRAY8_BITMAP, &GM, 0, NULL, &mat);
        if (dwSize == GDI_ERROR) continue;

        BYTE* pFontBMP = new BYTE[dwSize];
        GetGlyphOutlineW(hdc, character, GGO_GRAY8_BITMAP, &GM, dwSize, pFontBMP, &mat);

        sSpriteSize.nTotalWidth += GM.gmBlackBoxX + cx_nmaText;
        nMaxHeight = std::max(nMaxHeight, static_cast<int>(GM.gmBlackBoxY) + cx_nmaText);
        sSpriteSize.nMaxBaseline = std::max(sSpriteSize.nMaxBaseline, static_cast<int>(GM.gmptGlyphOrigin.y));
        nMaxDescent = std::max(nMaxDescent, static_cast<int>(GM.gmBlackBoxY) - static_cast<int>(GM.gmptGlyphOrigin.y));

        sSpriteSize.vecGlyphMetrics.push_back(GM);
        sSpriteSize.vecFontBitmaps.push_back(pFontBMP);
    }

    // �e�N�X�`���̍����𒲐�
    sSpriteSize.nAdjustedHeight = sSpriteSize.nMaxBaseline + nMaxDescent + cx_nmaText;

    SAFE_DELETE_ARRAY(pwcText);

	return sSpriteSize;
}

D3D11_TEXTURE2D_DESC Text::GenerateTextureDesc(const int& In_nWidth, const int& In_nHeight)
{
    D3D11_TEXTURE2D_DESC texDesc = {};
    texDesc.Width = In_nWidth;
    texDesc.Height = In_nHeight;
    texDesc.MipLevels = 1;
    texDesc.ArraySize = 1;
    texDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    texDesc.SampleDesc.Count = 1;
    texDesc.Usage = D3D11_USAGE_DYNAMIC;
    texDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
    texDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	return texDesc;
}

BYTE* Text::GenerateFontBitmap(SSpriteAttributes& In_sSpriteAttri,
    const D3D11_MAPPED_SUBRESOURCE& In_mappedResource,
    const D3D11_TEXTURE2D_DESC& In_texDesc)
{
    BYTE* pTexBuf = reinterpret_cast<BYTE*>(In_mappedResource.pData);
    int nOffsetX = 0;

    // �e�N�X�`���Ƀt�H���g�r�b�g�}�b�v������������
    for (size_t i = 0, end = In_sSpriteAttri.vecGlyphMetrics.size(); i < end; ++i)
    {
        const GLYPHMETRICS& GM = In_sSpriteAttri.vecGlyphMetrics[i];
        BYTE* pFontBMP = In_sSpriteAttri.vecFontBitmaps[i];

        const int baselineOffset = In_sSpriteAttri.nMaxBaseline - GM.gmptGlyphOrigin.y;
		const int endY = static_cast<int>(GM.gmBlackBoxY);
		const int endX = static_cast<int>(GM.gmBlackBoxX);

        for (int nY = 0, nX; nY < endY; ++nY)
        {
            for (nX = 0; nX < endX; ++nX)
            {
                DWORD alpha = pFontBMP[nY * ((GM.gmBlackBoxX + 3) & ~3) + nX] * 255 / 16;
                size_t index = ((nY + baselineOffset + cx_nHalfmaText) * In_mappedResource.RowPitch) + ((nX + nOffsetX + cx_nHalfmaText) * 4);
                if (index + 3 < In_texDesc.Width * In_texDesc.Height * 4) // ���E�`�F�b�N
                {
                    pTexBuf[index] = 0xFF; // Blue
                    pTexBuf[++index] = 0xFF; // Green
                    pTexBuf[++index] = 0xFF; // Red
                    pTexBuf[++index] = static_cast<BYTE>(alpha); // Alpha
                }
            }
        }

        nOffsetX += GM.gmBlackBoxX + cx_nmaText;
		SAFE_DELETE_ARRAY(pFontBMP);
    }
	return pTexBuf;
}
