// 2. Матрица – KMatrix
// 	@конструкторы, @деструктор;
// 	операции: @[], @=, @==, @!=, @+, @+=, @–, @–=, @*, @*=, <<, >>
// 	функции:
// 		@Transpose – транспонирование матрицы,
// 		@Rows() – количество строк,
// 		@Cols() – количество колонок,
// 		@Swap()  - обменять значения (т.е. матрицы).

import java.lang.reflect.Array;
import java.util.AbstractList;
import java.util.Arrays;
import java.lang.Number;

class Calc {
	public static <T extends Number> boolean isInteger(T a) {
		return a.getClass() == Integer.class;
	}

	public static <T extends Number> boolean isDouble(T a) {
		return a.getClass() == Double.class;
	}

	public static <T extends Number> T zero(T a) throws Exception {
		if (isInteger(a)) return (T)new Integer(0);
		if (isDouble(a)) return (T)new Double(0);
	    throw new Exception("Unsupported Numbers.");
	}

	public static <T extends Number> T add (T a, T b) throws Exception {
		if (isInteger(a)) {
	        return (T)(Integer)((Integer)a + (Integer)b);
	    }
	    if (isDouble(a)) {
	        return (T)(Double)((Double)a + (Double)b);
	    }
	    throw new Exception("Unsupported Numbers.");
	}

	public static <T extends Number> T sub (T a, T b) throws Exception {
		if (isInteger(a)) {
	        return (T)(Integer)((Integer)a - (Integer)b);
	    }
	    if (isDouble(a)) {
	        return (T)(Double)((Double)a - (Double)b);
	    }
	    throw new Exception("Unsupported Numbers.");
	}

	public static <T extends Number> T multiply (T a, T b) throws Exception {
		if (isInteger(a)) {
	        return (T)(Integer)((Integer)a * (Integer)b);
	    }
	    if (isDouble(a)) {
	        return (T)(Double)((Double)a * (Double)b);
	    }
	    throw new Exception("Unsupported Numbers.");
	}
}

class Matrix<T extends Number & Comparable<T>> extends AbstractList implements Cloneable {

	private T[][] data;

	public Matrix(int row, int col, Object fill) {
	    data = (T[][]) Array.newInstance(fill.getClass(), row, col);
	    for (int i = 0; i < row; i++) {
	        for (int j = 0; j < col; j++) {
	            data[i][j] = (T) fill;
	        }
    	}
	}

	public Matrix(T[][] m) {
		int row = m.length;
		if (row == 0) return;
		int col = m[0].length;
		if (col == 0) return;
	    data = (T[][]) Array.newInstance(m[0][0].getClass(), row, col);
	    for (int i = 0; i < row; i++) {
	        for (int j = 0; j < col; j++) {
	            data[i][j] = (T)m[i][j];
	        }
    	}	
	}

	public String toString() {
		int row = rows();
		String s = "Array " + rows() + "*" + cols() + ":\n";
		for (int i = 0; i < row; ++i) {	
			s += Arrays.toString(data[i]) + "\n";
		}
		return s;
	}

	public Matrix<T> clone() {
		return new Matrix<T>(data);
	}

	@Override
	public boolean equals(Object obj) {
		if (obj.getClass() == Matrix.class) {
			Matrix<T> m = (Matrix<T>)obj;
			if (empty()) return false;
			int row = rows();
			int col = cols();
			if (rows() != m.rows() || cols() != m.cols()) return false;
			for (int i = 0; i < row; ++i) {
				for (int j = 0; j < col; ++j) {
					if (!data[i][j].equals(m.data[i][j])) return false;
				}
			}
			return true;
			
		} else {
			return obj.equals((Object)this);
		}
	}

	public T[] get(int i) throws IndexOutOfBoundsException {
		if (i >= size()) {
			throw new IndexOutOfBoundsException();
		}
		return data[i];
	}

	public int size() {
		return rows();
	}

	public int rows() {
		return data.length;
	}

	public int cols() {
		return (data.length == 0 ? 0 : data[0].length);
	}

	public boolean empty() {
		return rows() == 0 || cols() == 0;
	}

	public void transpose() {
		if (empty()) return;
		T[][] tmp = data;
		int row = this.rows();
		int col = this.cols();
	    data = (T[][]) Array.newInstance(data[0][0].getClass(), col, row);
		for (int i = 0; i < row; i++) {
	        for (int j = 0; j < col; j++) {
	            data[j][i] = (T)tmp[i][j];
	        }
    	}
	}

	public void swap(Matrix<T> m) {
		T[][] tmp = data;
		data = m.data;
		m.data = tmp;
	}

	public boolean isInteger() throws Exception {
		if (empty()) throw new Exception("Matrix is empty");
		return data[0][0].getClass() == Integer.class;
	}

	public boolean isDouble() throws Exception {
		if (empty()) throw new Exception("Matrix is empty");
		return data[0][0].getClass() == Double.class;
	}

	public void add(Matrix<T> m) throws Exception {
		if (rows() != m.rows() || cols() != m.cols()) {
			throw new Exception("Different dimensions.");
		}
		int row = this.rows();
		int col = this.cols();
		for (int i = 0; i < row; i++) {
	        for (int j = 0; j < col; j++) {
	            data[i][j] = Calc.<T>add(data[i][j], m.data[i][j]);
	        }
    	}
	}

	public void sub(Matrix<T> m) throws Exception {
		if (rows() != m.rows() || cols() != m.cols()) {
			throw new Exception("Different dimensions.");
		}
		int row = this.rows();
		int col = this.cols();
		for (int i = 0; i < row; i++) {
	        for (int j = 0; j < col; j++) {
	            data[i][j] = Calc.<T>sub(data[i][j], m.data[i][j]);
	        }
    	}
	}

	public void multiply(Matrix<T> m) throws Exception {
		if (empty() || m.empty()) throw new Exception("Matrix is empty");
		if (cols() != m.rows()) throw new Exception("Wrong dimensions");
		T[][] tmp = data;
		int row = rows();
		int col = m.cols();
		int shared = cols();
			
	    data = (T[][]) Array.newInstance(tmp[0][0].getClass(), row, col);
		for (int i = 0; i < row; ++i) {
			for (int j = 0; j < col; ++j) {
				data[i][j] = Calc.<T>zero(tmp[0][0]);
				for (int l = 0; l < shared; ++l) {
					data[i][j] = Calc.<T>add(data[i][j], Calc.multiply(tmp[i][l], m.data[l][j]));
				}
			}
		}
	}

}

public class Main {
	public static void main(String[] args) {
		try {
			Integer[][] ia = new Integer[][]{{1,0,1},{0,1,0}};
			Double[][] da = new Double[][]{{0.,1.,0.},{1.,0.,1.}};
			Matrix<Integer> im = new Matrix(ia);
			System.out.println(im);
			Matrix<Integer> imc = im.clone();
			Matrix<Integer> imcc;
			imc.add(im);
			System.out.println(imc);
			imc.transpose();
			System.out.println(imc);
			im.multiply(imc);
			System.out.println(im);
			im.swap(imc);
			System.out.println(im);
			imcc = im;
			Matrix<Integer> imccc = im.clone();
			System.out.println(im.equals(imcc));
			System.out.println(im.equals(imccc));
		} catch (Exception e) {
			System.out.println(e.getMessage());
		}
	}
}