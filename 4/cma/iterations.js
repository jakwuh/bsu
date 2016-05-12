// Simple iterations: the solution -0.287652966289323±0.00001 was found with 26 iterations
// Newton: the solution -0.28768207245164723±0.00001 was found with 3 iterations
'use strict';
const EPS = 1E-5, TOL = 0.5

let log = console.log, M = Math

let f = x => (M.exp(x) + M.sqrt(1 + M.exp(2 * x)) - 2)
let fd = x => (M.exp(x) + M.exp(2 * x) / M.sqrt(M.exp(2 * x) + 1))
let phiN = x => (x - (f(x) / fd(x)))
let phiS = x => (x - f(x) / 5)

let bisection = (r) => {
	while (r.b - r.a > TOL) {
	    let c = (r.b + r.a) / 2
	    if (M.abs(f(c)) < EPS) return { a: c, b: c }
	    r[f(c) * f(r.a) < 0 ? 'b' : 'a'] = c
	}
	return r
}

let solve = r => {
	{
		let x = (r.a + r.b) / 2, count = 1
    	while (M.abs(x - (x = phiS(x))) > EPS && ++count);
    	log(`Simple iterations: the solution ${x}\xB1${EPS} was found with ${count} iterations`)
	}
	{
		let x = (r.a + r.b) / 2, count = 1
    	while (M.abs(x - (x = phiN(x))) > EPS && ++count);
    	log(`Newton: the solution ${x}\xB1${EPS} was found with ${count} iterations`)
	}
}

solve(bisection({ a: -1, b: 1 }))