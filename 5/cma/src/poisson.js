require('console.table')
const {cloneDeep} = require('lodash')
const {max, pow, abs} = Math
const {eval, subtract, transpose} = require('mathjs')

const array = n => [...Array(n).keys()].map(_ => 0)
const range = (a, b, n = 1) => [...Array(n + 1).keys()].map(i => a + (b - a) / n * i)

const f = (x, y) => eval('e^(-x y^2)', {x, y})
const top = (x, y) => x * (x - 1) * (x - 2)
const right = (x, y) => y * (y - 2) * (y - 3)
const bottom = (x, y) => (x - 1) * (x - 2)
const left = (x, y) => (y - 2) * (y - 3)

const EPS = 1E-5
const N = 10
const vx = range(1, 2, N)
const vy = range(3, 2, N)
const hx = abs(vx[1] - vx[0])
const hy = abs(vy[1] - vy[0])
const matrix = array(N + 1).map(_ => array(N + 1))

for (let i = 0; i < N + 1; ++i) {
    matrix[0][i] = top(vx[i], vy[0])
    matrix[N][i] = bottom(vx[i], vy[N])
    matrix[i][0] = left(vx[0], vy[i])
    matrix[i][N] = right(vx[N], vy[i])
}

let eps = 1
let iters_count = 0
let c = 1 / (2 / pow(hx, 2) + 2 / pow(hy, 2))
while (eps > EPS && ++iters_count) {
    eps = 0
    let prev_matrix = cloneDeep(matrix)
    for (let i = 1; i < N; ++i) {
        for (let j = N - 1; j > 0; --j) {
            matrix[i][j] = c * (f(vx[i], vy[j]) + 
                (prev_matrix[i + 1][j] + matrix[i - 1][j]) / pow(hx, 2) +
                (prev_matrix[i][j + 1] + matrix[i][j - 1]) / pow(hy, 2))
            eps = max(eps, abs(matrix[i][j] - prev_matrix[i][j]))
        }
    }
}

const solution = 
[[0., -0.099, -0.192, -0.273, -0.336, -0.375, -0.384, -0.357, -0.288, 
-0.171, 0.], [-0.09, -0.14483, -0.20528, -0.26218, -0.30918, -0.3414, 
-0.35521, -0.34869, -0.32286, -0.28523, -0.261], [-0.16, -0.18609, 
-0.22251, -0.26147, -0.29735, -0.32648, -0.3472, -0.36061, -0.37192, 
-0.3933, -0.448], [-0.21, -0.21743, -0.23755, -0.26414, -0.29261, 
-0.32037, -0.34717, -0.37573, -0.4128, -0.47044, -0.567], [-0.24, 
-0.23625, -0.24642, -0.26525, -0.28897, -0.31572, -0.34602, -0.38324, 
-0.43419, -0.5096, -0.624], [-0.25, -0.2413, -0.24686, -0.2618, 
-0.28268, -0.308, -0.33853, -0.37769, -0.4318, -0.51023, -0.625], 
[-0.24, -0.2322, -0.23818, -0.25273, -0.27233, -0.29549, -0.32291, 
-0.35771, -0.40557, -0.47479, -0.576], [-0.21, -0.20949, -0.22119, 
-0.23893, -0.2588, -0.27912, -0.30035, -0.32511, -0.35836, -0.40763, 
-0.483], [-0.16, -0.17485, -0.19854, -0.22338, -0.24517, -0.26219, 
-0.27463, -0.28445, -0.2956, -0.31469, -0.352], [-0.09, -0.13204, 
-0.17529, -0.21125, -0.23659, -0.25012, -0.25186, -0.24288, -0.22551, 
-0.20428, -0.189], [0., -0.09, -0.16, -0.21, -0.24, -0.25, -0.24, 
-0.21, -0.16, -0.09, 0.]]

console.log('Iterations count:', iters_count)
console.table(subtract(solution, matrix).map(row => row.map(v => Number(v.toPrecision(3)).toExponential())))
