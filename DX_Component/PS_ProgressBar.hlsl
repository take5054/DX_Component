// PS_ProgressBar.hlsl
// ���̃t�@�C���́A�i���o�[��`�悷�邽�߂̃s�N�Z���V�F�[�_�[���`���܂��B

// ���͍\����
struct PS_IN
{
    float4 pos : SV_POSITION; // ���_�̈ʒu
    float2 uv : TEXCOORD0; // �e�N�X�`�����W
    float4 color : COLOR0; // ���_�J���[
};

// �萔�o�b�t�@
cbuffer Percent : register(b0)
{
    float percent;
};

// �e�N�X�`���ƃT���v���[�X�e�[�g
Texture2D tex : register(t0);
SamplerState samp : register(s0);

// �s�N�Z���V�F�[�_�[�̃��C���֐�
float4 main(PS_IN pin) : SV_TARGET
{
    if (pin.uv.x > percent)
    {
        // Percent���E���̕����͓����ɂ���
        return float4(0.0f, 0.0f, 0.0f, 0.0f);
    }
    return tex.Sample(samp, pin.uv) * pin.color;
};
