require('console.table')
const {sum, prod, factorial, subtract, mean, lusolve} = require('mathjs')
const {take, takeRight, isArray, last, first, ary, uniq, initia} = require('lodash')
const {exp, abs, floor, cos, pow, PI} = Math
const {log, table} = console

const a = 0, b = 2
const M = 0.1 * exp(2) + 0.9

const w = v => x => prod(v.map(vi => x - vi))
const wd = v => (x, i) => w(v.filter((_, ind) => ind !== i))(x)
const range = (a, b, n = 1) => [...Array(n + 1).keys()].map(i => a + (b - a) / n * i)
const R = v => x => M / factorial(v.length) * abs(w(v)(x))
const f = x => 0.1 * exp(x) + 0.9 * exp(-x) 
const fd = x => 0.1 * exp(x) - 0.9 * exp(-x)
const array = n => [...Array(n).keys()]

const diffFactory = x => function diff(...v) {
	if (uniq(v).length === 1) {
		if (v.length === 1) return f(x[v[0]])
		else return fd(x[v[0]])
	} else {
		return (diff(...v.slice(1)) - diff(...v.slice(0, v.length - 1))) / (x[last(v)] - x[first(v)])
	}
}

const R2 = v => x => abs(w(v)(x) * diffFactory([x, ...v])(...[...Array(v.length + 1).keys()]));

const print = ({name, n, x, p, Rn, fn, r}) => {
	log(`${name} for n = ${n}`)
	table([,
		['x', ...x],
		['f(x)', ...fn],
		['p(x)', ...p],
		['|p(x) - f(x)|', ...r],
		['R(x, n)', ...Rn]
	])
}

const lagrange = v => x => {
	return w(v)(x) * sum(v.map((xi, i) => f(xi) / (x - xi) / wd(v)(xi, i)))
}
const lagrangeTest = n => {
	const v = range(a, b, n)
	const x = [mean(take(v, 2)), mean(take(v.slice(floor(n / 2)), 2)), mean(takeRight(v, 2))]
	const p = x.map(lagrange(v))
	const fn = x.map(ary(f, 1))
	const r = subtract(p, x.map(ary(f, 1))).map(abs)
	const Rn = x.map(R(v))
	print({name: 'Lagrange', n, x, p, Rn, fn, r})
}

const newton = v => x => {
	const diff = diffFactory(v)
	return f(v[0]) + sum([...Array(v.length - 1).keys()].map(i => {
		return prod(take(v, i + 1).map(xi => x - xi)) * diff(...[...Array(i + 2).keys()])
	}))
}
const newtonTest = n => {
	const v = range(a, b, n)
	const x = [mean(take(v, 2)), mean(take(v.slice(floor(n / 2)), 2)), mean(takeRight(v, 2))]
	const p = x.map(newton(v))
	const fn = x.map(ary(f, 1))
	const r = subtract(p, x.map(ary(f, 1))).map(abs)
	const Rn = x.map(R2(v))
	print({name: 'Newton', n, x, p, Rn, fn, r})
}

const chebyshevTest = n => {
	const v = [...Array(n + 1).keys()].map(i => mean(a, b) + mean(b, -a) * cos(PI * (i + 1 / 2) / (n + 1)))
	const x = [mean(take(v, 2)), mean(take(v.slice(floor(n / 2)), 2)), mean(takeRight(v, 2))]
	const p = x.map(lagrange(v))
	const fn = x.map(ary(f, 1))
	const r = subtract(p, x.map(ary(f, 1))).map(abs)
	const Rn = x.map(() => M / factorial(n + 1) * pow(b - a, n) * pow(2, 1 - 2 * n))
	print({name: 'Chebyshev, Lagrange', n, x, p, Rn, fn, r})
}

const ermit = (z, v) => x => {
	const diff = diffFactory(v)
	return f(v[z[0]]) + sum([...Array(z.length - 1).keys()].map(i => {
		return prod(take(z, i + 1).map(zi => x - v[zi])) * diff(...take(z, i + 2))
	}))
}
const ermitTest = n => {
	const v = range(a, b, n)
	const x = [mean(take(v, 2)), mean(take(v.slice(floor(n / 2)), 2)), mean(takeRight(v, 2))]
	const z = [...Array(2 * (n + 1)).keys()].map(i => floor(i / 2))
	const p = x.map(ermit(z, v))
	const fn = x.map(ary(f, 1))
	const r = subtract(p, x.map(ary(f, 1))).map(abs)
	const Rn = x.map(R(v))
	print({name: 'Ermit', n, x, p, Rn, fn, r})
}

const lsm = (v, m) => x => {
	const n = v.length - 1
	const phi = i => x => prod(array(i).map(k => x).concat(1))
	const A = array(m + 1).map(i => array(n + 1).map(j => 
		sum(array(n + 1).map(k => phi(i)(v[k]) * phi(j)(v[k])))))
	const B = array(m + 1).map(i => sum(array(n + 1).map(k => f(v[k]) * phi(i)(v[k]))))
	const a = lusolve(A, B)
	return sum(a.map((c, i) => c[0] * phi(i)(x)))
}
const lsmTest = n => {
	const v = range(a, b, n)
	const x = [mean(take(v, 2)), mean(take(v.slice(floor(n / 2)), 2)), mean(takeRight(v, 2))]
	const p = x.map(lsm(v, n))
	const fn = x.map(ary(f, 1))
	const r = subtract(p, x.map(ary(f, 1))).map(abs)
	const Rn = x.map(R(v))
	print({name: 'LSM', n, x, p, Rn, fn, r})
}

const spline = (v, h) => x => {
	const i = v.findIndex((_, i) => v[i] <= x && x <= v[i + 1])
	const n = v.length - 1

	let A = array(n + 1).map(() => array(n + 1))
	A[0][0] = A[n][n] = 2
	A[0][1] = A[n][n - 1] = 0
	array(n - 1).map(i => {
		A[i + 1][i] = A[i + 1][i + 2] = 1 / 2
		A[i + 1][i + 1] = 2
	})
	let D = array(n + 1)
	D[0] = D[n] = 0
	array(n - 1).map(i => {
		D[i + 1] = 3 / 2 * (f(v[i + 1]) - 2 * f(v[i]) + f(v[i - 1]))
	})
	const M = lusolve(A, D).map(v => v[0])

	const B = f(v[i]) - h * h / 6 * M[i]
	const C = (f(v[i + 1]) - f(v[i])) / h - h / 6 * (M[i + 1] - M[i])
	return (M[i] * pow(v[i + 1] - x, 3) + M[i + 1] * pow(x - v[i], 3)) / 6 / h + C * (x - v[i]) + B
}
const splineTest = n => {
	const v = range(a, b, n)
	const h = (b - a) / n
	const x = [mean(take(v, 2)), mean(take(v.slice(floor(n / 2)), 2)), mean(takeRight(v, 2))]
	const p = x.map(spline(v, h))
	const fn = x.map(ary(f, 1))
	const r = subtract(p, x.map(ary(f, 1))).map(abs)
	const Rn = x.map(R(v))
	print({name: 'Spline', n, x, p, Rn, fn, r})
}

lagrangeTest(5)
lagrangeTest(10)
newtonTest(5)
newtonTest(10)
chebyshevTest(5)
chebyshevTest(10)
ermitTest(3)
ermitTest(5)
lsmTest(5)
lsmTest(10)
splineTest(5)
splineTest(10)
