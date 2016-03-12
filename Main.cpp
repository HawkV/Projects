#include <iostream>
#include <string>
#include <vector>
using namespace std;

template <typename T>
class Matrix
{
	public:
		Matrix<T>(T _height, T _width, vector<T> args) : height(_height), width(_width)
		{
			vector<vector<T>> initMatrix(height, vector<T> (width));

			T num = 0;
			
			if (args.size() < width * height)
			{
				int emptyCount = width * height - args.size();

				for (int i = 0; i < emptyCount; i++)
				{
					args.push_back(0);
				}
			}

			for (int i = 0; i < height; i++)
			{
				for (int j = 0; j < width; j++)
				{
					initMatrix[i][j] = args[i * width + j];
				}
			}

			matrix = initMatrix;
		}

		vector<T> operator[] (int index)
		{
			return matrix[index];
		}

		Matrix<T> operator+ (const Matrix& mat)
		{
			if (mat.height == height && mat.width == width)
			{
				Matrix tempMat(*this);

				for (int i = 0; i < height; i++)
				{
					for (int j = 0; j < width; j++)
					{
						 tempMat.matrix[i][j] += mat.matrix[i][j];
					}
				}

				return tempMat;
			}
			else
			{
				throw exception("Matrix sizes aren't equal");
			}
		}
		Matrix<T> operator- (const Matrix& mat)
		{
			if (mat.height == height && mat.width == width)
			{
				Matrix tempMat(*this);

				for (int i = 0; i < height; i++)
				{
					for (int j = 0; j < width; j++)
					{
						tempMat.matrix[i][j] -= mat.matrix[i][j];
					}
				}

				return tempMat;
			}
			else
			{
				throw exception("Matrix sizes aren't equal");
			}
		}
		Matrix<T> operator* (const Matrix& mat)
		{
			Matrix tempMat(height, mat.width);

			if (width == mat.height)
			{
				for (int i = 0; i < tempMat.height; i++)
				{
					for (int j = 0; j < tempMat.width; j++)
					{
						for (int r = 0; r < mat.height; r++)
						{
							tempMat.matrix[i][j] += this->matrix[i][r] * mat.matrix[r][j];
						}
					}
				}
			}
			else
			{
				throw exception("Invalid matrix sizes");
			}

			return tempMat;
		}

		Matrix<T> operator+= (const Matrix& mat)
		{
			for (int i = 0; i < height; i++)
			{
				for (int j = 0; j < width; j++)
				{
					matrix[i][j] += mat.matrix[i][j];
				}
			}

			return *this;
		}
		Matrix<T> operator-= (const Matrix& mat)
		{
			for (int i = 0; i < height; i++)
			{
				for (int j = 0; j < width; j++)
				{
					matrix[i][j] -= mat.matrix[i][j];
				}
			}

			return *this;
		}
		Matrix<T> operator*= (const Matrix& mat)
		{
			Matrix tempMat(*this);

			*this = tempMat * (*this);

			return *this;
		}

		void Transpose()
		{
			Matrix tempMat(width, height);

			for (int i = 0; i < width; i++)
			{
				for (int j = 0; j < height; j++)
				{
					tempMat[i][j] = matrix[j][i];
				}
			}
		}
		void out()
		{
			cout << endl;

			for (int i = 0; i < height; i++)
			{
				for (int j = 0; j < width; j++)
				{
					cout << matrix[i][j] << " ";
				}

				cout << endl;
			}

			cout << endl;
		}

		int height, width;
	
		vector<vector<T>>  matrix;
};

template <typename T>
class SquareMatrix : public Matrix<T>
{
	public:
		SquareMatrix<T>(int dimensionNum, vector<T> args) : Matrix(dimensionNum, dimensionNum, args)
		{
		}

		SquareMatrix operator= (Matrix<T> const & mat)
		{
			if (mat.height == mat.width)
			{
				height = mat.height;
				width = mat.width;

				matrix = mat.matrix;
			}
			else
			{
				throw exception("");
			}

			return *this;
		}

		T Determinant()
		{
			SquareMatrix det(*this);

			for (int i = 0; i < height; i++)
			{
				if(det[i][i] == 0)
				{
					for (int j = i; j < height; j++)
					{
						if (det[i][j] != 0)
						{
							det.swapStr(0, j);
						}
					}

					if (det[i][i] == 0)
					{
						return 0;
					}
				}

				for (int j = i + 1; j < height; j++)
				{
					det.addStr(i, j, -det[j][i] / det[i][i]);
				}
			}

			int result = 1;

			for (int i = 0; i < height; i++)
			{
				result *= det[i][i];
			}

			return result;
		}
		T CharDet(T variable)
		{
			SquareMatrix temp(*this);

			for (int i = 0; i < height; i++)
			{
				temp.matrix[i][i]  -= variable;
			}

			return temp.Determinant();
		}
		T Trace()
		{
			T sum = 0;

			for (int i = 0; i < width; i++)
			{
				sum += matrix[i][i];
			}

			return sum;
		}
			
