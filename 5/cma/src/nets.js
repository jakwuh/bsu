require('console.table')
const {sin, cos, abs, pow} = Math
const {lusolve, subtract, transpose} = require('mathjs')

const array = n => [...Array(n).keys()].map(_ => 0)
const range = (a, b, n = 1) => [...Array(n + 1).keys()].map(i => a + (b - a) / n * i)

const N = 10
const x = range(0, 1, N)
const f = x.map(x => x * sin(2 * x))
const k = x.map(x => pow(cos(x), 2))
const q = x.map(x => sin(2 * x))
const h = abs(x[1] - x[0])
const y = x.map(x => x - 1)

const alpha0 = 0
const mu0 = -1
const alpha1 = 1
const mu1 = pow(cos(1), 2)

let A = array(N + 1).map(_ => array(N + 1))
let b = array(N + 1)

for (let i = 1; i < N; ++i) {
    A[i][i - 1] = -(k[i + 1] - k[i - 1]) / (4 * pow(h, 2)) + k[i] / pow(h, 2)
    A[i][i] = -2 * k[i] / pow(h, 2) - q[i]
    A[i][i + 1] = (k[i + 1] - k[i - 1]) / (4 * pow(h, 2)) + k[i] / pow(h, 2)
    b[i] = -f[i]
}

A[0][0] = h * q[0] / 2 + alpha0 + (k[0] + k[1]) / (2 * h)
A[0][1] = -(k[0] + k[1]) / (2 * h)
b[0] = mu0 + h * f[0] / 2

A[N][N - 1] = -(k[N] + k[N - 1]) / (2 * h)
A[N][N] = - A[N][N - 1] + alpha1 + h * q[N] / 2
b[N] = mu1 + h * f[N] / 2

const prettify = x => Number(x.toPrecision(6)).toExponential()
console.table([x.map(x => x.toFixed(2)), subtract(y, transpose(lusolve(A, b))[0]).map(prettify)])