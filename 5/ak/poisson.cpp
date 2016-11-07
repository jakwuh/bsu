#include <mpi.h>
#include <iostream>
#include <fstream>
#include <time.h>
#include <assert.h>
#include <vector>
#include <memory>
#include <cmath>

#define DEBUG 1
#define ROOT 0

using std::unique_ptr;
using std::vector;

double current_time();

double f(double x, double y);

double f_top(double x);

double f_right(double y);

double f_bottom(double x);

double f_left(double y);

struct Profiler {
    double start_preparing, end_preparing;
    double start_calculating, end_calculating;
    double start_sending, end_sending;
};

struct Point {
    double x, y;

    Point(double _x, double _y) : x(_x), y(_y) {
    }
};

template<typename T>
struct Square {
    T top, right, bottom, left;

    Square() {}

    Square(T _top, T _right, T _bottom, T _left)
            : top(_top), right(_right), bottom(_bottom), left(_left) {
    }
};

typedef Square<long> Area;

class Cell {
private:
    double step_x, step_y, sqr_step_x, sqr_step_y, weight, residual;
    long rows, columns;
    vector <vector<double>> inner_lines;
    unique_ptr<double[]>
            top_border, adjacent_top_border,
            right_border, adjacent_right_border,
            bottom_border, adjacent_bottom_border,
            left_border, adjacent_left_border;

    Area area, calc_area, world_area;
    Point left_top;

public:
    Cell(Area _world_area, Area _area, Point _left_top, double _step_x, double _step_y)
            : world_area(_world_area), area(_area), left_top(_left_top),
              step_x(_step_x), step_y(_step_y) {
        rows = area.bottom - area.top;
        columns = area.right - area.left;

        auto to_number = [](bool a) { return static_cast<long>(a); };

        calc_area.top = to_number(area.top == world_area.top);
        calc_area.left = to_number(area.left == world_area.left);
        calc_area.right = columns - to_number(area.right == world_area.right);
        calc_area.bottom = rows - to_number(area.bottom == world_area.bottom);

        auto allocate_zeros = [](long n) {
            auto ptr = new double[n];
            std::fill_n(ptr, n, 0);
            return ptr;
        };

        if (rows > 0 && columns > 0) {
            sqr_step_x = step_x * step_x;
            sqr_step_y = step_y * step_y;
            weight = 1. / (2 * (1. / sqr_step_x + 1. / sqr_step_y));

            top_border.reset(allocate_zeros(columns));
            left_border.reset(allocate_zeros(rows));
            bottom_border.reset(allocate_zeros(columns));
            right_border.reset(allocate_zeros(rows));

            if (area.top != world_area.top) {
                adjacent_top_border.reset(allocate_zeros(columns));
            } else {
                for (long j = 0; j < columns; ++j) {
                    set(0, j, f_top(left_top.x + step_x * j));
                }
            }

            if (area.bottom != world_area.bottom) {
                adjacent_bottom_border.reset(allocate_zeros(columns));
            } else {
                for (long j = 0; j < columns; ++j) {
                    set(rows - 1, j, f_bottom(left_top.x + step_x * j));
                }
            }

            if (area.left != world_area.left) {
                adjacent_left_border.reset(allocate_zeros(rows));
            } else {
                for (long i = 0; i < rows; ++i) {
                    set(i, 0, f_left(left_top.y + step_y * i));
                }
            }

            if (area.right != world_area.right) {
                adjacent_right_border.reset(allocate_zeros(rows));
            } else {
                for (long i = 0; i < rows; ++i) {
                    set(i, columns - 1, f_right(left_top.y + step_y * i));
                }
            }
        }

        if (rows > 2 && columns > 2) {
            inner_lines.resize(rows - 2);
            for (auto &it : inner_lines) {
                it.resize(columns - 2, 0);
            }
        }
    }

