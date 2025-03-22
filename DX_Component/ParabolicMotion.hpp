// ParabolicMotion.hpp
#pragma once

/// <summary>
/// 放物運動の計算
/// </summary>
namespace ParabolicMotion
{
	/// <summary>
	/// 使用例
	/// </summary>
	void SampleFunction();

	/// <summary>
	/// 距離を計算する
	/// </summary>
	/// <param name="[In_dv0]">初速度</param>
	/// <param name="[In_ddeg]">角度</param>
	/// <param name="[In_dHeight]">高さ</param>
	/// <returns>距離</returns>
	/// <remarks>doubleじゃないと誤差が大きい</remarks>
	double CalcDistance(const double& In_dv0, const double& In_ddeg, const double& In_dHeight);

	/// <summary>
	/// <para>高低差のある放物運動を初速と高さ,目標までの距離から最適な角度を求める</para>
	/// <para>高初速で短い距離を飛ばす場合でも最適角を計算可能</para>
	/// </summary>
	/// <param name="[In_dv0]">初速度</param>
	/// <param name="[In_dHeight]">高さ</param>
	/// <param name="[In_dTargetDistance]">目標距離</param>
	/// <returns>最適な角度(deg)</returns>
	/// <remarks>doubleじゃないと誤差が大きい</remarks>
	double FindOptimalAngleNewton(const double& In_dv0, const double& In_dHeight, const double& In_dTargetDistance);
}
