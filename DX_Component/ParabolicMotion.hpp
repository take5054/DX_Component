// ParabolicMotion.hpp
#pragma once

/// <summary>
/// �����^���̌v�Z
/// </summary>
namespace ParabolicMotion
{
	/// <summary>
	/// �g�p��
	/// </summary>
	void SampleFunction();

	/// <summary>
	/// �������v�Z����
	/// </summary>
	/// <param name="[In_dv0]">�����x</param>
	/// <param name="[In_ddeg]">�p�x</param>
	/// <param name="[In_dHeight]">����</param>
	/// <returns>����</returns>
	/// <remarks>double����Ȃ��ƌ덷���傫��</remarks>
	double CalcDistance(const double& In_dv0, const double& In_ddeg, const double& In_dHeight);

	/// <summary>
	/// <para>���፷�̂�������^���������ƍ���,�ڕW�܂ł̋�������œK�Ȋp�x�����߂�</para>
	/// <para>�������ŒZ���������΂��ꍇ�ł��œK�p���v�Z�\</para>
	/// </summary>
	/// <param name="[In_dv0]">�����x</param>
	/// <param name="[In_dHeight]">����</param>
	/// <param name="[In_dTargetDistance]">�ڕW����</param>
	/// <returns>�œK�Ȋp�x(deg)</returns>
	/// <remarks>double����Ȃ��ƌ덷���傫��</remarks>
	double FindOptimalAngleNewton(const double& In_dv0, const double& In_dHeight, const double& In_dTargetDistance);
}
