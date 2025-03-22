// Billboard.cpp

#include "Billboard.hpp"

DirectX::XMFLOAT4X4 Billboard::CreateBillboardMatrix(DirectX::XMFLOAT4X4 In_ViewMatrix, const DirectX::XMFLOAT3& In_rDrawPos)
{
   // viewを計算用の型に変換
   DirectX::XMMATRIX mCamInv = DirectX::XMLoadFloat4x4(&In_ViewMatrix);
   // 逆行列を求める
   mCamInv = DirectX::XMMatrixInverse(nullptr, mCamInv);
   // 一度、mCamInvをviewに変換
   DirectX::XMStoreFloat4x4(&In_ViewMatrix, mCamInv);
   // 逆行列の座標を0にする
   In_ViewMatrix._41 = In_ViewMatrix._42 = In_ViewMatrix._43 = 0.0f;
   // World行列と計算を行うため、再度veiwをmCamInvに変換
   mCamInv = DirectX::XMLoadFloat4x4(&In_ViewMatrix);

   DirectX::XMMATRIX mWorld =
       mCamInv * DirectX::XMMatrixTranslation(In_rDrawPos.x, In_rDrawPos.y, In_rDrawPos.z);
   // mWorldの転置行列を計算
   mWorld = DirectX::XMMatrixTranspose(mWorld);

   // 計算した行列をXMFLOAT4X4に変換
   DirectX::XMFLOAT4X4 world;
   DirectX::XMStoreFloat4x4(&world, mWorld);

   return world;
}

DirectX::XMMATRIX Billboard::CreateBillboardMatrix(DirectX::XMFLOAT4X4 In_ViewMatrix)
{
	// viewを計算用の型に変換
	DirectX::XMMATRIX mCamInv = DirectX::XMLoadFloat4x4(&In_ViewMatrix);
	// 逆行列を求める
	mCamInv = DirectX::XMMatrixInverse(nullptr, mCamInv);
	// 一度、mCamInvをviewに変換
	DirectX::XMStoreFloat4x4(&In_ViewMatrix, mCamInv);
	// 逆行列の座標を0にする
	In_ViewMatrix._41 = In_ViewMatrix._42 = In_ViewMatrix._43 = 0.0f;
	// World行列と計算を行うため、再度veiwをmCamInvに変換
	mCamInv = DirectX::XMLoadFloat4x4(&In_ViewMatrix);

	return mCamInv;
}
