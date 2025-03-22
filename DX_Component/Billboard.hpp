// Billboard.hpp
#pragma once

#include <DirectXMath.h>

/// <summary>
/// ビルボード行列を作成する
/// </summary>
namespace Billboard
{
	/// <summary>
	/// ビルボード行列を作成する
	/// </summary>
	/// <param name="[In_ViewMatrix]">ビュー行列</param>
	/// <param name="[In_rDrawPos]">描画位置</param>
	/// <returns>ビルボード行列</returns>
	DirectX::XMFLOAT4X4 CreateBillboardMatrix(DirectX::XMFLOAT4X4 In_ViewMatrix, const DirectX::XMFLOAT3& In_rDrawPos);

	/// <summary>
	/// ビルボード行列を作成する
	/// </summary>
	/// <param name="[In_ViewMatrix]">ビュー行列</param>
	/// <returns>ビルボード行列</returns>
	/// <remarks>XMMATRIXを返すのは重いので非推奨</remarks>
	DirectX::XMMATRIX CreateBillboardMatrix(DirectX::XMFLOAT4X4 In_ViewMatrix);
}
