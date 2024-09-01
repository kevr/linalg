#include "logging.hpp"
#include "matrix.hpp"
#include "random.hpp"
#include "vector.hpp"

template <typename T, std::size_t LR, std::size_t LC, std::size_t RR,
          std::size_t RC>
void dot_test()
{
    linalg::matrix<T, LR, LC> a(rng::random<T>{});
    linalg::matrix<T, RR, RC> b(rng::random<T>{});

    auto result = linalg::dot(a, b);

    print("- a\n{}", display(a));
    print("- b\n{}", display(b));
    print("- dot result\n{}", display(result));
}

int main(int, const char *[])
{
    using T = double;

    // Matrix operations
    linalg::matrix<T, 2, 5> matrix(rng::random<T>{});
    print("- matrix\n{}", display(matrix));

    auto matrix2 = matrix + matrix;
    print("- 2matrix\n{}", display(matrix2));
    print("- (2matrix - matrix)\n{}", display(matrix2 - matrix));

    matrix2 -= matrix;
    print("- (2matrix -= matrix)\n{}", display(matrix2));

    // Scalar/Matrix operations
    print("- 1 + matrix\n{}", display(1.0 + matrix));
    print("- 1 - matrix\n{}", display(1.0 - matrix));
    print("- 1 * matrix\n{}", display(1.0 * matrix));
    print("- 1 / matrix\n{}", display(1.0 / matrix));

    // Vector/Matrix operations
    std::vector<T> input(matrix.rows(), 2.0);
    print("- dot(m)\n> {}", display(linalg::dot(input, matrix)));

    // Vector operations
    print("- random_vector\n> {}", display(vector::random<T>(2)));
    std::vector<T> vec({2.0, 3.0});
    print("- vec\n> {}", display(vec));
    print("- vec + vec\n> {}", display(vec + vec));
    print("- vec - vec\n> {}", display(vec - vec));
    print("- vec * vec\n> {}", display(vec * vec));
    print("- vec / vec\n> {}", display(vec / vec));

    // Scalar/Vector operations
    print("- 1 + vec\n> {}", display(1.0 + vec));
    print("- 1 - vec\n> {}", display(1.0 - vec));
    print("- 1 * vec\n> {}", display(1.0 * vec));
    print("- 1 / vec\n> {}", display(1.0 / vec));

    vec -= vec;
    print("- vec -= vec\n> {}", display(vec));

    dot_test<T, 2, 2, 2, 2>();
    dot_test<T, 1, 3, 3, 2>();
    dot_test<T, 3, 3, 3, 3>();

    return 0;
}