    double get(long i, long j) {
        if (j == -1) {
            return adjacent_left_border[i];
        } else if (j == columns) {
            return adjacent_right_border[i];
        } else if (i == -1) {
            return adjacent_top_border[j];
        } else if (i == rows) {
            return adjacent_bottom_border[j];
        } else if (j == 0) {
            return left_border[i];
        } else if (j == columns - 1) {
            return right_border[i];
        } else if (i == 0) {
            return top_border[j];
        } else if (i == rows - 1) {
            return bottom_border[j];
        } else {
            return inner_lines[i - 1][j - 1];
        }
    }

    void set(long i, long j, double value) {
        if (j == -1) {
            adjacent_left_border[i] = value;
        } else if (j == columns) {
            adjacent_right_border[i] = value;
        } else if (i == -1) {
            adjacent_top_border[j] = value;
        } else if (i == rows) {
            adjacent_bottom_border[j] = value;
        } else {
            if (j == 0) {
                left_border[i] = value;
            }
            if (j == columns - 1) {
                right_border[i] = value;
            }
            if (i == 0) {
                top_border[j] = value;
            }
            if (i == rows - 1) {
                bottom_border[j] = value;
            }
            if (i > 0 && i < rows - 1 && j > 0 && j < columns - 1) {
                inner_lines[i - 1][j - 1] = value;
            }
        }
    }

