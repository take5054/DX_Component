// Billboard.cpp

#include "Billboard.hpp"

DirectX::XMFLOAT4X4 Billboard::CreateBillboardMatrix(DirectX::XMFLOAT4X4 In_ViewMatrix, const DirectX::XMFLOAT3& In_rDrawPos)
{
   // view���v�Z�p�̌^�ɕϊ�
   DirectX::XMMATRIX mCamInv = DirectX::XMLoadFloat4x4(&In_ViewMatrix);
   // �t�s������߂�
   mCamInv = DirectX::XMMatrixInverse(nullptr, mCamInv);
   // ��x�AmCamInv��view�ɕϊ�
   DirectX::XMStoreFloat4x4(&In_ViewMatrix, mCamInv);
   // �t�s��̍��W��0�ɂ���
   In_ViewMatrix._41 = In_ViewMatrix._42 = In_ViewMatrix._43 = 0.0f;
   // World�s��ƌv�Z���s�����߁A�ēxveiw��mCamInv�ɕϊ�
   mCamInv = DirectX::XMLoadFloat4x4(&In_ViewMatrix);

   DirectX::XMMATRIX mWorld =
       mCamInv * DirectX::XMMatrixTranslation(In_rDrawPos.x, In_rDrawPos.y, In_rDrawPos.z);
   // mWorld�̓]�u�s����v�Z
   mWorld = DirectX::XMMatrixTranspose(mWorld);

   // �v�Z�����s���XMFLOAT4X4�ɕϊ�
   DirectX::XMFLOAT4X4 world;
   DirectX::XMStoreFloat4x4(&world, mWorld);

   return world;
}

DirectX::XMMATRIX Billboard::CreateBillboardMatrix(DirectX::XMFLOAT4X4 In_ViewMatrix)
{
	// view���v�Z�p�̌^�ɕϊ�
	DirectX::XMMATRIX mCamInv = DirectX::XMLoadFloat4x4(&In_ViewMatrix);
	// �t�s������߂�
	mCamInv = DirectX::XMMatrixInverse(nullptr, mCamInv);
	// ��x�AmCamInv��view�ɕϊ�
	DirectX::XMStoreFloat4x4(&In_ViewMatrix, mCamInv);
	// �t�s��̍��W��0�ɂ���
	In_ViewMatrix._41 = In_ViewMatrix._42 = In_ViewMatrix._43 = 0.0f;
	// World�s��ƌv�Z���s�����߁A�ēxveiw��mCamInv�ɕϊ�
	mCamInv = DirectX::XMLoadFloat4x4(&In_ViewMatrix);

	return mCamInv;
}
