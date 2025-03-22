// ParabolicMotion.cpp

// ==============================
//	include
// ==============================
#include "ParabolicMotion.hpp"
#include <DirectXMath.h>
#include <algorithm>

// ==============================
//	�萔��`
// ==============================
constexpr double cx_dTolerance = 1e-6;	// ���e�덷
constexpr double cx_dDeltaDeg = 1e-4;	// �p�x�̔����ω�
constexpr double cx_fAbsGravity = 9.8;	// �d�͉����x
constexpr int cx_nMaxCalcAngleIteration = 100; // �ő�v�Z��
constexpr float cx_fFireSpeed = 450.0f; // �C�e�̑��x
constexpr float cx_fGroundHeight = 0.0f; // �n�ʂ̍���

void ParabolicMotion::SampleFunction()
{
    // �J�����̈ʒu�ƒ����_�̃x�N�g�����v�Z
	DirectX::XMFLOAT3 f3CamPos = { 2.5f, 8.0f, 2.5f };		// �J�����̈ʒu
	DirectX::XMFLOAT3 f3CamLookpos = { 0.0f, 5.0f, 0.0f };  // �J�����̒����_
    DirectX::XMVECTOR vCamPos = DirectX::XMLoadFloat3(&f3CamPos);
    DirectX::XMVECTOR vCamLookPos = DirectX::XMLoadFloat3(&f3CamLookpos);
    DirectX::XMVECTOR vDirection = DirectX::XMVectorSubtract(vCamLookPos, vCamPos);

    // �����x�N�g���𐳋K��
    vDirection = DirectX::XMVector3Normalize(vDirection);
    float t = (cx_fGroundHeight - f3CamPos.y) / DirectX::XMVectorGetY(vDirection);
	// �n�ʂɓ��B���Ȃ��ꍇ�͏������I��
	if (t < 0.0f) return;
    DirectX::XMVECTOR vIntersection = DirectX::XMVectorAdd(vCamPos, DirectX::XMVectorScale(vDirection, t));

    // �����_�̍��W���擾
    DirectX::XMFLOAT3 f3TargetPos;
    DirectX::XMStoreFloat3(&f3TargetPos, vIntersection);

    // �ˏo�̈ʒu���擾
	DirectX::XMFLOAT3 f3StartPos = { 0.0f, 0.0f, 0.0f };
    DirectX::XMVECTOR vStartPos = DirectX::XMLoadFloat3(&f3StartPos);

    // �ˏo��������_�ւ̃x�N�g�����v�Z
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
	double dRad = In_ddeg * DirectX::XM_PI / 180.0; // �p�x�����W�A���ɕϊ�
	return (In_dv0 * cos(dRad) / cx_fAbsGravity) *
		(In_dv0 * sin(dRad) + sqrt(pow(In_dv0 * sin(dRad), 2.0) + 2.0 * cx_fAbsGravity * In_dHeight));
}

double ParabolicMotion::FindOptimalAngleNewton(const double& In_dv0, const double& In_dHeight, const double& In_dTargetDistance)
{
	// ----- �ϐ��錾 -----
	double dDeg = 0.0; // �����p�x
	double dDistance, dDerivative, dCalcDistanceDiff;

	// ----- �j���[�g���@ -----
	for (int i = 0; i < cx_nMaxCalcAngleIteration; ++i)
	{
		// ���݂̋������v�Z
		dDistance = CalcDistance(In_dv0, dDeg, In_dHeight);
		// �����̔����𐔒l�I�Ɍv�Z
		dDerivative = (CalcDistance(In_dv0, dDeg + cx_dDeltaDeg, In_dHeight) - dDistance) / cx_dDeltaDeg;

		// �j���[�g���@�̍X�V��
		dCalcDistanceDiff = dDistance - In_dTargetDistance;
		if (std::abs(dCalcDistanceDiff) < cx_dTolerance)
			return dDeg; // ���e�덷���Ȃ����Ԃ�

		dDeg -= dCalcDistanceDiff / dDerivative;

		// �͈͂𐧌��i�p�x���s�����Ȓl�ɂȂ�Ȃ��悤�Ɂj
		if (dDeg < -90.0) dDeg = -90.0;
		else if (dDeg > 90.0)  dDeg = 90.0;
	}
	return 0.0; // ����������Ȃ��ꍇ
}