		void swapStr(int index1, int index2)
		{
			for (int i = 0; i < width; i++)
			{
				matrix[index1][i] += matrix[index2][i];
				matrix[index2][i] = matrix[index1][i] - matrix[index2][i];
				matrix[index1][i] -= matrix[index2][i];
			}
		}
		void addStr(int from, int to, T multiplier)
		{
			for (int i = 0; i < width; i++)
			{
				matrix[to][i] += multiplier * matrix[from][i];
			}
		}
		
		SquareMatrix<T> delRowAndCol (int row, int column)
		{
			vector<T> newData(0);

			for (int i = 0; i < width; i++)
			{
				for (int j = 0; j < width; j++)
				{
					if (i != row && j != column)
					{
						newData.push_back(matrix[i][j]);
					}
				}
			}

			SquareMatrix<T> newMat(width - 1, newData);

			return newMat;
		}
};

template <typename T>
class QuadSurface
{
	public:
		QuadSurface(vector<T> coefArray)
		{
			///
			int emptyElemCount = 10 - coefArray.size();

			for (int i = 0; i < emptyElemCount; i++)
			{
				coefArray.push_back(0);
			}

			a11 = coefArray[0];
			a22 = coefArray[1];
			a33 = coefArray[2];
			a12 = coefArray[3] / 2;
			a23 = coefArray[4] / 2;
			a13 = coefArray[5] / 2;
			a14 = coefArray[6] / 2;
			a24 = coefArray[7] / 2;
			a34 = coefArray[8] / 2;
			a44 = coefArray[9] / 2;
		}

		void FindSurfaceType()
		{
			I1 = a11 + a22 + a33;

			SquareMatrix<T> J3(3, vector<T>{a11, a12, a13,
										a12, a22, a23,
										a13, a23, a33});

			I3 = J3.Determinant();

			SquareMatrix<T>J2(2, vector<T>{a11, a12,
										a12, a22});

			I2 = J2.Determinant();

			J2.matrix[0][1] = a13;
			J2.matrix[1][0] = a13;
			J2.matrix[1][1] = a33;

			I2 += J2.Determinant();

			J2.matrix[0][0] = a22;
			J2.matrix[0][1] = a23;
			J2.matrix[1][0] = a23;

			I2 += J2.Determinant();
			
			SquareMatrix<T> J4(4, vector<T>{a11, a12, a13, a14,
										a12, a22, a23, a24,
										a13, a23, a33, a34,
										a14, a24, a34, a44});

			if (I3 == 0)
			{
				if (I2 == 0)
				{
					I3_half = J4.delRowAndCol(2, 2).Determinant() + J4.delRowAndCol(1, 1).Determinant() + J4.delRowAndCol(0, 0).Determinant();

					if (I3_half == 0)
					{
						SquareMatrix<T> J2_half(2, vector<T>{a11, a14,
														 a14, a44});

						I2_half = J2_half.Determinant();

						J2.matrix[0][0] = a22;
						J2.matrix[0][1] = a24;
						J2.matrix[1][0] = a24;

						I2_half += J2_half.Determinant();

						J2.matrix[0][0] = a33;
						J2.matrix[0][1] = a34;
						J2.matrix[1][0] = a34;

						I2_half += J2_half.Determinant();

						cout << I1 << "x^2 + " << I2_half / I1;
					}
					else
					{
						cout << I1 << "x^2 + " << sqrt(-I3_half / I1) << "y";
					}
				}
				else
				{
					///найти корни хар. полинома

					T D = pow(I1, 2) - 4 * I2;

					cout << I1 + sqrt(D) << "x^2 + " << I1 - sqrt(D) << "y^2 + ";

					I4 = J4.Determinant();

					if (I4 == 0)
					{
						cout << I3_half / I2;
					}
					else
					{
						cout << 2 * sqrt(-I4 / I2) << "z";
					}
				}
			}
			else
			{
				T Q = (I1*I1 - 3*I2) / 9;
				T R = (-2*pow(I1, 3) + 9 * I1 * I2 - 27 * I3) / 54;

				T t = R / pow(Q, 3 / 2);
				t = acos(t) / 3;
				T x1 = -2 * sqrt(Q) * cos(t) + I1 / 3;
				T x2 = -2 * sqrt(Q) * cos(t + (2 * 3.14 / 3)) + I1 / 3;
				T x3 = -2 * sqrt(Q) * cos(t - (2 * 3.14 / 3)) + I1 / 3;

				cout << x1 << "x^2 + (" << x2 << ")y^2 + (" << x3 << ")z^2 + (" << J4.Determinant() / I3 << ")";
			}
		}
			
		T I1, I2, I3, I3_half, I2_half, I4, I_Char;

		T a11, a22, a33, a12, a23, a13, a14, a24, a34, a44;
};


int main()
{
	cout << "" << std::endl;
	s.FindSurfaceType();
	system("pause>>null");

	return 0;
}
