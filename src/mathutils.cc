#include <mathutils.h>

#include <math.h>

#include <iostream>
#include <assert.h>

Vector3d Vector3dZero (0., 0., 0.);
Matrix3d Matrix3dIdentity (
		1., 0., 0.,
		0., 1., 0.,
		0., 0., 1
		);
Matrix3d Matrix3dZero (
		0., 0., 0.,
		0., 0., 0.,
		0., 0., 0.
		);
SpatialMatrix SpatialMatrixIdentity (
		1., 0., 0., 0., 0., 0.,
		0., 1., 0., 0., 0., 0.,
		0., 0., 1., 0., 0., 0.,
		0., 0., 0., 1., 0., 0.,
		0., 0., 0., 0., 1., 0.,
		0., 0., 0., 0., 0., 1.
		);

void VectorCrossVector (Vector3d &result, const Vector3d &vec_a, const Vector3d &vec_b) {
	result[0] = vec_a[1]*vec_b[2] - vec_a[2]*vec_b[1];
	result[1] = vec_a[2]*vec_b[0] - vec_a[0]*vec_b[2];
	result[2] = vec_a[0]*vec_b[1] - vec_a[1]*vec_b[0];
}

void VectorPrint (const char* msg, const Vector3d &vector) {
	std::cout << msg;
	int i;
	for (i = 0; i < 3; i++)
		std::cout << vector[i] << "\t";
	std::cout << std::endl;
}

void MatrixPrint (const char* msg, const Matrix3d &matrix) {
	std::cout << msg;
	int i, j;
	for (i = 0; i < 3; i++) {
		for (j = 0; j < 3; j++) {
			std::cout << matrix(i,j) << "\t";
		}
		std::cout << std::endl;
	}
}

inline void MatrixSetIdentity (Matrix3d &result) {
	result(0,0) = 1.;
	result(0,1) = 0.;
	result(0,2) = 0.;

	result(1,0) = 0.;
	result(1,1) = 1.;
	result(1,2) = 0.;
	
	result(2,0) = 0.;
	result(2,1) = 0.;
	result(2,2) = 1.;
}

inline void MatrixSetZero (Matrix3d &result) {
	result(0,0) = 0.;
	result(0,1) = 0.;
	result(0,2) = 0.;

	result(1,0) = 0.;
	result(1,1) = 0.;
	result(1,2) = 0.;
	
	result(2,0) = 0.;
	result(2,1) = 0.;
	result(2,2) = 0.;
}

inline void MatrixCopyTranspose (Matrix3d &result, const Matrix3d &src) {
	int i,j;
	for (i = 0; i < 3; i++) {
		for (j = 0; j < 3; j++) {
			result(i,j) = src(i,j);
		}
	}
}

inline void MatrixCopy (const Matrix3d &result, Matrix3d &src) {
	src = result;
}

Matrix3d VectorCrossMatrix (const Vector3d &vector) {
	return Matrix3d (
			         0, -vector[2],  vector[1],
			 vector[2],          0, -vector[0],
			-vector[1],  vector[0], 0);
}

void SpatialMatrixSetSubmatrix(SpatialMatrix &dest, unsigned int row, unsigned int col, const Matrix3d &matrix) {
	assert (row < 2 && col < 2);
	
	dest(row*3,col*3) = matrix(0,0);
	dest(row*3,col*3 + 1) = matrix(0,1);
	dest(row*3,col*3 + 2) = matrix(0,2);

	dest(row*3 + 1,col*3) = matrix(1,0);
	dest(row*3 + 1,col*3 + 1) = matrix(1,1);
	dest(row*3 + 1,col*3 + 2) = matrix(1,2);

	dest(row*3 + 2,col*3) = matrix(2,0);
	dest(row*3 + 2,col*3 + 1) = matrix(2,1);
	dest(row*3 + 2,col*3 + 2) = matrix(2,2);
}

bool SpatialMatrixCompareEpsilon (const SpatialMatrix &matrix_a, const SpatialMatrix &matrix_b, double epsilon) {
	assert (epsilon >= 0.);
	unsigned int i, j;

	for (i = 0; i < 6; i++) {
		for (j = 0; j < 6; j++) {
			if (fabs(matrix_a(i,j) - matrix_b(i,j)) >= epsilon) {
				std::cerr << "Expected:" 
					<< std::endl << matrix_a << std::endl
					<< "but was" << std::endl 
					<< matrix_b << std::endl;
				return false;
			}
		}
	}

	return true;
}