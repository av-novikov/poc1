#ifndef MATRIX_HPP_
#define MATRIX_HPP_

#include <initializer_list>
#include <cassert>
#include <cmath>
#include <limits>
#include <iostream>

#define EQUALITY_TOLERANCE 1.E-8

namespace data {
/**
 * Basic data types
 */
typedef unsigned int uint;
typedef double Scalar;

/**
 * Default implementation for matrix values container.
 *
 * @tparam M First matrix dimension.
 * @tparam N Second matrix dimension.
 * @tparam ElemType Type of elements constitute container
 */
template<uint M, uint N>
class DefaultMatrixContainer {
public:
	typedef Scalar DataType;
	DataType values[M * N];

	static const uint size;
};

template<uint M, uint N>
const uint DefaultMatrixContainer<M, N>::size = M * N;

/**
 * Genereic matrix class.
 *
 * @tparam M First matrix dimension.
 * @tparam N Second matrix dimension.
 * @tparam ElemType Type of elements constitute container
 * @tparam Container Container class to hold values.
 */
template<uint M, uint N, typename Container = DefaultMatrixContainer<M, N> >
class Matrix: public Container {
public:
	typedef Container Base;
	using typename Container::DataType;
protected:
	/**
	 * Returns values array index of matrix component.
	 *
	 * @param i First index.
	 * @param j Second index.
	 *
	 * @return Values array index.
	 */
	uint getIndex(const uint i, const uint j) const;
public:
	/**
	 * Default constructor.
	 */
	Matrix();

	/**
	 * Copy constructor
	 *
	 * @param m Matrix to construct from.
	 */
	Matrix(const Matrix<M, N, Container>& m);

	/**
	 * Assignment operator.
	 *
	 * @param m Matrix to assign values from.
	 *
	 * @return Reference to modified matrix instance.
	 */
	Matrix<M, N, Container>& operator=(const Matrix<M, N, Container>& m);

	/**
	 * Constructor that initializes matrix with specified values.
	 *
	 * @param values Values to initialize matrix with.
	 */
	Matrix(std::initializer_list<DataType> values);

	/**
	 * Returns matrix component.
	 *
	 * @param i First index.
	 * @param j Second index.
	 *
	 * @return Corresponding matrix component.
	 */
	DataType operator()(const uint i, const uint j) const;

	/**
	 * Returns reference to matrix component, used to modify matrix content.
	 *
	 * @param i First index.
	 * @param j Second index.
	 *
	 * @return Reference to corresponding matrix component.
	 */
	DataType& operator()(const uint i, const uint j);

	/**
	 * Transposes matrix.
	 *
	 * @return Transposed matrix.
	 */
	Matrix<N, M, Container> transpose() const;

	/**
	 * Transposes square matrix (modifies matrix contents).
	 */
	void transposeInplace();

