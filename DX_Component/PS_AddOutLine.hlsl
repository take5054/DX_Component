// PS_AddOutLine.hlsl
// このファイルは、アウトラインを追加するためのピクセルシェーダーを定義します。

struct PS_IN
{
    float4 pos : SV_POSITION;
    float2 uv : TEXCOORD0;
    float4 color : COLOR0;
};

cbuffer cbOutline : register(b0)
{
    float4 OutlineColor;    // アウトラインの色
    float OutlineThickness; // アウトラインの太さ
    float2 texsize;         // テクスチャのサイズ
};

Texture2D tex : register(t0);
SamplerState samp : register(s0);

float4 main(PS_IN pin) : SV_TARGET
{
    float2 texSize = float2(OutlineThickness / texsize.x, OutlineThickness / texsize.y);
    float4 originalColor = tex.Sample(samp, pin.uv) * pin.color;

    // 元のピクセルのアルファ値が0でない場合にのみアウトラインを適用
    if (originalColor.a > 0.0)
    {
        // サンプリングする周囲のピクセルのオフセット
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

        // 周囲のピクセルをサンプリングしてアウトラインを検出(ループ警告を回避するために展開)
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

    // アウトラインが検出されなかった場合は元の色を返す
    return originalColor;
}
