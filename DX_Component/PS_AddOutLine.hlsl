// PS_AddOutLine.hlsl
// ���̃t�@�C���́A�A�E�g���C����ǉ����邽�߂̃s�N�Z���V�F�[�_�[���`���܂��B

struct PS_IN
{
    float4 pos : SV_POSITION;
    float2 uv : TEXCOORD0;
    float4 color : COLOR0;
};

cbuffer cbOutline : register(b0)
{
    float4 OutlineColor;    // �A�E�g���C���̐F
    float OutlineThickness; // �A�E�g���C���̑���
    float2 texsize;         // �e�N�X�`���̃T�C�Y
};

Texture2D tex : register(t0);
SamplerState samp : register(s0);

float4 main(PS_IN pin) : SV_TARGET
{
    float2 texSize = float2(OutlineThickness / texsize.x, OutlineThickness / texsize.y);
    float4 originalColor = tex.Sample(samp, pin.uv) * pin.color;

    // ���̃s�N�Z���̃A���t�@�l��0�łȂ��ꍇ�ɂ̂݃A�E�g���C����K�p
    if (originalColor.a > 0.0)
    {
        // �T���v�����O������͂̃s�N�Z���̃I�t�Z�b�g
        float2 offsets[8] =
        {
            float2(-texSize.x, -texSize.y),
            float2(0, -texSize.y),
            float2(texSize.x, -texSize.y),
            float2(-texSize.x, 0),
            float2(texSize.x, 0),
            float2(-texSize.x, texSize.y),
            float2(0, texSize.y),
            float2(texSize.x, texSize.y)
        };

        // ���͂̃s�N�Z�����T���v�����O���ăA�E�g���C�������o(���[�v�x����������邽�߂ɓW�J)
        if (tex.Sample(samp, pin.uv + offsets[0]).a < 0.1 ||
            tex.Sample(samp, pin.uv + offsets[1]).a < 0.1 ||
            tex.Sample(samp, pin.uv + offsets[2]).a < 0.1 ||
            tex.Sample(samp, pin.uv + offsets[3]).a < 0.1 ||
            tex.Sample(samp, pin.uv + offsets[4]).a < 0.1 ||
            tex.Sample(samp, pin.uv + offsets[5]).a < 0.1 ||
            tex.Sample(samp, pin.uv + offsets[6]).a < 0.1 ||
            tex.Sample(samp, pin.uv + offsets[7]).a < 0.1)
        {
            return OutlineColor;
        }
    }

    // �A�E�g���C�������o����Ȃ������ꍇ�͌��̐F��Ԃ�
    return originalColor;
}