	Matrix<M, N, Container>& operator+=(const Matrix<M, N, Container>& m);
	Matrix<M, N, Container>& operator-=(const Matrix<M, N, Container>& m);
};

template<uint M, uint N, typename Container>
Matrix<M, N, Container>::Matrix() {
	static_assert(sizeof(this->values) >= sizeof(DataType)*M*N, "Container must have enough memory to store values");

	for (uint i = 0; i < M * N; i++)
		this->values[i] = (DataType)(0);
}

template<uint M, uint N, typename Container>
Matrix<M, N, Container>::Matrix(std::initializer_list<DataType> values) :
		Matrix() {
	uint i = 0;
	for (auto value : values)
		this->values[i++] = value;
}

template<uint M, uint N, typename Container>
Matrix<M, N, Container>::Matrix(const Matrix<M, N, Container>& m) {
	(*this) = m;
}

template<uint M, uint N, typename Container>
Matrix<M, N, Container>& Matrix<M, N, Container>::operator=(
		const Matrix<M, N, Container>& m) {
	for (uint i = 0; i < M; i++)
		for (uint j = 0; j < N; j++)
			(*this)(i, j) = m(i, j);

	return *this;
}

template<uint M, uint N, typename Container>
inline uint Matrix<M, N, Container>::getIndex(uint i, uint j) const {
	assert(i < M);
	assert(j < N);

	return i * N + j;
}

template<uint M, uint N, typename Container>
inline typename Container::DataType Matrix<M, N, Container>::operator()(const uint i,
		const uint j) const {
	return this->values[getIndex(i, j)];
}

template<uint M, uint N, typename Container>
inline typename Container::DataType& Matrix<M, N, Container>::operator()(const uint i, const uint j) {
	return this->values[getIndex(i, j)];
}

template<uint M, uint N, typename Container>
Matrix<N, M, Container> Matrix<M, N, Container>::transpose() const {
	Matrix<N, M, Container> result;

	for (uint i = 0; i < M; i++)
		for (uint j = 0; j < N; j++)
			result(j, i) = (*this)(i, j);

	return result;
}

template<uint M, uint N, typename Container>
void Matrix<M, N, Container>::transposeInplace() {
	(*this) = transpose();
}

/**
 * Computes negative of matrix B
 *
 * @tparam M First matrix dimension
 * @tparam N Second matrix dimension
 * @tparam Container Matrix container type
 * @param m Matrix to compute negative for.
 *
 * @return Negative of matrix
 */
template<uint M, uint N, typename Container>
Matrix<M, N, Container> operator-(const Matrix<M, N, Container>& m) {
	Matrix<M, N, Container> result;

	for (uint i = 0; i < M; i++)
		for (uint j = 0; j < N; j++)
			result(i, j) = -m(i, j);

	return result;
}

/**
 * Computes summ of two matrixes. Generic implementation.
 *
 * @tparam M First matrix dimension.
 * @tparam N Second matrix dimension.
 * @tparam Container1 Container type for first summ item.
 * @tparam Container2 Container type for second  summ item.
 * @tparam Container3 Container type for result.
 * @param m1 First summ item.
 * @param m2 Second summ item.
 *
 * @return Matrix summ (m1+m2).
 */
template<uint M, uint N, typename Container1, typename Container2, typename Container3>
Matrix<M, N, Container3> operator+(const Matrix<M, N, Container1>& m1,
		const Matrix<M, N, Container2>& m2) {
	Matrix<M, N, Container3> result;

	for (uint i = 0; i < M; i++)
		for (uint j = 0; j < N; j++)
			result(i, j) = m1(i, j) + m2(i, j);

	return result;
}

/**
 * Computes summ of two matrixes. Most useful specialization, made in assumption that result matrix should
 * use default matrix container.
 *
 * @tparam M First matrix dimension.
 * @tparam N Second matrix dimension.
 * @tparam Container1 Container type for first summ item.
 * @tparam Container2 Container type for second  summ item.
 * @param m1 First summ item.
 * @param m2 Second summ item.
 *
 * @return Matrix summ (m1+m2).
 */
template<uint M, uint N, typename Container1, typename Container2>
Matrix<M, N, DefaultMatrixContainer<M, N>> operator+(
		const Matrix<M, N, Container1>& m1,
		const Matrix<M, N, Container2>& m2) {
	return operator+<M, N, Container1, Container2, DefaultMatrixContainer<M, N>>(
			m1, m2);
}

/**
 * Computes summ of two matrixes. Specialized implementation, made in assumption that all matrixes
 * use default matrix container.
 *
 * @tparam M First matrix dimension.
 * @tparam N Second matrix dimension.
 * @tparam Container Container type for all matrixes.
 * @param m1 First summ item.
 * @param m2 Second summ item.
 *
 * @return Matrix summ (m1+m2).
 */
template<uint M, uint N, typename Container>
Matrix<M, N, Container> operator+(const Matrix<M, N, Container>& m1,
		const Matrix<M, N, Container>& m2) 
{
	return operator+<M, N, Container, Container, Container>(m1, m2);
}

template<uint M, uint N, typename Container>
Matrix<M, N, Container>& Matrix<M, N, Container>::operator+=(const Matrix<M, N, Container>& m)
{
	for (uint i = 0; i < M; i++)
		for (uint j = 0; j < N; j++)
			(*this)(i, j) += m(i, j);

	return *this;
}

/**
 * Computes difference of two matrixes. Generic implementation.
 *
 * @tparam M First matrix dimension.
 * @tparam N Second matrix dimension.
 * @tparam Container1 Container type for first difference item.
 * @tparam Container2 Container type for second  difference item.
 * @tparam Container3 Container type for result.
 * @param m1 First difference item.
 * @param m2 Second difference item.
 *
 * @return Matrix difference (m1-m2).
 */
template<uint M, uint N, typename Container1, typename Container2, typename Container3>
Matrix<M, N, Container3> operator-(const Matrix<M, N, Container1>& m1,
		const Matrix<M, N, Container2>& m2) {
	Matrix<M, N, Container3> result;

	for (uint i = 0; i < M; i++)
		for (uint j = 0; j < N; j++)
			result(i, j) = m1(i, j) - m2(i, j);

	return result;
}

/**
 * Computes difference of two matrixes. Most useful specialization, made in assumption that result matrix should
 * use default matrix container.
 *
 * @tparam M First matrix dimension.
 * @tparam N Second matrix dimension.
 * @tparam Container1 Container type for first difference item.
 * @tparam Container2 Container type for second  difference item.
 * @param m1 First difference item.
 * @param m2 Second difference item.
 *
 * @return Matrix difference (m1-m2).
 */
template<uint M, uint N, typename ElemType,
		typename Container1, typename Container2>
Matrix<M, N, DefaultMatrixContainer<M, N>> operator-(
		const Matrix<M, N, Container1>& m1,
		const Matrix<M, N, Container2>& m2) {
	return operator-<M, N, Container1, Container2, DefaultMatrixContainer<M, N>>(
			m1, m2);
}

/**
 * Computes difference of two matrixes. Specialized implementation, made in assumption that all matrixes
 * use default matrix container.
 *
 * @tparam M First matrix dimension.
 * @tparam N Second matrix dimension.
 * @tparam Container Container type for all matrixes.
 * @param m1 First difference item.
 * @param m2 Second difference item.
 *
 * @return Matrix difference (m1-m2).
 */
template<uint M, uint N, typename Container>
Matrix<M, N, Container> operator-(const Matrix<M, N, Container>& m1,
		const Matrix<M, N, Container>& m2) {
	return operator-<M, N, Container, Container, Container>(m1, m2);
}

template<uint M, uint N, typename Container>
Matrix<M, N, Container>& Matrix<M, N, Container>::operator-=(const Matrix<M, N, Container>& m)
{
	for (uint i = 0; i < M; i++)
		for (uint j = 0; j < N; j++)
			(*this)(i, j) -= m(i, j);

	return *this;
}

/**
 * Computes product of two matrixes. Generic implementation.
 *
 * @tparam M First dimension of first matrix (M x N).
 * @tparam N First (second) dimension of second (first) matrix (M x N or N x K respectively).
 * @tparam K Second dimension of second matrix (N x K).
 * @tparam Container1 Container type for first product item.
 * @tparam Container2 Container type for second  product item.
 * @tparam Container3 Container type for result.
 * @param m1 First product item.
 * @param m2 Second product item.
 *
 * @return Matrix product (m1*m2).
 */
template<uint M, uint N, uint K, typename Container1, typename Container2,
		typename Container3>
Matrix<M, K, Container3> operator*(const Matrix<M, N, Container1>& m1,
		const Matrix<N, K, Container2>& m2) {
	Matrix<M, K, Container3> result;

	for (uint i = 0; i < M; i++)

		for (uint j = 0; j < K; j++) {
			result(i, j) = 0;
			for (uint n = 0; n < N; n++)
				result(i, j) += m1(i, n) * m2(n, j);
		}

	return result;
}

/**
 * Computes product of two matrixes. Most useful specialization, made in assumption that result matrix should
 * use default matrix container.
 *
 * @tparam M First dimension of first matrix (M x N).
 * @tparam N First (second) dimension of second (first) matrix (M x N or N x K respectively).
 * @tparam K Second dimension of second matrix (N x K).
 * @tparam Container1 Container type for first product item.
 * @tparam Container2 Container type for second  product item.
 * @param m1 First product item.
 * @param m2 Second product item.
 *
 * @return Matrix product (m1*m2).
 */
template<uint M, uint N, uint K, typename Container1, typename Container2>
Matrix<M, K, DefaultMatrixContainer<M, K>> operator*(
		const Matrix<M, N, Container1>& m1,
		const Matrix<N, K, Container2>& m2) {
	return operator*<M, N, K, Container1, Container2,
			DefaultMatrixContainer<M, K>>(m1, m2);
}

/**
 * Computes product of two matrixes. Most useful specialization, made in assumption that both matrixes are
 * square and have the same container type.
 *
 * @tparam M Matrix size.
 * @tparam Container Container type for first product item.
 * @param m1 First product item.
 * @param m2 Second product item.
 *
 * @return Matrix product (m1*m2).
 */
template<uint M, typename Container>
Matrix<M, M, Container> operator*(const Matrix<M, M, Container>& m1,
		const Matrix<M, M, Container>& m2) {
	return operator*<M, M, M, Container, Container, Container>(m1, m2);
}

/**
 * Performs scalar multiplication.
 *
 * @tparam M First matrix dimesion.
 * @tparam N Second matrix dimension.
 * @tparam Container Container type of matrix.
 * @param m Matrix to multiply.
 * @param x Scalar to multiply by.
 *
 * @return Result of scalar multiplication.
 */
template<uint M, uint N, typename Container>
Matrix<M, N, Container> operator*(const Matrix<M, N, Container>& m,
		const typename Matrix<M, N, Container>::DataType x)
{
	Matrix<M, N, Container> result;

	for (uint i = 0; i < M; i++)
		for (uint j = 0; j < N; j++)
			result(i, j) = m(i, j) * x;

	return result;
}

/**
 * Performs scalar multiplication.
 *
 * @tparam M First matrix dimesion.
 * @tparam N Second matrix dimension.
 * @tparam Container Container type of matrix.
 * @param x ElemType to multiply by.
 * @param m Matrix to multiply.
 *
 * @return Result of scalar multiplication.
 */
template<uint M, uint N, typename Container>
Matrix<M, N, Container> operator*(const typename Matrix<M, N, Container>::DataType x,
		const Matrix<M, N, Container>& m) {
	return m * x;
}

/**
 * Performs scalar division.
 *
 * @tparam M First matrix dimesion.
 * @tparam N Second matrix dimension.
 * @tparam Container Container type of matrix.
 * @param m Matrix to divide.
 * @param x ElemType to divide by.
 *
 * @return Result of scalar division.
 */
template<uint M, uint N, typename Container>
Matrix<M, N, Container> operator/(const Matrix<M, N, Container>& m,
		const typename Matrix<M, N, Container>::DataType x) {
	return m * (1 / x);
}

template<uint M, uint N, typename Container1, typename Container2>
bool operator==(const Matrix<M, N, Container1>& m1,
		const Matrix<M, N, Container2>& m2) {
	for (uint i = 0; i < M; i++)
		for (uint j = 0; j < N; j++)
			// FIXME Should this constant be replaced by something context-specific?
			if (fabs(m1(i, j) - m2(i, j)) > EQUALITY_TOLERANCE)
				return false;

	return true;
}

template<uint M, uint N, typename Container1, typename Container2>
bool operator!=(const Matrix<M, N, Container1>& m1,
		const Matrix<M, N, Container2>& m2) {
	return !(m1 == m2);
}

template<uint M, uint N, typename Container>
Matrix<M, N, Container> multiply(const Matrix<M, N, Container>& m1, const Matrix<M, N, Container>& m2)
{
	Matrix<M, N, Container> result;

	for (uint i = 0; i < M; i++)
		for (uint j = 0; j < N; j++)
			result(i, j) = m1(i, j) * m2(i, j);

	return result;
};

template<uint M, uint N, typename Container>
Matrix<M, N, Container> divide(const Matrix<M, N, Container>& m1, const Matrix<M, N, Container>& m2)
{
	Matrix<M, N, Container> result;

	for (uint i = 0; i < M; i++)
		for (uint j = 0; j < N; j++)
		{
			if (std::abs(m2(i, j)) > EQUALITY_TOLERANCE)
				result(i, j) = m1(i, j) / m2(i, j);
			else
				result(i, j) = std::numeric_limits<Scalar>::infinity();
		}

	return result;
};

template<uint M, uint N, typename Container>
Matrix<M, N, Container> max(const Matrix<M, N, Container>& m1, const Matrix<M, N, Container>& m2)
{
	Matrix<M, N, Container> result;

	for (uint i = 0; i < M; i++)
		for (uint j = 0; j < N; j++)
			result(i, j) = std::max(m1(i, j), m2(i, j));

	return result;
};

template<uint M, uint N, typename Container>
Matrix<M, N, Container> min(const Matrix<M, N, Container>& m1, const Matrix<M, N, Container>& m2)
{
	Matrix<M, N, Container> result;

	for (uint i = 0; i < M; i++)
		for (uint j = 0; j < N; j++)
			result(i, j) = std::min(m1(i, j), m2(i, j));

	return result;
};

template<uint M, uint N, typename Container>
Matrix<M, N, Container> abs(const Matrix<M, N, Container>& m)
{
	Matrix<M, N, Container> result;

	for (uint i = 0; i < M; i++)
		for (uint j = 0; j < N; j++)
			result(i, j) = std::abs(m(i, j));

	return result;
};

	/**
	 * Definition of Vector class
	 */
	template<uint M, typename Container = DefaultMatrixContainer<M, 1> > using Vector = Matrix<M, 1, Container>;
};

namespace std {
using data::uint;
using data::Scalar;
using data::Matrix;

template<uint M, uint N, typename Container>
inline std::ostream& operator<<(std::ostream &os,
		const Matrix<M, N, Container>& mat) {
	for (uint i = 0; i < M; i++) {
		for (uint j = 0; j < N; j++)
			os << mat(i, j) << "\t";

		os << "\n";
	}

	return os;
};
};

#endif /* MATRIX_HPP_ */
