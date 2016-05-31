const {sum} = require('mathjs');
const {exp, sin, sqrt, ceil, pow, abs, PI} = Math
const {log} = console

const a = 0, b = PI
const I = 12.0703463163896
const f = x => exp(x) * sin(x)
const fd2max = PI / 4

const print = (name, n, h, I, In, R, EPS) => {
	log(`
		Method: ${name}
		n: ${n}
		h: ${h}
		I: ${I}
		In: ${In}
		R: ${R}
		EPS: ${EPS || 'Not set'}`)
}

const rectangles = (f, a, b, n) => {
	const h = (b - a) / n
	const nodes = [...Array(n).keys()].map(i => a + h * i + h / 2)
	return h * sum(nodes.map(f))
}
const rectanglesTest = EPS => {
	const n = ceil(sqrt(fd2max * pow(b - a, 3) / 24 / EPS))
	const In = rectangles(f, 0, PI, n)
	print('Rectangles', n, (b - a) / n, I, In, abs(I - In), EPS)
}

const trapezoids = (f, a, b, n) => {
	const h = (b - a) / n
	const nodes = [...Array(n - 1).keys()].map(i => a + h * (i + 1))
	return h * ((f(a) + f(b)) / 2 + sum(nodes.map(f)))
}
const trapezoidsTest = EPS => {
	const n = ceil(sqrt(fd2max * pow(b - a, 3) / 12 / EPS))
	const In = trapezoids(f, 0, PI, n)
	print('Trapezoids', n, (b - a) / n, I, In, abs(I - In), EPS)
}

const runge = (I, m, n, EPS) => {
	while (abs(I(n) - I(2 * n)) / (pow(2, m) - 1) > EPS) 
		return runge(I, m, n * 2, EPS)
	return {n, In: I(2 * n)}
}
const rungeTest = EPS => {
	const S = n => rectangles(f, a, b, n)
	const {n, In} = runge(S, 2, 1, EPS)
	print('Runge', n, (b - a) / n, I, In, abs(I - In), EPS)
}

const gauss = (f, a, b) => {
	const x = [-sqrt(0.6), 0, sqrt(0.6)]
	const A = [5 / 9, 8 / 9, 5 / 9]
	return (b - a) / 2 * sum([0, 1, 2].map(i => A[i] * f((b - a) / 2 * x[i] + (a + b) / 2)))
}
const gaussTest = () => {
	const n = 3
	const In = gauss(f, 0, PI)
	print('Gauss', n, (b - a) / n, I, In, abs(I - In))
}

[rectanglesTest, trapezoidsTest, rungeTest].map(f => {
	f(pow(10, -3))
	f(pow(10, -5))
	f(pow(10, -8))
})
gaussTest()




