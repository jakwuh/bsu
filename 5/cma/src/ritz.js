require('console.table')
const {sin, cos, abs, pow} = Math
const {lusolve, subtract, transpose, sum} = require('mathjs')

const array = n => [...Array(n).keys()].map(_ => 0)
const range = (a, b, n = 1) => [...Array(n + 1).keys()].map(i => a + (b - a) / n * i)

const n = 5
const N = 10
const x = range(0, 1, N)
const y = x.map(x => x - 1)
const f = x => x * sin(2 * x)
const k = x => pow(cos(x), 2)
const q = x => sin(2 * x)

const phi = [
    x => x - 1,
    ...[...Array(n).keys()].map(i => i + 1).map(i => x => pow(x, i + 1) * pow(x - 1, 2))
]

const phid = [
    x => 1,
    ...[...Array(n).keys()].map(i => i + 1).map(i => x => (i + 1) * pow(x, i) * pow(x - 1, 2) + 2 * pow(x, i + 1) * (x - 1))
]

const rectangles = (f, a = 0, b = 1, n = 1000) => {
    const h = (b - a) / n
    const nodes = [...Array(n).keys()].map(i => a + h * i + h / 2)
    return h * sum(nodes.map(f))
}

const A = array(n).map(_ => array(n))
const b = array(n)

for (let i = 1; i <= n; ++i) {
    for (let j = 1; j <= n; ++j) {
        const createF = (i, j) => x => k(x) * phid[i](x) * phid[j](x) + q(x) * phi[i](x) * phi[j](x)
        A[i - 1][j - 1] = rectangles(createF(i, j))
        b[i - 1] = rectangles(x => f(x) * phi[i](x)) - rectangles(createF(0, i)) 
    }
}

const ai = transpose(lusolve(A, b))[0]

const u = x => phi[0](x) + sum(phi.slice(1).map((f, i) => f(x) * ai[i]))
const answer = x.map(u)

const prettify = x => Number(x.toPrecision(6)).toExponential()
console.table([x.map(x => x.toFixed(2)), subtract(y, answer).map(prettify)])

