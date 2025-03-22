// ParabolicMotion.cpp

// ==============================
//	include
// ==============================
#include "ParabolicMotion.hpp"
#include <DirectXMath.h>
#include <algorithm>

// ==============================
//	定数定義
// ==============================
constexpr double cx_dTolerance = 1e-6;	// 許容誤差
constexpr double cx_dDeltaDeg = 1e-4;	// 角度の微小変化
constexpr double cx_fAbsGravity = 9.8;	// 重力加速度
constexpr int cx_nMaxCalcAngleIteration = 100; // 最大計算回数
constexpr float cx_fFireSpeed = 450.0f; // 砲弾の速度
constexpr float cx_fGroundHeight = 0.0f; // 地面の高さ

void ParabolicMotion::SampleFunction()
{
    // カメラの位置と注視点のベクトルを計算
	DirectX::XMFLOAT3 f3CamPos = { 2.5f, 8.0f, 2.5f };		// カメラの位置
	DirectX::XMFLOAT3 f3CamLookpos = { 0.0f, 5.0f, 0.0f };  // カメラの注視点
    DirectX::XMVECTOR vCamPos = DirectX::XMLoadFloat3(&f3CamPos);
    DirectX::XMVECTOR vCamLookPos = DirectX::XMLoadFloat3(&f3CamLookpos);
    DirectX::XMVECTOR vDirection = DirectX::XMVectorSubtract(vCamLookPos, vCamPos);

    // 方向ベクトルを正規化
    vDirection = DirectX::XMVector3Normalize(vDirection);
    float t = (cx_fGroundHeight - f3CamPos.y) / DirectX::XMVectorGetY(vDirection);
	// 地面に到達しない場合は処理を終了
	if (t < 0.0f) return;
    DirectX::XMVECTOR vIntersection = DirectX::XMVectorAdd(vCamPos, DirectX::XMVectorScale(vDirection, t));

    // 交差点の座標を取得
    DirectX::XMFLOAT3 f3TargetPos;
    DirectX::XMStoreFloat3(&f3TargetPos, vIntersection);

    // 射出の位置を取得
	DirectX::XMFLOAT3 f3StartPos = { 0.0f, 0.0f, 0.0f };
    DirectX::XMVECTOR vStartPos = DirectX::XMLoadFloat3(&f3StartPos);

    // 射出から交差点へのベクトルを計算
    DirectX::XMVECTOR vTargetPos = DirectX::XMLoadFloat3(&f3TargetPos);
    DirectX::XMVECTOR vToTarget = DirectX::XMVectorSubtract(vTargetPos, vStartPos);

    float fResualtAngle = static_cast<float>(FindOptimalAngleNewton(
        static_cast<double>(cx_fFireSpeed),
        static_cast<double>(cx_fGroundHeight - f3StartPos.y),
        static_cast<double>(DirectX::XMVectorGetX(DirectX::XMVector3Length(vToTarget))
            )));
}

double ParabolicMotion::CalcDistance(const double& In_dv0, const double& In_ddeg, const double& In_dHeight)
{
	double dRad = In_ddeg * DirectX::XM_PI / 180.0; // 角度をラジアンに変換
	return (In_dv0 * cos(dRad) / cx_fAbsGravity) *
		(In_dv0 * sin(dRad) + sqrt(pow(In_dv0 * sin(dRad), 2.0) + 2.0 * cx_fAbsGravity * In_dHeight));
}

double ParabolicMotion::FindOptimalAngleNewton(const double& In_dv0, const double& In_dHeight, const double& In_dTargetDistance)
{
	// ----- 変数宣言 -----
	double dDeg = 0.0; // 初期角度
	double dDistance, dDerivative, dCalcDistanceDiff;

	// ----- ニュートン法 -----
	for (int i = 0; i < cx_nMaxCalcAngleIteration; ++i)
	{
		// 現在の距離を計算
		dDistance = CalcDistance(In_dv0, dDeg, In_dHeight);
		// 距離の微分を数値的に計算
		dDerivative = (CalcDistance(In_dv0, dDeg + cx_dDeltaDeg, In_dHeight) - dDistance) / cx_dDeltaDeg;

		// ニュートン法の更新式
		dCalcDistanceDiff = dDistance - In_dTargetDistance;
		if (std::abs(dCalcDistanceDiff) < cx_dTolerance)
			return dDeg; // 許容誤差内なら解を返す

		dDeg -= dCalcDistanceDiff / dDerivative;

		// 範囲を制限（角度が不合理な値にならないように）
		if (dDeg < -90.0) dDeg = -90.0;
		else if (dDeg > 90.0)  dDeg = 90.0;
	}
	return 0.0; // 解が見つからない場合
}
