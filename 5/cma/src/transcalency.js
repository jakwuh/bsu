require('console.table')
const {cloneDeep} = require('lodash')
const {max, pow, abs, exp} = Math
const {eval, lusolve, subtract, transpose} = require('mathjs')

const array = n => [...Array(n).keys()].map(_ => 0)
const range = (a, b, n = 1) => [...Array(n + 1).keys()].map(i => a + (b - a) / n * i)

const f = (x, t) => 0
const u0 = x => exp(-x)
const alpha0 = 0
const beta0 = 1
const mu0 = t => -exp(t)
const alpha1 = 1
const beta1 = 0
const mu1 = t => exp(t - 1)
const sigma = .5

const EPS = 1E-5
const N = 10
const vx = range(0, 1, N)
const vt = range(0, 1, N)
const h = abs(vx[1] - vx[0])

const matrix = array(N + 1).map(_ => array(N + 1))
matrix[0] = vx.map(u0)

for (let j = 1; j <= N; ++j) {
    const A = array(N + 1).map(_ => array(N + 1))
    const b = array(N + 1)
    const u_prev = matrix[j - 1]

    A[0][0] = beta0 / h - alpha0 + (beta0 * h) / (2 * h)
    A[0][1] = -beta0 / h
    b[0] = - mu0(vx[j]) + (beta0 * h) / (2 * h) * (u_prev[0] + h * f(vx[0], vt[j]))

    A[N][N - 1] = -beta1 / h
    A[N][N] = alpha1 + beta1 / h + beta1 * h / (2 * h)
    b[N] = mu1(vt[j]) + beta1 * h / (2 * h) * (u_prev[N] + h * f(vx[N], vt[j]))

    for (let i = 1; i < N; ++i) {
        A[i][i - 1] = -sigma/pow(h, 2)
        A[i][i] = 1 / h + 2 * sigma / pow(h, 2)
        A[i][i + 1] = -sigma/pow(h, 2)
        b[i] = u_prev[i] / h + (1 - sigma) / pow(h, 2) * 
            (u_prev[i + 1] - 2 * u_prev[i] + u_prev[i - 1]) + f(vx[i], vt[j - 1])
    }

    matrix[j] = transpose(lusolve(A, b))[0]
}

const prettify = row => row.map(v => Number(v.toPrecision(5)))
console.table(matrix.map(prettify))

const solution = [[1., 0.90484, 0.81873, 0.74082, 0.67032, 0.60653, 0.54881, 0.49659, 
  0.44933, 0.40657, 0.36788], [1.10518, 1.00001, 0.90485, 0.81874, 
  0.74083, 0.67033, 0.60654, 0.54882, 0.49659, 0.44933, 
  0.40657], [1.22143, 1.1052, 1.00002, 0.90486, 0.81875, 0.74084, 
  0.67034, 0.60655, 0.54882, 0.4966, 0.44934], [1.34989, 1.22143, 
  1.1052, 1.00003, 0.90486, 0.81875, 0.74084, 0.67034, 0.60654, 
  0.54882, 0.49659], [1.49187, 1.3499, 1.22144, 1.1052, 1.00003, 
  0.90486, 0.81875, 0.74084, 0.67034, 0.60654, 0.54882], [1.64879, 
  1.49189, 1.34992, 1.22146, 1.10522, 1.00004, 0.90487, 0.81876, 
  0.74085, 0.67034, 0.60655], [1.82223, 1.64882, 1.49192, 1.34994, 
  1.22148, 1.10524, 1.00006, 0.90489, 0.81878, 0.74086, 
  0.67035], [2.01391, 1.82226, 1.64885, 1.49194, 1.34997, 1.2215, 
  1.10526, 1.00007, 0.9049, 0.81878, 0.74086], [2.22576, 2.01395, 
  1.8223, 1.64888, 1.49197, 1.34999, 1.22152, 1.10527, 1.00008, 
  0.90491, 0.81879], [2.45985, 2.22576, 2.01396, 1.8223, 1.64889, 
  1.49197, 1.34999, 1.22151, 1.10526, 1.00007, 0.90489], [2.71853, 
  2.45983, 2.22575, 2.01394, 1.82229, 1.64887, 1.49195, 1.34997, 
  1.22149, 1.10524, 1.00005]]


console.table(subtract(solution, matrix).map(row => row.map(v => Number(v.toPrecision(3)).toExponential())))
