// Billboard.hpp
#pragma once

#include <DirectXMath.h>

/// <summary>
/// �r���{�[�h�s����쐬����
/// </summary>
namespace Billboard
{
	/// <summary>
	/// �r���{�[�h�s����쐬����
	/// </summary>
	/// <param name="[In_ViewMatrix]">�r���[�s��</param>
	/// <param name="[In_rDrawPos]">�`��ʒu</param>
	/// <returns>�r���{�[�h�s��</returns>
	DirectX::XMFLOAT4X4 CreateBillboardMatrix(DirectX::XMFLOAT4X4 In_ViewMatrix, const DirectX::XMFLOAT3& In_rDrawPos);

	/// <summary>
	/// �r���{�[�h�s����쐬����
	/// </summary>
	/// <param name="[In_ViewMatrix]">�r���[�s��</param>
	/// <returns>�r���{�[�h�s��</returns>
	/// <remarks>XMMATRIX��Ԃ��̂͏d���̂Ŕ񐄏�</remarks>
	DirectX::XMMATRIX CreateBillboardMatrix(DirectX::XMFLOAT4X4 In_ViewMatrix);
}