    void debug() {
        MPI_Barrier(MPI_COMM_WORLD);

        for (long i = -1; i <= rows; ++i) {
            for (long j = -1; j <= columns; ++j) {
                bool crit1 = i == -1 && (!adjacent_top_border.get() || (j == -1 || j == columns));
                bool crit2 = i == rows && (!adjacent_bottom_border.get() || (j == -1 || j == columns));
                bool crit3 = j == -1 && (!adjacent_left_border.get() || (i == -1 || i == rows));
                bool crit4 = j == columns && (!adjacent_right_border.get() || (i == -1 || i == rows));
                if (crit1 || crit2 || crit3 || crit4) {
                    std::cout << "null\t";
                } else {
                    std::cout << get(i, j) << '\t';
                }
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
        MPI_Barrier(MPI_COMM_WORLD);
    }

    void calculate() {
        if (DEBUG) {
            printf("Calculating: top: %ld, left: %ld, bottom: %ld, right: %ld\n",
                   calc_area.top, calc_area.left, calc_area.bottom, calc_area.right);
        }

        residual = 0;
        for (long i = calc_area.top; i < calc_area.bottom; ++i) {
            for (long j = calc_area.left; j < calc_area.right; ++j) {
                double x = left_top.x + j * step_x;
                double y = left_top.y + i * step_y;
                double value = weight * ((get(i + 1, j) + get(i - 1, j)) / sqr_step_x
                                         + (get(i, j + 1) + get(i, j - 1)) / sqr_step_y - f(x, y));
                residual = std::max(residual, std::abs(value - get(i, j)));
                set(i, j, value);
            }
        }
    }

    double get_residual() {
        return residual;
    }

    void exchange(MPI_Comm &communicator) {
        MPI_Status status;
        int top, right, bottom, left;
        MPI_Cart_shift(communicator, 1, 1, &left, &right);
        MPI_Cart_shift(communicator, 0, 1, &top, &bottom);

        if (DEBUG) {
            printf("Exchanging data with top: %d, right: %d, bottom: %d, left: %d\n", top, right, bottom, left);
        }

        if (top != MPI_PROC_NULL) {
            MPI_Send(top_border.get(), columns, MPI_DOUBLE, top, 0, communicator);
        }
        if (bottom != MPI_PROC_NULL) {
            MPI_Recv(adjacent_bottom_border.get(), columns, MPI_DOUBLE, bottom, MPI_ANY_TAG, communicator, &status);
        }

        if (bottom != MPI_PROC_NULL) {
            MPI_Send(bottom_border.get(), columns, MPI_DOUBLE, bottom, 0, communicator);
        }
        if (top != MPI_PROC_NULL) {
            MPI_Recv(adjacent_top_border.get(), columns, MPI_DOUBLE, top, MPI_ANY_TAG, communicator, &status);
        }

        if (right != MPI_PROC_NULL) {
            MPI_Send(right_border.get(), rows, MPI_DOUBLE, right, 0, communicator);
        }
        if (left != MPI_PROC_NULL) {
            MPI_Recv(adjacent_left_border.get(), rows, MPI_DOUBLE, left, MPI_ANY_TAG, communicator, &status);
        }

        if (left != MPI_PROC_NULL) {
            MPI_Send(left_border.get(), rows, MPI_DOUBLE, left, 0, communicator);
        }
        if (right != MPI_PROC_NULL) {
            MPI_Recv(adjacent_right_border.get(), rows, MPI_DOUBLE, right, MPI_ANY_TAG, communicator, &status);
        }

        MPI_Barrier(communicator);
    }

    unique_ptr<double[]> serialize() {
        auto ptr = new double[rows * columns];
        for (long i = 0; i < rows; ++i) {
            for (long j = 0; j < columns; ++j) {
                ptr[i * columns + j] = get(i, j);
            }
        }
        return unique_ptr < double
        [] > (ptr);
    }
};

int main(int argc, char **argv) {
    int rank, processes_count;
    int processes_rows, processes_columns;
    long rows, columns;
    double top = 1, right = 1;
    MPI_Status status;
    Profiler profiler;

    std::cout.precision(5);
    std::cout << std::fixed;

    /*
     * (0,top) ...   (right,top)
     *  ...    ...       ...
     * (0,0)   ...    (right,0)
     */

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &processes_count);

    if (rank == ROOT) {
        std::cout << "Calculation of Poisson's equation." << std::endl;
        std::cout << "Enter how would you split the area (rows, columns): " << std::endl;
        std::cin >> rows >> columns;
    }

    MPI_Bcast(&rows, 1, MPI_LONG, ROOT, MPI_COMM_WORLD);
    MPI_Bcast(&columns, 1, MPI_LONG, ROOT, MPI_COMM_WORLD);

    processes_columns = (int) sqrt(processes_count);
    while (processes_columns > 1 && processes_count % processes_columns != 0) {
        processes_columns--;
    }

    assert(processes_count % processes_columns == 0);
    processes_rows = processes_count / processes_columns;

    if (rank == ROOT) {
        if (processes_columns == 1) {
            std::cout << "Using 1D topology with " << processes_count
                      << (processes_count == 1 ? " process" : " processes") << std::endl;
        } else {
            std::cout << "Using 2D topology with (" << processes_rows << " * "
                      << processes_columns << ") processes" << std::endl;
        }
    }

    profiler.start_preparing = current_time();
    int dimensions[2] = {processes_rows, processes_columns};
    int periods[2] = {0, 0};
    int coordinates[2];
    MPI_Comm communicator;

    MPI_Cart_create(MPI_COMM_WORLD, 2, dimensions, periods, 1, &communicator);
    MPI_Cart_coords(communicator, rank, 2, coordinates);

    double step_x = right / (columns - 1);
    double step_y = -top / (rows - 1);

    long first_columns = columns / processes_columns + columns % processes_columns;
    long other_columns = columns / processes_columns;
    long first_rows = rows / processes_rows + rows % processes_rows;
    long other_rows = rows / processes_rows;

    int process_i = coordinates[0];
    int process_j = coordinates[1];

    struct CellArea{
        long rows, rows_offset, columns, columns_offset;
    };

    auto calculate_area = [&](int i, int j) {
        long columns_offset = process_j == 0 ? 0 : first_columns + (process_j - 1) * other_columns;
        long rows_offset = process_i == 0 ? 0 : first_rows + (process_i - 1) * other_rows;
        long columns = process_j == 0 ? first_columns : other_columns;
        long rows = process_i == 0 ? first_rows : other_rows;
        return CellArea{rows, rows_offset, columns, columns_offset};
    };

    auto ca = calculate_area(process_i, process_j);
    double left_top_x = ca.columns_offset == 0 ? 0 : step_x * ca.columns_offset;
    double left_top_y = ca.rows_offset == 0 ? top : top + step_y * ca.rows_offset;

    Point point(left_top_x, left_top_y);
    Area world_area(0, columns, rows, 0);
    Area area(ca.rows_offset, ca.columns_offset + ca.columns,
              ca.rows_offset + ca.rows, ca.columns_offset);
    Cell cell(world_area, area, point, step_x, step_y);

    if (DEBUG) {
        printf("\nParameters for process #%d\n", rank);
        printf("\tprocess_i: %d\n\tprocess_j: %d\n", process_i, process_j);
        printf("\tarea.top: %ld\n\tarea.left: %ld\n\tarea.right: %ld\n\tarea.bottom: %ld\n",
               area.top, area.left, area.right, area.bottom);
        printf("\tleft_top.x: %f\n\tleft_top.y: %f\n\n", point.x, point.y);

    }

    MPI_Barrier(communicator);
    profiler.end_preparing = current_time();
    profiler.start_calculating = current_time();

    double max_residual = 1E20;
    long iterations_count = 0;

    while (max_residual > 1E-5) {
        cell.exchange(communicator);
        cell.calculate();
        iterations_count++;
        double residual = cell.get_residual();
        MPI_Allreduce(&residual, &max_residual, 1, MPI_DOUBLE, MPI_MAX, communicator);
    }
    profiler.end_calculating = current_time();
    profiler.start_sending = current_time();

    if (rank == ROOT) {
        vector <vector<double>> answer(rows, vector<double>(columns, 0));

        for (long i = 0; i < ca.rows; ++i) {
            for (long j = 0; j < ca.columns; ++j) {
                answer[i][j] = cell.get(i, j);
            }
        }

        for (long i = 1; i < processes_count; ++i) {
            MPI_Cart_coords(communicator, i, 2, coordinates);
            process_i = coordinates[0];
            process_j = coordinates[1];

            ca = calculate_area(process_i, process_j);

            unique_ptr<double[]> ptr(new double[ca.rows * ca.columns]);
            MPI_Recv(ptr.get(), ca.rows * ca.columns, MPI_DOUBLE, i, MPI_ANY_TAG, communicator, &status);

            for (long i = 0; i < ca.rows; ++i) {
                for (long j = 0; j < ca.columns; ++j) {
                    answer[ca.rows_offset + i][ca.columns_offset + j] = ptr[i * ca.columns + j];
                }
            }
        }
        profiler.end_sending = current_time();

        if (DEBUG && rows < 20 && columns < 20) {
            std::cout << std::endl;
            for (auto &row: answer) {
                for (auto &el: row) {
                    std::cout << el << '\t';
                }
                std::cout << std::endl;
            }
            std::cout << std::endl;
        }

        printf("\nDone!\n");
        printf("Iterations count: %.ld\n", iterations_count);
        printf("Time to prepare: %.3lfs\n", profiler.end_preparing - profiler.start_preparing);
        printf("Time to calculate: %.3lfs\n", profiler.end_calculating - profiler.start_calculating);
        printf("Time to send: %.3lfs\n", profiler.end_sending - profiler.start_sending);
        printf("Total time: %.3lfs\n", profiler.end_sending - profiler.start_preparing);
    } else {
        MPI_Send(cell.serialize().get(), ca.columns * ca.rows, MPI_DOUBLE, ROOT, 0, communicator);
    }

    MPI_Finalize();
}

double f(double x, double y) {
    return x * y;
}

double f_left(double y) {  // f_1
    return y * y;
}

double f_right(double y) {  // f_2
    return sin(y);
}

double f_bottom(double x) {  // f_3
    return x * x * x;
}

double f_top(double x) {  // f_4
    return x * x;
}

double current_time() {
    return clock() * 1. / CLOCKS_PER_SEC;
}
