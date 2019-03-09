#ifndef TRAJ_PROP_STEP_HPP
#define TRAJ_PROP_STEP_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER)
#pragma once
#endif

#include <Eigen/Dense>
#include <complex>

namespace oqs
{
	/** \brief Performs propagation step: y=A*x
	  *
	  * \tparam A: propagation matrix of non-hermitian hamiltonian.
	  * \tparam x: vector of wave function's previous state.
	  * \tparam y: vector of wave function's next state.
	*/
	void prop_step(Eigen::VectorXcd& y, const Eigen::MatrixXcd& A, const Eigen::VectorXcd& x)
	{
		y.noalias() = A * x;
	}
} // namespace oqs

#endif // TRAJ_PROP_STEP_HPP