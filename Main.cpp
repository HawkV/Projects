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

		/*vector<T> CharacterValues(T precision)
		{
			vector<T> charValues(height);   
			vector<T> intervals(height);

			for (int i = 0; i < height; i++)
			{
				T interval = 0;

				for (int j = 0; j < width; j++)
				{
					if (i != j)
					{
						interval += abs(matrix[i][j]);
					}
				}

				intervals[i] = interval;
			}

			T charValue1, charValue2;

			for (int i = 0; i < height; i++)
			{
				charValue1 = matrix[i][i] + intervals[i];
				charValue2 = matrix[i][i] - intervals[i];
				
				while(abs(CharDet(charValue2)) > precision)
				{ 
					charValue1 = ChordMethod(charValue1, charValue2);

					charValue1 += charValue2;
					charValue2 = charValue1 - charValue2;
					charValue1 -= charValue2;

					cout << charValue2 << ": " << CharDet(charValue2) << endl;
				}

				charValues[i] = charValue2;
				cout << endl << charValue2;
				cout << endl << endl;
			}

			return charValues;
		}*/
			
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
};

template <typename T>
class QuadSurface
{
	public:
		QuadSurface(vector<T> coefArray)
		{
			int emptyCount = 10 - coefArray.size();
			for (int i = 0; i < empty; i++)
			{
				coefArray.push_back(0);
			}

			this->coefArray = coefArray;

			///Invariants

		}
			
		T I1, I2, I3, I3_half, I2_half, I_Char;

		vector<T> coefArray;// a11, a22, a33, a12, a23, a13, a14, a24, a34, a44;
};


int main()
{
	cout << "" << std::endl;

	SquareMatrix<double> m1(3, vector<double>{1, 2, 3, 4, 5, 6, 7, 8, 9});
	
	SquareMatrix<double> m2(m1);

	double a = m1.Determinant();

	system("pause>>null");

	return 0;
}
