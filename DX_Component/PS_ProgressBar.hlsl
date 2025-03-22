// PS_ProgressBar.hlsl
// このファイルは、進捗バーを描画するためのピクセルシェーダーを定義します。

// 入力構造体
struct PS_IN
{
    float4 pos : SV_POSITION; // 頂点の位置
    float2 uv : TEXCOORD0; // テクスチャ座標
    float4 color : COLOR0; // 頂点カラー
};

// 定数バッファ
cbuffer Percent : register(b0)
{
    float percent;
};

// テクスチャとサンプラーステート
Texture2D tex : register(t0);
SamplerState samp : register(s0);

// ピクセルシェーダーのメイン関数
float4 main(PS_IN pin) : SV_TARGET
{
    if (pin.uv.x > percent)
    {
        // Percentより右側の部分は透明にする
        return float4(0.0f, 0.0f, 0.0f, 0.0f);
    }
    return tex.Sample(samp, pin.uv) * pin.color;
};
