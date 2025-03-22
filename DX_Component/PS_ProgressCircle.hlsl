// PS_ProgressCircle.hlsl
// ���̃t�@�C���́A�i���~��`�悷�邽�߂̃s�N�Z���V�F�[�_�[���`���܂��B

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
    // ���S�����_�ɂ���
    float2 uv = pin.uv - float2(0.5f, 0.5f);

    // �p�x���v�Z�i�J�n�n�_����ɐݒ�j
    float angle = atan2(uv.x, uv.y) / (2.0f * 3.14159265359f) + 0.5f;

    // �p�x��percent���傫���ꍇ�͓����ɂ���
    if (angle > percent)
    {
        return float4(0.0f, 0.0f, 0.0f, 0.0f);
    }

    return tex.Sample(samp, pin.uv) * pin.color;
};
