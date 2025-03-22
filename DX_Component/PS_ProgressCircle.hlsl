// PS_ProgressCircle.hlsl
// このファイルは、進捗円を描画するためのピクセルシェーダーを定義します。

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
    // 中心を原点にする
    float2 uv = pin.uv - float2(0.5f, 0.5f);

    // 角度を計算（開始地点を上に設定）
    float angle = atan2(uv.x, uv.y) / (2.0f * 3.14159265359f) + 0.5f;

    // 角度がpercentより大きい場合は透明にする
    if (angle > percent)
    {
        return float4(0.0f, 0.0f, 0.0f, 0.0f);
    }

    return tex.Sample(samp, pin.uv) * pin.color;
};
